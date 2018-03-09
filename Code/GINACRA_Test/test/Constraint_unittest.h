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


#ifndef GINACRA_COEFFICIENT_TEST_H
#define GINACRA_COEFFICIENT_TEST_H

/**
 * Unit test class for the class Constraint.
 *
 * @author Ulrich Loup
 * @since 2011-12-08
 * @version 2012-01-03
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

////#include <cppunit/extensions/HelperMacros.h>

//#include "Constraint.h"
//#include "operators.h"

using std::vector;
using GiNaC::symbol;
using GiNaCRA::Constraint;

class ConstraintTest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( ConstraintTest );
    // declare each test case
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testSatisfiedBy );

 CPPUNIT_TEST_SUITE_END()

 ;

 private:

     symbol         x, y, z, w;
     vector<symbol> v1, v2, v3;
     Constraint     c1, c2, c3, c4, c5, c6;

 public:

     void setUp();
     void tearDown();

     void testConstructor();
     void testSatisfiedBy();
};
#endif // GINACRA_COEFFICIENT_TEST_H
