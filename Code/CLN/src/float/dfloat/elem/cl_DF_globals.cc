// Global variables for cl_DF.

// General includes.
#include "cln_private.h"

// Specification.
#include "float/ffloat/cl_FF.h"
#include "float/dfloat/cl_DF.h"


// Implementation.

namespace cln {

#ifdef __CLN_MS_VC__
    const cl_DF cl_DF_0 = cl_DF(cl_allocate_df0());
    const cl_DF cl_DF_1 = cl_I_to_DF(1);
    const cl_DF cl_DF_minus1 = cl_I_to_DF(-1);
#else
    const cl_DF cl_DF_0 = cl_DF_0;
    const cl_DF cl_DF_1 = cl_DF_1;
    const cl_DF cl_DF_minus1 = cl_DF_minus1;
#endif

int cl_DF_globals_init_helper::count = 0;

cl_DF_globals_init_helper::cl_DF_globals_init_helper()
{
	if (count++ == 0) {
#if (cl_word_size == 64)
		new ((void *)&cl_DF_0) cl_DF(allocate_dfloat(0)); // 0.0d0
		new ((void *)&cl_DF_1) cl_DF(encode_DF(0, 1, bit(DF_mant_len))); // 1.0d0
		new ((void *)&cl_DF_minus1) cl_DF(encode_DF(-1,1,bit(DF_mant_len))); // -1.0d0
#else
		new ((void *)&cl_DF_0) cl_DF(allocate_dfloat(0, 0)); // 0.0d0
		new ((void *)&cl_DF_1) cl_DF(encode_DF(0, 1, bit(DF_mant_len - 32), 0)); // 1.0d0
		new ((void *)&cl_DF_minus1) cl_DF(encode_DF(-1, 1, bit(DF_mant_len - 32), 0)); // -1.0d0
#endif
	}
}
cl_DF_globals_init_helper::~cl_DF_globals_init_helper()
{
	if (--count == 0) {
		// Nothing to clean up
	}
}

}  // namespace cln

