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
 * @file RealAlgebraicNumberFactory_unittest.cpp
 *
 * @since: 2011-04-08
 * @version 2012-05-05
 * @author: Joachim Redies
 * @author: Ulrich Loup
 */

#include "RealAlgebraicNumberFactory_unittest.h"
#include "operators.h"

using GiNaCRA::OpenInterval;
using GiNaCRA::RealAlgebraicNumberPtr;
using GiNaCRA::RealAlgebraicNumberIRPtr;
using GiNaCRA::RealAlgebraicNumberNR;
using GiNaCRA::RealAlgebraicNumberIR;
using GiNaCRA::RealAlgebraicNumberFactory;
using GiNaCRA::UnivariatePolynomial;
using GiNaCRA::RationalUnivariatePolynomial;

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( RealAlgebraicNumberFactoryTest );

void RealAlgebraicNumberFactoryTest::setUp()
{
#ifdef GINACRA_INTERVALREPRESENTATIONFACTORYTEST_DEBUG
    cout << "algorithmsTest::setUp()" << endl;
#endif

}

void RealAlgebraicNumberFactoryTest::tearDown(){}

void RealAlgebraicNumberFactoryTest::testRealRoots()
{
    symbol s( "x" );

    list<RealAlgebraicNumberPtr> roots = RealAlgebraicNumberFactory::realRoots( RationalUnivariatePolynomial( s - 1, s ));
    CPPUNIT_ASSERT_EQUAL( 1, (int)roots.size() );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( 1 )), roots.front() );

    ex p  = pow( s, 4 ) - 2;
    roots = RealAlgebraicNumberFactory::realRoots( RationalUnivariatePolynomial( p, s ));
    list<RealAlgebraicNumberPtr>::const_iterator iter = roots.begin();
    CPPUNIT_ASSERT_EQUAL( 2, (int)roots.size() );
    CPPUNIT_ASSERT( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( -sqrt( sqrt( numeric( 2 ))))) = *(iter++) );
    CPPUNIT_ASSERT( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( sqrt( sqrt( numeric( 2 ))))) = *iter );

    roots = RealAlgebraicNumberFactory::realRoots( RationalUnivariatePolynomial( pow( s, 5 ) - 3 * pow( s, 4 ) + pow( s, 3 ) - pow( s, 2 ) + 2 * s
                                                                                 - 2, s ));
    CPPUNIT_ASSERT_EQUAL( (size_t)1, roots.size() );    // exactly one non-trivial irrational real root

    roots = RealAlgebraicNumberFactory::realRoots( RationalUnivariatePolynomial( s * (s - 5) * (s + 5) * (s - 23) * (s + 2), s ));
    //    for( auto i = roots.begin(); i != roots.end(); ++i )
    //        std::cout << " usorted:" << *i << std::endl;
    roots.sort();    // to get a comparable result not influenced by heuristics
    iter = roots.begin();
    //    for( auto i = roots.begin(); i != roots.end(); ++i )
    //        std::cout << " " << *i << std::endl;
    CPPUNIT_ASSERT_EQUAL( (size_t)5, roots.size() );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( -5 )), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( -2 )), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( 0 )), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( 5 )), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( 23 )), *(iter) );

    //     polynomial factorized: (-3+17*X)*(-4+17*X)*(-5+17*X)*(-6+17*X)*(-7+17*X)*(-8+17*X)*(-9+17*X)*(-10+17*X)*(-11+17*X)*(-12+17*X)
    roots = RealAlgebraicNumberFactory::realRoots(
        RationalUnivariatePolynomial(
            numeric( 239500800, 2015993900449 )
            - numeric( 383970240, 118587876497 )
              * static_cast<ex>(s)+numeric( 270074016, 6975757441 ) * pow( s, 2 ) - numeric( 109911300, 410338673 ) * pow( s, 3 )
                               + numeric( 28699460, 24137569 ) * pow( s, 4 ) - numeric( 5030235, 1419857 ) * pow( s, 5 )
                               + numeric( 600033, 83521 ) * pow( s, 6 ) - numeric( 48150, 4913 ) * pow( s, 7 ) + numeric( 2490, 289 ) * pow( s, 8 )
                               - numeric( 75, 17 ) * pow( s, 9 ) + pow( s, 10 ), s ));
    iter = roots.begin();
    CPPUNIT_ASSERT_EQUAL( (size_t)10, roots.size() );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 3, 17 ))), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 4, 17 ))), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 5, 17 ))), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 6, 17 ))), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 7, 17 ))), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 8, 17 ))), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 9, 17 ))), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 10, 17 ))), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 11, 17 ))), *(iter++) );
    CPPUNIT_ASSERT_EQUAL( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 12, 17 ))), *(iter++) );
}

void RealAlgebraicNumberFactoryTest::testCommonRealRoots()
{
    const symbol x( "x" );
    ex sqrt4_5 = pow( x, 4 ) - 5;
    ex sqrt3_5 = pow( x, 3 ) - 5;
    ex sqrt2_2 = pow( x, 2 ) - 2;
    ex two     = x - 2;
    ex e1      = sqrt4_5 * sqrt3_5 * sqrt2_2 * two;
    ex e2      = sqrt4_5 * sqrt2_2;
    ex e3      = sqrt3_5 * sqrt2_2 * two;
    list<RationalUnivariatePolynomial> l = list<RationalUnivariatePolynomial>();
    l.push_back( RationalUnivariatePolynomial( e1.expand(), x ));
    l.push_back( RationalUnivariatePolynomial( e2.expand(), x ));
    l.push_back( RationalUnivariatePolynomial( e3.expand(), x ));
    list<RealAlgebraicNumberPtr> roots = RealAlgebraicNumberFactory::commonRealRoots( l );
    //     for(list<RealAlgebraicNumberPtr>::const_iterator root = roots.begin(); root != roots.end(); ++root)
    //      print( *root, std::cout << " " );
    CPPUNIT_ASSERT_EQUAL( 2, static_cast<int>(roots.size()));
    //    CPPUNIT_ASSERT( roots.front( ).Interval( ).contains( -sqrt( numeric( 2 ) ) ) );
    //    CPPUNIT_ASSERT( roots.back( ).Interval( ).contains( sqrt( numeric( 2 ) ) ) );
}

void RealAlgebraicNumberFactoryTest::testRealRootsEval()
{
    symbol x( "x" ), y( "y" );
    UnivariatePolynomial p1( pow( x, 2 ) - 2, x );
    UnivariatePolynomial p2( 3 * (y + x), y );
    //    std::cout << p2 << " eval in roots of " << p1 << ":" << std::endl;
    list<RealAlgebraicNumberPtr>     roots    = RealAlgebraicNumberFactory::realRoots( p1 );
    vector<RealAlgebraicNumberIRPtr> evalList = vector<RealAlgebraicNumberIRPtr>();
    evalList.push_back( std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( roots.back() ));
    vector<symbol>               varList = vector<symbol>( 1, x );
    list<RealAlgebraicNumberPtr> points  = RealAlgebraicNumberFactory::realRootsEval( p2, evalList, varList );
    CPPUNIT_ASSERT_EQUAL( points.front(), roots.front() );
    //    for( auto i = points.begin(); i != points.end(); ++i )
    //        std::cout << " " << *i << std::endl;
}
