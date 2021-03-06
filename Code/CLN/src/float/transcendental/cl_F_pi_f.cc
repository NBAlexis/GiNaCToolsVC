// pi().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "float/cl_F.h"
#include "float/transcendental/cl_F_tran.h"

namespace cln {

const cl_F pi (float_format_t f)
{
	floatformatcase((uintC)f
	,	return cl_SF_pi();
	,	return cl_FF_pi();
	,	return cl_DF_pi();
	,	return pi(len);
	);
}

}  // namespace cln
