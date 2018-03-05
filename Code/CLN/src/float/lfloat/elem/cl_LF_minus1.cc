// minus1().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "float/lfloat/cl_LF.h"

namespace cln {

ALL_cl_LF_OPERATIONS_SAME_PRECISION()

const cl_LF minus1 (const cl_LF& x)
{
	return x + cl_I_to_LF(cl_I(-1),TheLfloat(x)->len);
}

}  // namespace cln
