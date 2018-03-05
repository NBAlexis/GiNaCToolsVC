/* src/timing/cl_t_config.h.  Generated from cl_t_config.h.in by configure.  */
// Defines OS dependent macros

#ifndef _CL_T_CONFIG_H
#define _CL_T_CONFIG_H

/* These definitions are adjusted by `configure' automatically. */


/* functions and declarations */

/* CL_GETTIMEOFDAY */
/* Define if you have the gettimeofday() function. */
#if defined(HAVE_GETTIMEOFDAY) && defined(_MSC_VER)
#undef HAVE_GETTIMEOFDAY 
#endif
//#define HAVE_GETTIMEOFDAY 1
/* Define if the declaration of gettimeofday() needs dots. */
/* #undef GETTIMEOFDAY_DOTS */
/* Define as the type of `tzp' in gettimeofday() declaration. */
#define GETTIMEOFDAY_TZP_T void *

/* CL_TIMES_CLOCK */
/* Define if you have the times() function and it returns the real time,
   but don't have the gettimeofday() function. */
/* #undef HAVE_TIMES_CLOCK */

/* CL_RUSAGE */
/* Define if you have <sys/resource.h>. */
/* #undef HAVE_SYS_RESOURCE_H */
/* Define if you also have <sys/time.h>, the getrusage() function,
   the struct rusage type, and <sys/resource.h> defines RUSAGE_SELF. */
/* #undef HAVE_GETRUSAGE */
/* Define as the type of `who' in getrusage() declaration. */
/* #undef RUSAGE_WHO_T */
/* Define if you have <sys/times.h>. */
/* #undef HAVE_SYS_TIMES_H */

/* CL_PERROR */
/* Define if <errno.h> or <stdio.h> contains a declaration for perror(). */
#define HAVE_PERROR_DECL /**/


#endif /* _CL_T_CONFIG_H */

