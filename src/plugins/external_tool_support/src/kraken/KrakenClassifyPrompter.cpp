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

#include "KrakenClassifyPrompter.h"
#include "KrakenClassifyWorkerFactory.h"

namespace U2 {
namespace LocalWorkflow {

KrakenClassifyPrompter::KrakenClassifyPrompter(Actor *actor)
    : PrompterBase<KrakenClassifyPrompter>(actor)
{

}

QString KrakenClassifyPrompter::composeRichDoc() {
    IntegralBusPort *input = qobject_cast<IntegralBusPort *>(target->getPort(KrakenClassifyWorkerFactory::INPUT_PORT_ID));
    Actor *readsProducer = input->getProducer(KrakenClassifyWorkerFactory::INPUT_READS_URL_SLOT_ID);

    const QString unsetString = "<font color='red'>" + tr("unset") + "</font>";
    const QString readsProducerName = NULL != readsProducer ? readsProducer->getLabel() : unsetString;

    const QString databaseUrl = getHyperlink(KrakenClassifyWorkerFactory::DATABASE_ATTR_ID, getURL(KrakenClassifyWorkerFactory::DATABASE_ATTR_ID));

    return tr("Classify sequences from <u>%1</u> with Kraken, use db_name database.").arg(readsProducerName).arg(databaseUrl);
}

}   // namespace LocalWorkflow
}   // namespace U2
