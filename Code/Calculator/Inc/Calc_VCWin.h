//=============================================================================
// FILENAME : Calc_VCWin.h
// 
// DESCRIPTION:
//
// REVISION:
//  [2/26/2018 nbale]
//=============================================================================
#pragma once

#ifdef _VCWIN

//#define WIN32_LEAN_AND_MEAN
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
#include <cstddef> // for size_t
#include <typeinfo> // for typeid
#include <iterator>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <cstddef> // for size_t
#include <functional>
#include <iosfwd>
#include <memory>
#include <cstdint>
#include <string>
#include <stack>
#include <cstring>

#undef min
#undef max

#ifndef _CALC_VCWIN_H_
#define _CALC_VCWIN_H_

//--------------------------------------------------------------------------------------------------------------
// Unwanted warnings
//--------------------------------------------------------------------------------------------------------------
// Unwanted VC++ level 4 warnings to disable.

#pragma warning(disable : 4100) /* unreferenced formal parameter										*/
#pragma warning(disable : 4201) /* nonstandard extension used : nameless struct/union					*/
#pragma warning(disable : 4127) /* Conditional expression is constant									*/
#pragma warning(disable : 4996) /* xxx was declared deprecated(Only In VC2005 or VC2008 when 2005 or 2008 change its functions)                          */
#pragma warning(disable : 4985) /* not derive standard operator new [] correctly?? !!!!!! -- Only in VC2008..... Check This later!!!!!! -- Alexis*/
#pragma warning(disable : 4121) /* alignment of a member was sensitive to packing -- Alexis*/

//--------------------------------------------------------------------------------------------------------------
// Function head
//--------------------------------------------------------------------------------------------------------------

#define __REMINDER_STR(s)		#s
#define __REMINDER_STRINT(s)		__REMINDER_STR(s)
#define REMINDER(prefix, msg)	message( __FILE__ "(" __REMINDER_STRINT(__LINE__) ") : " prefix msg )
#define TODO(msg)				REMINDER("TODO: ", #msg)

#ifndef _WINDOWS_
#define HANDLE void*
#define HINSTANCE void*
#endif

//--------------------------------------------------------------------------------------------------------------
// Type define
//--------------------------------------------------------------------------------------------------------------

// Undo any Windows defines.
#undef BYTE
#undef WORD
#undef DWORD
#undef INT
#undef FLOAT
#undef VOID
//#undef SIZE_T

#define VOID    void

//Type Define

typedef double					DOUBLE;
typedef unsigned __int64		QWORD;
typedef __int64					SQWORD;

// Unsigned base types.
typedef unsigned char		BYTE;		// 8-bit  unsigned.
typedef unsigned short		WORD;		// 16-bit unsigned.
typedef unsigned __int32	UINT;		// 32-bit unsigned.
typedef unsigned long		DWORD;		// 32-bit unsigned.
typedef unsigned __int64	QWORD;		// 64-bit unsigned.

                                        // Signed base types.
typedef	signed char			SBYTE;		// 8-bit  signed.
typedef signed short		SWORD;		// 16-bit signed.
typedef signed __int32  	INT;		// 32-bit signed.
typedef signed __int64		SQWORD;		// 64-bit signed.

                                        // Character types.
typedef char				ANSICHAR;	// An ANSI character.
typedef unsigned short      UNICHAR;	// A UNICODE character.
typedef unsigned char		ANSICHARU;	// An ANSI character.
typedef unsigned short      UNICHARU;	// A UNICODE character.

                                        // Other base types.
typedef signed __int32		UBOOL;		// Boolean 0 (FALSE) or 1 (TRUE).
typedef float				FLOAT;		// 32-bit IEEE floating point.
typedef double				DOUBLE;		// 64-bit IEEE double.
//TODO even undef SIZE_T not work..
//typedef unsigned long       SIZE_T;     // Corresponds to C SIZE_T.

#ifdef _WIN64
typedef unsigned __int64	PTRINT;		// Integer large enough to hold a pointer.
#else
typedef unsigned long		PTRINT;		// Integer large enough to hold a pointer.
#endif

                                        // Bitfield type.
typedef unsigned long       BITFIELD;	// For bit fields.

                                        // Offset of a struct member.
                                        //   (gcc3 thinks &((myclass*)NULL)->member is an invalid use of the "offsetof"
                                        //    macro. This is a broken heuristic in the compiler, but the workaround is
                                        //    to use a non-zero offset. 
#ifdef __GNUC__
#define STRUCT_OFFSET( struc, member ) \
    ( ( (PTRINT)&((struc*)0x1)->member ) - 0x1 )
#else
#define STRUCT_OFFSET( struc, member ) \
    ( (PTRINT)&((struc*)NULL)->member )
#endif

#define MC_UNUSE(val) (void)(val)

                                        //--------------------------------------------------------------------------------------------------------------
                                        // Cast
                                        //--------------------------------------------------------------------------------------------------------------

                                        // Cast
#define CAST(ttype,obj) ((ttype)(obj)) //(*(ttype*)(&obj))?
#if MCDEBUG
#define SCAST(ttype,obj) (static_cast<ttype>(obj))
#define DCAST(ttype,obj) (dynamic_cast<ttype>(obj))
#define CCAST(ttype,obj) (const_cast<ttype>(obj)) //do NEVER use this please
#else
#define SCAST(ttype,obj) ((ttype)(obj))
#define DCAST(ttype,obj) ((ttype)(obj))
#define CCAST(ttype,obj) ((ttype)(obj))
#endif

                                        //--------------------------------------------------------------------------------------------------------------
                                        // Unicode
                                        //--------------------------------------------------------------------------------------------------------------

                                        // Unicode or single byte character set mappings.
#define _TEXT_DEFINED
                                        //USE WINDOWS DEFINITION

#ifdef _UNICODE

#ifndef _TCHAR_DEFINED
typedef UNICHAR  TCHAR;
typedef UNICHARU TCHARU;
#endif

#ifndef _TEXT_DEFINED
#define _TEXT_DEFINED
#undef TEXT
#undef _T
#define TEXT(s) L ## s
#define _T(s) TEXT(s)
#endif

__BEGIN_NAMESPACE
FORCEINLINE TCHAR    FromAnsi(ANSICHAR In) { return CAST(BYTE, In); }
FORCEINLINE TCHAR    FromUnicode(UNICHAR In) { return In; }
FORCEINLINE ANSICHAR ToAnsi(TCHAR In) { return CAST(WORD, In) < 0x100 ? CAST(ANSICHAR, In) : CAST(ANSICHAR, MAXSBYTE); }
FORCEINLINE UNICHAR  ToUnicode(TCHAR In) { return In; }
__END_NAMESPACE

#else

#ifndef _TCHAR_DEFINED
typedef ANSICHAR  TCHAR;
typedef ANSICHARU TCHARU;
#endif
#undef TEXT
#undef _T
#define TEXT(s) s
#define _T(s) TEXT(s)

__BEGIN_NAMESPACE
FORCEINLINE TCHAR    FromAnsi(ANSICHAR In) { return In; }
FORCEINLINE TCHAR    FromUnicode(UNICHAR In) { return (WORD)In < 0x100 ? In : MAXSBYTE; }
FORCEINLINE ANSICHAR ToAnsi(TCHAR In) { return (WORD)In < 0x100 ? In : MAXSBYTE; }
FORCEINLINE UNICHAR  ToUnicode(TCHAR In) { return (BYTE)In; }
__END_NAMESPACE
#endif

//=====================================================
//	Standard Functions
//=====================================================
//--------------------------------------------------------------------------------------------------------------
// Trace
//--------------------------------------------------------------------------------------------------------------
//Trace

__BEGIN_NAMESPACE
WSAPI void CDECL appTraceA(const ANSICHAR* fmt, ...);
WSAPI void CDECL appTraceW(const UNICHAR* fmt, ...);
__END_NAMESPACE

#if MCDEBUG

#   ifdef _VCWIN

#	    ifdef UNICODE
#		    define appTrace	appTraceW
#	    else
#		    define appTrace	appTraceA
#	    endif

#   else
#	define appTrace {}
#   endif

#else
#define appTrace {}
#endif

//--------------------------------------------------------------------------------------------------------------
// kernel
//--------------------------------------------------------------------------------------------------------------
#define appBreak()				DebugBreak()
#if defined MCDEBUG
#define appAssert(exp) {if(!(exp)){appTrace(_T("%s(%d): Assert failed: %s\n"), _T(__FILE__), __LINE__, _T(#exp)); appBreak();}}
#define appVerify(exp) appAssert(exp)
#else
#define appAssert(exp) { (void)(exp); }
#define appVerify(exp) { (void)(exp); }
#endif

#ifdef MCDEBUG
#	define appFailMessage(msg) {appTrace(_T("%s(%d): Error: %s\n"), _T(__FILE__), __LINE__, (msg)); appBreak();}
#else
#	define appFailMessage(msg) {}
#endif

__BEGIN_NAMESPACE

FORCEINLINE DWORD appGetCycles() { LARGE_INTEGER ret; QueryPerformanceFrequency(&ret); return ret.LowPart; } //Maybe use QueryPerformanceFrequency?
FORCEINLINE FLOAT appGetTimeWINAPI()
{
    LARGE_INTEGER cpufrequency;
    appAssert(QueryPerformanceFrequency(&cpufrequency));
    FLOAT fPerTick = 1 / CAST(FLOAT, cpufrequency.QuadPart);
    appAssert(QueryPerformanceCounter(&cpufrequency));
    return fPerTick * CAST(FLOAT, cpufrequency.QuadPart);
}

FORCEINLINE void appStartTimer(DWORD& timer) { timer -= appGetCycles(); }
FORCEINLINE void appEndTimer(DWORD& timer) { timer += appGetCycles(); }
FORCEINLINE FLOAT appGetTime() { return SCAST(FLOAT, appGetCycles()) * 0.001f; }
__END_NAMESPACE

#define appGetSystemTime()		::GetTickCount()
#define appInterlockedIncrement(n)	InterlockedIncrement(CAST(LONG*,(n)))
#define appInterlockedDecrement(n)	InterlockedDecrement(CAST(LONG*,(n)))

//--------------------------------------------------------------------------------------------------------------
// string
//--------------------------------------------------------------------------------------------------------------
#   define appStrstr	_tcsstr
#   define appStrcpy	_tcscpy
#   define appStrcat	_tcscat
#   define appStrlen	_tcslen
#   define appStrcmp	_tcscmp
#   define appStricmp	_tcsicmp
#   define appStrncmp   _tcsncmp
#   define appStrupr	_tcsupr
#   define appStrlwr	_tcslwr
#   define appStrchr	_tcschr
#   define appStrrchr	_tcsrchr
#   define appSprintf	_stprintf
#   define appVsprintf	_vstprintf

#   define appToUpper	_totupper
#   define appIsSpace	_istspace
#   define appIsDigit	_istdigit
#   define appStoi		_tstoi
#   define appStof		_tstof

//Warning: please do not use following functions, they are used internally(Used in class CMCString)
#define _appStrpbrk		_tcspbrk
#define _appStrinc		_tcsinc
#define _appStrrev		_tcsrev
#define _appStrtol		_tcstol
#define _appStrtod		_tcstod
#define _appStrnicmp	_tcsnicmp

//--------------------------------------------------------------------------------------------------------------
// math
//--------------------------------------------------------------------------------------------------------------
#define appSin		sinf
#define appCos		cosf
#define appAcos		acosf
#define appTan		tanf
#define appAtan		atanf
#define appAtan2	atan2f
#define appFmod     fmod

#define appSwap     swap

__BEGIN_NAMESPACE
FORCEINLINE FLOAT appInvSqrt(FLOAT f) { return 1.f / sqrtf(f); }
__END_NAMESPACE

#define appSqrt		sqrtf

#define appFloor(f)		(SCAST(INT,floorf(f)))

__BEGIN_NAMESPACE
FORCEINLINE FLOAT appFractional(FLOAT Value) { return Value - appFloor(Value); }
__END_NAMESPACE


#if ASM

__BEGIN_NAMESPACE
FORCEINLINE INT appTrunc(FLOAT F)
{
    INT Result;
    if (0)
    {
        __asm
        {
            cvttss2si eax, [F]
        }
    }
    else
    {
        __asm
        {
            lea eax, [Result]
            fld F
            fistp dword ptr[eax]
            mov eax, [eax]
        }
    }
    // return value in eax.
}
__END_NAMESPACE

#else
#define appTrunc(x)		CAST(INT, x)
#endif

#define appModf(x,y)	fmodf(x,y)

__BEGIN_NAMESPACE
FORCEINLINE INT appCeil(FLOAT f) { return SCAST(INT, ceilf(f)); }
__END_NAMESPACE

#define appRand		rand

__BEGIN_NAMESPACE
const FLOAT __INV_RAND_MAX = 1.f / (SCAST(FLOAT, RAND_MAX + 1));

FORCEINLINE FLOAT appRandf() { return appRand() * __INV_RAND_MAX; }
FORCEINLINE INT appRound(FLOAT f) { return SCAST(INT, appFloor(f + 0.5f)); }

__END_NAMESPACE

//--------------------------------------------------------------------------------------------------------------
//error handling
//--------------------------------------------------------------------------------------------------------------
#if 0
#if USE_MC_GUARD
#define guard(func)			{static const TCHAR __FUNC_NAME__[]=TEXT(#func); try{
#define unguard(func)       }catch(TCHAR*Err){throw Err;}catch(...){appTrace(TEXT("%s, in %s, in %d"),__FUNC_NAME__,TEXT(__FILE__),__LINE__); throw;}}
//PAY ATTENTION HERE! WHEN USE unguardf, Use like this:
//unguardf( (TEXT("")) ) or unguardf( (TEXT("%d"), iNumber) ) 
#define unguardf(msg)		}catch(TCHAR*Err){throw Err;}catch(...){appTrace(TEXT("%s, in %s, in %d"),__FUNC_NAME__,TEXT(__FILE__),__LINE__); appTrace msg; throw;}}
#else
#define guard(func)	        {
#define unguard(func)       }
#define unguardf(msg)       }
#endif
#endif

#define guard guardwg
#define unguard unguardwg
#define unguardf unguardwg

__BEGIN_NAMESPACE

WSAPI void appInitCriticalSection();
WSAPI void appUninitCriticalSection();
WSAPI void appEnterCriticalSection();
WSAPI void appLeaveCriticalSection();

WSAPI INT appUnicodeToAnsi(char* mbstr, const wchar_t* wcstr, int bufsize);
WSAPI INT appAnsiToUnicode(UNICHAR* wcstr, const ANSICHAR* mbstr, INT bufsize);
WSAPI ANSICHAR* winToANSI(ANSICHAR* ACh, const TCHAR* InUCh, INT Count);
WSAPI TCHAR* winToUNICODE(TCHAR* UCh, const ANSICHAR* InACh, INT Count);
WSAPI INT winGetSizeANSI(const TCHAR* InUCh);
WSAPI INT winGetSizeUNICODE(const ANSICHAR* InACh);
WSAPI void appStrTrimLeft(TCHAR* &InStr);
WSAPI void appStrTrimRight(TCHAR* InStr);
WSAPI INT appStrToInt(const TCHAR* s);
WSAPI FLOAT appStrToFloat(const TCHAR* s);

#if defined(WIN32)
extern "C" void* __cdecl _alloca(SIZE_T);
#endif

#define appAlloca(size) ((0 == size) ? 0 : _alloca((size+7)&~7))

//#define ANSICHAR char
//#define UNICHAR wchar_t
#ifdef WIN32
#define GUnicodeOS TRUE
#define TCHAR_CALL_OS(funcW,funcA) (GUnicodeOS ? (funcW) : (funcA)) //always support Chinese?
#define TCHAR_TO_ANSI(str) winToANSI((ANSICHAR*)appAlloca(winGetSizeANSI(str)),str,winGetSizeANSI(str))
#define ANSI_TO_TCHAR(str) winToUNICODE((TCHAR*)appAlloca(sizeof(UNICHAR)*winGetSizeUNICODE(str)),str,winGetSizeUNICODE(str))
#else
#define TCHAR_TO_ANSI(str) str
#define ANSI_TO_TCHAR(str) str
#endif

//--------------------------------------------------------------------------------------------------------------
// memory
//--------------------------------------------------------------------------------------------------------------
FORCEINLINE void appMemzero(void* Dest, INT Count)
{
#if ASM
    __asm
    {
        mov		ecx, [Count]
        mov		edi, [Dest]
        xor eax, eax
        mov		edx, ecx
        shr		ecx, 2
        and edx, 3
        rep     stosd
        mov     ecx, edx
        rep     stosb
    }

#else
    memset(Dest, 0, Count);
#endif
}

FORCEINLINE void appMemcpy(void* Dest, const void* Src, INT Count)
{
#if ASM
    __asm
    {
        mov		ecx, Count
        mov		esi, Src
        mov		edi, Dest
        mov     edx, ecx
        shr     ecx, 2
        and edx, 3
        rep     movsd
        mov     ecx, edx
        rep     movsb
    }
#else
    memcpy(Dest, Src, Count);
#endif
}

FORCEINLINE INT appMemcmp(const void* Buf1, const void* Buf2, INT Count)
{
    return memcmp(Buf1, Buf2, Count);
}

FORCEINLINE UBOOL appMemIsZero(const void* V, int Count)
{
    //guard(appMemIsZero);
    BYTE* B = CAST(BYTE*, V);
    while (Count-- > 0)
        if (*B++ != 0)
            return FALSE;
    return TRUE;
    //unguard(appMemIsZero);
}

FORCEINLINE void* appMemmove(void* Dest, const void* Src, INT Count)
{
    return memmove(Dest, Src, Count);
}

FORCEINLINE void appMemset(void* Dest, INT C, INT Count)
{
    memset(Dest, C, Count);
}

#ifdef DEBUG
void RedirectIOToConsole();
#endif

__END_NAMESPACE

// Strings.
#define LINE_TERMINATOR TEXT("\r\n")
#define LINE_TERMINATOR_INLINE \r\n
#define PATH_SEPARATOR TEXT("\\")

// DLL file extension.
#define DLLEXT TEXT(".dll")

#endif//#ifndef _CALC_VCWIN_H_
#endif//#ifdef _VCWIN

//=============================================================================
// END OF FILE
//=============================================================================

