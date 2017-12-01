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

#ifndef _U2_KRAKEN_CLASSIFY_TASK_SETTINGS_H_
#define _U2_KRAKEN_CLASSIFY_TASK_SETTINGS_H_

#include <QStringList>

namespace U2 {

class KrakenClassifyTaskSettings {
public:
    KrakenClassifyTaskSettings();

    QString databaseUrl;
    QStringList readsUrls;
    QStringList pairedReadsUrls;
    bool quickOperation;
    int minNumberOfHits;
    int numberOfThreads;
    bool preloadDatabase;

    QString reportUrl;

    static const QString SINGLE_END;
    static const QString PAIRED_END;
};

}   // namespace U2

#endif // _U2_KRAKEN_CLASSIFY_TASK_SETTINGS_H_
