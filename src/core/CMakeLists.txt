include_directories(
    ${CMAKE_BINARY_DIR}/headers
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_definitions(-DQT_NO_KEYWORDS)

set(SOURCES
    qobjectlistmodel.cpp
)

add_library(HawaiiCore SHARED ${SOURCES})
add_library(Hawaii::Core ALIAS HawaiiCore)

target_link_libraries(HawaiiCore
    PUBLIC
        Qt5::Core
        Qt5::Qml
)

##############################################################################

generate_export_header(HawaiiCore EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/Hawaii/Core/hawaii_core_export.h)

target_include_directories(HawaiiCore INTERFACE "$<INSTALL_INTERFACE:${HAWAII_INCLUDEDIR}>")

set_target_properties(HawaiiCore PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_SOVERSION}
                      EXPORT_NAME Core)

ecm_generate_headers(HawaiiCore_CamelCase_HEADERS
  HEADER_NAMES
    QQuickList
    QObjectListModel
  PREFIX
    Core
  REQUIRED_HEADERS
    HawaiiCore_HEADERS
  OUTPUT_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/Hawaii
)
install(FILES ${HawaiiCore_CamelCase_HEADERS}
        DESTINATION ${HAWAII_INCLUDEDIR}/Core
        COMPONENT Devel)

install(TARGETS HawaiiCore EXPORT HawaiiCoreTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/Hawaii/Core/hawaii_core_export.h
      ${HawaiiCore_HEADERS}
      qquicklist.h
      qobjectlistmodel.h
    DESTINATION
      ${HAWAII_INCLUDEDIR}/core
    COMPONENT
      Devel
)

install(EXPORT HawaiiCoreTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE HawaiiCoreTargets.cmake NAMESPACE Hawaii::)
