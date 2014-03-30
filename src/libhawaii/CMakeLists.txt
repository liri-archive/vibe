project(libhawaii)

set(SOURCES
    appinfo.cpp
    package.cpp
    packages_p.cpp
    packagestructure.cpp
    pluginloader.cpp
    pluginmetadata.cpp
    xdgdesktopfile.cpp
)

ecm_setup_version(${LIBHAWAII_VERSION_STRING}
    VARIABLE_PREFIX LIBHAWAII
    VERSION_HEADER ${CMAKE_CURRENT_BINARY_DIR}/hawaii/hawaii_version.h
    PACKAGE_VERSION_FILE ${CMAKE_CURRENT_BINARY_DIR}/HawaiiConfigVersion.cmake
)

set(CMAKECONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/Hawaii)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_FULL_INCLUDEDIR}/hawaii)

add_library(hawaii SHARED ${SOURCES})
qt5_use_modules(hawaii Core Gui)
target_include_directories(hawaii INTERFACE ${INCLUDE_INSTALL_DIR})
set_target_properties(hawaii PROPERTIES
    VERSION ${LIBHAWAII_VERSION_STRING}
    SOVERSION ${LIBHAWAII_SOVERSION}
    EXPORT_NAME Hawaii
)

ecm_generate_headers(HEADERS
    HEADER_NAMES
        AppInfo
        Package
        PackageStructure
        PluginLoader
        PluginMetadata
    PREFIX Hawaii
    REQUIRED_HEADERS SMALL_HEADERS
)
generate_export_header(hawaii
    BASE_NAME Hawaii
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/hawaii/hawaii_export.h
)

ecm_configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/HawaiiConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/HawaiiConfig.cmake
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    PATH_VARS INCLUDE_INSTALL_DIR CMAKE_INSTALL_PREFIX
)

install(TARGETS hawaii
    EXPORT HawaiiTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/HawaiiConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/HawaiiConfigVersion.cmake
    DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    COMPONENT Devel
)
install(EXPORT HawaiiTargets
    DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    FILE HawaiiTargets.cmake
)
install(FILES
    ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hawaii/Hawaii
    COMPONENT Devel
)
install(FILES
    ${SMALL_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/hawaii/hawaii_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hawaii/hawaii
    COMPONENT Devel
)
