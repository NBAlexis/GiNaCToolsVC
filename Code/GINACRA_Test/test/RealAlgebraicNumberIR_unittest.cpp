#include "ginacra_test.h"
//#include "ginacra_test.h"
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


// #define GINACRA_INTERVALREPRESENTATIONTEST_DEBUG

/**
 * @file RealAlgebraicNumberIR_unittest.cpp
 *
 * Unit tests for the class RealAlgebraicNumberIR.
 *
 * @author Ulrich Loup
 * @since 2010-09-08
 * @version 2012-05-07
 */

//#include "RealAlgebraicNumberIR_unittest.h"
//#include "operators.h"

using std::cout;
using std::endl;
using GiNaC::symbol;
using GiNaC::pow;
using GiNaCRA::UnivariatePolynomial;

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( RealAlgebraicNumberIRTest );

void RealAlgebraicNumberIRTest::setUp()
{
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << "RealAlgebraicNumberIRTest::setUp()" << endl;
#endif
    const symbol                       x( "x" );
    const RationalUnivariatePolynomial p0( ex( x ), x );
    const OpenInterval                 i0( 0, 0 );
    a0 = RealAlgebraicNumberIR( p0, i0 );    // 0
    RationalUnivariatePolynomial p1( pow( x, 3 ) - pow( x, 2 ) + 2, x );
    OpenInterval i1( -2, 0 );
    a1 = RealAlgebraicNumberIR( p1, i1 );    // -1
    const RationalUnivariatePolynomial p2( pow( x, 2 ) - 2 * x + 1, x );
    const OpenInterval                 i2( -2, 2 );
    a2 = RealAlgebraicNumberIR( p2, i2 );    // 1
    const RationalUnivariatePolynomial p3( pow( x, 2 ) - 1, x );
    a3 = RealAlgebraicNumberIR( p3, i1 );    // -1
    const OpenInterval i3( 0, 2 );
    a4 = RealAlgebraicNumberIR( p3, i3 );    // 1
    const RationalUnivariatePolynomial p5( pow( x, 2 ) - 2, x );
    a5 = RealAlgebraicNumberIR( p5, i1 );    // -sqrt(2)
    const RationalUnivariatePolynomial p6( pow( x, 3 ) - 8, x );
    const OpenInterval                 i4( 1, 4 );
    a6 = RealAlgebraicNumberIR( p6, i4 );    // 2
    const RationalUnivariatePolynomial p7( pow( x, 4 ) - numeric( 1, 16 ), x );
    const OpenInterval                 i5( 0, 1 );
    a7 = RealAlgebraicNumberIR( p7, i5 );    // 1/2
}

void RealAlgebraicNumberIRTest::tearDown(){}

void RealAlgebraicNumberIRTest::testNormalizePolynomial()
{    // done in constructor
}

void RealAlgebraicNumberIRTest::testNormalizeInterval()
{    // done in constructor
}

void RealAlgebraicNumberIRTest::testConstructor()
{
    const symbol                       s( "s" );
    const RationalUnivariatePolynomial polynomial( pow( s, 3 ) - pow( s, 2 ) + 2, s );
    const OpenInterval                 interval( -2, 0 );
    const OpenInterval                 interval_normalized( -2, numeric( -1, 3 ));
    const RealAlgebraicNumberIR        number( polynomial, interval );
    CPPUNIT_ASSERT_EQUAL( static_cast<UnivariatePolynomial>(polynomial), static_cast<UnivariatePolynomial>(number.polynomial()));
    CPPUNIT_ASSERT_EQUAL( interval_normalized, number.interval() );    // interval normalized using ( 1 / ( 1 + max. coefficient of underlying polynomial) )
    CPPUNIT_ASSERT_EQUAL( 4, (int)number.sturmSequence().size() );
    const RationalUnivariatePolynomial c( -1, s );
    CPPUNIT_ASSERT_THROW( RealAlgebraicNumberIR( c, interval ), invalid_argument );
    const RationalUnivariatePolynomial q( s - 2, s );
    CPPUNIT_ASSERT_THROW( RealAlgebraicNumberIR( q, interval ), invalid_argument );
}

void RealAlgebraicNumberIRTest::testAddition()
{
    CPPUNIT_ASSERT_EQUAL( a0, a1 + a2 );
    CPPUNIT_ASSERT_EQUAL( a0, a3 + a2 );
    CPPUNIT_ASSERT_EQUAL( a0, a1 + (a2 + (a3 + a4)) );
    CPPUNIT_ASSERT_EQUAL( a0, a4 + a3 );

    CPPUNIT_ASSERT_EQUAL( a0, a4 + (-1) );
    CPPUNIT_ASSERT_EQUAL( a0, a6 + (-2) );
}

void RealAlgebraicNumberIRTest::testMinus()
{
    CPPUNIT_ASSERT_EQUAL( a2, -a1 );
    CPPUNIT_ASSERT_EQUAL( a1, -a2 );
}

void RealAlgebraicNumberIRTest::testSubtraction()
{
    CPPUNIT_ASSERT_EQUAL( a0, a2 - a4 );
    CPPUNIT_ASSERT_EQUAL( a0, a1 - (a2 + (a3 + a3)) );
    CPPUNIT_ASSERT_EQUAL( a0, a1 - a3 );
    CPPUNIT_ASSERT_EQUAL( a0, a6 - (a4 - a1) );
    CPPUNIT_ASSERT_EQUAL( a6, a4 - a1 );

    CPPUNIT_ASSERT_EQUAL( a0, a4 - 1 );
    CPPUNIT_ASSERT_EQUAL( a0, a6 - 2 );
}

void RealAlgebraicNumberIRTest::testMultiplication()
{
    CPPUNIT_ASSERT_EQUAL( a6, a5 * (a5 * a2) );
    CPPUNIT_ASSERT_EQUAL( a6, a5 * a5 );
    CPPUNIT_ASSERT_EQUAL( -a6, a5 * (a5 * a1) );

    CPPUNIT_ASSERT_EQUAL( a2, a7 * 2 );
    CPPUNIT_ASSERT_EQUAL( a1 * a5 * a5, a6 * (-1) );
}

void RealAlgebraicNumberIRTest::testDivision()
{
    CPPUNIT_ASSERT_EQUAL( a7, a4 / a6 );
    CPPUNIT_ASSERT_EQUAL( a5, a5 / a2 );
    CPPUNIT_ASSERT_EQUAL( a7, a4 / (a5 * a5) );

    CPPUNIT_ASSERT_EQUAL( a7, a4 / 2 );
}

void RealAlgebraicNumberIRTest::testPower()
{
    CPPUNIT_ASSERT_EQUAL( a1, a1 ^ 1 );
    CPPUNIT_ASSERT_EQUAL( a2, a1 ^ 2 );
    CPPUNIT_ASSERT_EQUAL( a2, a1 ^ 2 );
    CPPUNIT_ASSERT_EQUAL( a6, a5 ^ 2 );
}

void RealAlgebraicNumberIRTest::testEqual()
{
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << "RealAlgebraicNumberIRTest::testEqual" << endl;
    cout << a1 << " == " << a3 << endl;
#endif
    CPPUNIT_ASSERT( a1 == a3 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a2 << " == " << a4 << endl;
#endif
    CPPUNIT_ASSERT( a2 == a4 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a2 << " != " << a1 << endl;
#endif
    CPPUNIT_ASSERT( a2 != a1 );
}

void RealAlgebraicNumberIRTest::testLess()
{
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << "RealAlgebraicNumberIRTest::testLess" << endl;
    cout << a1 << " < " << a2 << endl;
#endif
    CPPUNIT_ASSERT( a1 < a2 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a3 << " < " << a4 << endl;
#endif
    CPPUNIT_ASSERT( a3 < a4 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a5 << " < " << a6 << endl;
#endif
    CPPUNIT_ASSERT( a5 < a6 );
}

void RealAlgebraicNumberIRTest::testGreater()
{
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << "RealAlgebraicNumberIRTest::testGreater" << endl;
    cout << a2 << " > " << a1 << endl;
#endif
    CPPUNIT_ASSERT( a2 > a1 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a4 << " > " << a3 << endl;
#endif
    CPPUNIT_ASSERT( a4 > a3 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a6 << " > " << a5 << endl;
#endif
    CPPUNIT_ASSERT( a6 > a5 );
}

void RealAlgebraicNumberIRTest::testLessEqual()
{
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << "RealAlgebraicNumberIRTest::testLessEqual" << endl;
    cout << a1 << " <= " << a2 << endl;
#endif
    CPPUNIT_ASSERT( a1 <= a2 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a3 << " <= " << a4 << endl;
#endif
    CPPUNIT_ASSERT( a3 <= a4 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a5 << " <= " << a6 << endl;
#endif
    CPPUNIT_ASSERT( a5 <= a6 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a1 << " <= " << a3 << endl;
#endif
    CPPUNIT_ASSERT( a1 <= a3 );
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << a2 << " <= " << a4 << endl;
#endif
    CPPUNIT_ASSERT( a2 <= a4 );
}

void RealAlgebraicNumberIRTest::testGreaterEqual()
{
#ifdef GINACRA_INTERVALREPRESENTATIONTEST_DEBUG
    cout << "RealAlgebraicNumberIRTest::testGreaterEqual" << endl;
#endif
    CPPUNIT_ASSERT( a2 >= a1 );
    CPPUNIT_ASSERT( a4 >= a3 );
    CPPUNIT_ASSERT( a6 >= a5 );
    CPPUNIT_ASSERT( a1 >= a3 );
    CPPUNIT_ASSERT( a2 >= a4 );
}

void RealAlgebraicNumberIRTest::testRefine()
{
    const OpenInterval i = a6.interval();
    CPPUNIT_ASSERT( i.contains( a6.interval() ));
    numeric l = a6.interval().left();
    numeric r = a6.interval().right();
    a6.refine();
    CPPUNIT_ASSERT( i.contains( a6.interval() ) && (l < a6.interval().left() || r > a6.interval().right()));
}

void RealAlgebraicNumberIRTest::testRefineEps()
{
    a6.refine( .001 );
    CPPUNIT_ASSERT( a6.interval().right() - a6.interval().left() <= .001 );
}

void RealAlgebraicNumberIRTest::testMemory()
{
    //     // this should run nearly without memory consumption
    //     cout << endl << "RealAlgebraicNumberIRTest::testMemory: Memory usage by this process shall now remain constant." << endl;
    //     const symbol x("X");
    //     const RationalUnivariatePolynomial p(pow(x, 3) - pow(x, 2) + 2, x);
    //     const OpenInterval i(-2, 0);
    //     unsigned n = 0;
    //     while(n < 10000000)
    //     {
    // //         RealAlgebraicNumberIR* a = new RealAlgebraicNumberIR(p, i);
    // //         delete a;
    //         RealAlgebraicNumberIR a(p, i);
    //         ++n;
    //     }
}

void RealAlgebraicNumberIRTest::testEvalf()
{
    // the numbers might differ in some cases, but the message is clear: numeric evaluation of expressions works with RealAlgebraicNumberIRs
    CPPUNIT_ASSERT_EQUAL( ex( numeric( -17, 16 )), ex( a3 ).evalf());
    CPPUNIT_ASSERT_EQUAL( ex( numeric( 17, 16 )), ex( a4 ).evalf());
}

void RealAlgebraicNumberIRTest::testSgn()
{
    CPPUNIT_ASSERT_EQUAL( GiNaC::ZERO_SIGN, a0.sgn() );
    CPPUNIT_ASSERT_EQUAL( GiNaC::NEGATIVE_SIGN, a1.sgn() );
    CPPUNIT_ASSERT_EQUAL( GiNaC::POSITIVE_SIGN, a2.sgn() );
    CPPUNIT_ASSERT_EQUAL( GiNaC::NEGATIVE_SIGN, a3.sgn() );
    CPPUNIT_ASSERT_EQUAL( GiNaC::POSITIVE_SIGN, a4.sgn() );
    CPPUNIT_ASSERT_EQUAL( GiNaC::NEGATIVE_SIGN, a5.sgn() );
    CPPUNIT_ASSERT_EQUAL( GiNaC::POSITIVE_SIGN, a6.sgn() );
    CPPUNIT_ASSERT_EQUAL( GiNaC::POSITIVE_SIGN, a7.sgn() );
}
