// truncate1().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "real/cl_R.h"
#include "cln/rational.h"
#include "cln/float.h"

namespace cln {

const cl_I truncate1 (const cl_R& x)
GEN_R_OP1_2(x, truncate1, return)

}  // namespace cln
