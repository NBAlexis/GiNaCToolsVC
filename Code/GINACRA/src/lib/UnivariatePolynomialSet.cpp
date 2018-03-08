#include "ginacra_private.h"
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


#include <assert.h>
//
//#include "UnivariatePolynomialSet.h"

/**
 * Implementation of UnivariatePolynomialSet.
 * @author Joachim Redies
 * @author Ulrich Loup
 * @since 2011-10-03
 * @version 2012-05-15
 */

namespace GiNaCRA
{
    ///////////////
    // Selectors //
    ///////////////

    const bool UnivariatePolynomialSet::isConstant( symbol& x ) const
    {
        for( UnivariatePolynomialSet::const_iterator it = this->begin(); it != this->end(); ++it )
        {
            if( static_cast<ex>(*it).degree( x ) != 0 )
                return false;
        }
        return true;
    }

    const symbol UnivariatePolynomialSet::variable() const
    {
        return this->begin()->variable();
    }

    ///////////////
    // Modifiers //
    ///////////////

    pair<UnivariatePolynomialSet::iterator, bool> UnivariatePolynomialSet::insert( const UnivariatePolynomial& x ) throw ( invalid_argument )
    {
        assert( 
            this->empty() || 
            (
                x.variable().is_equal(this->begin()->variable())
            )
        );
        //            throw invalid_argument( "The main variable does not fit!" );
        return unordered_set<UnivariatePolynomial, UnivariatePolynomialSetHasher, UnivariatePolynomialSetEquals>::insert( x );
    }

    template<class InputIterator>
    void UnivariatePolynomialSet::insert( InputIterator first, InputIterator last ) throw ( invalid_argument )
    {
        for( UnivariatePolynomialSet::iterator it = first; it != last; ++it )
            insert( *it );
    }

    void UnivariatePolynomialSet::removeNumbers()
    {
        list<UnivariatePolynomial> toDelete = list<UnivariatePolynomial>();
        for( UnivariatePolynomialSet::const_iterator it = this->begin(); it != this->end(); ++it )
            if( it->isConstant() && GiNaC::is_exactly_a<numeric>( it->lcoeff() ))
                toDelete.push_back( *it );
        for( list<UnivariatePolynomial>::const_iterator i = toDelete.begin(); i != toDelete.end(); ++i )
            this->erase( *i );
    }

    const UnivariatePolynomialSet UnivariatePolynomialSet::makePrimitive()
    {
        UnivariatePolynomialSet reducedSet = UnivariatePolynomialSet();
        for( UnivariatePolynomialSet::const_iterator it = this->cbegin(); it != this->cend(); ++it )
        {
            ex c = it->content();
            if( GiNaC::is_exactly_a<numeric>( c ))
                reducedSet.insert( it->primpart( c ));
            else
                reducedSet.insert( *it );
        }
        return reducedSet;
    }
}    // namespace GiNaC

