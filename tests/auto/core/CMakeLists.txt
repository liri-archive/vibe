include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}/../../src"
    "${CMAKE_CURRENT_BINARY_DIR}/../../src/core"
    "${CMAKE_CURRENT_BINARY_DIR}/../../src/core/Hawaii"
)

add_definitions(
    -DTEST_DATADIR="${CMAKE_CURRENT_SOURCE_DIR}/data/"
    -DQUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

add_executable(tst_qobjectlistmodel EXCLUDE_FROM_ALL tst_qobjectlistmodel.cpp)
target_link_libraries(tst_qobjectlistmodel Qt5::Test Hawaii::Core)
add_test(tst_qobjectlistmodel tst_qobjectlistmodel)
add_dependencies(check tst_qobjectlistmodel)
