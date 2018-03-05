// print_float().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/float_io.h"


// Implementation.

#include "cln/output.h"

namespace cln {

void print_float (std::ostream& stream, const cl_print_number_flags& flags, const cl_F& z)
{
	print_float(stream,(const cl_print_real_flags&)flags,z);
}

}  // namespace cln
