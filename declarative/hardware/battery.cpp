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

#include "battery.h"

#include <Fluid/DateUtils>

Q_LOGGING_CATEGORY(BATTERY, "vibe.hardware.battery")

using namespace Fluid;

Battery::Battery(const QString &udi, QObject *parent)
    : QObject(parent)
    , m_device(Solid::Device(udi))
{
    qCDebug(BATTERY) << "Added battery" << udi;

    m_battery = m_device.as<Solid::Battery>();
    connect(m_battery, &Solid::Battery::chargePercentChanged,
            [this](int, const QString &) { Q_EMIT chargePercentChanged(); });
    connect(m_battery, &Solid::Battery::chargePercentChanged,
            [this](int, const QString &) { Q_EMIT summaryChanged(); });
    connect(m_battery, &Solid::Battery::chargePercentChanged,
            [this](int, const QString &) { Q_EMIT chargeIconNameChanged(); });
    connect(m_battery, &Solid::Battery::capacityChanged,
            [this](int, const QString &) { Q_EMIT capacityChanged(); });
    connect(m_battery, &Solid::Battery::powerSupplyStateChanged,
            [this](bool, const QString &) { Q_EMIT powerSupplyChanged(); });
    connect(m_battery, &Solid::Battery::timeToEmptyChanged,
            [this](qlonglong, const QString &) { Q_EMIT timeToEmptyChanged(); });
    connect(m_battery, &Solid::Battery::timeToEmptyChanged,
            [this](qlonglong, const QString &) { Q_EMIT summaryChanged(); });
    connect(m_battery, &Solid::Battery::timeToFullChanged,
            [this](qlonglong, const QString &) { Q_EMIT timeToFullChanged(); });
    connect(m_battery, &Solid::Battery::timeToFullChanged,
            [this](qlonglong, const QString &) { Q_EMIT summaryChanged(); });
    connect(m_battery, &Solid::Battery::chargeStateChanged,
            [this](int, const QString &) { Q_EMIT chargeStateChanged(); });
    connect(m_battery, &Solid::Battery::chargeStateChanged,
            [this](int, const QString &) { Q_EMIT chargeIconNameChanged(); });
    connect(m_battery, &Solid::Battery::chargeStateChanged,
            [this](int, const QString &) { Q_EMIT summaryChanged(); });
    connect(m_battery, &Solid::Battery::energyChanged,
            [this](double, const QString &) { Q_EMIT energyChanged(); });
    connect(m_battery, &Solid::Battery::energyRateChanged,
            [this](double, const QString &) { Q_EMIT energyRateChanged(); });
    connect(m_battery, &Solid::Battery::voltageChanged,
            [this](double, const QString &) { Q_EMIT voltageChanged(); });
    connect(m_battery, &Solid::Battery::temperatureChanged,
            [this](double, const QString &) { Q_EMIT temperatureChanged(); });
}

Battery::~Battery()
{
    qCDebug(BATTERY) << "Removed battery" << m_device.udi();
}

QString Battery::udi() const
{
    return m_device.udi();
}

Battery::Type Battery::type() const
{
    return static_cast<Battery::Type>(m_battery->type());
}

Battery::Technology Battery::technology() const
{
    return static_cast<Battery::Technology>(m_battery->technology());
}

int Battery::chargePercent() const
{
    return m_battery->chargePercent();
}

int Battery::capacity() const
{
    return m_battery->capacity();
}

bool Battery::isRechargeable() const
{
    return m_battery->isRechargeable();
}

bool Battery::isPowerSupply() const
{
    return m_battery->isPowerSupply();
}

Battery::ChargeState Battery::chargeState() const
{
    return static_cast<Battery::ChargeState>(m_battery->chargeState());
}

qlonglong Battery::timeToEmpty() const
{
    return m_battery->timeToEmpty();
}

qlonglong Battery::timeToFull() const
{
    return m_battery->timeToFull();
}

double Battery::energy() const
{
    return m_battery->energy();
}

double Battery::energyRate() const
{
    return m_battery->energyRate();
}

double Battery::voltage() const
{
    return m_battery->voltage();
}

double Battery::temperature() const
{
    return m_battery->temperature();
}

bool Battery::isRecalled() const
{
    return m_battery->isRecalled();
}

QString Battery::recallVendor() const
{
    return m_battery->recallVendor();
}

QUrl Battery::recallUrl() const
{
    return QUrl(m_battery->recallUrl());
}

QString Battery::vendor() const
{
    return m_device.vendor();
}

QString Battery::product() const
{
    return m_device.product();
}

QString Battery::serial() const
{
    return m_battery->serial();
}

QString Battery::chargeIconName() const
{
    QString level = QLatin1String("full");

    if (chargePercent() < 25)
        level = QLatin1String("20");
    else if (chargePercent() < 35)
        level = QLatin1String("30");
    else if (chargePercent() < 55)
        level = QLatin1String("50");
    else if (chargePercent() < 65)
        level = QLatin1String("60");
    else if (chargePercent() < 85)
        level = QLatin1String("80");
    else if (chargePercent() < 95)
        level = QLatin1String("90");

    if (chargeState() == Battery::Charging || chargeState() == Battery::FullyCharged)
        return QStringLiteral("device/battery_charging_%1").arg(level);
    else
        return QStringLiteral("device/battery_%1").arg(level);
}

QString Battery::name() const
{
    if (isMouse()) {
        // TODO: Use m_battery.description() or product here()
        return product();
    } else if (type() == Battery::PrimaryBattery) {
        return QLatin1String("Battery");
    } else if (type() == Battery::MonitorBattery) {
        return QLatin1String("External Display");
    } else if (type() == Battery::KeyboardBattery) {
        return QLatin1String("Keyboard");
    } else {
        // TODO: Use m_battery.description() or product here()
        return product();
    }
}

QString Battery::iconName() const
{
    if (isMouse()) {
        return QLatin1String("hardware/mouse");
    } else if (type() == Battery::PrimaryBattery) {
        return chargeIconName();
    } else if (type() == Battery::MonitorBattery) {
        return QLatin1String("hardware/desktop_windows");
    } else if (type() == Battery::KeyboardBattery) {
        return QLatin1String("hardware/keyboard");
    } else if (type() == Battery::PhoneBattery) {
        return QLatin1String("hardware/smartphone");
    } else {
        return QLatin1String("device/battery_std");
    }
}

QString Battery::summary() const
{
    QString percent = QStringLiteral("%1%").arg(chargePercent());

    if (chargeState() == Battery::Charging) {
        return QStringLiteral("%1 until full")
            .arg(formatter.formatDuration(timeToFull() * 1000, KFormat::HideSeconds));
    } else if (chargeState() == Battery::Discharging && timeToEmpty() != 0) {
        return QStringLiteral("%1 remaining")
            .arg(formatter.formatDuration(timeToEmpty() * 1000, KFormat::HideSeconds));
    } else if (chargeState() == Battery::FullyCharged) {
        return QLatin1String("Fully Charged");
    } else {
        return percent;
    }
}

bool Battery::isMouse() const
{
    return type() == Battery::MouseBattery || type() == Battery::KeyboardMouseBattery
        || m_device.description().toLower().indexOf(QLatin1String("mouse")) != -1
        || product().toLower().indexOf(QLatin1String("mouse")) != -1;
}
