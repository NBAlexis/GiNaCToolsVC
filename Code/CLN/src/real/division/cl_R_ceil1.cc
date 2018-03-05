// ceiling1().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "real/cl_R.h"
#include "cln/rational.h"
#include "cln/float.h"

namespace cln {

const cl_I ceiling1 (const cl_R& x)
GEN_R_OP1_2(x, ceiling1, return)

}  // namespace cln
