// minusp().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/rational.h"


// Implementation.
#ifndef _MSC_VER
// why twice implemented?
#define minusp minusp_inline
#include "rational/cl_RA.h"
#undef minusp

namespace cln {

bool CL_FLATTEN minusp (const cl_RA& x)
{
	return minusp_inline(x);
}

}  // namespace cln
#endif