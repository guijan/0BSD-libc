/*
 * Copyright (c) 2022 Guilherme Janczak <guilherme.janczak@yandex.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <errno.h>
#include <stdlib.h>

/* https://man.netbsd.org/reallocarr.3 */
int
reallocarr(void *_dst, size_t nmemb, size_t size)
{
	void **dst = _dst;
	void *tmp;
	size_t result;
	int errnum;
	int rval;
	errnum = errno;
	rval = 0;

	result = nmemb * size;
	if (nmemb != 0 && result / nmemb != size) {
		/*
		 * NetBSD uses its EOVERFLOW for this, but it's not standard, so
		 * I'm using ERANGE. NetBSD doesn't document what it does to
		 * errno exactly, so this is still valid according to the man
		 * page.
		 */
		rval = ERANGE;
		goto end;
	}
	if (result == 0)
		result = 1;

	if ((tmp = realloc(*dst, result)) == NULL) {
		rval = errno;
		goto end;
	}

	*dst = tmp;
end:
	errno = errnum;
	return rval;
}
