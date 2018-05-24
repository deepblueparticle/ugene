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

#include "ExternalToolsWidget.h"

#include <U2Core/U2SafePoints.h>

#include <U2Lang/Dataset.h>
#include <U2Lang/URLAttribute.h>
#include <U2Lang/URLContainer.h>
#include <U2Lang/WorkflowUtils.h>


namespace U2 {

ExternalToolsWidgetController::ExternalToolsWidgetController() : toolsWidget(NULL) {
    timer = new QTimer;
    timer->setInterval(1000);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), SLOT(sl_timerShouts()));
}

ExternalToolsWidget* ExternalToolsWidgetController::getWidget(const QWebElement &container, Dashboard *parent) {
    if(NULL == toolsWidget) {
        toolsWidget = new ExternalToolsWidget(container, parent, this);
        connect(this, SIGNAL(si_update()), toolsWidget, SLOT(sl_onLogUpdate()));
    }
    return toolsWidget;
}

LogEntry ExternalToolsWidgetController::getEntry(int index) const {
    SAFE_POINT(index >= 0 && index < log.count(), "Invalid index", LogEntry());
    return log.at(index);
}

void ExternalToolsWidgetController::sl_onLogChanged(U2::Workflow::Monitor::LogEntry entry) {
    log << entry;
    if (!timer->isActive() && NULL != toolsWidget) {
        timer->start();
    }
}

void ExternalToolsWidgetController::sl_timerShouts() {
    emit si_update();
}

const QString ExternalToolsWidget::ID = "external tools";
const QString ExternalToolsWidget::LINE_BREAK("break_line");
const QString ExternalToolsWidget::SINGLE_QUOTE("s_quote");
const QString ExternalToolsWidget::BACK_SLASH("b_slash");

ExternalToolsWidget::ExternalToolsWidget(const QWebElement &_container,
                                         Dashboard *parent,
                                         const ExternalToolsWidgetController *_ctrl) :
    DashboardWidget(_container, ID, parent),
    ctrl(_ctrl)
{
    SAFE_POINT(NULL != ctrl, "Controller is NULL", );

    const WorkflowMonitor *workflowMonitor = dashboard->monitor();
    SAFE_POINT(NULL != workflowMonitor, "NULL workflow monitor!", );

    container.evaluateJavaScript("lwInitConteiner(this, 'params_tab_id_0')");

    foreach (LogEntry entry, ctrl->getLog()) {
        addInfoToWidget(entry);
    }

    lastEntryIndex = ctrl->getLogSize() - 1;
}

void ExternalToolsWidget::sl_onLogUpdate() {
    SAFE_POINT(sender() == ctrl, "Unexpected sender", );

    int lastLogIndex = ctrl->getLogSize() - 1;
    LogEntry entry = ctrl->getEntry(lastEntryIndex + 1);
    ++lastEntryIndex;

    for (; lastEntryIndex < lastLogIndex; lastEntryIndex++) {
        LogEntry curEntry = ctrl->getEntry(lastEntryIndex + 1);
        if (isSameNode(curEntry, entry) &&
                entry.logType != PROGRAM_PATH &&
                entry.logType != ARGUMENTS) {
            // accumulate
            entry.lastLine += curEntry.lastLine;
        } else {
            // node changed, commit
            addInfoToWidget(entry);
            entry = curEntry;
        }
    }

    addInfoToWidget(entry);
}

void ExternalToolsWidget::addInfoToWidget(const LogEntry &entry) {
    const QString tabId = "log_tab_id_" + entry.actorName;
    const QString runId = entry.toolName + " run " + QString::number(entry.runNumber);
    const QString mapId = tabId + "_" + runId;
    if (!taskCount.contains(mapId)) {
        taskCount[mapId] = 0;
    }

    QString lastPartOfLog = entry.lastLine;

    lastPartOfLog.replace(QRegExp("\\n"), LINE_BREAK);
    lastPartOfLog.replace(QRegExp("\\r"), "");
    lastPartOfLog.replace("'", SINGLE_QUOTE);
    lastPartOfLog.replace('\\', BACK_SLASH);

    QString addLogFunc = "lwAddTreeNode";
    addLogFunc += "('" + runId + "', ";
    addLogFunc += "'" + entry.actorName + "', ";
    addLogFunc += "'" + tabId + "', ";

    switch(entry.logType) {
    case ERROR_LOG:
        addLogFunc += "'" + lastPartOfLog + "', ";
        addLogFunc += "'0', ";
        addLogFunc += "'error')";
        container.evaluateJavaScript(addLogFunc);
        break;
    case OUTPUT_LOG:
        addLogFunc += "'" + lastPartOfLog + "', ";
        addLogFunc += "'0', ";
        addLogFunc += "'output')";
        container.evaluateJavaScript(addLogFunc);
        break;
    case PROGRAM_PATH:
        addLogFunc += "'" + lastPartOfLog + "', ";
        addLogFunc += "'" + QString::number(++taskCount[mapId]) + "', ";
        addLogFunc += "'program')";
        container.evaluateJavaScript(addLogFunc);
        break;
    case ARGUMENTS:
        addLogFunc += "'" + lastPartOfLog + "', ";
        addLogFunc += "'" + QString::number(taskCount[mapId]) + "', ";
        addLogFunc += "'arguments')";
        container.evaluateJavaScript(addLogFunc);
        break;
    }
}

bool ExternalToolsWidget::isSameNode(const LogEntry& prev, const LogEntry& cur) const {
    return prev.actorName == cur.actorName &&
            prev.logType == cur.logType &&
            prev.runNumber == cur.runNumber &&
            prev.toolName == cur.toolName;
}

} // namespace U2
