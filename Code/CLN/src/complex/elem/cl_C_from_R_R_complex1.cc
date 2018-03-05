// complex().

// General includes.
#include "cln_private.h"

// Specification.
#include "complex/cl_C.h"


// Implementation.

#include "real/cl_R.h"

namespace cln {

const cl_N complex (const cl_R& a, const cl_R& b)
{
// Methode:
// Falls b=0, nur a. sonst komplexe Zahl erzeugen.
	if (eq(b,0))
		return a;
	else
		return allocate_complex(a,b);
}

}  // namespace cln
