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

add_executable(libMWiki_test testrest.c)
set_target_properties(libMWiki_test PROPERTIES LINK_FLAGS -Wl,-lcunit)
#target_link_libraries(
 #   libMWiki
#)

add_test(libMWiki_test ${EXECUTABLE_OUTPUT_PATH}/libMWiki_test)

set(MEMORYCHECK_COMMAND:FILEPATH=/bin/usr/valgrind)
