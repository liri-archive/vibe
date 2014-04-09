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

#ifndef DATAPROVIDERMANAGER_H
#define DATAPROVIDERMANAGER_H

#include <QtCore/QObject>

#include <hawaii/hawaii_export.h>

namespace Hawaii {

class DataProvider;
class DataProviderManagerPrivate;

class HAWAII_EXPORT DataProviderManager : public QObject
{
    Q_OBJECT
public:
    explicit DataProviderManager(QObject *parent = 0);
    ~DataProviderManager();

    static DataProviderManager *instance();

    DataProvider *loadProvider(const QString &name);
    void unloadProvider(const QString &name);

    DataProvider *provider(const QString &name);

private:
    Q_DECLARE_PRIVATE(DataProviderManager)
    DataProviderManagerPrivate *const d_ptr;
};

} // namespace Hawaii

#endif // DATAPROVIDERMANAGER_H
