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


/**
 * Unit tests for the class RealAlgebraicNumberIR.
 *
 * @author Ulrich Loup
 * @since 2010-09-08
 * @version 2011-05-05
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

//#include "UnivariatePolynomialSet_unittest.h"
//#include "UnivariatePolynomialFactory.h"

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( UnivariatePolynomialSetTest );

void UnivariatePolynomialSetTest::setUp()
{
    x      = symbol( "x" );
    y      = symbol( "y" );
    z      = symbol( "z" );
    thrown = false;
}

void UnivariatePolynomialSetTest::tearDown(){}

void UnivariatePolynomialSetTest::testInsert()
{
    UnivariatePolynomialSet A;

    UnivariatePolynomial P( x * x + y * y, x );
    UnivariatePolynomial Q( x * x + y * y, y );
    A.insert( P );

    try
    {
        A.insert( Q );
    }

    catch( invalid_argument exp )
    {
        thrown = true;
    }

    CPPUNIT_ASSERT( thrown );
}

void UnivariatePolynomialSetTest::testRemoveConstants()
{
    UnivariatePolynomialSet A;
    A.insert( UnivariatePolynomial( 3, x ));
    A.insert( UnivariatePolynomial( 0, x ));
    A.insert( UnivariatePolynomial( y * y, x ));
    CPPUNIT_ASSERT( !A.empty() );
    A.removeNumbers();//.removeConstants();
    CPPUNIT_ASSERT( A.empty() );
}

void UnivariatePolynomialSetTest::testTruncation()
{
#ifdef GINACRA_MULTIVARIATEMONOMIALTEST_DEBUG
    cout << "UnivariatePolynomialFactoryTest::testTruncation()" << endl;
#endif

    //What is UnivariatePolynomialFactory??
    /*
    symbol x( "x" ), y( "y" );
    UnivariatePolynomial P( y * x * x + y * y * x + 3 + y, x );
    UnivariatePolynomialSet M( UnivariatePolynomialFactory::truncation( P ));
    CPPUNIT_ASSERT( !M.empty() );
    UniSetIter it = M.find( UnivariatePolynomial( y * y * x + 3 + y, x ));
    CPPUNIT_ASSERT( it != M.end() );
    it = M.find( UnivariatePolynomial( 3 + y, x ));
    CPPUNIT_ASSERT( it != M.end() );
    it = M.find( UnivariatePolynomial( 0, x ));
    CPPUNIT_ASSERT( it == M.end() );
    it = M.find( UnivariatePolynomial( y * x * x + y * y * x + 3 + y, x ));
    CPPUNIT_ASSERT( it != M.end() );
    */
}
