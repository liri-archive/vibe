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

#include "connectionmodel.h"
#include "networkmodel.h"
#include "uiutils.h"

ConnectionModel::ConnectionModel(QObject *parent)
    : QIdentityProxyModel(parent)
{
    NetworkModel *networkModel = new NetworkModel(this);
    setSourceModel(networkModel);
}

QHash<int, QByteArray> ConnectionModel::roleNames() const
{
    QHash<int, QByteArray> roles = QIdentityProxyModel::roleNames();

    roles[IconNameRole] = QByteArrayLiteral("iconName");
    roles[SymbolicIconNameRole] = QByteArrayLiteral("symbolicIconName");

    return roles;
}

QVariant ConnectionModel::data(const QModelIndex &index, int role) const
{
    const QModelIndex sourceIndex = sourceModel()->index(index.row(), 0);

    const NetworkManager::ConnectionSettings::ConnectionType type =
            static_cast<NetworkManager::ConnectionSettings::ConnectionType>(sourceModel()->data(sourceIndex, NetworkModel::TypeRole).toInt());

    QString tooltip;
    const QString iconName = UiUtils::iconAndTitleForConnectionSettingsType(type, tooltip);

    switch (role) {
    case IconNameRole:
        return iconName;
    case SymbolicIconNameRole:
        if (iconName.startsWith(QLatin1String("network-wired")))
            return QLatin1String("action/settings_ethernet");
        else if (iconName == QLatin1String("network-wireless-100-locked"))
            return QLatin1String("device/signal_wifi_4_bar_lock");
        else if (iconName == QLatin1String("network-wireless-80-locked"))
            return QLatin1String("device/signal_wifi_3_bar_lock");
        else if (iconName == QLatin1String("network-wireless-60-locked"))
            return QLatin1String("device/signal_wifi_2_bar_lock");
        else if (iconName == QLatin1String("network-wireless-40-locked"))
            return QLatin1String("device/signal_wifi_2_bar_lock");
        else if (iconName == QLatin1String("network-wireless-20-locked"))
            return QLatin1String("device/signal_wifi_1_bar_lock");
        else if (iconName == QLatin1String("network-wireless-0-locked"))
            return QLatin1String("device/signal_wifi_0_bar_lock");
        else if (iconName == QLatin1String("network-wireless-connected-100"))
            return QLatin1String("device/signal_wifi_4_bar");
        else if (iconName == QLatin1String("network-wireless-connected-80"))
            return QLatin1String("device/signal_wifi_3_bar");
        else if (iconName == QLatin1String("network-wireless-connected-60"))
            return QLatin1String("device/signal_wifi_2_bar");
        else if (iconName == QLatin1String("network-wireless-connected-40"))
            return QLatin1String("device/signal_wifi_2_bar");
        else if (iconName == QLatin1String("network-wireless-connected-20"))
            return QLatin1String("device/signal_wifi_1_bar");
        else if (iconName == QLatin1String("network-wireless-connected-0"))
            return QLatin1String("device/signal_wifi_0_bar");
        else if (iconName == QLatin1String("network-wireless-100"))
            return QLatin1String("device/signal_wifi_4_bar");
        else if (iconName == QLatin1String("network-wireless-60"))
            return QLatin1String("device/signal_wifi_2_bar");
        else if (iconName == QLatin1String("network-wireless-40"))
            return QLatin1String("device/signal_wifi_2_bar");
        else if (iconName == QLatin1String("network-wireless-80"))
            return QLatin1String("device/signal_wifi_3_bar");
        else if (iconName == QLatin1String("network-wireless-20"))
            return QLatin1String("device/signal_wifi_1_bar");
        else if (iconName == QLatin1String("network-wireless-0"))
            return QLatin1String("device/signal_wifi_0_bar");
        else if (iconName == QLatin1String("network-vpn"))
            return QLatin1String("communication/vpn_key");
        else if (iconName == QLatin1String("secure-card"))
            return QLatin1String("communication/vpn_key");
        else if (iconName == QLatin1String("network-bluetooth"))
            return QLatin1String("device/bluetooth");
        return QLatin1String("device/signal_wifi_0_bar");
    default:
        break;
    }

    return sourceModel()->data(index, role);
}

int ConnectionModel::columnCount(const QModelIndex &parentIndex) const
{
    Q_UNUSED(parentIndex);
    return 3;
}
