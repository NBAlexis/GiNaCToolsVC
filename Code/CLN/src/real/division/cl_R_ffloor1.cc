// ffloor().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "real/cl_R.h"
#include "rational/cl_RA.h"
#include "cln/integer.h"
#include "cln/sfloat.h"
#include "cln/ffloat.h"
#include "cln/dfloat.h"
#include "cln/lfloat.h"

namespace cln {

const cl_F ffloor (const cl_R& x)
{
	realcase6(x
	,	return cl_float(x);
	,	var const cl_I& a = numerator(x);
		var const cl_I& b = denominator(x);
		return cl_float(floor1(a,b));
	,	return ffloor(x);
	,	return ffloor(x);
	,	return ffloor(x);
	,	return ffloor(x);
	);
}

}  // namespace cln
