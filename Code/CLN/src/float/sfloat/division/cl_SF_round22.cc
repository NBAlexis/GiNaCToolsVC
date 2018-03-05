// round2().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "float/sfloat/cl_SF.h"

namespace cln {

const cl_SF_div_t round2 (const cl_SF& x, const cl_SF& y)
{
// Methode:
// (q,r) := round(x/y). Liefere q und x-y*q = y*r.
	var cl_SF_div_t q_r = round2(x/y);
	var cl_I& q = q_r.quotient;
	var cl_SF& r = q_r.remainder;
	return cl_SF_div_t(q,y*r);
}

}  // namespace cln
