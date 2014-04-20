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

#include <QtCore/QAtomicInt>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QHash>
#include <QtCore/QPluginLoader>
#include <QtCore/QJsonObject>

#include "dataprovider.h"
#include "dataprovider_p.h"
#include "dataprovidermanager.h"

namespace Hawaii {

Q_GLOBAL_STATIC(DataProviderManager, s_dataEngineManager)

/*
 * DataProviderManagerPrivate
 */

class DataProviderManagerPrivate
{
public:
    DataProviderManagerPrivate()
    {
    }

    QHash<QString, DataProvider *> providers;
};

/*
 * DataProviderManager
 */

DataProviderManager::DataProviderManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DataProviderManagerPrivate())
{
}

DataProviderManager::~DataProviderManager()
{
    delete d_ptr;
}

DataProviderManager *DataProviderManager::instance()
{
    return s_dataEngineManager();
}

DataProvider *DataProviderManager::loadProvider(const QString &name)
{
    Q_D(DataProviderManager);


    // Increase refcount and return the provider if it was previously registered
    if (d->providers.contains(name)) {
        DataProvider *provider = d->providers.value(name);
        provider->d_ptr->refCount.ref();
        return provider;
    }

    // Load the provider
    for (const QString &path: QCoreApplication::instance()->libraryPaths()) {
        // We only want plugin paths
        if (!path.endsWith(QStringLiteral("plugins")))
            continue;

        QDir pluginDir(path);
        pluginDir.cd(QStringLiteral("dataproviders"));

        for (const QString &fileName: pluginDir.entryList(QDir::Files)) {
            // Load the plugin
            const QString path = pluginDir.absoluteFilePath(fileName);
            QPluginLoader loader(path);

            // Check the interface name
            const QString iid = loader.metaData().value(QStringLiteral("IID")).toString();
            if (iid.isEmpty()) {
                qWarning("Invalid data provider plugin \"%s\": no metadata",
                       qPrintable(path));
                continue;
            }

            // Is this the plugin we are looking for?
            if (iid != name)
                continue;

            // Create a new instance and save it
            qDebug() << "-> Loading" << name << "data provider";
            QObject *plugin = loader.instance();
            DataProvider *provider = qobject_cast<DataProvider *>(plugin);
            if (provider) {
                provider->setParent(this);
                provider->d_ptr->refCount.ref();
                provider->d_ptr->valid = true;
                d->providers[name] = provider;
                return provider;
            } else {
                qDebug() << "  FAILED";
                delete plugin;
            }
        }
    }

    // Return an invalid provider
    DataProvider *provider = new DataProvider(this);
    d->providers[name] = provider;
    return provider;
}

void DataProviderManager::unloadProvider(const QString &name)
{
    Q_D(DataProviderManager);

    // Decrease reference count if we find the provider, and destroy
    // it when the nobody is using it anymore
    if (d->providers.contains(name)) {
        DataProvider *provider = d->providers.value(name);
        if (!provider->d_ptr->refCount.deref()) {
            d->providers.remove(name);
            delete provider;
        }
    }
}

DataProvider *DataProviderManager::provider(const QString &name)
{
    Q_D(DataProviderManager);

    // Just return it if we have found a match
    if (d->providers.contains(name))
        return d->providers.value(name);

    return loadProvider(name);
}

} // namespace Hawaii

#include "moc_dataprovidermanager.cpp"
