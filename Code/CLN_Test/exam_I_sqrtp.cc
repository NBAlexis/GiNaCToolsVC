#include "mainheader.h"

#define floor(a,b)  ((a) / (b))

#define ASSERT4SQRT(expr,a,b,c,d)  \
  if (!(expr)) {					\
	std::cerr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	std::cerr << #a" = " << a << endl;			\
	std::cerr << #b" = " << b << endl;			\
	std::cerr << #c" = " << c << endl;			\
	std::cerr << #d" = " << d << endl;			\
	++er;					\
  } else { ++done; }

void test_sqrtp (int &er, int &done)
{
	// As our algorithm for sqrtp does pre-filtering mod (64*63*65*11),
	// we check that no square is thrown away by this pre-filtering.
	{
		uintL a, b, c, d;
		for (a = 0; a <= floor(64,2); a++)
		  for (b = 0; b <= floor(63,2); b++)
		    for (c = 0; c <= floor(65,2); c++)
		      for (d = 0; d <= floor(11,2); d++) {
			// Produce a number x == a mod 64, x == b mod 63,
			// x == c mod 65, x == d mod 11, and square it.
			uintL x = 1306305*a + 1967680*b + 133056*c + 2358720*d;
			x = x % 2882880; // not strictly necessary
			cl_I w;
            ASSERT4SQRT(sqrtp(expt_pos(cl_I(x),cl_I(2)),&w) && w == x, a,b,c,d);
		}
	}
}
