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

#ifndef QMLDATAPROVIDER_H
#define QMLDATAPROVIDER_H

#include <QtCore/QObject>
#include <QtQml/QQmlPropertyMap>

#include <Hawaii/DataSource>

class QmlDataProviderPrivate;

class QmlDataProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool valid READ isValid)
    Q_PROPERTY(QString provider READ provider WRITE setProvider NOTIFY providerChanged)
    Q_PROPERTY(QStringList sources READ sources NOTIFY sourcesChanged)
    Q_PROPERTY(QStringList connectedSources READ connectedSources WRITE setConnectedSources NOTIFY connectedSourcesChanged)
    Q_PROPERTY(QQmlPropertyMap *data READ data NOTIFY dataChanged)
public:
    explicit QmlDataProvider(QObject *parent = 0);
    ~QmlDataProvider();

    bool isValid() const;

    QString provider() const;
    void setProvider(const QString &name);

    QStringList sources() const;

    QStringList connectedSources() const;
    void setConnectedSources(const QStringList &value);

    QQmlPropertyMap *data() const;

Q_SIGNALS:
    void providerChanged();
    void sourcesChanged();
    void connectedSourcesChanged();
    void dataChanged();

    void sourceAdded(const QString &name);
    void sourceChanged(const QString &name, const Hawaii::DataSource::Data &data);
    void sourceRemoved(const QString &name);

    void sourceConnected(const QString &name);
    void sourceDisconnected(const QString &name);

private:
    Q_DECLARE_PRIVATE(QmlDataProvider)
    QmlDataProviderPrivate *const d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_sourceChanged(const QString &sourceName, const DataSource::Data &sourceData))
    Q_PRIVATE_SLOT(d_func(), void _q_sourceRemoved(const QString &sourceName))
};

#endif // QMLDATAPROVIDER_H
