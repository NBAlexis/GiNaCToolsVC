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


#ifndef GINACRA_NUMERICREPRESENTATION_H
#define GINACRA_NUMERICREPRESENTATION_H

//#include <ginac/ginac.h>
//
//#include "RealAlgebraicNumber.h"
//#include "RationalUnivariatePolynomial.h"

namespace GiNaCRA
{
    /**
     * A real algebraic number exactly represented as a numeric.
     *
     * @author Joachim Redies
     * @author Ulrich Loup
     * @since 2011-10-14
     * @version 2012-03-15
     */
    class GINACRA_API RealAlgebraicNumberNR:
        public RealAlgebraicNumber,
        public numeric
    {
        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Construct a real algebraic number from a numeric <code>n</code>.
             * @param n
             * @param isRoot true marks this real algebraic number to stem from a root computation
             */
            RealAlgebraicNumberNR( const numeric& n, bool isRoot = true );

            /**
             * Copy constructor.
             * @param n
             */
            RealAlgebraicNumberNR( const RealAlgebraicNumberNR& n );

            /**
             * Clone-"Constructor"
             */
            RealAlgebraicNumberPtr clone() const
            {
                return RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( *this ));
            }

            ////////////////
            // Operations //
            ////////////////

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

            /** Computes a numeric value for this real algebraic number approximating it.
             * @complexity constant
             * @return a numeric value for this real algebraic number approximating it
             */
            const numeric approximateValue() const
            {
                return GiNaC::ex_to<numeric>( *this );
            }

        protected:

            ////////////////////////
            // Methods from basic //
            ////////////////////////

            void do_print( const print_context& c, unsigned level = 0 ) const;

    };

    typedef std::tr1::shared_ptr<RealAlgebraicNumberNR> RealAlgebraicNumberNRPtr;

}

#endif
