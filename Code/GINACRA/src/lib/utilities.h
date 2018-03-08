/*
 * GiNaCRA - GiNaC Real Algebra package
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


#ifndef GINACRA_UTILITIES_H
#define GINACRA_UTILITIES_H

/**
 * Collection of some basic algorithms just using GiNaC.
 *
 * @author Ulrich Loup
 * @since 2010-11-14
 * @version 2012-05-14
 */

//#include <ginac/ginac.h>
//#include <cln/cln.h>
#include <stdexcept>
//
//#include "constants.h"

using std::invalid_argument;
using std::map;
using std::vector;

namespace GiNaC
{
    /** Computes the product of a list of expressions.
     * @param l list of expressions
     * @return prod
     */
    GINACRA_API const ex prod( const lst& l ) throw ( invalid_argument );

    /** Computes the least common multiple of a list of expressions.
     * @param l list of expressions
     * @return lcm
     * @complexity linearly (in the length of l) many calls of GiNaC::lcm
     */
    GINACRA_API const ex lcm( const lst& l ) throw ( invalid_argument );

    /** Computes the least common multiple of two machine integers a and b.
     * @param a
     * @param b
     * @return lcm(a, b)
     * @complexity the complexity of gcd(a, b)
     */
    GINACRA_API long lcm( long a, long b );

    /** Computes the greatest common divisor of two integers a and b.
     * @param a
     * @param b
     * @return gcd(a, b)
     * @complexity O( digits( min(a, b) ) )
     */
    GINACRA_API long gcd( long a, long b );

    /** Computes the numerator q such that b / a = q / r and q and r are coprime.
     * @param a
     * @param b
     * @return a / gcd(a, b)
     * @complexity O( digits( min(a, b) ) ) + one integer division
     */
    GINACRA_API long numerator( long a, long b );

    /** Computes the numerator r such that b / a = q / r and q and r are coprime.
     * @param a
     * @param b
     * @return b / gcd(a, b)
     * @complexity O( digits( min(a, b) ) ) + integer division
     */
    GINACRA_API long denominator( long a, long b );

    /** Determines whether the given polynomial expression is constant in the given list of variables.
     * @param polynomial
     * @param symbolLst
     * @return the monomial underlying the given polynomial or 1 in case the expression is a sum.
     */
    GINACRA_API bool is_constant( const ex& polynomial, const vector<symbol>& symbolLst );

    /**
     * Tests whether the given expression p is a rational polynomial in x.
     * @param p
     * @param x
     * @return false in case the polynomial was found to be not rational, true otherwise
     */
    GINACRA_API bool is_rational_polynomial( const ex& p, const symbol& x );

    /**
     * Tests whether the given expression p is a polynomial in x with real algebraic coefficients, i.e. coefficients being rational or
     * mixed terms with RealAlgebraicNumberIRs.
     * @param p
     * @param x
     * @return false in case the polynomial was found to be not real algebraic, true otherwise
     */
    GINACRA_API bool is_realalgebraic_polynomial( const ex& p, const symbol& x );

    /**
     * Tests whether the given expression p is a term only containing only numbers returning <code>true</code> on <code>info(info_flags::numeric) && (info(info_flags::rational) || (info(info_flags::real) && info_flags::algebraic))</code>.
     * @param p
     * @return false in case the term was found to be not real algebraic, true otherwise
     */
    GINACRA_API bool is_realalgebraic_term( const ex& p );

    /** Determines the sign of the given numeric.
     * @param n numeric
     * @return the sign of the given numeric
     */
    GINACRA_API sign sgn( const numeric& n );

    /** For internal use only! Computes the monomial underlying the given polynomial in case the polynomial is a single term. Otherwise the method returns 1.
     * @param polynomial
     * @param symbolLst
     * @return the monomial underlying the given polynomial or 1 in case the expression is a sum.
     */
    GINACRA_API const ex monpart( const ex& polynomial, const vector<symbol>& symbolLst );

    /** For internal use only! Computes the polynomial coefficient underlying the given polynomial in case the polynomial is a single term. Otherwise the method returns 1.
     * @param polynomial
     * @param symbolLst
     * @return the (polynomial) coefficient underlying the given polynomial or 1 in case the expression is a sum.
     */
    GINACRA_API const ex coeffpart( const ex& polynomial, const vector<symbol>& symbolLst );

    /** For internal use only! Determins the monomial and its coefficient of the given polynomial w.r.t. the given list of variables, in case the polynomial is a single term. Otherwise the method returns 1.
     * @param polynomial
     * @param symbolLst
     * @param coefficient refernce to the coefficient to isolate
     * @param monomial reference to the monomial to isolate
     * @return the monomial underlying the given polynomial or 1 in case the expression is a sum.
     */
    GINACRA_API void isolateByVariables( const ex& polynomial, const vector<symbol>& symbolLst, ex& coefficient, ex& monomial );

    /**
     * Converts all coefficients of the given rational polynomial in the variables symbolLst to an exact rational numeric, so that is_rational_polynomial returns true.
     * @param p
     * @param symbolLst
     * @return p with all coefficients converted to an exact rational numeric
     */
    GINACRA_API const GiNaC::ex rationalize( const GiNaC::ex& p, const vector<GiNaC::symbol>& symbolLst );

    /**
     * Converts all coefficients of the given rational polynomial in the variable s to an exact rational numeric, so that is_rational_polynomial returns true.
     * @param p
     * @param s
     * @return p with all coefficients converted to an exact rational numeric
     */
    inline const GiNaC::ex rationalize( const GiNaC::ex& p, const GiNaC::symbol& s );

    /**
     * Converts the given numeric value to an exact numeric one.
     * @param n
     * @return an exact rational numeric of n
     */
    inline const GiNaC::numeric rationalize( const GiNaC::numeric& n );

    /** Sorts the given list of symbols lexicographicly.
     * @return new symbol list sorted lexicographicly
     */
    GINACRA_API const vector<symbol> sortVariables( const vector<symbol>& l );

    /** Compares two expressions lexicographically by their string representations.
     * @param a
     * @param b
     * @return true in case a is less or equal to b
     */
    GINACRA_API bool symbol_is_lesseq_lex( const symbol& a, const symbol& b );

    /** Compares two expressions lexicographically by their string representations.
     * @param a
     * @param b
     * @return true in case a is strictly less than b
     */
    GINACRA_API bool symbol_is_less_lex( const symbol& a, const symbol& b );

    // TODO make a good exception handling

    /**
     * Returns the signed Subresultant sequence.
     * The algorithm is originally from "New structure theorem for subresultants" -
     * Henri Lombardi, Marie-Francoise Roy and Mohab Safey El Din. See page 11-12
     * for the algorithm and page 5 for the notation.
     *
     * @param A the first Polynomial
     * @param B the second Polynomial
     * @param sym the main variable
     * @complexity O( deg(A)*deg(B) )
     * @return a map from int to ex, where the i-th index corresponds to the i-th subresultant in the subresultant sequence
     */
    GINACRA_API const map<int, ex> signedSubresultants( const ex& A, const ex& B, const symbol& sym );

    /**
     * Returns the Signed Subresultant Coefficient sequence.
     * The vectors contains the i-th coefficient of the
     * i-th element of Signed Subresultant sequence in
     * the i-th position. The Algorithm calls
     * calculateSignedSubresultants for the computation.
     *
     * @param A the first Polynomial
     * @param B the second Polynomial
     * @param sym the main variable
     * @complexity O( deg(A)*deg(B) )
     * @return a vector of ex with the coefficients
     */
    GINACRA_API const vector<ex> signedSubresultantsCoefficients( const ex& A, const ex& B, const symbol& sym ) throw ( invalid_argument );

}    // namespace GiNaC

namespace GiNaCRA
{
    struct GINACRA_API plus_second:
        std:: binary_function<unsigned, std::pair<unsigned, unsigned>, unsigned>
    {
        unsigned operator ()( unsigned x, const std::pair<unsigned, unsigned>& y ) const
        {
            return x + y.second;
        }
    };

}

#endif // GINACRA_UTILITIES_H
