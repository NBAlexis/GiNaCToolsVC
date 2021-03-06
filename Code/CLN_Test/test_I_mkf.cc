#include "mainheader.h"

int test_I_mask_field (int iterations)
{
	int error = 0;
	int i;
	// Check against ash.
	for (i = iterations; i > 0; i--) {
		cl_I a = testrandom_I();
		sintL s = random32() % 1024;
		sintL p = random32() % 1024;
		ASSERT3(mask_field(a,cl_byte(s,p)) == logand(a,ash(ash(1,s)-1,p)), a,s,p);
	}
	return error;
}
