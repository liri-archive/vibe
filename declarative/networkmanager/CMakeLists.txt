find_package(NetworkManager 0.9.8.4)
set_package_properties(NetworkManager PROPERTIES
                       TYPE REQUIRED)

find_package(MobileBroadbandProviderInfo)
set_package_properties(MobileBroadbandProviderInfo PROPERTIES
                       DESCRIPTION "Database of mobile broadband service providers"
                       URL "http://live.gnome.org/NetworkManager/MobileBroadband/ServiceProviders"
                       TYPE OPTIONAL)

add_definitions(-DWITH_MODEMMANAGER_SUPPORT=1)

include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}/../../headers"
)

add_definitions(-DQT_NO_KEYWORDS)

set(SOURCES
    appletproxymodel.cpp
    availabledevices.cpp
    connectionicon.cpp
    debug.cpp
    enabledconnections.cpp
    enums.cpp
    handler.cpp
    networkitemslist.cpp
    networkmodel.cpp
    networkmodelitem.cpp
    networkstatus.cpp
    plugin.cpp
    uiutils.cpp
)

add_library(nmplugin SHARED ${SOURCES})
target_link_libraries(nmplugin
                      Qt5::Core
                      Qt5::DBus
                      Qt5::Network
                      Qt5::Gui
                      Qt5::Qml
                      Qt5::Quick
                      KF5::NetworkManagerQt
                      KF5::ModemManagerQt)

install(FILES qmldir plugins.qmltypes
        DESTINATION ${QML_INSTALL_DIR}/Vibe/NetworkManager)
install(TARGETS nmplugin
        DESTINATION ${QML_INSTALL_DIR}/Vibe/NetworkManager)
