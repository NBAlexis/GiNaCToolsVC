// Includes the CPU specific cl_asm_*.cc file.

#include "cln_private.h"

#if defined(__sparc__) || defined(__sparc64__)
  #include "polynomial/elem/cl_asm_sparc_GF2.cc"
#endif

