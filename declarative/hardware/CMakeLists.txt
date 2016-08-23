set(SOURCES
    hardwareengine.cpp
    battery.cpp
    storagedevice.cpp
    plugin.cpp
)

add_library(hardwareplugin SHARED ${SOURCES})
target_link_libraries(hardwareplugin
                      Qt5::Core
                      Qt5::Qml
                      KF5::Solid
                      Fluid)

install(FILES qmldir plugins.qmltypes
    DESTINATION ${QML_INSTALL_DIR}/Hawaii/Hardware)
install(TARGETS hardwareplugin
    DESTINATION ${QML_INSTALL_DIR}/Hawaii/Hardware)
