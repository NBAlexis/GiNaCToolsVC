// I/O of lfloats.

#ifndef _CL_LFLOAT_IO_H
#define _CL_LFLOAT_IO_H

#include "cln/number_io.h"
#include "cln/lfloat.h"

namespace cln {

extern CLN_API cl_read_flags cl_LF_read_flags;
extern CLN_API const cl_F read_float(std::istream&, const cl_read_flags&);
inline std::istream& operator>> (std::istream& stream, cl_LF& result)
{
	result = As(cl_LF)(read_float(stream,cl_LF_read_flags));
	return stream;
}

extern CLN_API void print_float(std::ostream& stream, const cl_print_flags& flags, const cl_F& z);
extern CLN_API cl_print_flags default_print_flags;
// The following does strictly the same as the general `fprint' for floats.
// It is here only so that people don't need to include <cln/float_io.h>.
inline void fprint (std::ostream& stream, const cl_LF& x)
{
	print_float(stream,default_print_flags,x);
}
CL_DEFINE_PRINT_OPERATOR(cl_LF)

}  // namespace cln

#endif /* _CL_LFLOAT_IO_H */
