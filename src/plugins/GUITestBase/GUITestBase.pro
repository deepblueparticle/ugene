include (GUITestBase.pri)

# Input
HEADERS +=  src/GUITestBasePlugin.h \
            src/tests/crazy_user/GUICrazyUserTest.h \
            src/tests/crazy_user/GTRandomGUIActionFactory.h \
            src/tests/crazy_user/GTAbstractGUIAction.h \
#   Runnables
#   Runnables / Qt
            src/runnables/qt/MessageBoxFiller.h \
            src/runnables/qt/PopupChooser.h \
            src/runnables/qt/FontDialogFiller.h \
            src/runnables/qt/ColorDialogFiller.h \
#   Runnables / UGENE
#   Runnables / UGENE / ugeneui
            src/runnables/ugene/ugeneui/CreateNewProjectWidgetFiller.h \
            src/runnables/ugene/ugeneui/ExportProjectDialogFiller.h \
            src/runnables/ugene/ugeneui/SelectDocumentFormatDialogFiller.h \
            src/runnables/ugene/ugeneui/SequenceReadingModeSelectorDialogFiller.h \
#   Runnables / UGENE / corelibs
#   Runnables / UGENE / corelibs / U2Gui
            src/runnables/ugene/corelibs/U2Gui/ExportDocumentDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/CreateAnnotationWidgetFiller.h \
            src/runnables/ugene/corelibs/U2Gui/CreateDocumentFromTextDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/DownloadRemoteFileDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/EditSequenceDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/RangeSelectionDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/RemovePartFromSequenceDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/PositionSelectorFiller.h \
            src/runnables/ugene/corelibs/U2Gui/RangeSelectorFiller.h \
            src/runnables/ugene/corelibs/U2Gui/util/RenameSequenceFiller.h \
            src/runnables/ugene/corelibs/U2Gui/util/ProjectTreeItemSelectorDialogBaseFiller.h \
            src/runnables/ugene/corelibs/U2Gui/EditAnnotationDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/EditQualifierDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/EditGroupAnnotationsDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/ExportChromatogramFiller.h \
            src/runnables/ugene/corelibs/U2Gui/FindRepeatsDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/ImportBAMFileDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/AlignShortReadsDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/ExportImageDialogFiller.h \
            src/runnables/ugene/corelibs/U2Gui/ConvertAssemblyToSAMDialogFiller.h \
#   Runnables / UGENE / corelibs / U2View
            src/runnables/ugene/corelibs/U2View/utils_smith_waterman/SmithWatermanDialogBaseFiller.h \
            src/runnables/ugene/corelibs/U2View/ov_msa/DeleteGapsDialogFiller.h \
            src/runnables/ugene/corelibs/U2View/ov_msa/ConsensusSelectorDialogFiller.h \
            src/runnables/ugene/corelibs/U2View/ov_msa/ExtractSelectedAsMSADialogFiller.h \
            src/runnables/ugene/corelibs/U2View/ov_msa/DistanceMatrixDialogFiller.h \
            src/runnables/ugene/corelibs/U2View/ov_msa/BuildTreeDialogFiller.h \
            src/runnables/ugene/corelibs/U2View/ov_msa/LicenseAgreemntDialogFiller.h \
            src/runnables/ugene/corelibs/U2View/ov_msa/GenerateAlignmentProfileDialogFiller.h \
            src/runnables/ugene/corelibs/U2View/ov_msa/BranchSettingsDialogFiller.h \
#   Runnables / UGENE / plugins_3rdparty
#   Runnables / UGENE / plugins_3rdparty / kalign
            src/runnables/ugene/plugins_3rdparty/kalign/KalignDialogFiller.h \
            src/runnables/ugene/plugins_3rdparty/umuscle/MuscleDialogFiller.h \
            src/runnables/ugene/plugins_3rdparty/clustalw/ClustalWDialogFiller.h \
#   Runnables / UGENE / plugins
#   Runnables / UGENE / plugins / dotplot
            src/runnables/ugene/plugins/dotplot/DotPlotDialogFiller.h \
            src/runnables/ugene/plugins/dotplot/BuildDotPlotDialogFiller.h \
#   Runnables / UGENE / plugins / dna_export
            src/runnables/ugene/plugins/dna_export/ExportAnnotationsDialogFiller.h \
            src/runnables/ugene/plugins/dna_export/ExportMSA2SequencesDialogFiller.h \
            src/runnables/ugene/plugins/dna_export/ExportMSA2MSADialogFiller.h \
            src/runnables/ugene/plugins/dna_export/ExportSequences2MSADialogFiller.h \
            src/runnables/ugene/plugins/dna_export/ExportSequencesDialogFiller.h \
            src/runnables/ugene/plugins/dna_export/ExportSelectedSequenceFromliAnmentDialogFiller.h \
            src/runnables/ugene/plugins/dna_export/ImportAnnotationsToCsvFiller.h \
#   Runnables / UGENE / plugins / workflow_designer
            src/runnables/ugene/plugins/workflow_designer/WizardFiller.h \
            src/runnables/ugene/plugins/workflow_designer/StartupDialogFiller.h \
#   Utils classes
            src/GTUtilsApp.h \
            src/GTUtilsDialog.h \
            src/GTUtilsDocument.h \
            src/GTUtilsEscClicker.h \
            src/GTUtilsLog.h \
            src/GTUtilsMdi.h \
            src/GTUtilsProject.h \
            src/GTUtilsProjectTreeView.h \
            src/GTUtilsAnnotationsTreeView.h \
            src/GTUtilsBookmarksTreeView.h \
            src/GTUtilsSequenceView.h \
            src/GTUtilsToolTip.h \
            src/GTUtilsTaskTreeView.h \
            src/GTUtilsMsaEditorSequenceArea.h \
            src/GTUtilsOptionsPanel.h \
            src/GTUtilsQueryDesigner.h \
            src/GTUtilsWorkflowDesigner.h \
#   Tests
            src/tests/GUIInitialChecks.h \
#   Tests/Regression Scenarios
            src/tests/regression_scenarios/GTTestsRegressionScenarios.h \
#   Tests/Common Scenarios
            src/tests/common_scenarios/sequence_edit/GTTestsSequenceEdit.h \
            src/tests/common_scenarios/sequence_view/GTTestsSequenceView.h \
            src/tests/common_scenarios/toggle_view/GTTestsToggleView.h \
            src/tests/common_scenarios/project/GTTestsProject.h \
            src/tests/common_scenarios/project/bookmarks/GTTestsBookmarks.h \
            src/tests/common_scenarios/project/relations/GTTestsProjectRelations.h \
            src/tests/common_scenarios/project/remote_request/GTTestsProjectRemoteRequest.h \
            src/tests/common_scenarios/project/sequence_exporting/GTTestsProjectSequenceExporting.h \
            src/tests/common_scenarios/project/multiple_docs/GTTestsProjectMultipleDocs.h \
            src/tests/common_scenarios/project/anonymous_project/GTTestsProjectAnonymousProject.h \
            src/tests/common_scenarios/project/user_locking/GTTestsProjectUserLocking.h \
            src/tests/common_scenarios/project/document_modifying/GTTestsProjectDocumentModifying.h \
            src/tests/common_scenarios/project/sequence_exporting/from_project_view/GTTestsFromProjectView.h \
            src/tests/common_scenarios/msa_editor/GTTestsMsaEditor.h \
            src/tests/common_scenarios/msa_editor/colors/GTTestsMSAEditorColors.h \
            src/tests/common_scenarios/msa_editor/consensus/GTTestsMSAEditorConsensus.h \
            src/tests/common_scenarios/msa_editor/edit/GTTestsMSAEditorEdit.h \
            src/tests/common_scenarios/annotations/GTTestsAnnotations.h \
            src/tests/common_scenarios/annotations/edit/GTTestsAnnotationsEdit.h \
            src/tests/common_scenarios/annotations/qualifiers/GTTestsAnnotationsQualifiers.h \
            src/tests/common_scenarios/document_from_text/GTTestsDocumentFromText.h \
            src/tests/common_scenarios/annotations_import/GTTestsAnnotationsImport.h \
            src/tests/common_scenarios/smith_waterman_dialog/GTTestsSWDialog.h \
            src/tests/common_scenarios/options_panel/GTTestsOptionPanel.h \
            src/tests/common_scenarios/dp_view/GTTestsDpView.h \
            src/tests/common_scenarios/Assembling/Assembly_browser/GTTestsAssemblyBrowser.h \
            src/tests/common_scenarios/Assembling/bowtie2/GTTestsBowtie2.h \
            src/tests/common_scenarios/Query_Designer/GTTestsQuerryDesigner.h \
            src/tests/common_scenarios/workflow_designer/GTTestsWorkflowDesigner.h \
            src/tests/common_scenarios/tree_viewer/GTTestsCommonScenariousTreeviewer.h \
            src/tests/common_scenarios/repeat_finder/GTTestsRepeatFinder.h \
            src/tests/common_scenarios/undo_redo/GTTestsUndoRedo.h \
            src/tests/common_scenarios/NIAID_pipelines/GTTestsNiaidPipelines.h \
#   UGENE primitives
            src/api/GTMSAEditorStatusWidget.h \
            src/api/GTRegionSelector.h \
            src/api/GTSequenceReadingModeDialog.h \
            src/api/GTSequenceReadingModeDialogUtils.h \
#   Qt primitives
            src/api/GTClipboard.h \
            src/api/GTCheckBox.h \
            src/api/GTComboBox.h \
            src/api/GTTabWidget.h \
            src/api/GTTabBar.h \
            src/api/GTSpinBox.h \
            src/api/GTRadioButton.h \
            src/api/GTFileDialog.h \
            src/api/GTFile.h \
            src/api/GTGlobals.h \
            src/api/GTKeyboardDriver.h \
            src/api/GTKeyboardUtils.h \
            src/api/GTLineEdit.h \
            src/api/GTMenu.h \
            src/api/GTMenuBar.h \
            src/api/GTMouse.h \
            src/api/GTMouseDriver.h \
            src/api/GTTextEdit.h \
            src/api/GTPlainTextEdit.h \
            src/api/GTScrollBar.h \
            src/api/GTSystem.h \
            src/api/GTTreeWidget.h \
            src/api/GTToolbar.h \
            src/api/GTWidget.h \
            src/api/GTAction.h \
            src/api/GTDoubleSpinBox.h \
            src/api/GTTableView.h  \
    src/runnables/ugene/corelibs/U2Gui/AppSettingsDialogFiller.h \
    src/runnables/ugene/plugins/workflow_designer/AliasesDialogFiller.h \
    src/runnables/ugene/plugins/workflow_designer/RPackageDialorFiller.h \
    src/api/GTGraphicsItem.h
SOURCES +=  src/GUITestBasePlugin.cpp \
            src/tests/crazy_user/GUICrazyUserTest.cpp \
            src/tests/crazy_user/GTRandomGUIActionFactory.cpp \
            src/tests/crazy_user/GTAbstractGUIAction.cpp \
#   Runnables
#   Runnables / Qt
            src/runnables/qt/MessageBoxFiller.cpp \
            src/runnables/qt/PopupChooser.cpp \
            src/runnables/qt/FontDialogFiller.cpp \
            src/runnables/qt/ColorDialogFiller.cpp \
#   Runnables / UGENE
#   Runnables / UGENE / ugeneui
            src/runnables/ugene/ugeneui/CreateNewProjectWidgetFiller.cpp \
            src/runnables/ugene/ugeneui/ExportProjectDialogFiller.cpp \
            src/runnables/ugene/ugeneui/SelectDocumentFormatDialogFiller.cpp \
            src/runnables/ugene/ugeneui/SequenceReadingModeSelectorDialogFiller.cpp \
#   Runnables / UGENE / corelibs
#   Runnables / UGENE / corelibs / U2Gui
            src/runnables/ugene/corelibs/U2Gui/ExportDocumentDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/CreateAnnotationWidgetFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/CreateDocumentFromTextDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/DownloadRemoteFileDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/EditSequenceDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/RangeSelectionDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/RemovePartFromSequenceDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/PositionSelectorFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/RangeSelectorFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/util/RenameSequenceFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/util/ProjectTreeItemSelectorDialogBaseFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/EditAnnotationDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/EditQualifierDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/EditGroupAnnotationsDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/ExportChromatogramFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/FindRepeatsDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/AlignShortReadsDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/ImportBAMFileDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/ExportImageDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2Gui/ConvertAssemblyToSAMDialogFiller.cpp \
#   Runnables / UGENE / corelibs / U2View
            src/runnables/ugene/corelibs/U2View/utils_smith_waterman/SmithWatermanDialogBaseFiller.cpp \
            src/runnables/ugene/corelibs/U2View/ov_msa/DeleteGapsDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2View/ov_msa/ConsensusSelectorDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2View/ov_msa/ExtractSelectedAsMSADialogFiller.cpp \
            src/runnables/ugene/corelibs/U2View/ov_msa/GenerateAlignmentProfileDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2View/ov_msa/DistanceMatrixDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2View/ov_msa/BuildTreeDialogFiller.cpp \
            src/runnables/ugene/corelibs/U2View/ov_msa/BranchSettingsDialogFiller.cpp \
#   Runnables / UGENE / plugins_3rdparty
#   Runnables / UGENE / plugins_3rdparty / kalign
            src/runnables/ugene/plugins_3rdparty/kalign/KalignDialogFiller.cpp \
            src/runnables/ugene/plugins_3rdparty/umuscle/MuscleDialogFiller.cpp \
            src/runnables/ugene/plugins_3rdparty/clustalw/ClustalWDialogFiller.cpp \
#   Runnables / UGENE / plugins
#   Runnables / UGENE / plugins / dotplot
            src/runnables/ugene/plugins/dotplot/DotPlotDialogFiller.cpp \
            src/runnables/ugene/plugins/dotplot/BuildDotPlotDialogFiller.cpp \
#   Runnables / UGENE / plugins / dna_export
            src/runnables/ugene/plugins/dna_export/ExportAnnotationsDialogFiller.cpp \
            src/runnables/ugene/plugins/dna_export/ExportMSA2SequencesDialogFiller.cpp \
            src/runnables/ugene/plugins/dna_export/ExportMSA2MSADialogFiller.cpp \
            src/runnables/ugene/plugins/dna_export/ExportSequences2MSADialogFiller.cpp \
            src/runnables/ugene/plugins/dna_export/ExportSequencesDialogFiller.cpp \
            src/runnables/ugene/plugins/dna_export/ImportAnnotationsToCsvFiller.cpp \
            src/runnables/ugene/plugins/dna_export/ExportSelectedSequenceFromliAnmentDialogFiller.cpp \
#   Runnables / UGENE / plugins / workflow_designer
            src/runnables/ugene/plugins/workflow_designer/WizardFiller.cpp \
            src/runnables/ugene/plugins/workflow_designer/StartupDialogFiller.cpp \
#   Utils classes
            src/GTUtilsApp.cpp \
            src/GTUtilsDialog.cpp \
            src/GTUtilsDocument.cpp \
            src/GTUtilsEscClicker.cpp \
            src/GTUtilsLog.cpp \
            src/GTUtilsMdi.cpp \
            src/GTUtilsProject.cpp \
            src/GTUtilsProjectTreeView.cpp \
            src/GTUtilsAnnotationsTreeView.cpp \
            src/GTUtilsBookmarksTreeView.cpp \
            src/GTUtilsSequenceView.cpp \
            src/GTUtilsToolTip.cpp \
            src/GTUtilsTaskTreeView.cpp \
            src/GTUtilsMsaEditorSequenceArea.cpp \
            src/GTUtilsOptionsPanel.cpp \
            src/GTUtilsQueryDesigner.cpp \
            src/GTUtilsWorkflowDesigner.cpp \
#   Tests
            src/tests/GUIInitialChecks.cpp \
#   Tests/Regression Scenarios
            src/tests/regression_scenarios/GTTestsRegressionScenarios.cpp \
#   Tests/Common Scenarios
            src/tests/common_scenarios/sequence_edit/GTTestsSequenceEdit.cpp \
            src/tests/common_scenarios/sequence_view/GTTestsSequenceView.cpp \
            src/tests/common_scenarios/toggle_view/GTTestsToggleView.cpp \
            src/tests/common_scenarios/project/GTTestsProject.cpp \
            src/tests/common_scenarios/project/bookmarks/GTTestsBookmarks.cpp \
            src/tests/common_scenarios/project/relations/GTTestsProjectRelations.cpp \
            src/tests/common_scenarios/project/remote_request/GTTestsProjectRemoteRequest.cpp \
            src/tests/common_scenarios/project/sequence_exporting/GTTestsProjectSequenceExporting.cpp \
            src/tests/common_scenarios/project/user_locking/GTTestsProjectUserLocking.cpp \
            src/tests/common_scenarios/project/anonymous_project/GTTestsProjectAnonymousProject.cpp \
            src/tests/common_scenarios/project/multiple_docs/GTTestsProjectMultipleDocs.cpp \
            src/tests/common_scenarios/project/document_modifying/GTTestsProjectDocumentModifying.cpp \
            src/tests/common_scenarios/project/sequence_exporting/from_project_view/GTTestsFromProjectView.cpp \
            src/tests/common_scenarios/msa_editor/GTTestsMsaEditor.cpp \
            src/tests/common_scenarios/msa_editor/consensus/GTTestsMSAEditorConsensus.cpp \
            src/tests/common_scenarios/msa_editor/colors/GTTestsMSAEditorColors.cpp \
            src/tests/common_scenarios/msa_editor/edit/GTTestsMSAEditorEdit.cpp  \
            src/tests/common_scenarios/annotations/GTTestsAnnotations.cpp \
            src/tests/common_scenarios/annotations/edit/GTTestsAnnotationsEdit.cpp \
            src/tests/common_scenarios/annotations/qualifiers/GTTestsAnnotationsQualifiers.cpp \
            src/tests/common_scenarios/document_from_text/GTTestsDocumentFromText.cpp \
            src/tests/common_scenarios/annotations_import/GTTestsAnnotationsImport.cpp \
            src/tests/common_scenarios/smith_waterman_dialog/GTTestsSWDialog.cpp \
            src/tests/common_scenarios/options_panel/GTTestsOptionPanel.cpp \
            src/tests/common_scenarios/dp_view/GTTestsDpView.cpp \
            src/tests/common_scenarios/Assembling/Assembly_browser/GTTestsAssemblyBrowser.cpp \
            src/tests/common_scenarios/Assembling/bowtie2/GTTestsBowtie2.cpp \
            src/tests/common_scenarios/Query_Designer/GTTestsQuerryDesigner.cpp \
            src/tests/common_scenarios/workflow_designer/GTTestsWorkflowDesigner.cpp \
            src/tests/common_scenarios/tree_viewer/GTTestsCommonScenariousTreeviewer.cpp \
            src/tests/common_scenarios/repeat_finder/GTTestsRepeatFinder.cpp \
            src/tests/common_scenarios/undo_redo/GTTestsUndoRedo.cpp \
            src/tests/common_scenarios/NIAID_pipelines/GTTestsNiaidPipelines.cpp \
#   UGENE primitives
            src/api/GTMSAEditorStatusWidget.cpp \
            src/api/GTRegionSelector.cpp \
            src/api/GTSequenceReadingModeDialog.cpp \
            src/api/GTSequenceReadingModeDialogUtils.cpp \
#   Qt primitives
            src/api/GTClipboard.cpp \
            src/api/GTCheckBox.cpp \
            src/api/GTComboBox.cpp \
            src/api/GTTabWidget.cpp \
            src/api/GTTabBar.cpp \
            src/api/GTSpinBox.cpp \
            src/api/GTRadioButton.cpp \
            src/api/GTFileDialog.cpp \
            src/api/GTFile.cpp \
            src/api/GTGlobals.cpp \
            src/api/GTKeyboardDriver.cpp \
            src/api/GTKeyboardDriverLinux.cpp \
            src/api/GTKeyboardDriverMac.cpp \
            src/api/GTKeyboardDriverWindows.cpp \
            src/api/GTKeyboardUtils.cpp \
            src/api/GTLineEdit.cpp \
            src/api/GTMenu.cpp \
            src/api/GTMenuBar.cpp \
            src/api/GTMouse.cpp \
            src/api/GTMouseDriver.cpp \
            src/api/GTMouseDriverLinux.cpp \
            src/api/GTMouseDriverMac.cpp \
            src/api/GTMouseDriverWindows.cpp \
            src/api/GTTextEdit.cpp \
            src/api/GTPlainTextEdit.cpp \
            src/api/GTScrollBar.cpp \
            src/api/GTSystem.cpp \
            src/api/GTToolbar.cpp \
            src/api/GTTreeWidget.cpp \
            src/api/GTWidget.cpp \
            src/api/GTAction.cpp \
            src/api/GTDoubleSpinBox.cpp \
            src/api/GTTableView.cpp \
    src/runnables/ugene/corelibs/U2Gui/AppSettingsDialogFiller.cpp \
    src/runnables/ugene/plugins/workflow_designer/AliasesDialogFiller.cpp \
    src/runnables/ugene/plugins/workflow_designer/RPackageDialorFiller.cpp \
    src/api/GTGraphicsItem.cpp
