/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2017 UniPro <ugene@unipro.ru>
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

#include <U2Core/DNASequenceObject.h>
#include <U2Core/MultipleSequenceAlignmentObject.h>
#include <U2Core/U2DbiUtils.h>
#include <U2Core/U2ObjectDbi.h>
#include <U2Core/U2OpStatusUtils.h>
#include <U2Core/U2SafePoints.h>

#include <U2Gui/GUIUtils.h>

#include "UndoRedoFramework.h"
#include "ov_msa/MSACollapsibleModel.h"

namespace U2 {


UndoRedoFramework::UndoRedoFramework(QObject *p, GObject *_obj)
    : QObject(p),
      obj(_obj),
      stateComplete(true),
      undoStepsAvailable(0),
      redoStepsAvailable(0)
{
    SAFE_POINT(obj != NULL, "NULL GObject!", );

    undoAction = new QAction(this);
    undoAction->setText(tr("Undo"));
    undoAction->setIcon(QIcon(":core/images/undo.png"));
    undoAction->setShortcut(QKeySequence::Undo);
    GUIUtils::updateActionToolTip(undoAction);

    redoAction = new QAction(this);
    redoAction->setText(tr("Redo"));
    redoAction->setIcon(QIcon(":core/images/redo.png"));
    redoAction->setShortcut(QKeySequence::Redo);
    GUIUtils::updateActionToolTip(redoAction);

    checkUndoRedoEnabled();

    connect(obj, SIGNAL(si_lockedStateChanged()), SLOT(sl_lockedStateChanged()));
    connect(undoAction, SIGNAL(triggered()), this, SLOT(sl_undo()));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(sl_redo()));
}

void UndoRedoFramework::sl_completeStateChanged(bool _stateComplete) {
    stateComplete = _stateComplete;
}

void UndoRedoFramework::sl_lockedStateChanged() {
    checkUndoRedoEnabled();
}

void UndoRedoFramework::checkUndoRedoEnabled() {
    SAFE_POINT(obj != NULL, "NULL MSA Object!", );

    if (obj->isStateLocked() || !stateComplete) {
        undoAction->setEnabled(false);
        redoAction->setEnabled(false);
        return;
    }

    U2OpStatus2Log os;
    DbiConnection con(obj->getEntityRef().dbiRef, os);
    SAFE_POINT_OP(os, );

    U2ObjectDbi* objDbi = con.dbi->getObjectDbi();
    SAFE_POINT(NULL != objDbi, "NULL Object Dbi!", );

    bool enableUndo = objDbi->canUndo(obj->getEntityRef().entityId, os);
    SAFE_POINT_OP(os, );
    bool enableRedo = objDbi->canRedo(obj->getEntityRef().entityId, os);
    SAFE_POINT_OP(os, );

    undoAction->setEnabled(enableUndo);
    redoAction->setEnabled(enableRedo);
}

void UndoRedoFramework::sl_undo() {
    SAFE_POINT(obj != NULL, "NULL MSA Object!", );

    U2OpStatus2Log os;
    U2EntityRef entityRef =  obj->getEntityRef();

    assert(stateComplete);
    assert(!obj->isStateLocked());

    DbiConnection con(entityRef.dbiRef, os);
    SAFE_POINT_OP(os, );

    U2ObjectDbi* objDbi = con.dbi->getObjectDbi();
    SAFE_POINT(NULL != objDbi, "NULL Object Dbi!", );

    objDbi->undo(entityRef.entityId, os);
    SAFE_POINT_OP(os, );

    updateObject(MaModificationType_Undo);
}

void UndoRedoFramework::sl_redo() {
    SAFE_POINT(obj != NULL, "NULL MSA Object!", );

    U2OpStatus2Log os;
    U2EntityRef entityRef = obj->getEntityRef();

    assert(stateComplete);
    assert(!obj->isStateLocked());

    DbiConnection con(entityRef.dbiRef, os);
    SAFE_POINT_OP(os, );

    U2ObjectDbi* objDbi = con.dbi->getObjectDbi();
    SAFE_POINT(NULL != objDbi, "NULL Object Dbi!", );

    objDbi->redo(entityRef.entityId, os);
    SAFE_POINT_OP(os, );

    updateObject(MaModificationType_Redo);
}

SequenceUndoRedoFramework::SequenceUndoRedoFramework(QObject *p, U2SequenceObject *seqObj)
    : UndoRedoFramework(p, seqObj) {
    connect(seqObj, SIGNAL(si_sequenceChanged()), SLOT(sl_sequenceChanged()));

    // TODO_SVEDIT: seq object should notify about changes
    connect(undoAction, SIGNAL(triggered(bool)), SLOT(sl_sequenceChanged()));
    connect(redoAction, SIGNAL(triggered(bool)), SLOT(sl_sequenceChanged()));
}

void SequenceUndoRedoFramework::sl_sequenceChanged() {
    checkUndoRedoEnabled();
}

U2SequenceObject* SequenceUndoRedoFramework::getSequenceObject() {
    return dynamic_cast<U2SequenceObject*>(obj);
}

void SequenceUndoRedoFramework::updateObject(MaModificationType type) {
    U2SequenceObject* seq = getSequenceObject();
    seq->sl_resetDataCaches();
    emit si_updateRequired();
}

MsaUndoRedoFramework::MsaUndoRedoFramework(QObject *p, MultipleAlignmentObject *maObj)
    : UndoRedoFramework(p, maObj) {
    connect(maObj, SIGNAL(si_alignmentChanged(const MultipleAlignment&, const MaModificationInfo&)),
                   SLOT(sl_alignmentChanged()));
    connect(maObj, SIGNAL(si_completeStateChanged(bool)), SLOT(sl_completeStateChanged(bool)));
}

void MsaUndoRedoFramework::sl_alignmentChanged() {
    checkUndoRedoEnabled();
}

void MsaUndoRedoFramework::updateObject(MaModificationType type) {
    MaModificationInfo modInfo;
    modInfo.type = type;
    getMaObject()->updateCachedMultipleAlignment(modInfo);
}

MultipleAlignmentObject* MsaUndoRedoFramework::getMaObject() const {
    // TODO_SVEDIT: add safe_point for casting
    return dynamic_cast<MultipleAlignmentObject*>(obj);
}


} // namespace
