// min().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

namespace cln {

const cl_SF min (const cl_SF& x, const cl_SF& y)
{
	return (x <= y ? x : y);
}

}  // namespace cln
