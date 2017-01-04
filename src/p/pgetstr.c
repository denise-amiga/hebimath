/*
 * hebimath - arbitrary precision arithmetic library
 * See LICENSE file for copyright and license details
 */

#include "pcommon.h"

HEBI_API
size_t
hebi_pgetstr(
		char *restrict str,
		size_t len,
		hebi_packet *restrict w,
		size_t n,
		int base )
{
	const unsigned int flags = (unsigned int)base;
	const unsigned int ubase = flags & HEBI_STR_BASEMASK;

	char *start;
	char *end;
	char *ptr;
	int digit;
	int letterbase;
	unsigned int bits;      /* leading zero bits of ubase */
	MLIMB d;                /* ubase normalized for division */
	MLIMB v;                /* reciprocal estimate of d */
	MLIMB *wl;
	size_t nl;
	size_t rlen;

	ASSERT(n <= HEBI_PACKET_MAXLEN);
	ASSERT(2 <= ubase && ubase <= 62);

	/* setup pointers and result length */
	ptr = str;
	end = str + len - (len > 0);
	rlen = 0;

	/* write out optional radix prefix */
	if (flags & HEBI_STR_PREFIX) {
		if (ubase == 16) {
			if (LIKELY(ptr < end))
				*ptr++ = '0';
			if (LIKELY(ptr < end))
				*ptr++ = 'x';
			rlen += 2;
		} else if (ubase == 8) {
			if (LIKELY(ptr < end))
				*ptr++ = '0';
			rlen++;
		} else if (ubase == 2) {
			if (LIKELY(ptr < end))
				*ptr++ = '0';
			if (LIKELY(ptr < end))
				*ptr++ = 'b';
			rlen += 2;
		}
	}

	/* special case for zero-length input packet sequence */
	if (UNLIKELY(!n)) {
		if (LIKELY(!rlen || ubase != 8)) {
			if (LIKELY(ptr < end))
				*ptr++ = '0';
			rlen++;
		}
		if (LIKELY(len > 0))
			*ptr = '\0';
		return rlen;
	}

	/* determine lowercase or uppercase */
	letterbase = 'a' - 10;
	if (flags & HEBI_STR_UPPER)
		letterbase = 'A' - 10;

	/* compute reciprocal and normalized divisor */
	d = (MLIMB)ubase;
	bits = MLIMB_CLZ(d);
	d = d << bits;
	v = RECIPU_2x1(d);

	/*
	 * if we have no more space in output string, just consume
	 * digits in order to compute final result length
	 */
	if (UNLIKELY(ptr >= end)) {
		/* null-terminate output */
		if (len > 0)
			*ptr = '\0';

		/* consume digits */
		for ( ; n > 0; rlen++) {
			wl = MLIMB_PTR(w);
			nl = n * MLIMB_PER_PACKET;
			(void)PDIVREMRU_2x1(wl, wl, nl, bits, d, v);
			n = hebi_pnorm(w, n);
		}

		return rlen;
	}

	/*
	 * otherwise, compute and write character digits to string. wrap
	 * around in ring-buffer fashion if we run out of room: when the
	 * digits are reversed, the truncated string will then have the
	 * correct sequence of truncated digits
	 */
	start = ptr;
	do {
		for (ptr = start; ptr < end && n > 0; ptr++, rlen++) {
			wl = MLIMB_PTR(w);
			nl = n * MLIMB_PER_PACKET;
			digit = (int)PDIVREMRU_2x1(wl, wl, nl, bits, d, v);
			if (digit < 10)
				digit += '0';
			else if (ubase <= 36)
				digit += letterbase;
			else if (digit < 36)
				digit += 'A' - 10;
			else
				digit += 'a' - 36;
			*ptr = (char)digit;
			n = hebi_pnorm(w, n);
		}
	} while (UNLIKELY(n > 0));

	/* reverse the digits to arrive at a right-to-left ordered sequence */
	if (UNLIKELY(rlen >= len)) {
		for (end = ptr - 1; start < end; start++, end--)
			SWAP(char, *start, *end);
		start = ptr;
		ptr = str + len - 1;
	}

	*ptr = '\0';
	for (end = ptr - 1; start < end; start++, end--)
		SWAP(char, *start, *end);

	return rlen;
}
