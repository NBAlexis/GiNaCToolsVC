/** GiNaCRA - GiNaC Real Algebra package
 * Copyright (C) 2010-2012  Ulrich Loup, Joachim Redies, Sebastian Junges
 *
 * This file is part of GiNaCRA.
 *
 * GiNaCRA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GiNaCRA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GiNaCRA.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef GINACRA_OPERATORS_H
#define GINACRA_OPERATORS_H

/**
 * Collection of operators needed within the GiNaC Real Algebra package.
 *
 * This external declaration and implementation provides a better and standardized overview.
 *
 * @author Ulrich Loup
 * @since 2010-09-20
 * @version 2012-03-15
 */
#pragma once
//#include <ginac/operators.h>
//#include <tr1/memory>

namespace GiNaCRA
{

////////////
// Common //
////////////

/**
 * This is a wrapping function returning the maximum if the argument is of type GiNaC::numeric or RealAlgebraicNumberIR.
 *
 * If it is a RealAlgebraicNumberIR, the function returns the maximum of the absolute values of the interval bounds.
 * @param x
 * @return the absolute value (numeric) / the maximum of the absolute values of the interval bounds (RealAlgebraicNumberIR) / 0 in all other cases
 */
GINACRA_API const GiNaC::numeric abs( const GiNaC::ex& x );

//////////////////
// OpenInterval //
//////////////////

class GINACRA_API OpenInterval;

// binary arithmetic operators of OpenInterval
GINACRA_API const OpenInterval operator+( const OpenInterval&, const OpenInterval& );
GINACRA_API const OpenInterval operator-( const OpenInterval&, const OpenInterval& );
GINACRA_API const OpenInterval operator*( const OpenInterval&, const OpenInterval& );
// unary arithmetic operators of OpenInterval
GINACRA_API const OpenInterval operator-( const OpenInterval& );
// relational operators of OpenInterval
GINACRA_API const bool operator==( const OpenInterval&, const OpenInterval& );
GINACRA_API const bool operator!=( const OpenInterval&, const OpenInterval& );
GINACRA_API const bool operator<=( const OpenInterval&, const OpenInterval& );
GINACRA_API const bool operator>=( const OpenInterval&, const OpenInterval& );

// mixed arithmetic operators
GINACRA_API const OpenInterval operator+( const OpenInterval&, const GiNaC::numeric& );
GINACRA_API const OpenInterval operator+( const GiNaC::numeric&, const OpenInterval& );
GINACRA_API const OpenInterval operator-( const OpenInterval&, const GiNaC::numeric& );
GINACRA_API const OpenInterval operator-( const GiNaC::numeric&, const OpenInterval& );
GINACRA_API const OpenInterval operator*( const OpenInterval&, const GiNaC::numeric& );
GINACRA_API const OpenInterval operator*( const GiNaC::numeric&, const OpenInterval& );
GINACRA_API const OpenInterval operator/(const GiNaC::numeric&, const OpenInterval&) throw (std::overflow_error );
GINACRA_API const OpenInterval operator/(const OpenInterval&, const GiNaC::numeric&) throw (std::overflow_error );

//////////////////////////
// UnivariatePolynomial //
//////////////////////////

class GINACRA_API UnivariatePolynomial;
class GINACRA_API RationalUnivariatePolynomial;

// binary arithmetic operators
GINACRA_API const UnivariatePolynomial operator+( const UnivariatePolynomial&, const UnivariatePolynomial& );
GINACRA_API const UnivariatePolynomial operator-( const UnivariatePolynomial&, const UnivariatePolynomial& );
GINACRA_API const UnivariatePolynomial operator*( const UnivariatePolynomial&, const UnivariatePolynomial& );
GINACRA_API const UnivariatePolynomial operator/( const UnivariatePolynomial&, const UnivariatePolynomial& );
//const UnivariatePolynomial operator%( const UnivariatePolynomial&, const UnivariatePolynomial& );
GINACRA_API const RationalUnivariatePolynomial operator+( const RationalUnivariatePolynomial&, const RationalUnivariatePolynomial& );
GINACRA_API const RationalUnivariatePolynomial operator-( const RationalUnivariatePolynomial&, const RationalUnivariatePolynomial& );
GINACRA_API const RationalUnivariatePolynomial operator*( const RationalUnivariatePolynomial&, const RationalUnivariatePolynomial& );
GINACRA_API const RationalUnivariatePolynomial operator/( const RationalUnivariatePolynomial&, const RationalUnivariatePolynomial& );
GINACRA_API const RationalUnivariatePolynomial operator%( const RationalUnivariatePolynomial&, const RationalUnivariatePolynomial& );
// unary arithmetic operators
GINACRA_API const UnivariatePolynomial operator-( const UnivariatePolynomial& );
GINACRA_API const RationalUnivariatePolynomial operator-( const RationalUnivariatePolynomial& );
// relational operators
GINACRA_API const bool operator==( const UnivariatePolynomial&, const UnivariatePolynomial& );
GINACRA_API const bool operator!=( const UnivariatePolynomial&, const UnivariatePolynomial& );

/////////////////////////////
// UnivariatePolynomialSet //
/////////////////////////////

class GINACRA_API UnivariatePolynomialSet;

GINACRA_API std::ostream& operator<<( std::ostream& os, const UnivariatePolynomialSet& );

///////////////////////////
// RealAlgebraicNumberIR //
///////////////////////////

class GINACRA_API RealAlgebraicNumberIR;

// binary arithmetic operators
GINACRA_API RealAlgebraicNumberIR& operator+( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );
GINACRA_API RealAlgebraicNumberIR& operator-( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );
GINACRA_API RealAlgebraicNumberIR& operator*( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );
GINACRA_API RealAlgebraicNumberIR& operator/( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );
GINACRA_API RealAlgebraicNumberIR& operator^( RealAlgebraicNumberIR&, int );
// unary arithmetic operators
GINACRA_API RealAlgebraicNumberIR& operator-( RealAlgebraicNumberIR& );
// relational operators
GINACRA_API const bool operator==( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );
GINACRA_API const bool operator==( const RealAlgebraicNumberIR&, const RealAlgebraicNumberIR& );
GINACRA_API const bool operator!=( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );
GINACRA_API const bool operator<( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );
GINACRA_API const bool operator>( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );
GINACRA_API const bool operator<=( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );
GINACRA_API const bool operator>=( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& );

// mixed arithmetic operators
GINACRA_API RealAlgebraicNumberIR& operator+( const GiNaC::numeric&, RealAlgebraicNumberIR& );
GINACRA_API RealAlgebraicNumberIR& operator+( RealAlgebraicNumberIR&, const GiNaC::numeric& );
GINACRA_API RealAlgebraicNumberIR& operator-( const GiNaC::numeric&, RealAlgebraicNumberIR& );
GINACRA_API RealAlgebraicNumberIR& operator-( RealAlgebraicNumberIR&, const GiNaC::numeric& );
GINACRA_API RealAlgebraicNumberIR& operator*( const GiNaC::numeric&, RealAlgebraicNumberIR& );
GINACRA_API RealAlgebraicNumberIR& operator*( RealAlgebraicNumberIR&, const GiNaC::numeric& );
GINACRA_API RealAlgebraicNumberIR& operator/( const GiNaC::numeric&, RealAlgebraicNumberIR& );
GINACRA_API RealAlgebraicNumberIR& operator/( RealAlgebraicNumberIR&, const GiNaC::numeric& );

/////////////////////////
// RealAlgebraicNumber //
/////////////////////////

class GINACRA_API RealAlgebraicNumber;
class GINACRA_API RealAlgebraicNumberNR;

typedef std::tr1::shared_ptr<RealAlgebraicNumber> RealAlgebraicNumberPtr;

// basic binary operator
GINACRA_API RealAlgebraicNumberPtr binaryOperator( const RealAlgebraicNumberPtr& lh, const RealAlgebraicNumberPtr& rh, RealAlgebraicNumberIR&( *opIRIR )(RealAlgebraicNumberIR&, RealAlgebraicNumberIR&), RealAlgebraicNumberIR&( *opIRNR )(RealAlgebraicNumberIR&, const GiNaC::numeric&), const GiNaC::numeric( *opNRNR )(const GiNaC::numeric&, const GiNaC::numeric&) );
// binary arithmetic operators
GINACRA_API RealAlgebraicNumberPtr operator+(const RealAlgebraicNumberPtr&, const RealAlgebraicNumberPtr& );
GINACRA_API RealAlgebraicNumberPtr operator-(const RealAlgebraicNumberPtr&, const RealAlgebraicNumberPtr& );
GINACRA_API RealAlgebraicNumberPtr operator*(const RealAlgebraicNumberPtr&, const RealAlgebraicNumberPtr& );
GINACRA_API RealAlgebraicNumberPtr operator/(const RealAlgebraicNumberPtr&, const RealAlgebraicNumberPtr& );
GINACRA_API RealAlgebraicNumberPtr operator^( const RealAlgebraicNumberPtr&, int );
// unary arithmetic operators
GINACRA_API RealAlgebraicNumberPtr operator-( const RealAlgebraicNumberPtr& );
// relational operators
GINACRA_API const bool operator==( const RealAlgebraicNumberPtr&, const RealAlgebraicNumberPtr& );
GINACRA_API const bool operator!=( const RealAlgebraicNumberPtr&, const RealAlgebraicNumberPtr& );
GINACRA_API const bool operator<( const RealAlgebraicNumberPtr&, const RealAlgebraicNumberPtr& );

// streaming operators
GINACRA_API std::ostream& operator<<( std::ostream& os, const RealAlgebraicNumberPtr& );
GINACRA_API void print( const RealAlgebraicNumberPtr&, std::ostream& os = std::cout );

////////////////////////
// RealAlgebraicPoint //
////////////////////////

class GINACRA_API RealAlgebraicPoint;

// streaming operators
GINACRA_API std::ostream& operator<<( std::ostream& os, const RealAlgebraicPoint& );

////////////////
// Constraint //
////////////////

class GINACRA_API Constraint;

// relational operators
GINACRA_API const bool operator==( const Constraint&, const Constraint& );

// streaming operators
GINACRA_API std::ostream& operator<<( std::ostream& os, const Constraint& );

////////////////////////////////////////////////////////////////
// DIRECT IMPLEMENTATIONS of classes with template parameters //
////////////////////////////////////////////////////////////////

//////////////////////////////
//// MultivariatePolynomial //
//////////////////////////////
//
//template<typename monomialOrdering>
//class GINACRA_API MultivariatePolynomial;
//
//template<class monomialOrdering>
//std::ostream& operator<<( std::ostream & os, MultivariatePolynomial<monomialOrdering> p );
//
//// binary arithmetic operators of MultivariatePolynomial
//
//template<class monomialOrdering>
//const MultivariatePolynomial<monomialOrdering> operator+( const MultivariatePolynomial<monomialOrdering>& a, const MultivariatePolynomial<monomialOrdering>& b );
//
//template<class monomialOrdering>
//const MultivariatePolynomial<monomialOrdering> operator-( const MultivariatePolynomial<monomialOrdering>& a, const MultivariatePolynomial<monomialOrdering>& b );
//
//template<class monomialOrdering>
//const MultivariatePolynomial<monomialOrdering> operator*( const MultivariatePolynomial<monomialOrdering>& a, const MultivariatePolynomial<monomialOrdering>& b );
//
//template<class monomialOrdering>
//const MultivariatePolynomial<monomialOrdering> operator^( const MultivariatePolynomial<monomialOrdering>& a, const unsigned e );
//
//// unary arithmetic operators of MultivariatePolynomial
//
//template<class monomialOrdering>
//const MultivariatePolynomial<monomialOrdering> operator-( const MultivariatePolynomial<monomialOrdering>& a );
//
////////////////////////
//// MultivariateTerm //
////////////////////////
//
//template<typename monomialOrdering>
//class GINACRA_API MultivariateTerm;
//
//template<class monomialOrdering>
//std::ostream& operator<<( std::ostream & os, MultivariateTerm<monomialOrdering> p );
//
//template<class monomialOrdering>
//const MultivariateTerm<monomialOrdering> operator*( const MultivariateTerm<monomialOrdering>& a, const MultivariateTerm<monomialOrdering>& b );
//
///////////////////////////////
//// MultivariateCoefficient //
///////////////////////////////
//
//template<typename monomialOrdering>
//class GINACRA_API MultivariateCoefficient;
//template<class monomialOrdering>
//std::ostream& operator<<( std::ostream & os, MultivariateCoefficient<monomialOrdering> p );
//
////////////////////////////
//// MultivariateMonomial //
////////////////////////////
//
//template<typename monomialOrdering>
//class GINACRA_API MultivariateMonomial;
//
//template<class monomialOrdering>
//std::ostream& operator<<( std::ostream & os, MultivariateMonomial<monomialOrdering> p );
//
//// binary arithmetic operators of MultivariateTerm
//
//template<class monomialOrdering>
//const MultivariateMonomial<monomialOrdering> operator*( const MultivariateMonomial<monomialOrdering>& a, const MultivariateMonomial<monomialOrdering>& b );
//
//////////////////////////////////////////////
//// SpecialQuotientRingMultiplicationTable //
//////////////////////////////////////////////
//
//template<typename monomialOrdering>
//class GINACRA_API SpecialQuotientRingMultiplicationTable;
//
//template<class monomialOrdering>
//std::ostream& operator<<( std::ostream & os, SpecialQuotientRingMultiplicationTable<monomialOrdering> t );

} // namespace GiNaC

#endif // GINACRA_OPERATORS_H