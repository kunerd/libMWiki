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

#include <stdlib.h>
/**
 * Creates a LwParameter with the given name and value. The returned object should be freed with lw_rest_free() when no longer needed.

 * @param name name of the parameter
 * @param value value of the parameter
 * @return the new LwParameter
 *
 * @public
 * @memberof LwParameter
 */
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

/**
 * Adds a value to a LwParameter.
 *
 * @param parameter a LwParameter
 * @param value the value to add
 *
 * @public
 * @memberof LwParameter
 */
void
lw_parameter_add_value(LwParameter *parameter, const gchar *value)
{
  parameter->values = g_list_append(parameter->values, (gpointer) value);
}

/**
 * Frees the memory allocated for a LwParameter.
 *
 * @param parameter a LwParameter
 *
 * @public
 * @memberof LwParameter
 */
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

/**
 * Returns a string representation of a LwParameter.
 *
 * @param parameter a LwParameter
 * @return string representation of a LwParameter
 *
 * @public
 * @memberof LwParameter
 */
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

