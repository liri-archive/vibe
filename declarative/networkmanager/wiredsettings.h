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

#include <NetworkManagerQt/WiredSetting>
#include <NetworkManagerQt/Ipv6Setting>

#include "connectionsettings.h"
#include "security8021xsettings.h"
#include "ipv4settings.h"

class WiredSettings : public ConnectionSettings
{
    Q_OBJECT
    Q_PROPERTY(quint32 speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(QString macAddress READ macAddress WRITE setMacAddress NOTIFY macAddressChanged)
    Q_PROPERTY(QString clonedMacAddress READ clonedMacAddress WRITE setClonedMacAddress NOTIFY clonedMacAddressChanged)
    Q_PROPERTY(quint32 mtu READ mtu WRITE setMtu NOTIFY mtuChanged)
    Q_PROPERTY(Security8021xSettings *security READ securitySettings)
    Q_PROPERTY(IPv4Settings *ipv4 READ ipv4Settings)
public:
    WiredSettings(QObject *parent = nullptr);

    quint32 speed() const;
    void setSpeed(quint32 speed);

    QString macAddress() const;
    void setMacAddress(const QString &macAddress);

    QString clonedMacAddress() const;
    void setClonedMacAddress(const QString &clonedMacAddress);

    quint32 mtu() const;
    void setMtu(quint32 mtu);

    Security8021xSettings *securitySettings() const;
    IPv4Settings *ipv4Settings() const;

Q_SIGNALS:
    void speedChanged();
    void macAddressChanged();
    void clonedMacAddressChanged();
    void mtuChanged();

protected:
    void handlePathChanged() override;

private:
    NetworkManager::WiredSetting::Ptr m_wiredSetting;
    NetworkManager::Ipv6Setting::Ptr m_ipv6Setting;
    Security8021xSettings *m_securitySettings;
    IPv4Settings *m_ipv4Settings;
};
