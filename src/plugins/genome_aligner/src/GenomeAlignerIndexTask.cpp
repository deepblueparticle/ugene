/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2011 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <U2Core/DNASequenceObject.h>
#include <U2Core/DNASequence.h>
#include <U2Core/AppResources.h>
#include <U2Core/AppContext.h>
#include <U2Core/AppSettings.h>
#include <U2Core/Timer.h>
#include <U2Algorithm/OpenCLGpuRegistry.h>
#include "U2Formats/StreamSequenceReader.h"
#include <QtEndian>
#include <QtGlobal>
#include "GenomeAlignerIndex.h"

#include "GenomeAlignerIndexTask.h"

namespace U2 {

double GenomeAlignerIndexTask::MEMORY_DIVISION = 2.0/3.0;

GenomeAlignerIndexTask::GenomeAlignerIndexTask(const GenomeAlignerIndexSettings &settings)
: Task("Building genome aligner's index", TaskFlag_None), objLens(NULL),  unknownChar('N')
{
    baseFileName = settings.indexFileName;
    w = 31; // to avoid +- overflow

    bitTable = bt.getBitMaskCharBits(DNAAlphabet_NUCL);
    bitCharLen = bt.getBitMaskCharBitsNum(DNAAlphabet_NUCL);

    index = new GenomeAlignerIndex();
    index->baseFileName = baseFileName;
    index->unknownChar = unknownChar;
    index->bitFilter = ((BMType)1<<(bitCharLen * w))-1;
    this->settings = settings;
}

GenomeAlignerIndexTask::~GenomeAlignerIndexTask() {
}

SAType getPartStartPos(SAType seqLength, int parts, int curPart) {
    SAType start = (seqLength/parts)*curPart;
    if (curPart > 0) {
        start -= GenomeAlignerIndex::overlapSize;
    }
    return start;
}

SAType getPartLength(SAType seqLength, int parts, int curPart) {
    SAType length = 0;
    if (curPart < parts - 1) {
        length = (seqLength/parts) + GenomeAlignerIndex::overlapSize;
    } else {
        length = seqLength - (seqLength/parts)*curPart;
    }
    if (curPart > 0) {
        length += GenomeAlignerIndex::overlapSize;
    }
    return length;
}

void GenomeAlignerIndexTask::run() {
    QByteArray error;
    bool res = index->deserialize(error);
    if (!res) {
        algoLog.details(error + " Index file is corrupted. I will try to create a new index file.");
    }
    index->build = !(res && (index->seqPartSize == settings.seqPartSize));
    if (!index->build) {
        index->build = !QFile::exists(baseFileName + QString(".") + GenomeAlignerIndex::REF_INDEX_EXTENSION);
        seqLength = index->seqLength;
    }
    if (index->build) {
        reformatSequence();
        if (isCanceled() || hasErrors()) {
            return;
        }
        seqLength = objLens[objCount-1];
        index->seqLength = seqLength;
        index->w = w;
        index->seqPartSize = settings.seqPartSize;
    }

    MAX_ELEM_COUNT_IN_MEMORY = settings.seqPartSize*1024*1024;
    int parts = seqLength/(MAX_ELEM_COUNT_IN_MEMORY - 2*GenomeAlignerIndex::overlapSize) + 1;
    index->indexPart.partCount = parts;
    index->indexPart.seqStarts = new SAType[parts];
    index->indexPart.seqLengths = new SAType[parts];
    index->indexPart.saLengths = new SAType[parts];
    index->indexPart.partFiles = new QFile*[parts];

    int partLen = 0;
    if (1 == parts) {
        partLen = seqLength;
    } else {
        partLen = MAX_ELEM_COUNT_IN_MEMORY;
    }

    SAType start = 0;
    SAType length = 0;
    for (int i=0; i<parts; i++) {
        start = getPartStartPos(seqLength, parts, i);
        length = getPartLength(seqLength, parts, i);

        index->indexPart.seqStarts[i] = start;
        index->indexPart.seqLengths[i] = length;
        index->indexPart.partFiles[i] = new QFile(baseFileName + "." + QByteArray::number(i) + "." + GenomeAlignerIndex::SARRAY_EXTENSION);
        if (!index->build) {
            index->build = !index->indexPart.partFiles[i]->exists();
        }
    }

    
    if (!index->openIndexFiles()) {
        setError("Can't open some of index files");
        return;
    }
    memFreeSize = MEM_FOR_READS*1024*1024;
    gpuFreeSize = memFreeSize;
    SAType maxLength = index->indexPart.getMaxLength();

    try {
        index->indexPart.bitMask = new BMType[maxLength];
        index->indexPart.sArray = new SAType[maxLength];
        index->indexPart.seq = new char[maxLength];
    } catch(std::bad_alloc e) {
        setError("Can't allocate this amount of memory. Try to close some of your programs or to decrease \"maxMemorySize\"-option");
        return;
    }
    if (settings.justBuildIndex) {
        for (int i=0; i<parts; i++) {
            index->build = true;
            index->loadPart(i);
            index->indexPart.partFiles[i]->close();
        }
    }
}

void GenomeAlignerIndexTask::reformatSequence() {
    StreamSequenceReader seqReader;
    QList<GUrl> urls;
    urls.append(GUrl(settings.refFileName));
    bool init = seqReader.init(urls);
    if (!init) {
        setError(tr("Can not init short reads loader. %1").arg(seqReader.getErrorMessage()));
        return;
    }

    objCount = 0;
    QList<quint32> seqLens;

    QFile newRefFile(baseFileName + QString(".") + GenomeAlignerIndex::REF_INDEX_EXTENSION);
    newRefFile.open(QIODevice::WriteOnly);
    bool firstSeq = true;
    while (seqReader.hasNext()) {
        objCount++;
        const DNASequenceObject *obj = seqReader.getNextSequenceObject();
        if (NULL == obj) {
            setError("Reference object type must be a sequence, but not a multiple alignment");
            return;
        }
        if (DNAAlphabet_NUCL != obj->getAlphabet()->getType()) {
            setError("Unsupported file format: alphabet type is not NUCL");
            return;
        }
        const DNASequence &seq = obj->getDNASequence();
        seqLens.append(seq.length());
        newRefFile.write(seq.constData());
        if (firstSeq) {
            index->seqObjName = seq.getName() + QString("_and_others");
            firstSeq = false;
        }
    }
    newRefFile.close();

    if (0 == objCount) {
        setError(QString("Unsupported file format or empty reference in %1").arg(settings.refFileName));
        return;
    }
    index->objLens = new quint32[objCount];
    index->objCount = objCount;
    objLens = index->objLens;
    int i = 0;
    quint32 prev = 0;
    foreach (quint32 len, seqLens) {
        objLens[i] = prev + len;
        prev = objLens[i];
        i++;
    }
}

} //U2
