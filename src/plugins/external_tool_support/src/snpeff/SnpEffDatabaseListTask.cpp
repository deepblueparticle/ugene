/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2016 UniPro <ugene@unipro.ru>
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

#include "SnpEffDatabaseListTask.h"
#include "SnpEffTask.h"
#include "SnpEffSupport.h"

#include <U2Core/AppContext.h>
#include <U2Core/Settings.h>

#include <QDir>
#include <QFileInfo>

namespace U2 {

#define SNPEFF_DATABASE_LIST_SETTINGS + "snpEffDatabaseList"

SnpEffDatabaseListTask::SnpEffDatabaseListTask()
    : ExternalToolSupportTask(tr("SnpEff Database List task"), TaskFlags_FOSE_COSC) {
    dbListFilePath = AppContext::getSettings()->getValue(SNPEFF_DATABASE_LIST_SETTINGS, QVariant(""), true).toString();
}

void SnpEffDatabaseListTask::prepare() {
    if (!dbListFilePath.isEmpty() && QFileInfo(dbListFilePath).size() != 0) {
        return;
    }

    QString iniFile = AppContext::getSettings()->fileName();
    dbListFilePath = QFileInfo(iniFile).absoluteDir().absolutePath();
    dbListFilePath += QString(QDir::separator()) + "SnpEff_DB.list";

    const QStringList args = {"databases"};
    ExternalToolRunTask* etTask = new ExternalToolRunTask(ET_SNPEFF, args, new SnpEffParser(),
                                                          "", QStringList(), QString(), true);
    setListenerForTask(etTask);
    etTask->setStandartOutputFile(dbListFilePath);
    addSubTask(etTask);
}

void SnpEffDatabaseListTask::run() {
    if (stateInfo.isCoR()) {
        return;
    }
    coreLog.info(dbListFilePath);
    AppContext::getSettings()->setValue(SNPEFF_DATABASE_LIST_SETTINGS, dbListFilePath, true);
}

} // namespace U2
