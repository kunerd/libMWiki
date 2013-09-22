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

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set (libMWiki_VERSION_MAJOR 0)
set (libMWiki_VERSION_MINOR 0)
set (libMWiki_VERSION_PATCH 1)

set (SOURCE_FILES
    rest.c
    restparam.c
    webresource.c
)

################ GLIB2 install Check ####################
find_package(GLIB2 REQUIRED)
if (GLIB2_FOUND)
        add_definitions(${GLIB2_DEFINITIONS})
        include_directories(${GLIB2_INCLUDE_DIRS})
endif (GLIB2_FOUND)

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

add_library(mwiki SHARED libmwiki.c ${SOURCE_FILES})

target_link_libraries(
    mwiki
    ${GLIB2_LIBRARIES}
    ${CURL_LIBRARIES}
    ${LIBXML2_LIBRARIES}
)

# Tests ####################
enable_testing()
add_subdirectory(tests)


