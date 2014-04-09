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

#ifndef DATAPROVIDER_P_H
#define DATAPROVIDER_P_H

#include "datasource.h"

namespace Hawaii {

class DataProviderPrivate
{
public:
    DataProviderPrivate(Hawaii::DataProvider *self);

    void _q_sourceDestroyed(QObject *object);

    bool valid;
    QAtomicInt refCount;
    QHash<QString, DataSource *> sources;
    int timerId;

protected:
    Q_DECLARE_PUBLIC(DataProvider)
    DataProvider *q_ptr;
};

} // namespace Hawaii

#endif // DATAPROVIDER_P_H
