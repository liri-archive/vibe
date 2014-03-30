project(declarativeapplications)

include_directories(
    ${CMAKE_BINARY_DIR}/src/libhawaii
    ${CMAKE_BINARY_DIR}/src/libhawaiishell
)

set(SOURCES
    plugin.cpp
    applicationiconprovider.cpp
    applicationsmodel.cpp
)

set(FILES
    qmldir
)

add_library(hawaiishellapplicationsplugin SHARED ${SOURCES})
qt5_use_modules(hawaiishellapplicationsplugin Qml Quick)
target_link_libraries(hawaiishellapplicationsplugin hawaiishell)

install(TARGETS hawaiishellapplicationsplugin LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/qml/Hawaii/Shell/Applications)
install(FILES ${FILES}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/qml/Hawaii/Shell/Applications)
