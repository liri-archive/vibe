libQmlOS
========

[![ZenHub.io](https://img.shields.io/badge/supercharged%20by-zenhub.io-blue.svg)](https://zenhub.io)

[![License](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](http://www.gnu.org/licenses/lgpl.txt)
[![GitHub release](https://img.shields.io/github/release/qmlos/libqmlos.svg)](https://github.com/qmlos/libqmlos)
[![Build Status](https://travis-ci.org/qmlos/libqmlos.svg?branch=develop)](https://travis-ci.org/qmlos/libqmlos)
[![GitHub issues](https://img.shields.io/github/issues/qmlos/libqmlos.svg)](https://github.com/qmlos/libqmlos/issues)
[![Maintained](https://img.shields.io/maintenance/yes/2016.svg)](https://github.com/qmlos/libqmlos/commits/develop)

A collection of core classes used throughout qmlOS.

## Features

This library includes:

 * A Qt-style wrapper for GSettings that provides a nice
   settings API based on schemas with change notifications.
 * An enhanced `QList` that provides a model with change notifications for QML.
 * A QML wrapper around KWallet
 * A QML plugin to access storage devices and batteries
 * A QML plugin for freedesktop.org notification servers
 * A QML plugin for MPRIS2 clients

## Dependencies

Qt >= 5.6.0 with at least the following modules is required:

 * [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
 * [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)

The following modules and their dependencies are required:

 * [ECM >= 1.7.0](http://quickgit.kde.org/?p=extra-cmake-modules.git)
 * [glib >= 2.31.0](https://git.gnome.org/browse/glib)
 * [kwallet](http://quickgit.kde.org/?p=kwallet.git)
 * [solid](http://quickgit.kde.org/?p=solid.git)
 * [networkmanager-qt](http://quickgit.kde.org/?p=networkmanager-qt.git)
 * [modemmanager-qt](http://quickgit.kde.org/?p=modemmanager-qt.git)

## Installation

From the root of the repository, run:

```sh
mkdir build; cd build
cmake .. -DKDE_INSTALL_USE_QT_SYS_PATHS=ON
make
make install # use sudo if necessary
```

On the `cmake` line, you can specify additional configuration parameters:

 * `-DCMAKE_INSTALL_PREFIX=/path/to/install` (for example, `/opt/qmlos` or `/usr`)
 * `-DCMAKE_BUILD_TYPE=<build_type>`, where `<build_type>` is one of:
   * **Debug:** debug build
   * **Release:** release build
   * **RelWithDebInfo:** release build with debugging information

## Licensing

Licensed under the GNU Lesser General Public License version 3.0 terms.

## Notes

### Logging categories

Qt 5.2 introduced logging categories and we takes advantage of
them to make debugging easier.

Please refer to the [Qt](http://doc.qt.io/qt-5/qloggingcategory.html) documentation
to learn how to enable them.

### Available categories

 * Library:
   * **hawaii.qgsettings:** Qt GSettings wrapper

 * Settings QML plugin:
   * **hawaii.qml.settings:** Settings.

 * Hardware QML plugin:
   * **hawaii.qml.hardware:** Hardware service.
   * **hawaii.qml.hardware.battery:** Battery information.
   * **hawaii.qml.hardware.storagedevice:** Storage device information.

 * Notifications QML plugin:
   * **hawaii.qml.notifications:** Notifications service.

 * MPRIS2 QML plugin:
   * **hawaii.qml.mpris2:** MPRIS2 engine
   * **hawaii.qml.mpris2.player:** MPRIS2 player interface

 * Network QML plugin:
   * **hawaii.qml.networkmanager:** NetworkManager support.
