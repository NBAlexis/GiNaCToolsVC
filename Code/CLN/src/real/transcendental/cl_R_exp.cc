// exp().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cln/float.h"
#include "real/cl_R.h"

namespace cln {

const cl_R exp (const cl_R& x)
{
// Methode:
// x rational -> bei x=0 1 als Ergebnis, sonst x in Float umwandeln.
// x Float -> bekannt.

	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		if (zerop(x)) // x=0 -> 1 als Ergebnis
			return 1;
		return exp(cl_float(x)); // sonst in Float umwandeln
	} else {
		DeclareType(cl_F,x);
		return exp(x);
	}
}

}  // namespace cln
