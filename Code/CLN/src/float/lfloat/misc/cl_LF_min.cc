// min().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

namespace cln {

const cl_LF min (const cl_LF& x, const cl_LF& y)
{
	return (x <= y ? x : y);
}

}  // namespace cln
