project(HawaiiLibraries)

cmake_minimum_required(VERSION 2.8.9)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Set version
set(LIBHAWAII_VERSION_MAJOR 0)
set(LIBHAWAII_VERSION_MINOR 3)
set(LIBHAWAII_VERSION_PATCH 0)
set(LIBHAWAII_VERSION_STRING "${LIBHAWAII_VERSION_MAJOR}.${LIBHAWAII_VERSION_MINOR}.${LIBHAWAII_VERSION_PATCH}")

# Installation directories
include(GNUInstallDirs)

# Macro to print feature summary
include(FeatureSummary)

# Add custom uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

# Set up packaging
set(CPACK_PACKAGE_NAME "libhawaii")
set(CPACK_PACKAGE_VERSION "${LIBHAWAII_VERSION_STRING}")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SET_DESTDIR FALSE)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES "/build/;/.git;/*.user;/.tx/;~$;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

# ECM setup
find_package(ECM 0.0.10 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMPackageConfigHelpers)

# Macro to generate export header for libraries
include(GenerateExportHeader)

# Build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden -Wall -Wextra -Wno-unused-parameter -std=c++0x")

# Enable deprecated code
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0)

# Assume release build by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "" FORCE)
endif()

# Find Qt5
set(REQUIRED_QT_VERSION 5.0)
find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core Gui Qml Quick)

# Subdirectories
add_subdirectory(declarative)
add_subdirectory(src)

# Display featute summary
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
