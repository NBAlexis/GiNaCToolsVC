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


#ifndef GINACRA_INTERVALREPRESENTATION_TEST_H
#define GINACRA_INTERVALREPRESENTATION_TEST_H

/**
 * Unit test class for the class RealAlgebraicNumberIR.
 *
 * @author Ulrich Loup
 * @since 2010-09-08
 * @version 2012-05-07
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

#include <cppunit/extensions/HelperMacros.h>

#include "RealAlgebraicNumberIR.h"

using GiNaCRA::RationalUnivariatePolynomial;
using GiNaCRA::OpenInterval;
using GiNaCRA::RealAlgebraicNumberIR;

class RealAlgebraicNumberIRTest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( RealAlgebraicNumberIRTest );
    // declare each test case
    CPPUNIT_TEST( testNormalizePolynomial );
    CPPUNIT_TEST( testNormalizeInterval );
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST( testMinus );
    CPPUNIT_TEST( testSubtraction );
    CPPUNIT_TEST( testEqual );
    CPPUNIT_TEST( testLess );
    CPPUNIT_TEST( testGreater );
    CPPUNIT_TEST( testLessEqual );
    CPPUNIT_TEST( testGreaterEqual );
    CPPUNIT_TEST( testMultiplication );
    CPPUNIT_TEST( testDivision );
    CPPUNIT_TEST( testPower );
    CPPUNIT_TEST( testRefine );
    CPPUNIT_TEST( testRefineEps );
    CPPUNIT_TEST( testMemory );
    CPPUNIT_TEST( testEvalf );
    CPPUNIT_TEST( testSgn );

 CPPUNIT_TEST_SUITE_END()

 ;

 private:

     RationalUnivariatePolynomial p0, p1;
     OpenInterval                 i0, i1;
     RealAlgebraicNumberIR        a0, a1, a2, a3, a4, a5, a6, a7;

 public:

     void setUp();
     void tearDown();

     void testNormalizePolynomial();
     void testNormalizeInterval();
     void testConstructor();
     void testAddition();
     void testMinus();
     void testSubtraction();
     void testEqual();
     void testLess();
     void testGreater();
     void testLessEqual();
     void testGreaterEqual();
     void testMultiplication();
     void testDivision();
     void testPower();
     void testRefine();
     void testRefineEps();
     void testMemory();
     void testEvalf();
     void testSgn();
};
#endif // GINACRA_INTERVALREPRESENTATION_TEST_H
