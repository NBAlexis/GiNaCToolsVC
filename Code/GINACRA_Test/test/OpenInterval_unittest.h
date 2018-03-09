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


#ifndef GINACRA_OPENINTERVAL_TEST_H
#define GINACRA_OPENINTERVAL_TEST_H

////#include <cppunit/extensions/HelperMacros.h>

//#include "OpenInterval.h"

using GiNaCRA::OpenInterval;

/**
 * Unit test class for the class OpenInterval.
 *
 * @author Ulrich Loup
 * @since 2010-09-02
 * @version 2012-01-08
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */
class OpenIntervalTest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( OpenIntervalTest );
    // declare each test case
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testEquality );
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST( testMinus );
    CPPUNIT_TEST( testSubtraction );
    CPPUNIT_TEST( testMultiplication );
    CPPUNIT_TEST( testPower );
    CPPUNIT_TEST( testEvaluate );
    CPPUNIT_TEST( testLess );
    CPPUNIT_TEST( testGreater );
    CPPUNIT_TEST( testIsZero );
    CPPUNIT_TEST( testIsNormalized );
    CPPUNIT_TEST( testContainsNumeric );
    CPPUNIT_TEST( testContainsInterval );
    CPPUNIT_TEST( testIntersection );
    CPPUNIT_TEST( testMidpoint );
    CPPUNIT_TEST( testSample );
    CPPUNIT_TEST( testMemory );

 CPPUNIT_TEST_SUITE_END()

 ;

 private:

     OpenInterval i0, i1, i2, i3, i4, i5;

 public:

     void setUp();
     void tearDown();

     void testConstructor();
     void testEquality();
     void testAddition();
     void testMinus();
     void testSubtraction();
     void testMultiplication();
     void testPower();
     void testEvaluate();
     void testLess();
     void testGreater();
     void testIsZero();
     void testIsNormalized();
     void testContainsNumeric();
     void testContainsInterval();
     void testIntersection();
     void testMidpoint();
     void testSample();
     void testMemory();
};
#endif // GINACRA_OPENINTERVAL_TEST_H
