//=============================================================================
// FILENAME : nestedsum_private.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/5/2018 nbale]
//=============================================================================
#pragma once

//total header

#ifndef _NESTEDSUM_PRIVATE_H_
#define _NESTEDSUM_PRIVATE_H_

#include "cln_public.h"
#include "ginac_public.h"

#define NESTEDSUMS_API __declspec(dllexport)

//We need dll export serial
//We also need to use the macros
#undef GINAC_API
#define GINAC_API NESTEDSUMS_API


#include "config.h"

#include "nestedsums/version.h"
#include "nestedsums/flags.h"
#include "nestedsums/symbol_factory.h"
#include "nestedsums/hash_entry.h"

#include "nestedsums/root_of_unity.h"

#include "nestedsums/basic_letter.h"
#include "nestedsums/letter.h"
#include "nestedsums/unit_letter.h"

#include "nestedsums/Zsum.h"
#include "nestedsums/Ssum.h"
#include "nestedsums/Csum.h"
#include "nestedsums/Bsum.h"
#include "nestedsums/Euler_Zagier_sum.h"
#include "nestedsums/harmonic_sum.h"
#include "nestedsums/multiple_polylog.h"
#include "nestedsums/harmonic_polylog.h"
#include "nestedsums/nielsen_polylog.h"
#include "nestedsums/classical_polylog.h"
#include "nestedsums/multiple_zeta_value.h"
#include "nestedsums/Ssum_to_Infinity.h"
#include "nestedsums/harmonic_sum_to_Infinity.h"

#include "nestedsums/polygamma.h"
#include "nestedsums/list_polygamma.h"

#include "nestedsums/transcendental_A.h"
#include "nestedsums/transcendental_B.h"
#include "nestedsums/transcendental_C.h"
#include "nestedsums/transcendental_D.h"

#include "nestedsums/transc_fct_A.h"
#include "nestedsums/transc_fct_B.h"
#include "nestedsums/transc_fct_C.h"
#include "nestedsums/transc_fct_D.h"

#include "nestedsums/constants.h"
#include "nestedsums/helpers.h"
#include "nestedsums/functions.h"

#endif //#ifndef _NESTEDSUM_PRIVATE_H_

//=============================================================================
// END OF FILE
//=============================================================================
