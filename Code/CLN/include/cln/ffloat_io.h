// I/O of ffloats.

#ifndef _CL_FFLOAT_IO_H
#define _CL_FFLOAT_IO_H

#include "cln/number_io.h"
#include "cln/ffloat.h"

namespace cln {

extern CLN_API cl_read_flags cl_FF_read_flags;
extern CLN_API const cl_F read_float(std::istream&, const cl_read_flags&);

inline std::istream& operator>> (std::istream& stream, cl_FF& result)
{
	result = As(cl_FF)(read_float(stream,cl_FF_read_flags));
	return stream;
}

extern CLN_API void print_float(std::ostream& stream, const cl_print_flags& flags, const cl_F& z);
extern CLN_API cl_print_flags default_print_flags;
// The following does strictly the same as the general `fprint' for floats.
// It is here only so that people don't need to include <cln/float_io.h>.
inline void fprint (std::ostream& stream, const cl_FF& x)
{
	print_float(stream,default_print_flags,x);
}
CL_DEFINE_PRINT_OPERATOR(cl_FF)

}  // namespace cln

#endif /* _CL_FFLOAT_IO_H */
