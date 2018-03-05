// zerop().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "float/sfloat/cl_SF.h"

namespace cln {

CL_INLINE bool CL_INLINE_DECL(zerop) (const cl_SF& x)
{
	return x.word == make_SF_word(0,0,0);
}

}  // namespace cln
