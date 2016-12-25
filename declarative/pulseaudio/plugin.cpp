/****************************************************************************
 * This file is part of Vibe.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtQml>

#include "pulseaudio.h"
#include "client.h"
#include "sink.h"
#include "source.h"
#include "context.h"

static QJSValue pulseaudioSingleton(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)

    QJSValue object = scriptEngine->newObject();
    object.setProperty(QLatin1String("NormalVolume"), qreal(QPulseAudio::Context::NormalVolume));
    object.setProperty(QLatin1String("MinimalVolume"), qreal(QPulseAudio::Context::MinimalVolume));
    object.setProperty(QLatin1String("MaximalVolume"), qreal(QPulseAudio::Context::MaximalVolume));
    return object;
}

class PulseAudioPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    void registerTypes(const char *uri)
    {
        // @uri Vibe.PulseAudio
        Q_ASSERT(uri == QLatin1String("Vibe.PulseAudio"));

        qmlRegisterSingletonType(uri, 1, 0, "PulseAudio", pulseaudioSingleton);

        qmlRegisterType<QPulseAudio::CardModel>(uri, 1, 0, "CardModel");
        qmlRegisterType<QPulseAudio::SinkModel>(uri, 1, 0, "SinkModel");
        qmlRegisterType<QPulseAudio::SinkInputModel>(uri, 1, 0, "SinkInputModel");
        qmlRegisterType<QPulseAudio::SourceModel>(uri, 1, 0, "SourceModel");
        qmlRegisterType<QPulseAudio::SourceOutputModel>(uri, 1, 0, "SourceOutputModel");
        qmlRegisterType<QPulseAudio::StreamRestoreModel>(uri, 1, 0, "StreamRestoreModel");

        qmlRegisterType<QPulseAudio::Client>();
        qmlRegisterType<QPulseAudio::Sink>();
        qmlRegisterType<QPulseAudio::Source>();
    }
};

#include "plugin.moc"
