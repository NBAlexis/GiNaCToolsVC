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


#ifndef GINACRA_UNIVARIATEPOLYNOMIALSET_TEST_H
#define GINACRA_UNIVARIATEPOLYNOMIALSET_TEST_H

/**
 * Unit test class for the class RealAlgebraicNumberIR.
 *
 * @author Joachim
 * @since 2011-10-03
 * @version 2011-10-03
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

////#include <cppunit/extensions/HelperMacros.h>

//#include "UnivariatePolynomialSet.h"
//#include "settings.h"

using namespace GiNaC;

class UnivariatePolynomialSetTest:
    public CppUnit:: TestFixture
{
    // declare test suite
    CPPUNIT_TEST_SUITE( UnivariatePolynomialSetTest );
    // declare each test case
    CPPUNIT_TEST( testInsert );
    CPPUNIT_TEST( testRemoveConstants );
    CPPUNIT_TEST( testTruncation );

 CPPUNIT_TEST_SUITE_END()

 ;

 private:

     symbol x, y, z;
     bool   thrown;

 public:

     void setUp();
     void tearDown();

     void testInsert();
     void testRemoveConstants();
     void testTruncation();
};
#endif // GINACRA_INTERVALREPRESENTATION_TEST_H
