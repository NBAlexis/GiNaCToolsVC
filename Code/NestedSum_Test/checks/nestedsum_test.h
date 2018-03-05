//=============================================================================
// FILENAME : nestedsum_test.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/6/2018 nbale]
//=============================================================================
#pragma once

#ifndef _NESTEDSUM_TEST_H_
#define _NESTEDSUM_TEST_H_

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
#include "nestedsum_public.h"

#include "benchmark.h"
#include "examples.h"
#include "testsuite.h"

using namespace std;
using namespace GiNaC;
using namespace nestedsums;

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

#endif