include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}/../../headers"
    ${Qt5Core_PRIVATE_INCLUDE_DIRS}
)

add_definitions(-DQT_NO_KEYWORDS)

set(SOURCES
    desktopfile.cpp
    desktopfileaction.cpp
    kformat.cpp
    kformatprivate.cpp
    notification.cpp
    qobjectlistmodel.cpp
)

qt5_add_dbus_interfaces(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../declarative/notifications/org.freedesktop.Notifications.xml")

add_library(VibeCore SHARED ${SOURCES})
add_library(Vibe::Core ALIAS VibeCore)

target_link_libraries(VibeCore
    PUBLIC
        Qt5::Core
        Qt5::DBus
        Qt5::Gui
        Qt5::Qml
        Qt5Xdg
)

##############################################################################

generate_export_header(VibeCore EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/Vibe/core/vibe_core_export.h")

target_include_directories(VibeCore
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Vibe>"
        "$<INSTALL_INTERFACE:${VIBE_INCLUDEDIR}>"
)

set_target_properties(VibeCore PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_SOVERSION}
                      EXPORT_NAME Core)

ecm_generate_headers(VibeCore_CamelCase_HEADERS
  HEADER_NAMES
    DesktopFile
    DesktopFileAction
    Notification
    QQuickList
    QObjectListModel
    KFormat
  PREFIX
    Core
  REQUIRED_HEADERS
    VibeCore_HEADERS
  OUTPUT_DIR
    "${CMAKE_CURRENT_BINARY_DIR}/Vibe"
)
install(FILES ${VibeCore_CamelCase_HEADERS}
        DESTINATION ${VIBE_INCLUDEDIR}/Core
        COMPONENT Devel)

install(TARGETS VibeCore EXPORT VibeCoreTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(
    FILES
      "${CMAKE_CURRENT_BINARY_DIR}/Vibe/core/vibe_core_export.h"
      ${VibeCore_HEADERS}
      desktopfile.h
      desktopfileaction.h
      notification.h
      qquicklist.h
      qobjectlistmodel.h
      kformat.h
    DESTINATION
      ${VIBE_INCLUDEDIR}/core
    COMPONENT
      Devel
)

install(EXPORT VibeCoreTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE VibeCoreTargets.cmake NAMESPACE Vibe::)
