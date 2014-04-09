/****************************************************************************
 * This file is part of libhawaii.
 *
 * Copyright (C) 2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QDebug>
#include <QtCore/QAtomicInt>
#include <QtCore/QHash>
#include <QtCore/QTimerEvent>

#include "dataprovider.h"
#include "dataprovider_p.h"

namespace Hawaii {

/*
 * DataProviderPrivate
 */

DataProviderPrivate::DataProviderPrivate(DataProvider *self)
    : valid(false)
    , timerId(0)
    , q_ptr(nullptr)
{
}

void DataProviderPrivate::_q_sourceDestroyed(QObject *object)
{
    Q_Q(DataProvider);

    if (sources.contains(object->objectName())) {
        sources.remove(object->objectName());
        Q_EMIT q->sourceRemoved(object->objectName());
    }
}

/*
 * DataProvider
 */

DataProvider::DataProvider(QObject *parent)
    : QObject(parent)
    , d_ptr(new DataProviderPrivate(this))
{
}

DataProvider::~DataProvider()
{
    delete d_ptr;
}

bool DataProvider::isValid() const
{
    Q_D(const DataProvider);
    return d->valid;
}

bool DataProvider::isEmpty() const
{
    Q_D(const DataProvider);
    return d->sources.isEmpty();
}

QStringList DataProvider::sources() const
{
    Q_D(const DataProvider);
    return d->sources.keys();
}

DataSource *DataProvider::source(const QString &name) const
{
    Q_D(const DataProvider);
    return d->sources.value(name);
}

void DataProvider::timerEvent(QTimerEvent *event)
{
    Q_D(DataProvider);

    if (event->timerId() == d->timerId) {
        // Ask all the sources connected to update
        for (DataSource *source: d->sources.values())
            source->checkForUpdate();
    } else {
        QObject::timerEvent(event);
    }
}

void DataProvider::setPollingInterval(uint msecs)
{
    Q_D(DataProvider);

    // Kill the timer
    killTimer(d->timerId);
    d->timerId = 0;

    // Start another timer if a polling interval has been specified,
    // passing 0 ms to this method will actually disable polling
    if (msecs > 0)
        d->timerId = startTimer(msecs);
}

void DataProvider::addSource(DataSource *source)
{
    Q_D(DataProvider);

    if (source->objectName().isEmpty())
        return;

    connect(source, &DataSource::dataChanged, [=]() {
        Q_EMIT sourceChanged(source->objectName(), source->data());
    });
    connect(source, SIGNAL(destroyed(QObject*)),
            this, SLOT(_q_sourceDestroyed(QObject*)));
    d->sources[source->objectName()] = source;
    Q_EMIT sourceAdded(source->objectName());
}

void DataProvider::removeSource(const QString &name)
{
    Q_D(DataProvider);

    if (d->sources.contains(name)) {
        DataSource *source = d->sources.value(name);
        source->disconnect(this);
        source->deleteLater();
        d->sources.remove(name);
        Q_EMIT sourceRemoved(name);
    }
}

} // namespace Hawaii

#include "moc_dataprovider.cpp"
