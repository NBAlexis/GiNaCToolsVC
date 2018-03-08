//=============================================================================
// FILENAME : ginacra_public.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/9/2018 nbale]
//=============================================================================
#pragma once

//total header

#ifndef _GINACRA_PUBLIC_H_
#define _GINACRA_PUBLIC_H_

//lib
#if defined(_MSC_VER)
#   if !defined(GINACRA_API)
#	define __LIB_TITLE__	"ginacra"
#	define GINACRA_API __declspec(dllimport)
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

#endif //#ifndef _GINACRA_PUBLIC_H_

//=============================================================================
// END OF FILE
//=============================================================================

