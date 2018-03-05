#include "mainheader.h"

int maintime13(int argc, char * argv[])
{
#if HASTIME

	int repetitions = 1;
	if ((argc >= 3) && !strcmp(argv[1],"-r")) {
		repetitions = atoi(argv[2]);
		argc -= 2; argv += 2;
	}
	if (argc < 2)
		exit(1);
	uintL len = atoi(argv[1]);
#if 0
	cl_LF one = cl_I_to_LF(1,len);
	cl_F x = one + random_F(one)/3;
	cout << x << endl;
#else
	cl_F x = sqrt(sqrt(cl_I_to_LF(2,len)));
#endif
	cl_F y;
	extern int cl_lnx_algo;
	y = ln(x); // fill cache
#if 0
	cl_lnx_algo = 0;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { y = ln(x); }
	}
	cout << y << endl;
	cl_lnx_algo = 1;
#endif
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { y = ln(x); }
	}
	cout << y << endl;

#else
    return 0;
#endif
}
