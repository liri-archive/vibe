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

#include <QtCore/QMap>
#include <QtCore/QVariant>

#include "dataprovider.h"
#include "datasource.h"

namespace Hawaii {

/*
 * DataSourcePrivate
 */

class DataSourcePrivate
{
public:
    DataSourcePrivate(DataSource *self)
        : dirty(false)
        , q_ptr(self)
    {
    }

    DataProvider *dataProvider()
    {
        Q_Q(DataSource);

        QObject *object = q;
        DataProvider *provider = nullptr;

        while (!provider) {
            object = object->parent();
            if (!object)
                return nullptr;

            provider = qobject_cast<DataProvider *>(object);
            if (provider)
                break;
        }

        return provider;
    }

    DataSource::Data data;
    bool dirty;

protected:
    Q_DECLARE_PUBLIC(DataSource)
    DataSource *q_ptr;
};

/*
 * DataSource
 */

DataSource::DataSource(QObject *parent)
    : QObject(parent)
    , d_ptr(new DataSourcePrivate(this))
{
}

DataSource::~DataSource()
{
    delete d_ptr;
}

DataSource::Data DataSource::data() const
{
    Q_D(const DataSource);
    return d->data;
}

void DataSource::update()
{
    Q_D(DataSource);

    if (d->dirty) {
        Q_EMIT dataChanged();
        d->dirty = false;
    }
}

void DataSource::setEntry(const QString &key, const QVariant &value)
{
    Q_D(DataSource);

    d->data.insert(key, value);
    d->dirty = true;
}

void DataSource::removeEntry(const QString &key)
{
    Q_D(DataSource);

    if (!d->data.contains(key))
        return;

    d->data.remove(key);
    d->dirty = true;
}

void DataSource::checkForUpdate()
{
}

} // namespace Hawaii

#include "moc_datasource.cpp"
