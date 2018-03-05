//=============================================================================
// FILENAME : cln_public.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/2/2018 nbale]
//=============================================================================
#pragma once

//total header

#ifndef _CLN_PUBLIC_H_
#define _CLN_PUBLIC_H_

//lib
#if defined(_MSC_VER)
#   if !defined(CLN_API)
#	define __LIB_TITLE__	"libcln"
#	define CLN_API __declspec(dllimport)
#	define CLN_TEMPLATE
#	ifdef _DEBUG
#		define __LIB_FILE__	__LIB_TITLE__ "_d.lib"
#	else
#		define __LIB_FILE__ __LIB_TITLE__ ".lib"
#	endif
#	pragma comment(lib, __LIB_FILE__)
#	pragma message("linking with " __LIB_FILE__ "...")
#	undef __LIB_FILE__
#	undef __LIB_TITLE__
#   endif
#else
#	error "We shall in WIN"
#endif

//IncludeFiles
#define __CLN_PUBLIC 1
#include "cln/cln.h"

#endif //#ifndef _CLN_PUBLIC_H_

//=============================================================================
// END OF FILE
//=============================================================================

