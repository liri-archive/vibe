/****************************************************************************
* This file is part of Vibe.
 *
 * Copyright (C) 2015-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef HARDWAREENGINE_H
#define HARDWAREENGINE_H

#include <QtCore/QLoggingCategory>
#include <QtCore/QObject>
#include <QtQml/QQmlListProperty>

#include "battery.h"
#include "backlightdevice.h"
#include "storagedevice.h"

Q_DECLARE_LOGGING_CATEGORY(HARDWARE)

class HardwareEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Battery *primaryBattery READ primaryBattery NOTIFY batteriesChanged)
    Q_PROPERTY(QQmlListProperty<BacklightDevice> backlightDevices READ backlightDevices NOTIFY backlightDevicesChanged)
    Q_PROPERTY(QQmlListProperty<Battery> batteries READ batteries NOTIFY batteriesChanged)
    Q_PROPERTY(QQmlListProperty<StorageDevice> storageDevices READ storageDevices NOTIFY
                       storageDevicesChanged)
public:
    HardwareEngine(QObject *parent = 0);
    ~HardwareEngine();

    Battery *primaryBattery() const;
    QQmlListProperty<BacklightDevice> backlightDevices();
    QQmlListProperty<Battery> batteries();
    QQmlListProperty<StorageDevice> storageDevices();

Q_SIGNALS:
    void backlightDeviceAdded(BacklightDevice *device);
    void backlightDeviceRemoved(BacklightDevice *device);
    void backlightDevicesChanged();

    void storageDeviceAdded(StorageDevice *device);
    void storageDeviceRemoved(StorageDevice *device);
    void storageDevicesChanged();

    void batteryAdded(Battery *battery);
    void batteryRemoved(Battery *battery);
    void batteriesChanged();

private:
    QMap<QString, BacklightDevice *> m_backlightDevices;
    QMap<QString, Battery *> m_batteries;
    QMap<QString, StorageDevice *> m_storageDevices;
};

#endif // HARDWAREENGINE_H
