//=============================================================================
// FILENAME : Calc_Core.h
// 
// DESCRIPTION:
//
// REVISION:
//  [2/26/2018 nbale]
//=============================================================================
#pragma once

#ifndef _CALC_CORE_H_
#define _CALC_CORE_H_

//Name and Version
#ifdef  __NAMESPACE
#undef  __NAMESPACE
#endif
#define __NAMESPACE				Calculator

#ifdef  __GVERSION
#undef  __GVERSION
#endif
#define __GVERSION              (0.000)

#ifdef  __BEGIN_NAMESPACE
#undef  __BEGIN_NAMESPACE
#endif

#define __BEGIN_NAMESPACE		namespace __NAMESPACE{

#ifdef  __END_NAMESPACE
#undef  __END_NAMESPACE
#endif

#define __END_NAMESPACE			}

#ifdef  __USE_NAMESPACE
#undef  __USE_NAMESPACE
#endif

#define __USE_NAMESPACE			using namespace __NAMESPACE;

// Standard constants
#undef FALSE
#undef TRUE
#undef NULL

#define FALSE   0
#define TRUE    1
#define NULL    0
//#define VOID    void

// Global constants.
#undef MAXBYTE
#undef MAXWORD
#undef MAXDWORD
#undef MAXINT

enum { MAXBYTE = 0xff };
enum { MAXWORD = 0xffffU };
enum { MAXDWORD = 0xffffffffU };
enum { MAXSBYTE = 0x7f };
enum { MAXSWORD = 0x7fff };
enum { MAXINT = 0x7fffffff };
enum { INDEX_NONE = -1 };
enum { UNICODE_BOM = 0xfeff };
enum ENoInit { E_NoInit = 0 };

enum ERunningOS
{
    OS_WIN95 = 0,
    OS_WIN98,
    OS_WINME,
    OS_WIN2K,
    OS_WINXP,
    OS_WINNT,
    OS_LINUX_X86,
    OS_FREEBSD_X86,
    OS_LINUX_X86_64,
    OS_MAC_OSX_PPC,
    OS_WIN64_AMD,
    OS_UNKNOWN = 255
};

enum ERunningCPU
{
    CPU_INTEL = 0,
    CPU_AMD,
    CPU_AMD64,
    CPU_PPC,
    CPU_UNKNOWN = 255
};

//pointer
#define ARRAY_COUNT( aarray ) \
    ( sizeof(aarray) / sizeof((aarray)[0]) )

#define appSafeDelete(p)		{if(p){delete p; p=NULL;}}
#define appSafeDeleteArray(p)	{if(p){delete[] p; p=NULL;}}
#define appSafeRelease(p) { if(p) p->Release(); p = NULL; }

#endif//#ifndef _CALC_CORE_H_
//=============================================================================
// END OF FILE
//=============================================================================