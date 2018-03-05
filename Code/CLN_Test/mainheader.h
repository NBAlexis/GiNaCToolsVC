#pragma once

#define min min
#define max max

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <list>
#include <string>
#include <tchar.h>
#include <stdexcept>
#include <limits.h>
#include <malloc.h>    
#include <windows.h>
#include <comdef.h>

#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

#undef min
#undef max

#include "cln_public.h"

#ifndef MAIN_HEADER_H_CLNTEST
#define MAIN_HEADER_H_CLNTEST

using namespace cln;
using namespace std;

inline float gettime()
{
    LARGE_INTEGER cpufrequency;
    QueryPerformanceFrequency(&cpufrequency);
    float fPerTick = 1 / static_cast<float>(cpufrequency.QuadPart);
    QueryPerformanceCounter(&cpufrequency);
    return fPerTick * static_cast<float>(cpufrequency.QuadPart);
}

//=============================================================================
//Exam
//=============================================================================

struct plus_test {
    const char * arg1;
    const char * arg2;
    const char * result;
};

struct minus_test {
    const char * arg1;
    const char * arg2;
    const char * result;
};

struct mul_test {
    const char * arg1;
    const char * arg2;
    const char * result;
};

struct floor_test {
    const char * arg1;
    const char * arg2;
    const char * result1;
    const char * result2;
};

struct div_test {
    const char * arg1;
    const char * arg2;
    const char * result;
};

#define num_elements(array)  (sizeof(array)/sizeof(array[0]))

#define DO_BINOP_TEST(typename,type,rtype,opname,op)  \
static void test_##typename##_##opname (int & er, int & done)				\
{									\
	for (unsigned int i = 0; i < num_elements(typename##_##opname##_tests); i++) { \
		opname##_test& test = typename##_##opname##_tests[i];	\
		type arg1 = type(test.arg1);				\
		type arg2 = type(test.arg2);				\
		rtype computed_result = arg1 op arg2;			\
		rtype result = rtype(test.result);			\
		if (computed_result != result) {			\
			std::cerr << "Error in " #typename "_" #opname "_tests[" << i << "] !" << endl; \
			std::cerr << "Result should be: " << result << endl;	\
			std::cerr << "Result computed : " << computed_result << endl << endl;	\
			++er;					\
		}							\
        else \
        { \
            ++done; \
        } \
	}								\
}

#define DO_FLOOR_TEST(typename,type)  \
static void test_##typename##_floor (int & er, int & done)				\
{									\
	for (unsigned int i = 0; i < num_elements(typename##_floor_tests); i++) { \
		floor_test& test = typename##_floor_tests[i];		\
		type arg1 = type(test.arg1);				\
		type arg2 = type(test.arg2);				\
		type##_div_t computed_result = floor2(arg1,arg2);	\
		cl_I result1 = cl_I(test.result1);			\
		type result2 = type(test.result2);			\
		if ((computed_result.quotient != result1) || (computed_result.remainder != result2)) { \
			std::cerr << "Error in " #typename "_floor_tests[" << i << endl; \
			std::cerr << "Results should be: " << result1 << ", " << result2 << endl;	\
			std::cerr << "Results computed : " << computed_result.quotient << ", " << computed_result.remainder << endl << endl;	\
			++er;					\
		}							\
        else \
        { \
            ++done; \
        } \
	} \
}

#define DO_TESTS(typename,type,qtype)  \
  DO_BINOP_TEST(typename,type,type,plus,+)				\
  DO_BINOP_TEST(typename,type,type,minus,-)				\
  DO_BINOP_TEST(typename,type,type,mul,*)				\
  DO_FLOOR_TEST(typename,type)						\
  DO_BINOP_TEST(typename,type,qtype,div,/)				\
void test_##typename (int & er, int & done)						\
{									\
	test_##typename##_plus(er, done);				\
	test_##typename##_minus(er, done);				\
	test_##typename##_mul(er, done);				\
	test_##typename##_floor(er, done);				\
	test_##typename##_div(er, done);				\
}


extern void test_integer(int & er, int & done);
extern void test_rational(int & er, int & done);
extern void test_sfloat(int & er, int & done);
extern void test_ffloat(int & er, int & done);
extern void test_dfloat(int & er, int & done);
extern void test_lfloat(int & er, int & done);

inline void test_elementary(int & er, int & done)
{
    test_integer(er, done);
    test_rational(er, done);
    test_sfloat(er, done);
    test_ffloat(er, done);
    test_dfloat(er, done);
    test_lfloat(er, done);
}

extern void test_gcd(int & er, int & done);
extern void test_xgcd(int & er, int & done);
extern void test_sqrtp(int & er, int & done);

inline void etest_all(int & er, int & done)
{   
    std::cout << "Exam elementary..." << std::endl;
    test_elementary(er, done);
    std::cout << "Exam gcd..." << std::endl;
    test_gcd(er, done);
    std::cout << "Exam xgcd..." << std::endl;
    test_xgcd(er, done);
    std::cout << "Exam sqrtp..." << std::endl;
    test_sqrtp(er, done);
}

inline void exammain(int & er, int & done) { etest_all(er, done); }

//=============================================================================
//Test
//=============================================================================


#define ASSERT(expr)  \
  if (!(expr)) {					\
	std::cerr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	error = 1;					\
  } 

#define ASSERT1(expr,a)  \
  if (!(expr)) {					\
	std::cerr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	std::cerr << #a" = " << a << endl;			\
	error = 1;					\
  }

#define ASSERT2(expr,a,b)  \
  if (!(expr)) {					\
	std::cerr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	std::cerr << #a" = " << a << endl;			\
	std::cerr << #b" = " << b << endl;			\
	error = 1;					\
  }

#define ASSERT3(expr,a,b,c)  \
  if (!(expr)) {					\
	std::cerr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	std::cerr << #a" = " << a << endl;			\
	std::cerr << #b" = " << b << endl;			\
	std::cerr << #c" = " << c << endl;			\
	error = 1;					\
  }

#define ASSERT4(expr,a,b,c,d)  \
  if (!(expr)) {					\
	std::cerr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	std::cerr << #a" = " << a << endl;			\
	std::cerr << #b" = " << b << endl;			\
	std::cerr << #c" = " << c << endl;			\
	std::cerr << #d" = " << d << endl;			\
	error = 1;					\
  }

extern int test_I(int iterations);
extern int test_MI(int iterations);
extern int test_nt(int iterations);

inline int testmain(int iterations)
{
    bool b_testI = test_I(iterations);
    bool b_testMI = test_MI(iterations);
    bool b_testNT = test_nt(iterations);
    return (b_testI || b_testMI || b_testNT) ? 1 : 0;
}


//=============================================================================
//Time
//=============================================================================

extern int maintime1(int argc, char* argv[]);
extern int maintime2(int argc, char* argv[]);
extern int maintime3(int argc, char* argv[]);
extern int maintime4(int argc, char* argv[]);
extern int maintime5(int argc, char* argv[]);

extern int maintime6(int argc, char* argv[]);
extern int maintime7(int argc, char* argv[]);
extern int maintime8(int argc, char* argv[]);
extern int maintime9(int argc, char* argv[]);
extern int maintime10(int argc, char* argv[]);

extern int maintime11(int argc, char* argv[]);
extern int maintime12(int argc, char* argv[]);
extern int maintime13(int argc, char* argv[]);
extern int maintime14(int argc, char* argv[]);
extern int maintime15(int argc, char* argv[]);

extern int maintime16(int argc, char* argv[]);
extern int maintime17(int argc, char* argv[]);
extern int maintime18(int argc, char* argv[]);
extern int maintime19(int argc, char* argv[]);
extern int maintime20(int argc, char* argv[]);

extern int maintime21(int argc, char* argv[]);
extern int maintime22(int argc, char* argv[]);
extern int maintime23(int argc, char* argv[]);
extern int maintime24(int argc, char* argv[]);
extern int maintime25(int argc, char* argv[]);

extern int maintime26(int argc, char* argv[]);
extern int maintime27(int argc, char* argv[]);
extern int maintime28(int argc, char* argv[]);
extern int maintime29(int argc, char* argv[]);
extern int maintime30(int argc, char* argv[]);

extern int maintime31(int argc, char* argv[]);

#endif
