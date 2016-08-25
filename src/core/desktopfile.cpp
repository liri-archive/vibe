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

#include "desktopfile.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QStandardPaths>
#include <qt5xdg/xdgdesktopfile.h>
#include <qt5xdg/xdgdirs.h>

using namespace Hawaii;

const QMap<QString, QString> correctAppIds = {
        {"baobob", "org.gnome.baobob"},           {"cheese", "org.gnome.Cheese"},
        {"corebird", "org.baedert.corebird"},     {"dconf-editor", "ca.desrt.dconf-editor"},
        {"file-roller", "org.gnome.FileRoller"},  {"gnome-calendar", "org.gnome.Calendar"},
        {"gnome-disks", "org.gnome.DiskUtility"}, {"gnome-font-viewer", "org.gnome.font-viewer"},
        {"nautilus", "org.gnome.Nautilus"},       {"org.kate-editor.kate", "org.kde.kate"}};

DesktopFile::DesktopFile(QString path, QObject *parent)
    : QObject(parent)
{
    if (path.endsWith(".desktop"))
        setPath(path);
    else
        setAppId(path);
}

void DesktopFile::setAppId(QString appId)
{
    appId = canonicalAppId(appId);
    setPath(appId + ".desktop");
}

QString DesktopFile::canonicalAppId(QString appId)
{
    if (appId.endsWith(".desktop"))
        appId = QFileInfo(appId).completeBaseName();

    bool notFound = pathFromAppId(appId).isEmpty();

    if (notFound && correctAppIds.contains(appId))
        return correctAppIds[appId];
    else
        return appId;
}

QString DesktopFile::pathFromAppId(QString appId)
{
    return QStandardPaths::locate(QStandardPaths::ApplicationsLocation,
                                  appId + QStringLiteral(".desktop"));
}

QString DesktopFile::findFileInPaths(QString fileName, QStringList paths)
{
    for (QString path : paths) {
        if (QFile::exists(path + "/" + fileName)) {
            return path + "/" + fileName;
        }
    }

    return QString();
}

void DesktopFile::setPath(QString path)
{
    m_path = path;

    // Extracts "papyros-files" from "/path/to/papyros-files.desktop"
    m_appId = QFileInfo(path).completeBaseName();

    if (!m_path.startsWith("/"))
        m_path = pathFromAppId(m_appId);

    Q_EMIT pathChanged();
    Q_EMIT appIdChanged();

    load();
}

void DesktopFile::load()
{
    m_desktopFile = XdgDesktopFileCache::getFile(m_path);

    qDeleteAll(m_actions);
    m_actions.clear();

    QStringList actionNames =
            m_desktopFile->value("Actions").toString().split(';', QString::SkipEmptyParts);

    Q_FOREACH (QString actionName, actionNames) {
        const QString group = QStringLiteral("Desktop Action %1").arg(actionName);

        const QString name =
                m_desktopFile->localizedValue(QStringLiteral("%1/Name").arg(group)).toString();
        const QString iconName =
                m_desktopFile->localizedValue(QStringLiteral("%1/IconName").arg(group)).toString();
        const QString exec =
                m_desktopFile->localizedValue(QStringLiteral("%1/Exec").arg(group)).toString();

        // Name is required. Spec says to skip entries without it
        if (name.isEmpty())
            continue;

        m_actions << new DesktopFileAction(name, iconName, exec, this);
    }

    Q_EMIT dataChanged();
}

QString DesktopFile::name() const { return m_desktopFile ? m_desktopFile->name() : QString(); }

QString DesktopFile::genericName() const
{
    return m_desktopFile ? m_desktopFile->localizedValue("GenericName").toString() : QString();
}

QString DesktopFile::iconName() const
{
    return m_desktopFile ? m_desktopFile->iconName() : QString();
}

bool DesktopFile::hasIcon() const { return !QIcon::fromTheme(iconName()).isNull(); }

QString DesktopFile::comment() const { return m_desktopFile ? m_desktopFile->comment() : ""; }

bool DesktopFile::isValid() const { return m_desktopFile ? m_desktopFile->isValid() : false; }

bool DesktopFile::isShown(const QString &environment) const
{
    return m_desktopFile ? m_desktopFile->isShown(environment) : false;
}

bool DesktopFile::noDisplay() const
{
    return m_desktopFile ? m_desktopFile->value("NoDisplay").toBool() : true;
}
