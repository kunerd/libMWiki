/*
 *  libMWiki - A Mediawiki client library.
 *
 *  Copyright (C) 2011, 2012 Hendrik Kunert kunerd@users.sourceforge.net
 *
 *  This file is part of libMWiki.
 *
 *  libMWiki is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libMWiki is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libMWiki.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBWIKI_H
#define LIBWIKI_H

#include <glib.h>

typedef struct LwMediaWiki LwMediaWiki;

/**
 * The LwWiki struct represents a Mediwiki service enpoint.
 */
struct LwMediaWiki {
	const gchar *api_url; /**< @private API service URL.*/
	const gchar *user_agent; /**< @private User Agent.*/
};

extern LwMediaWiki*
lw_mediawiki_new(const gchar *api_url);

extern void
lw_mediawiki_free(LwMediaWiki *mw);


#endif
