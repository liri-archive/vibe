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

#include "kquickwallet.h"

#include <QDebug>

#define READ_SUCCESS 0

using namespace KWallet;

KQuickWallet::KQuickWallet(QObject *parent) : QObject(parent)
{
    // Nothing needed here
    m_folder = Wallet::PasswordFolder();
    open();
}

KQuickWallet::~KQuickWallet() { delete m_wallet; }

void KQuickWallet::open()
{
    m_wallet = Wallet::openWallet(Wallet::LocalWallet(), 0, Wallet::Asynchronous);

    Q_ASSERT(m_wallet != nullptr);

    connect(m_wallet, &Wallet::walletOpened, this, &KQuickWallet::walletOpened);
}

void KQuickWallet::walletOpened(bool success)
{
    setStatus(success ? KQuickWallet::Open : KQuickWallet::Error);

    if (success) {
        if (!m_wallet->hasFolder(m_folder))
            m_wallet->createFolder(m_folder);

        m_wallet->setFolder(m_folder);
    }
}

void KQuickWallet::setFolder(QString folder)
{
    if (m_folder != folder) {
        m_folder = folder;

        if (m_wallet != nullptr) {
            if (!m_wallet->hasFolder(folder))
                m_wallet->createFolder(folder);

            m_wallet->setFolder(folder);
        }

        Q_EMIT folderChanged();
    }
}

QStringList KQuickWallet::entryList() const
{
    if (m_wallet == nullptr || !m_wallet->isOpen())
        return QStringList();

    return m_wallet->entryList();
}

QString KQuickWallet::readPassword(QString key) const
{
    if (m_wallet == nullptr || !m_wallet->isOpen())
        return QString();

    QString password;
    if (m_wallet->readPassword(key, password) != READ_SUCCESS)
        return QString();
    return password;
}

bool KQuickWallet::writePassword(QString key, QString password) const
{
    if (m_wallet == nullptr || !m_wallet->isOpen())
        return false;

    return m_wallet->writePassword(key, password);
}
