// minusp().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "float/lfloat/cl_LF.h"

namespace cln {

CL_INLINE bool CL_INLINE_DECL(minusp) (const cl_LF& x)
{
	return -TheLfloat(x)->sign;
}

}  // namespace cln
