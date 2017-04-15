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

#include <QtQml/QtQml>

#include "availabledevices.h"
#include "appletproxymodel.h"
#include "connectionicon.h"
#include "connectionmodel.h"
#include "enabledconnections.h"
#include "enums.h"
#include "handler.h"
#include "networkmodel.h"
#include "networkstatus.h"
#include "technologyproxymodel.h"
#include "wiredsettings.h"

class NetworkManagerPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    void registerTypes(const char *uri)
    {
        // @uri Vibe.NetworkManager
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Vibe.NetworkManager"));

        qmlRegisterType<AvailableDevices>(uri, 1, 0, "AvailableDevices");
        qmlRegisterType<ConnectionIcon>(uri, 1, 0, "ConnectionIcon");
        qmlRegisterType<ConnectionModel>(uri, 1, 0, "ConnectionModel");
        qmlRegisterType<EnabledConnections>(uri, 1, 0, "EnabledConnections");
        qmlRegisterUncreatableType<Enums>(uri, 1, 0, "Enums",
                                          QLatin1String("Cannot instantiate Enums"));
        qmlRegisterType<NetworkStatus>(uri, 1, 0, "NetworkStatus");
        qmlRegisterType<Handler>(uri, 1, 0, "Handler");
        qmlRegisterType<NetworkModel>(uri, 1, 0, "NetworkModel");
        qmlRegisterType<AppletProxyModel>(uri, 1, 0, "AppletProxyModel");
        qmlRegisterType<TechnologyProxyModel>(uri, 1, 0, "TechnologyProxyModel");

        // Settings
        qmlRegisterUncreatableType<Security8021xSettings>(uri, 1, 0, "Security8021xSettings", tr("Cannot instantiate Security8021xSettings"));
        qmlRegisterUncreatableType<IPv4Settings>(uri, 1, 0, "IPv4Settings", tr("Cannot instantiate IPv4Settings"));
        qmlRegisterType<WiredSettings>(uri, 1, 0, "WiredSettings");
    }
};

#include "plugin.moc"
