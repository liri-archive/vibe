include(GenerateExportHeader)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(ECMGenerateHeaders)

ecm_setup_version(${PROJECT_VERSION} VARIABLE_PREFIX HAWAII
                  VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/hawaii_version.h"
                  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/HawaiiConfigVersion.cmake"
                  SOVERSION ${PROJECT_SOVERSION})

set(HAWAII_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/Hawaii")

set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/Hawaii")

ecm_configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/HawaiiConfig.cmake.in"
                                  "${CMAKE_CURRENT_BINARY_DIR}/HawaiiConfig.cmake"
                                  INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/HawaiiConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/HawaiiConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hawaii_version.h
        DESTINATION ${HAWAII_INCLUDEDIR}/hawaii COMPONENT Devel)

add_subdirectory(core)
add_subdirectory(settings)
add_subdirectory(translations)
