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

#include <string.h>

/* This strlcat is convoluted and hasn't been tested yet. */
size_t
strlcat(char *dst, const char *src, size_t dstlen)
{
	size_t i;

	i = dstlen > 0 ? strlen(dst) : 0;
	for (;; i++) {
		if (i >= dstlen) {
			/*
			 * If i > len, the destination string was larger than
			 * len.
			 */
			if (i == dstlen)
				dst[dstlen-1] = '\0';
			return (i + strlen(src));
		}
		dst[i] = *src++;
		if (*src == '\0')
			return (i);
	}

	/* NOTREACHED */
}
