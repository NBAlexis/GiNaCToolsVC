// print_integer().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/integer_io.h"


// Implementation.

#include "cln/output.h"

namespace cln {

void print_integer (std::ostream& stream, const cl_print_flags& flags, const cl_I& z)
{
	print_integer(stream,(const cl_print_number_flags&)flags,z);
}

}  // namespace cln
