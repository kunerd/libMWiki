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

#ifndef WEBRESOURCE_H
#define WEBRESOURCE_H

#include "rest.h"

#include <glib.h>

typedef struct
{
  gchar *raw_content;
  size_t size;
} LwWebresource;

LwWebresource *
lw_webresource_new();

LwWebresource *
lw_webresource_get(LwRest *rest);

LwWebresource *
lw_webresource_post(LwRest *rest);

void
lw_webresource_free(LwWebresource **resource);

#endif /* WEBRESOURCE_H */
