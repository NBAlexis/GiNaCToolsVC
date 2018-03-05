// minusp().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "float/sfloat/cl_SF.h"

namespace cln {

CL_INLINE bool CL_INLINE_DECL(minusp) (const cl_SF& x)
{
	return (x.word & bit(SF_sign_shift)) != 0;
}

}  // namespace cln
