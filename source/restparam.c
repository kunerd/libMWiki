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

#include "restparam.h"

LwParameter *
lw_parameter_new(const gchar *name, const gchar *value)
{
  LwParameter *parameter = NULL;

  parameter = malloc(sizeof(LwParameter));
  if (parameter == NULL)
    {
      /* TODO: log or error code */
      return NULL;
    }
  parameter->values = NULL;

  parameter->name = name;
  parameter->values = g_list_append(parameter->values, (gpointer) value);

  return parameter;
}

void
lw_parameter_free(LwParameter *parameter)
{
  if (parameter != NULL)
    {
      g_list_free(parameter->values);
      free(parameter);
      parameter = NULL;
    }
}

GString *
lw_parameter_to_string(LwParameter *parameter)
{
  GString *result = NULL;
  GList *iterator = NULL;
  gchar *temp_value = NULL;

  result = g_string_new(parameter->name);
  g_string_append(result, "=");

  for (iterator = parameter->values; iterator; iterator = g_list_next(iterator))
    {
      temp_value = (gchar*) iterator->data;
      g_string_append_printf(result, "%s | ", temp_value);
    }
  return result;
}

GString *
lw_parameter_to_GET(LwParameter *parameter)
{
  GString *result = NULL;
  GList *iterator = NULL;
  gchar *temp_value = NULL;

  result = g_string_new(parameter->name);
  g_string_append(result, "=");

  for (iterator = parameter->values; iterator; iterator = g_list_next(iterator))
    {
      temp_value = (gchar*) iterator->data;
      if (g_list_next(iterator) != NULL)
        {
          /* TODO: there are possible other separators*/
          g_string_append_printf(result, "%s|", temp_value);
        }
      else
        {
          g_string_append(result, temp_value);
        }
    }
  return result;
}

