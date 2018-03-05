// offsetof() and friends

// <stddef.h> in GCC 3.0/3.1 has the obscure property of redefining
// offsetof every time it is included, not just the first time.
// Therefore we do the same thing here, and make sure that this file
// gets included after each include of <stddef.h>.
#ifdef __CLN_MS_VC__
#include "cln/types.h"
#endif

#undef offsetof

#ifdef __CLN_MS_VC__
#if defined(__GNUG__)
  #define offsetof(type,ident)  ((sintP)&(((type*)1)->ident)-1)
#else
  #define offsetof(type,ident)  ((sintP)&(((type*)0)->ident))
#endif
#else
#if defined(__GNUG__)
  #define offsetof(type,ident)  ((long)&(((type*)1)->ident)-1)
#else
  #define offsetof(type,ident)  ((long)&(((type*)0)->ident))
#endif
#endif

#ifndef _CL_OFFSETOF_H
#define _CL_OFFSETOF_H

#define offsetofa(type,ident)  offsetof(type,ident[0])

#endif /* _CL_OFFSETOF_H */
