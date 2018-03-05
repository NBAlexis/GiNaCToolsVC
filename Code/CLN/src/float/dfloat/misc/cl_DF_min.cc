// min().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

namespace cln {

const cl_DF min (const cl_DF& x, const cl_DF& y)
{
	return (x <= y ? x : y);
}

}  // namespace cln
