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


#ifndef GINACRA_MULTIVARIATEPOLYNOMIALMR_H
#define GINACRA_MULTIVARIATEPOLYNOMIALMR_H

// #define GINACRA_MULTIVARIATEPOLYNOMIAL_DEBUG

//#include <ginac/ginac.h>
#include <iostream>
#include <stdexcept>

//#include "Polynomial.h"
//#include "utilities.h"
//#include "MultivariateTermMR.h"

using std::vector;
using std::invalid_argument;
using GiNaC::symbol;
using GiNaC::ex;

namespace GiNaCRA
{
    typedef bool (*MonomOrderingFc)( const MultivariateMonomialMR&, const MultivariateMonomialMR& );

    typedef std::set<MultivariateTermMR>::iterator         sMT_It;
    typedef std::set<MultivariateTermMR>::const_iterator   sMT_cIt;
    typedef std::set<MultivariateTermMR>::reverse_iterator sMT_rIt;

    /**
     * A class for comparing MultivariateMonomials according to a given function
     * @author Sebastian Junges
     * @since 2011-11-28
     */
    class GINACRA_API MonomMRCompare:
        public std:: binary_function<MultivariateMonomialMR, MultivariateMonomialMR, bool>
    {
        public:

            MonomMRCompare()
            {
                mOrderFunc = MultivariateMonomialMR::GrLexCompare;
            }

            MonomMRCompare( const MonomOrderingFc ordering )
            {
                mOrderFunc = ordering;
            }

            /**
             *
             * @param ordering
             * @return true if changed
             */
            bool SetMonomOrdering( const MonomOrderingFc ordering )
            {
                if( ordering == mOrderFunc )
                    return false;
                mOrderFunc = ordering;
                return false;
            }

            inline MonomOrderingFc GetMonomOrdering() const
            {
                return mOrderFunc;
            }

            inline bool operator ()( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 ) const
            {
                return mOrderFunc( m1, m2 );
            }

            GINACRA_API friend bool operator !=( const MonomMRCompare& m1, const MonomMRCompare& m2 );

        private:
            MonomOrderingFc mOrderFunc;

    };

    /**
     * A class for a multivariate polynomial providing a degree-based representation.
     *
     * @author Sebastian Junges
     * @since 2011-11-26
     * @version 2012-01-31
     */
    class GINACRA_API MultivariatePolynomialMR
    {
        public:
            MultivariatePolynomialMR();

            /**
             *
             * @param comp
             */
            MultivariatePolynomialMR( const MonomMRCompare& comp );

            /**
             *
             * @param t1
             * @param comp
             */
            MultivariatePolynomialMR( const MultivariateTermMR& t1, const MonomMRCompare& comp );

            /**
             *
             * @param t1
             * @param t2
             * @param comp
             */
            MultivariatePolynomialMR( const MultivariateTermMR& t1, const MultivariateTermMR& t2, const MonomMRCompare& comp );

            /**
             *
             * @param begin
             * @param last
             * @param comp
             */
            MultivariatePolynomialMR( sMT_It begin, sMT_It last, const MonomMRCompare& comp );

            /**
             * Constructs a multivariate polynomial with standard variables using graded degree lexicographic monomial ordering.
             * @param expr a polynomial
             * @param cmp the ordering
             */
            MultivariatePolynomialMR( const GiNaC::ex& expr, const MonomMRCompare& cmp );

            /**
             * Creates an object with the sum of the given terms
             * @param begin1
             * @param last1
             * @param begin2
             * @param last2
             * @param comp Monomial Ordering. Note that if this is different from the order of the sets 1 and 2, the creation of the object is slow.
             */
            MultivariatePolynomialMR( const sMT_It begin1, const sMT_It last1, const sMT_It begin2, const sMT_It last2, const MonomMRCompare& comp );

            /**
             *
             * @return
             */
            inline MonomOrderingFc getMonomOrderFunction() const
            {
                return mCmp.GetMonomOrdering();
            }

            inline MonomMRCompare getMonomOrder() const
            {
                return mCmp;
            }

            /**
             * Checks whether there are any terms
             * @return true, if zero
             */
            inline bool isZero() const
            {
                return mTerms.empty();
            }

            inline bool isConstant() const
            {
                return mTerms.size() == 1 && mTerms.begin()->constant();
            }

            /**
             * @return The leading monomial with respect to the current ordering
             */
            inline MultivariateMonomialMR lmon() const
            {
                //For performance reasons, it might be better to not do this check!
                if( !isZero() )
                {
                    return *mTerms.rbegin();
                }
                return MultivariateMonomialMR();
            }

            /**
             * @return the leading term with respect to the current ordering
             */
            inline MultivariateTermMR lterm() const
            {
                if( !isZero() )
                    return *mTerms.rbegin();
                return MultivariateTermMR();
            }

            /**
             * @return the coefficient of the leading term
             */
            inline GiNaC::ex lcoeff() const
            {
                return mTerms.rbegin()->getCoeffExpr();
            }

            /**
             * @return the number of terms
             * @rcomplexity constant
             */
            inline unsigned nrOfTerms() const
            {
                return mTerms.size();
            }

            /**
             *
             * @return a MultivariatePolynomial without the leading term.
             */
            inline const MultivariatePolynomialMR truncLT() const
            {
                return MultivariatePolynomialMR( (mTerms.begin()), --(mTerms.end()), mCmp );
            }

            /**
             * GiNaC expression representing the same multivariate polynomial.
             * @return
             */
            GiNaC::ex toEx() const;

            GINACRA_API friend bool operator ==( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 );
            GINACRA_API friend bool operator !=( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 );

            GINACRA_API friend const MultivariatePolynomialMR operator +( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 );
            GINACRA_API friend const MultivariatePolynomialMR operator +( const MultivariatePolynomialMR& p1, const MultivariateTermMR& t1 );
            GINACRA_API friend const MultivariatePolynomialMR operator +( const MultivariateTermMR& t1, MultivariatePolynomialMR& p1 );
            GINACRA_API friend const MultivariatePolynomialMR operator +( const MultivariatePolynomialMR& p1, const MultivariateMonomialMR& m1 );
            GINACRA_API friend const MultivariatePolynomialMR operator +( const MultivariateMonomialMR& m1, const MultivariatePolynomialMR& p1 );

            GINACRA_API friend const MultivariatePolynomialMR operator -( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 );
            GINACRA_API friend const MultivariatePolynomialMR operator -( const MultivariatePolynomialMR& p1 );

            //GINACRA_API friend const MultivariatePolynomialMR operator*(const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2);
            GINACRA_API friend const MultivariatePolynomialMR operator *( const MultivariatePolynomialMR& p1, const MultivariateTermMR& t1 );
            GINACRA_API friend const MultivariatePolynomialMR operator *( const MultivariateTermMR& t1, MultivariatePolynomialMR& p1 );
            GINACRA_API friend const MultivariatePolynomialMR operator *( const MultivariatePolynomialMR& p1, const MultivariateMonomialMR& m1 );
            GINACRA_API friend const MultivariatePolynomialMR operator *( const MultivariateMonomialMR& m1, const MultivariatePolynomialMR& p1 );

            /**
             *
             * @param os
             * @param rhs
             * @return
             */
            GINACRA_API friend std::ostream& operator <<( std::ostream& os, const MultivariatePolynomialMR& rhs );

            /**
             * Calculates the S-polynomial of p1 and p2
             * @param p1
             * @param p2
             * @return S-Polynomial
             */
            static const MultivariatePolynomialMR SPol( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 );

            /**
             * Calculates the remainder with respect to the ideal.
             * @param ideallistBegin
             * @param ideallistEnd
             * @return
             */
            MultivariatePolynomialMR CalculateRemainder( std::list<MultivariatePolynomialMR>::const_iterator ideallistBegin,
                                                         std::list<MultivariatePolynomialMR>::const_iterator ideallistEnd ) const;

            /**
             *
             */
            MultivariatePolynomialMR normalized();

            /**
             *
             * @param t1
             * @return
             */
            inline MultivariatePolynomialMR multiply( const MultivariateTermMR& t1 ) const
            {
                return (*this) * t1;
            }

            static bool sortByLeadingTerm( const MultivariatePolynomialMR& m1, const MultivariatePolynomialMR& m2 )
            {
                return (m1.getMonomOrderFunction()( m1.lmon(), m2.lmon() ));
            }

        protected:
            /// Ordering of Terms
            MonomMRCompare mCmp;
            /// Set of Terms
            std::set<MultivariateTermMR, MonomMRCompare> mTerms;

    };

}
#endif
