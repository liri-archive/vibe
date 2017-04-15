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

#include <NetworkManagerQt/Ipv4Setting>

class IPv4Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
public:
    enum ConfigMethod {
        AutomaticConfig = 0,
        LinkLocalConfig,
        ManualConfig,
        SharedConfig
    };
    Q_ENUM(ConfigMethod)

    IPv4Settings(QObject *parent = nullptr);

    bool isEnabled() const;
    void setEnabled(bool value);

    void setup(NetworkManager::Ipv4Setting::Ptr setting);
    void reset();

Q_SIGNALS:
    void enabledChanged();

private:
    NetworkManager::Ipv4Setting::Ptr m_setting;
};
