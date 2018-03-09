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


//#include "MultivariatePolynomialMR_unittest.h"
//#include "MultivariateTermMR_unittest.h"
//#include "MultivariateMonomialMR_unittest.h"
//#include "VariableListPool.h"

CPPUNIT_TEST_SUITE_REGISTRATION( MultivariatePolynomialMR_unittest );

using namespace :: GiNaCRA;

void MultivariatePolynomialMR_unittest::setUp()
{
    /** std::vector<pui> p1;
    p1.push_back(pui(1,2));
    p1.push_back(pui(2,2));
    std::vector<pui> p2;
    p2.push_back(pui(1,4));
    p2.push_back(pui(2,4));
    std::vector<pui> p5;
    p5.push_back(pui(1, 4));
    p5.push_back(pui(2, 2));
    std::vector<pui> p6;
    p6.push_back(pui(3, 4));
    p6.push_back(pui(4, 2));
    std::vector<pui> p7;
    p7.push_back(pui(1, 4));
    p7.push_back(pui(2, 2));
    p7.push_back(pui(3, 4));
    p7.push_back(pui(4, 2));

    MultivariateMonomialMR m1,m2,m3,m4,m5,m6,m7,m8;
    //x2y2
    m1 = MultivariateMonomialMR(p1.begin(), p1.end());
    //x4y4
    m2 = MultivariateMonomialMR(p2.begin(), p2.end());
    //x2
    m3 = MultivariateMonomialMR(1, 2);
    //x4
    m4 = MultivariateMonomialMR(1, 4);
    //x4y2
    m5 = MultivariateMonomialMR(p5.begin(), p5.end());
    //z4u2
    m6 = MultivariateMonomialMR(p6.begin(), p6.end());
    //x4y2z4u2
    m7 = MultivariateMonomialMR(p7.begin(), p7.end());
    //y2
    m8 = MultivariateMonomialMR(2, 2);
    */
    std::vector<pui> q1;
    q1.push_back( pui( 1, 1 ));
    q1.push_back( pui( 2, 1 ));

    std::vector<pui> q3;
    q3.push_back( pui( 1, 1 ));
    q3.push_back( pui( 2, 2 ));
    std::vector<pui> q2;
    q2.push_back( pui( 1, 2 ));
    q2.push_back( pui( 2, 1 ));
    MultivariateMonomialMR a1, xy, a3, a4, x, x2, y, xy2;
    a1  = MultivariateMonomialMR( 1, 3 );
    xy  = MultivariateMonomialMR( q1.begin(), q1.end() );
    a3  = MultivariateMonomialMR( q2.begin(), q2.end() );
    a4  = MultivariateMonomialMR( 2, 2 );
    x   = MultivariateMonomialMR( 1, 1 );
    x2  = MultivariateMonomialMR( 1, 2 );
    y   = MultivariateMonomialMR( 2, 1 );
    xy2 = MultivariateMonomialMR( q3.begin(), q3.end() );

    u1  = MultivariateTermMR( a1 );
    u2  = MultivariateTermMR( xy, -2 );
    u3  = MultivariateTermMR( a3 );
    u4  = MultivariateTermMR( a4, -2 );
    u5  = MultivariateTermMR( x );
    u6  = MultivariateTermMR( x2, -1 );
    u7  = MultivariateTermMR( xy2, -2 );
    std::set<MultivariateTermMR, MonomMRCompare> fs1 = std::set<MultivariateTermMR, MonomMRCompare>( MonomMRCompare() );
    fs1.insert( u1 );
    fs1.insert( u2 );
    f1 = MultivariatePolynomialMR( fs1.begin(), fs1.end(), MonomMRCompare() );

    std::set<MultivariateTermMR, MonomMRCompare> fs2 = std::set<MultivariateTermMR, MonomMRCompare>( MonomMRCompare() );
    fs2.insert( u3 );
    fs2.insert( u4 );
    fs2.insert( u5 );
    f2 = MultivariatePolynomialMR( fs2.begin(), fs2.end(), MonomMRCompare() );
    std::set<MultivariateTermMR, MonomMRCompare> fs3 = std::set<MultivariateTermMR, MonomMRCompare>( MonomMRCompare() );
    fs3.insert( u6 );
    f3 = MultivariatePolynomialMR( fs3.begin(), fs3.end(), MonomMRCompare() );
    std::set<MultivariateTermMR, MonomMRCompare> fs4 = std::set<MultivariateTermMR, MonomMRCompare>( MonomMRCompare() );
    fs4.insert( u2 );
    f4 = MultivariatePolynomialMR( fs4.begin(), fs4.end(), MonomMRCompare() );
    std::set<MultivariateTermMR, MonomMRCompare> fs5 = std::set<MultivariateTermMR, MonomMRCompare>( MonomMRCompare() );
    fs5.insert( u7 );
    f5 = MultivariatePolynomialMR( fs5.begin(), fs5.end(), MonomMRCompare() );

    //t1 = MultivariateTermMR(m1,2);
    //t12 = MultivariateTermMR(m1);
    //t2 = MultivariateTermMR(m2,2);
    //t4 = MultivariateTermMR(m4);
    //t5 = MultivariateTermMR(m5);
    //t8 = MultivariateTermMR(m8);

}

void MultivariatePolynomialMR_unittest::tearDown(){}

void MultivariatePolynomialMR_unittest::testEmpty()
{
    CPPUNIT_ASSERT( !f3.isZero() );
    CPPUNIT_ASSERT( f3.truncLT().isZero() );
}

void MultivariatePolynomialMR_unittest::testTruncLT()
{
    CPPUNIT_ASSERT_EQUAL( f4, f1.truncLT() );
}

void MultivariatePolynomialMR_unittest::testSubstract()
{
    CPPUNIT_ASSERT_EQUAL( f4, f1 - MultivariatePolynomialMR( u1, MonomMRCompare() ));
}

void MultivariatePolynomialMR_unittest::testSpol()
{
    CPPUNIT_ASSERT_EQUAL( f4, MultivariatePolynomialMR::SPol( f1, f3 ));
    CPPUNIT_ASSERT_EQUAL( f3, MultivariatePolynomialMR::SPol( f1, f2 ));
    CPPUNIT_ASSERT_EQUAL( f5, MultivariatePolynomialMR::SPol( f1, f4 ));

}

void MultivariatePolynomialMR_unittest::testRem()
{
    std::list<MultivariatePolynomialMR> l1;
    l1.push_back( f1 );
    l1.push_back( f2 );
    CPPUNIT_ASSERT_EQUAL( f3, f3.CalculateRemainder( l1.begin(), l1.end() ));
    l1.push_back( f3 );
    CPPUNIT_ASSERT( f3.CalculateRemainder( l1.begin(), l1.end() ).isZero() );
    l1.push_back( f4 );
    CPPUNIT_ASSERT( f5.CalculateRemainder( l1.begin(), l1.end() ).isZero() );
    //CPPUNIT_ASSERT();
}

void MultivariatePolynomialMR_unittest::testExpr()
{
    f1.toEx();
    //std::cout << f2.toEx() << std::endl;
    GiNaC::symbol x = VariableListPool::getVariableSymbol( 3 );
    GiNaC::symbol y = VariableListPool::getVariableSymbol( 4 );
    //std::cout << MultivariatePolynomialMR(GiNaC::ex(x*y+2*x*x)) << std::endl;
    //std::cout << f1.toEx() << std::endl;
    //std::cout << f2.toEx() << std::endl;
}

void MultivariatePolynomialMR_unittest::testMul(){}
