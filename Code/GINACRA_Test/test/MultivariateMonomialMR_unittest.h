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


#ifndef GINACRA_MULTIVARIATEMONOMIALMR_TEST_H
#define GINACRA_MULTIVARIATEMONOMIALMR_TEST_H

/**
 * Unit test class for the class MultivariateMonomialMR.
 *
 * @author Sebastian Junges
 * @since 2010-11-27
 * @version 2011-05-27
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

#include <cppunit/extensions/HelperMacros.h>

#include "MultivariateMonomialMR.h"
#include "operators.h" // need operators on top because of correct operator<< for tests.

using namespace GiNaCRA;

class MultivariateMonomialMRTest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( MultivariateMonomialMRTest );
    // declare each test case
    //CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testMultiplication );
    CPPUNIT_TEST( testLCM );
    CPPUNIT_TEST( testdeg );
    CPPUNIT_TEST( testlexorder );
    CPPUNIT_TEST( testgrevorder );
    CPPUNIT_TEST( testexpr );

 CPPUNIT_TEST_SUITE_END()

 ;

 private:
     MultivariateMonomialMR m1, m2, m3, m4, m5, m6, m7, m8;
     //symbol x, y;

 public:
     void setUp();
     void tearDown();

     void testConstructor();
     void testMultiplication();
     void testLCM();
     void testdeg();
     void testlexorder();
     void testgrevorder();
     void testexpr();

};
#endif // GINACRA_MULTIVARIATEMONOMIAL_TEST_H
