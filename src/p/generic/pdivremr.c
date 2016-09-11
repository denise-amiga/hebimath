/*
 * hebimath - arbitrary precision arithmetic library
 * See LICENSE file for copyright and license details
 */

#include "generic.h"

HEBI_API
size_t
PDIVREMR(
		hebi_packet *restrict q,
		MLIMB *restrict ul,
		const MLIMB *restrict dl,
		MLIMB v,
		size_t m,
		size_t n )
{
	MLIMB *restrict ql;
	MLIMB qhat, p1, p0, u1, u0, c1, c0;
	DLIMB p;
	size_t i, j;

	ASSERT(m >= n);
	ASSERT(n > 2);
	ASSERT((dl[n-1] & MLIMB_HIGH_BIT) != 0);

	/*
	 * ensure initial top two limbs of dividend are less than top two
	 * words of divisor, adjust dividend and quotient if necessary
	 */
	m -= n;
	n -= 2;
	j = m;

	u1 = ul[j+n+1];
	u0 = ul[j+n+0];
	ql = MLIMB_PTR(q);

	/* TODO: need to compare with entire divisor */
	if (UNLIKELY(u1 > dl[n+1] || (u1 == dl[n+1] && u0 >= dl[n+0]))) {
		ASSERT(!"NOT IMPLEMENTED");
		u1 -= dl[n+1] + (u0 < dl[n+1]);
		u0 -= dl[n+0];
		ul[j+n+1] = u1;
		ul[j+n+0] = u0;
		ql[m++] = 1;
	}

	/* clear top of last packet in quotient */
	if ((i = m % MLIMB_PER_PACKET) != 0)
		for ( ; i < MLIMB_PER_PACKET; i++)
			ql[m++] = 0;

	/* perform multi-word 3x2 reciprocal division */
	while (j--) {
		/* TODO: do we need to handle this case? */
		ASSERT(u1 != dl[n+1] || u0 != dl[n+0]);

		/* estimate quotient limb */
		DIVREMRU_3x2(&qhat, &u1, &u0, ul[j+n], dl[n+1], dl[n+0], v);

		/* multiply and subtract to compute remainder */
		c1 = 0;
		for (i = 0; i < n; i++) {
			p = (DLIMB)qhat * dl[i];
			p0 = (MLIMB)(p & MLIMB_MAX);
			p1 = (MLIMB)(p >> MLIMB_BIT);
			p0 = p0 + c1;
			c1 = p1 + (p0 < c1);
			c0 = ul[j+i];
			p0 = c0 - p0;
			c1 = c1 + (c0 < p0);
			ul[j+i] = p0;
		}
		c0 = u0 < c1;
		u0 = u0 - c1;
		c1 = u1 < c0;
		u1 = u1 - c0;
		ul[j+n] = u0;

		/* adjust if quotient estimate was too large */
		if (UNLIKELY(c1)) {
			c1 = 0;
			for (i = 0; i < n + 1; i++) {
				c0 = ul[j+i] + dl[i] + c1;
				c1 = (c0 < ul[j+i]) || (c0 == ul[j+i] && c1);
				ul[j+i] = c0;
			}
			u1 = u1 + dl[n+1] + c1;
			qhat--;
		}

		ql[j] = qhat;
	}

	ul[++n] = u1;

	/* clear top of last packet in remainder */
	if ((i = ++n % MLIMB_PER_PACKET) != 0)
		for ( ; i < MLIMB_PER_PACKET; i++)
			ul[n++] = 0;

	/* length of quotient in packets*/
	return m / MLIMB_PER_PACKET;
}