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

#include "webresource.h"

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

LwWebresource *
lw_webresource_new()
{
  LwWebresource *resource = NULL;

  resource = malloc(sizeof(LwWebresource));
  if (resource == NULL)
    {
      /* TODO: log or error code */
      return NULL;
    }

  resource->raw_content = g_malloc(sizeof(gchar));
  if (resource->raw_content == NULL)
    {
      /* TODO: log or error code */
      lw_webresource_free(&resource);
      return NULL;
    }

  resource->size = 0;

  return resource;
}

size_t
lw_webresource_curl_write_callback(LwWebresource *resource, size_t size, size_t nmemb,
    void *data)
{
  /* TODO refactor for gchar usage */
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *) data;

  resource->raw_content = realloc(resource->raw_content, resource->size + realsize + sizeof(gchar));
  if (resource->raw_content == NULL)
    {
      /* TODO log and error handling, out of memory! */
      printf("not enough memory (realloc returned NULL)\n");
      exit(EXIT_FAILURE);
    }

  memcpy(&(resource->raw_content[resource->size]), resource, realsize);
  resource->size += realsize;
  resource->raw_content[resource->size] = 0;

  return realsize;
}

LwWebresource *
lw_webresource_get(LwRest *rest)
{
  /* TODO refactor, remove curl_global_init and cleanup */
  CURL *curl_handle = NULL;
  LwWebresource *resource = NULL;

  resource = lw_webresource_new();
  if(resource == NULL)
    {
      return NULL;
    }

  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();

  curl_easy_setopt(curl_handle, CURLOPT_URL, rest->url);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION,
      lw_webresource_curl_write_callback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) &(resource));
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, rest->user_agent);

  curl_easy_perform(curl_handle);
  curl_easy_cleanup(curl_handle);

  curl_global_cleanup();

  return resource;
}

// implement that shit
//LwWebresource *
//lw_webresource_post(LwRestPtr rest);

void
lw_webresource_free(LwWebresource **resource)
{
  g_free((*resource)->raw_content);
  if (resource != NULL && *resource != NULL)
    {
      free(*resource);
      *resource = NULL;
    }
}

