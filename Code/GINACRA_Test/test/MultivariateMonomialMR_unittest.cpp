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


// #define GINACRA_MULTIVARIATEMONOMIALTEST_DEBUG

/**
 * Unit test class for the class MultivariateMonomialMR.
 *
 * @author Sebastian Junges
 * @since 2010-11-27
 * @version 2011-11-27
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

#include "MultivariateMonomialMR_unittest.h"

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( MultivariateMonomialMRTest );

void MultivariateMonomialMRTest::setUp()
{
    std::vector<pui> p1;
    p1.push_back( pui( 1, 2 ));
    p1.push_back( pui( 2, 2 ));
    std::vector<pui> p2;
    p2.push_back( pui( 1, 4 ));
    p2.push_back( pui( 2, 4 ));
    std::vector<pui> p5;
    p5.push_back( pui( 1, 4 ));
    p5.push_back( pui( 2, 2 ));
    std::vector<pui> p6;
    p6.push_back( pui( 3, 4 ));
    p6.push_back( pui( 4, 2 ));
    std::vector<pui> p7;
    p7.push_back( pui( 1, 4 ));
    p7.push_back( pui( 2, 2 ));
    p7.push_back( pui( 3, 4 ));
    p7.push_back( pui( 4, 2 ));

    //x2y2
    m1 = MultivariateMonomialMR( p1.begin(), p1.end() );
    //x4y4
    m2 = MultivariateMonomialMR( p2.begin(), p2.end() );
    //x2
    m3 = MultivariateMonomialMR( 1, 2 );
    //x4
    m4 = MultivariateMonomialMR( 1, 4 );
    //x4y2
    m5 = MultivariateMonomialMR( p5.begin(), p5.end() );
    //z4u2
    m6 = MultivariateMonomialMR( p6.begin(), p6.end() );
    //x4y2z4u2
    m7 = MultivariateMonomialMR( p7.begin(), p7.end() );
    //y2
    m8 = MultivariateMonomialMR( 2, 2 );
}

void MultivariateMonomialMRTest::tearDown(){}

void MultivariateMonomialMRTest::testConstructor(){}

void MultivariateMonomialMRTest::testMultiplication()
{
    CPPUNIT_ASSERT_EQUAL( m1 * m1, m2 );
    CPPUNIT_ASSERT_EQUAL( m3 * m3, m4 );
    CPPUNIT_ASSERT_EQUAL( m1 * m3, m5 );
    CPPUNIT_ASSERT_EQUAL( m5 * m6, m7 );
    CPPUNIT_ASSERT_EQUAL( m3 * m8, m1 );
}

void MultivariateMonomialMRTest::testdeg()
{
    CPPUNIT_ASSERT_EQUAL( m3.tdeg(), (unsigned)2 );
    CPPUNIT_ASSERT_EQUAL( m8.tdeg(), (unsigned)2 );
}

void MultivariateMonomialMRTest::testLCM()
{
    CPPUNIT_ASSERT_EQUAL( MultivariateMonomialMR::lcm( m1, m1 ), m1 );
    CPPUNIT_ASSERT_EQUAL( MultivariateMonomialMR::lcm( m1, m2 ), m2 );
    CPPUNIT_ASSERT_EQUAL( MultivariateMonomialMR::lcm( m4, m5 ), m5 );
    CPPUNIT_ASSERT_EQUAL( MultivariateMonomialMR::lcm( m3, m5 ), m5 );
    CPPUNIT_ASSERT_EQUAL( MultivariateMonomialMR::lcm( m7, m8 ), m7 );
}

void MultivariateMonomialMRTest::testlexorder()
{
    //std::cout << "testlexorder" << std::endl;
    CPPUNIT_ASSERT( MultivariateMonomialMR::LexCompare( m8, m3 ));
    CPPUNIT_ASSERT( MultivariateMonomialMR::LexCompare( m6, m5 ));
    CPPUNIT_ASSERT( !MultivariateMonomialMR::LexCompare( m4, MultivariateMonomialMR() ));
    CPPUNIT_ASSERT( !MultivariateMonomialMR::LexCompare( m4, m4 ));

}

void MultivariateMonomialMRTest::testgrevorder()
{
    //std::cout << "testgrevorder" << std::endl;
    CPPUNIT_ASSERT( MultivariateMonomialMR::GrRevLexCompare( m3, m8 ));

}

void MultivariateMonomialMRTest::testexpr()
{
    //std::cout << "testexpr" << std::endl;
    m1.toEx();
    //std::cout << m1.toEx() << std::endl;
    //std::cout << m2.toEx() << std::endl;
    //std::cout << m3.toEx() << std::endl;
    //std::cout << m4.toEx() << std::endl;

}
