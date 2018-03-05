#include "mainheader.h"

int maintime23(int argc, char * argv[])
{
#if HASTIME

	int repetitions = 1;
	if ((argc >= 3) && !strcmp(argv[1],"-r")) {
		repetitions = atoi(argv[2]);
		argc -= 2; argv += 2;
	}
	if (argc < 2)
		exit(1);
	cl_I m = cl_I(argv[1]);
	cl_I M = (cl_I)1 << (intDsize*m);
	cl_I a = random_I(M);
	// One run to fill the cache.
	{
		char* p = cl_decimal_string(a);
		free_hook(p);
	}
	// Now start the timing.
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { char* p = cl_decimal_string(a); free_hook(p); }
	}
#else
    return 0;
#endif
}
