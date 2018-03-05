/* include/cln/config.h.  Generated from config.h.in by configure.  */
#ifndef _CL_CONFIG_PUBLIC_H
#define _CL_CONFIG_PUBLIC_H

#include "cln/host_cpu.h"
#include "cln/version.h"

/* 
 * FIXME: this should not be exposed to user. Or at least it should be
 * renamed to CL_HAVE_LONGLONG or something like that.
 */
/* compiler supports the `long long' type */
#define HAVE_LONGLONG /**/

/* 
 * Numbers in the heap are stored as "digit" (or "limb" in GMP speak)
 * sequences. A digit is an unsigned int with sizeof(void *)*CHAR_BIT bits.
 * It should be 8 or 16 or 32 or 64 bits. If CLN is sitting on top of GMP
 * it should match mp_limb_t
 */
/* #undef GMP_DEMANDS_UINTD_INT */

/* #undef GMP_DEMANDS_UINTD_LONG */

/* #define GMP_DEMANDS_UINTD_LONG_LONG 1 */

/* size of long is 4 bytes in MinGW64, use long long instead of long for pointer */
#define __CLN_MS_VC__ 1 

#endif /* _CL_CONFIG_PUBLIC_H */

