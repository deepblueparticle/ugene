/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2014 UniPro <ugene@unipro.ru>
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

#include "GTTestsOptionPanelMSA.h"

#include "api/GTFileDialog.h"
#include "api/GTWidget.h"
#include "api/GTLineEdit.h"
#include "api/GTComboBox.h"
#include "api/GTBaseCompleter.h"
#include "api/GTKeyboardDriver.h"

#include "GTUtilsOptionPanelMSA.h"
#include "GTUtilsMsaEditorSequenceArea.h"
namespace U2{

namespace GUITest_common_scenarios_options_panel_MSA{

GUI_TEST_CLASS_DEFINITION(general_test_0001){
    const QString seqName = "Phaneroptera_falcata";
//    1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
//    2. Open general option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::General);
//    3. Use button to add Phaneroptera_falcata as referene
    GTUtilsOptionPanelMsa::addReference(os, seqName);
//    Expected state:
//    reference sequence line edit is empty
    QLineEdit* sequenceLineEdit = qobject_cast<QLineEdit*>(GTWidget::findWidget(os, "sequenceLineEdit"));
    CHECK_SET_ERR(sequenceLineEdit != NULL, "sequenceLineEdit not found");
    QString text = sequenceLineEdit->text();
    CHECK_SET_ERR(text == seqName, QString("sequenceLineEdit contains %1, expected: %2").arg(text).arg(seqName));
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::isSequenceHightighted(os, seqName), "sequence not highlighted");
//    Expected state: Phaneroptera_falcata highlighted as reference

//    4. Use button to remove reference
    GTUtilsOptionPanelMsa::removeReference(os);
//    Expected state:
//    reference sequence line edit contains "select and add"
//    Phaneroptera_falcata is not highlighted as reference
    text = sequenceLineEdit->text();
    CHECK_SET_ERR(text.isEmpty(), QString("sequenceLineEdit contains %1, no text ecpected").arg(text));
    CHECK_SET_ERR(!GTUtilsMSAEditorSequenceArea::isSequenceHightighted(os, seqName), "sequence not highlighted");
}

GUI_TEST_CLASS_DEFINITION(general_test_0001_1){
    //Difference: pupup completer is used
    const QString seqName = "Phaneroptera_falcata";
//    1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
//    2. Open general option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::General);
//    3. Use button to add Phaneroptera_falcata as reference
    GTUtilsOptionPanelMsa::addReference(os, seqName, GTUtilsOptionPanelMsa::Completer);
//    Expected state:
//    reference sequence line edit contains Phaneroptera_falcata
    QLineEdit* sequenceLineEdit = qobject_cast<QLineEdit*>(GTWidget::findWidget(os, "sequenceLineEdit"));
    CHECK_SET_ERR(sequenceLineEdit != NULL, "sequenceLineEdit not found");
    QString text = sequenceLineEdit->text();
    CHECK_SET_ERR(text == seqName, QString("sequenceLineEdit contains %1, expected: %2").arg(text).arg(seqName));
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::isSequenceHightighted(os, seqName), "sequence not highlighted");
//    Phaneroptera_falcata highlighted as reference

//    4. Use button to remove reference
    GTUtilsOptionPanelMsa::removeReference(os);
//    Expected state:
//    reference sequence line edit contains "select and add"
//    Phaneroptera_falcata is not highlighted as reference
    text = sequenceLineEdit->text();
    CHECK_SET_ERR(text.isEmpty(), QString("sequenceLineEdit contains %1, no text ecpected").arg(text));
    CHECK_SET_ERR(!GTUtilsMSAEditorSequenceArea::isSequenceHightighted(os, seqName), "sequence not highlighted");
}

GUI_TEST_CLASS_DEFINITION(general_test_0002){
    const QString seqName = "Phaneroptera_falcata";
//1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
//2. Open general option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::General);
//3. Type "phan" in reference line edit
    QLineEdit* sequenceLineEdit = qobject_cast<QLineEdit*>(GTWidget::findWidget(os, "sequenceLineEdit"));
    CHECK_SET_ERR(sequenceLineEdit != NULL, "sequenceLineEdit not found");
    GTLineEdit::setText(os, sequenceLineEdit, "phan");
    QStringList names = GTBaseCompleter::getNames(os, GTBaseCompleter::getCompleter(os));
//Expected state: popup helper contains Phaneroptera_falcata.(case insencivity is checked)
    int num = names.count();
    CHECK_SET_ERR(num == 1, QString("wrong number of sequences in completer. Expected 1, found %1").arg(num));

    QString name = names.at(0);
    CHECK_SET_ERR(name == seqName, QString("wrong sequence name. Expected %1, found %2").arg(seqName).arg(name));
}

GUI_TEST_CLASS_DEFINITION(general_test_0003){
//    1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
//    2. Open general option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::General);
//    3. Type some string which is not part some sequence's name
    QLineEdit* sequenceLineEdit = qobject_cast<QLineEdit*>(GTWidget::findWidget(os, "sequenceLineEdit"));
    CHECK_SET_ERR(sequenceLineEdit != NULL, "sequenceLineEdit not found");
    GTLineEdit::setText(os, sequenceLineEdit, "wrong name");
//    Expected state: empty popup helper appeared
    bool empty = GTBaseCompleter::isEmpty(os, GTBaseCompleter::getCompleter(os));
    CHECK_SET_ERR(empty, "completer is not empty");
    GTWidget::click(os, sequenceLineEdit);//needed to close completer
}

GUI_TEST_CLASS_DEFINITION(general_test_0004){
//    1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
//    2. Open general option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::General);
//    3. Rename Isophya_altaica_EF540820 to Phaneroptera_falcata
    GTUtilsMSAEditorSequenceArea::renameSequence(os, "Isophya_altaica_EF540820", "Phaneroptera_falcata");
//    4. Type "phan" in reference line edit
    QLineEdit* sequenceLineEdit = qobject_cast<QLineEdit*>(GTWidget::findWidget(os, "sequenceLineEdit"));
    CHECK_SET_ERR(sequenceLineEdit != NULL, "sequenceLineEdit not found");
    GTLineEdit::setText(os, sequenceLineEdit, "Phan");
    QStringList completerList = GTBaseCompleter::getNames(os, GTBaseCompleter::getCompleter(os));
//    Expected state: two sequence names "Phaneroptera_falcata" appeared in popup helper
    CHECK_SET_ERR(completerList.count() == 2, "wrong number of sequences in completer");
    QString first = completerList.at(0);
    QString second = completerList.at(1);
    CHECK_SET_ERR(first == "Phaneroptera_falcata", QString("first sequence in completer is wrong: %1").arg(first))
    CHECK_SET_ERR(second == "Phaneroptera_falcata", QString("second sequence in completer is wrong: %1").arg(second))
    GTWidget::click(os, sequenceLineEdit);//needed to close completer
}

GUI_TEST_CLASS_DEFINITION(general_test_0005){
//    1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
//    2. Open general option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::General);
//    3. Delete Hetrodes_pupus_EF540832
    GTUtilsMSAEditorSequenceArea::selectSequence(os, "Hetrodes_pupus_EF540832");
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep(300);
//    Expected state: Sequence number is 17
    int height = GTUtilsOptionPanelMsa::getHeight(os);
    CHECK_SET_ERR( height == 17, QString("wrong height. expected 17, found %1").arg(height));
//    4. Select one column. Press delete
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(5, 0), QPoint(5,17));
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep(300);
//    Expected state: Length is 603
    int length = GTUtilsOptionPanelMsa::getLength(os);
    CHECK_SET_ERR( length== 603, QString("wrong length. expected 17, found %1").arg(length));
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0001){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "UGENE" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme,"UGENE");
    QString a = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,0));
    QString t = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,2));
    QString g = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(2,0));
    QString c = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,0));
    QString gap = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,2));
    CHECK_SET_ERR(a == "#fcff92", QString("a has color %1").arg(a));
    CHECK_SET_ERR(t == "#ff99b1", QString("t has color %1").arg(t));
    CHECK_SET_ERR(g == "#4eade1", QString("g has color %1").arg(g));
    CHECK_SET_ERR(c == "#70f970", QString("c has color %1").arg(c));
    CHECK_SET_ERR(gap == "#ffffff", QString("gap has color %1").arg(gap));
//    4. Check colors for all symbols
//    (branches: check Jalview, Percentage Identity, Percentage Identity(gray), UGENE color schemes)
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0001_1){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "No colors" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme,"No colors");
    QString a = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,0));
    QString t = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,2));
    QString g = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(2,0));
    QString c = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,0));
    QString gap = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,2));
    CHECK_SET_ERR(a == "#ffffff", QString("a has color %1").arg(a));
    CHECK_SET_ERR(t == "#ffffff", QString("t has color %1").arg(t));
    CHECK_SET_ERR(g == "#ffffff", QString("g has color %1").arg(g));
    CHECK_SET_ERR(c == "#ffffff", QString("c has color %1").arg(c));
    CHECK_SET_ERR(gap == "#ffffff", QString("gap has color %1").arg(gap));
//    4. Check colors for all symbols
//    (branches: check Jalview, Percentage Identity, Percentage Identity(gray), UGENE color schemes)
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0001_2){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Jalview" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme,"Jalview");
    QString a = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,0));
    QString t = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,2));
    QString g = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(2,0));
    QString c = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,0));
    QString gap = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,2));
    CHECK_SET_ERR(a == "#64f73f", QString("a has color %1").arg(a));
    CHECK_SET_ERR(t == "#3c88ee", QString("t has color %1").arg(t));
    CHECK_SET_ERR(g == "#eb413c", QString("g has color %1").arg(g));
    CHECK_SET_ERR(c == "#ffb340", QString("c has color %1").arg(c));
    CHECK_SET_ERR(gap == "#ffffff", QString("gap has color %1").arg(gap));
//    4. Check colors for all symbols
//    (branches: check Jalview, Percentage Identity, Percentage Identity(gray), UGENE color schemes)
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0001_3){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Percentage Identity" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme,"Percentage Identity");
    QString a = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,0));
    QString t = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,2));
    QString g = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(2,0));
    QString c = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(5,0));
    QString gap = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,2));
    CHECK_SET_ERR(a == "#ccccff", QString("a has color %1").arg(a));
    CHECK_SET_ERR(t == "#ffffff", QString("t has color %1").arg(t));
    CHECK_SET_ERR(g == "#6464ff", QString("g has color %1").arg(g));
    CHECK_SET_ERR(c == "#9999ff", QString("c has color %1").arg(c));
    CHECK_SET_ERR(gap == "#ffffff", QString("gap has color %1").arg(gap));
//    4. Check colors for all symbols
//    (branches: check Jalview, Percentage Identity, Percentage Identity(gray), UGENE color schemes)
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0001_4){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Percentage Identity (gray)" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme,"Percentage Identity (gray)");
    QString a = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,0));
    QString t = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,2));
    QString g = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(2,0));
    QString c = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(5,0));
    QString gap = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,2));
    CHECK_SET_ERR(a == "#cccccc", QString("a has color %1").arg(a));
    CHECK_SET_ERR(t == "#ffffff", QString("t has color %1").arg(t));
    CHECK_SET_ERR(g == "#646464", QString("g has color %1").arg(g));
    CHECK_SET_ERR(c == "#999999", QString("c has color %1").arg(c));
    CHECK_SET_ERR(gap == "#ffffff", QString("gap has color %1").arg(gap));
//    4. Check colors for all symbols
//    (branches: check Jalview, Percentage Identity, Percentage Identity(gray), UGENE color schemes)
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0002){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Create custom color scheme
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme", NewColorSchemeCreator::nucl);
//    3. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    Expected state: color scheme added to "Color" combobox
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "No colors");
    GTComboBox::setIndexWithText(os, colorScheme, "Scheme");
//    4. Select custom scheme
//    Expected state: scheme changed
    QString a = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,0));
    QString t = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,2));
    QString g = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(2,0));
    QString c = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,0));
    QString gap = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,2));
    CHECK_SET_ERR(a == "#fcff92", QString("a has color %1").arg(a));
    CHECK_SET_ERR(t == "#ff99b1", QString("t has color %1").arg(t));
    CHECK_SET_ERR(g == "#4eade1", QString("g has color %1").arg(g));
    CHECK_SET_ERR(c == "#70f970", QString("c has color %1").arg(c));
    CHECK_SET_ERR(gap == "#ffffff", QString("gap has color %1").arg(gap));
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0002_1){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Create 3 color schemes
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme1", NewColorSchemeCreator::nucl);
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme2", NewColorSchemeCreator::nucl);
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme3", NewColorSchemeCreator::nucl);
//    Expected state: color schemes added to "Color" combobox
     GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
     QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
     GTComboBox::setIndexWithText(os, colorScheme, "Scheme1");
     GTComboBox::setIndexWithText(os, colorScheme, "Scheme2");
     GTComboBox::setIndexWithText(os, colorScheme, "Scheme3");
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0003){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Create custom color scheme
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme", NewColorSchemeCreator::nucl);
//    3. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    4. Select custom scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "Scheme");
//    5. Delete scheme which is selected
    GTUtilsMSAEditorSequenceArea::deleteColorScheme(os, "Scheme");
    GTGlobals::sleep(500);

//    UGENE not crashess
//    no color sheme is selected
    QString s = colorScheme->currentText();
    CHECK_SET_ERR(colorScheme->currentText() == "No colors", "wrong color scheme selected");
    QString a = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,0));
    QString t = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(0,2));
    QString g = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(2,0));
    QString c = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,0));
    QString gap = GTUtilsMSAEditorSequenceArea::getColor(os, QPoint(4,2));
    CHECK_SET_ERR(a == "#ffffff", QString("a has color %1").arg(a));
    CHECK_SET_ERR(t == "#ffffff", QString("t has color %1").arg(t));
    CHECK_SET_ERR(g == "#ffffff", QString("g has color %1").arg(g));
    CHECK_SET_ERR(c == "#ffffff", QString("c has color %1").arg(c));
    CHECK_SET_ERR(gap == "#ffffff", QString("gap has color %1").arg(gap));
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "No color" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme,"No colors");
//    4. Check colors for all symbols
    for(int i = 0; i<29; i++){
        GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(i,0), "#ffffff");
    }
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004_1){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Buried index" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme,"Buried index");
//    4. Check colors for all symbols
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#00a35c");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#00eb14");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#0000ff");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#00eb14");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#00f10e");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#008778");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#009d62");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#00d52a");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#0054ab");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#ffffff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#00ff00");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#007b84");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#009768");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#00eb14");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffffff");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#00e01f");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#00f10e");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#00fc03");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#00d52a");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#00db24");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ffffff");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#005fa0");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#00a857");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#00b649");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#00e619");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#00f10e");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#ffffff");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004_2){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Clustal X" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme,"Clustal X");
//    4. Check colors for all symbols
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#80a0f0");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#ffffff");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#f08080");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#c048c0");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#c048c0");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#80a0f0");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#f09048");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#15a4a4");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#80a0f0");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#ffffff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#f01505");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#80a0f0");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#80a0f0");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#15c015");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffffff");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#c0c000");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#15c015");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#f01505");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#15c015");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#15c015");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ffffff");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#80a0f0");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#80a0f0");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#ffffff");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#15a4a4");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#ffffff");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#ffffff");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004_3){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Helix propensity" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "Helix propensity");
//    4. Check colors for all symbols
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#e718e7");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#49b649");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#23dc23");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#778877");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#ff00ff");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#986798");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#00ff00");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#758a75");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#8a758a");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#ffffff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#a05fa0");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#ae51ae");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#ef10ef");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#1be41b");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffffff");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#00ff00");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#926d92");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#6f906f");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#36c936");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#47b847");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ffffff");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#857a85");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#8a758a");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#758a75");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#21de21");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#c936c9");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#ffffff");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004_4){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Hydrophobicity" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "Hydrophobicity");
//    4. Check colors for all symbols
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#ad0052");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#0c00f3");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#c2003d");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#0c00f3");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#0c00f3");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#cb0034");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#6a0095");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#1500ea");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#ff0000");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#ffffff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#0000ff");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#ea0015");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#b0004f");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#0c00f3");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffffff");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#4600b9");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#0c00f3");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#0000ff");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#5e00a1");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#61009e");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ffffff");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#f60009");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#5b00a4");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#680097");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#4f00b0");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#0c00f3");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#ffffff");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004_5){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Strand propensity" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "Strand propensity");
//    4. Check colors for all symbols
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#5858a7");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#4343bc");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#9d9d62");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#2121de");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#0000ff");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#c2c23d");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#4949b6");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#60609f");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#ecec13");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#ffffff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#4747b8");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#b2b24d");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#82827d");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#64649b");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffffff");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#2323dc");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#8c8c73");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#6b6b94");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#4949b6");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#9d9d62");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ffffff");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#ffff00");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#c0c03f");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#797986");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#d3d32c");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#4747b8");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#ffffff");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004_6){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Tailor" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "Tailor");
//    4. Check colors for all symbols
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#ccff00");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#ffffff");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#ffff00");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#ff0000");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#ff0066");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#00ff66");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#ff9900");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#0066ff");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#66ff00");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#ffffff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#6600ff");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#33ff00");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#00ff00");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#cc00ff");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffffff");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#ffcc00");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#ff00cc");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#0000ff");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#ff3300");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#ff6600");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ffffff");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#99ff00");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#00ccff");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#ffffff");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#00ffcc");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#ffffff");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#ffffff");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004_7){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Turn propensity" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "Turn propensity");
//    4. Check colors for all symbols
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#2cd3d3");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#f30c0c");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#a85757");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#e81717");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#3fc0c0");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#1ee1e1");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#ff0000");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#708f8f");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#00ffff");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#ffffff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#7e8181");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#1ce3e3");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#1ee1e1");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#ff0000");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffffff");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#f60909");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#778888");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#708f8f");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#e11e1e");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#738c8c");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ffffff");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#07f8f8");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#738c8c");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#7c8383");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#9d6262");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#5ba4a4");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#ffffff");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004_8){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "UGENE" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "UGENE");
//    4. Check colors for all symbols
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#00ccff");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#ccff99");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#6600ff");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#ffff00");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#c0bdbb");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#3df490");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#ff5082");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#fff233");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#00abed");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#6699ff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#ffee00");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#008fc6");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#1dc0ff");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#33ff00");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffff99");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#d5426c");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#3399ff");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#d5c700");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#ff83a7");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#ffd0dd");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ff00cc");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#ff6699");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#33cc78");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#fcfcfc");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#65ffab");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#ffffcc");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#33ff00");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0004_9){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select "Zappo" color scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "Zappo");
//    4. Check colors for all symbols
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#ffafaf");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#ffffff");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#ffff00");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#ff0000");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#ff0000");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#ffc800");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#ff00ff");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#6464ff");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#ffafaf");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#ffffff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#6464ff");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#ffafaf");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#ffafaf");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#00ff00");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffffff");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#ff00ff");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#00ff00");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#6464ff");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#00ff00");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#00ff00");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ffffff");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#ffafaf");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#ffc800");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#ffffff");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#ffc800");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#ffffff");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#ffffff");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0005){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Create custom color scheme
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme", NewColorSchemeCreator::amino);
//    3. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    Expected state: color scheme added to "Color" combobox
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "No colors");
    GTComboBox::setIndexWithText(os, colorScheme, "Scheme");
//    4. Select custom scheme
//    Expected state: scheme changed
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#ad0052");//a
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(1,0), "#0c00f3");//b
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#c2003d");//c
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,0), "#0c00f3");//d
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#0c00f3");//e
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(5,0), "#cb0034");//f
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,0), "#6a0095");//g
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,0), "#1500ea");//h
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(8,0), "#ff0000");//i
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(28,0), "#ffffff");//j
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(9,0), "#0000ff");//k
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(10,0), "#ea0015");//l
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(11,0), "#b0004f");//m
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(12,0), "#0c00f3");//n
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(26,0), "#ffffff");//o
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(13,0), "#4600b9");//p
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(14,0), "#0c00f3");//q
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(15,0), "#0000ff");//r
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(16,0), "#5e00a1");//s
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(17,0), "#61009e");//t
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(27,0), "#ffffff");//u
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(18,0), "#f60009");//v
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(19,0), "#5b00a4");//w
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(20,0), "#680097");//x
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(21,0), "#4f00b0");//y
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(22,0), "#0c00f3");//z
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(23,0), "#ffffff");//*
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(25,0), "#ffffff");//gap
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0005_1){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Create 3 color schemes
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme1", NewColorSchemeCreator::amino);
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme2", NewColorSchemeCreator::amino);
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme3", NewColorSchemeCreator::amino);
//    Expected state: color schemes added to "Color" combobox
     GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
     QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
     GTComboBox::setIndexWithText(os, colorScheme, "Scheme1", true, GTGlobals::UseMouse);
     GTComboBox::setIndexWithText(os, colorScheme, "Scheme2", true, GTGlobals::UseMouse);
     GTComboBox::setIndexWithText(os, colorScheme, "Scheme3", true, GTGlobals::UseMouse);
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0006){
//    1. Open file test/_common_data/alphabets/extended_amino.aln
    GTFileDialog::openFile(os, testDir + "_common_data/alphabets", "extended_amino.aln");
//    2. Create custom color scheme
    GTUtilsMSAEditorSequenceArea::createColorScheme(os, "Scheme", NewColorSchemeCreator::amino);
//    3. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    4. Select custom scheme
    QComboBox* colorScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "colorScheme"));
    GTComboBox::setIndexWithText(os, colorScheme, "Scheme");
//    5. Delete scheme which is selected
    GTUtilsMSAEditorSequenceArea::deleteColorScheme(os, "Scheme");
    GTGlobals::sleep(500);
//    UGENE not crashess
    for(int i = 0; i<29; i++){
        GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(i,0), "#ffffff");
    }

}

namespace {
void setHighlightingType(U2OpStatus &os, const QString& type){
    QComboBox* highlightingScheme = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "highlightingScheme"));
    CHECK_SET_ERR(highlightingScheme != NULL, "highlightingScheme not found");
    GTComboBox::setIndexWithText(os, highlightingScheme, type);
}
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0007){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select Phaneroptera_falcata as reference.
    GTUtilsOptionPanelMsa::addReference(os, "Phaneroptera_falcata");
//    4. Check no highlighting
    setHighlightingType(os, "No highlighting");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#fcff92");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,2), "#ff99b1");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#4eade1");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,0), "#70f970");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,2), "#ffffff");
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0007_1){
//    1. Open file test/_common_data/scenarios/msa/ty3.aln.gz
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "ty3.aln.gz");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select Phaneroptera_falcata as reference.
    GTUtilsOptionPanelMsa::addReference(os, "CfT-1_Cladosporium_fulvum");
//    4. Check no highlighting
    setHighlightingType(os, "No highlighting");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,1), "#c0bdbb");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,1), "#ffee00");

}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0008){
//    1. Open file test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select Phaneroptera_falcata as reference.
    GTUtilsOptionPanelMsa::addReference(os, "Phaneroptera_falcata");
//    4. Check Agreements highlighting type
    setHighlightingType(os, "Agreements");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,0), "#fcff92");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(0,2), "#ffffff");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(2,0), "#4eade1");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(3,1), "#ffffff");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(4,2), "#ffffff");
}

GUI_TEST_CLASS_DEFINITION(highlighting_test_0008_1){
//    1. Open file test/_common_data/scenarios/msa/ty3.aln.gz
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "ty3.aln.gz");
//    2. Open highlighting option panel tab
    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::Highlighting);
//    3. Select Phaneroptera_falcata as reference.
    GTUtilsOptionPanelMsa::addReference(os, "CfT-1_Cladosporium_fulvum");
//    4. Check Agreements highlighting type
    setHighlightingType(os, "Agreements");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(6,1), "#ffffff");
    GTUtilsMSAEditorSequenceArea::checkColor(os, QPoint(7,1), "#ffee00");

}

}
}
