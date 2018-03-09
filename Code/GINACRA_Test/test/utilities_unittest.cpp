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


// #define GINACRA_UTILITIESTEST_DEBUG

/**
 * Unit test class for the collection of utilities.
 *
 * @author Ulrich Loup
 * @since 2010-12-15
 * @version 2012-03-20
 */

////#include <cln/cln.h>

//#include "utilities_unittest.h"

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( utilitiesTest );

void utilitiesTest::setUp()
{
#ifdef GINACRA_UTILITIESTEST_DEBUG
    cout << "utilitiesTest::setUp()" << endl;
#endif
    x = symbol( "x" );
    y = symbol( "y" );
    z = symbol( "z" );
    l = vector<symbol>();
    l.push_back( x );
    l.push_back( y );
    c1 = 2 * z;
    m1 = pow( x, 2 ) * pow( y, 3 );
    p1 = c1 * m1;
}

void utilitiesTest::tearDown(){}

void utilitiesTest::testLcm()
{
#ifdef GINACRA_UTILITIESTEST_DEBUG
    cout << "utilitiesTest::testLcm()" << endl;
#endif
    ex a( 40 );
    ex b( 10 );
    ex c( 8 );
    lst l = lst( a, b, c );
    CPPUNIT_ASSERT_EQUAL( a, lcm( l ));
    CPPUNIT_ASSERT_EQUAL( b, lcm( lst( b )));
}

void utilitiesTest::testGcd()
{
    for( unsigned i = 100; i != 120; ++i )
        CPPUNIT_ASSERT_EQUAL( GiNaC::gcd( numeric( i ), numeric( i + 1 )), numeric( GiNaC::gcd( i, i + 1 )));
}

void utilitiesTest::testNumerator()
{
    for( unsigned i = 100; i != 120; ++i )
        for( unsigned j = 100; j != 120; ++j )
            CPPUNIT_ASSERT_EQUAL( cln::numerator( cln::cl_I( i ) / cln::cl_I( j )), cln::cl_I( GiNaC::numerator( i, j )));
}

void utilitiesTest::testDenominator()
{
    for( unsigned i = 100; i != 120; ++i )
        for( unsigned j = 100; j != 120; ++j )
            CPPUNIT_ASSERT_EQUAL( cln::denominator( cln::cl_I( i ) / cln::cl_I( j )), cln::cl_I( GiNaC::denominator( i, j )));
}

void utilitiesTest::testCoeffpart()
{
#ifdef GINACRA_UTILITIESTEST_DEBUG
    cout << "utilitiesTest::testCoeffpart()" << endl;
#endif
    CPPUNIT_ASSERT_EQUAL( c1, coeffpart( p1, l ));
}

void utilitiesTest::testMonpart()
{
#ifdef GINACRA_UTILITIESTEST_DEBUG
    cout << "utilitiesTest::testMonpart()" << endl;
#endif
    CPPUNIT_ASSERT_EQUAL( m1, monpart( p1, l ));
}

void utilitiesTest::testIsolateByVariables()
{
#ifdef GINACRA_UTILITIESTEST_DEBUG
    cout << "utilitiesTest::testIsolateByVariables()" << endl;
#endif
    ex c( 1 ), m( 1 );
    isolateByVariables( p1, l, c, m );
    CPPUNIT_ASSERT_EQUAL( c * m, p1 );
}

void utilitiesTest::testSortVariables()
{
#ifdef GINACRA_UTILITIESTEST_DEBUG
    cout << "utilitiesTest::testSortVariables()" << endl;
#endif
}

void utilitiesTest::testSubresultants()
{
    symbol z( "z" ), a( "a" ), b( "b" ), c( "c" );    // lexicographic order

    ex P( a * pow( z, 5 ) + b * pow( z, 4 ) + c );
    ex PP = P.diff( z );
    map<int, ex> subres = signedSubresultants( P, PP, z );
    CPPUNIT_ASSERT_EQUAL( resultant( P, PP, z ), resultant( P, PP, z ));
    vector<ex> v = signedSubresultantsCoefficients( P, PP, z );

    CPPUNIT_ASSERT_EQUAL( v[2], ex( 0 ));
    CPPUNIT_ASSERT_EQUAL( v[1], ex( -100 * pow( a, 3 ) * pow( b, 2 ) * pow( c, 2 )));
    CPPUNIT_ASSERT_EQUAL( v[0], ex( 256 * a * pow( b, 5 ) * pow( c, 3 ) + 3125 * pow( a, 5 ) * pow( c, 4 )));
}
