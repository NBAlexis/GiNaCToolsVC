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


#ifndef MULTIVARIATEPOLYNOMIALMR_UNITTEST_H
#define MULTIVARIATEPOLYNOMIALMR_UNITTEST_H

////#include <cppunit/extensions/HelperMacros.h>
//#include "MultivariatePolynomialMR.h"

using namespace GiNaCRA;

class MultivariatePolynomialMR_unittest:
    public CPPUNIT_NS:: TestFixture
{
    CPPUNIT_TEST_SUITE( MultivariatePolynomialMR_unittest );
    CPPUNIT_TEST( testEmpty );
    CPPUNIT_TEST( testTruncLT );
    CPPUNIT_TEST( testSubstract );
    CPPUNIT_TEST( testSpol );
    CPPUNIT_TEST( testRem );
    CPPUNIT_TEST( testExpr );
    CPPUNIT_TEST( testMul );

 CPPUNIT_TEST_SUITE_END()

 ;

 public:
     void setUp();
     void tearDown();

 private:
     MultivariateTermMR       t1, t2, t3, t4, t5, t6;
     MultivariateTermMR       u1, u2, u3, u4, u5, u6, u7;
     MultivariatePolynomialMR f1, f2, f3, f4, f5, f6;

     void testEmpty();
     void testTruncLT();
     void testSubstract();
     void testSpol();
     void testRem();
     void testExpr();
     void testMul();

};

#endif   /** MULTIVARIATEPOLYNOMIALMR_UNITTEST_H */
