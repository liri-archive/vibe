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

#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include <hawaii/hawaii_export.h>
#include <hawaii/datasource.h>

namespace Hawaii {

class DataProviderPrivate;

class HAWAII_EXPORT DataProvider : public QObject
{
    Q_OBJECT
public:
    explicit DataProvider(QObject *parent = 0);
    ~DataProvider();

    bool isValid() const;

    bool isEmpty() const;

    virtual QStringList sources() const;

    Q_INVOKABLE DataSource *source(const QString &name) const;

Q_SIGNALS:
    void sourceAdded(const QString &name);
    void sourceChanged(const QString &name, const DataSource::Data &data);
    void sourceRemoved(const QString &name);

protected:
    virtual void timerEvent(QTimerEvent *event);

    virtual void setPollingInterval(uint msecs);

    void addSource(DataSource *source);
    void removeSource(const QString &name);

private:
    friend class DataProviderManager;

    Q_DECLARE_PRIVATE(DataProvider)
    DataProviderPrivate *const d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_sourceDestroyed(QObject *object))
};

} // namespace Hawaii

#define HawaiiDataProvider_iid "org.hawaii.dataprovider"

Q_DECLARE_INTERFACE(Hawaii::DataProvider, HawaiiDataProvider_iid)

#endif // DATAPROVIDER_H
