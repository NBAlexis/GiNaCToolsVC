// format_padded_string().

// General includes.
#include "cln_private.h"

// Specification.
#include "real/format-output/cl_format.h"


// Implementation.

#include <cstring>

namespace cln {

void format_padded_string (std::ostream& stream, sintL mincol, sintL colinc, sintL minpad, char padchar, bool padleftflag, const char * str)
{
	var sintL need = static_cast<sintL>(::strlen(str) + minpad); // so viele Zeichen mindestens
	var uintL auxpad = (need < mincol
			    ? ceiling((uintL)(mincol - need), colinc) * colinc
			    : 0
			   );
	if (!padleftflag)
		fprint(stream,str);
	format_padding(stream,minpad+auxpad,padchar);
	if (padleftflag)
		fprint(stream,str);
}

}  // namespace cln
