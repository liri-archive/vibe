include_directories(
    ${CMAKE_BINARY_DIR}/src/core
    ${CMAKE_BINARY_DIR}/src/core/Hawaii
)

set(SOURCES
    formatter.cpp
    plugin.cpp
)

add_library(hawaiicore SHARED ${SOURCES})
target_link_libraries(hawaiicore
                      Qt5::Core
                      Qt5::Qml
                      Hawaii::Core)

install(FILES qmldir
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Core)
install(TARGETS hawaiicore
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Core)
