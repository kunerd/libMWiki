#include "libmwiki.h"

#include <stdlib.h>

#define DEFAULT_USER_AGENT "libMWiki/1.1 (https://github.com/kunerd/libMWiki; qkunerd@gmail.com)"

/* FIXME: correct version number from configuration */
const LwMediaWiki MEDIAWIKI_DEFAULT = {
	"",
	DEFAULT_USER_AGENT
};

LwMediaWiki*
lw_mediawiki_new(const gchar *api_url) {
	LwMediaWiki *mw = NULL;

	mw = malloc(sizeof(LwMediaWiki));
	if (mw == NULL ) {
		/* TODO: log or error code */
		return NULL ;
	}

	*mw = MEDIAWIKI_DEFAULT;

	mw->api_url = api_url;

	return mw;
}

void lw_mediawiki_free(LwMediaWiki *mw) {
	if (mw != NULL ) {
		free(mw);
	}
}
