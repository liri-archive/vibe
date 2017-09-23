Vibe
====

[![ZenHub.io](https://img.shields.io/badge/supercharged%20by-zenhub.io-blue.svg)](https://zenhub.io)

[![License](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](http://www.gnu.org/licenses/lgpl.txt)
[![GitHub release](https://img.shields.io/github/release/lirios/vibe.svg)](https://github.com/lirios/vibe)
[![Build Status](https://travis-ci.org/lirios/vibe.svg?branch=develop)](https://travis-ci.org/lirios/vibe)
[![GitHub issues](https://img.shields.io/github/issues/lirios/vibe.svg)](https://github.com/lirios/vibe/issues)
[![Maintained](https://img.shields.io/maintenance/yes/2017.svg)](https://github.com/lirios/vibe/commits/develop)

A collection of core classes used throughout Liri.

## Features

This library includes:

 * A QML plugin to access storage devices and batteries
 * A QML plugin for freedesktop.org notification servers
 * A QML plugin for MPRIS2 clients
 * A QML plugin for PolicyKit agents.

## Dependencies

Qt >= 5.6.0 with at least the following modules is required:

 * [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
 * [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)

The following modules and their dependencies are required:

 * [qbs-shared](https://github.com/lirios/qbs-shared.git)
 * [fluid](https://github.com/lirios/fluid.git)
 * [libliri](https://github.com/lirios/libliri.git)
 * [solid](http://quickgit.kde.org/?p=solid.git)
 * [networkmanager-qt](http://quickgit.kde.org/?p=networkmanager-qt.git)
 * [modemmanager-qt](http://quickgit.kde.org/?p=modemmanager-qt.git)
 * [polkit-qt5](http://quickgit.kde.org/?p=polkit-qt-1.git)
 * [pulseaudio >= 5.0.0](https://cgit.freedesktop.org/pulseaudio/pulseaudio/)

## Installation

Qbs is a new build system that is much easier to use compared to qmake or CMake.

If you want to learn more, please read the [Qbs manual](http://doc.qt.io/qbs/index.html),
especially the [setup guide](http://doc.qt.io/qbs/configuring.html) and how to install artifacts
from the [installation guide](http://doc.qt.io/qbs/installing-files.html).

From the root of the repository, run:

```sh
qbs setup-toolchains --type gcc /usr/bin/g++ gcc
qbs setup-qt /usr/bin/qmake-qt5 qt5
qbs config profiles.qt5.baseProfile gcc
qbs -d build -j $(nproc) profile:qt5 # use sudo if necessary
```

On the last `qbs` line, you can specify additional configuration parameters at the end:

 * `qbs.installRoot:/path/to/install` (for example `/`)
 * `qbs.installPrefix:path/to/install` (for example `opt/liri` or `usr`)

The following are only needed if `qbs.installPrefix` is a system-wide path such as `usr`
and the default value doesn't suit your needs. All are relative to `qbs.installRoot`:

 * `modules.lirideployment.libDir:path/to/lib` where libraries are installed (default: `lib`)
 * `modules.lirideployment.qmlDir:path/to/qml` where QML plugins are installed (default: `lib/qml`)
 * `modules.lirideployment.pluginsDir:path/to/plugins` where Qt plugins are installed (default: `lib/plugins`)
 * `modules.lirideployment.qbsModulesDir:path/to/qbs` where Qbs modules are installed (default: `share/qbs/modules`)

See [lirideployment.qbs](https://github.com/lirios/qbs-shared/blob/develop/modules/lirideployment/lirideployment.qbs)
for more deployment-related parameters.

If you specify `qbs.installRoot` you might need to prefix the entire line with `sudo`,
depending on whether you have permissions to write there or not.

## Notes

### Logging categories

Qt 5.2 introduced logging categories and we takes advantage of
them to make debugging easier.

Please refer to the [Qt](http://doc.qt.io/qt-5/qloggingcategory.html) documentation
to learn how to enable them.

### Available categories

 * Hardware QML plugin:
   * **vibe.hardware:** Hardware service.
   * **vibe.hardware.battery:** Battery information.
   * **vibe.hardware.storagedevice:** Storage device information.

 * Notifications QML plugin:
   * **vibe.notifications:** Notifications service.

 * MPRIS2 QML plugin:
   * **vibe.mpris2:** MPRIS2 engine
   * **vibe.mpris2.player:** MPRIS2 player interface

 * Network QML plugin:
   * **vibe.networkmanager:** NetworkManager support.

 * PolicyKit QML plugin:
   * **vibe.policykit:** PolicyKit agent.

## Licensing

Licensed under the terms of the GNU Lesser General Public License version 3 or,
at your option, any later version.
