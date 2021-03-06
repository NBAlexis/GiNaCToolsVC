// cl_fget().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/string.h"


// Implementation.

#include "cln/io.h"
#include "base/string/cl_spushstring.h"

namespace cln {

const cl_string cl_fget (std::istream& stream, int n, char delim)
{
	var cl_spushstring buffer;
	// Handling of eofp is tricky: EOF is reached when (!stream.good()) || (stream.eof()).
	while (stream.good()) {
		var int c = stream.get();
		if (stream.eof())
			break;
		if (c==delim) {
			stream.unget();
			break;
		}
		if (--n <= 0) {
			stream.unget();
			stream.setstate(std::ios::failbit);
			break;
		}
		buffer.push(c);
	}
	return buffer.contents();
}

}  // namespace cln
