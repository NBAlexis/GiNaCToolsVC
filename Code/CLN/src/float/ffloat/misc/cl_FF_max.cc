// max().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

namespace cln {

const cl_FF max (const cl_FF& x, const cl_FF& y)
{
	return (x >= y ? x : y);
}

}  // namespace cln
