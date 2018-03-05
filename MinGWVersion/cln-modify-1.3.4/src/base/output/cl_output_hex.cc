// fprinthexadecimal().

// General includes.
#include "base/cl_sysdep.h"

// Specification.
#include "cln/io.h"


// Implementation.

namespace cln {
#ifdef __MinGW64__
void fprinthexadecimal (std::ostream& stream, unsigned long long x)
{
	#define bufsize 16
	var char buf[bufsize+1];
	var char* bufptr = &buf[bufsize];
	*bufptr = '\0';
	do {
		unsigned long long q = x / 16;
		unsigned long long r = x % 16;
		*--bufptr = (r<10 ? '0'+r : 'A'-10+r);
		x = q;
	} while (x > 0);
	fprint(stream,bufptr);
	#undef bufsize
}

void fprinthexadecimal (std::ostream& stream, long long x)
{
	if (x >= 0)
		fprintdecimal(stream,(unsigned long long)x);
	else {
		fprintchar(stream,'-');
		fprintdecimal(stream,(unsigned long long)(-1-x)+1);
	}
}
#else
void fprinthexadecimal (std::ostream& stream, unsigned long x)
{
	#define bufsize 16
	var char buf[bufsize+1];
	var char* bufptr = &buf[bufsize];
	*bufptr = '\0';
	do {
		unsigned long q = x / 16;
		unsigned long r = x % 16;
		*--bufptr = (r<10 ? '0'+r : 'A'-10+r);
		x = q;
	} while (x > 0);
	fprint(stream,bufptr);
	#undef bufsize
}

void fprinthexadecimal (std::ostream& stream, long x)
{
	if (x >= 0)
		fprintdecimal(stream,(unsigned long)x);
	else {
		fprintchar(stream,'-');
		fprintdecimal(stream,(unsigned long)(-1-x)+1);
	}
}
#endif
}  // namespace cln
