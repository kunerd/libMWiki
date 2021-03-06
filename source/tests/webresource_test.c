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
#include "webresource.h"

#define ENDPOINT_URL "http://en.wikipedia.org/w/api.php"
#define ACTION_PARAM "action"
#define ACTION_VALUE "parse"
#define FORMAT_PARAM "format"
#define FORMAT_VALUE "xml"
#define TEXT_PARAM "text"
#define TEXT_VALUE "test"

START_TEST (test_LwWebresource_create_and_destroy)
	{
		LwWebresource *resource = NULL;

		resource = lw_webresource_new();
		ck_assert(resource != NULL);

		lw_webresource_free(&resource);
		ck_assert(resource == NULL);
	}END_TEST

Suite* lw_rest_suite(void) {
	Suite *suite = suite_create("LwWebresource");

	TCase *tcase = tcase_create("LwWebresource");
	tcase_add_test(tcase, test_LwWebresource_create_and_destroy);

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

