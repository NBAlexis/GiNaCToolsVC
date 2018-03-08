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


#ifndef MULTIVARIATETERMMR_UNITTEST_H
#define MULTIVARIATETERMMR_UNITTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "MultivariateTermMR.h"

using namespace GiNaCRA;

class MultivariateTermMR_unittest:
    public CPPUNIT_NS:: TestFixture
{
    CPPUNIT_TEST_SUITE( MultivariateTermMR_unittest );
    CPPUNIT_TEST( testdivby );
    CPPUNIT_TEST( testlcmdivt );

 CPPUNIT_TEST_SUITE_END()

 ;

 public:
     void setUp();
     void tearDown();

 private:
     MultivariateTermMR t1, t2, t3, t4, t5, t6, t7, t8;
     MultivariateTermMR t12;

     void testdivby();
     void testlcmdivt();
};

#endif   /** MULTIVARIATETERMMR_UNITTEST_H */
