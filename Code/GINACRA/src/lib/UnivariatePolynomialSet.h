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


#ifndef GINACRA_UNIVARIATEPOLYNOMIALSET_H
#define GINACRA_UNIVARIATEPOLYNOMIALSET_H

#include <unordered_set>
//#include <ginac/ginac.h>
//#include "UnivariatePolynomial.h"

using std::unordered_set;
using std::pair;
using std::cout;
using std::endl;

namespace GiNaCRA
{
    /// Hash function for the unordered univariate polynomial set.
    struct GINACRA_API UnivariatePolynomialSetHasher
    {
        size_t operator ()( const UnivariatePolynomial& p ) const
        {
            return p.gethash();
        }
    };

    /// Comparison function for the unordered univariate polynomial set.
    struct GINACRA_API UnivariatePolynomialSetEquals
    {
        bool operator ()( const UnivariatePolynomial& p, const UnivariatePolynomial& q ) const
        {
            return p.isEqual( q );
        }
    };

    /**
     * This class encapsulates a set of UnivariatePolynomials and its helping methods.
     * It is important to now that the class is based on the functionality of std::unordered_set
     * but it ensures that only UnivariatePolynomials of the same main variable
     * are inserted.
     * @author Joachim Redies
     * @author Ulrich Loup
     * @since 2011-10-03
     * @version 2012-01-20
     */
    class GINACRA_API UnivariatePolynomialSet:
        public std:: unordered_set<UnivariatePolynomial, UnivariatePolynomialSetHasher, UnivariatePolynomialSetEquals>
    {
        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Creates an empty set.
             */
            UnivariatePolynomialSet(){}

            /**
             * Creates a set initialized with the contents between first (inclusively) and last (exclusively).
             * @param first
             * @param last
             */
            template<class InputIterator>
            UnivariatePolynomialSet( InputIterator first, InputIterator last ):
                std::unordered_set<UnivariatePolynomial, UnivariatePolynomialSetHasher, UnivariatePolynomialSetEquals>( first, last )
            {}

            ///////////////
            // Selectors //
            ///////////////

            /**
             * Checks whether the whole set is constant in x.
             * @param x the variable to check for
             * @return true if the set is constant otherwise false.
             */
            const bool isConstant( symbol& x ) const;

            /**
             * Return the main variable which all Polynomials share
             * in this set.
             * @return the main variable
             */
            const symbol variable() const;

            ///////////////
            // Modifiers //
            ///////////////

            /**
             * Inserts an element x into the set.
             * Throws an exception if the main variable does not fit to the main variables already in the set.
             * @param x the element to insert
             * @return an iterator to the element and true if it has been inserted and false it has been there before.
             */
            pair<UnivariatePolynomialSet::iterator, bool> insert( const UnivariatePolynomial& x ) throw ( invalid_argument );

            /**
             * Insert the elements between the iterators into the set.
             * Throws an exception if only of the inserted polynomials has a different main variable
             * then the main variable of the polynomials already in the set.
             * @param first iterator marking the beginning of the elements to insert
             * @param last iterator marking the end of the elements to insert
             */
            template<class InputIterator>
            void insert( InputIterator first, InputIterator last ) throw ( invalid_argument );

            /**
             * Removes all constant elements without parameters.
             */
            void removeNumbers();

            /**
             * Replaces all polynomials by its primitive part.
             * @return this set where all polynomials are replaced by their primitive part
             */
            const UnivariatePolynomialSet makePrimitive();
    };

}    // namespace GiNaC

#endif
