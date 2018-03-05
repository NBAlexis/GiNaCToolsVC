//////////////////////////////////////////////////////////////////////////
//  [2/26/2018 nbale]
//////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "Calc_Config.h"

#ifndef WSAPI
#define WSAPI __DLL_IMPORT
#endif

#define MCAPI WSAPI

#pragma __PACK_PUSH

#define appMalloc malloc
#define appFree(p) free((void*)(p))
#define appRealloc realloc

// #define appMemset memset
// #define appMemcpy memcpy
// #define appMemcmp memcmp

#define __MCNEW new

#include "Calc_Core.h"
#include "Calc_VCWin.h"
#include "Calc_WinConsoleIO.h"

//GMP
#include "gmp-6.1.2/gmp.h"

#pragma comment(lib, "gmp-6.1.2/libgmp-10.lib")
#pragma message("linking with " "libgmp-10.lib" "...")

#include "cln_public.h"

#include "ginac_public.h"

using namespace __NAMESPACE;

class MCAPI CFundament
{
public:
    //nothing
};

class MCAPI IMCInterface
{
public:
    virtual ~IMCInterface(void) { ; }
};

#pragma __PACK_POP

#endif //#ifndef _CALCULATOR_H_
//=============================================================================
// END OF FILE
//=============================================================================