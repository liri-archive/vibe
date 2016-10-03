/*
 * This file is part of Fluid.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * $BEGIN_LICENSE:MPL2$
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * $END_LICENSE$
 */

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>

#include <Vibe/Core/Notification>

#include "config.h"

using namespace Vibe;

#define TR(x) QT_TRANSLATE_NOOP("Command line parser", QLatin1String(x))

int main(int argc, char *argv[])
{
    // Application
    QCoreApplication app(argc, argv);
    app.setApplicationName(QLatin1String("Vibe"));
    app.setApplicationVersion(VIBE_VERSION_STRING);
    app.setOrganizationName(QLatin1String("Liri"));
    app.setOrganizationDomain(QLatin1String("liri.io"));

    // Command line parser
    QCommandLineParser parser;
    parser.setApplicationDescription(TR("Notifications client"));
    parser.addHelpOption();
    parser.addVersionOption();

    // Summary
    QCommandLineOption summary(QStringList() << QLatin1String("summary") << QLatin1String("s"),
                               TR("Summary"), TR("summary"));
    parser.addOption(summary);

    // Body
    QCommandLineOption body(QStringList() << QLatin1String("body") << QLatin1String("b"),
                            TR("Body text"), TR("body"));
    parser.addOption(body);

    // Icon
    QCommandLineOption icon(QStringList() << QLatin1String("icon") << QLatin1String("i"),
                            TR("Application icon"), TR("icon"));
    parser.addOption(icon);

    // Parse command line
    parser.process(app);

    // At least the summary must be set
    if (!parser.isSet(summary)) {
        qCritical("Please specify a summary");
        return 1;
    }

    // Notification
    Notification *n = new Notification();
    QObject::connect(n, &Notification::sendSucceeded,
                     &app, &QCoreApplication::quit);
    QObject::connect(n, &Notification::sendFailed,
                     &app, &QCoreApplication::quit);
    n->setSummary(parser.value(summary));
    if (parser.isSet(body))
        n->setBody(parser.value(body));
    if (parser.isSet(icon))
        n->setApplicationIcon(parser.value(icon));
    n->send();

    return app.exec();
}
