set(SOURCES
    plugin.cpp
    kquickwallet.cpp
)

add_library(hawaiiwallet SHARED ${SOURCES})
target_link_libraries(hawaiiwallet
                      Qt5::Core
                      Qt5::Qml
                      KF5::Wallet)

install(TARGETS hawaiiwallet
        LIBRARY DESTINATION ${QML_INSTALL_DIR}/Hawaii/Wallet)
install(FILES qmldir
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/Wallet)
