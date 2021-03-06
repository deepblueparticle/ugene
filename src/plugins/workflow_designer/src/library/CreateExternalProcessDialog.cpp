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

#include <QMessageBox>
#include <QWizardPage>

#include <U2Core/AppContext.h>
#include <U2Core/BaseDocumentFormats.h>
#include <U2Core/DocumentModel.h>
#include <U2Core/QObjectScopedPointer.h>
#include <U2Core/U2SafePoints.h>

#include <U2Designer/DelegateEditors.h>

#include <U2Gui/DialogUtils.h>
#include <U2Gui/HelpButton.h>

#include <U2Lang/ActorPrototypeRegistry.h>
#include <U2Lang/BaseTypes.h>
#include <U2Lang/ConfigurationEditor.h>
#include <U2Lang/ExternalToolCfg.h>
#include <U2Lang/HRSchemaSerializer.h>
#include <U2Lang/WorkflowEnv.h>
#include <U2Lang/WorkflowSettings.h>

#include "CfgExternalToolModel.h"
#include "CreateExternalProcessDialog.h"
#include "WorkflowEditorDelegates.h"
#include "../util/WorkerNameValidator.h"

namespace U2 {

class ExecStringValidator : public QValidator {
public:
    ExecStringValidator(QObject *parent = 0)
        : QValidator(parent) {}
    State validate(QString &input, int &) const {
        if (input.contains("\"")) {
            return Invalid;
        }
        return Acceptable;
    }
};

CreateExternalProcessDialog::CreateExternalProcessDialog(QWidget *p, ExternalProcessConfig *cfg, bool lastPage)
: QWizard(p), initialCfg(NULL), lastPage(lastPage) {
    ui.setupUi(this);

    new U2::HelpButton(this, button(QWizard::HelpButton), "2097199");

    connect(ui.addInputButton, SIGNAL(clicked()), SLOT(sl_addInput()));
    connect(ui.addOutputButton, SIGNAL(clicked()), SLOT(sl_addOutput()));
    connect(ui.deleteInputButton, SIGNAL(clicked()), SLOT(sl_deleteInput()));
    connect(ui.deleteOutputButton, SIGNAL(clicked()), SLOT(sl_deleteOutput()));
    connect(ui.addAttributeButton, SIGNAL(clicked()), SLOT(sl_addAttribute()));
    connect(ui.deleteAttributeButton, SIGNAL(clicked()), SLOT(sl_deleteAttribute()));
    connect(this, SIGNAL(currentIdChanged(int)), SLOT(sl_validatePage(int)));

    QFontMetrics info(ui.descr1TextEdit->font());
    ui.descr1TextEdit->setFixedHeight(info.height() * 8);
    ui.descr2TextEdit->setFixedHeight(info.height() * 10);
    ui.descr3TextEdit->setFixedHeight(info.height() * 7);
    ui.descr4TextEdit->setFixedHeight(info.height() * 12);

    ui.inputTableView->setModel(new CfgExternalToolModel(true));
    ui.outputTableView->setModel(new CfgExternalToolModel(false));
    ui.attributesTableView->setModel(new CfgExternalToolModelAttributes());

    ui.inputTableView->setItemDelegate(new ProxyDelegate());
    ui.outputTableView->setItemDelegate(new ProxyDelegate());
    ui.attributesTableView->setItemDelegate(new ProxyDelegate());

    ui.inputTableView->horizontalHeader()->setStretchLastSection(true);
    ui.outputTableView->horizontalHeader()->setStretchLastSection(true);
    ui.attributesTableView->horizontalHeader()->setStretchLastSection(true);
    ui.inputTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui.outputTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui.attributesTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    QFontMetrics fm(ui.inputTableView->font());
    ui.inputTableView->setColumnWidth(1, fm.width(SEQ_WITH_ANNS)*1.5);
    ui.outputTableView->setColumnWidth(1, fm.width(SEQ_WITH_ANNS)*1.5);
    ui.templateLineEdit->setValidator(new ExecStringValidator(this));    ui.nameLineEdit->setValidator(new WorkerNameValidator(this));

    initialCfg = new ExternalProcessConfig(*cfg);
    init(cfg);

    editing = true;
    connect(ui.nameLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(sl_validateName(const QString &)));
    connect(ui.templateLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(sl_validateCmdLine(const QString &)));
    connect(ui.inputTableView->model(), SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)), SLOT(validateDataModel(const QModelIndex &, const QModelIndex &)));
    connect(ui.outputTableView->model(), SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)), SLOT(validateDataModel(const QModelIndex &, const QModelIndex &)));
    connect(ui.attributesTableView->model(), SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)), SLOT(validateAttributeModel(const QModelIndex &, const QModelIndex &)));
    descr1 = ui.descr1TextEdit->toHtml();
    //validateNextPage();

    DialogUtils::setWizardMinimumSize(this);
}

static void clearModel(QAbstractItemModel *model) {
    int count = model->rowCount();
    while (count > 0) {
        model->removeRow(0);
        count--;
    }
}

void CreateExternalProcessDialog::init(ExternalProcessConfig *cfg) {
    int ind = 0;
    clearModel(ui.inputTableView->model());
    foreach(const DataConfig &dataCfg, cfg->inputs) {
        ui.inputTableView->model()->insertRow(0, QModelIndex());
        QModelIndex index = ui.inputTableView->model()->index(ind,0);
        ui.inputTableView->model()->setData(index, dataCfg.attrName);
        index = ui.inputTableView->model()->index(ind,1);
        ui.inputTableView->model()->setData(index, dataCfg.type);
        index = ui.inputTableView->model()->index(ind,2);
        ui.inputTableView->model()->setData(index, dataCfg.format);
        index = ui.inputTableView->model()->index(ind,3);
        ui.inputTableView->model()->setData(index, dataCfg.description);
        ind++;
    }

    ind = 0;
    clearModel(ui.outputTableView->model());
    foreach(const DataConfig &dataCfg, cfg->outputs) {
        ui.outputTableView->model()->insertRow(0, QModelIndex());
        QModelIndex index = ui.outputTableView->model()->index(ind,0);
        ui.outputTableView->model()->setData(index, dataCfg.attrName);
        index = ui.outputTableView->model()->index(ind,1);
        ui.outputTableView->model()->setData(index, dataCfg.type);
        index = ui.outputTableView->model()->index(ind,2);
        ui.outputTableView->model()->setData(index, dataCfg.format);
        index = ui.outputTableView->model()->index(ind,3);
        ui.outputTableView->model()->setData(index, dataCfg.description);
        ind++;
    }

    ind = 0;
    clearModel(ui.attributesTableView->model());
    foreach(const AttributeConfig &attrCfg, cfg->attrs) {
        ui.attributesTableView->model()->insertRow(0, QModelIndex());
        QModelIndex index = ui.attributesTableView->model()->index(ind,0);
        ui.attributesTableView->model()->setData(index, attrCfg.attrName);
        index = ui.attributesTableView->model()->index(ind,1);
        ui.attributesTableView->model()->setData(index, attrCfg.type);
        index = ui.attributesTableView->model()->index(ind,2);
        ui.attributesTableView->model()->setData(index, attrCfg.description);
        ind++;
    }

    ui.nameLineEdit->setText(cfg->name);
    ui.descriptionTextEdit->setText(cfg->description);
    ui.templateLineEdit->setText(cfg->cmdLine);
    ui.prompterTextEdit->setText(cfg->templateDescription);
}

void CreateExternalProcessDialog::sl_addInput() {
    ui.inputTableView->model()->insertRow(0, QModelIndex());
    validateDataModel();
}

void CreateExternalProcessDialog::sl_addOutput() {
    ui.outputTableView->model()->insertRow(0, QModelIndex());
    validateDataModel();
}

void CreateExternalProcessDialog::sl_deleteInput() {
    QModelIndex index = ui.inputTableView->currentIndex();
    ui.inputTableView->model()->removeRow(index.row());
    validateDataModel();
}

void CreateExternalProcessDialog::sl_deleteOutput() {
    QModelIndex index = ui.outputTableView->currentIndex();
    ui.outputTableView->model()->removeRow(index.row());
    validateDataModel();
}

void CreateExternalProcessDialog::sl_addAttribute() {
    ui.attributesTableView->model()->insertRow(0, QModelIndex());
    validateAttributeModel();
}

void CreateExternalProcessDialog::sl_deleteAttribute() {
    QModelIndex index = ui.attributesTableView->currentIndex();
    ui.attributesTableView->model()->removeRow(index.row());
    validateAttributeModel();
}

CreateExternalProcessDialog::CreateExternalProcessDialog( QWidget *p /* = NULL*/ )
: QWizard(p), initialCfg(NULL), lastPage(false) {
    ui.setupUi(this);

    new U2::HelpButton(this, button(QWizard::HelpButton), "2097199");

    connect(ui.addInputButton, SIGNAL(clicked()), SLOT(sl_addInput()));
    connect(ui.addOutputButton, SIGNAL(clicked()), SLOT(sl_addOutput()));
    connect(ui.deleteInputButton, SIGNAL(clicked()), SLOT(sl_deleteInput()));
    connect(ui.deleteOutputButton, SIGNAL(clicked()), SLOT(sl_deleteOutput()));
    connect(ui.addAttributeButton, SIGNAL(clicked()), SLOT(sl_addAttribute()));
    connect(ui.deleteAttributeButton, SIGNAL(clicked()), SLOT(sl_deleteAttribute()));
    //connect(button(QWizard::FinishButton), SIGNAL(clicked()), SLOT(sl_OK()));
    connect(button(QWizard::NextButton), SIGNAL(clicked()), SLOT(sl_generateTemplateString()));
    //connect(button(QWizard::NextButton), SIGNAL(clicked()), SLOT(validateNextPage()));
    connect(this, SIGNAL(currentIdChanged(int)), SLOT(sl_validatePage(int)));

    connect(ui.nameLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(sl_validateName(const QString &)));
    connect(ui.templateLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(sl_validateCmdLine(const QString &)));

    ui.inputTableView->setModel(new CfgExternalToolModel(true));
    ui.outputTableView->setModel(new CfgExternalToolModel(false));
    ui.attributesTableView->setModel(new CfgExternalToolModelAttributes());

    connect(ui.inputTableView->model(), SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)), SLOT(validateDataModel(const QModelIndex &, const QModelIndex &)));
    connect(ui.outputTableView->model(), SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)), SLOT(validateDataModel(const QModelIndex &, const QModelIndex &)));
    connect(ui.attributesTableView->model(), SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)), SLOT(validateAttributeModel(const QModelIndex &, const QModelIndex &)));

    ui.inputTableView->setItemDelegate(new ProxyDelegate());
    ui.outputTableView->setItemDelegate(new ProxyDelegate());
    ui.attributesTableView->setItemDelegate(new ProxyDelegate());

    ui.inputTableView->horizontalHeader()->setStretchLastSection(true);
    ui.outputTableView->horizontalHeader()->setStretchLastSection(true);
    ui.attributesTableView->horizontalHeader()->setStretchLastSection(true);

    ui.inputTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui.outputTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui.attributesTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    QFontMetrics fm(ui.inputTableView->font());
    ui.inputTableView->setColumnWidth(1, fm.width(SEQ_WITH_ANNS)*1.5);
    ui.outputTableView->setColumnWidth(1, fm.width(SEQ_WITH_ANNS)*1.5);

    QFontMetrics info(ui.descr1TextEdit->font());
    ui.descr1TextEdit->setFixedHeight(info.height() * 8);
    ui.descr2TextEdit->setFixedHeight(info.height() * 10);
    ui.descr3TextEdit->setFixedHeight(info.height() * 7);
    ui.descr4TextEdit->setFixedHeight(info.height() * 12);

    descr1 = ui.descr1TextEdit->toHtml();
    editing = false;

    ui.templateLineEdit->setValidator(new ExecStringValidator(this));
    ui.nameLineEdit->setValidator(new WorkerNameValidator(this));

    DialogUtils::setWizardMinimumSize(this);
}

CreateExternalProcessDialog::~CreateExternalProcessDialog() {
    delete initialCfg;
}

void CreateExternalProcessDialog::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    if (lastPage) {
        for (int i=0; i<(pageIds().size()-1); i++) {
            next();
        }
    }
}

QString removeEmptyLines(const QString &str) {
    QStringList res;
    foreach(const QString &s, str.split(QRegExp("(\n|\r)"))) {
        if (!s.trimmed().isEmpty()) {
            res.append(s);
        }
    }
    return res.join("\r\n");
}

void CreateExternalProcessDialog::accept() {
    CfgExternalToolModel *model;
    cfg = new ExternalProcessConfig();
    cfg->name = ui.nameLineEdit->text();
    cfg->description = removeEmptyLines(ui.descriptionTextEdit->toPlainText());
    cfg->templateDescription = removeEmptyLines(ui.prompterTextEdit->toPlainText());

    model = static_cast<CfgExternalToolModel*>(ui.inputTableView->model());
    foreach(CfgExternalToolItem *item, model->getItems()) {
        cfg->inputs << item->itemData;
    }

    model = static_cast<CfgExternalToolModel*>(ui.outputTableView->model());
    foreach(CfgExternalToolItem *item, model->getItems()) {
        cfg->outputs << item->itemData;
    }

    CfgExternalToolModelAttributes *aModel = static_cast<CfgExternalToolModelAttributes*>(ui.attributesTableView->model());
    foreach(AttributeItem *item, aModel->getItems()) {
        AttributeConfig attributeData;
        attributeData.attrName = item->getName();
        attributeData.type = item->getDataType();
        attributeData.description = item->getDescription();
        cfg->attrs << attributeData;
    }

    cfg->cmdLine = ui.templateLineEdit->text();

    if(!validate()) {
        return;
    }

    if (NULL != initialCfg) {
        if (!(*initialCfg == *cfg)) {
            int res = QMessageBox::question(this, tr("Warning"),
                tr("You have changed the structure of the element (name, slots, attributes' names and types). "
                "All elements on the scene would be removed. Do you really want to change it?\n"
                "You could also reset the dialog to the initial state."),
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Reset, QMessageBox::No);
            if (QMessageBox::No == res) {
                return;
            } else if (QMessageBox::Reset == res) {
                init(initialCfg);
                return;
            }
        }
    }

    QString str = HRSchemaSerializer::actor2String(cfg);
    QString dir = WorkflowSettings::getExternalToolDirectory();
    QDir d(dir);
    if(!d.exists()) {
        d.mkdir(dir);
    }
    cfg->filePath = dir + cfg->name + ".etc";
    QFile file(cfg->filePath);
    file.open(QIODevice::WriteOnly);
    file.write(str.toLatin1());
    file.close();

    done(QDialog::Accepted);
}

bool CreateExternalProcessDialog::validate() {
    QString title = tr("Create Element");
    if(cfg->inputs.isEmpty() && cfg->outputs.isEmpty())  {
        QMessageBox::critical(this, title, tr("Please set the input/output data."));
        return false;
    }

    if(cfg->cmdLine.isEmpty()) {
        QMessageBox::critical(this, title, tr("Please set the command line to run external tool."));
        return false;
    }

    if(cfg->name.isEmpty()) {
        QMessageBox::critical(this, title, tr("Please set the name for the new element."));
        return false;
    }

    QRegExp invalidSymbols("[\\.,:;\\?]");
    if(cfg->name.contains(invalidSymbols)) {
        QMessageBox::critical(this, title, tr("Invalid symbols in the element name."));
        return false;
    }

    if(WorkflowEnv::getProtoRegistry()->getProto(cfg->name) && !editing) {
        QMessageBox::critical(this, title, tr("Element with this name already exists."));
        return false;
    }

    invalidSymbols = QRegExp("\\W");
    QStringList nameList;
    foreach(const DataConfig & dc, cfg->inputs) {
        if(dc.attrName.isEmpty()) {
            QMessageBox::critical(this, title, tr("For one or more parameter name was not set."));
            return false;
        }
        if(dc.attrName.contains(invalidSymbols)) {
            QMessageBox::critical(this, title, tr("Invalid symbols in a name.").arg(dc.attrName));
            return false;
        }
        nameList << dc.attrName;
    }
    foreach(const DataConfig & dc, cfg->outputs) {
        if(dc.attrName.isEmpty()) {
            QMessageBox::critical(this, title, tr("For one or more parameter name was not set."));
            return false;
        }
        if(dc.attrName.contains(invalidSymbols)) {
            QMessageBox::critical(this, title, tr("Invalid symbols in a name.").arg(dc.attrName));
            return false;
        }
        nameList << dc.attrName;
    }
    foreach(const AttributeConfig & ac, cfg->attrs) {
        if(ac.attrName.isEmpty()) {
            QMessageBox::critical(this, title, tr("For one or more parameter name was not set."));
            return false;
        }
        if(ac.attrName.contains(invalidSymbols)) {
            QMessageBox::critical(this, title, tr("Invalid symbols in a name.").arg(ac.attrName));
            return false;
        }
        nameList << ac.attrName;
    }

    if(nameList.removeDuplicates() > 0) {
        QMessageBox::critical(this, title, tr("The same name of element parameters was found"));
        return false;
    }

    foreach(const QString &str, nameList) {
        if(!cfg->cmdLine.contains("$" + str)) {
            QObjectScopedPointer<QMessageBox> msgBox = new QMessageBox(this);
            msgBox->setWindowTitle(title);
            msgBox->setText(tr("You don't use parameter %1 in template string. Continue?").arg(str));
            msgBox->addButton(tr("Continue"), QMessageBox::ActionRole);
            QPushButton *cancel = msgBox->addButton(tr("Abort"), QMessageBox::ActionRole);
            msgBox->exec();
            CHECK(!msgBox.isNull(), false);
            if(msgBox->clickedButton() == cancel) {
                return false;
            }
        }
    }

    return true;
}

void CreateExternalProcessDialog::sl_generateTemplateString() {
    QString cmd = "<My tool>";

    CfgExternalToolModel *model = static_cast<CfgExternalToolModel*>(ui.inputTableView->model());
    foreach(CfgExternalToolItem *item, model->getItems()) {
        cmd += " $" + item->itemData.attrName;
    }

    model = static_cast<CfgExternalToolModel*>(ui.outputTableView->model());
    foreach(CfgExternalToolItem *item, model->getItems()) {
        cmd += " $" + item->itemData.attrName;
    }

    CfgExternalToolModelAttributes *aModel = static_cast<CfgExternalToolModelAttributes*>(ui.attributesTableView->model());
    int i = 0;
    foreach(AttributeItem *item, aModel->getItems()) {
        i++;
        cmd +=  " -p" + QString::number(i) + " $" + item->getName();
    }

    ui.templateLineEdit->setText(cmd);
}

bool CreateExternalProcessDialog::validateProcessName(const QString &name, QString &error) {
    if(name.isEmpty()) {
        error = tr("Please set the name for the new element.");
        return false;
    }

    QRegExp spaces("\\s");
    if(name.contains(spaces)) {
        error = tr("Spaces in the element name.");
        return false;
    }

    QRegExp invalidSymbols("\\W");
    if(name.contains(invalidSymbols)) {
        error = tr("Invalid symbols in the element name.");
        return false;
    }

    if(WorkflowEnv::getProtoRegistry()->getProto(name) && !editing) {
        error = tr("Element with this name already exists.");
        return false;
    }

    return true;
}

static QString statusTemplate = QString("<font color=\"%1\">%2</font>");
void CreateExternalProcessDialog::sl_validateName( const QString &text) {
    QString error;
    bool res = validateProcessName(text, error);

    button(QWizard::NextButton)->setEnabled(res);
    QString statusStr;
    if (res) {
        statusStr = statusTemplate.arg("green").arg(tr("It is the correct name"));
    } else {
        statusStr = statusTemplate.arg("#A6392E").arg(error);
    }
    ui.descr1TextEdit->setText(descr1.arg(statusStr));
}

void CreateExternalProcessDialog::sl_validateCmdLine( const QString & text) {
    if(text.isEmpty()) {
        button(QWizard::FinishButton)->setEnabled(false);
    } else {
        button(QWizard::FinishButton)->setEnabled(true);
    }
}

void CreateExternalProcessDialog::validateDataModel(const QModelIndex &, const QModelIndex & ) {
    bool res = true;
    CfgExternalToolModel *model;

    QRegExp invalidSymbols("\\W");
    QStringList nameList;
    model = static_cast<CfgExternalToolModel*>(ui.inputTableView->model());
    foreach(CfgExternalToolItem *item, model->getItems()) {
        if(item->itemData.attrName.isEmpty()) {
            //QMessageBox::critical(this, title, tr("For one or more parameter name was not set."));
            res = false;
        }
        if(item->itemData.attrName.contains(invalidSymbols)) {
            //QMessageBox::critical(this, title, tr("Invalid symbols in a name.").arg(dc.attrName));
            res = false;
        }
        nameList << item->itemData.attrName;
    }

    model = static_cast<CfgExternalToolModel*>(ui.outputTableView->model());
    foreach(CfgExternalToolItem *item, model->getItems()) {
        if(item->itemData.attrName.isEmpty()) {
            //QMessageBox::critical(this, title, tr("For one or more parameter name was not set."));
            res = false;
        }
        if(item->itemData.attrName.contains(invalidSymbols)) {
            //QMessageBox::critical(this, title, tr("Invalid symbols in a name.").arg(dc.attrName));
            res = false;
        }
        nameList << item->itemData.attrName;
    }



    if(nameList.removeDuplicates() > 0) {
        //QMessageBox::critical(this, title, tr("The same name of element parameters was found"));
        res = false;
    }

    if(nameList.isEmpty()) {
        res = false;
    }
    button(QWizard::NextButton)->setEnabled(res);
}

void CreateExternalProcessDialog::validateAttributeModel(const QModelIndex &, const QModelIndex & ) {
    bool res = true;
    CfgExternalToolModel *model;

    QRegExp invalidSymbols("\\W");
    QStringList nameList;
    model = static_cast<CfgExternalToolModel*>(ui.inputTableView->model());
    foreach(CfgExternalToolItem *item, model->getItems()) {
        if(item->itemData.attrName.isEmpty()) {
            //QMessageBox::critical(this, title, tr("For one or more parameter name was not set."));
            res = false;
        }
        if(item->itemData.attrName.contains(invalidSymbols)) {
            //QMessageBox::critical(this, title, tr("Invalid symbols in a name.").arg(dc.attrName));
            res = false;
        }
        nameList << item->itemData.attrName;
    }

    model = static_cast<CfgExternalToolModel*>(ui.outputTableView->model());
    foreach(CfgExternalToolItem *item, model->getItems()) {
        if(item->itemData.attrName.isEmpty()) {
            //QMessageBox::critical(this, title, tr("For one or more parameter name was not set."));
            res = false;
        }
        if(item->itemData.attrName.contains(invalidSymbols)) {
            //QMessageBox::critical(this, title, tr("Invalid symbols in a name.").arg(dc.attrName));
            res = false;
        }
        nameList << item->itemData.attrName;
    }

    CfgExternalToolModelAttributes *aModel = static_cast<CfgExternalToolModelAttributes*>(ui.attributesTableView->model());
    foreach(AttributeItem *item, aModel->getItems()) {
        if(item->getName().isEmpty()) {
            //QMessageBox::critical(this, title, tr("For one or more parameter name was not set."));
            res = false;
        }
        if(item->getName().contains(invalidSymbols)) {
            //QMessageBox::critical(this, title, tr("Invalid symbols in a name.").arg(ac.attrName));
            res = false;
        }
        nameList << item->getName();
    }


    if(nameList.removeDuplicates() > 0) {
        //QMessageBox::critical(this, title, tr("The same name of element parameters was found"));
        res = false;
    }
    button(QWizard::NextButton)->setEnabled(res);
}

void CreateExternalProcessDialog::validateNextPage() {
    int id = currentId();
    switch(id) {
        case 0:
            sl_validateName(ui.nameLineEdit->text());
            break;
        case 1:
            validateDataModel();
            break;
        case 2:
            validateAttributeModel();
        case 3:
            sl_validateCmdLine(ui.templateLineEdit->text());
    }
}

void CreateExternalProcessDialog::sl_validatePage(int id) {
    switch(id) {
        case 0:
            sl_validateName(ui.nameLineEdit->text());
            break;
        case 1:
            validateDataModel();
            break;
        case 2:
            validateAttributeModel();
        case 3:
            sl_validateCmdLine(ui.templateLineEdit->text());
    }
}

}
