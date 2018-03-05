// Built-in real number ring.

#ifndef _CL_REAL_RING_H
#define _CL_REAL_RING_H

#include "cln/ring.h"
#include "cln/real_class.h"

namespace cln {

typedef cl_specialized_number_ring<cl_R> cl_real_ring;
extern CLN_API const cl_real_ring cl_R_ring;		// math. R
extern CLN_API cl_class cl_class_real_ring;

class CLN_API cl_R_ring_init_helper
{
	static int count;
public:
	cl_R_ring_init_helper();
	~cl_R_ring_init_helper();
};

static cl_R_ring_init_helper cl_R_ring_init_helper_instance;

}  // namespace cln

#endif /* _CL_REAL_RING_H */
