/****************************************************************************
 * This file is part of Vibe.
 *
 * Copyright (C) 2017 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPLv3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#pragma once

#include <QObject>

#include <NetworkManagerQt/Security8021xSetting>

class Security8021xSettings : public QObject
{
    Q_OBJECT
public:
    enum EapMethod {
        EapMethodUnknown = 0,
        EapMethodLeap,
        EapMethodMd5,
        EapMethodTls,
        EapMethodPeap,
        EapMethodTtls,
        EapMethodSim,
        EapMethodFast
    };
    Q_ENUM(EapMethod)

    Security8021xSettings(QObject *parent = nullptr);

    void setup(NetworkManager::Security8021xSetting::Ptr setting);
    void reset();

private:
    NetworkManager::Security8021xSetting::Ptr m_setting;
};
