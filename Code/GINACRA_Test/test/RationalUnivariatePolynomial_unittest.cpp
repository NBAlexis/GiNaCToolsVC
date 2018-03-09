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


// #define GINACRA_RATIONALUNIVARIATEPOLYNOMIALTEST_DEBUG

/**
 * Unit tests for the class RationalUnivariatePolynomial.
 *
 * @author Ulrich Loup
 * @since 2010-09-08
 * @version 2012-03-15
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

//#include "RationalUnivariatePolynomial_unittest.h"

using GiNaC::symbol;
using GiNaC::pow;
using GiNaC::numeric;
using GiNaCRA::RationalUnivariatePolynomial;

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( RationalUnivariatePolynomialTest );

void RationalUnivariatePolynomialTest::setUp()
{
#ifdef GINACRA_RATIONALUNIVARIATEPOLYNOMIALTEST_DEBUG
    cout << "RationalUnivariatePolynomialTest::setUp()" << endl;
#endif
    x  = symbol( "x" );
    p0 = RationalUnivariatePolynomial( 0, x );
    p1 = RationalUnivariatePolynomial( pow( x, 3 ) - pow( x, 2 ) + 2, x );
    p2 = RationalUnivariatePolynomial( numeric( 2, 9 ) * x - 2, x );
    p3 = RationalUnivariatePolynomial( numeric( -225 ), x );
    p4 = RationalUnivariatePolynomial( pow( (x - 3), 2 ) * (x - 1) * (x + 3), x );
    p5 = RationalUnivariatePolynomial( (x - 5) * (x - 4) * (x - 2) * (x + 1) * (x + 2) * (x + 4), x );
    p6 = RationalUnivariatePolynomial( pow( x, 4 ) - 5 * pow( x, 2 ) + 4, x );
    //p7 = RationalUnivariatePolynomial(pow(x,2)-2,x);
    p7  = RationalUnivariatePolynomial( (pow( x, 3 ) - 1) * (pow( x, 2 ) - 9), x );
    p8  = RationalUnivariatePolynomial( x - 2, x );
    p9  = RationalUnivariatePolynomial( x + 1, x );
    p10 = RationalUnivariatePolynomial( x, x );
}

void RationalUnivariatePolynomialTest::tearDown(){}

void RationalUnivariatePolynomialTest::testConstructor()
{
    const symbol                       s( "s" );
    const ex                           expression = pow( s, 17 ) * 3 - pow( s, 3 ) + 2;
    const RationalUnivariatePolynomial polynomial( expression, s );
    CPPUNIT_ASSERT_EQUAL( s, polynomial.variable() );
    CPPUNIT_ASSERT( expression == polynomial );
    CPPUNIT_ASSERT_THROW( RationalUnivariatePolynomial( expression * x, s ), invalid_argument );
}

void RationalUnivariatePolynomialTest::testSgn()
{
    CPPUNIT_ASSERT_EQUAL( POSITIVE_SIGN, p1.sgn( 0 ));
    CPPUNIT_ASSERT_EQUAL( ZERO_SIGN, p1.sgn( -1 ));
    CPPUNIT_ASSERT_EQUAL( NEGATIVE_SIGN, p1.sgn( -2 ));

    CPPUNIT_ASSERT_EQUAL( ZERO_SIGN, static_cast<RationalUnivariatePolynomial>(p1.diff()).sgn( 0 ));
    CPPUNIT_ASSERT_EQUAL( NEGATIVE_SIGN, p2.sgn( 0 ));
    CPPUNIT_ASSERT_EQUAL( NEGATIVE_SIGN, p3.sgn( 0 ));
}

void RationalUnivariatePolynomialTest::testHasZeroRoot()
{
    CPPUNIT_ASSERT( !p0.hasZeroRoot() );
    CPPUNIT_ASSERT( !p1.hasZeroRoot() );
    CPPUNIT_ASSERT( !p2.hasZeroRoot() );
    CPPUNIT_ASSERT( !p3.hasZeroRoot() );
    CPPUNIT_ASSERT( RationalUnivariatePolynomial( x, x ).hasZeroRoot() );
}

void RationalUnivariatePolynomialTest::testEvaluateAt()
{
    CPPUNIT_ASSERT_EQUAL( numeric( 2 ), p1.evaluateAt( 0 ));
    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), p1.evaluateAt( -1 ));
    CPPUNIT_ASSERT_EQUAL( numeric( -10 ), p1.evaluateAt( -2 ));

    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), static_cast<RationalUnivariatePolynomial>(p1.diff()).evaluateAt( 0 ));
    CPPUNIT_ASSERT_EQUAL( numeric( -2 ), p2.evaluateAt( 0 ));
    CPPUNIT_ASSERT_EQUAL( numeric( -225 ), p3.evaluateAt( 0 ));
}

void RationalUnivariatePolynomialTest::testMaximumNorm()
{
    CPPUNIT_ASSERT_EQUAL( numeric( 2 ), p1.maximumNorm() );
}

void RationalUnivariatePolynomialTest::testCauchyBound()
{
    CPPUNIT_ASSERT_EQUAL( numeric( 0 ), p0.cauchyBound() );
    CPPUNIT_ASSERT_EQUAL( numeric( 4 ), p1.cauchyBound() );
}

void RationalUnivariatePolynomialTest::testSturmSequence()
{
    list<RationalUnivariatePolynomial>                 seq  = RationalUnivariatePolynomial::standardSturmSequence( p1, p1.diff() );
    list<RationalUnivariatePolynomial>::const_iterator iter = seq.begin();
    CPPUNIT_ASSERT_EQUAL( 4, (int)seq.size() );
    CPPUNIT_ASSERT_EQUAL( p1, static_cast<RationalUnivariatePolynomial>(*iter) );
    ++iter;
    CPPUNIT_ASSERT_EQUAL( static_cast<RationalUnivariatePolynomial>(p1.diff()), static_cast<RationalUnivariatePolynomial>(*iter) );
    ++iter;
    CPPUNIT_ASSERT_EQUAL( p2, static_cast<RationalUnivariatePolynomial>(*iter) );
    ++iter;
    CPPUNIT_ASSERT_EQUAL( p3, static_cast<RationalUnivariatePolynomial>(*iter) );
}

void RationalUnivariatePolynomialTest::testSignVariations()
{
    list<RationalUnivariatePolynomial> seq = RationalUnivariatePolynomial::standardSturmSequence( p1, p1.diff() );
    CPPUNIT_ASSERT_EQUAL( (unsigned)1, RationalUnivariatePolynomial::signVariations( seq, 0 ));
    seq = RationalUnivariatePolynomial::standardSturmSequence( p6, p6.diff() );
    CPPUNIT_ASSERT_EQUAL( (unsigned)0, RationalUnivariatePolynomial::signVariations( seq, 10 ));
    CPPUNIT_ASSERT_EQUAL( (unsigned)4, RationalUnivariatePolynomial::signVariations( seq, -3 ));
}

void RationalUnivariatePolynomialTest::testSturmCauchyIndex()
{
    //See ISBN-13: 978-3642069642 Example 2.54
    CPPUNIT_ASSERT_EQUAL( 0, RationalUnivariatePolynomial::calculateSturmCauchyIndex( p4, p5 ));
    //See ISBN-13: 978-3642069642 Example 2.52
    CPPUNIT_ASSERT_EQUAL( 4, RationalUnivariatePolynomial::calculateSturmCauchyIndex( p6, p6.diff() ));
}

void RationalUnivariatePolynomialTest::testRemainderTarskiQuery()
{
    RationalUnivariatePolynomial pol1 = RationalUnivariatePolynomial( 1, x );
    CPPUNIT_ASSERT_EQUAL( 4, RationalUnivariatePolynomial::calculateRemainderTarskiQuery( p6, pol1 ));
    CPPUNIT_ASSERT_EQUAL( 1, RationalUnivariatePolynomial::calculateRemainderTarskiQuery( p7, p10 ));
    CPPUNIT_ASSERT_EQUAL( 1, RationalUnivariatePolynomial::calculateRemainderTarskiQuery( p7, p9 ));
    CPPUNIT_ASSERT_EQUAL( -1, RationalUnivariatePolynomial::calculateRemainderTarskiQuery( p7, p8 ));
}

void RationalUnivariatePolynomialTest::testMemory()
{
    //     // this should run nearly without memory consumption
    //     cout << endl << "RationalUnivariatePolynomialTest::testMemory: Memory usage by this process shall now remain constant." << endl;
    //     const symbol* y = new symbol("y");
    //     unsigned n = 0;
    //     while(n < 1000000)
    //     {
    //         RationalUnivariatePolynomial* p = new RationalUnivariatePolynomial(pow(*y, 3) - pow(*y, 2) + 2, y);
    //         ++n;
    //         delete p;
    //     }
    //     delete y;
}
