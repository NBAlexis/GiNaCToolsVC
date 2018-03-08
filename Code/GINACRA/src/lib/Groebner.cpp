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


#include <algorithm>
#include <list>
//
//#include "Groebner.h"
//#include "MultivariatePolynomialMR.h"

namespace GiNaCRA
{
    Groebner::Groebner():
        mIsSolved( true ),
        mIsReduced( true )
    {}

    Groebner::Groebner( const MultivariatePolynomialMR& p1 ):
        mIsSolved( true ),
        mIsReduced( false )
    {
        mIdeal.push_back( p1 );
        mGB.assign( mIdeal.begin(), mIdeal.end() );
    }

    Groebner::Groebner( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 ):
        mIsSolved( false ),
        mIsReduced( false )
    {
        mIdeal.push_back( p1 );
        mIdeal.push_back( p2 );
        mIdeal.sort( MultivariatePolynomialMR::sortByLeadingTerm );
        mGB.assign( mIdeal.begin(), mIdeal.end() );
        fillB();
    }

    Groebner::Groebner( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2, const MultivariatePolynomialMR& p3 ):
        mIsSolved( false ),
        mIsReduced( false )
    {
        mIdeal.push_back( p1 );
        mIdeal.push_back( p2 );
        mIdeal.push_back( p3 );
        mIdeal.sort( MultivariatePolynomialMR::sortByLeadingTerm );
        mGB.assign( mIdeal.begin(), mIdeal.end() );
        fillB();

    }

    Groebner::Groebner( std::list<MultivariatePolynomialMR>::iterator begin_generatingset,
                        std::list<MultivariatePolynomialMR>::iterator end_generatingset ):
        mIsSolved( false ),
        mIsReduced( false )
    {
        mIdeal = std::list<MultivariatePolynomialMR>( begin_generatingset, end_generatingset );
        mIdeal.sort( MultivariatePolynomialMR::sortByLeadingTerm );
        mGB.assign( mIdeal.begin(), mIdeal.end() );
        fillB();
    }

    void Groebner::addPolynomial( const MultivariatePolynomialMR& p1 )
    {
        lpol_It
        inputloc = std::lower_bound<lpol_It, MultivariatePolynomialMR>( mGB.begin(), mGB.end(), p1, MultivariatePolynomialMR::sortByLeadingTerm );
        inputloc    = mGB.insert( inputloc, p1 );
        lpol_It end = mGB.end();
        // Add all new pairs
        for( lpol_It i = mGB.begin(); i != end; ++i )
        {
            if( i == inputloc )
                continue;
            //pairsToBeChecked.push_back( std::make_pair<lpol_cIt, lpol_cIt>( i, inputloc ));
            pairsToBeChecked.push_back(std::make_pair(i, inputloc));

        }

        lpol_It inputlocIdeal = std::lower_bound<lpol_It, MultivariatePolynomialMR>( mIdeal.begin(), mIdeal.end(), p1,
                                                                                     MultivariatePolynomialMR::sortByLeadingTerm );
        mIdeal.insert( inputlocIdeal, p1 );

        mIsReduced = false;
    }

    void Groebner::solve()
    {
        while( !pairsToBeChecked.empty() )
        {
            std::pair<lpol_cIt, lpol_cIt> p = pairsToBeChecked.front();
            pairsToBeChecked.pop_front();

            //   std::cout << "(i,j) =  ("<< *(p.first) << ", " << *(p.second) << ")"<< std::endl;
            MultivariatePolynomialMR r = MultivariatePolynomialMR::SPol( *(p.first), *(p.second) );
            //    std::cout << "Spol " <<r << std::endl;
            MultivariatePolynomialMR rem = MultivariatePolynomialMR::SPol( *(p.first), *(p.second) ).CalculateRemainder( mGB.begin(), mGB.end() );
            //     std::cout << "Remainder " << rem << std::endl;

            // If the remainder is not zero, we will add it to the ideal
            if( rem.isConstant() )
            {
                mGB.clear();
                mGB.push_back( rem );
                mIsSolved  = true;
                mIsReduced = true;
                return;
            }

            if( !rem.isZero() )
            {
                addPolynomial( rem );
            }

        }
    }

    void Groebner::reduce()
    {
        bool solved;
        if( pairsToBeChecked.empty() )
            solved = true;
        if( mIsReduced )
            return;
        // Minimize (faster than the reduction algorithm)
        for( lpol_It i = mGB.begin(); i != mGB.end(); )
        {
            bool div = false;
            for( lpol_It j = mGB.begin(); j != i &&!div; ++j )
            {
                div = i->lterm().dividable( j->lterm() );
            }

            lpol_It j = i;
            ++j;
            for( ; !div && j != mGB.end(); ++j )
            {
                div = i->lterm().dividable( j->lterm() );
            }

            if( div )
            {
                i = mGB.erase( i );
            }
            else
            {
                ++i;
            }
        }
        // Calculate reduction
        // The number of polynomials will not change anymore!
        std::list<MultivariatePolynomialMR> reduced;
        lpol_It i = mGB.begin();
        reduced.push_back( i->normalized() );
        for( ++i; i != mGB.end(); ++i )
        {
            reduced.push_back( i->CalculateRemainder( reduced.begin(), reduced.end() ).normalized() );
        }
        mGB.swap( reduced );

        if( solved )
        {
            mIsReduced = true;
        }
        else
        {
            fillB();
        }
    }

    void Groebner::fillB()
    {
        for( lpol_cIt i = mGB.begin(); i != mGB.end(); ++i )
        {
            for( lpol_cIt j = i; j != mGB.end(); ++j )
            {
                if( i == j )
                    continue;
                pairsToBeChecked.push_back( std::pair<lpol_cIt, lpol_cIt>( i, j ));
            }
        }
    }

    /**
     *
     * @return true, if the GroebnerBase is not equal to the initial ideal
     */
    bool Groebner::hasBeenReduced() const
    {
        if( mIdeal.size() != mGB.size() )
            return true;

        return !std::equal( mIdeal.begin(), mIdeal.end(), mGB.begin() );

    }

}
