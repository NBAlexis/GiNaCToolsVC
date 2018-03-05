// max().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/integer.h"


// Implementation.

namespace cln {

const cl_I max (const cl_I& x, const cl_I& y)
{
	return (x >= y ? x : y);
}

}  // namespace cln
