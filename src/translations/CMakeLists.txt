install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/VibeTranslations.cmake"
              "${CMAKE_CURRENT_SOURCE_DIR}/VibeTranslationLoader.cmake"
              "${CMAKE_CURRENT_SOURCE_DIR}/VibeTranslationLoader.cpp.in"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)
