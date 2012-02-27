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
#include "rest.h"

#include <stdlib.h>

/**
 * The LwRest struct represents a Web service.
 */
struct LwRest
{
  const gchar *url; /**< @private Web service base URL.*/
  GList *params; /**< @private List of parameters for the Web service.*/

};

/**
 * Creates a new LwRest object for specified Web service URL.
 * The returned object should be freed with lw_rest_free() when no longer needed.
 *
 * @param service_url URL of the Web service.
 * @return the newly created LwRest
 *
 * @public
 * @memberof LwRest
 */
LwRestPtr
lw_rest_new(const gchar *service_url)
{
  struct LwRest *rest = NULL;

  rest = malloc(sizeof(struct LwRest));
  if (rest == NULL)
    {
      /* TODO: log or error code */
      return NULL;
    }

  rest->url = service_url;
  rest->params = NULL;

  return rest;
}

/**
 * Adds a parameter to a LwRest.
 *
 * @warning Parameters and their values are not freed with lw_rest_free().
 *
 * @param rest a LwRest
 * @param parameter a LwParameter
 *
 * @public
 * @memberof LwRest
 */
void
lw_rest_add_parameter(LwRestPtr rest, LwParameter *parameter)
{
  rest->params = g_list_append(rest->params, (gpointer) parameter);
}

/**
 * Adds a parameter to a LwRest.
 *
 * @warning The variable argument list must end with NULL. If you forget the NULL, behavior of lw_rest_add_parameter() is not defined.
 *
 * @param rest a LwRest
 * @param name the parameter name
 * @param value the value
 * @param ... a NULL-terminated list of strings to append as values for the parameter
 *
 * @return the added LwParameter object
 *
 * @public
 * @memberof LwRest
 */
LwParameter *
lw_rest_add_parameter_from_string(LwRestPtr rest, const gchar *name,
    const gchar *value, ...)
{
  va_list param_list;
  LwParameter *parameter = NULL;
  gchar* temp_value = NULL;

  parameter = lw_parameter_new(name, value);

  va_start(param_list, value);
  temp_value = va_arg(param_list, gchar *);
  while (temp_value != NULL)
    {
      parameter->values = g_list_append(parameter->values,
          (gpointer) temp_value);
      temp_value = va_arg(param_list, gchar *);
    }

  va_end(param_list);

  lw_rest_add_parameter(rest, parameter);

  return parameter;
}

/**
 * Returns a string representation of a LwRest.
 *
 * @param rest a LwRest
 * @return string representation of a LwRest
 *
 * @public
 * @memberof LwRest
 */
GString *
lw_rest_to_string(LwRestPtr rest)
{
  GString *result = NULL;
  GList *iterator = NULL;
  GString *temp_parameter_string = NULL;

  result = g_string_new("RESTful Webservice: ");
  g_string_append(result, "url: ");

  for (iterator = rest->params; iterator != NULL;
      iterator = g_list_next(iterator))
    {
      temp_parameter_string = lw_parameter_to_string(
          (LwParameter *) iterator->data);
      g_string_append_printf(result, " parameter: %s,",
          temp_parameter_string->str);
      g_string_free(temp_parameter_string, TRUE);
    }

  return result;
}

/**
 * Creates a GET request URI for the given LwRest.
 *
 * @param rest a LwRest
 * @return string, that represents an GET request URI
 *
 * @public
 * @memberof LwRest
 */
gchar *
lw_rest_create_GET_request(LwRestPtr rest)
{
  /* TODO: strip illegal characters from the result URI */
  GString *result_string = NULL;
  GList *iterator = NULL;
  GString *temp_parameter_string = NULL;
  gchar *result = NULL;

  result_string = g_string_new(rest->url);
  g_string_append(result_string, "?");

  for (iterator = rest->params; iterator != NULL;
      iterator = g_list_next(iterator))
    {
      temp_parameter_string = lw_parameter_to_GET(
          (LwParameter *) iterator->data);
      if (g_list_next(iterator) != NULL)
        {
          /* TODO: maybe there are other separators */
          g_string_append_printf(result_string, "%s&",
              temp_parameter_string->str);
        }
      else
        {
          g_string_append(result_string, temp_parameter_string->str);
        }
      g_string_free(temp_parameter_string, TRUE);
    }
  result = result_string->str;
  g_string_free(result_string, FALSE);
  return result;
}

/**
 *
 * @param rest
 * @param with_parameters
 *
 * @private
 * @memberof LwRest
 */
lw_rest_free_helper(LwRestPtr *rest, gboolean with_parameters)
{
  if (rest != NULL && *rest != NULL)
    {
      if (with_parameters == TRUE)
        {
          g_list_free_full((*rest)->params, (gpointer) lw_parameter_free);
        }
      else
        {
          g_list_free((*rest)->params);
        }
      free(*rest);
      *rest = NULL;
    }
}

/**
 * Frees the memory allocated for the LwRest object.
 * Also it frees the memory allocated for added LwParameter objects.
 *
 * @param rest a LwRestPtr
 *
 * @public
 * @memberof LwRest
 */
void
lw_rest_free(LwRestPtr *rest)
{
  lw_rest_free_helper(rest, TRUE);
}

/**
 * Frees the memory allocated for the LwRest object.
 * Does not free the memory allocated for LwParameter objects.
 *
 * @warning LwParameter objects should be freed with lw_parameter_free() when no longer needed.
 *
 * @param rest a LwRestPtr
 *
 * @public
 * @memberof LwRest
 */
void
lw_rest_free_without_parameters(LwRestPtr *rest)
{
  lw_rest_free_helper(rest, FALSE);
}
