/*
 * This file is part of Vibe.
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

#include <QtDBus/QDBusInterface>
#include <QtGui/QGuiApplication>

#include "notification.h"
#include "notification_p.h"
#include "notificationsinterface.h"

const QString serviceName = QLatin1String("org.freedesktop.Notifications");
const QString path = QLatin1String("/org/freedesktop/Notifications");

namespace Vibe {

NotificationPrivate::NotificationPrivate()
    : iface(nullptr)
    , replacesId(0)
    , timeout(-1)
{
}

/*!
 * \qmltype Notification
 * \inqmlmodule Vibe.Notifications
 * \preliminary
 * \brief An object that represents a single notification of an application.
 *
 * Notification can be used to send notifications from an application
 * according to the Desktop Notifications Specification.
 *
 * The latest version of the Desktop Notifications Specification can be
 * obtained \l{http://developer.gnome.org/notification-spec}(here).
 *
 * \code
 * Button {
 *     Notification {
 *         id: notification
 *         summary: qsTr("Message sent")
 *         body: qsTr("Email message to Joe sent.")
 *         onActionInvoked: console.log("Clicked:", action)
 *         onClosed: console.log("Closed for", reason)
 *     }
 *
 *     text: qsTr("Send Email")
 *     onClicked: notification.send()
 * }
 * \endcode
 */

/*!
 * \class Notification
 * \inmodule VibeCore
 * \preliminary
 * \brief An object that represents a single notification of an application.
 *
 * Notification can be used to send notifications from an application
 * according to the Desktop Notifications Specification.
 *
 * The latest version of the Desktop Notifications Specification can be
 * obtained \l{http://developer.gnome.org/notification-spec}(here).
 */

/*!
 * Constructs a Notification with the given \a parent.
 */
Notification::Notification(QObject *parent)
    : QObject(*new NotificationPrivate(), parent)
{
    Q_D(Notification);

    // Initialize with values from the application
    if (!QGuiApplication::applicationName().isEmpty())
        d->appName = QGuiApplication::applicationName();
    if (!QGuiApplication::desktopFileName().isEmpty())
        d->hints.insert(QLatin1String("desktop-entry"), QGuiApplication::desktopFileName());

    // D-Bus interface
    d->iface = new OrgFreedesktopNotificationsInterface(
                serviceName, path,
                QDBusConnection::sessionBus(),
                this);
    connect(d->iface, &OrgFreedesktopNotificationsInterface::ActionInvoked, this, [this, d](uint id, const QString &action) {
        if (d->replacesId == id)
            Q_EMIT actionInvoked(action);
    });
    connect(d->iface, &OrgFreedesktopNotificationsInterface::NotificationClosed, this, [this, d](uint id, uint reason) {
        if (d->replacesId == id)
            Q_EMIT closed(static_cast<Notification::CloseReason>(reason));
    });
}

/*!
 * \qmlproperty object Vibe::Notifications::Notification::applicationName
 *
 * This property holds the name of the application sending the notification.
 * It's the application's formal name, rather than some sort of ID.
 * An example would be "FooBar Web Browser" rather than "org.foobar.web-browser".
 */

/*!
 * \property Notification::applicationName
 *
 * This property holds the name of the application sending the notification.
 * It's the application's formal name, rather than some sort of ID.
 * An example would be "FooBar Web Browser" rather than "org.foobar.web-browser".
 */
QString Notification::applicationName() const
{
    Q_D(const Notification);
    return d->appName;
}

void Notification::setApplicationName(const QString &name)
{
    Q_D(Notification);

    if (d->appName == name)
        return;

    d->appName = name;
    Q_EMIT applicationNameChanged();
}

/*!
 * \qmlproperty object Vibe::Notifications::Notification::applicationIcon
 *
 * This property holds the name of the application sending the notification.
 * It's the application's formal name, rather than some sort of ID.
 * An example would be "FooBar Web Browser" rather than "org.foobar.web-browser".
 */

/*!
 * \property Notification::applicationIcon
 *
 * This property holds the name of the application sending the notification.
 * It's the application's formal name, rather than some sort of ID.
 * An example would be "FooBar Web Browser" rather than "org.foobar.web-browser".
 */
QString Notification::applicationIcon() const
{
    Q_D(const Notification);
    return d->appIcon;
}

void Notification::setApplicationIcon(const QString &icon)
{
    Q_D(Notification);

    if (d->appIcon == icon)
        return;

    d->appIcon = icon;
    Q_EMIT applicationIconChanged();
}

/*!
 * \qmlproperty object Vibe::Notifications::Notification::summary
 *
 * This property holds the summary of the notification.
 * It's a single line overview of the notification, it should generally
 * not be longer than 40 characters. It must be encoded using UTF-8.
 */

/*!
 * \property Notification::summary
 *
 * This property holds the summary of the notification.
 * It's a single line overview of the notification, it should generally
 * not be longer than 40 characters. It must be encoded using UTF-8.
 */
QString Notification::summary() const
{
    Q_D(const Notification);
    return d->summary;
}

void Notification::setSummary(const QString &summary)
{
    Q_D(Notification);

    if (d->summary == summary)
        return;

    d->summary = summary;
    Q_EMIT summaryChanged();
}

/*!
 * \qmlproperty object Vibe::Notifications::Notification::body
 *
 * This property holds the body of text.
 * The body can be multi-line and contain XML-based markup that
 * consists of a small subset of HTML along with a few additional
 * tags;
 *
 * Markup usually supported by notification servers:
 * <b> ... </b> - Bold
 * <i> ... </i> - Italic
 * <u> ... </u> - Underline
 * <a href="..."> ... </a> - Hyperlink
 * <img src="..." alt="..."/> - Image
 */

/*!
 * \property Notification::body
 *
 * This property holds the body of text.
 * The body can be multi-line and contain XML-based markup that
 * consists of a small subset of HTML along with a few additional
 * tags;
 *
 * Markup usually supported by notification servers:
 * <b> ... </b> - Bold
 * <i> ... </i> - Italic
 * <u> ... </u> - Underline
 * <a href="..."> ... </a> - Hyperlink
 * <img src="..." alt="..."/> - Image
 */
QString Notification::body() const
{
    Q_D(const Notification);
    return d->body;
}

void Notification::setBody(const QString &body)
{
    Q_D(Notification);

    if (d->body == body)
        return;

    d->body = body;
    Q_EMIT bodyChanged();
}

/*!
 * \qmlproperty object Vibe::Notifications::Notification::replacesId
 *
 * This property holds the ID of an existing notification that this
 * notification is intended to replace.
 */

/*!
 * \property Notification::replacesId
 *
 * This property holds the ID of an existing notification that this
 * notification is intended to replace.
 */
quint32 Notification::replacesId() const
{
    Q_D(const Notification);
    return d->replacesId;
}

void Notification::setReplacesId(quint32 id)
{
    Q_D(Notification);

    if (d->replacesId == id)
        return;

    d->replacesId = id;
    Q_EMIT replacesIdChanged();
}

/*!
 * \enum Notification::Urgency
 *
 * This enum type describes the urgency level of a notification.
 *
 * \value Low The notification is not urgent.
 * \value Normal The notification is like most other notifications.
 * \value Critical The notification is very important.
 */

/*!
 * \qmlproperty object Vibe::Notifications::Notification::urgency
 *
 * This property holds the urgency level of the notification.
 * Urgency is a hint, setting it with Notification::setHint() will change
 * the value here.
 */

/*!
 * \property Notification::urgency
 *
 * This property holds the urgency level of the notification.
 * Urgency is a hint, setting it with Notification::setHint() will change
 * the value here.
 */
Notification::Urgency Notification::urgency() const
{
    Q_D(const Notification);

    bool ok = false;
    int value = d->hints.value(QLatin1String("urgency"), QLatin1String("1")).toInt(&ok);
    if (!ok)
        return Notification::UrgencyNormal;
    return static_cast<Notification::Urgency>(value);
}

void Notification::setUrgency(Notification::Urgency urgency)
{
    Q_D(Notification);

    setHint(QLatin1String("urgency"), QString::number(int(urgency)));
}

/*!
 * \qmlproperty object Vibe::Notifications::Notification::timeout
 *
 * This property holds the timeout in milliseconds since the display of
 * the notification at which the notification should automatically close.
 *
 * If -1, the expiration time depends on the notification server's settings,
 * and may vary for the type of notification. If 0, never expire.
 *
 * \default -1
 */

/*!
 * \property Notification::timeout
 *
 * This property holds the timeout in milliseconds since the display of
 * the notification at which the notification should automatically close.
 *
 * If -1, the expiration time depends on the notification server's settings,
 * and may vary for the type of notification. If 0, never expire.
 *
 * \default -1
 */
int Notification::timeout() const
{
    Q_D(const Notification);
    return d->timeout;
}

void Notification::setTimeout(int timeout)
{
    Q_D(Notification);

    if (d->timeout == timeout)
        return;

    d->timeout = timeout;
    Q_EMIT timeoutChanged();
}

/*!
 * Returns the hints for this notification.
 * \sa Notification::setHint
 */
QVariantMap Notification::hints() const
{
    Q_D(const Notification);
    return d->hints;
}

/*!
 * Set a hint named \a name with value \a value.
 * The "urgency" hint is set with Notification::setUrgency().
 * \sa Notification::setUrgency
 */
void Notification::setHint(const QString &name, const QVariant &value)
{
    Q_D(Notification);
    d->hints.insert(name, value);
}

/*!
 * Remove the hint called \a name.
 */
bool Notification::removeHint(const QString &name)
{
    Q_D(Notification);
    return d->hints.remove(name) > 0;
}

/*!
 * Remove all hints.
 */
void Notification::clearHints()
{
    Q_D(Notification);
    d->hints.clear();
}

/*!
 * Returns the actions for this notification.
 */
QStringList Notification::actions() const
{
    Q_D(const Notification);
    return d->actions;
}

/*!
 * Sets the actions for this notification.
 */
void Notification::setActions(const QStringList &actions)
{
    Q_D(Notification);
    d->actions = actions;
}

/*!
 * Returns the list of capabilities of the notifications server.
 * This call is synchronous.
 */
QStringList Notification::getCapabilities() const
{
    Q_D(const Notification);

    QDBusPendingReply<QStringList> reply = d->iface->GetCapabilities();
    reply.waitForFinished();
    return reply.argumentAt<0>();
}

/*!
 * Sends the notification.
 * If \l replacesId is zero, a new notification will be created and
 * \l replacesId will be updated to contain that ID, otherwise the
 * existing notification with the \l replacesId ID will be updated.
 */
void Notification::send()
{
    Q_D(Notification);

    QDBusPendingCall call = d->iface->Notify(d->appName, d->replacesId, d->appIcon,
                                             d->summary, d->body,
                                             d->actions, d->hints,
                                             d->timeout);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(call, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [&](QDBusPendingCallWatcher *self) {
        QDBusPendingReply<uint> reply = *self;
        if (reply.isError()) {
            Q_EMIT sendFailed();
        } else {
            setReplacesId(reply.argumentAt<0>());
            Q_EMIT sendSucceeded(replacesId());
        }
        self->deleteLater();
    });
}

/*!
 * Closes the notification identified by \l replacesId.
 */
void Notification::close()
{
    Q_D(Notification);

    if (!d->replacesId != 0) {
        QDBusPendingCall call = d->iface->CloseNotification(d->replacesId);
        QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(call, this);
        connect(watcher, &QDBusPendingCallWatcher::finished, this, [&](QDBusPendingCallWatcher *self) {
            QDBusPendingReply<> reply = *self;
            if (!reply.isError()) {
                setReplacesId(0);
                Q_EMIT closed(Notification::Closed);
                self->deleteLater();
            }
        });
    }
}

} // namespace Vibe

#include "moc_notification.cpp"
