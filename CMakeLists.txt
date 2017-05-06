project(Vibe)

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
cmake_policy(VERSION 3.4.1)

# Instruct CMake to run moc and rrc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Apple-specific configuration
set(APPLE_SUPPRESS_X11_WARNING ON)

# Set version
set(PROJECT_VERSION "0.9.0")
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_SOVERSION 0)

if(NOT USE_SUPERBUILD)
    # Set up packaging
    set(CPACK_PACKAGE_NAME "vibe")
    set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
    set(CPACK_GENERATOR "TGZ")
    set(CPACK_SET_DESTDIR FALSE)
    set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
    set(CPACK_SOURCE_IGNORE_FILES "/build/;/.git;/*.user;/.tx/;~$;${CPACK_SOURCE_IGNORE_FILES}")
    include(CPack)
    add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
endif()

# ECM
find_package(ECM 1.7.0 REQUIRED NO_MODULE)
list(APPEND CMAKE_MODULE_PATH
    "${ECM_MODULE_PATH}"
    "${ECM_KDE_MODULE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

# Macros
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)

# Find pkg-config here so that it can be referenced soon
find_package(PkgConfig)

# Build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden -Werror -Wall -Wextra -Wformat -Wswitch-default -Wunused-parameter -pedantic -std=c++11")

# qCDebug() uses zero variadic arguments, so we need to disable this warning
# as it would become an error with -Werror
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments")
endif()

# Assume release build by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "" FORCE)
endif()

# Find PulseAudio
find_package(PulseAudio 5.0.0 REQUIRED)

# Find Qt5
set(REQUIRED_QT_VERSION "5.6.0")
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED COMPONENTS
             Network Xml DBus Gui Qml Quick QuickTest)

# Find KF5
set(REQUIRED_KF5_VERSION "5.8.0")
find_package(KF5 ${REQUIRED_KF5_VERSION} REQUIRED COMPONENTS
             Wallet Solid NetworkManagerQt ModemManagerQt)

# Find PolicyKit Qt5
set(REQUIRED_POLKITQT_VERSION "0.103.0")
find_package(PolkitQt5-1 ${REQUIRED_POLKITQT_VERSION} REQUIRED)

# Find Fluid
set(REQUIRED_FLUID_VERSION "0.7.90")
find_package(Fluid ${REQUIRED_FLUID_VERSION} REQUIRED)

# Subdirectories
add_subdirectory(headers)
add_subdirectory(src)
add_subdirectory(declarative)

# Display featute summary
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
