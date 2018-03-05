#include "mainheader.h"

int maintime8(int argc, char * argv[])
{
#if HASTIME

	int repetitions = 1;
	if ((argc >= 3) && !strcmp(argv[1],"-r")) {
		repetitions = atoi(argv[2]);
		argc -= 2; argv += 2;
	}
	if (argc < 2)
		exit(1);
	extern int cl_atan_algo;
	uintL len = atoi(argv[1]);
#if 0
	cl_LF one = cl_I_to_LF(1,len);
	cl_F x = scale_float(random_F(one),-1);
	cout << x << endl;
#else
	cl_F x = sqrt(cl_I_to_LF(2,len))-1;
#endif
	cl_F y;
#if 0
	cl_atan_algo = 0;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { y = atan(x); }
	}
	cout << y << endl;
	cl_atan_algo = 1;
#endif
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { y = atan(x); }
	}
	cout << y << endl;

#else
    return 0;
#endif
}
