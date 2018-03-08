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


// #define GINACRA_OPENINTERVALTEST_DEBUG

/**
 * Unit tests for the class OpenInterval.
 *
 * @author Ulrich Loup
 * @since 2010-09-02
 * @version 2012-05-13
 */

#include "OpenInterval_unittest.h"
#include "operators.h"

using GiNaC::numeric;

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( OpenIntervalTest );

void OpenIntervalTest::setUp()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::setUp()" << endl;
#endif
    i0 = OpenInterval();
    i1 = OpenInterval( numeric( -1, 2 ), 2 );
    i2 = OpenInterval( -2, 1 );
    i3 = OpenInterval( -4, 2 );
    i4 = OpenInterval( -5, 4 );
    i5 = OpenInterval( -2, 4 );
}

void OpenIntervalTest::tearDown()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::tearDown()" << endl;
#endif
}

void OpenIntervalTest::testConstructor()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testConstructor()" << endl;
#endif
    numeric zero        = numeric( 0 );
    numeric l           = numeric( -2 );
    numeric r           = numeric( 1002 );
    OpenInterval i      = OpenInterval( l, r );
    OpenInterval i_zero = OpenInterval();
    CPPUNIT_ASSERT_EQUAL( l, i.left() );
    CPPUNIT_ASSERT_EQUAL( r, i.right() );
    CPPUNIT_ASSERT_EQUAL( zero, i_zero.left() );
    CPPUNIT_ASSERT_EQUAL( zero, i_zero.right() );
}

void OpenIntervalTest::testEquality()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testEquality()" << endl;
#endif
    CPPUNIT_ASSERT( !(i0 == i1) );
    CPPUNIT_ASSERT( !(i1 == i2) );
    CPPUNIT_ASSERT( !(i2 == i3) );
    CPPUNIT_ASSERT( !(i3 == i0) );
}

void OpenIntervalTest::testAddition()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testAddition()" << endl;
#endif
    CPPUNIT_ASSERT_EQUAL( i3, i2 + i2 );
    CPPUNIT_ASSERT_EQUAL( i3 + i3, i2 + i3 + i2 );
    CPPUNIT_ASSERT_EQUAL( i3 + i3, i2 + i2 + i2 + i2 );

    CPPUNIT_ASSERT_EQUAL( 1 + i2, i2 + 1 );
    CPPUNIT_ASSERT_EQUAL( OpenInterval( 0, 3 ), i2 + 2 );
}

void OpenIntervalTest::testMinus()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testMinus()" << endl;
#endif
    CPPUNIT_ASSERT_EQUAL( i5, -i3 );
}

void OpenIntervalTest::testSubtraction()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testSubtraction()" << endl;
#endif
    CPPUNIT_ASSERT_EQUAL( i4, i3 - i2 );
    CPPUNIT_ASSERT_EQUAL( i3, i3 - (i0 - i0) );
}

void OpenIntervalTest::testMultiplication()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testMultiplication()" << endl;
#endif
    CPPUNIT_ASSERT_EQUAL( i3, i1 * i2 );
}

void OpenIntervalTest::testPower()
{
    CPPUNIT_ASSERT_EQUAL( i1, i1.pow( 1 ));
    CPPUNIT_ASSERT_EQUAL( i2, i2.pow( 1 ));
    CPPUNIT_ASSERT( (i1 * i1).contains( i1.pow( 2 )));
    CPPUNIT_ASSERT_EQUAL( OpenInterval( 0, 4 ), i1.pow( 2 ));
    CPPUNIT_ASSERT_EQUAL( OpenInterval( -numeric( 1, 8 ), 8 ), i1.pow( 3 ));
}

void OpenIntervalTest::testEvaluate()
{
    GiNaC::symbol x( "x" ), y( "y" );
    GiNaC::ex     p = 2 * GiNaC::pow( x, 2 ) + x * y - 1;
    OpenInterval result = 2 * i1 * i1 + i1 * i2 - 1;
    GiNaCRA::evalintervalmap m = GiNaCRA::evalintervalmap();
    m[x] = i1;
    m[y] = i2;
    CPPUNIT_ASSERT_EQUAL( result, OpenInterval::evaluate( p, m ));
    CPPUNIT_ASSERT_EQUAL( i1 + i2, OpenInterval::evaluate( x + y, m ));
    CPPUNIT_ASSERT_EQUAL( 5 * i1, OpenInterval::evaluate( 5 * x, m ));
    CPPUNIT_ASSERT_EQUAL( i2, OpenInterval::evaluate( y, m ));
    CPPUNIT_ASSERT_EQUAL( i1 - 1, OpenInterval::evaluate( x - 1, m ));
}

void OpenIntervalTest::testLess()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testLess()" << endl;
#endif
    CPPUNIT_ASSERT( i1 <= i0 );
    CPPUNIT_ASSERT( i2 <= i1 );
    CPPUNIT_ASSERT( i3 <= i2 );
    CPPUNIT_ASSERT( i3 <= i0 );
}

void OpenIntervalTest::testGreater()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testGreater()" << endl;
#endif
    CPPUNIT_ASSERT( i1 >= i0 );
    CPPUNIT_ASSERT( i1 >= i2 );
    CPPUNIT_ASSERT( i3 >= i2 );
    CPPUNIT_ASSERT( i3 >= i0 );
}

void OpenIntervalTest::testIsZero()
{
    CPPUNIT_ASSERT( i0.isZero() );
    CPPUNIT_ASSERT( !(i2 - i2).isZero() );
}

void OpenIntervalTest::testIsNormalized()
{
    CPPUNIT_ASSERT( i0.isNormalized() );
    CPPUNIT_ASSERT( !i3.isNormalized() );
    CPPUNIT_ASSERT( OpenInterval( -3, -0.1 ).isNormalized() );
}

void OpenIntervalTest::testContainsNumeric()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testContains()" << endl;
#endif
    CPPUNIT_ASSERT( i1.contains( 0 ));
    CPPUNIT_ASSERT( i2.contains( numeric( 1, 2 )));
    CPPUNIT_ASSERT( i3.contains( 1 ));
    CPPUNIT_ASSERT( i4.contains( -2 ));
    CPPUNIT_ASSERT( i5.contains( 3 ));
}

void OpenIntervalTest::testContainsInterval()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testContains()" << endl;
#endif
    CPPUNIT_ASSERT( i3.contains( i2 ));
    CPPUNIT_ASSERT( i4.contains( i3 ));
    CPPUNIT_ASSERT( i4.contains( i5 ));
}

void OpenIntervalTest::testIntersection()
{
    CPPUNIT_ASSERT_EQUAL( i2, i2.intersection( i5 ));
}

void OpenIntervalTest::testMidpoint()
{
    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), i0.midpoint() );
    CPPUNIT_ASSERT_EQUAL( numeric( 3, 4 ), i1.midpoint() );
    CPPUNIT_ASSERT_EQUAL( numeric( -1, 2 ), i2.midpoint() );
    CPPUNIT_ASSERT_EQUAL( numeric( -1 ), i3.midpoint() );
    CPPUNIT_ASSERT_EQUAL( numeric( -1, 2 ), i4.midpoint() );
    CPPUNIT_ASSERT_EQUAL( numeric( 1 ), i5.midpoint() );
}

void OpenIntervalTest::testSample()
{
    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), i0.sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), i1.sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), i2.sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), i3.sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), i4.sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), i5.sample() );

    CPPUNIT_ASSERT_EQUAL( numeric( 1 ), OpenInterval( numeric( 1, 3 ), numeric( 3, 2 )).sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( 1 ), OpenInterval( numeric( 1, 3 ), numeric( 5, 4 )).sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( 1, 2 ), OpenInterval( numeric( 1, 3 ), numeric( 3, 4 )).sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( 91, 3 ), OpenInterval( numeric( 30 ), numeric( 61, 2 )).sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( -1 ), OpenInterval( numeric( -123 ), numeric( -1, 2 )).sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( 2, 103 ), OpenInterval( numeric( 1, 52 ), numeric( 1, 51 )).sample() );

    CPPUNIT_ASSERT_EQUAL( numeric( -3, 4 ), OpenInterval( numeric( -25, 32 ), numeric( -23, 32 )).sample() );
    CPPUNIT_ASSERT_EQUAL( numeric( -3, 4 ), OpenInterval( numeric( -25, 32 ), numeric( -23, 32 )).sampleFast() );
}

void OpenIntervalTest::testMemory()
{
#ifdef GINACRA_OPENINTERVALTEST_DEBUG
    cout << "OpenIntervalTest::testMemory()" << endl;
#endif
    // // this should run nearly without memory consumption
    // cout << "OpenIntervalTest::testMemory: Memory usage by this process shall now remain constant." << endl;
    // unsigned n = 0;
    // while(n < 50000000)
    // {
    //     OpenInterval* i = new OpenInterval(-2, 23);
    //     ++n;
    //     delete i;
    // }
}
