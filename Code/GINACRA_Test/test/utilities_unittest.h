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


#ifndef GINACRA_UTILITIES_TEST_H
#define GINACRA_UTILITIES_TEST_H

/**
 * Unit test class for the collection of utilities.
 *
 * @author Ulrich Loup
 * @since 2010-11-14
 * @version 2012-03-20
 */

#include <cppunit/extensions/HelperMacros.h>

#include "utilities.h"

using namespace GiNaC;

class utilitiesTest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( utilitiesTest );
    // declare each test case
    CPPUNIT_TEST( testLcm );
    CPPUNIT_TEST( testGcd );
    CPPUNIT_TEST( testNumerator );
    CPPUNIT_TEST( testDenominator );
    CPPUNIT_TEST( testCoeffpart );
    CPPUNIT_TEST( testMonpart );
    CPPUNIT_TEST( testIsolateByVariables );
    CPPUNIT_TEST( testSortVariables );
    CPPUNIT_TEST( testSubresultants );

 CPPUNIT_TEST_SUITE_END()

 ;

 private:

     symbol         x, y, z;
     vector<symbol> l;
     ex             c1, m1, p1;

 public:

     void setUp();
     void tearDown();

     void testLcm();
     void testGcd();
     void testNumerator();
     void testDenominator();
     void testCoeffpart();
     void testMonpart();
     void testIsolateByVariables();
     void testSortVariables();
     void testSubresultants();
};
#endif // GINACRA_UTILITIES_TEST_H
