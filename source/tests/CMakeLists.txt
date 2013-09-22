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


################ GLIB2 install Check ####################
find_package(Check)
if (CHECK_FOUND)
    add_definitions(${CHECK_DEFINITIONS})
    include_directories(${CHECK_INCLUDE_DIRS})
    
    ############### LwRest Test #######################################
    add_executable(LwRest_test testrest.c)
    target_link_libraries(
        LwRest_test
        mwiki
        ${CHECK_LIBRARIES}
    )
    add_test(LwRest_test ${EXECUTABLE_OUTPUT_PATH}/LwRest_test)
    
    ############### LwMediawiki Test #######################################
    
    add_executable(LwMediawiki_test test_libmwiki.c)
    target_link_libraries(
        LwMediawiki_test
        mwiki
        ${CHECK_LIBRARIES}
    )
    add_test(LwMediawiki_test ${EXECUTABLE_OUTPUT_PATH}/LwMediawiki_test)
    
    
    ############### LwWebresource Test #######################################
    
    add_executable(LwWebresource_test webresource_test.c)
    target_link_libraries(
        LwWebresource_test
        mwiki
        ${CHECK_LIBRARIES}
    )
    add_test(LwWebresource_test ${EXECUTABLE_OUTPUT_PATH}/LwWebresource_test)
    
endif (CHECK_FOUND)

