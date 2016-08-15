include_directories(
    ${CMAKE_BINARY_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/core/Hawaii
)

set(SOURCES
    main.cpp
)

add_executable(notify ${SOURCES})
target_link_libraries(notify Hawaii::Core)

install(TARGETS notify RUNTIME
        DESTINATION ${BIN_INSTALL_DIR})
