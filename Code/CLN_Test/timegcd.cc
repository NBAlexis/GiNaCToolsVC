#include "mainheader.h"

int maintime7(int argc, char * argv[])
{
	int repetitions = 1;
	if ((argc >= 3) && !strcmp(argv[1],"-r")) {
		repetitions = atoi(argv[2]);
		argc -= 2; argv += 2;
	}
	if (argc < 2)
		exit(1);
	cl_I m1 = cl_I(argv[1]);
	cl_I M1 = (cl_I)1 << (intDsize*m1);
	cl_I m2 = (argc>2 ? cl_I(argv[2]) : m1);
	cl_I M2 = (cl_I)1 << (intDsize*m2);
	cl_I a = random_I(M1);
	cl_I b = random_I(M2);
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { cl_I g = gcd(a,b); }
//	    { cl_I u; cl_I v; cl_I g = xgcd(a,b,&u,&v); }
	}
}
