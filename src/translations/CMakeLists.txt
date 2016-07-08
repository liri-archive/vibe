install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/HawaiiTranslations.cmake"
              "${CMAKE_CURRENT_SOURCE_DIR}/HawaiiTranslationLoader.cmake"
              "${CMAKE_CURRENT_SOURCE_DIR}/HawaiiTranslationLoader.cpp.in"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)
