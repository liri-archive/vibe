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

#include <QtCore/QObject>

#include <NetworkManagerQt/Connection>

class ConnectionSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool autoConnect READ autoConnect WRITE setAutoConnect NOTIFY autoConnectChanged)
    Q_PROPERTY(bool availableToOtherUsers READ availableToOtherUsers WRITE setAvailableToOtherUsers NOTIFY availableToOtherUsersChanged)
public:
    ConnectionSettings(QObject *parent = nullptr);

    QString path() const;
    void setPath(const QString &path);

    QString name() const;
    void setName(const QString &name);

    bool autoConnect() const;
    void setAutoConnect(bool value);

    bool availableToOtherUsers() const;
    void setAvailableToOtherUsers(bool value);

Q_SIGNALS:
    void pathChanged();
    void settingsAvailable();
    void nameChanged();
    void autoConnectChanged();
    void availableToOtherUsersChanged();

protected:
    NetworkManager::Connection::Ptr m_connection;
    NetworkManager::ConnectionSettings::Ptr m_settings;

    virtual void handlePathChanged() = 0;

    void updateSettings(const QString &type, const QVariantMap &map);

private:
    QString m_path;

    QString getCurrentUserName() const;
};
