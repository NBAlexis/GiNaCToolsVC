// format_new_roman().

// General includes.
#include "cln_private.h"

// Specification.
#include "real/format-output/cl_format.h"


// Implementation.

#include <sstream>
#include "cln/integer.h"
#include "cln/integer_io.h"
#include "cln/exception.h"

namespace cln {

void format_new_roman (std::ostream& stream, const cl_I& arg)
{
	if (!(0 < arg && arg < 4000)) {
		std::ostringstream buf;
		fprint(buf, "format_new_roman: argument should be in the range 1 - 3999, not ");
		fprint(buf, arg);
		fprint(buf, ".");
		throw runtime_exception(buf.str());
	}
	var uintL value = cl_I_to_UL(arg);
	struct roman { char symbol; uintL value; };
	static const roman scale[7] = {
		{ 'I',    1 },
		{ 'V',    5 },
		{ 'X',   10 },
		{ 'L',   50 },
		{ 'C',  100 },
		{ 'D',  500 },
		{ 'M', 1000 },
	};
	for (int i = 6; value > 0 /* && i >= 0 */ ; i--) {
		var const roman * p = &scale[i];
		var uintL multiplicity = floor(value,p->value);
		value = value % p->value;
		while (multiplicity > 0) {
			fprintchar(stream,p->symbol);
			multiplicity--;
		}
		if (value == 0)
			break;
		// Must have i > 0 here.
		var const roman * p_minor = &scale[(i-1) & ~1];
		var uintL lowered_value = p->value - p_minor->value;
		if (value >= lowered_value) {
			fprintchar(stream,p_minor->symbol);
			fprintchar(stream,p->symbol);
			value = value - lowered_value;
		}
	}
}

}  // namespace cln
