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


//#include "MultivariateTermMR_unittest.h"
//#include "MultivariateTermMR.h"

CPPUNIT_TEST_SUITE_REGISTRATION( MultivariateTermMR_unittest );

void MultivariateTermMR_unittest::setUp()
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

    MultivariateMonomialMR m1, m2, m3, m4, m5, m6, m7, m8;
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

    //std::cout << "constructor" << std::endl;
    t1  = MultivariateTermMR( m1, 2 );
    t12 = MultivariateTermMR( m1 );
    t2  = MultivariateTermMR( m2, 2 );
    t4  = MultivariateTermMR( m4 );
    t5  = MultivariateTermMR( m5 );
    t8  = MultivariateTermMR( m8 );

}

void MultivariateTermMR_unittest::tearDown(){}

void MultivariateTermMR_unittest::testdivby()
{
    //std::cout << "testdivby" << std::endl;

    CPPUNIT_ASSERT_EQUAL( t1, t2.divby( t12 ).first );
    CPPUNIT_ASSERT_EQUAL( t8, t5.divby( t4 ).first );
    CPPUNIT_ASSERT( !t1.divby( t2 ).second );
    CPPUNIT_ASSERT( !t8.divby( t5 ).second );
    CPPUNIT_ASSERT( t1.divby( t12 ).second );
}

void MultivariateTermMR_unittest::testlcmdivt()
{
    CPPUNIT_ASSERT_EQUAL( t8, t4.lcmdivt( t5 ));
}
