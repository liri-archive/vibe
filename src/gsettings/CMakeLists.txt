include_directories(
    ${CMAKE_BINARY_DIR}/headers
    ${CMAKE_CURRENT_BINARY_DIR}
    ${gio_INCLUDE_DIRS}
)

add_definitions(-DQT_NO_KEYWORDS)

set(SOURCES
    qgvariantutils.cpp
    qgsettings.cpp
    utils.cpp
)

add_library(HawaiiGSettings SHARED ${SOURCES})
add_library(Hawaii::GSettings ALIAS HawaiiGSettings)

target_link_libraries(HawaiiGSettings
    PUBLIC
        Qt5::Core
    PRIVATE
        ${gio_LIBRARIES}
)

##############################################################################

generate_export_header(HawaiiGSettings EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/Hawaii/gsettings/hawaii_gsettings_export.h)

target_include_directories(HawaiiGSettings INTERFACE "$<INSTALL_INTERFACE:${HAWAII_INCLUDEDIR}>")

set_target_properties(HawaiiGSettings PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_SOVERSION}
                      EXPORT_NAME HawaiiGSettings)

ecm_generate_headers(HawaiiGSettings_CamelCase_HEADERS
  HEADER_NAMES
    QGSettings
  PREFIX
    GSettings
  REQUIRED_HEADERS
    HawaiiGSettings_HEADERS
  OUTPUT_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/Hawaii
)
install(FILES ${HawaiiGSettings_CamelCase_HEADERS}
        DESTINATION ${HAWAII_INCLUDEDIR}/GSettings
        COMPONENT Devel)

install(TARGETS HawaiiGSettings EXPORT HawaiiGSettingsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/Hawaii/gsettings/hawaii_gsettings_export.h
      ${HawaiiGSettings_HEADERS}
      qgsettings.h
    DESTINATION
      ${HAWAII_INCLUDEDIR}/gsettings
    COMPONENT
      Devel
)

install(EXPORT HawaiiGSettingsTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE HawaiiGSettingsTargets.cmake NAMESPACE Hawaii::)
