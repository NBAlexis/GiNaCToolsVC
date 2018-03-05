// zerop().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/rational.h"


// Implementation.
#ifndef _MSC_VER
// why twice implemented?
#define zerop inline_zerop
#include "rational/cl_RA.h"
#undef zerop

namespace cln {

bool zerop (const cl_RA& x)
{
	return inline_zerop(x);
}

}  // namespace cln
#endif