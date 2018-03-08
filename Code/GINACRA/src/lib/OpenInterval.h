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


#ifndef GINACRA_OPENINTERVAL_H
#define GINACRA_OPENINTERVAL_H

//#include <ginac/ginac.h>
#include <stdexcept>

//#include "settings.h"

namespace GiNaCRA
{
    using GiNaC::basic;
    using GiNaC::numeric;
    using GiNaC::ex;
    using GiNaC::print_context;
    using GiNaC::status_flags;

    //////////////
    // Typedefs //
    //////////////

    class GINACRA_API OpenInterval;
    typedef std::map<GiNaC::symbol, OpenInterval, GiNaC::ex_is_less> evalintervalmap;

    /**
     * A class for an open interval providing interval arithmetic operations.
     * All operations are performed in constant time.
     *
     * @author Ulrich Loup
     * @since 2010-08-03
     * @version 2012-05-14
     * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
     */
    class GINACRA_API OpenInterval:
        public basic
    {
        // Call GiNaC macro (registrar.h) for initiating the implementation into the basic type.
        GINAC_DECLARE_REGISTERED_CLASS(OpenInterval, basic)

        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Constructs an open interval ]n-1, n+1[.
             * @param n middle
             */
            OpenInterval( const numeric& n );

            /**
             * Constructs an open interval ]l, r[.
             * @param l left bound of the open interval ]l, r[
             * @param r right bound of the open interval ]l, r[
             */
            OpenInterval( const numeric& l, const numeric& r ) throw ( std::invalid_argument );

            /**
             * Constructs an open interval from another.
             * @param i other open interval
             */
            OpenInterval( const OpenInterval& i );

            ~OpenInterval();

            ///////////////
            // Selectors //
            ///////////////

            /**
             * Set new left bound for the interval.
             * @param l new left bound
             */
            void setLeft( const numeric& l ) throw ( std::invalid_argument );

            /**
             * Set new right bound for the interval.
             * @param r new right bound
             */
            void setRight( const numeric& r ) throw ( std::invalid_argument );

            /**
             * Selects the left bound.
             * @return numeric
             */
            const numeric left() const;

            /**
             * Selects the right bound.
             * @return numeric
             */
            const numeric right() const;

            ////////////////
            // Operations //
            ////////////////

            /**
             * @return true in case the bounds of the interval are both zero
             */
            const bool isZero() const;

            /**
             * @return true in case the interval is zero or it does not contain zero and its right bound is not zero itself (for root order determination)
             */
            const bool isNormalized() const;

            /**
             * @param n
             * @return true in case n is contained in this OpenInterval
             */
            const bool contains( const numeric& n ) const;

            /**
             * @param o
             * @return true in case o is a subset of this OpenInterval
             */
            const bool contains( const OpenInterval& o ) const;

            /**
             *
             * @param n
             * @return true in case n meets the interval bounds or a point inbetween
             */
            const bool meets( const numeric& n ) const;

            /**
             * @param o
             * @return intersection with the given OpenInterval and this OpenInterval, or (0, 0) in case the intersection is empty
             */
            const OpenInterval intersection( const OpenInterval& o ) const;

            /**
             * @return the midpoint of this interval
             */
            const numeric midpoint() const;

            /** Chooses a numeric value out of the interval with the smallest numeric representation.
             * The core algorithm works with machine integer arithmetic whenever possible.
             * @complexity O( lcm( denominator( Left() ) * denominator( Right() ) )^2 )
             * @return a sample value with a minimal numeric representation
             */
            const numeric sample() const;

            /** Returns sample() if the bounds are small enough for machine computations and midpoint otherwise.
             * @return sample() if the bounds are small enough for machine computations and midpoint otherwise
             */
            const numeric sampleFast() const
            {
                return (mLeft.numer() < RealAlgebraicNumberSettings::MAX_FASTSAMPLE_BOUND
                        && mRight.numer() < RealAlgebraicNumberSettings::MAX_FASTSAMPLE_BOUND
                        && mLeft.denom() < RealAlgebraicNumberSettings::MAX_FASTSAMPLE_BOUND
                        && mRight.denom() < RealAlgebraicNumberSettings::MAX_FASTSAMPLE_BOUND) ? sample() : midpoint();
            }

            /**
             * Computes the absolute value of this interval, i.e. the maximum of the absolute values of its bounds.
             * @return absolute value of the interval
             * @see Marc Daumas, Guillaume Melquiond, and Cesar Munoz - "Guaranteed Proofs Using Interval Arithmetic".
             */
            const OpenInterval abs() const;

            ///////////////////////////
            // Arithmetic Operations //
            ///////////////////////////

            /** Adds two intervals and returns their sum.
             * @param o
             * @return sum
             */
            const OpenInterval add( const OpenInterval& o ) const;

            /** Returns the negative value.
             * @return negative value
             */
            const OpenInterval minus() const;

            /** Multiplies two intervals and returns their product.
             * @param o
             * @return product
             */
            const OpenInterval mul( const OpenInterval& o ) const;

            /** Divides two intervals.
             * @param o
             * @return this interval divided by the argument
             * @throws invalid_argument in case the argument interval contains zero
             */
            const OpenInterval div( const OpenInterval& o ) const throw ( std::invalid_argument );

            /** Computes the power to <code>e</code> of this interval.
             * @param e exponent
             * @return power to <code>e</code> of this interval
             */
            const OpenInterval pow( unsigned e ) const;

            /**
             *
             * @param p
             * @param m
             * @return
             */
            static OpenInterval evaluate( const ex& p, evalintervalmap m ) throw ( std::invalid_argument );

            ///////////////////////////
            // Relational Operations //
            ///////////////////////////

            /**
             * @param o
             * @return true in case the other interval equals this
             */
            const bool isEqual( const OpenInterval& o ) const;

            /** Compares only the left bounds of the involved intervals.
             * @param o
             * @return true in case the other interval is less then this
             */
            const bool isLess( const OpenInterval& o ) const;

            /** Compares only the right bounds of the involved intervals.
             * @param o
             * @return true in case the other interval is greater then this
             */
            const bool isGreater( const OpenInterval& o ) const;

        protected:

            /////////////////////////
            // Methods from basic  //
            /////////////////////////

            bool is_equal_same_type( const basic& ) const;
            void do_print( const print_context&, unsigned level = 0 ) const;
            ex evalf( int level = 0 ) const;
            unsigned calchash() const;

        private:

            ////////////////
            // Attributes //
            ////////////////

            numeric mLeft;    // pointer to the left bound of the interval (pointer is fixed, value not)
            numeric mRight;    // pointer to the right bound of the interval (pointer is fixed, value not)

            /////////////////////////
            // AUXILIARY FUNCTIONS //
            /////////////////////////

            /** Finds a number t between l:=numeratorL/denominatorL and r:=numeratorR/denominatorR so that t has a minimal number of digits.
             * The algorithm uses cln arithmetic operations only.
             * @param numeratorL
             * @param denominatorL
             * @param numeratorR
             * @param denominatorR
             * @return
             */
            inline static const numeric findSample( cln::cl_I numeratorL, cln::cl_I denominatorL, cln::cl_I numeratorR, cln::cl_I denominatorR );

            /** Finds a number t between l:=numeratorL/denominatorL and r:=numeratorR/denominatorR so that t has a minimal number of digits.
             * The algorithm uses machine integer arithmetic only.
             * @param numeratorL
             * @param denominatorL
             * @param numeratorR
             * @param denominatorR
             * @return
             */
            inline static const numeric findSample( long numeratorL, long denominatorL, long numeratorR, long denominatorR );

    };    // class OpenInterval

}    // namespace GiNaC

#endif
