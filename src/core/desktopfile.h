/*
 * This file is part of Hawaii.
 *
 * Copyright (C) 2014 Bogdan Cuza <bogdan.cuza@hotmail.com>
 * Copyright (C) 2015-2016 Michael Spencer <sonrisesoftware@gmail.com>
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
 */

#pragma once

#include <QtCore/QObject>

#include <Hawaii/core/hawaii_core_export.h>
#include <qt5xdg/xdgdesktopfile.h>

#include "desktopfileaction.h"

namespace Hawaii
{

class HAWAIICORE_EXPORT DesktopFile : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY dataChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY dataChanged)
    Q_PROPERTY(QString genericName READ genericName NOTIFY dataChanged)
    Q_PROPERTY(bool hasIcon READ hasIcon NOTIFY dataChanged)
    Q_PROPERTY(QString comment READ comment NOTIFY dataChanged)
    Q_PROPERTY(QList<DesktopFileAction *> actions READ actions NOTIFY dataChanged)
    Q_PROPERTY(bool noDisplay READ noDisplay NOTIFY dataChanged)

    Q_PROPERTY(QString appId READ appId WRITE setAppId NOTIFY appIdChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)

    Q_PROPERTY(bool isValid READ isValid NOTIFY dataChanged)
    Q_PROPERTY(bool isShown READ isShown NOTIFY dataChanged)

public:
    explicit DesktopFile(QString path = "", QObject *parent = 0);

    QString name() const;
    QString genericName() const;
    QString iconName() const;
    bool hasIcon() const;
    QString comment() const;
    bool isValid() const;
    bool isShown(const QString &environment = QString()) const;
    bool noDisplay() const;

    QString appId() const { return m_appId; }
    QString path() const { return m_path; }

    QList<DesktopFileAction *> actions() const { return m_actions; }

    static QString canonicalAppId(QString appId);

public Q_SLOTS:
    void setAppId(QString appId);
    void setPath(QString path);
    void load();

Q_SIGNALS:
    void dataChanged();
    void isValidChanged();
    void pathChanged();
    void appIdChanged();

private:
    static QString pathFromAppId(QString appId);
    static QString findFileInPaths(QString fileName, QStringList paths);

    QString m_appId;
    QString m_path;
    XdgDesktopFile *m_desktopFile;
    QList<DesktopFileAction *> m_actions;
};
}
