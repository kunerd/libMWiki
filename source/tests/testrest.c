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

#include <check.h>

#include "rest.h"

/*
 * Create and destroy a LwRest-Object. For memory leak detections.
 */
START_TEST (test_LwWebresource_get)
	{
		LwRest *rest = NULL;

		rest = lw_rest_new("http://some.webservice.url.de");
		ck_assert(rest != NULL);
		lw_rest_free(&rest);
		ck_assert(rest == NULL);
	}END_TEST

START_TEST (test_LwRest_free_without_parameters)
	{
		LwRest *rest = NULL;
		LwParameter *parameter = NULL;

		rest = lw_rest_new("http://some.webservice.url.de");
		parameter = lw_parameter_new("parameter", "value");
		lw_rest_add_parameter(rest, parameter);

		lw_rest_free_without_parameters(&rest);

		lw_parameter_free(parameter);

		ck_assert(rest == NULL);
	}END_TEST

START_TEST (test_LwRest_add_parameter_with_single_value)
	{
		LwRest *rest = NULL;
		LwParameter *parameter = NULL;
		gchar *request = NULL;

		rest = lw_rest_new("http://webservice");
		parameter = lw_parameter_new("parameter", "value");

		lw_rest_add_parameter(rest, parameter);
		request = lw_rest_create_GET_request(rest);

		ck_assert_str_eq(request, "http://webservice?parameter=value");

		g_free(request);
		lw_rest_free(&rest);
	}END_TEST

START_TEST (test_LwRest_add_parameter_from_string_with_single_value)
	{
		LwRest *rest = NULL;
		gchar *request = NULL;

		rest = lw_rest_new("http://webservice");
		lw_rest_add_parameter_from_string(rest, "parameter", "value", NULL );
		request = lw_rest_create_GET_request(rest);
		ck_assert_str_eq(request, "http://webservice?parameter=value");

		g_free(request);
		lw_rest_free(&rest);
	}END_TEST

START_TEST (test_LwRest_add_parameter_from_string_with_multiple_values)
	{
		LwRest *rest = NULL;
		gchar *request = NULL;

		rest = lw_rest_new("http://webservice");
		lw_rest_add_parameter_from_string(rest, "parameter", "value1", "value2",
				"value3", NULL );
		request = lw_rest_create_GET_request(rest);
		ck_assert_str_eq(request,
				"http://webservice?parameter=value1|value2|value3");

		g_free(request);
		lw_rest_free(&rest);
	}END_TEST

START_TEST (test_LwRest_add_multiple_parameters_from_string)
	{
		LwRest *rest = NULL;
		gchar *request = NULL;

		rest = lw_rest_new("http://webservice");
		lw_rest_add_parameter_from_string(rest, "parameter1", "value1", NULL );
		lw_rest_add_parameter_from_string(rest, "parameter2", "value1",
				"value2", NULL );

		request = lw_rest_create_GET_request(rest);
		ck_assert_str_eq(request,
				"http://webservice?parameter1=value1&parameter2=value1|value2");

		g_free(request);
		lw_rest_free(&rest);
	}END_TEST

START_TEST (test_LwRest_create_POST_fields_with_single_parameter)
	{
		LwRest *rest = NULL;
		gchar *post_fields = NULL;

		rest = lw_rest_new("http://www.werbservice.de");
		lw_rest_add_parameter_from_string(rest, "parameter1", "value1",
				"value2", NULL );

		post_fields = lw_rest_create_POST_fields(rest);

		ck_assert_str_eq(post_fields, "parameter1=value1|value2");

		g_free(post_fields);
		lw_rest_free(&rest);
	}END_TEST

START_TEST (test_LwRest_create_POST_fields_with_multiple_parameter)
	{
		LwRest *rest = NULL;
		gchar *post_fields = NULL;

		rest = lw_rest_new("http://www.werbservice.de");
		lw_rest_add_parameter_from_string(rest, "parameter1", "value1",
				"value2", NULL );
		lw_rest_add_parameter_from_string(rest, "parameter2", "value1",
				"value2", NULL );
		post_fields = lw_rest_create_POST_fields(rest);

		ck_assert_str_eq(post_fields,
				"parameter1=value1|value2&parameter2=value1|value2");

		g_free(post_fields);
		lw_rest_free(&rest);
	}END_TEST

START_TEST (test_LwRest_create_GET_request_without_parameter)
	{
		LwRest *rest = NULL;
		gchar *get_request = NULL;

		rest = lw_rest_new("http://www.webservice.de");
		get_request = lw_rest_create_GET_request(rest);

		ck_assert_str_eq(get_request, "http://www.webservice.de");

		g_free(get_request);
		lw_rest_free(&rest);
	}END_TEST

START_TEST (test_LwRest_create_POST_fields_without_parameter)
	{
		LwRest *rest = NULL;
		gchar *post_fields;

		rest = lw_rest_new("http://www.webservice.de");
		post_fields = lw_rest_create_POST_fields(rest);

		ck_assert_str_eq(post_fields, "");

		g_free(post_fields);
		lw_rest_free(&rest);
	}END_TEST

Suite* lw_rest_suite(void) {
	Suite *suite = suite_create("LwRest");

	TCase *tcase = tcase_create("LwRest");
	tcase_add_test(tcase, test_LwWebresource_get);
	tcase_add_test(tcase, test_LwRest_free_without_parameters);
	tcase_add_test(tcase, test_LwRest_add_parameter_with_single_value);
	tcase_add_test(tcase,
			test_LwRest_add_parameter_from_string_with_single_value);
	tcase_add_test(tcase,
			test_LwRest_add_parameter_from_string_with_multiple_values);
	tcase_add_test(tcase, test_LwRest_add_multiple_parameters_from_string);
	tcase_add_test(tcase, test_LwRest_create_POST_fields_with_single_parameter);
	tcase_add_test(tcase,
			test_LwRest_create_POST_fields_with_multiple_parameter);
	tcase_add_test(tcase, test_LwRest_create_GET_request_without_parameter);
	tcase_add_test(tcase, test_LwRest_create_POST_fields_without_parameter);

	suite_add_tcase(suite, tcase);
	return suite;
}

int main(int argc, char *argv[]) {
	int number_failed;
	Suite *suite = lw_rest_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_NORMAL);
	number_failed = srunner_ntests_failed(runner);
	srunner_free(runner);
	return number_failed;
}
