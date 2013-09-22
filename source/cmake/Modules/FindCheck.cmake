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

# - Try to find Check
# Once done this will define
#  CHECK_FOUND - System has CHECK
#  CHECK_INCLUDE_DIRS - The CHECK include directories
#  CHECK_LIBRARIES - The libraries needed to use CHECK
#  CHECK_DEFINITIONS - Compiler switches required for using CHECK

FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(PC_CHECK libcheck QUIET)
SET(CHECK_DEFINITIONS ${PC_CHECK_CFLAGS_OTHER})

find_path(
	CHECK_INCLUDE_DIR check.h
	HINTS ${CMAKE_FIND_ROOT_PATH}
		${PC_CHECK_INCLUDEDIR}
   		${PC_CHECK_INCLUDE_DIRS}
	PATH_SUFFIXES libcheck
)

find_library(
	CHECK_LIBRARY NAMES check libcheck
	HINTS ${CMAKE_FIND_ROOT_PATH}
		${PC_CHECK_LIBDIR}
		${PC_CHECK_LIBRARY_DIRS}
)

set(CHECK_LIBRARIES ${CHECK_LIBRARY} )
set(CHECK_INCLUDE_DIRS ${CHECK_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CHECK_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CHECK  DEFAULT_MSG
                                  CHECK_LIBRARY CHECK_INCLUDE_DIR)

mark_as_advanced(CHECK_INCLUDE_DIR CHECK_LIBRARY )
