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
  rest = lw_rest_new("http://de.wikipedia.org/w/api.php");
  lw_rest_add_parameter_from_string(rest, "action", "sitematrix", NULL);
  lw_rest_add_parameter_from_string(rest, "format", "xml", NULL);

  resource = lw_webresource_get(rest);

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
      || (NULL == CU_add_test(pSuite, "get request", test_LwWebresource_get)))
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

