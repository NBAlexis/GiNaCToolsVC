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


// #define GINACRA_INTERVALREPRESENTATION_DEBUG

/**
 * @file RealAlgebraicNumberIR.cpp
 *
 * @author Ulrich Loup
 * @since 2010-07-28
 * @version 2012-05-15
 * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
 */

#include <assert.h>
//
//#include "RealAlgebraicNumberIR.h"

using GiNaC::ZERO_SIGN;
using GiNaC::POSITIVE_SIGN;
using GiNaC::NEGATIVE_SIGN;
using GiNaC::gcd;
using std::cout;
using std::endl;

namespace GiNaCRA
{
    // Call GiNaC macro (registrar.h) for completing the implementation into the basic type.

    GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(RealAlgebraicNumberIR, basic, print_func<print_context>( &RealAlgebraicNumberIR::do_print ))

    //////////////////////////
    // Con- and destructors //
    //////////////////////////

    RealAlgebraicNumberIR::RealAlgebraicNumberIR():
        RealAlgebraicNumber( true, true, 0 ),
        mPolynomial(),
        mInterval(),
        mSturmSequence( RationalUnivariatePolynomial::standardSturmSequence( mPolynomial, mPolynomial.diff() )),
        mRefinementCount( 0 )
    {
        setflag( GiNaC::status_flags::expanded );
    }

    RealAlgebraicNumberIR::RealAlgebraicNumberIR( const symbol& s ) throw ( invalid_argument ):
        RealAlgebraicNumber( true, true, 0 ),
        mPolynomial( s, s ),
        mInterval( 0, 0 ),
        mSturmSequence( RationalUnivariatePolynomial::standardSturmSequence( mPolynomial, mPolynomial.diff() )),
        mRefinementCount( 0 )
    {
        setflag( status_flags::expanded );
    }

    RealAlgebraicNumberIR::RealAlgebraicNumberIR( const RationalUnivariatePolynomial& p,
                                                  const OpenInterval& i,
                                                  const list<RationalUnivariatePolynomial>& seq,
                                                  const bool normalize,
                                                  const bool isRoot )
            throw ( invalid_argument ):
        RealAlgebraicNumber( isRoot,
                             false,
                             0 ),
#ifdef GINACRA_INTERVALREPRESENTATION_OPT_NORMALIZE_POLYNOMIAL
        mPolynomial( p.sepapart() ),
#else
        mPolynomial( p ),
#endif
        mInterval( i ),
        mSturmSequence( seq.empty() ? RationalUnivariatePolynomial::standardSturmSequence( p, p.diff() ) : seq ),
        mRefinementCount( 0 )
    {
        if( mPolynomial.isConstant() )
            throw invalid_argument( "A real algebraic number must not been initialized with a constant polynomial." );
        if( normalize )
            normalizeInterval();
        if( mInterval.contains( 0 ))
            mIsNumeric = true;
        if( mPolynomial.degree() <= 1 )
        {
            mIsNumeric = true;
            numeric a  = mPolynomial.coeff( 1 );
            numeric b  = mPolynomial.coeff( 0 );
            mValue     = a == 0 ? b : -b / a;
            mInterval.setLeft( OpenInterval( mInterval.left(), mValue ).sampleFast() );
            mInterval.setRight( OpenInterval( mValue, mInterval.right() ).sampleFast() );
        }
        setflag( GiNaC::status_flags::expanded );
    }

    RealAlgebraicNumberIR::~RealAlgebraicNumberIR(){}

    RealAlgebraicNumberPtr RealAlgebraicNumberIR::clone() const
    {
        return RealAlgebraicNumberIRPtr( new RealAlgebraicNumberIR( *this ));
    }

    /////////////////////////
    // Methods from basic  //
    /////////////////////////

    int RealAlgebraicNumberIR::compare_same_type( const basic& other ) const
    {
        RealAlgebraicNumberIR o = static_cast<const RealAlgebraicNumberIR&>(other);
        // may not use isEqual since this method only works non-mutably, take heuristics
        if( mInterval.right() <= o.mInterval.left() )
            return -1;
        if( o.mInterval.right() <= mInterval.left() )
            return 1;
        return 0;
    }

    bool RealAlgebraicNumberIR::is_equal_same_type( const basic& other ) const
    {
        // for this method one may not use isEqual since this method only works non-mutably, take heuristics (if heuristics result in false, the result is correct, otherwise not necessarily
        RealAlgebraicNumberIR o = static_cast<const RealAlgebraicNumberIR&>(other);
        if( (mInterval.isZero() && o.interval().isZero()) || (mIsNumeric && o.mIsNumeric && mValue == o.mValue) )    // fast exact case
            return true;
        if( mInterval.right() <= o.mInterval.left() || o.mInterval.right() <= mInterval.left() )    // exact case without refinement
            return false;
        // now that intervals have nonzero intersection, check for possible common root
        //    ex ca = ex();
        //    ex cb = ex();
        //    if( gcd( o.polynomial( ), mPolynomial ) != 1 ) // polynomials have common factor (might still be a different root)
        //        return true;
        return true;
    }

    void RealAlgebraicNumberIR::do_print( const print_context& c, unsigned level ) const
    {
        // print_context::s is a reference to an ostream
        c.s << '{' << static_cast<UnivariatePolynomial>(mPolynomial) << ": " << mInterval << '}' << (mIsRoot ? "~" : "");
        if( mIsNumeric )
            c.s << " (" << mValue << ")";
    }

    ex RealAlgebraicNumberIR::evalf( int level ) const
    {
        if( level )
        {
            RealAlgebraicNumberIR copy( *this );
            for( int i = 0; i < level; ++i )
                copy.refine();
            return copy.approximateValue();
        }
        return mInterval.midpoint();
    }

    unsigned RealAlgebraicNumberIR::calchash() const
    {
        return mPolynomial.gethash();
    }

    bool RealAlgebraicNumberIR::info( unsigned inf ) const
    {
        switch( inf )
        {
            case GiNaC::info_flags::numeric:
            case GiNaC::info_flags::polynomial:
            case GiNaC::info_flags::rational_function:
            case GiNaC::info_flags::expanded:
            case GiNaC::info_flags::real:
            //case GiNaC::info_flags::algebraic:
                return true;
        }
        return false;
    }

    ///////////////
    // Operators //
    ///////////////

    // assignment operators

    const RealAlgebraicNumberIR& RealAlgebraicNumberIR::operator = ( const RealAlgebraicNumberIR& o )
    {
        mInterval        = o.mInterval;
        mPolynomial      = o.mPolynomial;
        mSturmSequence   = o.mSturmSequence;
        mRefinementCount = o.mRefinementCount;
        if( mInterval.contains( 0 ))
            mIsNumeric = true;
        else
            mIsNumeric = o.mIsNumeric;
        mIsRoot = o.mIsRoot;
        mValue  = o.mValue;
        return *this;
    }

    ////////////////
    // Operations //
    ////////////////

    void RealAlgebraicNumberIR::normalizeInterval() throw ( invalid_argument )
    {
        // shift the right border below zero or set the zero interval
        numeric a = (1 + mPolynomial.maximumNorm()).inverse();
        if( RationalUnivariatePolynomial::signVariations( mSturmSequence, mInterval.left() )
                > RationalUnivariatePolynomial::signVariations( mSturmSequence, -a ))    // zero is in ]left, -a[
            mInterval.setRight( -a );
        else if( RationalUnivariatePolynomial::signVariations( mSturmSequence, a )
                 > RationalUnivariatePolynomial::signVariations( mSturmSequence, mInterval.right() ))    // zero is in ]a, right[
            mInterval.setLeft( a );
        else if( !mInterval.contains( 0 ) &&!mInterval.isZero() )
            throw invalid_argument( "The interval is not suitable for this real algebraic number." );
        else    // zero is in ]-a, a[ => zero is 0
        {
            mInterval.setLeft( 0 );
            mInterval.setRight( 0 );
        }
    }

    void RealAlgebraicNumberIR::refine( RealAlgebraicNumberSettings::RefinementStrategy strategy )
    {
        if( mIsNumeric )
        {    // refine the interval based on the numeric value determined earlier
            mInterval.setLeft( OpenInterval( mInterval.left(), mValue ).sampleFast() );
            mInterval.setRight( OpenInterval( mValue, mInterval.right() ).sampleFast() );
            return;
        }
        numeric m = mInterval.midpoint();
        bool foundRootAlready = false;
        switch( strategy )
        {
            case RealAlgebraicNumberSettings::GENERIC_REFINEMENTSTRATEGY:
                // m = mInterval.midpoint();
                break;
            case RealAlgebraicNumberSettings::BINARYNEWTON_REFINEMENTSTRATEGY:
                m = mPolynomial.approximateRealRoot( m, mInterval, 1 );    // try Newton's solution as root (proceed with next case)
            case RealAlgebraicNumberSettings::BINNARYMIDPOINTSAMPLE_REFINEMENTSTRATEGY:
                if( mPolynomial.sgn( m ) == ZERO_SIGN )
                {
                    foundRootAlready = true;
                    break;
                }    // else: move on to BINARYSAMPLE_REFINEMENTSTRATEGY
            case RealAlgebraicNumberSettings::BINARYSAMPLE_REFINEMENTSTRATEGY:
                if( mRefinementCount < RealAlgebraicNumberSettings::MAXREFINE_REFINEMENTSTRATEGY )    // only take MAXREFINE_REFINEMENTSTRATEGY
                    m = mInterval.sample();
                break;
        }
        if( !foundRootAlready && mPolynomial.sgn( m ) != ZERO_SIGN )
        {    // split the interval
            if( RationalUnivariatePolynomial::signVariations( mSturmSequence, mInterval.left() )
                    > RationalUnivariatePolynomial::signVariations( mSturmSequence, m ))
                mInterval.setRight( m );
            else
                mInterval.setLeft( m );
        }
        else
        {    // split the interval including m and store m under mValue
            mInterval.setLeft( (mInterval.left() + m) / numeric( 2 ));    // in order to be compatible with algorithms purely working with refine
            mInterval.setRight( (mInterval.right() + m) / numeric( 2 ));    // in order to be compatible with algorithms purely working with refine
            mValue     = m;
            mIsNumeric = true;
        }
        ++mRefinementCount;
        assert( mInterval.left() < mInterval.right() );
    }

    bool RealAlgebraicNumberIR::refineAvoiding( numeric n )
    {
        //        cout << "Call: refine " << mPolynomial << "  " << mInterval << " avoiding " << n << " (" << *this << ")" << endl;
        if( mIsNumeric )    // refine the interval based on the numeric value determined earlier
        {
            if( !mInterval.meets( n ))
                return false;
            if( mValue < n )
                mInterval.setRight( OpenInterval( mValue, n ).sampleFast() );
            else if( mValue > n )
                mInterval.setLeft( OpenInterval( n, mValue ).sampleFast() );
            else
                return true;
            return false;
        }
        if( mInterval.contains( n ))
        {
            if( mPolynomial.sgn( n ) == ZERO_SIGN )
            {
                mValue     = n;
                mIsNumeric = true;
                return true;
            }
            // n is no root and partitions the interval, choose the half which carries the root
            if( RationalUnivariatePolynomial::signVariations( mSturmSequence, mInterval.left() )
                    > RationalUnivariatePolynomial::signVariations( mSturmSequence, n ))    // ] left(), n [ has real roots
                mInterval.setRight( n );
            else
                mInterval.setLeft( n );
            ++mRefinementCount;
        }
        else if( mInterval.left() != n && mInterval.right() != n )    // <=> !mInterval.meets(n)
            return false;
        // here, n is one of the interval bounds and the interval contains a real root => avoid n by refinement
        bool isLeft = mInterval.left() == n;    // which bound needs to be refined?
        // initial guess for the new bound
        numeric newBound = mInterval.sampleFast();
        if( mPolynomial.sgn( newBound ) == ZERO_SIGN )
        {
            mValue     = newBound;
            mIsNumeric = true;
            if( isLeft )
                mInterval.setLeft( OpenInterval( n, newBound ).sampleFast() );
            else
                mInterval.setRight( OpenInterval( newBound, n ).sampleFast() );
            return false;
        }
        if( isLeft )
            mInterval.setLeft( newBound );
        else
            mInterval.setRight( newBound );
        while( RationalUnivariatePolynomial::countRealRoots( mSturmSequence, mInterval ) == 0 )
        {
            //            cout << "Loop: refine " << mInterval << " avoiding " << n << endl;
            // refine the bound meeting n
            if( isLeft )
            {
                numeric oldBound = mInterval.left();
                numeric newBound = OpenInterval( n, oldBound ).sampleFast();
                if( mPolynomial.sgn( newBound ) == ZERO_SIGN )
                {
                    mValue     = newBound;
                    mIsNumeric = true;
                    mInterval.setLeft( OpenInterval( n, newBound ).sampleFast() );
                    return false;
                }
                mInterval.setRight( oldBound );
                mInterval.setLeft( newBound );
            }
            else
            {
                numeric oldBound = mInterval.right();
                numeric newBound = OpenInterval( oldBound, n ).sampleFast();
                if( mPolynomial.sgn( newBound ) == ZERO_SIGN )
                {
                    mValue     = newBound;
                    mIsNumeric = true;
                    mInterval.setRight( OpenInterval( newBound, n ).sampleFast() );
                    return false;
                }
                mInterval.setLeft( oldBound );
                mInterval.setRight( newBound );
            }
        }
        return false;
    }

    GiNaC::sign RealAlgebraicNumberIR::sgn() const
    {
        if( mInterval.isZero() )
            return ZERO_SIGN;
        if( mInterval.left() < 0 )
            return NEGATIVE_SIGN;
        return POSITIVE_SIGN;
    }

    GiNaC::sign RealAlgebraicNumberIR::sgn( const RationalUnivariatePolynomial& p ) const
    {
        list<RationalUnivariatePolynomial> seq = RationalUnivariatePolynomial::standardSturmSequence(
                                                     mPolynomial,
                                                     mPolynomial.isCompatible( p )
                                                     ? (RationalUnivariatePolynomial)mPolynomial.diff() * p
                                                     : RationalUnivariatePolynomial(
                                                         mPolynomial.diff()
                                                         * p.subs(
                                                             GiNaC::lst( p.variable() ),
                                                             GiNaC::lst( mPolynomial.variable() )), mPolynomial.variable() ));
        switch( RationalUnivariatePolynomial::signVariations( seq, (mInterval).left() )
                - RationalUnivariatePolynomial::signVariations( seq, (mInterval).right() ))
        {
            case 0:
                return ZERO_SIGN;
            case 1:
                return POSITIVE_SIGN;
        }
        //        case -1:
        return NEGATIVE_SIGN;
    }

    ///////////////////////////
    // Arithmetic Operations //
    ///////////////////////////

    RealAlgebraicNumberIR& RealAlgebraicNumberIR::add( RealAlgebraicNumberIR& o ) throw ( invalid_argument )
    {
        if( mInterval.isZero() || o.interval().isZero() )
            return o;
        const symbol x   = mPolynomial.variable();
        const ex     x_o = o.mPolynomial.variable();    // usually: x_o == x
        const symbol y   = symbol( "y" );
        ex res = UnivariatePolynomial( mPolynomial.subs( x == static_cast<ex>(x)-static_cast<ex>(y) ),
                                       y ).resultant( UnivariatePolynomial( o.mPolynomial.subs( x_o == y ), y ));
        RationalUnivariatePolynomial p = RationalUnivariatePolynomial( res, x ).primpart();
        list<RationalUnivariatePolynomial> seq = RationalUnivariatePolynomial::standardSturmSequence( p, p.diff() );
        OpenInterval i = mInterval + o.mInterval;    // interval of the new real algebraic number, possibly needs to be refined
        while( RationalUnivariatePolynomial::signVariations( seq, i.left() ) - RationalUnivariatePolynomial::signVariations( seq, i.right() ) > 1 )
        {    // refine as long as exactly one sign variation within the new interval
            refine();
            o.refine();
            i = mInterval + o.mInterval;    // refined interval of the new algebraic number
        }
        return *new RealAlgebraicNumberIR( p, i, seq );
    }

    RealAlgebraicNumberIR& RealAlgebraicNumberIR::minus() const
    {
        if( mInterval.isZero() )
            return *new RealAlgebraicNumberIR( *this );
        RationalUnivariatePolynomial p( mPolynomial.subs( mPolynomial.variable() == -static_cast<ex>(mPolynomial.variable())),
                                        mPolynomial.variable() );
        return *new RealAlgebraicNumberIR( p, -mInterval, list<RationalUnivariatePolynomial>(), false );    // prohibit normalization
    }

    RealAlgebraicNumberIR& RealAlgebraicNumberIR::mul( RealAlgebraicNumberIR& o ) throw ( invalid_argument )
    {
        if( mInterval.isZero() || o.interval().isZero() )
            return *zero( mPolynomial.variable() );
        const symbol x   = mPolynomial.variable();
        const ex     x_o = o.mPolynomial.variable();    // usually: x_o == x
        const symbol y   = symbol( "y" );
        RationalUnivariatePolynomial
        p = RationalUnivariatePolynomial( resultant( GiNaC::pow( y, mPolynomial.degree() )
                                                     * mPolynomial.subs( x == (static_cast<ex>(x) / static_cast<ex>(y)) ), o.mPolynomial.subs( x_o
                                                                         == y ), y ), x ).primpart();
        list<RationalUnivariatePolynomial> seq = RationalUnivariatePolynomial::standardSturmSequence( p, p.diff() );
        OpenInterval i = mInterval * o.mInterval;    // interval of the new real algebraic number, possibly needs to be refined
        while( RationalUnivariatePolynomial::signVariations( seq, i.left() ) - RationalUnivariatePolynomial::signVariations( seq, i.right() )
                > numeric( 1 ))
        {    // refine as long as exactly one sign variation within the new interval
            refine();
            o.refine();
            i = mInterval * o.mInterval;    // refined interval of the new algebraic number
        }
        return *new RealAlgebraicNumberIR( p, i, seq );
    }

    RealAlgebraicNumberIR& RealAlgebraicNumberIR::inverse() const throw ( invalid_argument )
    {
        return *new RealAlgebraicNumberIR( RationalUnivariatePolynomial(
            (GiNaC::pow( mPolynomial.variable(), mPolynomial.degree() )
             * (mPolynomial.subs(
                 mPolynomial.variable() == (numeric( 1 ) / static_cast<ex>(mPolynomial.variable()))))).expand(), mPolynomial.variable() ).primpart(),
                                           OpenInterval( mInterval.right().inverse(), mInterval.left().inverse() ));
    }

    RealAlgebraicNumberIR& RealAlgebraicNumberIR::pow( int e ) throw ( invalid_argument )
    {
        // ugly workaround:
        RealAlgebraicNumberIR r = *this;
        for( int i = 1; i != e; ++i )
            r = r.mul( r );
        return *new RealAlgebraicNumberIR( r );

        //    RealAlgebraicNumberIR res;
        //    RealAlgebraicNumberIR curpot = *this;
        //
        //    while(e > 0)
        //    {
        //        if (e % 2 == 1)
        //        {
        //            if (res == NULL) {
        //                res = res * curpot;
        //            }
        //        }
        //        curpot = curpot * curpot;
        //        e /= 2;
        //    }
        //
        //    return *new RealAlgebraicNumberIR(res);
        //
    }

    ///////////////////////////
    // Relational Operations //
    ///////////////////////////

    const bool RealAlgebraicNumberIR::isEqual( RealAlgebraicNumberIR& o )
    {
        if( (mInterval.isZero() && o.interval().isZero()) || (mIsNumeric && o.mIsNumeric && mValue == o.mValue) )    // fast exact case
            return true;
        if( mInterval.right() <= o.mInterval.left() || o.mInterval.right() <= mInterval.left() )    // exact case without refinement
            return false;
        // otherwise: the two numbers are equal iff they subtract to zero, which is the number with the zero-interval
        RealAlgebraicNumberIR oMinus = o.minus();
        return this->add( oMinus ).interval().isZero();
    }

    const bool RealAlgebraicNumberIR::isLessWhileUnequal( RealAlgebraicNumberIR& o )
    {
        // the two intervals are refined until the interval bounds uniquely determine the ordering
        while( true )
        {
            /** Check whether
             *  -----]--------[----------------
             *  --------------]--------[------- .
             */
            if( mInterval.right() <= o.mInterval.left() )
                return true;

            /** Check whether
             *  --------------]--------[-------
             *  -----]--------[---------------- .
             */
            if( o.mInterval.right() <= mInterval.left() )
                return false;

            /// * @todo improve search
            this->refine();
            o.refine();
        }
    }

    const bool RealAlgebraicNumberIR::isLess( RealAlgebraicNumberIR& o )
    {
        if( this->isEqual( o ))
            return false;
        return this->isLessWhileUnequal( o );
    }

    ////////////////////
    // Static Methods //
    ////////////////////

    RealAlgebraicNumberIR* RealAlgebraicNumberIR::zero( const symbol& s )
    {
        return new RealAlgebraicNumberIR( s );
    }

}    // namespace GiNaC

