include_directories(
    ${PULSEAUDIO_INCLUDE_DIR}
    ${GLIB2_INCLUDE_DIR}
)

set(SOURCES
    card.cpp
    client.cpp
    context.cpp
    device.cpp
    maps.cpp
    operation.cpp
    port.cpp
    profile.cpp
    pulseaudio.cpp
    pulseobject.cpp
    ref.cpp
    sink.cpp
    sinkinput.cpp
    source.cpp
    sourceoutput.cpp
    stream.cpp
    volumeobject.cpp
    debug.cpp
    server.cpp
    streamrestore.cpp
)

add_library(QPulseAudioPrivate STATIC ${SOURCES})
target_link_libraries(QPulseAudioPrivate
    Qt5::Core
    Qt5::Gui
    ${PULSEAUDIO_LIBRARY}
    ${PULSEAUDIO_MAINLOOP_LIBRARY}
)
