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
#include <stddef.h>

/* Microsoft's C strcpy_s.
 * https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strcpy-s-wcscpy-s-mbscpy-s?view=msvc-170
 *
 * This implementation isn't fully compliant. It doesn't fill dst with 0xFE when
 * debugging and it doesn't use C11 Annex K's rsize_t type.
 */
int
strcpy_s(char *dst, size_t size, const char *src)
{
	size_t i;

	if (dst == NULL)
		return ((errno = EINVAL));
	if (src == NULL) {
		/*
		 * XXX:
		 * Microsoft's documentation is ambiguous.
		 *
		 * How does Microsoft handle size == 0 when src is NULL?
		 * Do they return ERANGE?
		 *
		 * How does Microsoft handle size == 0 when src is non-NULL?
		 * Do they write a '\0' to *dst anyway?
		 */
		if (size > 0)
			*dst = '\0';
		return ((errno = EINVAL));
	}

	for (i = 0;; i++) {
		if (i >= size) {
			if (size > 0)
				*dst = '\0';
			return ((errno = ERANGE));
		}
		dst[i] = src[i];
		if (src[i] == '\0')
			return (0);
	}
	/* NOTREACHED */
}
