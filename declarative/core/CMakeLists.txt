include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}/../../src/core"
    "${CMAKE_CURRENT_BINARY_DIR}/../../src/core/Vibe"
)

set(SOURCES
    formatter.cpp
    plugin.cpp
)

add_library(hawaiicore SHARED ${SOURCES})
target_link_libraries(hawaiicore
                      Qt5::Core
                      Qt5::Qml
                      Vibe::Core)

install(FILES qmldir
        DESTINATION ${QML_INSTALL_DIR}/Vibe/Core)
install(TARGETS hawaiicore
        DESTINATION ${QML_INSTALL_DIR}/Vibe/Core)
