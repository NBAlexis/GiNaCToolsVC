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


#ifndef GINACRA_UNIVARIATEPOLYNOMIAL_H
#define GINACRA_UNIVARIATEPOLYNOMIAL_H

//#include <ginac/flags.h>
//#include <ginac/ginac.h>
#include <stdexcept>

//#include "constants.h"
//#include "Polynomial.h"

using std::ostream;
using std::invalid_argument;
using std::overflow_error;
using std::list;
using GiNaC::symbol;
using GiNaC::print_context;
using GiNaC::X;

namespace GiNaCRA
{
    /**
     * A class for a univariate polynomial providing everything what a GiNaC expression of type polynomial is and in addition, stores the single main variable of the polynomial.
     *
     * @author Ulrich Loup
     * @since 2010-08-03
     * @version 2012-05-19
     * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
     */
    class GINACRA_API UnivariatePolynomial:
        public Polynomial
    {
        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Constructs a univariate polynomial consisting of the standard variable defined in constants.h.
             */
            UnivariatePolynomial():
                Polynomial( 0 ),
                mVariable( X ),
                mEnabledPolynomialCheck( false )
            {}

            /**
             * Constructs a univariate polynomial with exactly the specified root.
             * @param n root to-be
             */
            UnivariatePolynomial( const numeric& n ):
                Polynomial( X - n ),
                mVariable( X ),
                mEnabledPolynomialCheck( false )
            {}

            /**
             * Constructs a univariate polynomial.
             * @param p polynomial
             * @param s main variable of the univariate polynomial p
             * @param enableCheck if set to <code>true</code> (default), the polynomial is checked for being a proper polynomial by GiNaC::ex::is_polynomial. Otherwise no check will be performed.
             */
            UnivariatePolynomial( const ex& p, const symbol& s, bool enableCheck = true ) throw ( invalid_argument );

            /**
             * Constructs a univariate polynomial as copy of another one.
             * @param p univariate polynomial
             */
            UnivariatePolynomial( const UnivariatePolynomial& p ):
                Polynomial( p ),
                mVariable( p.mVariable ),
                mEnabledPolynomialCheck( p.mEnabledPolynomialCheck )
            {}

            ///////////////
            // Selectors //
            ///////////////

            /**
             * Selects the main variable of the polynomial.
             * @return symbol
             */
            const symbol variable() const
            {
                return mVariable;
            }

            /**
             * Selects the flag for the is_rational_polynomial check.
             * @return flag for the is_rational_polynomial check
             */
            const bool enabledPolynomialCheck() const
            {
                return mEnabledPolynomialCheck;
            }

            ///////////////
            // Operators //
            ///////////////

            UnivariatePolynomial inVariable( const symbol& x ) const
            {
                return UnivariatePolynomial( this->subs( mVariable == x ), x );
            }

            // assignment operators

            /**
             * This polynomial gets all values of the other.
             */
            const UnivariatePolynomial& operator = ( const UnivariatePolynomial& );

            /**
             * This polynomial gets all values of the other expression, using the current main variable.
             */
            const UnivariatePolynomial& operator = ( const ex& );

            ////////////////
            // Operations //
            ////////////////

            /**
             * @param i degree of which the coefficient shall be returned
             * @return the i-th coefficient of this polynomial
             */
            ex coeff( int i ) const
            {
                return ex::coeff( mVariable, i );
            }

            /**
             * @return the leading coefficient of this polynomial
             */
            ex lcoeff() const
            {
                return ex::lcoeff( mVariable );
            }

            /**
             * @return the trailing coefficient of this polynomial
             */
            ex tcoeff() const
            {
                return ex::tcoeff( mVariable );
            }

            /**
             * @return the content of this polynomial
             */
            ex content() const
            {
                return ex::content( mVariable );
            }

            /**
             * @param nth
             * @return nth derivative of the univariate polynomial in the given symbol
             */
            UnivariatePolynomial diff( unsigned nth = 1 ) const
            {
                return UnivariatePolynomial( ex::diff( mVariable, nth ), mVariable, mEnabledPolynomialCheck );
            }

            /**
             * Removes the leading term.
             * @return the polynomial without leading term
             */
            UnivariatePolynomial trunc() const;

            /**
             * Returns true if the univariate polynomial is the zero polynomial, otherwise false.
             * @return true if the univariate polynomial is the zero polynomial, otherwise false.
             */
            bool isZero() const
            {
                return ex::is_zero();
            }

            /**
             * @return true in case the polynomial's lowest degree is not 0
             */
            const bool hasZeroRoot() const
            {
                return ldegree() > 0;
            }

            /**
             * @return degree of the univariate polynomial in its respective symbol
             */
            int degree() const
            {
                return ex::degree( mVariable );
            }

            /** The low-degree is the smallest exponent at the main variable occuring.
             * @return low-degree of the univariate polynomial in its respective symbol
             */
            int ldegree() const
            {
                return ex::ldegree( mVariable );
            }

            /**
             * @return primitive part of the univariate polynomial
             */
            UnivariatePolynomial primpart() const
            {
                return UnivariatePolynomial( ex::primpart( mVariable ), mVariable, mEnabledPolynomialCheck );
            }

            /**
             * @param content precomputed content of this polynomial
             * @return primitive part of the univariate polynomial
             */
            UnivariatePolynomial primpart( const ex& content ) const
            {
                return UnivariatePolynomial( ex::primpart( mVariable, content ), mVariable, mEnabledPolynomialCheck );
            }

            /** Computes a polynomial being decomposed into linear factors of multiplicity 1 with the same set of zeros as this polynomial.
             *
             * This is also referred to as the square-free part.
             *
             * @return separable part of the univariate polynomial, or zero in case the polynomial was constant
             */
            UnivariatePolynomial sepapart() const;

            /** Eliminates the root 0 from the polynomial by dividing the polynomial by a power of the main variable.
             * @complexity linear in degree()
             */
            UnivariatePolynomial nonzeropart() const;

            /**
             * Compares univariate polynomials for compatibility regarding common computations.
             * @return true in case the other UnivariatePolynomial has the same symbol as this.
             */
            bool isCompatible( const UnivariatePolynomial& o ) const
            {
                return mVariable == o.mVariable;
            }

            /**
             * Returns true if the univariate polynomial is constant in the respective variable, otherwise false.
             * @return true if the univariate polynomial is constant in the respective variable, otherwise false.
             */
            bool isConstant() const
            {
                return ex::degree( mVariable ) == 0;
            }

            /** Evaluation of the univariate polynomial at the specified expression, yielding a term in the coefficients only.
             * @param a an expression for evaluation
             * @return value of the univariate polynomial at the specified numeric.
             */
            ex evaluateAt( const ex& a ) const
            {
                return UnivariatePolynomial( ex::subs( mVariable == a ), mVariable );
            }

            ///////////////////////////
            // Arithmetic Operations //
            ///////////////////////////

            /**
             * Compute the remainder of <code>o</code> modulo the given polynomial in <b>this</b> variable.
             * @param o other polynomial
             * @return
             */
            const UnivariatePolynomial rem( const UnivariatePolynomial& o ) const
            {
                return UnivariatePolynomial( GiNaC::rem( *this, o, mVariable ), mVariable );
            }

            /**
             * Compute the quotient of division by <code>o</code> in <b>this</b> variable.
             * @param o other polynomial
             * @return
             */
            const UnivariatePolynomial quo( const UnivariatePolynomial& o ) const
            {
                return UnivariatePolynomial( GiNaC::quo( *this, o, mVariable ), mVariable, mEnabledPolynomialCheck );
            }

            /**
             * Compute the sum of this and <code>o</code> in <b>this</b> variable.
             * @param o other polynomial
             * @return
             */
            const UnivariatePolynomial add( const UnivariatePolynomial& o ) const
            {
                return UnivariatePolynomial( *this + o, mVariable, mEnabledPolynomialCheck );
            }

            /**
             * Compute the product of this and <code>o</code> in <b>this</b> variable.
             * @param o other polynomial
             * @return
             */
            const UnivariatePolynomial mul( const UnivariatePolynomial& o ) const
            {
                return UnivariatePolynomial( *this * o, mVariable, mEnabledPolynomialCheck );
            }

            /**
             * Compute the subtraction of this by <code>o</code> in <b>this</b> variable.
             * @param o other polynomial
             * @return
             */
            const UnivariatePolynomial sub( const UnivariatePolynomial& o ) const
            {
                return UnivariatePolynomial( *this - o, mVariable, mEnabledPolynomialCheck );
            }

            /**
             * Calculates the square.
             * @return this polynomial squared
             */
            UnivariatePolynomial square() const
            {
                return UnivariatePolynomial( (*this) * (*this), mVariable, mEnabledPolynomialCheck );
            }

            /**
             * Computes the greatest common divisor of this polynomial and the given by Euclid's algorithm.
             *
             * @param o
             * @return the greatest common divisor of this polynomial and the given
             */
            const UnivariatePolynomial gcd( const UnivariatePolynomial& o ) const
            {
                return UnivariatePolynomial( GiNaC::gcd( *this, o ), mVariable, mEnabledPolynomialCheck );
            }

            /**
             * Compute the resultant of <code>o</code> and the given polynomial in <b>this</b> variable.
             *
             * The resultant ist the subresultant of lowest degree.
             * @param o other polynomial
             * @return the resultant of this polynomial and o
             * @see subresultants, GiNaC::resultant
             */
            const UnivariatePolynomial resultant( const UnivariatePolynomial& o ) const
            {
                return UnivariatePolynomial( GiNaC::resultant( *this, o, mVariable ), mVariable );
                //                return UnivariatePolynomial::subresultants( *this, o ).front();
            }

            ///////////////////////////
            // Relational Operations //
            ///////////////////////////

            /**
             * @param o
             * @return true in case the other univariate polynomial equals this
             */
            const bool isEqual( const UnivariatePolynomial& o ) const
            {
                return (this->is_equal( o ) && mVariable.is_equal( o.mVariable ));
            }

            ////////////////////
            // Static Methods //
            ////////////////////

            /**
             * Generates a standard Sturm sequence by generating an additively inverted polynomial remainder sequence.
             *
             * Convention: If one polynomial is zero, the corresponding Sturm sequence is zero followed by the other polynomial.
             *
             * @param a
             * @param b
             * @return Vector of pointers to the elements of the standard Sturm sequence
             */
            static list<UnivariatePolynomial> standardSturmSequence( const UnivariatePolynomial& a,
                                                                     const UnivariatePolynomial& b )
                    throw ( invalid_argument );

            /**
             * Compares two univariate polynomials. The behavior of this function is equivalent to <code>GiNaC::ex_is_less( a, b )</code>.
             * @param a
             * @param b
             * @return true if <code>a < b</code>, false otherwise
             */
            static bool univariatePolynomialIsLess( const UnivariatePolynomial& a, const UnivariatePolynomial& b );

            /**
             * Compares two univariate polynomials.
             *
             * The behavior of this function is equivalent to a.degree() &lt; b.degree() or a.degree() &gt;= b.degree() and <code>GiNaC::ex_is_less( a, b )</code>.
             * @param a
             * @param b
             * @return true if <code>a < b</code>, false otherwise
             */
            static bool univariatePolynomialIsLessLowDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b );

            /**
             * Compares two univariate polynomials.
             *
             * The behavior of this function is equivalent to a.degree() odd or a.degree() &gt;= b.degree() and <code>GiNaC::ex_is_less( a, b )</code>.
             * @param a
             * @param b
             * @return true if <code>a < b</code>, false otherwise
             */
            static bool univariatePolynomialIsLessOddDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b );

            /**
             * Compares two univariate polynomials.
             *
             * The behavior of this function is equivalent to a.degree() odd and a.degree() &lt; b.degree() or a.degree() &gt;= b.degree() and <code>GiNaC::ex_is_less( a, b )</code>.
             * @param a
             * @param b
             * @return true if <code>a < b</code>, false otherwise
             */
            static bool univariatePolynomialIsLessOddLowDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b );

            /**
             * Compares two univariate polynomials.
             *
             * The behavior of this function is equivalent to a.degree() even or a.degree() &gt;= b.degree() and <code>GiNaC::ex_is_less( a, b )</code>.
             * @param a
             * @param b
             * @return true if <code>a < b</code>, false otherwise
             */
            static bool univariatePolynomialIsLessEvenDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b );

            /**
             * Compares two univariate polynomials.
             *
             * The behavior of this function is equivalent to a.degree() even and a.degree() &lt; b.degree() or a.degree() &gt;= b.degree() and <code>GiNaC::ex_is_less( a, b )</code>.
             * @param a
             * @param b
             * @return true if <code>a < b</code>, false otherwise
             */
            static bool univariatePolynomialIsLessEvenLowDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b );

            /**
             * Predefined flags for different solving strategies in <code>UnivariatePolynomial::subresultants</code>.
             */
            enum subresultantStrategy
            {
                GENERIC_SUBRESULTANTSTRATEGY = 0,    /* * Generic algorithm. */
                LAZARDS_SUBRESULTANTSTRATEGY = 1,    /* * Perform Lazard's optimization. */
                DUCOS_SUBRESULTANTSTRATEGY = 2,    /* * Perform Ducos' optimization. */
            };

            /**
             * Computes the subresultant sequence according to the algorithm in
             * [Lionel Ducos. Optimizations of the subresultant algorithm. Journal of Pure and Applied Algebra 145 (2000) 149–163]
             *
             * Marginal cases: Let the degree of a be smaller or equal than the degree of b.
             * if deg(b) is less than 2, then only a, b are returned.
             *
             * @param a the first Polynomial
             * @param b the second Polynomial
             * @param strategy choice of optimization. Standard is none, other possibilities are due to the sections 2 and 3 of the paper.
             * @return the subresultant sequence in descending order of degree.
             * @complexity O( deg(a)*deg(b) )
             */
            static const list<UnivariatePolynomial> subresultants( const UnivariatePolynomial& a,
                                                                   const UnivariatePolynomial& b,
                                                                   const subresultantStrategy strategy = GENERIC_SUBRESULTANTSTRATEGY );

            /**
             * Returns the leading coefficients of the subresultants of a and b.
             *
             * @param a the first Polynomial
             * @param b the second Polynomial
             * @param strategy choice of optimization. Standard is none, other possibilities are due to the sections 2 and 3 of the paper.
             * @see UnivariatePolynomial::subresultants
             * @return vector containing at the i-th position the i-th subresultant coefficient
             */
            static const vector<ex> subresultantCoefficients( const UnivariatePolynomial& a,
                                                              const UnivariatePolynomial& b,
                                                              const subresultantStrategy strategy = GENERIC_SUBRESULTANTSTRATEGY );

            /**
             * Returns the i-th coefficients of the i-th subresultant of a and b at the i-th position of the result vector.
             *
             * @param a the first Polynomial
             * @param b the second Polynomial
             * @param strategy choice of optimization. Standard is none, other possibilities are due to the sections 2 and 3 of the paper.
             * @see UnivariatePolynomial::subresultants
             * @return vector containing at the i-th position the i-th subresultant coefficient
             */
            static const vector<ex> principalSubresultantCoefficients( const UnivariatePolynomial& a,
                                                                       const UnivariatePolynomial& b,
                                                                       const subresultantStrategy strategy = GENERIC_SUBRESULTANTSTRATEGY );

            /////////////////////
            // Methods from ex //
            /////////////////////

            void do_print( const print_context& c, unsigned level = 0 ) const;

        protected:

            ////////////////
            // Attributes //
            ////////////////

            symbol mVariable;    // the main variable of the univariate polynomial (only changed by using operator=)
            bool   mEnabledPolynomialCheck;    // flag to disable (when set to false) the is_polynomial check in the constructors in every method of this object

        private:

            ///////////////////////
            // Auxiliary Methods //
            ///////////////////////

    };    // class UnivariatePolynomial

}    // namespace GiNaC

#endif
