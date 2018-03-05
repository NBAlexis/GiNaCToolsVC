// numerator().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/rational.h"


// Implementation.
#ifndef _MSC_VER
// why twice implemented?
#define numerator inline_numerator
#include "rational/cl_RA.h"
#undef numerator

namespace cln {

const cl_I numerator (const cl_RA& r)
{
	return inline_numerator(r);
}

}  // namespace cln
#endif