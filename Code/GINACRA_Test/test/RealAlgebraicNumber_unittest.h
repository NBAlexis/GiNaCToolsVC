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


#ifndef GINACRA_INTERVALREPRESENTATION_TEST_H
#define GINACRA_INTERVALREPRESENTATION_TEST_H

/**
 * Unit test class for the class RealAlgebraicNumber together with its representations.
 *
 * @author Ulrich Loup
 * @since 2011-10-30
 * @version 2011-11-26
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

////#include <cppunit/extensions/HelperMacros.h>

//#include "RealAlgebraicNumber.h"
//#include "RealAlgebraicNumberIR.h"
//#include "RealAlgebraicNumberNR.h"

using GiNaCRA::RationalUnivariatePolynomial;
using GiNaCRA::OpenInterval;
using GiNaCRA::RealAlgebraicNumberIR;

using namespace GiNaC;

class RealAlgebraicNumberTest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( RealAlgebraicNumberTest );
    // declare each test case
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST( testMinus );
    CPPUNIT_TEST( testSubtraction );
    CPPUNIT_TEST( testEqual );
    CPPUNIT_TEST( testLess );
    CPPUNIT_TEST( testMultiplication );
    CPPUNIT_TEST( testDivision );
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

     void testConstructor();
     void testAddition();
     void testMinus();
     void testSubtraction();
     void testEqual();
     void testLess();
     void testMultiplication();
     void testDivision();
     void testSgn();
};
#endif // GINACRA_INTERVALREPRESENTATION_TEST_H
