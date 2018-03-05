// class cl_composite_condition.

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/modinteger.h"


// Implementation.

#include "cln/io.h"
#include "cln/integer_io.h"

namespace cln {

const char * cl_composite_condition::name () const
{ return "cl_composite_condition"; }

void cl_composite_condition::print (std::ostream& strm) const
{
	fprint(strm, "Exception <cl_composite_condition> occurred: p = ");
	fprint(strm, p);
	fprint(strm, " is not a prime, ");
	if (zerop(factor))
		fprint(strm, "no factor found");
	else {
		fprint(strm, "factor found: ");
		fprint(strm, factor);
	}
	fprint(strm, "\n");
}

}  // namespace cln
