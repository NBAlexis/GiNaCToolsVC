//=============================================================================
// FILENAME : Calc_Win.cpp
// 
// DESCRIPTION:
//
// REVISION:
//  [2/26/2018 nbale]
//=============================================================================
#pragma once

#include "Calculator_Pch.h"

#include <mmsystem.h>
#pragma __IMPORT_LIB("winmm.lib")

#ifndef _CALC_VCWIN_CPP_
#define _CALC_VCWIN_CPP_

#ifdef _VCWIN

__BEGIN_NAMESPACE

CRITICAL_SECTION s_cs;

/**
*
*
*/
WSAPI void appInitCriticalSection()
{
    ::InitializeCriticalSection(&s_cs);
}

/**
*
*
*/
WSAPI void appUninitCriticalSection()
{
    ::DeleteCriticalSection(&s_cs);
}

/**
*
*
*/
WSAPI void appEnterCriticalSection()
{
    //::EnterCriticalSection(&s_cs);
}

/**
*
*
*/
WSAPI void appLeaveCriticalSection()
{
    // ::LeaveCriticalSection(&s_cs);
}

/**
*
*
*/
WSAPI void appTraceA(const ANSICHAR* Fmt, ...)
{
    static char buf[1024] = "";
    appEnterCriticalSection();
    va_list ArgPtr;
    va_start(ArgPtr, Fmt);
    _vsnprintf_s(buf, 1023, Fmt, ArgPtr);
    va_end(ArgPtr);
    OutputDebugStringA(buf);
    printf(buf);
    appLeaveCriticalSection();
}

/**
*
*
*/
WSAPI void appTraceW(const UNICHAR* Fmt, ...)
{
    static wchar_t buf[1024] = _T("");
    appEnterCriticalSection();
    va_list ArgPtr;
    va_start(ArgPtr, Fmt);
    _vsnwprintf_s(buf, 1023, Fmt, ArgPtr);
    va_end(ArgPtr);
    OutputDebugStringW(buf);
    wprintf(buf);
    appLeaveCriticalSection();
}

/**
*
*
*/
WSAPI INT appUnicodeToAnsi(ANSICHAR* mbstr, const UNICHAR* wcstr, int bufsize)
{
    if (bufsize == 0 && mbstr != NULL)
        return 0;

    INT result = ::WideCharToMultiByte(CP_ACP, 0, wcstr, -1,
        mbstr, bufsize, NULL, NULL);
    appAssert(NULL == mbstr || result <= CAST(INT, bufsize));
    if (result > 0)
        mbstr[result - 1] = 0;
    return result;
}

/**
*
*
*/
WSAPI INT appAnsiToUnicode(UNICHAR* wcstr, const ANSICHAR* mbstr, INT bufsize)
{
    INT count = bufsize / 2;
    if (count == 0 && wcstr != NULL)
        return 0;

    INT result = ::MultiByteToWideChar(CP_ACP, 0, mbstr, -1,
        wcstr, count);
    appAssert(wcstr == NULL || result <= (INT)count);
    if (result > 0)
        wcstr[result - 1] = 0;
    else
    {
        //show_last_error();
    }
    return result * 2;
}

/**
*
*
*/
WSAPI ANSICHAR* winToANSI(ANSICHAR* ACh, const UNICHAR* InUCh, INT Count)
{
    WideCharToMultiByte(CP_ACP, 0, InUCh, -1, ACh, Count, NULL, NULL);
    return ACh;
}

/**
*
*
*/
WSAPI TCHAR* winToUNICODE(UNICHAR* UCh, const ANSICHAR* InACh, INT Count)
{
    MultiByteToWideChar(CP_ACP, 0, InACh, -1, UCh, Count);
    return UCh;
}

/**
*
*
*/
WSAPI INT winGetSizeANSI(const UNICHAR* InUCh)
{
    return WideCharToMultiByte(CP_ACP, 0, InUCh, -1, NULL, 0, NULL, NULL);
}

/**
*
*
*/
WSAPI INT winGetSizeUNICODE(const ANSICHAR* InACh)
{
    return MultiByteToWideChar(CP_ACP, 0, InACh, -1, NULL, 0);
}

/**
*
*
*/
WSAPI void appStrTrimLeft(TCHAR* &InStr)
{
    while (*InStr && (' ' == (*InStr) || '\t' == (*InStr)))
        ++InStr;
}

/**
*
*
*/
WSAPI void appStrTrimRight(TCHAR* InStr)
{
    TCHAR* p = InStr + appStrlen(InStr) - 1;
    while (p > InStr)
    {
        if (' ' == (*p) || '\t' == (*p))
            *p-- = 0;
        else
            break;
    }
}

/**
*
*
*/
WSAPI INT appStrToInt(const TCHAR* s)
{
    INT base;
    TCHAR* p = CAST(TCHAR*, s);
    appStrTrimLeft(p);
    if ('0' == p[0] && ('x' == p[1] || 'X' == p[1]))
        base = 16;
    else
        base = 10;
    return _appStrtol(p, &p, base);
}

/**
*
*
*/
WSAPI FLOAT appStrToFloat(const TCHAR* s)
{
    TCHAR* p;
    return (FLOAT)_appStrtod(s, &p);
}

#ifndef _USE_OLD_IOSTREAMS
using namespace std;
#endif

#ifdef DEBUG

static const WORD MAX_CONSOLE_LINES = 1024;

void RedirectIOToConsole() {

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

__END_NAMESPACE

#endif //WIN32

#endif//#ifndef _CALC_VCWIN_CPP_

//=============================================================================
// END OF FILE
//=============================================================================


