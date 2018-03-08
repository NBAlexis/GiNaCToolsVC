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


#ifndef GINAC_RA_INTERVALREPRESENTATION_H
#define GINAC_RA_INTERVALREPRESENTATION_H

// Optimization flags
#define GINACRA_INTERVALREPRESENTATION_OPT_NORMALIZE_POLYNOMIAL // call normalizePolynomial in the constructor

//#include <ginac/flags.h>
//#include <ginac/registrar.h>
//#include <ginac/ginac.h>
#include <stdexcept>

//#include "settings.h"
//#include "RationalUnivariatePolynomial.h"
//#include "OpenInterval.h"
//#include "RealAlgebraicNumber.h"
//#include "operators.h"

namespace GiNaCRA
{
    /**
     * An implementation of an real algebraic number providing methods to add, multiply or evaluate their sign on polynomials.
     *
     *
     *
     * @author Ulrich Loup
     * @since 2010-07-28
     * @version 2012-05-07
     * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
     */
    class GINACRA_API RealAlgebraicNumberIR:
        public RealAlgebraicNumber,
        public basic
    {
        // Call GiNaC macro (registrar.h) for initiating the implementation into the basic type.
        GINAC_DECLARE_REGISTERED_CLASS(RealAlgebraicNumberIR, basic)

        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            //     RealAlgebraicNumberIR(const symbol& s) throw(invalid_argument); -> private

            /**
             * Constructs a real algebraic number in interval representation (p, l, r) with a normalized interval w.r.t. normalizeInterval.
             */
            //RealAlgebraicNumberIR( );

            /**
             * Constructs a real algebraic number in interval and order representation (p, l, r, o) with a normalized interval w.r.t. normalizeInterval.
             *
             * <ul>
             * <li>p can be changed within the constructor, but is later constant.<li>
             * <li>i can be changed later by refine(), but is only normalized within the constructor in case not normalized before.</li>
             * </ul>
             *
             * @param p polynomial having the real algebraic number as one of its roots
             * @param i open interval ]l, r[ containing the real algebraic number (should be normalized)
             * @param s standard Sturm sequence
             * @param normalize if set to false, the interval will not be normalized in the constructor (default is true)
             * @param isRoot true marks this real algebraic number to stem from a root computation
             */
            RealAlgebraicNumberIR( const RationalUnivariatePolynomial& p,
                                   const OpenInterval& i,
                                   const list<RationalUnivariatePolynomial>& s = list<RationalUnivariatePolynomial>(),
                                   const bool normalize = true,
                                   const bool isRoot = true )
                    throw ( invalid_argument );

            /**
             * Destructor.
             */
            ~RealAlgebraicNumberIR();

            /**
             * Clone-"Constructor"
             */
            RealAlgebraicNumberPtr clone() const;

            ///////////////
            // Selectors //
            ///////////////

            /**
             * Selects the polynomial having this real algebraic number as one of its roots.
             * @return polynomial having the number as one of its roots
             */
            const RationalUnivariatePolynomial polynomial() const
            {
                return mPolynomial;
            }

            /**
             * Selects the open interval ]l, r[ containing the real algebraic number.
             * @return open interval ]l, r[ containing the real algebraic number
             */
            const OpenInterval interval() const
            {
                return mInterval;
            }

            /**
             * Returns a pre-computed standard Sturm sequence of the polynomial and its derivative.
             * @return standard Sturm sequence of the polynomial and its derivative.
             */
            const list<RationalUnivariatePolynomial> sturmSequence() const
            {
                return mSturmSequence;
            }

            /** Returns how often one of the refine methods was called before.
             * @return number of refinement steps executed on this real algebraic number
             */
            const unsigned refinementCount() const
            {
                return mRefinementCount;
            }

            ///////////////
            // Operators //
            ///////////////

            // assignment operators

            /**
             * This number gets all values of the other.
             */
            const RealAlgebraicNumberIR& operator = ( const RealAlgebraicNumberIR& );

            ////////////////
            // Operations //
            ////////////////

            /** Normalizes the interval of an real algebraic number to not contain zero, in case the number is non-zero.
             */
            void normalizeInterval() throw ( invalid_argument );

            /** Refines the interval i of this real algebraic number yielding the interval j such that <code>2*(j.Right()-j.Left()) &lt;= i.Right()-i.Left()</code>. This is cutting the interval in the middle and choosing the half where the root lays in.
             * @param strategy strategy selection according to RealAlgebraicNumberFactory::searchRealRootsStrategy
             * @rcomplexity constant
             * @scomplexity constant
             */
            void refine( RealAlgebraicNumberSettings::RefinementStrategy strategy = RealAlgebraicNumberSettings::DEFAULT_REFINEMENTSTRATEGY );

            /** Refines the interval i of this real algebraic number yielding the interval j such that <code>(j.Right()-j.Left()) &lt;= eps</code>.
             * @param eps
             */
            inline void refine( numeric eps )
            {
                while( mInterval.right() - mInterval.left() > eps )
                    this->refine();
            }

            /** Refines the interval i of this real algebraic number yielding the interval j such that !j.meets(n). If true is returned, n is the exact numeric representation of this root. Otherwise not.
             * @param n
             * @rcomplexity constant
             * @scomplexity constant
             * @return true, if n is the exact numeric representation of this root, otherwise false
             */
            bool refineAvoiding( numeric n );

            /**
             * Returns sign (GiNaC::ZERO_SIGN, GiNaC::POSITIVE_SIGN, GiNaC::NEGATIVE_SIGN) of this real algebraic number.
             * @return sign of this real algebraic number.
             */
            GiNaC::sign sgn() const;

            /**
             * Returns sign (GiNaC::ZERO_SIGN, GiNaC::POSITIVE_SIGN, GiNaC::NEGATIVE_SIGN) of the specified univariate polynomial at this real algebraic number.
             * @param p rational univariate polynomial
             * @return sign of the univariate polynomial at this real algebraic number.
             */
            GiNaC::sign sgn( const RationalUnivariatePolynomial& p ) const;

            /** Computes a numeric value for this real algebraic number approximating it. This is also the outcome of ex::evalf().
             * @complexity constant
             * @return a numeric value for this real algebraic number approximating it
             */
            const numeric approximateValue() const
            {
                return mInterval.midpoint();
            }

            /** Chooses a numeric value out of the isolating interval with the smallest numeric representation.
             * @complexity constant
             * @return a numeric value for this real algebraic representing a good sample
             */
            const numeric sampleValue() const
            {
                return mInterval.sample();
            }

            ///////////////////////////
            // Arithmetic Operations //
            ///////////////////////////

            /** Adds two real algebraic numbers and returns a reference to their sum.
             * @param o
             * @return sum
             */
            RealAlgebraicNumberIR& add( RealAlgebraicNumberIR& o ) throw ( invalid_argument );

            /** Returns the negative value.
             * @return negative value
             */
            RealAlgebraicNumberIR& minus() const;

            /** Multiplies two real algebraic numbers and returns a reference to their product.
             * @param o
             * @return product
             */
            RealAlgebraicNumberIR& mul( RealAlgebraicNumberIR& o ) throw ( invalid_argument );

            /** Returns the inverse.
             * @return inverse value
             */
            RealAlgebraicNumberIR& inverse() const throw ( invalid_argument );

            /** Returns the power.
             * @param e
             * @return inverse value
             */
            RealAlgebraicNumberIR& pow( int e ) throw ( invalid_argument );

            ///////////////////////////
            // Relational Operations //
            ///////////////////////////

            /** Compares two real algebraic numbers for equality. Note that both numbers could be muted by means of refinement!
             * @param o
             * @return true in case the other real algebraic number is equals to this one
             */
            const bool isEqual( RealAlgebraicNumberIR& o );

            /** Checks whether this number is less than the other while assuming that the two numbers are unequal. Note that both numbers could be muted by means of refinement!
             * @param o
             * @return true in case the other real algebraic number is less to this one if the two number do <b>not</b> equal (otherwise there might be an infinite refinement loop)
             */
            const bool isLessWhileUnequal( RealAlgebraicNumberIR& o );

            /** Compares two real algebraic numbers by less-than. Note that both numbers could be muted by means of refinement!
             * @param o reference to the other real algebraic number.
             * @return true in case the other real algebraic number is strictly less than this one
             */
            const bool isLess( RealAlgebraicNumberIR& o );

            ////////////////////////
            // Methods from basic //
            ////////////////////////

            bool info( unsigned inf ) const;

            ////////////////////
            // Static Methods //
            ////////////////////

            /**
             * @param s the main variable of the underlying polynomial
             * @return the RealAlgebraicNumberIR representation for 0
             */
            static RealAlgebraicNumberIR* zero( const symbol& s );

        protected:

            ////////////////////////
            // Methods from basic //
            ////////////////////////

            bool is_equal_same_type( const basic& other ) const;

            void do_print( const print_context& c, unsigned level = 0 ) const;

            /**
             * Outputs the midpoint of the isolating interval after <code>level</code> additional refinements.
             *
             * Note that the refinements are not performed on this object but on a copy since this method does not mute this object.
             *
             * @param level number of additional refinements
             * @return midpoint of the isolating interval after <code>level</code> additional refinements
             */
            ex evalf( int level = 0 ) const;

            unsigned calchash() const;

        private:

            ////////////////
            // Attributes //
            ////////////////

            /// polynomial of this interval representation
            RationalUnivariatePolynomial mPolynomial;
            /// isolating interval of this interval representation
            OpenInterval mInterval;
            /// Standard Sturm sequence of the polynomial and its derivative
            list<RationalUnivariatePolynomial> mSturmSequence;
            /// number of refinements executed to the isolating interval
            unsigned mRefinementCount;

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Private zero constructor.
             * @param s main symbol of the polynomial belonging to the real algebraic number
             */
            RealAlgebraicNumberIR( const symbol& s ) throw ( invalid_argument );
    };

    typedef std::tr1::shared_ptr<RealAlgebraicNumberIR> RealAlgebraicNumberIRPtr;

}    // namespace GiNaC

#endif
