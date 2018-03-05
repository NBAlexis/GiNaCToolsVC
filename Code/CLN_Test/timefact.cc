#include "mainheader.h"

int maintime6(int argc, char * argv[])
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
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    cl_I f = factorial(FN_to_V(m));
	}
#else
    return 0;
#endif
}
