/* src/base/cl_base_config.h.  Generated from cl_base_config.h.in by configure.  */
// Defines OS dependent macros

#ifndef _CL_BASE_CONFIG_H
#define _CL_BASE_CONFIG_H

/* These definitions are adjusted by `configure' automatically. */


/* functions and declarations */

/* CL_GETTIMEOFDAY */
/* Define if you have the gettimeofday() function. */
#define HAVE_GETTIMEOFDAY 1
/* Define if the declaration of gettimeofday() needs dots. */
/* #undef GETTIMEOFDAY_DOTS */
/* Define as the type of `tzp' in gettimeofday() declaration. */
#define GETTIMEOFDAY_TZP_T void *

/* CL_TIMES_CLOCK */
/* Define if you have the times() function and it returns the real time,
   but don't have the gettimeofday() function. */
/* #undef HAVE_TIMES_CLOCK */


#endif /* _CL_BASE_CONFIG_H */

