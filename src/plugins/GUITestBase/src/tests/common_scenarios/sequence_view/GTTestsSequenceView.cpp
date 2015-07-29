/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2015 UniPro <ugene@unipro.ru>
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

#include "GTTestsSequenceView.h"
#include "api/GTClipboard.h"
#include "api/GTComboBox.h"
#include "api/GTLineEdit.h"
#include "api/GTMouseDriver.h"
#include "api/GTGlobals.h"
#include "api/GTWidget.h"
#include "api/GTAction.h"
#include "api/GTMenu.h"
#include "api/GTFile.h"
#include "api/GTFileDialog.h"
#include "api/GTSequenceReadingModeDialog.h"
#include "api/GTKeyboardDriver.h"
#include "api/GTRadioButton.h"
#include "GTUtilsCircularView.h"
#include "GTUtilsProject.h"
#include "GTUtilsProjectTreeView.h"
#include "GTUtilsAnnotationsTreeView.h"
#include "GTUtilsMdi.h"
#include "GTUtilsSequenceView.h"
#include "GTUtilsTaskTreeView.h"
#include "runnables/qt/PopupChooser.h"
#include "runnables/ugene/corelibs/U2Gui/ExportImageDialogFiller.h"
#include "runnables/ugene/corelibs/U2Gui/RangeSelectionDialogFiller.h"
#include "runnables/ugene/ugeneui/SaveProjectDialogFiller.h"
#include "runnables/ugene/plugins/dna_export/ExportSequencesDialogFiller.h"
#include "runnables/ugene/plugins_3rdparty/primer3/Primer3DialogFiller.h"
#include "runnables/ugene/ugeneui/SequenceReadingModeSelectorDialogFiller.h"
#include "runnables/ugene/plugins/enzymes/FindEnzymesDialogFiller.h"
#include "runnables/qt/MessageBoxFiller.h"
#include <U2View/DetView.h>
#include <U2Core/AppContext.h>
#include <U2View/ADVConstants.h>

#if (QT_VERSION < 0x050000) //Qt 5
#include <QtGui/QApplication>
#else
#include <QtWidgets/QApplication>
#endif

namespace U2 {

namespace GUITest_common_scenarios_sequence_view {

GUI_TEST_CLASS_DEFINITION(test_0002) {
//    disable circular view for protein sequences (0002400)

//    1. Open file samples/PDB/1CF7.pdb
//    Expected state: 'Show circular view' button disabled for 1CF7 chain 1 sequence and 1CF7 chain 2 sequence, but enabled for others

    GTFileDialog::openFile(os, dataDir+"samples/PDB/", "1CF7.PDB");
    GTGlobals::sleep(3000);

    QWidget *w0 = GTWidget::findWidget(os, "ADV_single_sequence_widget_0");
    QWidget *w1 = GTWidget::findWidget(os, "ADV_single_sequence_widget_1");
    QWidget *w2 = GTWidget::findWidget(os, "ADV_single_sequence_widget_2");
    QWidget *w3 = GTWidget::findWidget(os, "ADV_single_sequence_widget_3");

    GTGlobals::FindOptions f;
    f.failIfNull=false;

    QWidget *button0 = GTWidget::findWidget(os,"CircularViewAction",w0,f);
    QWidget *button1 = GTWidget::findWidget(os,"CircularViewAction",w1,f);
    QWidget *button2 = GTWidget::findWidget(os,"CircularViewAction",w2);
    QWidget *button3 = GTWidget::findWidget(os,"CircularViewAction",w3);
    GTGlobals::sleep(3000);

    CHECK_SET_ERR(button0 == NULL, "b0 is not NULL");
    CHECK_SET_ERR(button1 == NULL, "b1 is not NULL");
    CHECK_SET_ERR(button2 != NULL, "b2 is NULL");
    CHECK_SET_ERR(button3 != NULL, "b3 is NULL");
}

GUI_TEST_CLASS_DEFINITION(test_0002_1) {

    GTFileDialog::openFile(os, dataDir+"samples/PDB/", "1CF7.PDB");
    GTGlobals::sleep(3000);

    QWidget *w0 = GTWidget::findWidget(os, "ADV_single_sequence_widget_0");
    QWidget *w1 = GTWidget::findWidget(os, "ADV_single_sequence_widget_1");
    QWidget *w2 = GTWidget::findWidget(os, "ADV_single_sequence_widget_2");
    QWidget *w3 = GTWidget::findWidget(os, "ADV_single_sequence_widget_3");

    QAbstractButton* b0 = GTAction::button(os,"complement_action", w0);
    QAbstractButton* b1 = GTAction::button(os,"complement_action", w1);
    QAbstractButton* b2 = GTAction::button(os,"complement_action", w2);
    QAbstractButton* b3 = GTAction::button(os,"complement_action", w3);
    GTGlobals::sleep(3000);

    CHECK_SET_ERR(b0 == NULL, "b0 is not NULL");
    CHECK_SET_ERR(b1 == NULL, "b1 is not NULL");
    CHECK_SET_ERR(b2 != NULL, "b2 is NULL");
    CHECK_SET_ERR(b3 != NULL, "b3 is NULL");

    }
GUI_TEST_CLASS_DEFINITION(test_0002_2) {

    GTFileDialog::openFile(os, dataDir+"samples/PDB/", "1CF7.PDB");
    GTGlobals::sleep(3000);

    QWidget *w0 = GTWidget::findWidget(os, "ADV_single_sequence_widget_0");
    QWidget *w1 = GTWidget::findWidget(os, "ADV_single_sequence_widget_1");
    QWidget *w2 = GTWidget::findWidget(os, "ADV_single_sequence_widget_2");
    QWidget *w3 = GTWidget::findWidget(os, "ADV_single_sequence_widget_3");

    QAbstractButton* b0 = GTAction::button(os,"translation_action", w0);
    QAbstractButton* b1 = GTAction::button(os,"translation_action", w1);
    QAbstractButton* b2 = GTAction::button(os,"translation_action", w2);
    QAbstractButton* b3 = GTAction::button(os,"translation_action", w3);
    GTGlobals::sleep(3000);

    CHECK_SET_ERR(b0 == NULL, "b0 is not NULL");
    CHECK_SET_ERR(b1 == NULL, "b1 is not NULL");
    CHECK_SET_ERR(b2 != NULL, "b2 is NULL");
    CHECK_SET_ERR(b3 != NULL, "b3 is NULL");

    }

GUI_TEST_CLASS_DEFINITION(test_0003) {
//    Unnecessary buttons are enabled in zoom view (0001251)

//    1. Open file samples/FASTA/human_T1.fa

//    2. Hide details view with button {Toggle view->Hide details view}, if it already hided skip this step.
//    Expected state: buttons 'Show amino translations' and 'Show amino strand' are disabled

//    3. Show details view with button {Toggle view->Show details view}
//    Expected state: buttons 'Show amino translations' and 'Show amino strand' becomes enabled

    GTFileDialog::openFile(os, dataDir + "samples/FASTA/", "human_T1.fa");
    GTGlobals::sleep();

    QWidget *toggleViewButton = GTWidget::findWidget(os, "toggleViewButton");
    Runnable *chooser = new PopupChooser(os, QStringList() << "toggleDetailsView");
    GTUtilsDialog::waitForDialog(os, chooser);
    GTWidget::click(os, toggleViewButton);
    GTGlobals::sleep();

    GTGlobals::sleep();
    QAbstractButton* translation = GTAction::button(os, "translation_action");

    CHECK_SET_ERR(translation -> isEnabled() == false, "button is not disabled");

    GTGlobals::sleep();
    QAbstractButton* complement = GTAction::button(os, "complement_action");

    CHECK_SET_ERR(complement -> isEnabled() == false, "button is not disabled");

    Runnable *chooser1 = new PopupChooser(os, QStringList() << "toggleDetailsView");
    GTUtilsDialog::waitForDialog(os, chooser1);
    GTWidget::click(os, toggleViewButton);
    GTGlobals::sleep();

    GTGlobals::sleep();
    QAbstractButton* translation1 = GTAction::button(os, "translation_action");
    GTGlobals::sleep();
    CHECK_SET_ERR(translation1 -> isEnabled() == true, "button is not enabled");


    GTGlobals::sleep();
    QAbstractButton* complement1 = GTAction::button(os, "complement_action");

    GTGlobals::sleep();
    CHECK_SET_ERR(complement1 -> isEnabled() == true, "button is not enabled");
    }
GUI_TEST_CLASS_DEFINITION(test_0003_1) {

    GTFileDialog::openFile(os, dataDir + "samples/FASTA/", "human_T1.fa");
    GTGlobals::sleep();

    QWidget* ext_button = GTWidget::findWidget(os, "qt_toolbar_ext_button", GTWidget::findWidget(os, "mwtoolbar_activemdi"));
    if(ext_button != NULL && ext_button->isVisible()){
        GTWidget::click(os, ext_button);
    }

    QWidget *toggleViewButton = GTWidget::findWidget(os, "toggleViewButton");
    Runnable *chooser = new PopupChooser(os, QStringList() << "toggleAllSequenceViews");
    GTUtilsDialog::waitForDialog(os, chooser);
    GTWidget::click(os, toggleViewButton);
    GTGlobals::sleep();

    GTGlobals::sleep();
    QAbstractButton* translation = GTAction::button(os, "translation_action");

    CHECK_SET_ERR(translation -> isEnabled() == false, "button is not disabled");

    GTGlobals::sleep();
    QAbstractButton* complement = GTAction::button(os, "complement_action");

    CHECK_SET_ERR(complement -> isEnabled() == false, "button is not disabled");

    Runnable *chooser1 = new PopupChooser(os, QStringList() << "toggleAllSequenceViews");
    GTUtilsDialog::waitForDialog(os, chooser1);
    GTWidget::click(os, toggleViewButton);
    GTGlobals::sleep();

    GTGlobals::sleep();
    QAbstractButton* translation1 = GTAction::button(os, "translation_action");

    GTGlobals::sleep();
    CHECK_SET_ERR(translation1 -> isEnabled() == true, "button is not enabled");

    GTGlobals::sleep();
    QAbstractButton* complement1 = GTAction::button(os, "complement_action");

    GTGlobals::sleep();
    CHECK_SET_ERR(complement1 -> isEnabled() == true, "button is not enabled");
    }
GUI_TEST_CLASS_DEFINITION(test_0003_2) {
    GTFileDialog::openFile(os, dataDir + "samples/FASTA/", "human_T1.fa");
    GTGlobals::sleep();

    QWidget *toggleViewButton = GTWidget::findWidget(os, "toggleViewButton");
    Runnable *chooser = new PopupChooser(os, QStringList() << "toggleDetailsView");
    GTUtilsDialog::waitForDialog(os, chooser);
    GTWidget::click(os, toggleViewButton);
    GTGlobals::sleep();

    GTGlobals::sleep();
    QAbstractButton* translation = GTAction::button(os, "translation_action");

    CHECK_SET_ERR(translation -> isEnabled() == false, "button is not disabled");

    GTGlobals::sleep();
    QAbstractButton* complement = GTAction::button(os, "complement_action");

    CHECK_SET_ERR(complement -> isEnabled() == false, "button is not disabled");

    Runnable *chooser1 = new PopupChooser(os, QStringList() << "toggleDetailsView");
    GTUtilsDialog::waitForDialog(os, chooser1);
    GTWidget::click(os, toggleViewButton);
    GTGlobals::sleep();

    GTGlobals::sleep();
    QAbstractButton* translation1 = GTAction::button(os, "translation_action");

    GTGlobals::sleep();
    CHECK_SET_ERR(translation1 -> isEnabled() == true, "button is not enabled");

    GTGlobals::sleep();
    CHECK_SET_ERR(complement -> isEnabled() == true, "button is not disabled");

    Runnable *chooser2 = new PopupChooser(os, QStringList() << "toggleDetailsView");
    GTUtilsDialog::waitForDialog(os, chooser2);
    GTWidget::click(os, toggleViewButton);
    GTGlobals::sleep();

    GTGlobals::sleep();
    CHECK_SET_ERR(translation -> isEnabled() == false, "button is not disabled");

    GTGlobals::sleep();
    QAbstractButton* complement1 = GTAction::button(os, "complement_action");

    GTGlobals::sleep();
    CHECK_SET_ERR(complement1 -> isEnabled() == false, "button is not disabled");


    }
GUI_TEST_CLASS_DEFINITION(test_0004) {
//    UGENE crashes on subsequence export (0002423)

//    1. Open sequence

//    2. Select some region

//    3. Call context menu "Export -> Export selected sequence region"

//    4. Press Export button in dialog.
//    Expected state: UGENE not crashed

    GTFileDialog::openFile(os, testDir + "_common_data/fasta/", "fa1.fa");
    GTGlobals::sleep(1000);

    GTUtilsSequenceView::selectSequenceRegion(os, 1, 3);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ADV_MENU_EXPORT" << "action_export_selected_sequence_region"));
    GTUtilsDialog::waitForDialog(os, new ExportSelectedRegionFiller(os, testDir + "_common_data/scenarios/sandbox/", "exp.fasta"));
    GTMouseDriver::click(os, Qt::RightButton);
}

GUI_TEST_CLASS_DEFINITION(test_0004_1) { //CHANGES: keyboard used instead mouse

    GTFileDialog::openFile(os, testDir + "_common_data/fasta/", "fa1.fa");
    GTGlobals::sleep(1000);

    GTUtilsSequenceView::selectSequenceRegion(os, 1, 3);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ADV_MENU_EXPORT" << "action_export_selected_sequence_region"));
    GTUtilsDialog::waitForDialog(os, new ExportSelectedRegionFiller(os, testDir + "_common_data/scenarios/sandbox/", "exp.fasta"));
    GTMouseDriver::click(os, Qt::RightButton);
}

GUI_TEST_CLASS_DEFINITION(test_0005) {
//    ADVSeqWidget auto annotations (0002588)

//    1. Open file with amino alphabet (_common_data/fasta/multy_fa.fa)
//    Expected state: Auto-annotations disabled

//    3. Open file with (samples/FASTA/human_T1.fa)

//    4. Activate AA
//    Expected state: UGENE not Crashes

    class AllActionsPopupChooser : public PopupChooser {
    public:
        AllActionsPopupChooser(U2OpStatus &_os) : PopupChooser(_os, QStringList()) {}
        void run() {
            GTGlobals::sleep(100);
            QMenu* activePopupMenu = qobject_cast<QMenu*>(QApplication::activePopupWidget());

            int i = 0;
            QList<QAction*> act = activePopupMenu->actions();
            foreach (QAction* a, act) {
                QString s = a->objectName();
                if (i == 1) {
                    GTMenu::clickMenuItem(os, activePopupMenu, s, GTGlobals::UseMouse);
                }
                GTGlobals::sleep(100);
                i++;
            }
        }
    };

    GTUtilsDialog::waitForDialog(os, new SequenceReadingModeSelectorDialogFiller(os));
    GTUtilsProject::openFiles(os, testDir + "_common_data/fasta/multy_fa.fa");
    GTUtilsDocument::checkDocument(os, "multy_fa.fa");

    QWidget* toggleAutoAnnotationsButton = GTWidget::findWidget(os, "toggleAutoAnnotationsButton");
    CHECK_SET_ERR(toggleAutoAnnotationsButton != NULL, "toggleAutoAnnotationsButton is NULL");
    CHECK_SET_ERR(toggleAutoAnnotationsButton->isEnabled() == false, "toggleAutoAnnotationsButton is enabled, expected disabled");


    GTUtilsProject::openFiles(os, dataDir + "samples/FASTA/human_T1.fa");
    GTUtilsDocument::checkDocument(os, "human_T1.fa");

    toggleAutoAnnotationsButton = GTWidget::findWidget(os, "toggleAutoAnnotationsButton");
    CHECK_SET_ERR(toggleAutoAnnotationsButton != NULL, "toggleAutoAnnotationsButton is NULL");
    CHECK_SET_ERR(toggleAutoAnnotationsButton->isEnabled() == true, "toggleAutoAnnotationsButton is disabled, expected enabled");

    GTUtilsDialog::waitForDialog(os, new AllActionsPopupChooser(os));
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep(1000);
}
GUI_TEST_CLASS_DEFINITION(test_0006) {

//1. Enable Auto-annotations
//     GTGlobals::sleep();
//     GTGlobals::sleep();
    GTFileDialog::openFile(os, dataDir + "samples/FASTA", "human_T1.fa");

    QWidget* toggleAutoAnnotationsButton = GTWidget::findWidget(os, "toggleAutoAnnotationsButton");
//  !!! dirty fastfix of test, very temporary
    QToolBar* tb = qobject_cast<QToolBar*>(toggleAutoAnnotationsButton->parent());
    QToolButton* extensionButton = tb->findChild<QToolButton*>("qt_toolbar_ext_button");
//

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "Restriction Sites"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ORFs"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    //2. Open any PBD file from samples
    //Expected state: there is no auto-annotations for opened sequences

    GTFileDialog::openFile(os, dataDir + "samples/PDB", "1CF7.PDB");

    GTGlobals::sleep();
    QTreeWidgetItem* enz = GTUtilsAnnotationsTreeView::findItem(os, "enzymes", GTGlobals::FindOptions(false));
    QTreeWidgetItem* orf = GTUtilsAnnotationsTreeView::findItem(os, "orfs", GTGlobals::FindOptions(false));
    CHECK_SET_ERR(enz == NULL, "enzymes unexpectedly present");
    CHECK_SET_ERR(orf == NULL, "orfs unexpectedly present");
    GTGlobals::sleep();

    }

GUI_TEST_CLASS_DEFINITION(test_0006_1) {
    //1. Enable Auto-annotations
    GTGlobals::sleep();
    GTGlobals::sleep();
    GTFileDialog::openFile(os, dataDir + "samples/FASTA", "human_T1.fa");

    QWidget* toggleAutoAnnotationsButton = GTWidget::findWidget(os, "toggleAutoAnnotationsButton");
//  !!! dirty fastfix of test, very temporary
    QToolBar* tb = qobject_cast<QToolBar*>(toggleAutoAnnotationsButton->parent());
    QToolButton* extensionButton = tb->findChild<QToolButton*>("qt_toolbar_ext_button");
//

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "Restriction Sites"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ORFs"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    //1. Disable Auto-annotations
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "Restriction Sites"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ORFs"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    //3. Enable Auto-annotations
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "Restriction Sites"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ORFs"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    //2. Open any PBD file from samples
    //Expected state: there is no auto-annotations for opened sequences
    GTFileDialog::openFile(os, dataDir + "samples/PDB", "1CF7.PDB");
    GTGlobals::sleep();

    //Expected state: there is no auto-annotations for opened sequences
    GTGlobals::sleep();
    QTreeWidgetItem* enz = GTUtilsAnnotationsTreeView::findItem(os, "enzymes", GTGlobals::FindOptions(false));
    QTreeWidgetItem* orf = GTUtilsAnnotationsTreeView::findItem(os, "orfs", GTGlobals::FindOptions(false));
    CHECK_SET_ERR(enz == NULL, "enzymes unexpectedly present");
    CHECK_SET_ERR(orf == NULL, "orfs unexpectedly present");
    GTGlobals::sleep();

    }

GUI_TEST_CLASS_DEFINITION(test_0006_2) {
    //2. Open any PBD file from samples
    GTGlobals::sleep();
    GTGlobals::sleep();
    GTFileDialog::openFile(os, dataDir + "samples/PDB", "1CF7.PDB");

    //1. Enable Auto-annotations
    QWidget* toggleAutoAnnotationsButton = GTWidget::findWidget(os, "toggleAutoAnnotationsButton");
//  !!! dirty fastfix of test, very temporary
    QToolBar* tb = qobject_cast<QToolBar*>(toggleAutoAnnotationsButton->parent());
    QToolButton* extensionButton = tb->findChild<QToolButton*>("qt_toolbar_ext_button");
//

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "Restriction Sites"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ORFs"));
    if (extensionButton->isVisible()) {
        GTWidget::click(os, extensionButton);
        GTGlobals::sleep(1000);
    }
    GTWidget::click(os, toggleAutoAnnotationsButton);
    GTGlobals::sleep();

    //Expected state: there is no auto-annotations for opened sequences
    GTGlobals::sleep();
    QTreeWidgetItem* enz = GTUtilsAnnotationsTreeView::findItem(os, "enzymes", GTGlobals::FindOptions(false));
    QTreeWidgetItem* orf = GTUtilsAnnotationsTreeView::findItem(os, "orfs", GTGlobals::FindOptions(false));
    CHECK_SET_ERR(enz == NULL, "enzymes unexpectedly present");
    CHECK_SET_ERR(orf == NULL, "orfs unexpectedly present");
    GTGlobals::sleep();

    }

GUI_TEST_CLASS_DEFINITION(test_0018) {
//    1) Click "Open file" button.

//    2) Choose two sequence files: "_common_data/fasta/DNA.fa" and "_common_data/fasta/DNA_1_seq.fa". And click "Open" button.
//    Expected state: the dialog appears.

//    3) Choose "Merge sequence mode" and click "OK" button.
//    Expected state: one sequence view with a merged sequence is opened. Its name is "merged_document.gb"; its length is 2249.

    QList<QUrl> files;
    files << testDir + "_common_data/fasta/DNA.fa";
    files << testDir + "_common_data/fasta/DNA_1_seq.fa";
    GTSequenceReadingModeDialog::mode = GTSequenceReadingModeDialog::Merge;
    GTUtilsProject::openFiles(os, files);

    int length = GTUtilsSequenceView::getLengthOfSequence(os);
    CHECK_SET_ERR(2249 == length, QString("Sequence length mismatch. Expected: %1. Actual: %2").arg(2249).arg(length));

    QString mergedFileName = testDir + "_common_data/fasta/merged_document.gb";
    QFile::remove(mergedFileName);
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0021) {
//     1. Open '_common_data/primer3/linear_circular_results.fa'
//     2. Launch Primer3 with default settings
//     Expected state: even the sequence is linear, Primer3 finds primers on junction

    GTFileDialog::openFile(os, testDir + "/_common_data/primer3", "linear_circular_results.fa");

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ADV_MENU_ANALYSE" << "primer3_action"));
    GTUtilsDialog::waitForDialog(os, new Primer3DialogFiller(os));

    GTMouseDriver::click(os);
    GTMouseDriver::click(os, Qt::RightButton);

    GTGlobals::sleep();
    QList<U2Region> pair2 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 2  (0, 2)");
    CHECK_SET_ERR( pair2.contains(U2Region(3, 21)), "No 4..24 region");
    CHECK_SET_ERR( pair2.contains(U2Region(153, 12)), "No 154..165 region");
    CHECK_SET_ERR( pair2.contains(U2Region(0, 8)), "No 1..8 region");

    QList<U2Region> pair5 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 5  (0, 2)");
    CHECK_SET_ERR( pair5.contains(U2Region(6, 21)), "No 7..27 region");
    CHECK_SET_ERR( pair5.contains(U2Region(155, 10)), "No 156..165 region");
    CHECK_SET_ERR( pair5.contains(U2Region(0, 10)), "No 1..10 region");
}

GUI_TEST_CLASS_DEFINITION(test_0022) {
//     1. Open '_common_data/primer3/circular_primers.gb
//     2. Launch Primer3 with default settings
//     Expected state: the sequence is circular - a few primers cover junction point

    GTFileDialog::openFile(os, testDir + "/_common_data/primer3", "circular_primers.gb");

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ADV_MENU_ANALYSE" << "primer3_action"));
    GTUtilsDialog::waitForDialog(os, new Primer3DialogFiller(os));

    GTMouseDriver::click(os);
    GTMouseDriver::click(os, Qt::RightButton);

    GTGlobals::sleep();
    QList<U2Region> pair1 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 1  (0, 2)");
    CHECK_SET_ERR( pair1.contains(U2Region(139, 20)), "No 140..159 region");
    CHECK_SET_ERR( pair1.contains(U2Region(331, 20)), "No 332..351 region");

    QList<U2Region> pair5 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 5  (0, 2)");
    CHECK_SET_ERR( pair5.contains(U2Region(123, 20)), "No 124..143 region");
    CHECK_SET_ERR( pair5.contains(U2Region(350, 1)), "No 351..351 region");
    CHECK_SET_ERR( pair5.contains(U2Region(0, 19)), "No 1..19 region");
}

GUI_TEST_CLASS_DEFINITION(test_0023) {
//     1. Open '_common_data/primer3/DNA.gb'
//     2. Launch Primer3 with default settings
//     Expected state: results cover junction point
//     3. Remove circular mark
//     4. Launch Primer3 with different annotation name
//     Expected state: results are linear

    GTFileDialog::openFile(os, testDir + "/_common_data/primer3", "DNA.gb");

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ADV_MENU_ANALYSE" << "primer3_action"));
    GTUtilsDialog::waitForDialog(os, new Primer3DialogFiller(os));

    GTMouseDriver::click(os);
    GTMouseDriver::click(os, Qt::RightButton);

    GTGlobals::sleep();
    QList<U2Region> pair1 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 1  (0, 2)");
    CHECK_SET_ERR( pair1.contains(U2Region(160, 20)), "No 161..180 region");
    CHECK_SET_ERR( pair1.contains(U2Region(684, 20)), "No 685..704 region");

    QList<U2Region> pair4 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 4  (0, 2)");
    CHECK_SET_ERR( pair4.contains(U2Region(66, 20)), "No 67..86 region");
    CHECK_SET_ERR( pair4.contains(U2Region(606, 20)), "No 607..626 region");

    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "Primers_DNA"));
    GTUtilsDialog::waitForDialog(os, new PopupChooserbyText(os, QStringList() << "Mark as circular"));
    GTMouseDriver::click(os, Qt::RightButton);

    GTWidget::click(os, GTWidget::findWidget(os, "render_area_Primers_DNA"));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ADV_MENU_ANALYSE" << "primer3_action"));
    Primer3DialogFiller::Primer3Settings settings;
    settings.resultsCount = 5;
    settings.primersName = "linear";
    GTUtilsDialog::waitForDialog(os, new Primer3DialogFiller(os, settings));

    GTMouseDriver::click(os);
    GTMouseDriver::click(os, Qt::RightButton);

    GTGlobals::sleep(5000);
    pair1 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 1  (0, 2)", "linear  (5, 0)");
    CHECK_SET_ERR( pair1.contains(U2Region(423, 20)), "No 424..443 region");
    CHECK_SET_ERR( pair1.contains(U2Region(582, 20)), "No 583..602 region");

    QList<U2Region> pair5 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 5  (0, 2)", "linear  (5, 0)");
    CHECK_SET_ERR( pair5.contains(U2Region(422, 20)), "No 423..442 region");
    CHECK_SET_ERR( pair5.contains(U2Region(607, 20)), "No 608..627 region");

    GTUtilsDialog::waitForDialog(os, new MessageBoxNoToAllOrNo(os));
    GTUtilsDocument::removeDocument(os, "DNA.gb");
//    GTUtilsDialog::waitForDialog(os, new SaveProjectDialogFiller(os, QDialogButtonBox::No));
}

GUI_TEST_CLASS_DEFINITION(test_0024) {
//    1. Open 'human_T1.fa'
//    2. Open CV
//    3. Select big region covering junction point
//    4. Launch Primer3 search (set results count to 50)
//    Expected state: primers are located on both selected regions(start and end).

    GTFileDialog::openFile(os, dataDir + "/samples/FASTA", "human_T1.fa");
    ADVSingleSequenceWidget* wgt = GTUtilsSequenceView::getSeqWidgetByNumber(os);
    CHECK_SET_ERR(wgt != NULL, "ADVSequenceWidget is NULL");
    GTUtilsCv::cvBtn::click(os, wgt);

    GTUtilsDialog::waitForDialog(os, new selectSequenceRegionDialogFiller(os, "150000..199950,1..50000"));
    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ADV_MENU_ANALYSE" << "primer3_action"));
    Primer3DialogFiller::Primer3Settings settings;
    settings.resultsCount = 50;
    GTUtilsDialog::waitForDialog(os, new Primer3DialogFiller(os, settings));
    GTWidget::click(os, wgt, Qt::RightButton);

    GTGlobals::sleep(30000);

    QList<U2Region> pair32 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 32  (0, 2)");
    CHECK_SET_ERR( pair32.contains(U2Region(36311, 20)), "No 36312..36331 region");
    CHECK_SET_ERR( pair32.contains(U2Region(36552, 20)), "No 36553..36572 region");

    QList<U2Region> pair50 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 50  (0, 2)");
    CHECK_SET_ERR( pair50.contains(U2Region(2350, 20)), "No 2351..2370 region");
    CHECK_SET_ERR( pair50.contains(U2Region(2575, 20)), "No 2576..2595 region");

    QList<U2Region> pair14 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 14  (0, 2)");
    CHECK_SET_ERR( pair14.contains(U2Region(194911, 20)), "No 194912..194931 region");
    CHECK_SET_ERR( pair14.contains(U2Region(195159, 20)), "No 195160..195179 region");

    QList<U2Region> pair4 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 4  (0, 2)");
    CHECK_SET_ERR( pair4.contains(U2Region(163701, 20)), "No 163702..163721 region");
    CHECK_SET_ERR( pair4.contains(U2Region(163856, 20)), "No 163857..163876 region");
}

GUI_TEST_CLASS_DEFINITION(test_0025) {
//    1. Open '_common_data/primer3/DNA.gb'
//    2. Select region that cover junction point
//    3. Launch Primer3 search with default settings
//    Expected state: primers(left and right) are located on either side of junction point

    GTFileDialog::openFile(os, testDir + "/_common_data/primer3", "DNA.gb");
    ADVSingleSequenceWidget* wgt = GTUtilsSequenceView::getSeqWidgetByNumber(os);
    CHECK_SET_ERR(wgt != NULL, "ADVSequenceWidget is NULL");

    GTUtilsDialog::waitForDialog(os, new selectSequenceRegionDialogFiller(os, "560..743,1..180"));
    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ADV_MENU_ANALYSE" << "primer3_action"));
    GTUtilsDialog::waitForDialog(os, new Primer3DialogFiller(os));
    GTWidget::click(os, wgt, Qt::RightButton);

    GTGlobals::sleep();

    QList<U2Region> pair1 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 1  (0, 2)");
    CHECK_SET_ERR( pair1.contains(U2Region(160, 20)), "No 161..180 region");
    CHECK_SET_ERR( pair1.contains(U2Region(684, 20)), "No 685..704 region");

    QList<U2Region> pair4 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 4  (0, 2)");
    CHECK_SET_ERR( pair4.contains(U2Region(66, 20)), "No 67..86 region");
    CHECK_SET_ERR( pair4.contains(U2Region(606, 20)), "No 607..626 region");
}

GUI_TEST_CLASS_DEFINITION(test_0026) {
//    1. Open 'common_data/primer3/DNA.gb'
//    2. Open Primer3 dialog
//    3. Set region to circular: 560..(743,1)..180
//    4. Accept the dialog
//    Expected state: no warning apeared, primers are located on selected region
    GTFileDialog::openFile(os, testDir + "/_common_data/primer3", "DNA.gb");

    ADVSingleSequenceWidget* wgt = GTUtilsSequenceView::getSeqWidgetByNumber(os);
    CHECK_SET_ERR(wgt != NULL, "ADVSequenceWidget is NULL");

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "ADV_MENU_ANALYSE" << "primer3_action"));
    Primer3DialogFiller::Primer3Settings settings;
    settings.start = 560;
    settings.end = 180;
    GTUtilsDialog::waitForDialog(os, new Primer3DialogFiller(os, settings));
    GTWidget::click(os, wgt, Qt::RightButton);

    GTGlobals::sleep();

    QList<U2Region> pair1 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 1  (0, 2)");
    CHECK_SET_ERR( pair1.contains(U2Region(160, 20)), "No 161..180 region");
    CHECK_SET_ERR( pair1.contains(U2Region(684, 20)), "No 685..704 region");

    QList<U2Region> pair4 = GTUtilsAnnotationsTreeView::getAnnotatedRegionsOfGroup(os, "pair 4  (0, 2)");
    CHECK_SET_ERR( pair4.contains(U2Region(66, 20)), "No 67..86 region");
    CHECK_SET_ERR( pair4.contains(U2Region(606, 20)), "No 607..626 region");
}

GUI_TEST_CLASS_DEFINITION(test_0027) {
//    Default export
//    1. Open sars.gb
//    2. Export sequence as image

    GTFileDialog::openFile(os, dataDir + "/samples/Genbank", "sars.gb");

    GTUtilsDialog::waitForDialog(os, new ExportSequenceImage(os, sandBoxDir + "seq_image_0027"));
    GTWidget::click(os, GTAction::button(os, "export_image"));
}

GUI_TEST_CLASS_DEFINITION(test_0028) {
//    Check region selector appearance
//    Region selector is hidden if CurrentView export is selected

    GTFileDialog::openFile(os, dataDir + "/samples/Genbank", "sars.gb");

    class RegionChecker : public Filler {
    public:
        RegionChecker(U2OpStatus& os)
            : Filler(os, "ImageExportForm") {}
        virtual void run() {
            QWidget* dialog = QApplication::activeModalWidget();
            CHECK_SET_ERR(dialog, "activeModalWidget is NULL");

            QRadioButton* radioButton = dialog->findChild<QRadioButton*>("currentViewButton");
            GTRadioButton::click(os, radioButton);

            QWidget* rangeSelector = dialog->findChild<QWidget*>("range_selector");
            CHECK_SET_ERR(rangeSelector != NULL, "range_selector not found");
            CHECK_SET_ERR(!rangeSelector->isVisible(), "range_selector is visible");

            radioButton = dialog->findChild<QRadioButton*>("zoomButton");
            GTRadioButton::click(os, radioButton);
            CHECK_SET_ERR(rangeSelector->isVisible(), "range_selector is hidden");

            radioButton = dialog->findChild<QRadioButton*>("detailsButton");
            GTRadioButton::click(os, radioButton);
            CHECK_SET_ERR(rangeSelector->isVisible(), "range_selector is hidden");

            radioButton = dialog->findChild<QRadioButton*>("currentViewButton");
            GTRadioButton::click(os, radioButton);
            CHECK_SET_ERR(!rangeSelector->isVisible(), "range_selector is hidden");

            QDialogButtonBox* box = qobject_cast<QDialogButtonBox*>(GTWidget::findWidget(os, "buttonBox", dialog));
            CHECK_SET_ERR(box != NULL, "buttonBox is NULL");
            QPushButton* button = box->button(QDialogButtonBox::Cancel);
            CHECK_SET_ERR(button !=NULL, "ok button is NULL");
            GTWidget::click(os, button);
        }
    };

    GTUtilsDialog::waitForDialog(os, new RegionChecker(os));
    GTWidget::click(os, GTAction::button(os, "export_image"));
}

GUI_TEST_CLASS_DEFINITION(test_0029) {
//    Check boundaries of export in raster formats
//    1. Open sars.gb
//    2. Zoom in a few times
//    3. Open Export Image dialog
//    4. Select Details view export
//    Expected state: warning message appeared, export is blocked
//    5. Select a fewer region
//    Expected state: warning is hidden, export is available
//    6. Select Zoomed Image export
//    Expected state: warning message appeared, export is blocked
//    7. Select a fewer region
//    Expected state: warning is hidden, export is available


    GTFileDialog::openFile(os, dataDir + "/samples/Genbank", "sars.gb");

    QAction* zoom = GTAction::findActionByText(os, "Zoom In");
    CHECK_SET_ERR(zoom != NULL, "Cannot find Zoom In action");
    for (int i = 0; i < 8; i++) {
        GTWidget::click(os, GTAction::button(os, zoom));
    }

    class LimitsChecker : public Filler {
    public:
        LimitsChecker(U2OpStatus& os)
            : Filler(os, "ImageExportForm") {}
        virtual void run() {
            QWidget* dialog = QApplication::activeModalWidget();
            CHECK_SET_ERR(dialog, "activeModalWidget is NULL");

            QWidget* rangeSelector = dialog->findChild<QWidget*>("range_selector");
            CHECK_SET_ERR(rangeSelector != NULL, "range_selector not found");
            CHECK_SET_ERR(!rangeSelector->isVisible(), "range_selector is visible");

            QDialogButtonBox* box = qobject_cast<QDialogButtonBox*>(GTWidget::findWidget(os, "buttonBox", dialog));
            CHECK_SET_ERR(box != NULL, "buttonBox is NULL");
            QPushButton* okbutton = box->button(QDialogButtonBox::Ok);
            CHECK_SET_ERR(okbutton !=NULL, "ok button is NULL");
            CHECK_SET_ERR(okbutton->isEnabled(), "Export button is unexpectedly disabled");

            QRadioButton* radioButton = dialog->findChild<QRadioButton*>("zoomButton");
            GTRadioButton::click(os, radioButton);
            CHECK_SET_ERR(!okbutton->isEnabled(), "Export button is unexpectedly enabled");

            QLineEdit* end = dialog->findChild<QLineEdit*>("end_edit_line");
            GTLineEdit::setText(os, end, "100");
            CHECK_SET_ERR(okbutton->isEnabled(), "Export button is unexpectedly disabled");

            radioButton = dialog->findChild<QRadioButton*>("detailsButton");
            GTRadioButton::click(os, radioButton);
            GTLineEdit::setText(os, end, "10000");
            CHECK_SET_ERR(!okbutton->isEnabled(), "Export button is unexpectedly enabled");

            GTLineEdit::setText(os, end, "100");
            CHECK_SET_ERR(okbutton->isEnabled(), "Export button is unexpectedly disabled");

            QPushButton* button = box->button(QDialogButtonBox::Cancel);
            CHECK_SET_ERR(button !=NULL, "cancel button is NULL");
            GTWidget::click(os, button);
        }
    };

    GTUtilsDialog::waitForDialog(os, new LimitsChecker(os));
    GTWidget::click(os, GTAction::button(os, "export_image"));
}

GUI_TEST_CLASS_DEFINITION(test_0030) {
//    Check boundaries of export fro SVG
//    1. Open human_T1.fa
//    2. Find restriction sites YkrI
//    3. Open Export Image dialog
//    4. Select SVG format
//    Expected state: export is available
//    5. Select Details view export
//    Expected state: warning message appeared, export is blocked
//    6. Select a fewer region
//    Expected state: warning is hidden, export is available
//    6. Select Zoomed Image export and the whole sequence to export
//    Expected state: warning message appeared, export is blocked
//    5. Select a fewer region and export that
//    Expected state: warning is hidden, export is available


    GTFileDialog::openFile(os, dataDir + "/samples/FASTA", "human_T1.fa");

    GTUtilsDialog::waitForDialog(os, new FindEnzymesDialogFiller(os, QStringList() << "YkrI"));
    GTUtilsDialog::waitForDialog(os, new PopupChooserbyText(os, QStringList() << "Analyze" << "Find restriction sites"));
    GTMouseDriver::click(os, Qt::RightButton);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTGlobals::sleep();

    class SvgLimitsChecker : public Filler {
    public:
        SvgLimitsChecker(U2OpStatus& os)
            : Filler(os, "ImageExportForm") {}
        virtual void run() {
            QWidget* dialog = QApplication::activeModalWidget();
            CHECK_SET_ERR(dialog, "activeModalWidget is NULL");

            // set SVG format
            QComboBox* formatsBox = dialog->findChild<QComboBox*>("formatsBox");
            CHECK_SET_ERR(formatsBox != NULL, "formatBox is NULL");
            GTComboBox::setIndexWithText(os, formatsBox, "svg");

            // export is available
            QDialogButtonBox* box = qobject_cast<QDialogButtonBox*>(GTWidget::findWidget(os, "buttonBox", dialog));
            CHECK_SET_ERR(box != NULL, "buttonBox is NULL");
            QPushButton* okbutton = box->button(QDialogButtonBox::Ok);
            CHECK_SET_ERR(okbutton != NULL, "ok button is NULL");
            CHECK_SET_ERR(okbutton->isEnabled(), "Export button is unexpectedly disabled");

            // select Details -- export is disabled
            QRadioButton* radioButton = dialog->findChild<QRadioButton*>("detailsButton");
            GTRadioButton::click(os, radioButton);
            CHECK_SET_ERR(!okbutton->isEnabled(), "Export button is unexpectedly enabled");

            QLineEdit* end = dialog->findChild<QLineEdit*>("end_edit_line");
            GTLineEdit::setText(os, end, "2300");
            CHECK_SET_ERR(okbutton->isEnabled(), "Export button is unexpectedly disabled");

            // set Zoom view export
            radioButton = dialog->findChild<QRadioButton*>("zoomButton");
            GTRadioButton::click(os, radioButton);
            CHECK_SET_ERR(okbutton->isEnabled(), "Export button is unexpectedly disabled");
            GTLineEdit::setText(os, end, "199000");
            CHECK_SET_ERR(!okbutton->isEnabled(), "Export button is unexpectedly enabled");

            // select a fewer region -- export is enabled
            GTLineEdit::setText(os, end, "10000");
            CHECK_SET_ERR(okbutton->isEnabled(), "Export button is unexpectedly disabled");

            QLineEdit* fileEdit = dialog->findChild<QLineEdit*>("fileNameEdit");
            GTLineEdit::setText(os, fileEdit, sandBoxDir + "/seq_view_test_0030.svg");

            GTWidget::click(os, okbutton);
        }
    };

    GTUtilsDialog::waitForDialog(os, new SvgLimitsChecker(os));
    GTWidget::click(os, GTAction::button(os, "export_image"));
    GTUtilsTaskTreeView::waitTaskFinished(os);

    qint64 fileSize = GTFile::getSize(os, sandBoxDir + "/seq_view_test_0030.svg");
    CHECK_SET_ERR(fileSize > 15 * 1024 * 1024, QString("SVG file is too small: %1").arg(fileSize));
}

GUI_TEST_CLASS_DEFINITION(test_0031){
//    Open human_T1.fa
    GTFileDialog::openFile(os, dataDir + "samples/FASTA/", "human_T1.fa");
//    Select some redion
    GTUtilsSequenceView::selectSequenceRegion(os, 10, 20);
//    Use context menu {Copy->Copy reverse complement sequence}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ADV_MENU_COPY
                                                      << "Copy reverse complement sequence"));

    GTMenu::showContextMenu(os, GTUtilsSequenceView::getSeqWidgetByNumber(os));

    QString clipboardtext = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardtext == "AACTTTGGTGA", "Unexpected reverse complement: " + clipboardtext)
}

GUI_TEST_CLASS_DEFINITION(test_0031_1){
//    Open human_T1.fa
    GTFileDialog::openFile(os, dataDir + "samples/FASTA/", "human_T1.fa");
//    Select some redion
    GTUtilsSequenceView::selectSequenceRegion(os, 10, 20);
//    Use context menu {Copy->Copy reverse complement sequence}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ADV_MENU_COPY
                                                      << "Copy reverse complement sequence"));

    GTMenu::showContextMenu(os, GTUtilsSequenceView::getSeqWidgetByNumber(os));

    QString clipboardtext = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardtext == "AACTTTGGTGA", "Unexpected reverse complement: " + clipboardtext)
}

GUI_TEST_CLASS_DEFINITION(test_0031_2){
//    Open murine.gb
    GTFileDialog::openFile(os, dataDir + "samples/Genbank/", "murine.gb");
//    Select annotation
    GTUtilsSequenceView::clickAnnotation(os, "misc_feature", 2);
//    Use context menu {Copy->Copy reverse complement sequence}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ADV_MENU_COPY
                                                      << "action_copy_annotation_sequence"));

    GTMenu::showContextMenu(os, GTUtilsSequenceView::getSeqWidgetByNumber(os));

    QString clipboardtext = GTClipboard::text(os);
    QString expected = "AATGAAAGACCCCACCCGTAGGTGGCAAGCTAGCTTAAGTAACGCCACTTTGCAAGGCATGGAAAAATACATAACTGAGAATAGAAAAGTTCAGATCAAGGTC"
            "AGGAACAAAGAAACAGCTGAATACCAAACAGGATATCTGTGGTAAGCGGTTCCTGCCCCGGCTCAGGGCCAAGAACAGATGAGACAGCTGAGTGATGGGCCAAACAGGATATCT"
            "GTGGTAAGCAGTTCCTGCCCCGGCTCGGGGCCAAGAACAGATGGTCCCCAGATGCGGTCCAGCCCTCAGCAGTTTCTAGTGAATCATCAGATGTTTCCAGGGTGCCCCAAGGA"
            "CCTGAAAATGACCCTGTACCTTATTTGAACTAACCAATCAGTTCGCTTCTCGCTTCTGTTCGCGCGCTTCCGCTCTCCGAGCTCAATAAAAGAGCCCACAACCCCTCACTCGGC"
            "GCGCCAGTCTTCCGATAGACTGCGTCGCCCGGGTACCCGTATTCCCAATAAAGCCTCTTGCTGTTTGCATCCGAATCGTGGTCTCGCTGTTCCTTGGGAGGGTCTCCTCTGAGTGATTGACTACCCACGACGGGGGTCTTTCATT";
    CHECK_SET_ERR(clipboardtext == expected, "Unexpected reverse complement: " + clipboardtext);

//    Check joined annotations
    GTUtilsSequenceView::clickAnnotation(os, "CDS", 2970);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ADV_MENU_COPY
                                                      << "action_copy_annotation_sequence"));

    GTMenu::showContextMenu(os, GTUtilsSequenceView::getSeqWidgetByNumber(os));

    clipboardtext = GTClipboard::text(os);
    expected = "ATGGTAGCAGCCATTGCCGTACTGACAAAGGATGCAGGCAAGCTAACCATGGGACAGCCACTAGTCATTCTGGCCCCCCATGCAGTAGAGGCACTAGTCAAACAACCCCC"
            "CGACCGCTGGCTTTCCAACGCCCGGATGACTCACTATCAGGCCTTGCTTTTGGACACGGACCGGGTCCAGTTCAGACCGGTGGTAGCCCTGAACCCGGCTACGCTGCTCCCAC"
            "TGCCTGAGAAAGGGCTGCAACACAACTGCCTTGATATCCTGGCCGAAGCTCATGGAACCCGACCCGACCTAACGGACCAGCCGCTCCCAGACGCCGACCACACCTGGTACACG"
            "GATGGAAGCAGTCTTTTACAAGAGGGACAGCGTAAGGCGGGAGCTGCGGTGACCACCGAGACCGAGAAGCCTTCCCAACCAAGAAAAAAAACCGCCAAGGTCGTAAAT";
    CHECK_SET_ERR(clipboardtext == expected, "Unexpected reverse complement for joined annotation: " + clipboardtext);

}

GUI_TEST_CLASS_DEFINITION(test_0031_3){
//    Open murine.gb
    GTFileDialog::openFile(os, dataDir + "samples/Genbank/", "murine.gb");
//    Select annotation
    GTUtilsSequenceView::clickAnnotation(os, "misc_feature", 2);
//    Use context menu {Copy->Copy reverse complement sequence}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ADV_MENU_COPY
                                                      << "action_copy_annotation_sequence"));

    GTMenu::showContextMenu(os, GTUtilsSequenceView::getSeqWidgetByNumber(os));

    QString clipboardtext = GTClipboard::text(os);
    QString expected = "AATGAAAGACCCCACCCGTAGGTGGCAAGCTAGCTTAAGTAACGCCACTTTGCAAGGCATGGAAAAATACATAACTGAGAATAGAAAAGTTCAGATCAAGGTC"
            "AGGAACAAAGAAACAGCTGAATACCAAACAGGATATCTGTGGTAAGCGGTTCCTGCCCCGGCTCAGGGCCAAGAACAGATGAGACAGCTGAGTGATGGGCCAAACAGGATATCT"
            "GTGGTAAGCAGTTCCTGCCCCGGCTCGGGGCCAAGAACAGATGGTCCCCAGATGCGGTCCAGCCCTCAGCAGTTTCTAGTGAATCATCAGATGTTTCCAGGGTGCCCCAAGGA"
            "CCTGAAAATGACCCTGTACCTTATTTGAACTAACCAATCAGTTCGCTTCTCGCTTCTGTTCGCGCGCTTCCGCTCTCCGAGCTCAATAAAAGAGCCCACAACCCCTCACTCGGC"
            "GCGCCAGTCTTCCGATAGACTGCGTCGCCCGGGTACCCGTATTCCCAATAAAGCCTCTTGCTGTTTGCATCCGAATCGTGGTCTCGCTGTTCCTTGGGAGGGTCTCCTCTGAGTGATTGACTACCCACGACGGGGGTCTTTCATT";
    CHECK_SET_ERR(clipboardtext == expected, "Unexpected reverse complement: " + clipboardtext);

//    Check joined annotations
    GTUtilsSequenceView::clickAnnotation(os, "CDS", 2970);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ADV_MENU_COPY
                                                      << "action_copy_annotation_sequence"));

    GTMenu::showContextMenu(os, GTUtilsSequenceView::getSeqWidgetByNumber(os));

    clipboardtext = GTClipboard::text(os);
    expected = "ATGGTAGCAGCCATTGCCGTACTGACAAAGGATGCAGGCAAGCTAACCATGGGACAGCCACTAGTCATTCTGGCCCCCCATGCAGTAGAGGCACTAGTCAAACAACCCCC"
            "CGACCGCTGGCTTTCCAACGCCCGGATGACTCACTATCAGGCCTTGCTTTTGGACACGGACCGGGTCCAGTTCAGACCGGTGGTAGCCCTGAACCCGGCTACGCTGCTCCCAC"
            "TGCCTGAGAAAGGGCTGCAACACAACTGCCTTGATATCCTGGCCGAAGCTCATGGAACCCGACCCGACCTAACGGACCAGCCGCTCCCAGACGCCGACCACACCTGGTACACG"
            "GATGGAAGCAGTCTTTTACAAGAGGGACAGCGTAAGGCGGGAGCTGCGGTGACCACCGAGACCGAGAAGCCTTCCCAACCAAGAAAAAAAACCGCCAAGGTCGTAAAT";
    CHECK_SET_ERR(clipboardtext == expected, "Unexpected reverse complement for joined annotation: " + clipboardtext);

}

#define GET_ACTIONS QMenu *activePopupMenu = qobject_cast<QMenu *>(QApplication::activePopupWidget()); \
CHECK_SET_ERR(NULL != activePopupMenu, "Active popup menu is NULL"); \
GTMenu::clickMenuItemByText(os, activePopupMenu, QStringList() << "Translation frames"); \
activePopupMenu = qobject_cast<QMenu *>(QApplication::activePopupWidget()); \
QAction* direct1 = GTMenu::getMenuItem(os, activePopupMenu, "1 direct translation frame", true); \
QAction* direct2 = GTMenu::getMenuItem(os, activePopupMenu, "2 direct translation frame", true); \
QAction* direct3 = GTMenu::getMenuItem(os, activePopupMenu, "3 direct translation frame", true); \
QAction* compl1 = GTMenu::getMenuItem(os, activePopupMenu, "1 complementary translation frame", true); \
QAction* compl2 = GTMenu::getMenuItem(os, activePopupMenu, "2 complementary translation frame", true); \
QAction* compl3 = GTMenu::getMenuItem(os, activePopupMenu, "3 complementary translation frame", true);

GUI_TEST_CLASS_DEFINITION(test_0032){
//    Open human_T1.fa
    GTFileDialog::openFile(os, dataDir + "samples/FASTA/", "human_T1.fa");
//    Click "Amino translations" button on mdi toolbar
    QWidget* aminoToolbarButton = GTWidget::findWidget(os, "AminoToolbarButton");
    GTUtilsDialog::waitForDialog(os, new PopupChooserbyText(os, QStringList()<<"Translation frames"<<"Show direct only"));
    GTWidget::click(os, aminoToolbarButton);
//    Check "Show direct only"
    class DirectPopupChecker : public CustomScenario {
        void run(U2OpStatus &os) {
            GET_ACTIONS

            CHECK_SET_ERR(direct1->isChecked(), "check1: direct1 is not checked");
            CHECK_SET_ERR(direct2->isChecked(), "check1: direct2 is not checked");
            CHECK_SET_ERR(direct3->isChecked(), "check1: direct3 is not checked");
            CHECK_SET_ERR(!compl1->isChecked(), "check1: compl1 is checked");
            CHECK_SET_ERR(!compl2->isChecked(), "check1: compl2 is checked");
            CHECK_SET_ERR(!compl3->isChecked(), "check1: compl3 is checked");


            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["esc"]);
            GTGlobals::sleep(200);
            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["esc"]);
        }
    };
    GTUtilsDialog::waitForDialog(os, new PopupChecker(os, new DirectPopupChecker));
    GTWidget::click(os, aminoToolbarButton);

    //    Check "Show complementary only"
    GTUtilsDialog::waitForDialog(os, new PopupChooserbyText(os, QStringList()<<"Translation frames"<<"Show complementary only"));
    GTWidget::click(os, aminoToolbarButton);

    class ComplPopupChecker : public CustomScenario {
        void run(U2OpStatus &os) {
            GET_ACTIONS

            CHECK_SET_ERR(!direct1->isChecked(), "check2: direct1 is checked");
            CHECK_SET_ERR(!direct2->isChecked(), "check2: direct2 is checked");
            CHECK_SET_ERR(!direct3->isChecked(), "check2: direct3 is checked");
            CHECK_SET_ERR(compl1->isChecked(), "check2: compl1 is not checked");
            CHECK_SET_ERR(compl2->isChecked(), "check2: compl2 is not checked");
            CHECK_SET_ERR(compl3->isChecked(), "check2: compl3 is not checked");


            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["esc"]);
            GTGlobals::sleep(200);
            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["esc"]);
        }
    };
    GTUtilsDialog::waitForDialog(os, new PopupChecker(os, new ComplPopupChecker));
    GTWidget::click(os, aminoToolbarButton);

    //    Check "Show all"
    GTUtilsDialog::waitForDialog(os, new PopupChooserbyText(os, QStringList()<<"Translation frames"<<"Show all"));
    GTWidget::click(os, aminoToolbarButton);

    class AllPopupChecker : public CustomScenario {
        void run(U2OpStatus &os) {
            GET_ACTIONS

            CHECK_SET_ERR(direct1->isChecked(), "check3: direct1 is checked");
            CHECK_SET_ERR(direct2->isChecked(), "check3: direct2 is checked");
            CHECK_SET_ERR(direct3->isChecked(), "check3: direct3 is checked");
            CHECK_SET_ERR(compl1->isChecked(), "check3: compl1 is not checked");
            CHECK_SET_ERR(compl2->isChecked(), "check3: compl2 is not checked");
            CHECK_SET_ERR(compl3->isChecked(), "check3: compl3 is not checked");


            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["esc"]);
            GTGlobals::sleep(200);
            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["esc"]);
        }
    };
    GTUtilsDialog::waitForDialog(os, new PopupChecker(os, new AllPopupChecker));
    GTWidget::click(os, aminoToolbarButton);
}
#undef GET_ACTIONS

GUI_TEST_CLASS_DEFINITION(test_0034){

}

} // namespace GUITest_common_scenarios_sequence_view

} // namespace U2
