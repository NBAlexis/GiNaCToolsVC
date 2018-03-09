//=============================================================================
// FILENAME : ginacra_test.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/9/2018 nbale]
//=============================================================================
#pragma once

#ifndef _GINACRA_TEST_H_
#define _GINACRA_TEST_H_

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

#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

//GINAC
//#include <cstddef> // for size_t
//#include <typeinfo> // for typeid
//#include <iterator>
//#include <map>
//#include <set>
//#include <list>
//#include <vector>
//#include <algorithm>
//#include <utility>
//#include <iomanip>
//#include <iostream>
//#include <stdexcept>
//#include <cstddef> // for size_t
//#include <functional>
//#include <iosfwd>
//#include <memory>
//#include <cstdint>
//#include <string>
//#include <stack>
//#include <cstring>

#undef min
#undef max

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
#include "ginac_public.h"
#include "ginacra_public.h"

using namespace std;
using namespace GiNaC;
using namespace GiNaCRA;

namespace CppUnit
{

    template< class T > class TSimpleDoubleLinkedList : public T
    {
    public:
        TSimpleDoubleLinkedList* m_pNext;
        TSimpleDoubleLinkedList** m_ppPrevLink;
        void Unlink()
        {
            if (m_pNext)
                m_pNext->m_ppPrevLink = m_ppPrevLink;
            if (m_ppPrevLink)
                *m_ppPrevLink = m_pNext;
        }
        void Link(TSimpleDoubleLinkedList*& Before)
        {
            if (Before)
                Before->m_ppPrevLink = &m_pNext;
            m_pNext = Before;
            m_ppPrevLink = &Before;
            Before = this;
        }
    };

    class TestFixture
    {
    public:
        virtual void setUp() {}
        virtual void tearDown() {}
    };

    class thetestsuit
    {
    public:
        virtual const char* GetName() { return "No Name"; }
        virtual void DoTest() {}
    };

    //typedef void(*testfunc)(void);

    typedef TSimpleDoubleLinkedList<thetestsuit> testUnits;
    //typedef TSimpleDoubleLinkedList<testfunc> testFunctions;

    //static testUnits* sAllTests;
    static int iErrors = 0;
}

#define CPPUNIT_TEST_SUITE(classname) \
public: \
class classname##thetestsuit : public CppUnit::testUnits { \
     public: \
     classname##thetestsuit() { GFac.AddClass(this); }\
     virtual const char * GetName() { return #classname; } \
     virtual void DoTest() { \
     classname impl; \
     impl.setUp(); 


#define CPPUNIT_TEST(functionname) impl.functionname();

#define CPPUNIT_TEST_SUITE_END() }};


#define CPPUNIT_TEST_SUITE_REGISTRATION(classname) \
static classname::classname##thetestsuit classname##staticimp;


#define CPPUNIT_NS CppUnit

#define CPPUNIT_ASSERT(a) if (!(a)) { ++CppUnit::iErrors; }

#define CPPUNIT_ASSERT_EQUAL(a, b) if ((a) != (b)) { ++CppUnit::iErrors; }

#define CPPUNIT_ASSERT_EQUAL4(a, b, c, d) if ((a) != (b) || (a) != (c) || (a) != (d)) { ++CppUnit::iErrors; }

#define CPPUNIT_ASSERT_THROW(a, b) try { a; } catch(...) { cout << "should throw" << #b << endl; }


class CTestFactory 
{
public:
    CppUnit::testUnits* sAllTests;
    CTestFactory() 
    {

    }

    void AddClass(CppUnit::testUnits * otherc)
    {
        otherc->Link(sAllTests);
    }
};

extern CTestFactory GFac;

#include "test/CAD_unittest.h"
#include "test/Constraint_unittest.h"
#include "test/Groebner_unittest.h"
#include "test/MultivariateMonomialMR_unittest.h"
#include "test/MultivariatePolynomialMR_unittest.h"
#include "test/MultivariateTermMR_unittest.h"
#include "test/OpenInterval_unittest.h"
#include "test/RationalUnivariatePolynomial_unittest.h"
#include "test/RealAlgebraicNumberFactory_unittest.h"
#include "test/RealAlgebraicNumberIR_unittest.h"
#include "test/RealAlgebraicNumber_unittest.h"
#include "test/test.h"
#include "test/UnivariatePolynomialSet_unittest.h"
#include "test/UnivariatePolynomial_unittest.h"
#include "test/utilities_unittest.h"

const string   VERSION        = "2010-12-25";
const string   SUPPORT        = "Ulrich Loup <loup* @cs.rwth-aachen.de>";
const unsigned TESTCOUNT      = 100;    // number of repetitions
const unsigned TERMCOUNT      = 62;    // number of terms in the polynomial except for the constant part
const unsigned MAXDEGREE      = 80;    // maximum degree (+1) of polynomials
const unsigned MAXCOEFFICIENT = 1001;    // maximum coefficient (+1) of polynomials

#include "examples/benchmark_Groebner_1.h"
#include "examples/benchmark_CAD_1.h"
#include "examples/example1.h"
#include "examples/example2.h"
#include "examples/example3.h"
#include "examples/example4.h"
#include "examples/example_AlgoSyn-presentation-2012-07.h"
#include "examples/example_CADincremental_1.h"
#include "examples/example_CADincremental_2.h"
#include "examples/example_CADincremental_3.h"
#include "examples/example_CAD_1.h"
#include "examples/example_CAD_2.h"
#include "examples/example_CAD_3.h"
#include "examples/example_CAD_4.h"
#include "examples/example_CAD_5.h"
#include "examples/example_CAD_6.h"
#include "examples/example_CAD_7.h"
#include "examples/example_CAD_8.h"
#include "examples/example_CAD_9.h"
#include "examples/example_CAD_A.h"
#include "examples/example_CAD_B.h"
#include "examples/example_CAD_C.h"
#include "examples/example_IR_1.h"
#include "examples/example_IR_2.h"
#include "examples/example_IR_3.h"
#include "examples/example_IR_4.h"
#include "examples/example_NFM2011-presentation.h"
#include "examples/example_RAN_1.h"
#include "examples/example_RAN_2.h"
#include "examples/example_RAN_3.h"
#include "examples/example_SGB_1.h"

//AddOtherIncludeHere

//class classnameAAthetestsuit : public CppUnit::testUnits {
//public:
//    classnameAAthetestsuit() 
//    { 
//        Link(CppUnit::sAllTests); 
//    }
//    virtual const char * GetName() { return "BB"; }
//    virtual void DoTest()
//    {
//        Groebner_unittest abc;
//        abc.setUp();
//    }
//};
//
//classnameAAthetestsuit * classnameAAthetestsuit::mmmm = new classnameAAthetestsuit();

inline float gettime()
{
    LARGE_INTEGER cpufrequency;
    QueryPerformanceFrequency(&cpufrequency);
    float fPerTick = 1 / static_cast<float>(cpufrequency.QuadPart);
    QueryPerformanceCounter(&cpufrequency);
    return fPerTick * static_cast<float>(cpufrequency.QuadPart);
}

static const WORD MAX_CONSOLE_LINES = 1024;

inline void RedirectIOToConsole() {

    //Create a console for this application
    AllocConsole();

    // Get STDOUT handle
    HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
    FILE *COutputHandle = _fdopen(SystemOutput, "w");

    // Get STDERR handle
    HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
    int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
    FILE *CErrorHandle = _fdopen(SystemError, "w");

    // Get STDIN handle
    HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
    int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
    FILE *CInputHandle = _fdopen(SystemInput, "r");

    //make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
    std::ios_base::sync_with_stdio(true);

    // Redirect the CRT standard input, output, and error handles to the console
    freopen_s(&CInputHandle, "CONIN$", "r", stdin);
    freopen_s(&COutputHandle, "CONOUT$", "w", stdout);
    freopen_s(&CErrorHandle, "CONOUT$", "w", stderr);

    //Clear the error state for each of the C++ standard stream objects. We need to do this, as
    //attempts to access the standard streams before they refer to a valid target will cause the
    //iostream objects to enter an error state. In versions of Visual Studio after 2005, this seems
    //to always occur during startup regardless of whether anything has been read from or written to
    //the console or not.
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();

}




#endif //_GINACRA_TEST_H_
