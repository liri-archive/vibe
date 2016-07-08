#.rst
# HawaiiMacros
# ------------
#
# This module provides the ``hawaii_translate_ts`` and ``hawaii_translate_desktop``
# functions for translating Qt applications and desktop entries.
#
# ::
#
#   hawaii_translate_ts(<qm_files>
#                       SOURCES <file> [<file> [...]]
#                       [COMPONENT <component>]
#                       [UPDATE_TRANSLATIONS]
#                       [UPDATE_OPTIONS <option> [<option> [...]]]
#                       [TEMPLATE <template>]
#                       [TRANSLATION_DIR <trans_dir>]
#                       [INSTALL_DIR <install_dir>])
#
# Generate .qm compiled translation files into the <qm_files> variable
# from source <file>s.
#
# An optional component can be specified with COMPONENT but it's only
# effective if INSTALL_DIR is present. Defaults to "Runtime".
#
# If UPDATE_TRANSLATIONS flag is present it extracts and compiles
# the translations. If it's not present it only compiles the
# translations.
# If UPDATE_TRANSLATIONS flag is present, ``hawaii_translate_ts``
# creates the ``update_<name>_ts`` target that will update the
# .ts files.
#
# UPDATE_OPTIONS are optional arguments to lupdate and is only
# effective with UPDATE_TRANSLATIONS.
#
# You can specify an optional translation base name with TEMPLATE.
# Default is ${PROJECT_NAME}.
#
# An optional path to the directory with the .ts files, relative
# to CMakeList.txt can be specified with TRANSLATION_DIR.
# Defaults to "translations".
#
# An optional destination of the compiled files in <qm_files> can
# be specified with INSTALL_DIR. If not present the installation
# is not performed.
#
# ``hawaii_translate_ts`` uses Qt linguist tools, hence it
# checks if Qt5LinguistTools is available to import its macros.
#
# ::
#
#   hawaii_translate_desktop(<result_var>
#                            SOURCES <file> [<file> [...]]
#                            [TRANSLATION_DIR <trans_dir>])
#
# Generates translated desktop files in the result variable <result_var>
# from the source <file>s.
#
# An optional path to the directory with the .desktop files, relative
# to CMakeList.txt can be specified with TRANSLATION_DIR.
# Defaults to "translations".
#
# Translation desktop entry file names are based on <file>, so for
# example if <file> is coolapp.desktop.in, translation file names
# are coolapp_<lang>.desktop.in.
#

#=============================================================================
# Copyright 2014 Luís Pereira <luis.artur.pereira@gmail.com>
# Copyright 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#=============================================================================

include(CMakeParseArguments)

function(hawaii_translate_ts qmFiles)
    set(options UPDATE_TRANSLATIONS)
    set(oneValueArgs TEMPLATE TRANSLATION_DIR INSTALL_DIR COMPONENT)
    set(multiValueArgs SOURCES UPDATE_OPTIONS)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT DEFINED ARGS_UPDATE_OPTIONS)
        set(ARGS_UPDATE_OPTIONS "")
    endif()

    if(NOT DEFINED ARGS_TEMPLATE)
        set(ARGS_TEMPLATE "${PROJECT_NAME}")
    endif()

    if (NOT DEFINED ARGS_TRANSLATION_DIR)
        set(ARGS_TRANSLATION_DIR "translations")
    endif()

    find_package(Qt5LinguistTools CONFIG REQUIRED)

    file(GLOB tsFiles "${ARGS_TRANSLATION_DIR}/${ARGS_TEMPLATE}_*.ts")
    set(templateFile "${ARGS_TRANSLATION_DIR}/${ARGS_TEMPLATE}.ts")

    if(ARGS_UPDATE_TRANSLATIONS)
        qt5_create_translation(QMS
            ${ARGS_SOURCES}
            ${templateFile}
            OPTIONS ${ARGS_UPDATE_OPTIONS}
        )
        qt5_create_translation(QM
            ${ARGS_SOURCES}
            ${tsFiles}
            OPTIONS ${ARGS_UPDATE_OPTIONS}
        )
        add_custom_target("update_${ARGS_TEMPLATE}_ts" ALL DEPENDS ${QMS})
    else()
        qt5_add_translation(QM ${tsFiles})
    endif()

    if(DEFINED ARGS_INSTALL_DIR)
        if(NOT DEFINED ARGS_COMPONENT)
            set(ARGS_COMPONENT "Runtime")
        endif()

        install(FILES ${QM}
                DESTINATION "${ARGS_INSTALL_DIR}"
                COMPONENT "${ARGS_COMPONENT}")
    endif()

    set(${qmFiles} ${QM} PARENT_SCOPE)
endfunction()


# Original Author: Alexander Sokolov <sokoloff.a@gmail.com>
function(hawaii_translate_desktop result_var)
    # Parse arguments
    set(oneValueArgs TRANSLATION_DIR)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(ARGS "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(ARGS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown keywords given to hawaii_translate_desktop(): \"${ARGS_UNPARSED_ARGUMENTS}\"")
    endif()

    if(NOT DEFINED ARGS_SOURCES)
        set(${result_var} "" PARENT_SCOPE)
        return()
    else()
        set(sources ${ARGS_SOURCES})
    endif()

    if(NOT DEFINED ARGS_TRANSLATION_DIR)
        set(translation_dir "translations")
    else()
        set(translation_dir ${ARGS_TRANSLATION_DIR})
    endif()

    get_filename_component(translation_dir ${translation_dir} ABSOLUTE)

    foreach(_in_file ${sources})
        get_filename_component(_in_file ${_in_file} ABSOLUTE)
        get_filename_component(_file_name ${_in_file} NAME_WE)

        get_filename_component(_file_ext  ${_in_file} EXT)
        string(REPLACE ".in" "" _file_ext ${_file_ext})

        set(_out_file "${CMAKE_CURRENT_BINARY_DIR}/${_file_name}${_file_ext}")

        file(GLOB translations ${translation_dir}/${_file_name}_*${_file_ext})

        set(_pattern "'\\[.*]\\s*='")
        if(translations)
            list(SORT translations)
            add_custom_command(OUTPUT ${_out_file}
                COMMAND grep -v -a "'#TRANSLATIONS_DIR='" ${_in_file} > ${_out_file}
                COMMAND grep -h -a ${_pattern} ${translations} >> ${_out_file}
                COMMENT "Generating ${_file_name}${_file_ext}"
            )
        else()
            add_custom_command(OUTPUT ${_out_file}
                COMMAND grep -v -a "'#TRANSLATIONS_DIR='" ${_in_file} > ${_out_file}
                COMMENT "Generating ${_file_name}${_file_ext}"
            )
        endif()

        set(__result ${__result} ${_out_file})
    endforeach()

    set(${result_var} ${__result} PARENT_SCOPE)
endfunction()
