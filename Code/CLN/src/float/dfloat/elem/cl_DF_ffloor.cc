// ffloor().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "float/dfloat/cl_DF.h"

#include "base/cl_inline.h"
#include "float/dfloat/elem/cl_DF_minusp.cc"

namespace cln {

const cl_DF CL_FLATTEN ffloor (const cl_DF& x)
{
	if (minusp_inline(x))
		return futruncate(x);
	else
		return ftruncate(x);
}

}  // namespace cln
