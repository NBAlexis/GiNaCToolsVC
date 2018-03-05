// exp1().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "float/transcendental/cl_F_tran.h"
#include "float/cl_F.h"

namespace cln {

const cl_F exp1 (float_format_t f)
{
	floatformatcase((uintC)f
	,	return cl_SF_exp1();
	,	return cl_FF_exp1();
	,	return cl_DF_exp1();
	,	return exp1(len);
	);
}

}  // namespace cln
