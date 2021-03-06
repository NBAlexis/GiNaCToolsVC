// cl_float().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "float/cl_F.h"
#include "float/sfloat/cl_SF.h"
#include "float/ffloat/cl_FF.h"
#include "float/dfloat/cl_DF.h"
#include "float/lfloat/cl_LF.h"

namespace cln {

const cl_F cl_float (const cl_RA& x)
{
	floatformatcase(default_float_format
	,	return cl_RA_to_SF(x);
	,	return cl_RA_to_FF(x);
	,	return cl_RA_to_DF(x);
	,	return cl_RA_to_LF(x,len);
	);
}

}  // namespace cln
