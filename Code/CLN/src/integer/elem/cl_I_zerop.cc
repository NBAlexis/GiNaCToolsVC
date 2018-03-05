// zerop().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/integer.h"


// Implementation.
#ifndef _MSC_VER
// why twice implemented?
#define zerop inline_zerop
#include "integer/cl_I.h"
#undef zerop

namespace cln {

bool zerop (const cl_I& x)
{
	return inline_zerop(x);
}

}  // namespace cln
#endif