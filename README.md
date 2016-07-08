Hawaii Core Library
===================

[![ZenHub.io](https://img.shields.io/badge/supercharged%20by-zenhub.io-blue.svg)](https://zenhub.io)

[![License](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](http://www.gnu.org/licenses/lgpl.txt)
[![GitHub release](https://img.shields.io/github/release/hawaii-desktop/libhawaii.svg)](https://github.com/hawaii-desktop/libhawaii)
[![Build Status](https://travis-ci.org/hawaii-desktop/libhawaii.svg?branch=develop)](https://travis-ci.org/hawaii-desktop/libhawaii)
[![GitHub issues](https://img.shields.io/github/issues/hawaii-desktop/libhawaii.svg)](https://github.com/hawaii-desktop/libhawaii/issues)
[![Maintained](https://img.shields.io/maintenance/yes/2016.svg)](https://github.com/hawaii-desktop/libhawaii/commits/develop)

A collection of core classes used throughout Hawaii.

## Features

This library includes:

 * A Qt-style wrapper for GSettings that provides a nice
   settings API based on schemas with change notifications.
 * An enhanced `QList` that provides a model with change notifications for QML.
 * A QML wrapper around KWallet

### Dependencies

 Qt >= 5.4.0 with at least the following modules is required:

 * [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
 * [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)

 The following modules and their dependencies are required:

 * [ECM >= 1.4.0](http://quickgit.kde.org/?p=extra-cmake-modules.git)
 * [glib >= 2.31.0](https://git.gnome.org/browse/glib)
 * [KWallet](http://api.kde.org/frameworks-api/frameworks5-apidocs/kwallet/html/)

### Installation

From the root of the repository, run:

```sh
mkdir build; cd build
cmake .. -DKDE_INSTALL_USE_QT_SYS_PATHS=ON
make
make install # use sudo if necessary
```

On the `cmake` line, you can specify additional configuration parameters:

 * `-DCMAKE_INSTALL_PREFIX=/path/to/install` (for example, `/opt/hawaii` or `/usr`)
 * `-DCMAKE_BUILD_TYPE=<build_type>`, where `<build_type>` is one of:
   * **Debug:** debug build
   * **Release:** release build
   * **RelWithDebInfo:** release build with debugging information

### Licensing

Licensed under the GNU Lesser General Public License version 3.0 terms.
