/*
 * This file is part of Vibe.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
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

#include <Vibe/core/vibe_core_export.h>

namespace Vibe
{

class VIBECORE_EXPORT DesktopFileAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString iconName READ iconName CONSTANT)
    Q_PROPERTY(QString command READ command CONSTANT)

public:
    DesktopFileAction(const QString &name, const QString &iconName, const QString &command,
                      QObject *parent = nullptr);

    /*!
     * \brief Action name.
     *
     * Returns the action name.
     */
    QString name() const { return m_name; }

    /*!
     * \brief Icon name.
     *
     * Returns the icon name.
     */
    QString iconName() const { return m_iconName; }

    /*!
     * \brief Action command.
     *
     * Returns the command to execute this action.
     */
    QString command() const { return m_command; }

private:
    QString m_name;
    QString m_iconName;
    QString m_command;
};
}
