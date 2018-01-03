/****************************************************************************
 * This file is part of Vibe.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPLv3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

import QtQuick 2.0
import Fluid.Core 1.0 as FluidCore
import Vibe.PulseAudio 1.0

FluidCore.Object {
    readonly property real from: 0
    readonly property real to: 100
    readonly property real stepPercentage: 5
    readonly property real stepSize: Math.round(stepPercentage * PulseAudio.NormalVolume / 100.0)
    readonly property bool visible: sinkModel.defaultSink !== null
    readonly property bool muted: visible ? sinkModel.defaultSink.muted || sinkModel.defaultSink.volume === PulseAudio.MinimalVolume : false

    signal volumeChanged(real volume)

    SinkModel {
        id: sinkModel
    }

    // Set volume as soon as the default sink is available
    Connections {
        target: sinkModel
        onDefaultSinkChanged: volumeChanged(getVolumePercentage())
    }

    // Set volume every time it changes
    Connections {
        target: sinkModel.defaultSink
        onVolumeChanged: volumeChanged(getVolumePercentage())
    }

    function getIconName() {
        if (!sinkModel.defaultSink || sinkModel.defaultSink.muted || sinkModel.defaultSink.volume === PulseAudio.MinimalVolume)
            return "av/volume_off"

        var volume = getVolumePercentage()
        if (volume < 33.0)
            return "av/volume_mute"
        else if (volume < 66.0)
            return "av/volume_down"

        return "av/volume_up"
    }

    function getVolumePercentage() {
        if (!sinkModel.defaultSink)
            return 0.0
        return (sinkModel.defaultSink.volume / PulseAudio.NormalVolume) * 100.0
    }

    function setVolumePercentage(value) {
        if (!sinkModel.defaultSink || value < 0 || value > 100)
            return
        sinkModel.defaultSink.volume = (PulseAudio.NormalVolume * value) / 100.0
    }

    function setMinimumVolume() {
        if (sinkModel.defaultSink)
            sinkModel.defaultSink.volume = PulseAudio.MinimalVolume
    }

    function setMaximumVolume() {
        if (sinkModel.defaultSink)
            sinkModel.defaultSink.volume = PulseAudio.NormalVolume
    }

    function toggleMute() {
        if (sinkModel.defaultSink)
            sinkModel.defaultSink.muted = !sinkModel.defaultSink.muted
    }

    function increase() {
        if (sinkModel.defaultSink)
            setVolumePercentage(getVolumePercentage() + stepPercentage)
    }

    function decrease() {
        if (sinkModel.defaultSink)
            setVolumePercentage(getVolumePercentage() - stepPercentage)
    }
}
