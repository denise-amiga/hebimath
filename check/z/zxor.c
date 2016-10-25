/*
 * hebimath - arbitrary precision arithmetic library
 * See LICENSE file for copyright and license details
 */

#include "../check.h"

static const char xor_script[] =
"define xor(a, b) {\n"
"	auto r, s, t, u, x\n"
"	s = 1\n"
"	if (!(a < 0 && b < 0) && (a < 0 || b < 0))\n"
"		s = -1\n"
"	if (a < 0)\n"
"		a = -a\n"
"	if (b < 0)\n"
"		b = -b\n"
"	r = 0\n"
"	x = 1\n"
"	while (a || b) {\n"
"		t = a % 2\n"
"		a /= 2\n"
"		u = b % 2\n"
"		b /= 2\n"
"		if (!(t && u) && (t || u))\n"
"			r += x\n"
"		x *= 2\n"
"	}\n"
"	return r * s\n"
"}\n";

int
main(int argc, char *argv[])
{
	checkinit(argc, argv);
	bcwrite(xor_script);
	zcheckbinop(hebi_zxor, "xor(%Z, %Z)", 0);
	return 0;
}
