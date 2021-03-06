// floating_point_underflow_exception().

// General includes.
#include "cln_private.h"

// Specification.
#include "float/cl_F.h"


// Implementation.

#include "cln/io.h"

namespace cln {

floating_point_underflow_exception::floating_point_underflow_exception ()
	: floating_point_exception("floating point underflow.")
{}

}  // namespace cln
