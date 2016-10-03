include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}/../headers"
    "${CMAKE_CURRENT_BINARY_DIR}/../src/core/Vibe"
)

set(SOURCES
    main.cpp
)

add_executable(notify ${SOURCES})
target_link_libraries(notify Vibe::Core)

install(TARGETS notify RUNTIME
        DESTINATION ${BIN_INSTALL_DIR})
