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


/**
 * @file RealAlgebraicNumberFactory.cpp
 *
 * @since: 2011-10-18
 * @version: 2012-05-07
 * @author: Joachim Redies
 * @author Ulrich Loup
 */

#include <assert.h>
//
//#include "RealAlgebraicNumberFactory.h"
//#include "utilities.h"
//#include "operators.h"

namespace GiNaCRA
{
    using std::cout;
    using std::endl;

    struct polynomial_has_nonzero_sign:
        public unary_function<RationalUnivariatePolynomial, bool>
    {
        RationalUnivariatePolynomial p;

        polynomial_has_nonzero_sign( const RationalUnivariatePolynomial& p ):
            p( p )
        {}

        /**
         * Tests whether the given RationalUnivariatePolynomial has nonzero sign on the given real algebraic number.
         * @param a (unverified input)
         */
        bool operator ()( const RealAlgebraicNumberPtr& a ) const
        {
            return a->sgn( p ) != GiNaC::ZERO_SIGN;
        }
    };

    ////////////
    // Common //
    ////////////

    bool RealAlgebraicNumberFactory::equal( const RealAlgebraicNumberPtr& a, const RealAlgebraicNumberPtr& b )
    {
        RealAlgebraicNumberIRPtr aIR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( a );
        RealAlgebraicNumberNRPtr aNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( a );
        RealAlgebraicNumberIRPtr bIR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( b );
        RealAlgebraicNumberNRPtr bNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( b );

        /** Equal-type equality goes back to original operators.
         * Equality of a numerically-represented object N and an by-interval-represented object I is:
         * N == I    iff    (A): I.Polynomial() vanishes at N [thus N is among the zeros of the polynomial]
         *                      and
         *                  (B): N is contained in I.Interval() [thus N is the zero represented by I].
         */
        if( aIR != 0 )
        {
            if( bIR != 0 )    // compare two interval representations
                return *aIR == *bIR;
            else    // compare one numeric with an interval representation
            {
                if( !aIR->refineAvoiding( *bNR ))    // try to refine the isolating interval of irA to avoid nrB
                    return false;    // i.e. nrB is not in the isolating interval or not root of the polynomial of irA
            }
        }
        else if( aNR != 0 )
        {
            if( bNR != 0 )
                return static_cast<numeric>(*aNR) == static_cast<numeric>(*bNR);
            else    // compare one numerical with an interval representation
            {
                if( !bIR->refineAvoiding( *aNR ))    // try to refine the isolating interval of irB to avoid nrA
                    return false;    // i.e. nrA is not in the isolating interval or not root of the polynomial of irB
            }
        }
        return true;    // nrA must be the exact numeric representation of irB OR nrB must be the exact numeric representation of irA
    }

    bool RealAlgebraicNumberFactory::less( const RealAlgebraicNumberPtr& a, const RealAlgebraicNumberPtr& b )
    {
        if( RealAlgebraicNumberFactory::equal( a, b ))
            return false;

        /** - now intervals in possible IRs are disjoint, as well as numerics of NRs are not contained in the isolating intervals
         * - both numbers can be regarded as unequal (weak ordering is enough)
         */

        RealAlgebraicNumberIRPtr aIR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( a );
        RealAlgebraicNumberNRPtr aNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( a );
        RealAlgebraicNumberIRPtr bIR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( b );
        RealAlgebraicNumberNRPtr bNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( b );

        if( aIR != 0 )
        {
            if( bIR != 0 )
                return aIR->isLessWhileUnequal( *bIR );
            else
                return aIR->interval().right() <= b->value();
        }
        else if( aNR != 0 )
        {
            if( bNR != 0 )
                return a->value() <= b->value();
            else
                return a->value() <= bIR->interval().left();
        }
        return true;
    }

    bool RealAlgebraicNumberFactory::isRealAlgebraicNumberNR( const RealAlgebraicNumberPtr& A )
    {
        RealAlgebraicNumberNRPtr nrA = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( A );
        if( nrA != 0 )
            return true;
        else
            return false;
    }

    bool RealAlgebraicNumberFactory::isRealAlgebraicNumberIR( const RealAlgebraicNumberPtr& A )
    {
        RealAlgebraicNumberIRPtr irA = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( A );
        if( irA != 0 )
            return true;
        else
            return false;
    }

    ////////////////
    // Real Roots //
    ////////////////

    list<RealAlgebraicNumberPtr> RealAlgebraicNumberFactory::realRoots( const RationalUnivariatePolynomial& p,
                                                                        RealAlgebraicNumberSettings::IsolationStrategy pivoting )
    {
        /*
         Annotations to the algorithm:
         (1) Use Sturm's theorem:
         # real roots of p in ]l, r[ = signVariations<RationalUnivariatePolynomial>(standardSturmSequence<RationalUnivariatePolynomial>(p, p'), l) - signVariations<RationalUnivariatePolynomial>(standardSturmSequence<RationalUnivariatePolynomial>(p, p'), r)
         (2) All real roots of p are in
         (a)    ]-1-p.maximumNorm(), 1+p.maximumNorm()[,
         (b)    ]-p.oneNorm(), p.oneNorm()[,
         (c)    ]-p.twoNorm(), p.twoNorm()[, or
         (d)    ]-p.cauchyBound(), p.cauchyBound()[ (see Lemmas 10.2 and 10.3 in ISBN 0-387-94090-1).
         (3) Perform a binary (or more ~> parallel??) search on initial interval by divide & conquer.
         */

        list<RealAlgebraicNumberPtr> roots = list<RealAlgebraicNumberPtr>();    // list of p's roots
        if( p.isConstant() )
            return roots;
        list<RationalUnivariatePolynomial> seq = RationalUnivariatePolynomial::standardSturmSequence( p, p.diff() );
        // determine two initial intervals as minimal representatives of the above mentioned bounds, excluding 0 (yields normalized intervals in the first place)
        numeric l    = -1 - p.maximumNorm();
        numeric r    = 1 + p.maximumNorm();
        numeric norm = p.cauchyBound();    // twoNorm and oneNorm are upper bounds for the Cauchy bound; thus, we neglect them
        if( r > norm )
            r = norm;
        norm = -norm;
        if( l < norm )
            l = norm;
        // PREPROCESSING:
        // check whether 0 is a root and remove the respective monomial
        bool zeroRoot = p.hasZeroRoot();
        RationalUnivariatePolynomial q = zeroRoot ? RationalUnivariatePolynomial( p.nonzeropart() ) : p;
        if( zeroRoot )    // 0 is a root (which is added in the end)
            seq = RationalUnivariatePolynomial::standardSturmSequence( q, q.diff() );    // reduce Sturm sequence
        // MAIN-SEARCH:
        // recursive divide & conquer search of non-zero roots
        const unsigned varMinLeft = RationalUnivariatePolynomial::signVariations( seq, l );    // for root order computations
        searchRealRoots( varMinLeft, q, seq, OpenInterval( l, 0 ), &roots, 0, pivoting );
        searchRealRoots( varMinLeft, q, seq, OpenInterval( 0, r ), &roots, 0, pivoting );
        if( zeroRoot )
            roots.push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( 0, true )));    // mark as root
        return roots;
    }

    list<RealAlgebraicNumberPtr> RealAlgebraicNumberFactory::realRootsEval( const UnivariatePolynomial& p,
                                                                            const evalmap& m,
                                                                            RealAlgebraicNumberSettings::IsolationStrategy pivoting )
            throw ( invalid_argument )
    {
        list<RealAlgebraicNumberPtr> roots = list<RealAlgebraicNumberPtr>();
        if( p.isConstant() )
            return roots;

        /* Evaluating
         */
        symbol y = p.variable();    // variable to be solved for
        if( m.find( y ) != m.end() )
            throw invalid_argument( "The main variable of the polynomial may not occur in the evaluation map." );
        evalmap::const_iterator i = m.begin();
        ex currentResultant = GiNaC::resultant( i->second->polynomial(), p, i->first );
        //        ex currentResultant = GiNaC::resultant( p, i->second->polynomial(), i->first );
        //        ex currentResultant = UnivariatePolynomial(p, i->first).resultant(i->second->polynomial());
        map<symbol, OpenInterval, GiNaC::ex_is_less> varToInterval;
        varToInterval[i->first] = i->second->interval();
        // compute the result polynomial and the interval map over all variables
        ++i;
        for( ; i != m.end(); ++i )
        {
            currentResultant = GiNaC::resultant( i->second->polynomial(), currentResultant, i->first );
            //            currentResultant = UnivariatePolynomial(currentResultant, i->first).resultant(i->second->polynomial());
            varToInterval[i->first] = i->second->interval();
        }
        RationalUnivariatePolynomial res = RationalUnivariatePolynomial( currentResultant, y );
        list<RationalUnivariatePolynomial> seq = RationalUnivariatePolynomial::standardSturmSequence( res, res.diff() );

        /* Root-finding PREPROCESSING:
         */
        // check whether 0 is a root and remove the respective monomial
        bool zeroRoot = res.hasZeroRoot();
        RationalUnivariatePolynomial q = zeroRoot ? res.nonzeropart() : res;
        if( zeroRoot )    // 0 is a root (which is added in the end)
            seq = RationalUnivariatePolynomial::standardSturmSequence( q, q.diff() );    // reduce Sturm sequence
        // compute the Cauchy bound of p
        OpenInterval cauchyBoundInterval = OpenInterval();
        OpenInterval lcfInterval         = OpenInterval::evaluate( p.lcoeff(), varToInterval ).abs();    // we have to perform the conversion of coefficients because it is not clear whether we have a numeric or a RealAlgebraicNumberIR
        if( !lcfInterval.isZero() )
        {
            for( int d = p.ldegree(); d <= p.degree(); ++d )
                cauchyBoundInterval = cauchyBoundInterval.add( OpenInterval::evaluate( p.coeff( d ), varToInterval ).abs().div( lcfInterval ));
        }
        numeric l = -cauchyBoundInterval.right();
        numeric r = cauchyBoundInterval.right();
        // possibly optimize bounds by maximum norm of resultant
        numeric norm = 1 + res.maximumNorm();
        if( r > norm )
            r = norm;
        norm = -norm;
        if( l < norm )
            l = norm;
        //        cout << "realRootsEval: search root of " << res << " in " << l << " and "  << r << endl;
        // Root-finding MAIN-SEARCH:
        // recursive divide & conquer search of non-zero roots
        const unsigned varMinLeft = RationalUnivariatePolynomial::signVariations( seq, l );    // for root order computations
        searchRealRoots( varMinLeft, q, seq, OpenInterval( l, 0 ), &roots, 0, pivoting );
        searchRealRoots( varMinLeft, q, seq, OpenInterval( 0, r ), &roots, 0, pivoting );
        if( zeroRoot )
            roots.push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( 0, true )));    // mark as root
        return roots;
    }

    list<RealAlgebraicNumberPtr> RealAlgebraicNumberFactory::realRootsEval( const UnivariatePolynomial& p,
                                                                            const vector<RealAlgebraicNumberIRPtr>& a,
                                                                            const vector<symbol>& v,
                                                                            RealAlgebraicNumberSettings::IsolationStrategy pivoting )
            throw ( invalid_argument )
    {
        if( a.size() != v.size() )
            throw invalid_argument( "The number of specified variables does not match the number of specified numbers." );
        evalmap m = evalmap();
        for( unsigned i = 0; i != v.size(); ++i )
            m[v.at( i )] = a.at( i );
        return RealAlgebraicNumberFactory::realRootsEval( p, m );
    }

    list<RealAlgebraicNumberPtr> RealAlgebraicNumberFactory::commonRealRoots( const list<RationalUnivariatePolynomial>& l )
    {
        // heuristics: determine polynomial p with lowest degree (chance of less roots to test)
        list<RationalUnivariatePolynomial>::const_iterator q = l.begin();
        RationalUnivariatePolynomial p = *q;
        ++q;
        for( ; q != l.end(); ++q )
            if( q->degree() < p.degree() )
                p = *q;
        // determine real roots of p and remove any root which is no root of another polynomial in l
        list<RealAlgebraicNumberPtr> commonRoots = realRoots( p );
        for( q = l.begin(); q != l.end(); ++q )
            commonRoots.remove_if( polynomial_has_nonzero_sign( *q ));
        return commonRoots;
    }

    /////////////////////////
    // Auxiliary Functions //
    /////////////////////////

    void RealAlgebraicNumberFactory::searchRealRoots( const unsigned varMinLeft,
                                                      const RationalUnivariatePolynomial& p,
                                                      const list<RationalUnivariatePolynomial>& seq,
                                                      const OpenInterval& i,
                                                      list<RealAlgebraicNumberPtr>* roots,
                                                      unsigned offset,
                                                      RealAlgebraicNumberSettings::IsolationStrategy pivoting )
    {
        //    cout << "Search roots of " << p << " in " << i << endl;
        // common block
        unsigned varRight  = RationalUnivariatePolynomial::signVariations( seq, i.right() );
        int      rootCount = RationalUnivariatePolynomial::signVariations( seq, i.left() ) - varRight;
        //    cout << "Found " << rootCount << " root(s)!" << endl;

        /** rootCount is the number of real roots in i due to Sturm's theorem, where i is viewed as a CLOSED interval.
         * Note that the left and right bounds of the interval i must be no roots of the polynomial p in Sturm's theorem.
         * Since this might happen anyway, we have to check the bounds before the recursive calls and introduce appropriate offsets.
         */
        rootCount -= offset;
        if( rootCount <= 0 )    // Tests showed, that in some cases the offset is not needed what results in a negative root count when subtracting the offset anyway.
            return;
        bool middleIsRoot = false;
        // midpoint should be checked for both cases, there is a root inside i (as a heuristics for a numeric representation) or i has to be split by the middle
        numeric pivot = i.midpoint();
        if( p.sgn( pivot ) == GiNaC::ZERO_SIGN )
        {
            if( pivoting != RealAlgebraicNumberSettings::SIMPLE_ISOLATIONSTRATEGY )
                roots->push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( pivot, true )));    // mark as root
            middleIsRoot = true;
        }

        switch( pivoting )
        {
            case RealAlgebraicNumberSettings::SIMPLE_ISOLATIONSTRATEGY:
            {
                if( rootCount == 1 )
                {    // no dissection needed
                    roots->push_back( RealAlgebraicNumberIRPtr( new RealAlgebraicNumberIR( p, i, seq, false )));    // prohibit interval normalization
                    return;
                }
                if( middleIsRoot )    // in this case, pivot is a root itself what requires a correction in real root counting
                    ++offset;
                // split interval into two parts by the pivot element
                unsigned allRootCount = roots->size();
                numeric middleBoundLeft  = i.left();
                numeric middleBoundRight = i.right();
                searchRealRoots( varMinLeft, p, seq, OpenInterval( i.left(), pivot ), roots, offset, pivoting );    // search left
                if( middleIsRoot && allRootCount < roots->size() )
                {    // found roots at the left
                    allRootCount                      = roots->size();
                    RealAlgebraicNumberIRPtr lastRoot = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( roots->back() );
                    assert( lastRoot != 0 );
                    lastRoot->refineAvoiding( pivot );
                    middleBoundLeft = lastRoot->interval().right();
                }
                searchRealRoots( varMinLeft, p, seq, OpenInterval( pivot, i.right() ), roots, offset, pivoting );    // search right
                if( middleIsRoot && allRootCount < roots->size() )
                {    // found roots at the right
                    RealAlgebraicNumberIRPtr lastRoot = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( roots->back() );
                    assert( lastRoot != 0 );
                    lastRoot->refineAvoiding( pivot );
                    middleBoundRight = lastRoot->interval().left();
                    // add middle
                    roots->push_back( RealAlgebraicNumberIRPtr( new RealAlgebraicNumberIR( p, OpenInterval( middleBoundLeft, middleBoundRight ), seq,
                                                                                           false )));    // prohibit interval normalization
                }
                return;
            }
            case RealAlgebraicNumberSettings::GENERIC_ISOLATIONSTRATEGY:
                if( rootCount == 1 )
                {    // no dissection needed
                    if( middleIsRoot )
                        return;
                    roots->push_back( RealAlgebraicNumberIRPtr( new RealAlgebraicNumberIR( p, i, seq, false )));    // prohibit interval normalization
                    return;
                }
                if( middleIsRoot )    // in this case, pivot is a root itself what requires a correction in real root counting
                    ++offset;
                // split interval into two parts by the pivot element
                searchRealRoots( varMinLeft, p, seq, OpenInterval( i.left(), pivot ), roots, offset, pivoting );    // search left
                searchRealRoots( varMinLeft, p, seq, OpenInterval( pivot, i.right() ), roots, offset, pivoting );    // search right
                return;
            case RealAlgebraicNumberSettings::BINARYSAMPLE_ISOLATIONSTRATEGY:
                if( rootCount == 1 )
                {
                    if( middleIsRoot )
                        return;
                    pivot = i.sample();    // try sample as root
                    if( p.sgn( pivot ) == GiNaC::ZERO_SIGN )
                        roots->push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( pivot, true )));    // mark as root
                    else
                        roots->push_back( RealAlgebraicNumberIRPtr( new RealAlgebraicNumberIR( p, i, seq, false )));    // prohibit interval normalization
                    return;
                }
                pivot = i.sample();    // try sample as separating element
                if( p.sgn( pivot ) == GiNaC::ZERO_SIGN )    // first check it for being a root
                {
                    roots->push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( pivot, true )));    // mark as root
                    ++offset;    // because pivot is a root itself and will serve as separating element, a correction in real root counting is required
                }
                // split interval into two parts by the pivot element
                searchRealRoots( varMinLeft, p, seq, OpenInterval( i.left(), pivot ), roots, offset, pivoting );    // search left
                searchRealRoots( varMinLeft, p, seq, OpenInterval( pivot, i.right() ), roots, offset, pivoting );    // search right
                return;
            case RealAlgebraicNumberSettings::TERNARYSAMPLE_ISOLATIONSTRATEGY:
            case RealAlgebraicNumberSettings::TERNARYNEWTON_ISOLATIONSTRATEGY:
                if( rootCount == 1 )
                {    // perform bisection
                    if( middleIsRoot )
                        return;
                    if( pivoting == RealAlgebraicNumberSettings::TERNARYSAMPLE_ISOLATIONSTRATEGY )
                        pivot = i.sample();    // try sample as root
                    else    // case RealAlgebraicNumberSettings::TERNARYNEWTON_ISOLATIONSTRATEGY
                        pivot = p.approximateRealRoot( pivot, i, 1 );    // try Newton's solution as root
                    if( p.sgn( pivot ) == GiNaC::ZERO_SIGN )
                        roots->push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( pivot, true )));    // mark as root
                    else
                        roots->push_back( RealAlgebraicNumberIRPtr( new RealAlgebraicNumberIR( p, i, seq, false )));    // prohibit interval normalization
                    return;
                }
                numeric pivot2 = pivot;    // init: change nothing
                if( pivoting == RealAlgebraicNumberSettings::TERNARYSAMPLE_ISOLATIONSTRATEGY )
                    pivot2 = i.sample();    // try sample as second separating element
                else    // case RealAlgebraicNumberSettings::TERNARYNEWTON_ISOLATIONSTRATEGY
                    pivot2 = p.approximateRealRoot( pivot, i, 1 );    // try Newton's solution as second separating element
                if( pivot == pivot2 )
                {
                    // split interval into two parts by the pivot element
                    searchRealRoots( varMinLeft, p, seq, OpenInterval( i.left(), pivot ), roots, offset, pivoting );    // search left
                    searchRealRoots( varMinLeft, p, seq, OpenInterval( pivot, i.right() ), roots, offset, pivoting );    // search right
                }
                else
                {
                    if( p.sgn( pivot2 ) == GiNaC::ZERO_SIGN )    // first check it for being a root
                    {
                        roots->push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( pivot2, true )));    // mark number as root
                        ++offset;    // because pivot2 is a root itself and will serve as separating element, a correction in real root counting is required
                    }
                    if( middleIsRoot )    // in this case, pivot is also a root requiring a correction in real root counting (maximum offset of 2)
                        ++offset;
                    numeric pivotMin = std::min( pivot, pivot2 );
                    numeric pivotMax = std::max( pivot, pivot2 );
                    // split interval into three parts by the two pivot elements
                    searchRealRoots( varMinLeft, p, seq, OpenInterval( i.left(), pivotMin ), roots, offset, pivoting );
                    searchRealRoots( varMinLeft, p, seq, OpenInterval( pivotMin, pivotMax ), roots, offset, pivoting );
                    searchRealRoots( varMinLeft, p, seq, OpenInterval( pivotMax, i.right() ), roots, offset, pivoting );
                }
                return;
        }
    }

    const RealAlgebraicNumberPtr RealAlgebraicNumberFactory::evaluateIR( const UnivariatePolynomial& p,
                                                                         const vector<RealAlgebraicNumberIRPtr>& a,
                                                                         const vector<symbol>& v )
            throw ( invalid_argument )
    {
        evalmap m = evalmap();
        for( unsigned i = 0; i < v.size(); ++i )
            m[v.at( i )] = a.at( i );
        return RealAlgebraicNumberFactory::evaluateIR( p, m );
    }

    const RealAlgebraicNumberPtr RealAlgebraicNumberFactory::evaluateIR( const UnivariatePolynomial& p, const evalmap m ) throw ( invalid_argument )
    {
        //        cout << "call evalIR( " << p << "( " << p.variable() <<  " ) , [";
        //        for( evalmap::const_iterator iter = m.begin(); iter != m.end(); ++iter )
        //            cout << "  " << iter->first << " -> " << *iter->second;
        //        cout << "] )" << endl;
        //        cout << "p rational: " << GiNaC::is_rational_polynomial(p, p.variable()) <<  endl;
        //        cout << "evalmap size: " << m.size() <<  endl;
        //
        //        if( m.size() == 1 && m.begin()->second->sgn( RationalUnivariatePolynomial( p )) == GiNaC::ZERO_SIGN )
        //            return RealAlgebraicNumberIRPtr( RealAlgebraicNumberIR::zero( p.variable() ) );
        evalmap::const_iterator i = m.begin();
        symbol y                              = symbol();    // local auxiliary variable
        UnivariatePolynomial currentResultant = UnivariatePolynomial( y - p, i->first ).resultant( i->second->polynomial().inVariable( i->first ));
        map<symbol, OpenInterval, GiNaC::ex_is_less> mInterval;
        mInterval[i->first] = i->second->interval();
        // compute the result polynomial and the initial result interval
        ++i;
        for( ; i != m.end(); ++i )
        {
            currentResultant    = UnivariatePolynomial( currentResultant, i->first ).resultant( i->second->polynomial().inVariable( i->first ));
            mInterval[i->first] = i->second->interval();
        }
        //        cout << "current resultant: " << currentResultant << endl;
        RationalUnivariatePolynomial r = RationalUnivariatePolynomial( currentResultant, y );    // r in y??
        //        cout << "current resultant poly: " << r << endl;
        list<RationalUnivariatePolynomial> seq = RationalUnivariatePolynomial::standardSturmSequence( r, r.diff() );
        OpenInterval interval = OpenInterval::evaluate( p, mInterval );
        // refine the result interval until it isolates exactly one real root of the result polynomial
        //        cout << "p = " << r << endl;
        while( RationalUnivariatePolynomial::countRealRoots( seq, interval ) != 1 )
        {
            //                        cout << "i = " << interval << endl;
            for( i = m.begin(); i != m.end(); ++i )
            {
                i->second->refine();
                mInterval[i->first] = i->second->interval();
            }
            interval = OpenInterval::evaluate( p, mInterval );
        }
        //        cout << "evalIR Result: " << std::tr1::shared_ptr<RealAlgebraicNumber>( new RealAlgebraicNumberIR( r, interval )) << endl;
        return std::tr1::shared_ptr<RealAlgebraicNumber>( new RealAlgebraicNumberIR( r, interval ));
    }
}
