// read_number_eof_exception().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/number_io.h"


// Implementation.

#include "cln/io.h"

namespace cln {

read_number_eof_exception::read_number_eof_exception ()
	: read_number_exception("read_number: end of stream encountered")
{}

}  // namespace cln
