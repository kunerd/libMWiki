/*
 *  libWiki - A Mediawiki client library.
 *
 *  Copyright (C) 2011, 2012 Hendrik Kunert kunerd@users.sourceforge.net
 *
 *  This file is part of libWiki.
 *
 *  libWiki is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libWiki is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libWiki.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RESTPARAM_H
#define RESTPARAM_H

#include "glib.h"

typedef struct
{
  const gchar *name;
  GList *values;
} LwParameter;

LwParameter *
lw_parameter_new(const gchar *name, const gchar *value);

void
lw_parameter_free(LwParameter *parameter);

GString *
lw_parameter_to_string(LwParameter *parameter);

GString *
lw_parameter_to_GET(LwParameter *parameter);

#endif /* RESTPARAM_H */
