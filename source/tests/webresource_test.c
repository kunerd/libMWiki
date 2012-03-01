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

#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"
#include "rest.h"
#include "webresource.h"


#define ENDPOINT_URL "http://en.wikipedia.org/w/api.php"
#define ACTION_PARAM "action"
#define ACTION_VALUE "parse"
#define FORMAT_PARAM "format"
#define FORMAT_VALUE "xml"
#define TEXT_PARAM "text"
#define TEXT_VALUE "test"

#define EXPECTED_RESULT "<?xml version=\"1.0\"?><api><parse title=\"API\" displaytitle=\"API\"><text xml:space=\"preserve\">&lt;p&gt;test&lt;/p&gt;\n\
\n\
\n\
&lt;!-- \n\
NewPP limit report\n\
Preprocessor node count: 1/1000000\n\
Post-expand include size: 0/2048000 bytes\n\
Template argument size: 0/2048000 bytes\n\
Expensive parser function count: 0/500\n\
--&gt;\n\
</text><langlinks /><categories /><links /><templates /><images /><externallinks /><sections /></parse></api>"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int
init_suite1(void)
{
  if (NULL == (temp_file = fopen("temp.txt", "w+")))
    {
      return -1;
    }
  else
    {
      return 0;
    }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int
clean_suite1(void)
{
  if (0 != fclose(temp_file))
    {
      return -1;
    }
  else
    {
      temp_file = NULL;
      return 0;
    }
}

void
test_LwWebresource_create_and_destroy()
{
  LwWebresource *resource = NULL;

  resource = lw_webresource_new();
  CU_ASSERT_PTR_NOT_NULL(resource);

  lw_webresource_free(&resource);
  CU_ASSERT_PTR_NULL(resource);
}

void
test_LwWebresource_get()
{
  LwRest *rest = NULL;
  LwWebresource *resource = NULL;

  /* TODO don't make any change actions, because this is the real Wikipedia API */
  rest = lw_rest_new(ENDPOINT_URL);
  lw_rest_add_parameter_from_string(rest, ACTION_PARAM, ACTION_VALUE, NULL);
  lw_rest_add_parameter_from_string(rest, FORMAT_PARAM, FORMAT_VALUE, NULL);
  lw_rest_add_parameter_from_string(rest, TEXT_PARAM, TEXT_VALUE, NULL);

  resource = lw_webresource_get(rest);
  CU_ASSERT_STRING_EQUAL(resource->raw_content, EXPECTED_RESULT);

  lw_webresource_free(&resource);
  lw_rest_free(&rest);
}

void
test_LwWebresource_post()
{
  LwRest *rest = NULL;
  LwWebresource *resource = NULL;

  /* TODO don't make any change actions, because this is the real Wikipedia API */
  rest = lw_rest_new(ENDPOINT_URL);
  lw_rest_add_parameter_from_string(rest, ACTION_PARAM, ACTION_VALUE, NULL);
  lw_rest_add_parameter_from_string(rest, FORMAT_PARAM, FORMAT_VALUE, NULL);
  lw_rest_add_parameter_from_string(rest, TEXT_PARAM, TEXT_VALUE, NULL);

  resource = lw_webresource_post(rest);
  CU_ASSERT_STRING_EQUAL(resource->raw_content, EXPECTED_RESULT);

  lw_webresource_free(&resource);
  lw_rest_free(&rest);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int
main()
{
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("LwWebresource", init_suite1, clean_suite1);
  if (NULL == pSuite)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suite */
  if ((NULL
      == CU_add_test(pSuite, "create and destroy LwWebresource object",
          test_LwWebresource_create_and_destroy))
      || (NULL == CU_add_test(pSuite, "get request", test_LwWebresource_get))
      || (NULL == CU_add_test(pSuite, "post reuqest", test_LwWebresource_post)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

