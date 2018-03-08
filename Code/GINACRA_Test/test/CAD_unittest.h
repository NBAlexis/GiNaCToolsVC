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


#ifndef GINACRA_CAD_TEST_H
#define GINACRA_CAD_TEST_H

/**
 * Unit test class for the class CAD.
 *
 * @author Ulrich Loup
 * @since 2011-12-06
 * @version 2012-01-20
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

#include <cppunit/extensions/HelperMacros.h>

#include "CAD.h"

using GiNaCRA::CAD;
using GiNaCRA::UnivariatePolynomial;

class CAD_unittest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( CAD_unittest );
    CPPUNIT_TEST( testCheck );
    CPPUNIT_TEST( testComplete );
    CPPUNIT_TEST( testSampleList );
    CPPUNIT_TEST( testSamplesStatic );
    CPPUNIT_TEST( testSamples );
    CPPUNIT_TEST( testElimination );
    CPPUNIT_TEST( testAddPolynomials );

 // declare each test case
 CPPUNIT_TEST_SUITE_END()

 ;

 private:

     symbol               x, y;
     UnivariatePolynomial p1, p2;
     CAD                  cad;

 public:

     void setUp();
     void tearDown();

     void testCheck();
     void testComplete();
     void testSampleList();
     void testSamplesStatic();
     void testSamples();
     void testElimination();
     void testAddPolynomials();

};
#endif // GINACRA_CAD_TEST_H
