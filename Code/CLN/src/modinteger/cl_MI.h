// Private modular integer operations.

#ifndef _CL_MI_H
#define _CL_MI_H

#include "cln/modinteger.h"

namespace cln {

extern cl_composite_condition* cl_notify_composite (const cl_modint_ring& R, const cl_I& nonunit);

#ifdef _MSC_VER
extern cl_class cl_class_modint_ring;
#endif

}  // namespace cln

#endif /* _CL_MI_H */
