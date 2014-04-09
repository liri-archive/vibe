project(declarativecore)

include_directories(
    ${CMAKE_BINARY_DIR}/src/libhawaii
    ${CMAKE_BINARY_DIR}/src/libhawaiishell
)

set(SOURCES
    plugin.cpp
    packagesmodel.cpp
    packagesmodelitem.cpp
    qmldataprovider.cpp
)

set(FILES
    qmldir
)

add_library(hawaiishellcoreplugin SHARED ${SOURCES})
qt5_use_modules(hawaiishellcoreplugin Qml Quick)
target_link_libraries(hawaiishellcoreplugin hawaiishell)

install(TARGETS hawaiishellcoreplugin LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/qml/Hawaii/Shell/Core)
install(FILES ${FILES}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/qml/Hawaii/Shell/Core)
