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


// #define GINACRA_OPENINTERVAL_DEBUG

/**
 * Implementation of the class MultivariateMonomialMR.
 *
 * @author Sebastian Junges
 * @since 2011-11-26
 * @version 2011-11-26
 * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

//#include "MultivariateMonomialMR.h"
//#include "utilities.h"
//#include "VariableListPool.h"

using std::vector;
using std::ostream;

namespace GiNaCRA
{
    bool sort_first( const std::pair<unsigned, unsigned>& p1, const std::pair<unsigned, unsigned>& p2 )
    {
        return p1.first < p2.first;
    }

    bool compare_first( const std::pair<unsigned, unsigned>& p1, const std::pair<unsigned, unsigned>& p2 )
    {
        return p1.first == p2.first;
    }

    MultivariateMonomialMR::MultivariateMonomialMR():
        mExponents(),
        mTotDeg( 0 )
    {}

    MultivariateMonomialMR::MultivariateMonomialMR( unsigned nrVars ):
        mExponents(),
        mTotDeg( 0 )
    {
        mExponents.reserve( nrVars );
    }

    MultivariateMonomialMR::MultivariateMonomialMR( unsigned varIndex, int exponent ):
        mExponents( 1, pui( varIndex, exponent ))
    {
        mTotDeg = exponent;
    }

    MultivariateMonomialMR::MultivariateMonomialMR( vui_cIt vecBegin, vui_cIt vecEnd )
    {
        mExponents = std::vector<pui>( vecBegin, vecEnd );
        std::sort( mExponents.begin(), mExponents.end(), sort_first );
        std::unique( mExponents.begin(), mExponents.end(), compare_first );
        mTotDeg = std::accumulate( vecBegin, vecEnd, 0, plus_second() );
    }

    GiNaC::ex MultivariateMonomialMR::toEx() const
    {
        GiNaC::ex expr = GiNaC::ex( 1 );
        for( vui_cIt it = mExponents.begin(); it != mExponents.end(); ++it )
        {
            expr *= GiNaC::pow( VariableListPool::getVariableSymbol( it->first ), it->second );
        }
        return expr;
    }

    const MultivariateMonomialMR MultivariateMonomialMR::lcm( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 )
    {
        if( m1.mExponents.empty() )
            return m2;
        if( m2.mExponents.empty() )
            return m1;

        vui_cIt m1it  = m1.mExponents.begin();
        vui_cIt m2it  = m2.mExponents.begin();

        vui_cIt m1end = m1.mExponents.end();
        vui_cIt m2end = m2.mExponents.end();
        unsigned tdeg = 0;
        MultivariateMonomialMR newMon( m1.mExponents.size() + m2.mExponents.size() );

        while( true )
        {
            while( m1it->first == m2it->first )
            {
                unsigned deg = std::max( m1it->second, m2it->second );
                newMon.mExponents.push_back( pui( m1it->first, deg ));
                tdeg += deg;
                ++m1it;
                ++m2it;
                if( m1it == m1end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m2it, m2end );
                    newMon.mTotDeg = std::accumulate( m2it, m2end, tdeg, plus_second() );
                    return newMon;
                }
                if( m2it == m2end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m1it, m1end );
                    newMon.mTotDeg = std::accumulate( m1it, m1end, tdeg, plus_second() );
                    return newMon;
                }
            }
            while( m1it->first < m2it->first )
            {
                newMon.mExponents.push_back( *m1it );
                tdeg += m1it->second;
                ++m1it;
                if( m1it == m1end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m2it, m2end );
                    newMon.mTotDeg = std::accumulate( m2it, m2end, tdeg, plus_second() );
                    return newMon;
                }
            }
            while( m1it->first > m2it->first )
            {
                newMon.mExponents.push_back( *m2it );
                tdeg += m2it->second;
                ++m2it;
                if( m2it == m2end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m1it, m1end );
                    newMon.mTotDeg = std::accumulate( m1it, m1end, tdeg, plus_second() );
                    return newMon;
                }
            }
        }
    }

    bool operator ==( const MultivariateMonomialMR& lhs, const MultivariateMonomialMR& rhs )
    {
        if( lhs.mTotDeg != rhs.mTotDeg )
            return false;
        return (lhs.mExponents == rhs.mExponents);
    }

    bool operator !=( const MultivariateMonomialMR& lhs, const MultivariateMonomialMR& rhs )
    {
        return !(lhs == rhs);
    }

    std::ostream& operator <<( ostream& os, const MultivariateMonomialMR& rhs )
    {
        os << "[";
        for( vui_cIt it = rhs.mExponents.begin(); it != rhs.mExponents.end(); ++it )
        {
            os << "x_" << it->first << "^" << it->second;
        }
        return (os << "]");
    }

    bool MultivariateMonomialMR::LexCompare( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 )
    {
        if( m1.tdeg() == 0 && m2.tdeg() != 0 )
            return true;
        if( m2.tdeg() == 0 )
            return false;
        vui_cIt m1it = m1.mExponents.begin();
        vui_cIt m2it = m2.mExponents.begin();

        while( m1it != m1.mExponents.end() )
        {
            if( m2it == m2.mExponents.end() )
                return false;
            //which variable occurs first
            if( m1it->first == m2it->first )
            {
                //equal variables
                if( m1it->second < m2it->second )
                    return true;
                if( m1it->second > m2it->second )
                    return false;
            }
            else
            {
                return (m1it->first > m2it->first);
            }
            ++m1it;
            ++m2it;
        }
        if( m2it == m2.mExponents.end() )
            return false;
        return true;
    }

    bool MultivariateMonomialMR::GrLexCompare( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 )
    {
        unsigned m1deg = m1.tdeg();
        unsigned m2deg = m2.tdeg();
        if( m1deg > m2deg )
            return false;
        if( m2deg > m1deg )
            return true;
        return LexCompare( m1, m2 );
    }

    bool MultivariateMonomialMR::GrRevLexCompare( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 )
    {
        unsigned m1deg = m1.tdeg();
        unsigned m2deg = m2.tdeg();
        if( m1deg > m2deg )
            return false;
        if( m2deg > m1deg )
            return true;
        return LexCompare( m2, m1 );
    }

    const MultivariateMonomialMR operator *( const MultivariateMonomialMR& m1, const MultivariateMonomialMR& m2 )
    {
        if( m1.mExponents.empty() )
            return m2;
        if( m2.mExponents.empty() )
            return m1;

        vui_cIt m1it  = m1.mExponents.begin();
        vui_cIt m2it  = m2.mExponents.begin();

        vui_cIt m1end = m1.mExponents.end();
        vui_cIt m2end = m2.mExponents.end();

        MultivariateMonomialMR newMon( m1.mExponents.size() + m2.mExponents.size() );
        newMon.mTotDeg = m1.mTotDeg + m2.mTotDeg;

        while( true )
        {
            while( m1it->first == m2it->first )
            {
                newMon.mExponents.push_back( pui( m1it->first, (m1it->second + m2it->second) ) );
                ++m1it;
                ++m2it;
                if( m1it == m1end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m2it, m2end );
                    return newMon;
                }
                if( m2it == m2end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m1it, m1end );
                    return newMon;
                }
            }
            while( m1it->first < m2it->first )
            {
                newMon.mExponents.push_back( *m1it );
                ++m1it;
                if( m1it == m1end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m2it, m2end );
                    return newMon;
                }
            }
            while( m1it->first > m2it->first )
            {
                newMon.mExponents.push_back( *m2it );
                ++m2it;
                if( m2it == m2end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m1it, m1end );
                    return newMon;
                }
            }
        }
    }

    /**  bool InternalMultivariateMonomialMR::varsMatch(const InternalMultivariateMonomialMR& lhs, const InternalMultivariateMonomialMR& rhs) {
          return (lhs.mVariables.size() == rhs.mVariables.size()) && (std::equal(lhs.mVariables.begin(), lhs.mVariables.end(), rhs.mVariables.begin()));
      }*/

}
