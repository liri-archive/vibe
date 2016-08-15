/*
 * This file is part of Hawaii.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

namespace Hawaii {

class NotificationPrivate;

class HAWAIICORE_EXPORT Notification : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Notification)
    Q_PROPERTY(QString applicationName READ applicationName WRITE setApplicationName NOTIFY applicationNameChanged)
    Q_PROPERTY(QString applicationIcon READ applicationIcon WRITE setApplicationIcon NOTIFY applicationIconChanged)
    Q_PROPERTY(QString summary READ summary WRITE setSummary NOTIFY summaryChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(quint32 replacesId READ replacesId WRITE setReplacesId NOTIFY replacesIdChanged)
    Q_PROPERTY(Urgency urgency READ urgency WRITE setUrgency NOTIFY urgencyChanged)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)
public:
    enum Urgency {
        UrgencyLow = 0,
        UrgencyNormal = 1,
        UrgencyCritical = 2
    };
    Q_ENUM(Urgency)

    enum CloseReason {
        Expired = 1,
        DismissedByUser = 2,
        Closed = 3
    };
    Q_ENUM(CloseReason)

    explicit Notification(QObject *parent = nullptr);

    QString applicationName() const;
    void setApplicationName(const QString &name);

    QString applicationIcon() const;
    void setApplicationIcon(const QString &icon);

    QString summary() const;
    void setSummary(const QString &summary);

    QString body() const;
    void setBody(const QString &body);

    quint32 replacesId() const;
    void setReplacesId(quint32 id);

    Urgency urgency() const;
    void setUrgency(Urgency urgency);

    int timeout() const;
    void setTimeout(int timeout);

    QVariantMap hints() const;
    void setHint(const QString &name, const QVariant &value);
    bool removeHint(const QString &name);
    void clearHints();

    QStringList actions() const;
    void setActions(const QStringList &actions);

    QStringList getCapabilities() const;

    Q_INVOKABLE void send();
    Q_INVOKABLE void close();

Q_SIGNALS:
    void applicationNameChanged();
    void applicationIconChanged();
    void summaryChanged();
    void bodyChanged();
    void replacesIdChanged();
    void urgencyChanged();
    void timeoutChanged();
    void defaultActionChanged();
    void sendFailed();
    void sendSucceeded(uint id);
    void actionInvoked(const QString &action);
    void closed(CloseReason reason);
};

} // namespace Hawaii
