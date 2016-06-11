Hawaii libraries
================

[![GitHub release](https://img.shields.io/github/release/hawaii-desktop/libhawaii.svg)](https://github.com/hawaii-desktop/hawaii-shell)
[![GitHub issues](https://img.shields.io/github/issues/hawaii-desktop/libhawaii.svg)](https://github.com/hawaii-desktop/hawaii-shell/issues)
[![IRC Network](https://img.shields.io/badge/irc-freenode-blue.svg "IRC Freenode")](https://webchat.freenode.net/?channels=hawaii-desktop)

These are the libraries used by Hawaii Shell and other projects related
to the Hawaii desktop environment.

## Overview

This library includes

* A Qt-style wrapper for GSettings that provides a nice
  settings API based on schemas with change notifications.

## License

Licensed under the GNU Lesser General Public License version 3.0 terms.

## Dependencies

Qt >= 5.4.0 with at least the following modules is required:

* [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
* [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)

The following modules and their dependencies are required:

* [ECM >= 1.4.0](http://quickgit.kde.org/?p=extra-cmake-modules.git)
* [glib >= 2.31.0](https://git.gnome.org/browse/glib)

## Build

Building this module is a piece of cake.

Assuming you are in the source directory, just create a build directory
and run cmake:

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/opt/hawaii ..
```

To do a debug build the last command can be:

```sh
cmake -DCMAKE_INSTALL_PREFIX=/opt/hawaii -DCMAKE_BUILD_TYPE=Debug ..
```

To do a release build instead it can be:

```sh
cmake -DCMAKE_INSTALL_PREFIX=/opt/hawaii -DCMAKE_BUILD_TYPE=Release ..
```

If not passed, the `CMAKE_INSTALL_PREFIX` parameter defaults to /usr/local.
You have to specify a path that fits your needs, /opt/hawaii is just an example.

The `CMAKE_BUILD_TYPE` parameter allows the following values:

* **Debug:** debug build
* **Release:** release build
* **RelWithDebInfo:** release build with debugging information

### System-wide installation

Those who want to perform a system-wide installation, such as package
maintainers, should pass different arguments to cmake:

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DKDE_INSTALL_USE_QT_SYS_PATHS=ON ..
```

Feel free to choose whatever `CMAKE_BUILD_TYPE` value you desire.

## Installation

It's really easy, it's just a matter of typing:

```sh
make install
```

from the build directory.
