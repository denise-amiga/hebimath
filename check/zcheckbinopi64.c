/*
 * hebimath - arbitrary precision arithmetic library
 * See LICENSE file for copyright and license details
 */

#include "check.h"

void
zcheckbinopi64(
		void (*f)(hebi_zptr, hebi_zsrcptr, int64_t),
		const char* op,
		int flags )
{
	hebi_z r, a;
	int64_t b;

	hebi_zinit(r);
	hebi_zinit(a);

	if (check_max_perm <= 0)
		check_max_perm = 256;
	check_max_iter = check_max_perm;

	for (check_iter = check_start_iter;
			check_iter < check_max_iter;
			check_iter++) {
		/* generate test inputs */
		zpermutation(check_iter, check_max_perm, 1, a);
		if ((flags & LHS_NONZERO) && hebi_zzero(a))
			continue;

		/* first pass: read-only inputs */
		for (check_pass = 0; check_pass < check_num_i64values; check_pass++) {
			b = check_i64values[check_pass];
			if ((flags & RHS_NONZERO) && !b)
				continue;
			(*f)(r, a, b);
			zcheckbc(r, "%Z %s %lld", a, op, (long long)b);
		}

		/* second pass: inplace operation on lhs input */
		for ( ; check_pass < 2 * check_num_i64values; check_pass++) {
			b = check_i64values[check_pass - check_num_i64values];
			if ((flags & RHS_NONZERO) && !b)
				continue;
			hebi_zset(r, a);
			(*f)(a, a, b);
			zcheckbc(a, "%Z %s %lld", r, op, (long long)b);
			if (hebi_zzero(a))
				hebi_zset(a, r);
		}
	}

	hebi_zdestroy(r);
	hebi_zdestroy(a);
}
