// denominator().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/rational.h"


// Implementation.
#ifndef _MSC_VER
// why twice implemented?
#define denominator inline_denominator
#include "rational/cl_RA.h"
#undef denominator

namespace cln {

const cl_I denominator (const cl_RA& r)
{
	return inline_denominator(r);
}

}  // namespace cln
#endif