include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(ECMGenerateHeaders)

ecm_setup_version(${PROJECT_VERSION} VARIABLE_PREFIX VIBE
                  VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/vibe_version.h"
                  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/VibeConfigVersion.cmake"
                  SOVERSION ${PROJECT_SOVERSION})

set(VIBE_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/Vibe")

set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/Vibe")

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/VibeConfig.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/VibeConfig.cmake"
                              INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/VibeConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/VibeConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/vibe_version.h
        DESTINATION ${VIBE_INCLUDEDIR}/vibe COMPONENT Devel)

add_subdirectory(core)
add_subdirectory(settings)
add_subdirectory(translations)
