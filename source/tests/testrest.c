/*
 *  Wikipedia Lookup - A third-party Pidgin plug-in which offers
 *  you the possibility to look up received and typed words on Wikipedia.
 *
 *  Copyright (C) 2011, 2012 Hendrik Kunert kunerd@users.sourceforge.net
 *
 *  This file is part of Wikipedia Lookup.
 *
 *  Wikipedia Lookup is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Wikipedia Lookup is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Wikipedia Lookup.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"
#include "rest.h"

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

/*
 * Create and destroy a LwRest-Object. For memory leak detections.
 */
void
test_LwRest_new_and_free()
{
  LwRestPtr rest = NULL;

  rest = lw_rest_new("http://some.webservice.url.de");
  CU_ASSERT_PTR_NOT_NULL(rest);
  lw_rest_free(&rest);
  CU_ASSERT_PTR_NULL(rest);
}

void
test_LwRest_free_without_parameters()
{
  LwRestPtr rest = NULL;
  LwParameter *parameter = NULL;

  rest = lw_rest_new("http://some.webservice.url.de");
  parameter = lw_parameter_new("parameter", "value");
  lw_rest_add_parameter(rest, parameter);

  lw_rest_free_without_parameters(&rest);

  lw_parameter_free(parameter);
  CU_ASSERT_PTR_NULL(rest);
}

void
test_LwRest_add_parameter_with_single_value()
{
  LwRestPtr rest = NULL;
  LwParameter *parameter = NULL;
  gchar *request = NULL;

  rest = lw_rest_new("http://webservice");
  parameter = lw_parameter_new("parameter", "value");

  lw_rest_add_parameter(rest, parameter);
  request = lw_rest_create_GET_request(rest);

  CU_ASSERT_STRING_EQUAL(request, "http://webservice?parameter=value");

  g_free(request);
  lw_rest_free(&rest);
}

void
test_LwRest_add_parameter_from_string_with_single_value()
{
  LwRestPtr rest = NULL;
  gchar *request = NULL;

  rest = lw_rest_new("http://webservice");
  lw_rest_add_parameter_from_string(rest, "parameter", "value", NULL);
  request = lw_rest_create_GET_request(rest);
  CU_ASSERT_STRING_EQUAL(request, "http://webservice?parameter=value");

  g_free(request);
  lw_rest_free(&rest);
}

void
test_LwRest_add_parameter_from_string_with_multiple_values()
{
  LwRestPtr rest = NULL;
  gchar *request = NULL;

  rest = lw_rest_new("http://webservice");
  lw_rest_add_parameter_from_string(rest, "parameter", "value1", "value2",
      "value3", NULL);
  request = lw_rest_create_GET_request(rest);
  CU_ASSERT_STRING_EQUAL(request,
      "http://webservice?parameter=value1|value2|value3");

  g_free(request);
  lw_rest_free(&rest);
}

void
test_LwRest_add_multiple_parameters_from_string()
{
  LwRestPtr rest = NULL;
  gchar *request = NULL;

  rest = lw_rest_new("http://webservice");
  lw_rest_add_parameter_from_string(rest, "parameter1", "value1", NULL);
  lw_rest_add_parameter_from_string(rest, "parameter2", "value1", "value2",
      NULL);

  request = lw_rest_create_GET_request(rest);
  CU_ASSERT_STRING_EQUAL(request,
      "http://webservice?parameter1=value1&parameter2=value1|value2");

  g_free(request);
  lw_rest_free(&rest);
}

void
test_LwRest_create_POST_fields_with_single_parameter()
{
  LwRestPtr rest = NULL;
  gchar *post_fields = NULL;

  rest = lw_rest_new("http://www.werbservice.de");
  lw_rest_add_parameter_from_string(rest, "parameter1", "value1",
      "value2", NULL);

  post_fields = lw_rest_create_POST_fields(rest);

  CU_ASSERT_STRING_EQUAL(post_fields, "parameter1=value1|value2");

  g_free(post_fields);
  lw_rest_free(&rest);
}

void
test_LwRest_create_POST_fields_with_multiple_parameter()
{
  LwRestPtr rest = NULL;
  gchar *post_fields = NULL;

  rest = lw_rest_new("http://www.werbservice.de");
  lw_rest_add_parameter_from_string(rest, "parameter1", "value1",
      "value2", NULL);
  lw_rest_add_parameter_from_string(rest, "parameter2", "value1",
      "value2", NULL);
  post_fields = lw_rest_create_POST_fields(rest);

  CU_ASSERT_STRING_EQUAL(post_fields,
      "parameter1=value1|value2&parameter2=value1|value2");

  g_free(post_fields);
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
  pSuite = CU_add_suite("LwRest", init_suite1, clean_suite1);
  if (NULL == pSuite)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suite */
  if ((NULL
      == CU_add_test(pSuite, "create and destroy a LwRest-Object",
          test_LwRest_new_and_free))
      || (NULL
          == CU_add_test(pSuite, "free LwRest without parameters",
              test_LwRest_free_without_parameters))
      || (NULL
          == CU_add_test(pSuite, "add parameter with single value",
              test_LwRest_add_parameter_with_single_value))
      || (NULL
          == CU_add_test(pSuite, "add parameter from string with single value",
              test_LwRest_add_parameter_from_string_with_single_value))
      || (NULL
          == CU_add_test(pSuite,
              "add parameter from string with multiple values",
              test_LwRest_add_parameter_from_string_with_multiple_values))
      || (NULL
          == CU_add_test(pSuite, "add multiple parameters from string",
              test_LwRest_add_multiple_parameters_from_string))
      || (NULL
          == CU_add_test(pSuite, "create POST fields with single parameter",
              test_LwRest_create_POST_fields_with_single_parameter))
      || (NULL
          == CU_add_test(pSuite, "create POST fields with multiple parameters", test_LwRest_create_POST_fields_with_multiple_parameter)))
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

