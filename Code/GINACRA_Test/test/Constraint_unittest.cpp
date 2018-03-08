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
 * Unit test class for the class Constraint.
 *
 * @author Ulrich Loup
 * @version 2011-12-08
 * @version 2012-01-03
 */

#include "Constraint_unittest.h"
#include "constants.h"

using GiNaC::ZERO_SIGN;
using GiNaC::POSITIVE_SIGN;
using GiNaC::NEGATIVE_SIGN;
using GiNaC::numeric;
using GiNaCRA::OpenInterval;
using GiNaCRA::Polynomial;
using GiNaCRA::RationalUnivariatePolynomial;
using GiNaCRA::RealAlgebraicPoint;
using GiNaCRA::RealAlgebraicNumberPtr;
using GiNaCRA::RealAlgebraicNumberNR;
using GiNaCRA::RealAlgebraicNumberIR;
using GiNaCRA::Constraint;

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( ConstraintTest );

void ConstraintTest::setUp()
{
    x  = symbol( "x" );
    y  = symbol( "y" );
    z  = symbol( "z" );
    w  = symbol( "w" );
    v1 = vector<symbol>();
    v1.push_back( x );
    v1.push_back( y );
    v2 = vector<symbol>();
    v2.push_back( x );
    v2.push_back( y );
    v2.push_back( z );
    v3 = vector<symbol>();
    v3.push_back( x );
    v3.push_back( y );
    v3.push_back( z );
    v3.push_back( w );

    c1 = Constraint( Polynomial( pow( y, 2 ) + pow( x, 2 ) - 1 ), ZERO_SIGN, v1 );
    c2 = Constraint( Polynomial( pow( x, 2 ) + pow( y, 2 ) + pow( z, 2 ) - 1 ), NEGATIVE_SIGN, v2 );
    c3 = Constraint( Polynomial( pow( x, 4 ) + pow( y, 4 ) + pow( z, 4 ) + pow( w, 4 ) - 1 ), NEGATIVE_SIGN, v3 );
    c4 = Constraint( Polynomial( pow( x, 4 ) + pow( y, 4 ) + pow( z, 4 ) + pow( w, 4 ) - 1 ), NEGATIVE_SIGN, v3, true );    // >= 0
    c5 = Constraint( Polynomial( pow( x, 4 ) + pow( y, 4 ) + pow( z, 4 ) + pow( w, 4 ) - 1 ), ZERO_SIGN, v3, true );    // != 0
    c6 = Constraint( Polynomial( pow( x, 4 ) + pow( y, 4 ) + pow( z, 4 ) + pow( w, 4 ) - 1 ), POSITIVE_SIGN, v3 );
}

void ConstraintTest::tearDown(){}

void ConstraintTest::testConstructor()
{
    CPPUNIT_ASSERT_EQUAL( c1, Constraint( Polynomial( pow( y, 2 ) + pow( x, 2 ) - 1 ), ZERO_SIGN, v1 ));
    CPPUNIT_ASSERT_THROW( Constraint( Polynomial( pow( pow( symbol( "z" ), 2 ), 2 ) + pow( x, 2 ) - 1 ), ZERO_SIGN, v1 ), invalid_argument );
}

void ConstraintTest::testSatisfiedBy()
{
    vector<RealAlgebraicNumberPtr> numbers1 = vector<RealAlgebraicNumberPtr>();
    numbers1.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( 0 )));
    numbers1.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( 1 )));
    CPPUNIT_ASSERT_EQUAL( true, c1.satisfiedBy( RealAlgebraicPoint( numbers1 )));
    vector<RealAlgebraicNumberPtr> numbers2 = vector<RealAlgebraicNumberPtr>();
    numbers2.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( 0 )));
    numbers2.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( y * y - 2, y ), OpenInterval( -2, -1 ))));
    CPPUNIT_ASSERT_EQUAL( false, c1.satisfiedBy( RealAlgebraicPoint( numbers2 )));
    vector<RealAlgebraicNumberPtr> numbers3 = vector<RealAlgebraicNumberPtr>();
    numbers3.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( x * x - 1, x ), OpenInterval( .5, 2 ))));
    numbers3.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( y * y - 1, y ), OpenInterval( -2, -.5 ))));
    CPPUNIT_ASSERT_EQUAL( false, c1.satisfiedBy( RealAlgebraicPoint( numbers3 )));
    vector<RealAlgebraicNumberPtr> numbers4 = vector<RealAlgebraicNumberPtr>();
    numbers4.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( x * x - numeric( 9, 10 ), x ),
                                                                           OpenInterval( .5, 2 ))));
    numbers4.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( y * y - numeric( 9, 10 ), y ),
                                                                           OpenInterval( .5, 1 ))));
    numbers4.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( z * z - numeric( 9, 10 ), z ),
                                                                           OpenInterval( .5, 1 ))));
    //    CPPUNIT_ASSERT_EQUAL( false, c2.satisfiedBy( RealAlgebraicPoint( numbers4 ) ) );
    //    vector<RealAlgebraicNumberPtr> numbers5 = vector<RealAlgebraicNumberPtr > ( );
    //    numbers5.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( x * x - numeric( 9, 10 ), x ), OpenInterval( .5, 2 ) ) ) );
    //    numbers5.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( y * y - numeric( 9, 10 ), y ), OpenInterval( .5, 1 ) ) ) );
    //    numbers5.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( z * z - numeric( 9, 10 ), z ), OpenInterval( .5, 1 ) ) ) );
    //    numbers5.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( w * w - numeric( 9, 10 ), w ), OpenInterval( .5, 1 ) ) ) );
    //    CPPUNIT_ASSERT_EQUAL( false, c3.satisfiedBy( RealAlgebraicPoint( numbers5 ) ) );
    //    CPPUNIT_ASSERT_EQUAL( true, c4.satisfiedBy( RealAlgebraicPoint( numbers5 ) ) );
    //    CPPUNIT_ASSERT_EQUAL( true, c5.satisfiedBy( RealAlgebraicPoint( numbers5 ) ) );
    //    CPPUNIT_ASSERT_EQUAL( true, c6.satisfiedBy( RealAlgebraicPoint( numbers5 ) ) );
}
