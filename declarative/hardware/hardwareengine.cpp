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

#include <QtCore/QDirIterator>

#include <Solid/DeviceNotifier>
#include <Solid/StorageAccess>

#include "hardwareengine.h"

Q_LOGGING_CATEGORY(HARDWARE, "vibe.hardware")

HardwareEngine::HardwareEngine(QObject *parent) : QObject(parent)
{
    // Populate list as devices come and go
    Solid::DeviceNotifier *notifier = Solid::DeviceNotifier::instance();
    connect(notifier, &Solid::DeviceNotifier::deviceAdded, [this](const QString &udi) {
        Solid::Device device(udi);
        if (device.as<Solid::Battery>()) {
            Battery *battery = new Battery(device.udi());
            m_batteries[device.udi()] = battery;
            Q_EMIT batteriesChanged();
            Q_EMIT batteryAdded(battery);
        } else if (device.as<Solid::StorageAccess>()) {
            StorageDevice *storageDevice = new StorageDevice(device.udi());
            m_storageDevices[device.udi()] = storageDevice;
            Q_EMIT storageDevicesChanged();
            Q_EMIT storageDeviceAdded(storageDevice);
        }
    });
    connect(notifier, &Solid::DeviceNotifier::deviceRemoved, [this](const QString &udi) {
        Battery *battery = m_batteries.value(udi, Q_NULLPTR);
        if (battery) {
            m_batteries.remove(udi);
            Q_EMIT batteriesChanged();
            Q_EMIT batteryRemoved(battery);
            battery->deleteLater();
            return;
        }

        StorageDevice *storageDevice = m_storageDevices.value(udi, Q_NULLPTR);
        if (storageDevice) {
            m_storageDevices.remove(udi);
            Q_EMIT storageDevicesChanged();
            Q_EMIT storageDeviceRemoved(storageDevice);
            storageDevice->deleteLater();
            return;
        }
    });

    // Add already existing devices
    qCDebug(HARDWARE) << "Populate initial devices list";
    for (const Solid::Device &device : Solid::Device::allDevices()) {
        if (device.as<Solid::Battery>()) {
            Battery *battery = new Battery(device.udi());
            m_batteries[device.udi()] = battery;
            Q_EMIT batteriesChanged();
            Q_EMIT batteryAdded(battery);
        } else if (device.as<Solid::StorageAccess>()) {
            StorageDevice *storageDevice = new StorageDevice(device.udi());
            m_storageDevices[device.udi()] = storageDevice;
            Q_EMIT storageDevicesChanged();
            Q_EMIT storageDeviceAdded(storageDevice);
        }
    }

    // Add backlight devices
    QDirIterator it(QLatin1String("/sys/class/backlight"));
    while (it.hasNext()) {
        bool ok = false;

        // Must be able to open the file, otherwise skip the device altogether
        QString deviceFile = it.next() + QLatin1String("/brightness");
        QFile file(deviceFile);
        if (!file.open(QIODevice::ReadOnly))
            continue;
        ok = false;
        uint value = file.readAll().simplified().toUInt(&ok);
        if (!ok)
            continue;

        // Must be able to read max brightness, otherwise skip the device altogether
        QFile maxBrightnessFile(it.filePath() + QLatin1String("/max_brightness"));
        if (!maxBrightnessFile.open(QIODevice::ReadOnly))
            continue;

        // Read max brightness
        ok = false;
        uint maxBrightness = maxBrightnessFile.readAll().simplified().toUInt(&ok);
        if (!ok || maxBrightness == 0)
            continue;

        // Scale value to max brightness
        value = value == maxBrightness ? 255 : (value * 256) / (maxBrightness + 1);

        // Create the device
        BacklightDevice *device = new BacklightDevice(it.fileName(), value, maxBrightness);
        m_backlightDevices[device->name()] = device;
    }
}

HardwareEngine::~HardwareEngine()
{
    qDeleteAll(m_backlightDevices);
    m_backlightDevices.clear();

    qDeleteAll(m_storageDevices);
    m_storageDevices.clear();
}

Battery *HardwareEngine::primaryBattery() const
{
    Q_FOREACH (Battery *battery, m_batteries) {
        if (battery->type() == Battery::PrimaryBattery)
            return battery;
    }

    return nullptr;
}

QQmlListProperty<BacklightDevice> HardwareEngine::backlightDevices()
{
    auto countFunc = [](QQmlListProperty<BacklightDevice> *prop) {
        return static_cast<HardwareEngine *>(prop->object)->m_backlightDevices.count();
    };
    auto atFunc = [](QQmlListProperty<BacklightDevice> *prop, int index) {
        return static_cast<HardwareEngine *>(prop->object)->m_backlightDevices.values().at(index);
    };
    return QQmlListProperty<BacklightDevice>(this, 0, countFunc, atFunc);
}

QQmlListProperty<Battery> HardwareEngine::batteries()
{
    auto countFunc = [](QQmlListProperty<Battery> *prop) {
        return static_cast<HardwareEngine *>(prop->object)->m_batteries.count();
    };
    auto atFunc = [](QQmlListProperty<Battery> *prop, int index) {
        return static_cast<HardwareEngine *>(prop->object)->m_batteries.values().at(index);
    };
    return QQmlListProperty<Battery>(this, 0, countFunc, atFunc);
}

QQmlListProperty<StorageDevice> HardwareEngine::storageDevices()
{
    auto countFunc = [](QQmlListProperty<StorageDevice> *prop) {
        return static_cast<HardwareEngine *>(prop->object)->m_storageDevices.count();
    };
    auto atFunc = [](QQmlListProperty<StorageDevice> *prop, int index) {
        return static_cast<HardwareEngine *>(prop->object)->m_storageDevices.values().at(index);
    };
    return QQmlListProperty<StorageDevice>(this, 0, countFunc, atFunc);
}

#include "moc_hardwareengine.cpp"
