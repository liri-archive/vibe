/****************************************************************************
* This file is part of Vibe.
 *
 * Copyright (C) 2017 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtMath>

#include "backlightdevice.h"

BacklightDevice::BacklightDevice(const QString &name, quint8 value, uint maxValue, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_value(value)
    , m_maxValue(maxValue)
{
}

QString BacklightDevice::name() const
{
    return m_name;
}

int BacklightDevice::value() const
{
    return m_value;
}

void BacklightDevice::setValue(int value)
{
    if (m_value == value)
        return;

    // Restrict value to 0:255
    quint8 actualValue = qBound(0, value, 255);

    // TODO: gain privilege to change the value

    m_value = actualValue;
    Q_EMIT valueChanged();
}

uint BacklightDevice::maxValue() const
{
    return m_maxValue;
}
