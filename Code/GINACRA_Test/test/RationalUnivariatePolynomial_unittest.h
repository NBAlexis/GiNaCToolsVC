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


#ifndef GINACRA_RATIONALUNIVARIATEPOLYNOMIAL_TEST_H
#define GINACRA_RATIONALUNIVARIATEPOLYNOMIAL_TEST_H

/**
 * Unit test class for the class RationalUnivariatePolynomial.
 *
 * @author Ulrich Loup
 * @since 2010-09-08
 * @version 2012-01-11
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

////#include <cppunit/extensions/HelperMacros.h>

//#include "RationalUnivariatePolynomial.h"

using GiNaCRA::RationalUnivariatePolynomial;

using namespace GiNaC;

class RationalUnivariatePolynomialTest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( RationalUnivariatePolynomialTest );
    // declare each test case
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testSgn );
    CPPUNIT_TEST( testHasZeroRoot );
    CPPUNIT_TEST( testEvaluateAt );
    CPPUNIT_TEST( testMaximumNorm );
    CPPUNIT_TEST( testCauchyBound );
    CPPUNIT_TEST( testSturmSequence );
    CPPUNIT_TEST( testSignVariations );
    CPPUNIT_TEST( testSturmCauchyIndex );
    CPPUNIT_TEST( testRemainderTarskiQuery );
    CPPUNIT_TEST( testMemory );

 CPPUNIT_TEST_SUITE_END()

 ;

 private:

     symbol                       x;
     RationalUnivariatePolynomial p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;

 public:

     void setUp();
     void tearDown();

     void testConstructor();
     void testSgn();
     void testHasZeroRoot();
     void testEvaluateAt();
     void testMaximumNorm();
     void testCauchyBound();
     void testSturmSequence();
     void testSignVariations();
     void testSturmCauchyIndex();
     void testRemainderTarskiQuery();
     void testSquare();
     void testMemory();
};
#endif // GINACRA_RATIONALUNIVARIATEPOLYNOMIAL_TEST_H
