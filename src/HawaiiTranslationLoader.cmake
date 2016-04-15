#.rst
# Qt5TranslationLoader
# --------------------
#
# This module provides the ``hawaii_translation_loader`` function that
# generates C++ code to load translations for Qt applications and
# libraries.
#
# ::
#
#   hawaii_translation_loader(<dest_var>
#                             TRANSLATIONS_DIR <translations_dir>
#                             CATALOG_NAME <catalog_name>)
#
# Generates C++ code that installs the translation catalog <catalog_name>
# from the <translations_dir> directory for Qt applications and libraries.
# The <translations_dir> path is relative to the generic data location
# returned by QStandardPaths.
#
# The generated code is appended to <sources_var>.
#

#=============================================================================
# Copyright 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
# Copyright 2014 Luís Pereira <luis.artur.pereira@gmail.com>
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

function(hawaii_translation_loader destFiles)
    set(options "")
    set(oneValueArgs TRANSLATIONS_DIR CATALOG_NAME)
    set(multiValueArgs "")
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT ARGS_TRANSLATIONS_DIR)
        message(FATAL_ERROR "Missing TRANSLATIONS_DIR argument to hawaii_translation_loader")
    endif()

    if(NOT ARGS_CATALOG_NAME)
        message(FATAL_ERROR "Missing CATALOG_NAME argument to hawaii_translation_loader")
    endif()

    configure_file(
        ${HAWAII_CMAKE_MODULES_DIR}/HawaiiTranslationLoader.cpp.in
        HawaiiTranslationLoader.cpp @ONLY
    )
    set(${destFiles} ${${destFiles}} ${CMAKE_CURRENT_BINARY_DIR}/HawaiiTranslationLoader.cpp PARENT_SCOPE)
endfunction()
