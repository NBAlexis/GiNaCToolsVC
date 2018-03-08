#include "ginacra_private.h"

//#include "MultivariateTermMR.h"

namespace GiNaCRA
{
    const MultivariateTermMR MultivariateTermMR::lcmdivt( const MultivariateMonomialMR& m1 ) const
    {
        if( m1.mExponents.empty() )
            return MultivariateTermMR( *this );

        vui_cIt t1it  = mExponents.begin();
        vui_cIt m1it  = m1.mExponents.begin();

        vui_cIt t1end = mExponents.end();
        vui_cIt m1end = m1.mExponents.end();
        unsigned tdeg = 0;
        MultivariateTermMR newMon( mExponents.size() + m1.mExponents.size() );
        newMon.mCoeff = mCoeff.inverse();
        while( true )
        {
            while( t1it->first == m1it->first )
            {
                unsigned deg = std::max( t1it->second, m1it->second ) - t1it->second;
                if( deg != 0 )
                {
                    newMon.mExponents.push_back( pui( t1it->first, deg ));
                    tdeg += deg;
                }
                ++t1it;
                ++m1it;
                if( t1it == t1end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m1it, m1end );
                    newMon.mTotDeg = std::accumulate( m1it, m1end, tdeg, plus_second() );
                    return newMon;
                }
                if( m1it == m1end )
                {
                    newMon.mTotDeg = tdeg;
                    return newMon;
                }
            }
            while( t1it->first < m1it->first )
            {
                ++t1it;
                if( t1it == t1end )
                {
                    newMon.mExponents.insert( newMon.mExponents.end(), m1it, m1end );
                    newMon.mTotDeg = std::accumulate( m1it, m1end, tdeg, plus_second() );
                    return newMon;
                }
            }
            while( t1it->first > m1it->first )
            {
                newMon.mExponents.push_back( *m1it );
                tdeg += m1it->second;
                ++m1it;
                if( m1it == m1end )
                {
                    newMon.mTotDeg = tdeg;
                    return newMon;
                }
            }
        }
    }

    bool MultivariateTermMR::dividable( const MultivariateTermMR& denom ) const
    {
        if( denom.mExponents.empty() )
            return true;
        if( mTotDeg < denom.mTotDeg )
            return false;

        vui_cIt t1it  = mExponents.begin();
        vui_cIt m1it  = denom.mExponents.begin();
        vui_cIt t1end = mExponents.end();
        vui_cIt m1end = denom.mExponents.end();

        //is it dividable?

        while( true )
        {
            while( t1it->first == m1it->first )
            {
                if( t1it->second < m1it->second )
                    return false;
                ++t1it;
                ++m1it;
                if( m1it == m1end )
                    return true;
                if( t1it == t1end )
                    return false;
            }
            while( t1it->first < m1it->first )
            {
                ++t1it;
                if( t1it == t1end )
                    return false;
            }
            if( t1it->first > m1it->first )
                return false;
        }

        return true;
    }

    std::pair<MultivariateTermMR, bool> MultivariateTermMR::divby( const MultivariateTermMR& denom ) const
    {
        if( denom.mExponents.empty() )
            return std::pair<const MultivariateTermMR, bool>( MultivariateTermMR( *this, mCoeff / denom.mCoeff ), true );

        if( !dividable( denom ))
            return std::pair<const MultivariateTermMR, bool>( MultivariateTermMR(), false );
            // yes it is dividable.

        vui_cIt t1it              = mExponents.begin();
        vui_cIt m1it              = denom.mExponents.begin();
        vui_cIt t1end             = mExponents.end();
        vui_cIt m1end             = denom.mExponents.end();

        MultivariateTermMR newMon = MultivariateTermMR( mExponents.size() );
        newMon.mTotDeg            = mTotDeg - denom.tdeg();
        newMon.mCoeff             = mCoeff / denom.mCoeff;

        while( true )
        {
            while( t1it->first == m1it->first )
            {
                unsigned deg = t1it->second - m1it->second;
                if( deg != 0 )
                {
                    newMon.mExponents.push_back( pui( t1it->first, deg ));
                }
                ++t1it;
                ++m1it;
                if( m1it == m1end )
                {    // if t1it == t1end than also m1it == m1end
                    newMon.mExponents.insert( newMon.mExponents.end(), t1it, t1end );
                    return std::pair<const MultivariateTermMR, bool>( MultivariateTermMR( newMon ), true );
                }
            }

            while( t1it->first < m1it->first )
            {
                newMon.mExponents.push_back( *t1it );
                ++t1it;
            }
        }
        return std::pair<const MultivariateTermMR, bool>( newMon, true );
    }

    bool operator ==( const MultivariateTermMR& t1, const MultivariateTermMR& t2 )
    {
        return (t1.mCoeff == t2.mCoeff) && ((MultivariateMonomialMR)t1 == (MultivariateMonomialMR)t2);
    }

    const MultivariateTermMR operator *( const MultivariateTermMR& t1, const MultivariateTermMR& t2 )
    {
        return MultivariateTermMR( (MultivariateMonomialMR)t1 * (MultivariateMonomialMR)t2, t1.mCoeff * t2.mCoeff );
    }

    const MultivariateTermMR operator *( const MultivariateTermMR& t1, const MultivariateMonomialMR& m1 )
    {
        return MultivariateTermMR( (MultivariateMonomialMR)t1 * m1, t1.mCoeff );
    }

    const MultivariateTermMR operator *( const MultivariateMonomialMR& m1, const MultivariateTermMR& t1 )
    {
        return t1 * m1;
    }

    std::ostream& operator <<( std::ostream& os, const MultivariateTermMR& rhs )
    {
        return os << rhs.mCoeff << (MultivariateMonomialMR)rhs;
    }
}
