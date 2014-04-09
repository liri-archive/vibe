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

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtCore/QObject>

#include <hawaii/hawaii_export.h>

namespace Hawaii {

class DataProvider;
class DataSourcePrivate;

class HAWAII_EXPORT DataSource : public QObject
{
    friend class DataProvider;

    Q_OBJECT
    Q_PROPERTY(DataSource::Data data READ data NOTIFY dataChanged)
public:
    typedef QMap<QString, QVariant> Data;

    explicit DataSource(QObject *parent = 0);
    ~DataSource();

    Data data() const;

public Q_SLOTS:
    void update();

Q_SIGNALS:
    void dataChanged();

protected:
    virtual void setEntry(const QString &key, const QVariant &value);
    virtual void removeEntry(const QString &key);

    virtual void checkForUpdate();

private:
    Q_DECLARE_PRIVATE(DataSource)
    DataSourcePrivate *const d_ptr;
};

} // namespace Hawaii

#endif // DATASOURCE_H
