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

#ifndef _U2_FIND_PATTERN_WIDGET_H_
#define _U2_FIND_PATTERN_WIDGET_H_

#include <ui/ui_FindPatternForm.h>

#include <U2Gui/CreateAnnotationWidgetController.h>

#include <QtGui/QtGui>


namespace U2 {

class ADVSequenceObjectContext;
class ADVSequenceWidget;
class AnnotatedDNAView;
class CreateAnnotationWidgetController;

enum SeqTranslIndex {
    SeqTranslIndex_Sequence,
    SeqTranslIndex_Translation
};

enum RegionSelectionIndex {
    RegionSelectionIndex_WholeSequence,
    RegionSelectionIndex_CustomRegion
};

enum ErrorMessageFlag {
    PatternIsTooLong,
    PatternAlphabetDoNotMatch
};


class FindPatternWidget : public QWidget, private Ui_FindPatternForm
{
    Q_OBJECT
public:
    FindPatternWidget(AnnotatedDNAView*);

private slots:
    void sl_showLessClicked(const QString&);

    void sl_onAlgorithmChanged(int);
    void sl_onRegionOptionChanged(int);
    void sl_enableBoxMaxResult(int checkBoxState);
    void sl_onRegionValueEdited();
    void sl_onMatchPercentChanged();
    void sl_onSequenceTranslationChanged(int);
    void sl_onSearchPatternChanged();
    void sl_onSearchClicked();

    /** Another sequence has been selected */
    void sl_onFocusChanged(ADVSequenceWidget*, ADVSequenceWidget*);

    /** A sequence part was added, removed or replaced */
    void sl_onSequenceModified(ADVSequenceObjectContext*);

private:
    void initLayout();
    void initAlgorithmLayout();
    void initStrandSelection();
    void initSeqTranslSelection();
    void initRegionSelection();
    void initResultsLimit();
    void updateLayout();
    void updateShowOptions();
    void connectSlots();
    void tunePercentBox();
    int getMaxError() const;

    /**
     * Enables or disables the Search button depending on
     * the Pattern field value (it should be not empty and not too long)
     * and on the validity of the region.
     */
    void checkState();

    /**
     * The "Match" spin is disabled if this is an amino acid sequence or
     * the search pattern is empty. Otherwise it is enabled.
     */
    void enableDisableMatchSpin();

    /** Update when a new document has been created, etc. */
    void updateAnnotationsWidget();

    /** Allows showing of several error messages. */
    void showHideErrorMessage(bool show, ErrorMessageFlag errorMessageFlag);

    void verifyPatternAlphabet();

    void setRegionToWholeSequence();

    U2Region getCompleteSearchRegion(bool& regionIsCorrect, qint64 maxLen) const;

    AnnotatedDNAView* annotatedDnaView;
    CreateAnnotationWidgetController* annotController;

    bool isAminoSequenceSelected;
    bool showMore;
    bool regionIsCorrect;
    int selectedAlgorithm;

    QList<ErrorMessageFlag> errorFlags;

    /** Widgets in the Algorithm group */
    QHBoxLayout* layoutMismatch;
    QHBoxLayout* layoutRegExpLen;
    QHBoxLayout* layoutRegExpInfo;

    QLabel* lblMatch;
    QSpinBox* spinMatch;
    QCheckBox* useAmbiguousBasesBox;

    QCheckBox* boxUseMaxResultLen;
    QSpinBox* boxMaxResultLen;

    QWidget* annotsWidget;

    static const int DEFAULT_RESULTS_NUM_LIMIT;
    static const int DEFAULT_REGEXP_RESULT_LENGTH_LIMIT;
};

} // namespace


#endif
