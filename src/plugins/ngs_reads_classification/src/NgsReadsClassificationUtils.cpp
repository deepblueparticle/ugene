/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2018 UniPro <ugene@unipro.ru>
 * http://ugene.net
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

#include <QFileInfo>

#include <U2Core/GUrlUtils.h>

#include "NgsReadsClassificationUtils.h"

namespace U2 {

QString NgsReadsClassificationUtils::getClassificationFileName(const QString &sourceFileUrl, const QString &toolName, const QString &extension, bool trunkate) {
    static const QStringList pairedSuffixes = QStringList() << "-R1" << "-R2"
                                                            << "_1" << "_2"
                                                            << "_R1_001" << "_R2_001"
                                                            << "_R1" << "_R2";

    QString baseName = QFileInfo(sourceFileUrl).completeBaseName();
    if (trunkate) {
        foreach (const QString &suffix, pairedSuffixes) {
            if (baseName.endsWith(suffix)) {
                baseName.chop(suffix.length());
                break;
            }
        }
    }
    return baseName + QString("_%1_classification.%2").arg(toolName).arg(extension);
}

}   // namespace U2
