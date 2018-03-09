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


#ifndef GINACRA_UNIVARIATEPOLYNOMIAL_TEST_H
#define GINACRA_UNIVARIATEPOLYNOMIAL_TEST_H

/**
 * Unit test class for the class UnivariatePolynomial.
 *
 * @author Ulrich Loup
 * @since 2010-09-06
 * @version 2012-05-15
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

////#include <cppunit/extensions/HelperMacros.h>

//#include "UnivariatePolynomial.h"

using GiNaCRA::UnivariatePolynomial;

class UnivariatePolynomialTest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( UnivariatePolynomialTest );
    // declare each test case
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testEquality );
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST( testMinus );
    CPPUNIT_TEST( testSubtraction );
    CPPUNIT_TEST( testMultiplication );
    CPPUNIT_TEST( testDivision );
    CPPUNIT_TEST( testRemainder );
    CPPUNIT_TEST( testEvaluation );
    CPPUNIT_TEST( testCoeff );
    CPPUNIT_TEST( testLcoeff );
    CPPUNIT_TEST( testTcoeff );
    CPPUNIT_TEST( testDiff );
    CPPUNIT_TEST( testSepapart );
    CPPUNIT_TEST( testNonzeropart );
    CPPUNIT_TEST( testIsConstant );
    CPPUNIT_TEST( testSturmSequence );
    CPPUNIT_TEST( testSquare );
    CPPUNIT_TEST( testMemory );
    CPPUNIT_TEST( testSubresultants );

 CPPUNIT_TEST_SUITE_END()

 ;

 private:

     symbol               x, y;
     ex                   polynomial;
     UnivariatePolynomial p0, p1, p2, p3, p4, p5, p6, p7;

 public:

     void setUp();
     void tearDown();

     void testConstructor();
     void testEquality();
     void testAddition();
     void testMinus();
     void testSubtraction();
     void testMultiplication();
     void testDivision();
     void testRemainder();
     void testEvaluation();
     void testTwoNormSquare();
     void testCoeff();
     void testLcoeff();
     void testTcoeff();
     void testDiff();
     void testSepapart();
     void testNonzeropart();
     void testIsConstant();
     void testSturmSequence();
     void testSquare();
     void testMemory();
     void testSubresultants();
};
#endif // GINACRA_UNIVARIATEPOLYNOMIAL_TEST_H
