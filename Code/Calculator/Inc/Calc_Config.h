//=============================================================================
// FILENAME : Calc_Config.h
// 
// DESCRIPTION:
//
// REVISION:
//  [2/26/2018 nbale]
//=============================================================================
#pragma once

#ifndef _CALC_CONFIG_H_
#define _CALC_CONFIG_H_

//Config
#if defined(DEBUG) || defined(_DEBUG)
#	undef DEBUG
#	undef _DEBUG
#	define DEBUG		1
#	define _DEBUG		1
# define MCDEBUG 1
#endif

#if defined(UNICODE) || defined(_UNICODE)
#	undef UNICODE
#	undef _UNICODE
#	define UNICODE		1
#	define _UNICODE		1
#endif

#if /*defined(_MSC_VER) && */defined(_CPPUNWIND)
#define USE_MC_GUARD 1
#else
#define USE_MC_GUARD 0
#endif

//win32 platform
#ifdef _VCWIN
#undef _VCWIN
#endif

#define _VCWIN 1

//temp debug
#define YJCTEMP 1

//cup
//fuck those ASMs
//#define ASM 1

#if _VCWIN
# define __DLL_IMPORT			__declspec(dllimport)
# define MCPRIVATE
# define __DLL_EXPORT			__declspec(dllexport)
# define __IMPORT_LIB(libname)	comment(lib, libname)
# undef FORCEINLINE
# undef CDECL
# define FORCEINLINE             __forceinline
# define CDECL                   __cdecl

# define SUPPORTS_PRAGMA_PACK 1
# define __PACK_PUSH				pack(push, 8)
# define __PACK_POP				pack(pop)
#endif

#endif//#ifndef _CALC_CONFIG_H_
//=============================================================================
// END OF FILE
//=============================================================================