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

#include <NetworkManagerQt/Utils>

#include "wirelesssettings.h"

WirelessSettings::WirelessSettings(QObject *parent)
    : ConnectionSettings(parent)
    , m_ipv4Settings(new IPv4Settings(this))
{
}

quint32 WirelessSettings::mtu() const
{
    if (m_wirelessSettings)
        return m_wirelessSettings->mtu();
    else
        qWarning("NetworkManager wireless settings are invalid");
    return 0;
}

void WirelessSettings::setMtu(quint32 mtu)
{
    if (m_wirelessSettings) {
        if (this->mtu() == mtu)
            return;
        m_wirelessSettings->setMtu(mtu);
        m_connection->save();
        Q_EMIT mtuChanged();
    } else {
        qWarning("NetworkManager wireless settings are invalid");
    }
}

void WirelessSettings::handlePathChanged()
{
    NetworkManager::ConnectionSettings::Ptr settings = m_connection->settings();
    if (settings) {
        m_wirelessSettings = settings->setting(NetworkManager::Setting::Wireless).dynamicCast<NetworkManager::WirelessSetting>();
        m_ipv4Settings->setup(settings->setting(NetworkManager::Setting::Ipv4).dynamicCast<NetworkManager::Ipv4Setting>());
        m_ipv6Setting = settings->setting(NetworkManager::Setting::Ipv6).dynamicCast<NetworkManager::Ipv6Setting>();
    } else {
        m_wirelessSettings.reset();
        m_ipv4Settings->reset();
        m_ipv6Setting.reset();
    }

    Q_EMIT mtuChanged();
}
