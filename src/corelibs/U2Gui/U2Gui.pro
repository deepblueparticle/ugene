include (U2Gui.pri)

# Input
HEADERS += src/AppSettingsGUI.h \
           src/MainWindow.h \
           src/Notification.h \
           src/NotificationsTypes.h \
           src/NotificationWidget.h \
           src/ObjectViewModel.h \
           src/ObjectViewTasks.h \
           src/OpenViewTask.h \
           src/PasteController.h \
           src/PluginViewer.h \
           src/ProjectParsing.h \
           src/ProjectView.h \
           src/ToolsMenu.h \
           src/U2SavableWidget.h \
           src/U2WidgetStateStorage.h \
           src/UnloadDocumentTask.h \
           src/WelcomePageAction.h \
           src/options_panel/GroupHeaderImageWidget.h \
           src/options_panel/GroupOptionsWidget.h \
           src/options_panel/OptionsPanel.h \
           src/options_panel/OptionsPanelGroup.h \
           src/options_panel/OptionsPanelWidget.h \
           src/options_panel/OPWidgetFactory.h \
           src/options_panel/OPWidgetFactoryRegistry.h \
           src/options_panel/ShowHideSubgroupWidget.h \
           src/util/AddNewDocumentDialogController.h \
           src/util/AddNewDocumentDialogImpl.h \
           src/util/AuthenticationDialog.h \
           src/util/AuthenticationWidget.h \
           src/util/BreakpointConditionEditDialog.h \
           src/util/CreateAnnotationDialog.h \
           src/util/CreateAnnotationFullWidget.h \
           src/util/CreateAnnotationNormalWidget.h \
           src/util/CreateAnnotationOptionsPanelWidget.h \
           src/util/CreateAnnotationWidget.h \
           src/util/CreateAnnotationWidgetController.h \
           src/util/CreateDocumentFromTextDialogController.h \
           src/util/CreateObjectRelationDialogController.h \
           src/util/CreateSequenceFromTextAndOpenViewTask.h \
           src/util/CredentialsAskerGui.h \
           src/util/DialogUtils.h \
           src/util/DocumentFormatComboboxController.h \
           src/util/DownloadRemoteFileDialog.h \
           src/util/EditQualifierDialog.h \
           src/util/EditSequenceDialogController.h \
           src/util/EditSettingsDialog.h \
           src/util/ExportAnnotations2CSVTask.h \
           src/util/ExportAnnotationsDialog.h \
           src/util/ExportDocumentDialogController.h \
           src/util/ExportImageDialog.h \
           src/util/ExportObjectUtils.h \
           src/util/GenbankLocationValidator.h \
           src/util/GlassView.h \
           src/util/GObjectComboBoxController.h \
           src/util/GraphUtils.h \
           src/util/GroupedComboBoxDelegate.h \
           src/util/GScrollBar.h \
           src/util/GUIUtils.h \
           src/util/HelpButton.h \
           src/util/ImportSequenceFromRawDataTask.h \
           src/util/InputWidgetsControllers.h \
           src/util/ImportWidgetsFactories.h \
           src/util/LabelClickTransmitter.h \
           src/util/LastUsedDirHelper.h \
           src/util/LocalToolbar.h \
           src/util/MultiClickMenu.h \
           src/util/ObjectViewTreeController.h \
           src/util/OrderedToolbar.h \
           src/util/PositionSelector.h \
           src/util/ProjectDocumentComboBoxController.h \
           src/util/ProjectTreeItemSelectorDialog.h \
           src/util/ProjectTreeItemSelectorDialogImpl.h \
           src/util/RangeSelector.h \
           src/util/RegionSelector.h \
           src/util/RegionSelectorController.h \
           src/util/RegionSelectorWithExcludedRegion.h \
           src/util/RemovePartFromSequenceDialogController.h \
           src/util/SaveDocumentController.h \
           src/util/ScaleBar.h \
           src/util/ScriptEditorDelegate.h \
           src/util/ScriptEditorDialog.h \
           src/util/ScriptEditorWidget.h \
           src/util/ScriptHighlighter.h \
           src/util/SearchBox.h \
           src/util/SearchGenbankSequenceDialogController.h \
           src/util/SelectionModificationHelper.h \
           src/util/SeqPasterWidgetController.h \
           src/util/SequenceTextEdit.h \
           src/util/SuggestCompleter.h \
           src/util/TreeWidgetUtils.h \
           src/util/U2FileDialog.h \
           src/util/U2LongLongValidator.h \
           src/util/WidgetWithLocalToolbar.h \
           src/util/imageExport/ImageExportTask.h \
           src/util/imageExport/WidgetScreenshotExportTask.h \
           src/util/ImportWidgets/AceImportWidget.h \
           src/util/ImportWidgets/AprImportWidget.h \
           src/util/ImportWidgets/ImportWidget.h \
           src/util/logview/LogView.h \
           src/util/project/filter_tasks/FeatureKeyFilterTask.h \
           src/util/project/filter_tasks/MaContentFilterTask.h \
           src/util/project/filter_tasks/MaSeqNameFilterTask.h \
           src/util/project/filter_tasks/ObjectNameFilterTask.h \
           src/util/project/filter_tasks/SequenceAccFilterTask.h \
           src/util/project/filter_tasks/TextContentFilterTask.h \
           src/util/project/ConnectionHelper.h \
           src/util/project/DocumentFolders.h \
           src/util/project/EditableTreeView.h \
           src/util/project/FilteredProjectItemDelegate.h \
           src/util/project/FilteredProjectGroup.h \
           src/util/project/FolderNameDialog.h \
           src/util/project/LoadDocumentTaskProvider.h \
           src/util/project/ProjectFilteringController.h \
           src/util/project/ProjectFilterNames.h \
           src/util/project/ProjectFilterProxyModel.h \
           src/util/project/ProjectTreeController.h \
           src/util/project/ProjectUpdater.h \
           src/util/project/ProjectUtils.h \
           src/util/project/ProjectViewFilterModel.h \
           src/util/project/ProjectViewModel.h \
           src/util/shared_db/CommonImportOptionsDialog.h \
           src/util/shared_db/EditConnectionDialog.h \
           src/util/shared_db/ImportOptionsWidget.h \
           src/util/shared_db/ImportToDatabaseDialog.h \
           src/util/shared_db/ItemToImportEditDialog.h \
           src/util/shared_db/SharedConnectionsDialog.h

FORMS += src/util/AddNewDocumentDialog.ui \
         src/util/AuthenticationDialog.ui \
         src/util/AuthenticationWidget.ui \
         src/util/BreakpointConditionEditDialog.ui \
         src/util/CreateAnnotationDialog.ui \
         src/util/CreateAnnotationFullWidget.ui \
         src/util/CreateAnnotationNormalWidget.ui \
         src/util/CreateAnnotationOptionsPanelWidget.ui \
         src/util/CreateDocumentFromTextDialog.ui \
         src/util/CreateObjectRelationDialog.ui \
         src/util/DownloadRemoteFileDialog.ui \
         src/util/EditQualifierDialog.ui \
         src/util/EditSequenceDialog.ui \
         src/util/EditSettingsDialog.ui \
         src/util/ExportAnnotationsDialog.ui \
         src/util/ExportDocumentDialog.ui \
         src/util/ExportImageDialog.ui \
         src/util/project/FolderNameDialog.ui \
         src/util/MultipartDocFormatConfiguratorWidget.ui \
         src/util/ProjectTreeItemSelectorDialogBase.ui \
         src/util/RangeSelectionDialog.ui \
         src/util/RegionSelectorWithExcludedRegion.ui \
         src/util/RemovePartFromSequenceDialog.ui \
         src/util/ScriptEditorDialog.ui \
         src/util/SearchGenbankSequenceDialog.ui \
         src/util/SeqPasterWidget.ui \
         src/util/ImportWidgets/AceImportWidget.ui \
         src/util/ImportWidgets/AprImportWidget.ui \
         src/util/shared_db/CommonImportOptionsDialog.ui \
         src/util/shared_db/EditConnectionDialog.ui \
         src/util/shared_db/ImportOptionsWidget.ui \
         src/util/shared_db/ImportToDatabaseDialog.ui \
         src/util/shared_db/ItemToImportEditDialog.ui \
         src/util/shared_db/SharedConnectionsDialog.ui

SOURCES += src/MainWindow.cpp \
           src/Notification.cpp \
           src/NotificationWidget.cpp \
           src/ObjectViewModel.cpp \
           src/ObjectViewTasks.cpp \
           src/OpenViewTask.cpp \
           src/PasteController.cpp \
           src/ProjectParsing.cpp \
           src/ToolsMenu.cpp \
           src/UnloadDocumentTask.cpp \
           src/U2SavableWidget.cpp \
           src/U2WidgetStateStorage.cpp \
           src/WelcomePageAction.cpp \
           src/options_panel/GroupHeaderImageWidget.cpp \
           src/options_panel/GroupOptionsWidget.cpp \
           src/options_panel/OptionsPanel.cpp \
           src/options_panel/OptionsPanelGroup.cpp \
           src/options_panel/OptionsPanelWidget.cpp \
           src/options_panel/OPWidgetFactory.cpp \
           src/options_panel/OPWidgetFactoryRegistry.cpp \
           src/options_panel/ShowHideSubgroupWidget.cpp \
           src/util/AddNewDocumentDialogImpl.cpp \
           src/util/AuthenticationDialog.cpp \
           src/util/AuthenticationWidget.cpp \
           src/util/BreakpointConditionEditDialog.cpp \
           src/util/CreateAnnotationDialog.cpp \
           src/util/CreateAnnotationWidget.cpp \
           src/util/CreateAnnotationFullWidget.cpp \
           src/util/CreateAnnotationNormalWidget.cpp \
           src/util/CreateAnnotationOptionsPanelWidget.cpp \
           src/util/CreateAnnotationWidgetController.cpp \
           src/util/CreateDocumentFromTextDialogController.cpp \
           src/util/CreateObjectRelationDialogController.cpp \
           src/util/CreateSequenceFromTextAndOpenViewTask.cpp \
           src/util/CredentialsAskerGui.cpp \
           src/util/DialogUtils.cpp \
           src/util/DocumentFormatComboboxController.cpp \
           src/util/DownloadRemoteFileDialog.cpp \
           src/util/EditQualifierDialog.cpp \
           src/util/EditSequenceDialogController.cpp \
           src/util/EditSettingsDialog.cpp \
           src/util/ExportAnnotations2CSVTask.cpp \
           src/util/ExportAnnotationsDialog.cpp \
           src/util/ExportDocumentDialogController.cpp \
           src/util/ExportImageDialog.cpp \
           src/util/ExportObjectUtils.cpp \
           src/util/GenbankLocationValidator.cpp \
           src/util/GlassView.cpp \
           src/util/GObjectComboBoxController.cpp \
           src/util/GraphUtils.cpp \
           src/util/GroupedComboBoxDelegate.cpp \
           src/util/GScrollBar.cpp \
           src/util/GUIUtils.cpp \
           src/util/HelpButton.cpp \
           src/util/ImportSequenceFromRawDataTask.cpp \
           src/util/InputWidgetsControllers.cpp \
           src/util/ImportWidgetsFactories.cpp \
           src/util/LabelClickTransmitter.cpp \
           src/util/LastUsedDirHelper.cpp \
           src/util/LocalToolbar.cpp \
           src/util/MultiClickMenu.cpp \
           src/util/ObjectViewTreeController.cpp \
           src/util/OrderedToolbar.cpp \
           src/util/PositionSelector.cpp \
           src/util/ProjectDocumentComboBoxController.cpp \
           src/util/ProjectTreeItemSelectorDialog.cpp \
           src/util/RangeSelector.cpp \
           src/util/RegionSelector.cpp \
           src/util/RegionSelectorController.cpp \
           src/util/RegionSelectorWithExcludedRegion.cpp \
           src/util/RemovePartFromSequenceDialogController.cpp \
           src/util/SaveDocumentController.cpp \
           src/util/ScaleBar.cpp \
           src/util/ScriptEditorDelegate.cpp \
           src/util/ScriptEditorDialog.cpp \
           src/util/ScriptEditorWidget.cpp \
           src/util/ScriptHighlighter.cpp \
           src/util/SearchBox.cpp \
           src/util/SearchGenbankSequenceDialogController.cpp \
           src/util/SelectionModificationHelper.cpp \
           src/util/SeqPasterWidgetController.cpp \
           src/util/SequenceTextEdit.cpp \
           src/util/SuggestCompleter.cpp \
           src/util/TreeWidgetUtils.cpp \
           src/util/U2FileDialog.cpp \
           src/util/U2LongLongValidator.cpp \
           src/util/WidgetWithLocalToolbar.cpp \
           src/util/imageExport/ImageExportTask.cpp \
           src/util/imageExport/WidgetScreenshotExportTask.cpp \
           src/util/ImportWidgets/AceImportWidget.cpp \
           src/util/ImportWidgets/AprImportWidget.cpp \
           src/util/ImportWidgets/ImportWidget.cpp \
           src/util/logview/LogView.cpp \
           src/util/project/filter_tasks/FeatureKeyFilterTask.cpp \
           src/util/project/filter_tasks/MaContentFilterTask.cpp \
           src/util/project/filter_tasks/MaSeqNameFilterTask.cpp \
           src/util/project/filter_tasks/ObjectNameFilterTask.cpp \
           src/util/project/filter_tasks/SequenceAccFilterTask.cpp \
           src/util/project/filter_tasks/TextContentFilterTask.cpp \
           src/util/project/ConnectionHelper.cpp \
           src/util/project/DocumentFolders.cpp \
           src/util/project/EditableTreeView.cpp \
           src/util/project/FilteredProjectItemDelegate.cpp \
           src/util/project/FilteredProjectGroup.cpp \
           src/util/project/FolderNameDialog.cpp \
           src/util/project/ProjectFilteringController.cpp \
           src/util/project/ProjectFilterNames.cpp \
           src/util/project/ProjectFilterProxyModel.cpp \
           src/util/project/ProjectTreeController.cpp \
           src/util/project/ProjectUpdater.cpp \
           src/util/project/ProjectUtils.cpp \
           src/util/project/ProjectViewFilterModel.cpp \
           src/util/project/ProjectViewModel.cpp \
           src/util/shared_db/CommonImportOptionsDialog.cpp \
           src/util/shared_db/EditConnectionDialog.cpp \
           src/util/shared_db/ImportOptionsWidget.cpp \
           src/util/shared_db/ImportToDatabaseDialog.cpp \
           src/util/shared_db/ItemToImportEditDialog.cpp \
           src/util/shared_db/SharedConnectionsDialog.cpp
RESOURCES += U2Gui.qrc
TRANSLATIONS += transl/russian.ts
