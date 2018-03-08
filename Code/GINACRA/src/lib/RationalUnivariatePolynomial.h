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


#ifndef GINACRA_RATIONALUNIVARIATEPOLYNOMIAL_H
#define GINACRA_RATIONALUNIVARIATEPOLYNOMIAL_H

//#include "UnivariatePolynomial.h"
//#include "OpenInterval.h"

using GiNaC::ex_to;

namespace GiNaCRA
{
    /**
     * A class for a univariate polynomial providing everything what a GiNaC expression of type polynomial is and in addition, stores the single main variable of the polynomial.
     * This special superclass of UnivariatePolynomial is for rational coefficients only.
     *
     * @author Ulrich Loup
     * @since 2010-09-07
     * @version 2012-04-15
     * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
     */
    class GINACRA_API RationalUnivariatePolynomial:
        public UnivariatePolynomial
    {
        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Constructs a univariate polynomial consisting of the standard variable defined in constants.h.
             */
            RationalUnivariatePolynomial():
                UnivariatePolynomial()
            {}

            /**
             * Constructs a  rational univariate polynomial in case the given expression is a rational univariate polynomial in the specified variable.
             * @param p polynomial
             * @param s main variable of the univariate polynomial p
             */
            RationalUnivariatePolynomial( const ex& p, const symbol& s ) throw ( invalid_argument );

            /**
             * Constructs a rational univariate polynomial as copy of a univariate polynomial in case it is rational.
             * @param p univariate polynomial
             */
            RationalUnivariatePolynomial( const UnivariatePolynomial& p ) throw ( invalid_argument );

            ////////////////
            // Operations //
            ////////////////

            /**
             * @param i degree of which the coefficient shall be returned
             * @return the i-th coefficient of this polynomial
             */
            numeric coeff( int i ) const
            {
                return ex_to<numeric>( ex::coeff( mVariable, i ));    // cast safe because of the constructor
            }

            /**
             * @return the leading coefficient of this polynomial
             */
            numeric lcoeff() const
            {
                return ex_to<numeric>( ex::lcoeff( mVariable ));
            }

            /**
             * @return the trailing coefficient of this polynomial
             */
            numeric tcoeff() const
            {
                return ex_to<numeric>( ex::tcoeff( mVariable ));
            }

            /**
             * Returns sign (-1, 0, 1) of the rational univariate polynomial at the specified numeric.
             * @param a numeric
             * @return sign of the rational univariate polynomial at the specified numeric.
             */
            GiNaC::sign sgn( const numeric& a ) const;

            /** Evaluation of the rational univariate polynomial at the specified numeric, yielding a new numeric.
             * @param a numeric
             * @return value of the univariate polynomial at the specified numeric.
             */
            numeric evaluateAt( const numeric& a ) const;

            /**
             * @return One-norm of the rational univariate polynomial in case this has numeric coefficients.
             */
            numeric oneNorm() const;

            /**
             * @return Two-norm of the rational univariate polynomial in case this has numeric coefficients.
             */
            numeric twoNorm() const;

            /**
             * @return Maximum-norm of the real algebraic univariate polynomial in case this has numeric coefficients.
             */
            numeric maximumNorm() const;

            /** Computes the (upper) Cauchy bound, following Notation 10.1 (ISBN 0-387-94090-1).
             * @return the (upper) Cauchy bound, following Notation 10.1 (ISBN 0-387-94090-1)
             */
            numeric cauchyBound() const;

            /** Computes the number of real roots of the polynomial <code>p</code>.
             * @return the number of real roots of the polynomial
             */
            unsigned countRealRoots() const;

            /**
             * Searches a real root of this polynomial within the given interval i, starting at position start, which is returned if there was no result after steps+1 iterations of the Newton's method.
             * @param start
             * @param i
             * @param steps
             * @return a real root of this polynomial within the given interval i or start if no such root is found within the given number of steps+1
             */
            numeric approximateRealRoot( const numeric start, const OpenInterval& i, unsigned steps = 3 ) const;

            ////////////////////
            // Static Methods //
            ////////////////////

            /**
             * Generates a standard Sturm sequence by generating an additively inverted polynomial remainder sequence. This method is specially tailored to RationalUnivariatePolynomial.
             * @param a
             * @param b
             * @return Vector of pointers to the elements of the standard Sturm sequence
             *@todo naming is not according to the source of our other algorithms, this is actually the computation of the signed remainder sequence. SturmSequences are SRemS over P,P'.
             */
            static list<RationalUnivariatePolynomial> standardSturmSequence( const RationalUnivariatePolynomial& a,
                                                                             const RationalUnivariatePolynomial& b );

            /**
             * Counts the changes of sign when evaluating the given sequence of real algebraic univariate polynomials at the given numeric. This method is specially tailored to RationalUnivariatePolynomial.
             * @param seq A sequence of univariate polynomials in possibly different variables.
             * @param a
             * @return positive int
             */
            static unsigned signVariations( const list<RationalUnivariatePolynomial>& seq, const numeric& a );

            /** Calculates the Cauchy-Index
             * @param p Univariate nonzero polynomial
             * @param q Univariate polynomial
             * @return the Cauchy-Index Ind(Q/P)
             * @see Algorithm 9.1
             * TODO implement an overloaded cauchyIndex with custom bounds.
             */
            static int calculateSturmCauchyIndex( const RationalUnivariatePolynomial& p, const RationalUnivariatePolynomial& q );

            /** Computes the number of real roots of a polynomial in the specified interval, by using its standard Sturm sequence.
             * @param seq
             * @param i isolating interval where the real roots w.r.t. seq shall be counted
             * @return the number of real roots of the polynomial, whose standard Sturm sequence is given, in the interval i
             */
            static unsigned countRealRoots( const list<RationalUnivariatePolynomial>& seq, const OpenInterval& i )
            {
                // number of real roots in i, due to Sturm's theorem
                return signVariations( seq, i.left() ) - signVariations( seq, i.right() );
            }

            /** Computes the number of real roots of the polynomial <code>p</code> in the specified interval.
             * @param p
             * @param i isolating interval where the real roots of p shall be counted
             * @return the number of real roots of the polynomial in the interval i
             */
            static unsigned countRealRoots( const RationalUnivariatePolynomial& p, const OpenInterval& i )
            {
                list<RationalUnivariatePolynomial> seq = standardSturmSequence( p, p.diff() );
                return signVariations( seq, i.left() ) - signVariations( seq, i.right() );
            }

            /** Calculates the TarskiQuery
             * @param p Univariate nonzero polynomial
             * @param q Univariate polynomial
             * @return The TarskiQuery TaQ(q,p), defined as the sum over the signs(q(x)) where x are roots of p
             * @see Algorithm 9.2
             * TODO implement a more efficient way to calculate it by using algorithm 9.5.
             */
            static int calculateRemainderTarskiQuery( const RationalUnivariatePolynomial& p, const RationalUnivariatePolynomial& q );

            /** Sign Determination
             * @param z Univariate nonzero polynomial describing a set of points.
             * @param polynomials vector with the polynomial
             * @return A set of vectors representing the sign conditions realized by polynomials
             * @todo Move this to a better location.
             * @todo Restrict the passing of the polynomeslist not to vectors, but make it possible to pass other containers as well. This could be done by iterators, but it is difficult
             * to make sure that they are passed pointing at polynomials.
             */
            //template<class BidirectionalIterator>
            //static std::set<std::vector<Sign> > calculateSignDetermination(const RationalUnivariatePolynomial& z, const std::vector<RationalUnivariatePolynomial>& polynomials);
    };

}    // namespace GiNaC

#endif // GINACRA_RATIONALUNIVARIATEPOLYNOMIAL_H
