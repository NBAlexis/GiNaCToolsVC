// eulerconst().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "float/cl_F.h"
#include "float/transcendental/cl_F_tran.h"

namespace cln {

const cl_F eulerconst (float_format_t f)
{
	floatformatcase((uintC)f
	,	return cl_SF_eulerconst();
	,	return cl_FF_eulerconst();
	,	return cl_DF_eulerconst();
	,	return eulerconst(len);
	);
}

}  // namespace cln
