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


#ifndef GINACRA_MULTIVARIATEMONOMIALMR_H
#define GINACRA_MULTIVARIATEMONOMIALMR_H

// #define GINACRA_MULTIVARIATEPOLYNOMIAL_DEBUG

//#include <ginac/ginac.h>
#include <stdexcept>
#include <iostream>
#include <numeric>
#include <vector>

namespace GiNaCRA
{
    typedef std::pair<unsigned, unsigned>    pui;
    typedef std::vector<pui>::const_iterator vui_cIt;

    class GINACRA_API MultivariateTermMR;

    /**
     * A class for a multivariate monomial providing a degree-based representation.
     *
     * @author Sebastian Junges
     * @since 2010-11-26
     * @version 2011-12-15
     * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
     *
     * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
     */
    class GINACRA_API MultivariateMonomialMR
    {
        public:
            friend class GINACRA_API MultivariateTermMR;
            MultivariateMonomialMR();

            /**
             * Preallocates space for .. vars.
             * @param nrVars
             */
            MultivariateMonomialMR( unsigned nrVars );
            //MultivariateMonomialMR( const GiNaC::ex& expr );

            /**
             * Creates a monomial over a single variable;
             * @param varIndex the index of the variable in the global list.
             * @param exponent the exponent
             */
            MultivariateMonomialMR( unsigned varIndex, int exponent );

            /**
             * A vector of pairs with indices and matching exponents. It is assumed that each variable occurs only once.
             * @param vecBegin
             * @param vecEnd
             */
            MultivariateMonomialMR( vui_cIt vecBegin, vui_cIt vecEnd );

            /**
             * @return the total degree, the sum of the exponents.
             * @rcomplexity constant
             */
            inline unsigned tdeg() const
            {
                return mTotDeg;
            }

            inline bool constant() const
            {
                return (tdeg() == 0);
            }

            //InternalMultivariateMonomialMR& operator=(const InternalMultivariateMonomialMR& rhs);
            //InternalMultivariateMonomialMR& operator*=(const InternalMultivariateMonomialMR& rhs);
            //InternalMultivariateMonomialMR& operator/=(const InternalMultivariateMonomialMR& rhs);

            /**
             *
             * @return an expression representing the monomial
             */
            GiNaC::ex toEx() const;

            GINACRA_API friend const MultivariateMonomialMR operator *( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 );
            GINACRA_API friend const MultivariateMonomialMR operator /( const MultivariateMonomialMR& nom, const MultivariateMonomialMR& denom );

            GINACRA_API friend bool operator !=( const MultivariateMonomialMR& lhs, const MultivariateMonomialMR& rhs );
            GINACRA_API friend bool operator ==( const MultivariateMonomialMR& lhs, const MultivariateMonomialMR& rhs );
            GINACRA_API friend std::ostream& operator <<( std::ostream& os, const MultivariateMonomialMR& rhs );

            //static bool varsMatch(const MultivariateMonomialMR& lhs, const MultivariateMonomialMR& rhs);

            /**
             * Computes the least common multiple of the two parameters
             * @param m1
             * @param m2
             * @return A monomial representing the least common multiple
             */
            static const MultivariateMonomialMR lcm( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 );

            /**
             *
             * @param m1
             * @param m2
             * @return true, iff m1 < m2
             */
            static bool LexCompare( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 );

            /**
             *
             * @param m1
             * @param m2
             * @return true iff m1 < m2
             */
            static bool GrLexCompare( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 );

            /**
             *
             * @param m1
             * @param m2
             * @return true iff m1 < m2
             */
            static bool GrRevLexCompare( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 );

        private:
            ///maps the variable x_k to the exponent
            std::vector<std::pair<unsigned, unsigned> > mExponents;
            ///we need the total degree that often that we better save it.
            unsigned mTotDeg;

    };

}
#endif
