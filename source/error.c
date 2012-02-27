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

#include "error.h"

#include <stdlib.h>
struct LibWikiError
{
  gchar *code;
  gchar *message;
};

LibWikiErrorHandle
LibWikiError_construct(void)
{
  LibWikiErrorHandle o;
  if (!(o = malloc(sizeof(struct LibWikiError))))
    {
      return NULL;
    }
  return o;
}

void
LibWikiError_destruct(LibWikiErrorHandle o)
{
  if (o != NULL)
    {
      g_free(o->code);
      g_free(o->message);
      free(o);
    }
}

gchar *
LibWikiError_toString(LibWikiErrorHandle o)
{
  return g_strdup_printf("%s, %s", o->code, o->message);
}
