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

#include "ipv4settings.h"
#include "wiredsettings.h"

WiredSettings::WiredSettings(QObject *parent)
    : ConnectionSettings(parent)
    , m_securitySettings(new Security8021xSettings(this))
    , m_ipv4Settings(new IPv4Settings(this))
{
}

quint32 WiredSettings::speed() const
{
    if (m_wiredSetting)
        return m_wiredSetting->speed();
    else
        qWarning("NetworkManager wired settings are invalid");
    return 0;
}

void WiredSettings::setSpeed(quint32 speed)
{
    if (m_wiredSetting) {
        if (this->speed() == speed)
            return;
        m_wiredSetting->setSpeed(speed);
        updateSettings(m_wiredSetting->name(), m_wiredSetting->toMap());
        Q_EMIT speedChanged();
    } else {
        qWarning("NetworkManager wired settings are invalid");
    }
}

QString WiredSettings::macAddress() const
{
    if (m_wiredSetting)
        return NetworkManager::macAddressAsString(m_wiredSetting->macAddress());
    else
        qWarning("NetworkManager wired settings are invalid");
    return QString();
}

void WiredSettings::setMacAddress(const QString &macAddress)
{
    if (m_wiredSetting) {
        if (this->macAddress() == macAddress)
            return;
        m_wiredSetting->setMacAddress(NetworkManager::macAddressFromString(macAddress));
        updateSettings(m_wiredSetting->name(), m_wiredSetting->toMap());
        Q_EMIT macAddressChanged();
    } else {
        qWarning("NetworkManager wired settings are invalid");
    }
}

QString WiredSettings::clonedMacAddress() const
{
    if (m_wiredSetting)
        return NetworkManager::macAddressAsString(m_wiredSetting->clonedMacAddress());
    else
        qWarning("NetworkManager wired settings are invalid");
    return QString();
}

void WiredSettings::setClonedMacAddress(const QString &clonedMacAddress)
{
    if (m_wiredSetting) {
        if (this->clonedMacAddress() == clonedMacAddress)
            return;
        m_wiredSetting->setClonedMacAddress(NetworkManager::macAddressFromString(clonedMacAddress));
        updateSettings(m_wiredSetting->name(), m_wiredSetting->toMap());
        Q_EMIT clonedMacAddressChanged();
    } else {
        qWarning("NetworkManager wired settings are invalid");
    }
}

quint32 WiredSettings::mtu() const
{
    if (m_wiredSetting)
        return m_wiredSetting->mtu();
    else
        qWarning("NetworkManager wired settings are invalid");
    return 0;
}

void WiredSettings::setMtu(quint32 mtu)
{
    if (m_wiredSetting) {
        if (this->mtu() == mtu)
            return;
        m_wiredSetting->setMtu(mtu);
        updateSettings(m_wiredSetting->name(), m_wiredSetting->toMap());
        Q_EMIT mtuChanged();
    } else {
        qWarning("NetworkManager wired settings are invalid");
    }
}

Security8021xSettings *WiredSettings::securitySettings() const
{
    return m_securitySettings;
}

IPv4Settings *WiredSettings::ipv4Settings() const
{
    return m_ipv4Settings;
}

void WiredSettings::handlePathChanged()
{
    NetworkManager::ConnectionSettings::Ptr settings = m_connection->settings();
    if (settings) {
        m_wiredSetting = settings->setting(NetworkManager::Setting::Wired).dynamicCast<NetworkManager::WiredSetting>();
        m_wiredSetting->setAutoNegotiate(true);
        m_ipv4Settings->setup(settings->setting(NetworkManager::Setting::Ipv4).dynamicCast<NetworkManager::Ipv4Setting>());
        m_ipv6Setting = settings->setting(NetworkManager::Setting::Ipv6).dynamicCast<NetworkManager::Ipv6Setting>();
    } else {
        m_wiredSetting.reset();
        m_ipv4Settings->reset();
        m_ipv6Setting.reset();
    }

    Q_EMIT speedChanged();
    Q_EMIT macAddressChanged();
    Q_EMIT clonedMacAddressChanged();
    Q_EMIT mtuChanged();
}
