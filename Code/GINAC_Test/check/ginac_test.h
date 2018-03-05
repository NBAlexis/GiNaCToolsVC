//=============================================================================
// FILENAME : ginac_test.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/4/2018 nbale]
//=============================================================================
#pragma once

#ifndef _GINAC_TEST_H_
#define _GINAC_TEST_H_

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

#include "test_runner.h"

extern unsigned exam_archive();
extern unsigned exam_clifford();
extern unsigned exam_color();


extern int main_bugme_chinrem_gcd();
extern int main_check_inifcns();
extern int main_check_lsolve();
extern int main_check_matrices();
extern int main_check_mul_info();
extern int main_check_numeric();
extern int main_exam_cra();
extern int main_exam_differentiation();
extern int main_exam_factor();
extern int main_exam_hashmap();
extern int main_exam_indexed();
extern int main_exam_inifcns();
extern int main_exam_inifcns_nstdsums();
extern int main_exam_lsolve();
extern int main_exam_matrices();
extern int main_exam_misc();
extern int main_exam_mod_gcd();
extern int main_exam_normalization();
extern int main_exam_numeric();
extern int main_exam_paranoia();
extern int main_exam_polygcd();
extern int main_exam_powerlaws();
extern int main_exam_pseries();
extern int main_exam_real_imag();
extern int main_exam_structure();
extern int main_factor_univariate_bug();
extern int main_heur_gcd_bug();
extern int main_match_bug();
extern int main_numeric_archive();
extern int main_parser_bugs();
extern int main_pgcd_infinite_loop();
extern int main_pgcd_relatively_prime_bug();
extern int main_time_antipode();
extern int main_time_dennyfliegner();
extern int main_time_fateman_expand();
extern int main_time_gammaseries();
extern int main_time_hashmap();
extern int main_time_lw_A();
extern int main_time_lw_B();
extern int main_time_lw_C();
extern int main_time_lw_D();
extern int main_time_lw_E();
extern int main_time_lw_F();
extern int main_time_lw_G();
extern int main_time_lw_H();
extern int main_time_lw_IJKL();
extern int main_time_lw_M1();
extern int main_time_lw_M2();
extern int main_time_lw_N();
extern int main_time_lw_O();
extern int main_time_lw_P();
extern int main_time_lw_Pprime();
extern int main_time_lw_Q();
extern int main_time_lw_Qprime();
extern int main_time_parser(unsigned n_max = 32768);
extern int main_time_toeplitz();
extern int main_time_uvar_gcd();
extern int main_time_vandermonde();

inline float gettime()
{
    LARGE_INTEGER cpufrequency;
    QueryPerformanceFrequency(&cpufrequency);
    float fPerTick = 1 / static_cast<float>(cpufrequency.QuadPart);
    QueryPerformanceCounter(&cpufrequency);
    return fPerTick * static_cast<float>(cpufrequency.QuadPart);
}

class debugStreambuf : public std::streambuf
{
public:
    virtual int_type overflow(int_type c = EOF)
    {
        if (c != EOF)
        {
            const char buf[] = { c, '\0' };
            OutputDebugStringA(buf);
        }
        return c;
    }
};

class Cout2VisualStudioDebugOutput
{

    debugStreambuf dbgstream;
    std::streambuf *default_stream;
    std::streambuf *default_streamerr;
    std::streambuf *default_streamlog;

public:
    Cout2VisualStudioDebugOutput()
    {
        default_stream = std::cout.rdbuf(&dbgstream);
        default_streamerr = std::cerr.rdbuf(&dbgstream);
        default_streamlog = std::clog.rdbuf(&dbgstream);
    }

    ~Cout2VisualStudioDebugOutput()
    {
        std::cout.rdbuf(default_stream);
        std::cerr.rdbuf(default_stream);
        std::clog.rdbuf(default_stream);
    }
};

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


#endif