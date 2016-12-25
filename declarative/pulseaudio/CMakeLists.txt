add_subdirectory(qpulseaudio)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/qpulseaudio
    ${PULSEAUDIO_INCLUDE_DIR}
    ${GLIB2_INCLUDE_DIR}
)

set(SOURCES
    plugin.cpp
)

add_library(pulseaudioplugin SHARED ${SOURCES})
target_link_libraries(pulseaudioplugin
                      Qt5::DBus
                      Qt5::Qml
                      QPulseAudioPrivate)

set(FILES
    qmldir
    VolumeControl.qml
)

install(FILES ${FILES}
        DESTINATION ${QML_INSTALL_DIR}/Vibe/PulseAudio)
install(TARGETS pulseaudioplugin
        DESTINATION ${QML_INSTALL_DIR}/Vibe/PulseAudio)
