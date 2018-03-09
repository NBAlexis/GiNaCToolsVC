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


// #define GINACRA_UNIVARIATEPOLYNOMIALTEST_DEBUG

/**
 * Unit tests for the class UnivariatePolynomial.
 *
 * @author Ulrich Loup
 * @since 2010-09-06
 * @version 2012-04-20
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

//#include "UnivariatePolynomial_unittest.h"
//#include "utilities.h"
//#include "operators.h"

using std::vector;
using std::map;
using std::cout;
using std::endl;

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( UnivariatePolynomialTest );

void UnivariatePolynomialTest::setUp()
{
#ifdef GINACRA_UNIVARIATEPOLYNOMIALTEST_DEBUG
    cout << "UnivariatePolynomialTest::setUp()" << endl;
#endif
    x          = symbol( "x" );
    y          = symbol( "y" );
    p0         = UnivariatePolynomial( 0, x );
    p1         = UnivariatePolynomial( x * x - 1, x );
    p2         = UnivariatePolynomial( -2 * x + 2, x );
    p3         = UnivariatePolynomial( 3 * x * x - 6 * x + 3, x );
    polynomial = ex( pow( x, 17 ) * pow( y, 3 ) - y * pow( x, 2 ) + pow( y, 3 ) * pow( x, 2 ) + 2 );
    p4         = UnivariatePolynomial( polynomial, x );
    p5         = UnivariatePolynomial( polynomial, y );
    p6         = UnivariatePolynomial( x * x - 2 * x + 1, x );
    p7         = UnivariatePolynomial( x - 1, x );
}

void UnivariatePolynomialTest::tearDown(){}

void UnivariatePolynomialTest::testConstructor()
{
    const symbol               s( "s" );
    const symbol               r( "r" );
    const ex                   expression = pow( s, 17 ) * pow( r, 3 ) - r * r * s + 2;
    const UnivariatePolynomial polynomial( expression, s );
    CPPUNIT_ASSERT_EQUAL( s, polynomial.variable() );
    CPPUNIT_ASSERT( expression == polynomial );
}

void UnivariatePolynomialTest::testEquality()
{
    ex p_expanded = polynomial.expand().collect( y );
    CPPUNIT_ASSERT_EQUAL( p_expanded, (ex)p5 );
    CPPUNIT_ASSERT( p_expanded == p5 );
    p_expanded = polynomial.expand().collect( x );
    CPPUNIT_ASSERT_EQUAL( p_expanded, (ex)p4 );
    CPPUNIT_ASSERT( p_expanded == p4 );
    CPPUNIT_ASSERT( p4 != p5 );
}

void UnivariatePolynomialTest::testAddition()
{
    CPPUNIT_ASSERT_EQUAL( p6, p1 + p2 );
    CPPUNIT_ASSERT_EQUAL( p3, p6 + (p6 + p6) );
    //     CPPUNIT_ASSERT_EQUAL( p3, p1 + (p2 + (p1 + (p2 + (p1 + p2)) );
}

void UnivariatePolynomialTest::testMinus()
{
    // tested in testSubtraction
}

void UnivariatePolynomialTest::testSubtraction()
{
    CPPUNIT_ASSERT_EQUAL( -p2, p1 - p6 );
    CPPUNIT_ASSERT_EQUAL( p0, p6 - (p1 + p2) );
}

void UnivariatePolynomialTest::testMultiplication()
{
    CPPUNIT_ASSERT_EQUAL( p6, p7 * p7 );
}

void UnivariatePolynomialTest::testDivision()
{
    CPPUNIT_ASSERT_EQUAL( p7, p6 / p7 );
}

void UnivariatePolynomialTest::testRemainder()
{
    //    CPPUNIT_ASSERT_EQUAL( p0, p6 % p7 );
}

void UnivariatePolynomialTest::testEvaluation()
{
    const ex zero( 0 );
    const ex valx( 2.0 - 9 * y + 129140172.0 * pow( y, 3 ));
    const ex valy( 2 + 39.375 * x * x + 42.875 * pow( x, 17 ));
    CPPUNIT_ASSERT_EQUAL( zero, p6.evaluateAt( 1 ));
    CPPUNIT_ASSERT_EQUAL( valx, p4.evaluateAt( 3 ));
    CPPUNIT_ASSERT_EQUAL( valy, p5.evaluateAt( 3.5 ));
}

void UnivariatePolynomialTest::testCoeff()
{
    CPPUNIT_ASSERT_EQUAL( ex( 0 ), p0.coeff( 1 ));
}

void UnivariatePolynomialTest::testLcoeff()
{
    CPPUNIT_ASSERT_EQUAL( ex( 0 ), p0.lcoeff() );
}

void UnivariatePolynomialTest::testTcoeff()
{
    CPPUNIT_ASSERT_EQUAL( ex( 0 ), p0.tcoeff() );
}

void UnivariatePolynomialTest::testDiff()
{
    const UnivariatePolynomial d_p4( 17 * pow( x, 16 ) * pow( y, 3 ) - 2 * y * x + 2 * pow( y, 3 ) * x, x );
    CPPUNIT_ASSERT_EQUAL( d_p4, p4.diff() );
}

void UnivariatePolynomialTest::testSepapart()
{
    CPPUNIT_ASSERT_EQUAL( p0, p0.sepapart() );
    CPPUNIT_ASSERT_EQUAL( p1, p1.sepapart() );
    CPPUNIT_ASSERT_EQUAL( UnivariatePolynomial( x - 1, x ), p2.sepapart() );
    CPPUNIT_ASSERT_EQUAL( p7, p3.sepapart() );
    CPPUNIT_ASSERT_EQUAL( p4, p4.sepapart() );
    CPPUNIT_ASSERT_EQUAL( p5, p5.sepapart() );
    CPPUNIT_ASSERT_EQUAL( p7, p6.sepapart() );
    CPPUNIT_ASSERT_EQUAL( p7, p7.sepapart() );
}

void UnivariatePolynomialTest::testNonzeropart()
{
    CPPUNIT_ASSERT_EQUAL( p1, p1.nonzeropart() );
    CPPUNIT_ASSERT_EQUAL( p2, p2.nonzeropart() );
    CPPUNIT_ASSERT_EQUAL( p3, p3.nonzeropart() );
    UnivariatePolynomial p( x * x + x, x );
    CPPUNIT_ASSERT_EQUAL( UnivariatePolynomial( x + 1, x ), p.nonzeropart() );
}

void UnivariatePolynomialTest::testIsConstant()
{
    CPPUNIT_ASSERT_EQUAL( true, p0.isConstant() );
}

void UnivariatePolynomialTest::testSturmSequence()
{
    // convention: If both polynomials are zero, the corresponding Sturm sequence is just the element zero.
    list<UnivariatePolynomial> seq = UnivariatePolynomial::standardSturmSequence( p0, p0 );
    CPPUNIT_ASSERT_EQUAL( 1, (int)seq.size() );
    for( list<UnivariatePolynomial>::const_iterator iter = seq.begin(); iter != seq.end(); ++iter )
        CPPUNIT_ASSERT_EQUAL( p0, *iter );
    // convention: If one polynomial is zero, the corresponding Sturm sequence is zero followed by the other polynomial.
    seq = UnivariatePolynomial::standardSturmSequence( p0, p3 );
    list<UnivariatePolynomial>::const_iterator iter = seq.begin();
    CPPUNIT_ASSERT_EQUAL( 2, (int)seq.size() );
    CPPUNIT_ASSERT_EQUAL( p0, *iter );
    ++iter;
    CPPUNIT_ASSERT_EQUAL( p3, *iter );
    // Two identical polynomials cause a sequence of length 2 with just two copies of the input polynomials
    const UnivariatePolynomial c( -234, x );
    seq  = UnivariatePolynomial::standardSturmSequence( c, c );
    iter = seq.begin();
    CPPUNIT_ASSERT_EQUAL( 2, (int)seq.size() );
    CPPUNIT_ASSERT_EQUAL( c, *iter );
    ++iter;
    CPPUNIT_ASSERT_EQUAL( c, *iter );
    seq  = UnivariatePolynomial::standardSturmSequence( p1, p1 );
    iter = seq.begin();
    CPPUNIT_ASSERT_EQUAL( 2, (int)seq.size() );
    CPPUNIT_ASSERT_EQUAL( p1, *iter );
    ++iter;
    CPPUNIT_ASSERT_EQUAL( p1, *iter );
    // Other tests:
    const UnivariatePolynomial p1_1( 1, x );
    seq  = UnivariatePolynomial::standardSturmSequence( p1, p1.diff() );
    iter = seq.begin();
    CPPUNIT_ASSERT_EQUAL( 3, (int)seq.size() );
    CPPUNIT_ASSERT_EQUAL( p1, *iter );
    ++iter;
    CPPUNIT_ASSERT_EQUAL( p1.diff(), *iter );
    ++iter;
    CPPUNIT_ASSERT_EQUAL( p1_1, *iter );
}

void UnivariatePolynomialTest::testSquare()
{
    CPPUNIT_ASSERT_EQUAL( p0.square(), p0.square() );
    UnivariatePolynomial p( x, x );
    CPPUNIT_ASSERT_EQUAL( UnivariatePolynomial( x * x, x ), p.square() );
}

void UnivariatePolynomialTest::testMemory()
{
    //     // this should run nearly without memory consumption
    //     cout << endl << "UnivariatePolynomialTest::testMemory: Memory usage by this process shall now remain constant." << endl;
    //     const symbol z = symbol("z");
    //     unsigned n = 0;
    //     while(n < 1000000)
    //     {
    //         UnivariatePolynomial* p = new UnivariatePolynomial(pow(z, 3) - pow(z, 2) + 2, z);
    //         ++n;
    //         delete p;
    //     }
}

void UnivariatePolynomialTest::testSubresultants()
{
    symbol a( "a" ), b( "b" ), c( "c" );    // lexicographic order
    list<UnivariatePolynomial> subresLst;
    int                        count;
    // non-defective subresultants have the same degree than their index
#define SUBRESTEST_NONDEFECTIVE(polynomial)\
    subresLst = UnivariatePolynomial::subresultants( UnivariatePolynomial( polynomial, x ), UnivariatePolynomial( polynomial.diff(x), x ));\
    CPPUNIT_ASSERT_EQUAL( (int) subresLst.size(), polynomial.degree( x ) + 1 );\
    count = 0;\
    for( list<UnivariatePolynomial>::const_iterator i = subresLst.begin(); i != subresLst.end(); ++i )\
        CPPUNIT_ASSERT_EQUAL( count++, i->degree());
    // defective subresultants have a strictly lower degree than their index
#define SUBRESTEST_PARTLYDEFECTIVE(polynomial)\
    subresLst = UnivariatePolynomial::subresultants( UnivariatePolynomial( polynomial, x ), UnivariatePolynomial( polynomial.diff(x), x ));\
    CPPUNIT_ASSERT_EQUAL( (int) subresLst.size(), polynomial.degree( x ) + 1 );\
    count = 0;\
    for( list<UnivariatePolynomial>::const_iterator i = subresLst.begin(); i != subresLst.end(); ++i )\
        CPPUNIT_ASSERT( count++ >= i->degree());
    ex p( pow( x, 4 ) + a * pow( x, 2 ) + b * x + c );
    SUBRESTEST_NONDEFECTIVE( p );
    p = a * pow( x, 5 ) + b * pow( x, 4 ) + c;
    SUBRESTEST_PARTLYDEFECTIVE( p );
}
