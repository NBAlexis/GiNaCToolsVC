// minusp().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/integer.h"


// Implementation.
#ifndef _MSC_VER
// why twice implemented?
#define minusp inline_minusp
#include "integer/cl_I.h"
#undef minusp

namespace cln {

bool minusp (const cl_I& x)
{
	return inline_minusp(x);
}

}  // namespace cln
#endif
