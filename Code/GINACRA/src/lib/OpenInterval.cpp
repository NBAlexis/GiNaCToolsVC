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
 * @file OpenInterval.cpp
 *
 * Implementation of the class OpenInterval.
 *
 * @author Ulrich Loup
 * @since 2010-08-03
 * @version 2012-05-14
 * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
 */

//#include <cln/cln.h>
#include <assert.h>
//
//#include "OpenInterval.h"
//#include "operators.h"
//#include "utilities.h"

namespace GiNaCRA
{
    using std::cout;
    using std::endl;

    // Call GiNaC macro (registrar.h) for completing the implementation into the basic type. This shall be performed AFTER the implementing the classes (here at the end of RealAlgebraicNumberIR.h).

    GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(OpenInterval, basic, print_func<print_context>( &OpenInterval::do_print ))

    // GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(numeric, basic,
    //   print_func<print_context>(&numeric::do_print).
    //   print_func<print_latex>(&numeric::do_print_latex).
    //   print_func<print_csrc>(&numeric::do_print_csrc).
    //   print_func<print_csrc_cl_N>(&numeric::do_print_csrc_cl_N).
    //   print_func<print_tree>(&numeric::do_print_tree).
    //   print_func<print_python_repr>(&numeric::do_print_python_repr))

    //////////////////////////
    // Con- and destructors //
    //////////////////////////

    OpenInterval::OpenInterval():
        mLeft( numeric( 0 )),
        mRight( numeric( 0 ))
    {
        setflag( status_flags::expanded );
    }

    OpenInterval::OpenInterval( const numeric& n ):
        mLeft( numeric( n - 1 )),
        mRight( numeric( n + 1 ))
    {
        setflag( status_flags::expanded );
    }

    OpenInterval::OpenInterval( const numeric& l, const numeric& r ) throw ( std::invalid_argument ):
        mLeft( numeric( l )),
        mRight( numeric( r ))
    {
#ifdef GINACRA_OPENINTERVAL_DEBUG
        cout << "OpenInterval::OpenInterval " << *this << endl;
#endif
        if( l > r )
            throw std::invalid_argument( "Specified bounds do not define an interval." );
        setflag( status_flags::expanded );
    }

    OpenInterval::OpenInterval( const OpenInterval& i ):
        mLeft( numeric( i.left() )),
        mRight( numeric( i.right() ))
    {
        setflag( status_flags::expanded );
    }

    OpenInterval::~OpenInterval(){}

    ///////////////
    // Selectors //
    ///////////////

    void OpenInterval::setLeft( const numeric& l ) throw ( std::invalid_argument )
    {
        assert( l <= mRight );    // throw std::invalid_argument( "Specified bounds do not define an interval." );
        mLeft = l;
    }

    void OpenInterval::setRight( const numeric& r ) throw ( std::invalid_argument )
    {
        assert( mLeft <= r );    // throw std::invalid_argument( "Specified bounds do not define an interval." );
        mRight = r;
    }

    const numeric OpenInterval::left() const
    {
        return mLeft;
    }

    const numeric OpenInterval::right() const
    {
        return mRight;
    }

    /////////////////////////
    // Methods from basic  //
    /////////////////////////

    int OpenInterval::compare_same_type( const basic& o ) const
    {
        const OpenInterval& oi = static_cast<const OpenInterval&>(o);
        if( this->isEqual( oi ))
            return 0;
        if( this->isLess( oi ))
            return -1;
        //  if(this->isGreater(oi)) // last case
        return 1;
    }

    bool OpenInterval::is_equal_same_type( const basic& o ) const
    {
        const OpenInterval& oi = static_cast<const OpenInterval&>(o);
        return this->isEqual( oi );
    }

    unsigned OpenInterval::calchash() const
    {
        // use the hash value of the midpoint
        hashvalue = ((mLeft + mRight) / numeric( 2 )).gethash();
        this->setflag( status_flags::hash_calculated );
        return hashvalue;
    }

    void OpenInterval::do_print( const print_context& c, unsigned level ) const
    {
        c.s << ']' << mLeft << ", " << mRight << '[';
    }

    ex OpenInterval::evalf( int level ) const
    {
        return (mLeft + mRight) / numeric( 2 );
        ;    // set the evaluated flag
    }

    ////////////////
    // Operations //
    ////////////////

    const bool OpenInterval::isZero() const
    {
        return mLeft == numeric( 0 ) && mRight == numeric( 0 );
    }

    const bool OpenInterval::isNormalized() const
    {
        return mLeft > numeric( 0 ) || mRight < numeric( 0 ) || (mLeft == numeric( 0 ) && mRight == numeric( 0 ));
    }

    const bool OpenInterval::contains( const numeric& n ) const
    {
        return (mLeft < n && mRight > n) || (n == 0 && mLeft == numeric( 0 ) && mRight == numeric( 0 ));
    }

    const bool OpenInterval::contains( const OpenInterval& o ) const
    {
        return mLeft <= o.mLeft && mRight >= o.mRight;
    }

    const bool OpenInterval::meets( const numeric& n ) const
    {
        return mLeft <= n && mRight >= n;
    }

    const OpenInterval OpenInterval::intersection( const OpenInterval& o ) const
    {
        if( mRight < o.mLeft || o.mRight < mLeft )    // intersection empty
            return OpenInterval();
        if( mLeft <= o.mLeft && mRight >= o.mRight )    // this contains o
            return OpenInterval( o );
        if( mLeft >= o.mLeft && mRight <= o.mRight )    // o contains this
            return OpenInterval( *this );
        if( mLeft <= o.mLeft && mRight <= o.mRight )    // right bound of o outside intersection
            return OpenInterval( o.mLeft, mRight );
        if( mLeft >= o.mLeft && mRight >= o.mRight )    // left bound of o outside intersection
            return OpenInterval( mLeft, o.mRight );
        // symmetric:
        // right bound of this outside intersection
        // left bound of this outside intersection
        return OpenInterval();
    }

    const numeric OpenInterval::midpoint() const
    {
        return (mLeft + mRight) / numeric( 2 );
    }

    const numeric OpenInterval::sample() const
    {
        /** Goal: Compute a rational number within the isolating interval with the smallest number representation.
         */
        if( (mLeft < numeric( 0 ) && mRight > numeric( 0 )) || (mLeft == numeric( 0 ) && mRight == numeric( 0 )))    // exclude most trivial case where the interval contains zero (which probably does not occur in practice)
            return numeric( 0 );
        // store real parts as rational numbers (safe because only rational numbers occur in this situation)
        cln::cl_RA l            = cln::rational( cln::realpart( mLeft.to_cl_N() ));
        cln::cl_RA r            = cln::rational( cln::realpart( mRight.to_cl_N() ));
        cln::cl_RA d            = r - l;    // distance d positive since r > l in a nonzero open interval
        cln::cl_I  denominatorD = cln::denominator( d );    // denom(d) = lcm( denom(l), denom(r))
        if( d > 1 )
        {    // there is an integer within the isolating interval ( this is necessary but not sufficient )
            if( cln::signum( r ) == -1 )    // both bounds are negative, so r has the smaller number representation
                return cln::denominator( r ) == 1 ? numeric( r - 1 ) : numeric( cln::floor1( r ));
            else if( cln::signum( l ) == 1 )    // both bounds are positive, so l has the smaller number representation
                return cln::denominator( l ) == 1 ? numeric( l + 1 ) : numeric( cln::ceiling1( l ));
            else if( cln::signum( r ) == 0 )    // -1 must be in the interval because of d > 1
                return numeric( -1 );
            else if( cln::signum( l ) == 0 )    // 1 must be in the interval because of d > 1
                return numeric( 1 );
            else    // that l is negative and r is positive does not often occur due to normalization of the intervals (zero not contained)
                return numeric( 0 );
        }
        else if( denominatorD == 1 )
        {    // special case: d already is an integer
            return numeric( l + (d != 1 ? 1 : d / 2) );
        }
        else
        {
            /* Perform a linear search on the denominators k from 1 to dDenom+1 so that
             * - k is minimal (done by iteration order)
             * - there is a rational s/k with lN'/lD'=l < s/k < r=rN'/rD', which is equivalent to:
             *   there is an integer i with lN = lN'*(lcm(k,dDenom)/lD') < i < rN'*(lcm(k,dDenom)/rD') = rN:
             *      lcm(k, dDenom) divides i
             * Remarks:
             * - An integer between l and r could still exist, therefore k=1 is checked as well.
             * - There is always a rational with denominator dDenom + 1 between l and r (which does not always hold for dDenom!).
             * - The integer divisions here are performed as rationals by cutting their denominators, which should always be 1. (Could increase efficiency.)
             */
            cln::cl_I numeratorL   = cln::numerator( l );
            cln::cl_I numeratorR   = cln::numerator( r );
            cln::cl_I denominatorL = cln::denominator( l );
            cln::cl_I denominatorR = cln::denominator( r );
            if( numeratorL < LONG_MAX && numeratorR < LONG_MAX && denominatorL < LONG_MAX && denominatorR < LONG_MAX )
                return OpenInterval::findSample( cln::cl_I_to_long( numeratorL ),
                                                 cln::cl_I_to_long( denominatorL ),
                                                 cln::cl_I_to_long( numeratorR ),
                                                 cln::cl_I_to_long( denominatorR ));
            return OpenInterval::findSample( numeratorL, denominatorL, numeratorR, denominatorR );
        }
    }

    const OpenInterval OpenInterval::abs() const
    {
        numeric l = GiNaC::abs( mLeft );
        numeric r = GiNaC::abs( mRight );
        if( mLeft == 0 || mRight == 0 || GiNaC::sgn( mLeft ) == GiNaC::sgn( mRight ))
            return OpenInterval( std::min<numeric>( l, r ), std::max<numeric>( l, r ));
        return OpenInterval( 0, std::max<numeric>( l, r ));
    }

    ///////////////////////////
    // Arithmetic Operations //
    ///////////////////////////

    const OpenInterval OpenInterval::add( const OpenInterval& o ) const
    {
        return OpenInterval( mLeft + o.mLeft, mRight + o.mRight );
    }

    const OpenInterval OpenInterval::minus() const
    {
        return OpenInterval( -mRight, -mLeft );
    }

    const OpenInterval OpenInterval::mul( const OpenInterval& o ) const
    {
        numeric min  = mLeft * o.mLeft;
        numeric max  = min;
        numeric next = mLeft * o.mRight;
        if( next < min )
            min = next;
        else if( max != next )
            max = next;
        next = mRight * o.mLeft;
        if( next < min )
            min = next;
        else if( next > max )
            max = next;
        next = mRight * o.mRight;
        if( next < min )
            min = next;
        else if( next > max )
            max = next;
        return OpenInterval( min, max );
    }

    const OpenInterval OpenInterval::div( const OpenInterval& o ) const throw ( std::invalid_argument )
    {
        if( o.contains( 0 ))
            throw (std::invalid_argument( "Division by interval containing zero not allowed." ));
        numeric min  = o.mLeft == 0 ? mLeft / o.mRight : mLeft / o.mLeft;    // only one, o.mLeft or o.mRight, might be 0
        numeric max  = min;
        numeric next = o.mRight == 0 ? mLeft / o.mLeft : mLeft / o.mRight;    // only one, o.mLeft or o.mRight, might be 0
        if( next < min )
            min = next;
        else if( max != next )
            max = next;
        next = o.mLeft == 0 ? mRight / o.mRight : mRight / o.mLeft;    // only one, o.mLeft or o.mRight, might be 0
        if( next < min )
            min = next;
        else if( next > max )
            max = next;
        next = o.mRight == 0 ? mRight / o.mLeft : mRight / o.mRight;    // only one, o.mLeft or o.mRight, might be 0
        if( next < min )
            min = next;
        else if( next > max )
            max = next;
        return OpenInterval( min, max );
    }

    const OpenInterval OpenInterval::pow( unsigned e ) const
    {
        if( e % 2 || mLeft >= 0 )    // e is odd or left positive
            return OpenInterval( GiNaC::ex_to<numeric>( GiNaC::pow( mLeft, e )), GiNaC::ex_to<numeric>( GiNaC::pow( mRight, e )));
        else if( mRight < 0 )
            return OpenInterval( GiNaC::ex_to<numeric>( GiNaC::pow( mRight, e )), GiNaC::ex_to<numeric>( GiNaC::pow( mLeft, e )));
        return OpenInterval( 0, GiNaC::ex_to<numeric>( std::max<ex>( GiNaC::pow( mRight, e ), GiNaC::pow( mLeft, e ))));
    }

    OpenInterval OpenInterval::evaluate( const ex& p, evalintervalmap m ) throw ( std::invalid_argument )
    {
        if( m.empty() )
            return OpenInterval();
        if( GiNaC::is_exactly_a<numeric>( p ))
            return OpenInterval() + GiNaC::ex_to<numeric>( p );

        /// Use Horner's method to perform the interval-arithmetic operations according to the polynomial p in the variable s.
        GiNaC::symbol s = m.begin()->first;
        OpenInterval i = m.begin()->second;
        OpenInterval result;
        if( m.size() == 1 )
        {
            for( int d = GiNaC::degree( p, s ); d >= 0; --d )
            {
                if( !GiNaC::is_exactly_a<numeric>( GiNaC::coeff( p, s, d )))
                    throw std::invalid_argument( "The given polynomial has more variables than defined in the evaluation map." );
                result = GiNaC::ex_to<numeric>( GiNaC::coeff( p, s, d )) + result * i;
            }
        }
        else
        {
            m.erase( m.begin() );
            for( int d = GiNaC::degree( p, s ); d >= 0; --d )
                result = OpenInterval::evaluate( GiNaC::coeff( p, s, d ), m ) + result * i;
        }
        return result;
    }

    ///////////////////////////
    // Relational Operations //
    ///////////////////////////

    const bool OpenInterval::isEqual( const OpenInterval& o ) const
    {
        return (mLeft == o.mLeft && mRight == o.mRight);    // exact same bounds
    }

    const bool OpenInterval::isLess( const OpenInterval& o ) const
    {
        /**  -----]------------[------------    <=
         *  ----------]------------[-------
         * or
         *  -----]------------[------------ <=
         *  ----------]-----[-------------- holds.
         */
        return (mLeft <= o.mLeft);    // only compare left bounds
    }

    const bool OpenInterval::isGreater( const OpenInterval& o ) const
    {
        /**  ----------]------------[-------    >=
         *  -----]------------[------------
         * or
         *  ----------]------------[------- >=
         *  -------------]----[------------ holds.
         */
        return (mRight >= o.mRight);    // only compare right bounds
    }

    /////////////////////////
    // AUXILIARY FUNCTIONS //
    /////////////////////////

    inline const numeric OpenInterval::findSample( cln::cl_I numeratorL, cln::cl_I denominatorL, cln::cl_I numeratorR, cln::cl_I denominatorR )
    {
        cln::cl_I k             = 1;    // current denominator
        cln::cl_I gcdK          = 1;
        cln::cl_I denominatorLR = cln::lcm( denominatorL, denominatorR );
        cln::cl_I lcmK          = cln::numerator( (k * denominatorLR) / gcdK );
        cln::cl_I lN            = numeratorL * (cln::numerator( lcmK / denominatorL ));
        cln::cl_I rN            = numeratorR * (cln::numerator( lcmK / denominatorR ));
        while( true )    // search stops at dDenom + 1, which is a possible refinement
        {
            // alternating search: i iterates from the beginning, j from the end
            cln::cl_I i = lN + 1;    // strict bounds!
            cln::cl_I j = rN - 1;    // strict bounds!
            while( i <= j )
            {
                cln::cl_RA candidate = i / lcmK;    // does lcmK divide i ?
                if( cln::denominator( candidate ) == k )    // yes!
                    return numeric( candidate );
                if( j != i )
                {
                    cln::cl_RA candidate = j / lcmK;    // does lcmK divide j ?
                    if( cln::denominator( candidate ) == k )    // yes!
                        return numeric( candidate );
                    --j;
                }
                ++i;
            }
            ++k;
            gcdK = cln::gcd( k, denominatorLR );
            lcmK = cln::numerator( (k * denominatorLR) / gcdK );
            lN   = numeratorL * (cln::numerator( lcmK / denominatorL ));
            rN   = numeratorR * (cln::numerator( lcmK / denominatorR ));
        }
    }

    inline const numeric OpenInterval::findSample( long numeratorL, long denominatorL, long numeratorR, long denominatorR )
    {
        long k             = 1;    // current denominator
        long gcdK          = 1;    // = GiNaC::gcd( k, denominatorLR );
        long denominatorLR = GiNaC::lcm( denominatorL, denominatorR );
        long lcmK          = GiNaC::numerator( k * denominatorLR, gcdK );
        long lN            = numeratorL * (GiNaC::numerator( lcmK, denominatorL ));
        long rN            = numeratorR * (GiNaC::numerator( lcmK, denominatorR ));
        while( true )    // search stops at dDenom + 1, which is a possible refinement
        {
            // alternating search: i iterates from the beginning, j from the end
            long i = lN + 1;    // strict bounds!
            long j = rN - 1;    // strict bounds!
            while( i <= j )
            {
                if( GiNaC::denominator( i, lcmK ) == k )    // lcmK divides i !
                    return numeric( i, lcmK );
                if( j != i )
                {
                    if( GiNaC::denominator( j, lcmK ) == k )    // lcmK divides j !
                        return numeric( j, lcmK );
                    --j;
                }
                ++i;
            }
            ++k;
            gcdK = cln::gcd( k, denominatorLR );
            lcmK = GiNaC::numerator( (k * denominatorLR), gcdK );
            lN   = numeratorL * (GiNaC::numerator( lcmK, denominatorL ));
            rN   = numeratorR * (GiNaC::numerator( lcmK, denominatorR ));
        }
    }

}    // namespace GiNaC

