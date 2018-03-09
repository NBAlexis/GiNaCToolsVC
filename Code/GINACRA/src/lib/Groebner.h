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


#ifndef GROEBNER_H
#define GROEBNER_H

//#include "MultivariatePolynomialMR.h"

namespace GiNaCRA
{
    /**
    * Class encapsulating the calculation of Groebner bases.
    *
    * @author Sebastian Junges
    * @since 2011-12-05
    * @version 2012-01-19
    */
    class GINACRA_API Groebner
    {
        public:

            Groebner();

            /**
             * Creates an ideal with 1 polynomial
             * @param p1
             */
            Groebner( const MultivariatePolynomialMR& p1 );

            /**
             * Creates an ideal with 2 polynomials
             * @param p1
             * @param p2
             */
            Groebner( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 );

            /**
             * Creates an ideal with 3 polynomials
             * @param p1
             * @param p2
             * @param p3
             */
            Groebner( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2, const MultivariatePolynomialMR& p3 );

            /**
             * Creates an ideal by the list of polynomials
             * @param begin_generatingset
             * @param end_generatingset
             */
            Groebner( std::list<MultivariatePolynomialMR>::iterator begin_generatingset,
                      std::list<MultivariatePolynomialMR>::iterator end_generatingset );

            void addPolynomial( const MultivariatePolynomialMR& p1 );

            /**
             * Reduce the input-ideal to a Groebner basis.
             *
             * This method implements the original Buchberger algorithm.
             * @see ISBN-10: 0387946802, Ch, 2, §7
             */
            void solve();

            /**
             * Reduces the ideal.
             */
            void reduce();

            /**
             * Output the polynomials in the internal representation.
             * @param os
             * @param rhs
             * @return
             */
            GINACRA_API friend std::ostream& operator <<( std::ostream& os, const Groebner& rhs )
            {
                os << "{";
                for( lpol_cIt i = rhs.mGB.begin(); i != rhs.mGB.end(); ++i )
                {
                    os << *i << std::endl;
                }
                return os << "}";
            }

            /**
             * Output the polynomials as expressions
             */
            void print() const
            {
                std::cout << "{" << std::endl;
                for( lpol_cIt i = mGB.begin(); i != mGB.end(); ++i )
                {
                    std::cout << i->toEx() << std::endl;
                }
                std::cout << "}";
            }

            std::list<MultivariatePolynomialMR> getBase()
            {
                return mGB;
            }

            inline bool isConstant() const
            {
                return mGB.size() == 1 && mGB.begin()->isConstant();
            }

            /**
             *
             * @return is there any polynomial in the groebner basis
             */
            inline bool isEmpty() const
            {
                return mIdeal.empty();
            }

            /**
             *
             * @return how many polynomials are actually in the basis
             */
            inline unsigned size() const
            {
                return mGB.size();
            }

            inline bool isReduced() const
            {
                return mIsReduced;
            }

            inline bool isSolved() const
            {
                return pairsToBeChecked.empty();
            }

            bool hasBeenReduced() const;

        private:
            void fillB();

            std::list<MultivariatePolynomialMR>                         mIdeal;
            std::list<MultivariatePolynomialMR>                         mGB;
            typedef std::list<MultivariatePolynomialMR>::iterator       lpol_It;
            typedef std::list<MultivariatePolynomialMR>::const_iterator lpol_cIt;

            /// A list of pairs to be checked
            std::list<std::pair<lpol_cIt, lpol_cIt> > pairsToBeChecked;

            /// A flag whether the basis is solved already
            bool mIsSolved;
            /// A flag whether the basis is reduced already
            bool mIsReduced;
    };

}
#endif   /** GROEBNER_H */
