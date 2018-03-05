//=============================================================================
// FILENAME : polyfunctions.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/5/2018 nbale]
//=============================================================================
#pragma once

#ifndef _POLYFUNCTIONS_H_
#define _POLYFUNCTIONS_H_

namespace GiNaC {

    //gcd_uvar.cpp
    extern GINAC_API upoly sr_gcd(const upoly& a, const upoly& b);
    extern GINAC_API bool heur_gcd_z(upoly& g, const upoly& a, const upoly& b);
    extern GINAC_API upoly pseudoremainder(const upoly& a, const upoly& b);
}

#endif _POLYFUNCTIONS_H_

//=============================================================================
// END OF FILE
//=============================================================================