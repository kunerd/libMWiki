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

typedef enum
{
  POST_REQUEST, GET_REQUEST
} LwRequestType;

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

  resource->raw_content = malloc(1);
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
lw_webresource_curl_write_callback(void *ptr, size_t size, size_t nmemb,
    void *data)
{
  /* TODO refactor for gchar usage */
  size_t realsize = size * nmemb;
  LwWebresource *mem = (LwWebresource *) data;

  mem->raw_content = realloc(mem->raw_content, mem->size + realsize + 1);
  if (mem->raw_content == NULL)
    {
      /* out of memory! */
      printf("not enough memory (realloc returned NULL)\n");
      exit(EXIT_FAILURE);
    }

  memcpy(&(mem->raw_content[mem->size]), ptr, realsize);
  mem->size += realsize;
  mem->raw_content[mem->size] = 0;

  return realsize;
}

void
lw_webresource_request(LwWebresource *resource, LwRest *rest, LwRequestType type)
{
  CURL *curl_handle = NULL;
  gchar *post_fields = NULL;
  gchar *get_url = NULL;

  /* TODO remove curl_global_init and cleanup here */
  curl_global_init(CURL_GLOBAL_ALL);

  curl_handle = curl_easy_init();

  resource = lw_webresource_new();
  if (resource == NULL)
    {
	  /* FIXME error handling */
      return;
    }

  switch (type)
    {

  case POST_REQUEST:
    {
      post_fields = lw_rest_create_POST_fields(rest);
      curl_easy_setopt(curl_handle, CURLOPT_URL, rest->url);
      curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, post_fields);
    }
    break;

  case GET_REQUEST:
    {
      get_url = lw_rest_create_GET_request(rest);
      curl_easy_setopt(curl_handle, CURLOPT_URL, get_url);
    }
    break;

  default:
	  /* FIXME error handling */
    return;
    }

  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION,
      lw_webresource_curl_write_callback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) resource);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, rest->user_agent);

  curl_easy_perform(curl_handle);
  curl_easy_cleanup(curl_handle);

  curl_global_cleanup();

  g_free(post_fields);
  g_free(get_url);

}

void
lw_webresource_get(LwWebresource *resource, LwRest *rest)
{
  lw_webresource_request(resource, rest, GET_REQUEST);
}

void
lw_webresource_post(LwWebresource *resource, LwRest *rest)
{
  lw_webresource_request(resource, rest, POST_REQUEST);
}

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

