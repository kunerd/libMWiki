#
#  libMWiki - A Mediawiki client library.
#
#  Copyright (C) 2011, 2012 Hendrik Kunert kunerd@users.sourceforge.net
#
#  This file is part of libMWiki.
#
#  libMWiki is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  libMWiki is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with libMWiki.  If not, see <http://www.gnu.org/licenses/>.
#

project(libMWiki C)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

set (wplookup_VERSION_MAJOR 0)
set (wplookup_VERSION_MINOR 0)
set (wplookup_VERSION_PATCH 1)

set (SOURCE_FILES
#    wparticle.c
#    wpopensearch.c
#    wpxml.c
#    adapter.c
#    error.c
    rest.c
    restparam.c
)

################ Gtk2 install Check ####################
find_package(GTK2 REQUIRED)
if (GTK2_FOUND)
        add_definitions(${GTK2_DEFINITIONS})
        include_directories(${GTK2_INCLUDE_DIRS})
endif (GTK2_FOUND)

################ LIBXML2 install Check ####################
find_package(LibXml2 REQUIRED)
if (LIBXML2_FOUND)
        add_definitions(${LIBXML2_DEFINITIONS})
        include_directories(${LIBXML2_INCLUDE_DIRS})
endif (LIBXML2_FOUND)

################ Curl install Check ####################
find_package(CURL REQUIRED)
if (CURL_FOUND)
        add_definitions(${CURL_DEFINITIONS})
        include_directories(${CURL_INCLUDE_DIRS})
endif (CURL_FOUND)

################ Doxygen ###############################
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(wpldoc ALL
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

# used for linking into a shared library
add_definitions(-fPIC)

#add_library(libMWiki STATIC libMWiki.c ${SOURCE_FILES})

#target_link_libraries(
#        wplookup
#        ${GTK2_LIBRARIES}
#        ${CURL_LIBRARIES}
#       ${LIBXML2_LIBRARIES}
#)

if(UNIX)
    enable_testing()
    add_subdirectory(tests)
endif(UNIX)
