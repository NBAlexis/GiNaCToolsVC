// ceiling1().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "float/cl_F.h"
#include "cln/sfloat.h"
#include "cln/ffloat.h"
#include "cln/dfloat.h"
#include "cln/lfloat.h"

namespace cln {

const cl_I ceiling1 (const cl_F& x)
GEN_F_OP1(x, ceiling1, return)

}  // namespace cln
