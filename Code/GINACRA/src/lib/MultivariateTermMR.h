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


#ifndef GINACRA_MULTIVARIATETERMMR_H
#define GINACRA_MULTIVARIATETERMMR_H

// #define GINACRA_MULTIVARIATEPOLYNOMIAL_DEBUG

//#include <ginac/ginac.h>
#include <stdexcept>
#include <utility>
//
//#include "MultivariateMonomialMR.h"
//#include "MultivariateCoefficientMR.h"
//#include "utilities.h"

namespace GiNaCRA
{
    /**
     * A class for a multivariate polynomial providing a degree-based representation.
     *
     * @author Sebastian Junges
     * @since 2010-11-26
     * @version 2011-12-08
     *
     * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
     */
    class GINACRA_API MultivariateTermMR:
        public MultivariateMonomialMR
    {
        public:

            /**
             * Does nothing, just to be able to return something empty
             */
            MultivariateTermMR():
                mCoeff()
            {}

            /**
             *
             * @param size The number of variables expected, to allocate space at initialization.
             */
            MultivariateTermMR( unsigned size ):
                MultivariateMonomialMR( size ),
                mCoeff( 1 )
            {}

            /**
             *
             * @param coeff
             */
            MultivariateTermMR( GiNaC::ex coeff ):
                MultivariateMonomialMR(),
                mCoeff( coeff )
            {}

            /**
             *
             * @param m1
             * @param coeff
             */
            MultivariateTermMR( const MultivariateMonomialMR& m1, const GiNaC::ex& coeff ):
                MultivariateMonomialMR( m1 ),
                mCoeff( coeff )
            {}

            /**
             *
             * @param m1
             * @param coeff
             */
            MultivariateTermMR( const MultivariateMonomialMR& m1, const MultivariateCoefficientMR& coeff ):
                MultivariateMonomialMR( m1 ),
                mCoeff( coeff )
            {}

            /**
             *
             * @param m1
             */
            MultivariateTermMR( const MultivariateMonomialMR& m1 ):
                MultivariateMonomialMR( m1 ),
                mCoeff( 1 )
            {}

            friend bool operator ==( const MultivariateTermMR& t1, const MultivariateTermMR& t2 );
            friend const MultivariateTermMR operator *( const MultivariateTermMR& t1, const MultivariateTermMR& t2 );
            friend const MultivariateTermMR operator *( const MultivariateTermMR& t1, const MultivariateMonomialMR& m1 );
            friend const MultivariateTermMR operator *( const MultivariateMonomialMR& m1, const MultivariateTermMR& t1 );

            /**
             * Compares the monomials
             * @param m2
             * @return
             */
            inline bool hasEqualExponents( const MultivariateTermMR& m2 ) const
            {
                if( mTotDeg != m2.mTotDeg || mExponents.size() != m2.mExponents.size() )
                    return false;
                return std::equal( mExponents.begin(), mExponents.end(), m2.mExponents.begin() );
            }

            /**
             *
             * @return
             */
            inline GiNaC::ex toEx() const
            {
                return getCoeffExpr() * super::toEx();
            }

            /**
             *
             * @return
             */
            inline GiNaC::ex getCoeffExpr() const
            {
                return mCoeff.getExpression();
            }

            /**
             *
             * @return the coefficient
             */
            inline MultivariateCoefficientMR getCoeff() const
            {
                return mCoeff;
            }

            /**
             *
             * @return The additive inverse of the term.
             */
            inline MultivariateTermMR negate() const
            {
                return MultivariateTermMR( *this, -mCoeff );
            }

            /*
             * Part of the SPolynomial calculation.
             * @param m1
             * @return lcm(mon(this),m1) divided by t1
             */
            const MultivariateTermMR lcmdivt( const MultivariateMonomialMR& m1 ) const;

            /**
             *
             * @param denom
             * @return
             */
            bool dividable( const MultivariateTermMR& denom ) const;

            /**
             *
             * @param denom
             * @return
             */
            std::pair<MultivariateTermMR, bool> divby( const MultivariateTermMR& denom ) const;

            /**
             *
             * @param c
             * @return
             */
            MultivariateTermMR divide( const ex& c ) const
            {
                return MultivariateTermMR( *this, mCoeff.getExpression() / c );
            }

            /**
             * @param os
             * @param rhs
             * @return
             */
            friend std::ostream& operator <<( std::ostream& os, const MultivariateTermMR& rhs );

        protected:
            MultivariateCoefficientMR mCoeff;

        private:
            typedef MultivariateMonomialMR super;
    };

}

/*
namespace std {

        template<typename t1, typename t2>
        pair<const GiNaCRA::MultivariateTermMR, bool>& pair<const GiNaCRA::MultivariateTermMR, bool>::operator=(const pair<const GiNaCRA::MultivariateTermMR, bool>& input);

}*/

#endif
