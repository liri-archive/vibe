/****************************************************************************
 * This file is part of libhawaii.
 *
 * Copyright (C) 2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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

#include <QtCore/QDebug>

#include <Hawaii/DataProvider>
#include <Hawaii/DataProviderManager>

#include "qmldataprovider.h"

using namespace Hawaii;

/*
 * QmlDataProviderPrivate
 */

class QmlDataProviderPrivate
{
public:
    QmlDataProviderPrivate(QmlDataProvider *self)
        : provider(nullptr)
        , data(nullptr)
        , q_ptr(self)
    {
        data = new QQmlPropertyMap();
    }

    ~QmlDataProviderPrivate()
    {
        delete data;
    }

    void loadProvider()
    {
        Q_Q(QmlDataProvider);

        if (providerName.isEmpty())
            return;

        DataProvider *newProvider = DataProviderManager::instance()->provider(providerName);
        if (!newProvider->isValid()) {
            qWarning() << "Data provider" << providerName << "is not valid";
            return;
        }

        if (provider != newProvider) {
            // Data provider was changed: disconnect all signals and decrease
            // refcount if we previously had another provider loaded
            if (provider) {
                provider->disconnect(q);
                DataProviderManager::instance()->unloadProvider(oldProviderName);
            }

            // Switch to the new data provider and connect its signals
            provider = newProvider;
            QObject::connect(provider, SIGNAL(sourceAdded(QString)),
                             q, SIGNAL(sourcesChanged()),
                             Qt::QueuedConnection);
            QObject::connect(provider, SIGNAL(sourceAdded(QString)),
                             q, SIGNAL(sourceAdded(QString)),
                             Qt::QueuedConnection);
            QObject::connect(provider, SIGNAL(sourceRemoved(QString)),
                             q, SIGNAL(sourcesChanged()));
            QObject::connect(provider, SIGNAL(sourceRemoved(QString)),
                             q, SIGNAL(sourceRemoved(QString)));
            QObject::connect(provider, SIGNAL(sourceRemoved(QString)),
                             q, SLOT(_q_sourceRemoved(QString)));
        }

        // Connect all sources we care about
        for (QString sourceName: connectedSources) {
            QObject::connect(provider, SIGNAL(sourceChanged(QString,DataSource::Data)),
                             q, SLOT(_q_sourceChanged(QString,DataSource::Data)));
            Q_EMIT q->sourceConnected(sourceName);
        }
    }

    void _q_sourceChanged(const QString &sourceName, const DataSource::Data &sourceData)
    {
        Q_Q(QmlDataProvider);

        if (connectedSources.contains(sourceName)) {
            data->insert(sourceName, sourceData);
            Q_EMIT q->dataChanged();
            Q_EMIT q->sourceChanged(sourceName, sourceData);
        }
    }

    void _q_sourceRemoved(const QString &sourceName)
    {
        Q_Q(QmlDataProvider);

        // Remove data for this source
        data->clear(sourceName);

        // Disconnect this source
        if (connectedSources.contains(sourceName)) {
            connectedSources.removeAll(sourceName);
            Q_EMIT q->sourceDisconnected(sourceName);
            Q_EMIT q->connectedSourcesChanged();
        }
    }

    QString oldProviderName;
    QString providerName;
    Hawaii::DataProvider *provider;
    QQmlPropertyMap *data;
    QStringList connectedSources;

protected:
    Q_DECLARE_PUBLIC(QmlDataProvider)
    QmlDataProvider *q_ptr;
};

/*
 * QmlDataProvider
 */

QmlDataProvider::QmlDataProvider(QObject *parent)
    : QObject(parent)
    , d_ptr(new QmlDataProviderPrivate(this))
{
}

QmlDataProvider::~QmlDataProvider()
{
    delete d_ptr;
}

bool QmlDataProvider::isValid() const
{
    Q_D(const QmlDataProvider);
    return d->provider && d->provider->isValid();
}

QString QmlDataProvider::provider() const
{
    Q_D(const QmlDataProvider);
    return d->providerName;
}

void QmlDataProvider::setProvider(const QString &name)
{
    Q_D(QmlDataProvider);

    if (name != d->providerName) {
        d->oldProviderName = d->providerName;
        d->providerName = name;
        d->loadProvider();
        Q_EMIT providerChanged();
    }
}

QStringList QmlDataProvider::sources() const
{
    Q_D(const QmlDataProvider);
    return d->provider && d->provider->isValid() ? d->provider->sources() : QStringList();
}

QStringList QmlDataProvider::connectedSources() const
{
    Q_D(const QmlDataProvider);
    return d->connectedSources;
}

void QmlDataProvider::setConnectedSources(const QStringList &value)
{
    Q_D(QmlDataProvider);

    bool isChanged = d->connectedSources != value;

    if (d->provider) {
        // Disconnect sources not in the new list and remove their data
        for (QString sourceName: d->connectedSources) {
            if (!value.contains(sourceName)) {
                d->connectedSources.removeAll(sourceName);
                d->data->clear(sourceName);
                d->provider->disconnect(this);
                Q_EMIT sourceDisconnected(sourceName);
            }
        }

        // Connect sources that were never connected before
        for (QString sourceName: value) {
            if (!d->connectedSources.contains(sourceName)) {
                d->connectedSources.append(sourceName);
                connect(d->provider, SIGNAL(sourceChanged(QString,DataSource::Data)),
                        this, SLOT(_q_sourceChanged(QString,DataSource::Data)));
                Q_EMIT sourceConnected(sourceName);
            }
        }
    }

    if (isChanged)
        Q_EMIT connectedSourcesChanged();
}

QQmlPropertyMap *QmlDataProvider::data() const
{
    Q_D(const QmlDataProvider);
    return d->data;
}

#include "moc_qmldataprovider.cpp"
