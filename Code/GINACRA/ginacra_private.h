//=============================================================================
// FILENAME : ginacra_h.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/8/2018 nbale]
//=============================================================================
#pragma once

//total header

#ifndef _GINACRA_PRIVATE_H_
#define _GINACRA_PRIVATE_H_

#include "cln_public.h"
#include "ginac_public.h"

#define GINACRA_API __declspec(dllexport)

//We need dll export serial
//We also need to use the macros
#undef GINAC_API
#define GINAC_API GINACRA_API

//#include "config.h"

#include "src/lib/SymbolDB.h"
#include "src/lib/VariableListPool.h"
#include "src/lib/constants.h"
#include "src/lib/Polynomial.h"
#include "src/lib/UnivariatePolynomial.h"
#include "src/lib/settings.h"
#include "src/lib/utilities.h"
#include "src/lib/tree.h"
#include "src/lib/OpenInterval.h"
#include "src/lib/RationalUnivariatePolynomial.h"
#include "src/lib/RealAlgebraicNumber.h"
#include "src/lib/RealAlgebraicNumberIR.h"
#include "src/lib/RealAlgebraicNumberNR.h"
#include "src/lib/RealAlgebraicNumberFactory.h"
#include "src/lib/RealAlgebraicPoint.h"
#include "src/lib/Constraint.h"
#include "src/lib/UnivariatePolynomialSet.h"
#include "src/lib/operators.h"
#include "src/lib/UnivariateRepresentation.h"
#include "src/lib/CAD.h"
#include "src/lib/MultivariateMonomialMR.h"
#include "src/lib/MultivariateCoefficientMR.h"
#include "src/lib/MultivariateTermMR.h"
#include "src/lib/MultivariatePolynomialMR.h"
#include "src/lib/Groebner.h"


#endif //#ifndef _NESTEDSUM_PRIVATE_H_

//=============================================================================
// END OF FILE
//=============================================================================
