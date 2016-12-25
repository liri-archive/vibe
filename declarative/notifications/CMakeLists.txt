include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}/../../headers"
    "${CMAKE_CURRENT_BINARY_DIR}/../../src/core/Vibe"
)

set(SOURCES
    notifications.cpp
    notificationsdaemon.cpp
    notificationsimage.cpp
    notificationsimageprovider.cpp
    plugin.cpp
)

qt5_add_dbus_adaptor(SOURCES
    org.freedesktop.Notifications.xml
    notificationsdaemon.h NotificationsDaemon)

add_library(notificationsplugin SHARED ${SOURCES})
target_link_libraries(notificationsplugin
                      Qt5::Core
                      Qt5::DBus
                      Qt5::Gui
                      Qt5::Qml
                      Qt5::Quick
                      Vibe::Core)

install(FILES qmldir plugins.qmltypes
    DESTINATION ${QML_INSTALL_DIR}/Vibe/Notifications)
install(TARGETS notificationsplugin
    DESTINATION ${QML_INSTALL_DIR}/Vibe/Notifications)
