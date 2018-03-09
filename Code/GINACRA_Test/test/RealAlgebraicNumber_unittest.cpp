#include "ginacra_test.h"
//Hide because GINACRA_INTERVALREPRESENTATION_TEST_H
#if 0
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


/**
 * Unit tests for the class RealAlgebraicNumber.
 *
 * @author Ulrich Loup
 * @since 2011-10-30
 * @version 2011-10-30
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

//#include "RealAlgebraicNumber_unittest.h"

using GiNaCRA::RealAlgebraicNumber;
using GiNaC::symbol;
using GiNaC::pow;

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( RealAlgebraicNumberTest );

void RealAlgebraicNumberTest::setUp()
{
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

void RealAlgebraicNumberTest::tearDown(){}

void RealAlgebraicNumberTest::testConstructor()
{
    const symbol                       s( "s" );
    const RationalUnivariatePolynomial polynomial( (s - 1) * (s + 1), s );
    const RealAlgebraicNumber          r1 = RealAlgebraicNumberIR( polynomial, OpenInterval( -2, 0 ));
    const RealAlgebraicNumber          r2 = RealAlgebraicNumberIR( polynomial, OpenInterval( 0, 2 ));
    //     CPPUNIT_ASSERT_EQUAL( r2, r1 );
}

void RealAlgebraicNumberTest::testAddition(){}

void RealAlgebraicNumberTest::testMinus()
{
    //     CPPUNIT_ASSERT_EQUAL( a2, -a1 );
    //     CPPUNIT_ASSERT_EQUAL( a1, -a2 );
}

void RealAlgebraicNumberTest::testSubtraction(){}

void RealAlgebraicNumberTest::testMultiplication(){}

void RealAlgebraicNumberTest::testDivision(){}

void RealAlgebraicNumberTest::testEqual(){}

void RealAlgebraicNumberTest::testLess(){}

void RealAlgebraicNumberTest::testSgn(){}

#endif