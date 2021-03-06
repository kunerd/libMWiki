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

#ifndef LIBWIKI_REST_H
#define LIBWIKI_REST_H

#include "restparam.h"

#include <glib.h>

/**
 * The LwRest struct represents a Web service.
 */
typedef struct LwRest
{
  const gchar *url; /**< @private Web service base URL.*/
  const gchar *user_agent; /**< @private User Agent.*/
  GList *params; /**< @private List of parameters for the Web service.*/

}LwRest;

LwRest *
lw_rest_new(const gchar *service_url);

void
lw_rest_add_parameter(LwRest *rest, LwParameter *parameter);

LwParameter *
lw_rest_add_parameter_from_string(LwRest *rest, const gchar *name,
    const gchar *value, ...);

GString *
lw_rest_to_string(LwRest *rest);

gchar *
lw_rest_create_GET_request(LwRest *rest);

gchar *
lw_rest_create_POST_fields(LwRest *rest);

void
lw_rest_free(LwRest **rest);

void
lw_rest_free_without_parameters(LwRest **rest);

#endif
