// atan().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/real.h"


// Implementation.

namespace cln {

const cl_R atan (const cl_R& x)
{
// Methode:
// arctan(x) = arctan(X=1,Y=x).
	return atan(1,x);
}

}  // namespace cln
