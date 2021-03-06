// floor2().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "float/dfloat/cl_DF.h"

namespace cln {

const cl_DF_div_t floor2 (const cl_DF& x, const cl_DF& y)
{
// Methode:
// (q,r) := floor(x/y). Liefere q und x-y*q = y*r.
	var cl_DF_div_t q_r = floor2(x/y);
	var cl_I& q = q_r.quotient;
	var cl_DF& r = q_r.remainder;
	return cl_DF_div_t(q,y*r);
}

}  // namespace cln
