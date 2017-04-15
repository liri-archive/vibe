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

#include "ipv4settings.h"

IPv4Settings::IPv4Settings(QObject *parent)
    : QObject(parent)
{
}

bool IPv4Settings::isEnabled() const
{
    return true;
}

void IPv4Settings::setEnabled(bool value)
{
    Q_UNUSED(value);
    Q_EMIT enabledChanged();
}

void IPv4Settings::setup(NetworkManager::Ipv4Setting::Ptr setting)
{
    m_setting = setting;
    Q_EMIT enabledChanged();
}

void IPv4Settings::reset()
{
    m_setting.reset();
    Q_EMIT enabledChanged();
}
