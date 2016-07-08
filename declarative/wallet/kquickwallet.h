/*
 * libhawaii - A QML module and collection of classes used throughout Hawaii
 *
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QObject>
#include <KWallet/KWallet>

class KQuickWallet : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)
    Q_PROPERTY(WalletStatus status READ status NOTIFY statusChanged)
    Q_PROPERTY(bool enabled READ isEnabled CONSTANT)

    Q_ENUMS(WalletStatus)

public:
    enum WalletStatus
    {
        Open,
        Closed,
        Error
    };

    KQuickWallet(QObject *parent = nullptr);
    ~KQuickWallet();

    QString folder() const { return m_folder; }
    WalletStatus status() const { return m_status; }
    bool isEnabled() const { return KWallet::Wallet::isEnabled(); }

    Q_INVOKABLE QStringList entryList() const;
    Q_INVOKABLE QString readPassword(QString key) const;
    Q_INVOKABLE bool writePassword(QString key, QString password) const;

public Q_SLOTS:
    void setFolder(QString folder);

Q_SIGNALS:
    void folderChanged();
    void statusChanged(WalletStatus status);

private Q_SLOTS:
    void walletOpened(bool success);

private:
    void open();

    void setStatus(WalletStatus status)
    {
        if (status != m_status) {
            m_status = status;
            Q_EMIT statusChanged(status);
        }
    }

    QString m_folder;
    KWallet::Wallet *m_wallet = nullptr;
    WalletStatus m_status = Closed;
};
