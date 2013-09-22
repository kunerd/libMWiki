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
#include "libmwiki.h"

#define USER_AGENT "libMWiki/1.1 (https://github.com/kunerd/libMWiki; qkunerd@gmail.com)"
#define API_URL "http://some.webservice.url.de"

/*
 * Create and destroy a LwMediawiki-Object. For memory leak detections.
 */START_TEST (test_LwMediaWiki_create)
	{
		LwMediaWiki *mw = NULL;

		mw = lw_mediawiki_new(API_URL);
		ck_assert(mw != NULL);
		lw_mediawiki_free(mw);
	}END_TEST

/*
 * Check default values.
 */START_TEST (test_LwMediaWiki_defaults)
	{
		LwMediaWiki *mw = NULL;

		mw = lw_mediawiki_new(API_URL);
		ck_assert_str_eq(mw->api_url, API_URL);
		ck_assert_str_eq(mw->user_agent, USER_AGENT);

		lw_mediawiki_free(mw);
	}END_TEST

Suite* lw_rest_suite(void) {
	Suite *suite = suite_create("LwMediaWiki");

	TCase *tcase = tcase_create("LwMediaWiki");
	tcase_add_test(tcase, test_LwMediaWiki_create);
	tcase_add_test(tcase, test_LwMediaWiki_defaults);

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
