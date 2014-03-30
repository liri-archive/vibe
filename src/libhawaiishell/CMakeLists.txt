project(libhawaiishell)

include_directories(
    ${QtConfiguration_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/src/libhawaii
)

set(SOURCES
    containment.cpp
    containmentitem.cpp
    element.cpp
    elementitem.cpp
    hawaiishell.cpp
    mantle.cpp
    qmlobject.cpp
    qmlobjectincubationcontroller_p.cpp
    quickview.cpp
)

ecm_setup_version(${LIBHAWAII_VERSION_STRING}
    VARIABLE_PREFIX LIBHAWAII
    VERSION_HEADER ${CMAKE_CURRENT_BINARY_DIR}/hawaiishell/hawaiishell_version.h
    PACKAGE_VERSION_FILE ${CMAKE_CURRENT_BINARY_DIR}/HawaiiShellConfigVersion.cmake
)

set(CMAKECONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/HawaiiShell)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_FULL_INCLUDEDIR}/hawaii)

add_library(hawaiishell SHARED ${SOURCES})
qt5_use_modules(hawaiishell Qml Quick)
target_include_directories(hawaiishell INTERFACE ${INCLUDE_INSTALL_DIR})
target_link_libraries(hawaiishell
    hawaii
    ${QtConfiguration_LIBRARIES}
)
set_target_properties(hawaiishell PROPERTIES
    VERSION ${LIBHAWAII_VERSION_STRING}
    SOVERSION ${LIBHAWAII_SOVERSION}
    EXPORT_NAME HawaiiShell
)

ecm_generate_headers(HEADERS
    HEADER_NAMES
        Containment
        ContainmentItem
        Element
        ElementItem
        HawaiiShell
        Mantle
        QmlObject
        QuickView
    PREFIX HawaiiShell
    REQUIRED_HEADERS SMALL_HEADERS
)
generate_export_header(hawaiishell
    BASE_NAME HawaiiShell
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/hawaiishell/hawaiishell_export.h
)

ecm_configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/HawaiiShellConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/HawaiiShellConfig.cmake
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    PATH_VARS INCLUDE_INSTALL_DIR CMAKE_INSTALL_PREFIX
)

install(TARGETS hawaiishell
    EXPORT HawaiiShellTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/HawaiiShellConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/HawaiiShellConfigVersion.cmake
    HawaiiShellMacros.cmake
    DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    COMPONENT Devel
)
install(EXPORT HawaiiShellTargets
    DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    FILE HawaiiShellTargets.cmake
)
install(FILES
    ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hawaii/HawaiiShell
    COMPONENT Devel
)
install(FILES
    ${SMALL_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/hawaiishell/hawaiishell_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hawaii/hawaiishell
    COMPONENT Devel
)
