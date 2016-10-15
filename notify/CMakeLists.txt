include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}/../headers"
    "${CMAKE_CURRENT_BINARY_DIR}/../src/core/Vibe"
)

set(SOURCES
    main.cpp
)

add_executable(liri-notify ${SOURCES})
target_link_libraries(liri-notify Vibe::Core)

install(TARGETS liri-notify RUNTIME
        DESTINATION ${BIN_INSTALL_DIR})
