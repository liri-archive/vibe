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

#include <NetworkManagerQt/WirelessSetting>
#include <NetworkManagerQt/Ipv6Setting>

#include "connectionsettings.h"
#include "ipv4settings.h"

class WirelessSettings : public ConnectionSettings
{
    Q_OBJECT
    Q_PROPERTY(quint32 mtu READ mtu WRITE setMtu NOTIFY mtuChanged)
public:
    WirelessSettings(QObject *parent = nullptr);

    quint32 mtu() const;
    void setMtu(quint32 mtu);

Q_SIGNALS:
    void mtuChanged();

protected:
    void handlePathChanged() override;

private:
    NetworkManager::WirelessSetting::Ptr m_wirelessSettings;
    NetworkManager::Ipv6Setting::Ptr m_ipv6Setting;
    IPv4Settings *m_ipv4Settings;
};
