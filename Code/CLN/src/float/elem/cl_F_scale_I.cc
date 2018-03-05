// scale_float().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cln/sfloat.h"
#include "cln/ffloat.h"
#include "cln/dfloat.h"
#include "cln/lfloat.h"
#include "float/cl_F.h"

namespace cln {

const cl_F scale_float (const cl_F& x, const cl_I& delta)
{
	floatcase(x
	,	return scale_float(x,delta);
	,	return scale_float(x,delta);
	,	return scale_float(x,delta);
	,	return scale_float(x,delta);
	);
}

}  // namespace cln
