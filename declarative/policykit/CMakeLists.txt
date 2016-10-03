include_directories(
    ${Qt5Core_PRIVATE_INCLUDE_DIRS}
    ${POLKITQT-1_INCLUDE_DIRS}
)

set(SOURCES
    listener_p.cpp
    logging_p.cpp
    policykitagent.cpp
    plugin.cpp
)

add_library(polkitplugin SHARED ${SOURCES})
target_link_libraries(polkitplugin
                      Qt5::Core
                      Qt5::DBus
                      Qt5::Qml
                      ${POLKITQT-1_CORE_LIBRARY}
                      ${POLKITQT-1_AGENT_LIBRARY})

install(FILES qmldir plugins.qmltypes
        DESTINATION ${QML_INSTALL_DIR}/Vibe/PolicyKit)
install(TARGETS polkitplugin
        DESTINATION ${QML_INSTALL_DIR}/Vibe/PolicyKit)
