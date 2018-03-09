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
 * @file CAD_unittest.cpp
 *
 * Unit tests for the class CAD.
 *
 * @author Ulrich Loup
 * @since 2011-12-06
 * @version 2012-03-21
 */

//#include "CAD_unittest.h"
//#include "RealAlgebraicPoint.h"
//#include "RealAlgebraicNumberFactory.h"
//#include "operators.h"

using GiNaC::symbol;
using GiNaC::pow;
using GiNaC::ZERO_SIGN;
using GiNaC::POSITIVE_SIGN;
using GiNaC::NEGATIVE_SIGN;
using GiNaCRA::UnivariatePolynomial;
using GiNaCRA::RationalUnivariatePolynomial;
using GiNaCRA::UnivariatePolynomialSet;
using GiNaCRA::RealAlgebraicPoint;
using GiNaCRA::RealAlgebraicNumberPtr;
using GiNaCRA::RealAlgebraicNumberNR;
using GiNaCRA::RealAlgebraicNumberIR;
using GiNaCRA::RealAlgebraicNumberNRPtr;
using GiNaCRA::RealAlgebraicNumberIRPtr;
using GiNaCRA::SampleList;
using GiNaCRA::Polynomial;
using GiNaCRA::Constraint;
using GiNaCRA::RealAlgebraicNumberFactory;
using GiNaCRA::CAD;

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( CAD_unittest );

void CAD_unittest::setUp()
{
    x = symbol( "x" );
    y = symbol( "y" );
    vector<symbol> v = vector<symbol>();
    v.push_back( x );
    v.push_back( y );

    p1 = UnivariatePolynomial( pow( y, 2 ) + pow( x, 2 ) - 1, x );
    //    p2 = UnivariatePolynomial( x + y - 1, x );
    //        p1 = UnivariatePolynomial( 144 * pow( y, 2 ) + 96 * pow( x, 2 ) * y + 9 * pow( x, 4 ) + 105 * pow( x, 2 ) + 70 * x - 98, x );
    //        p2 = UnivariatePolynomial( x * pow( y, 2 ) + 6 * x * y + pow( x, 3 ) + 9 * x, x );
    p2 = UnivariatePolynomial( x - y, x );

    UnivariatePolynomialSet s;

    s.insert( p1 );
    s.insert( p2 );
    cad = CAD( s, v );
    //    cad.complete( );
}

void CAD_unittest::tearDown(){}

void CAD_unittest::testCheck()
{
    RealAlgebraicPoint r = RealAlgebraicPoint();
    vector<Constraint> constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, ZERO_SIGN, cad.variables() ));
    constraints.push_back( Constraint( p2, ZERO_SIGN, cad.variables() ));
    CPPUNIT_ASSERT( cad.check( constraints, r ));
    CPPUNIT_ASSERT( cad.check( constraints, r ));    // to test the proper functioning of sample tree traversal
    //        cout << "**** Sample: " << r << endl;
    //        cout << "Complete: " << cad.isComplete() << endl;
    //    cad.printSampleTree( cout );
    //
    constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, POSITIVE_SIGN, cad.variables() ));
    constraints.push_back( Constraint( p2, NEGATIVE_SIGN, cad.variables() ));
    CPPUNIT_ASSERT( cad.check( constraints, r ));
    //        cout << "**** Sample: " << r << endl;
    //        cout << "Complete: " << cad.isComplete() << endl;
    //    cad.printSampleTree( cout );
    //
    constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, NEGATIVE_SIGN, cad.variables() ));
    constraints.push_back( Constraint( p2, POSITIVE_SIGN, cad.variables() ));
    CPPUNIT_ASSERT( cad.check( constraints, r ));
    //        cout << "**** Sample: " << r << endl;
    //        cout << "Complete: " << cad.isComplete() << endl;
    //    cad.printSampleTree( cout );
    //
    constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, ZERO_SIGN, cad.variables() ));
    constraints.push_back( Constraint( p2, POSITIVE_SIGN, cad.variables() ));
    CPPUNIT_ASSERT( cad.check( constraints, r ));
    //        cout << "**** Sample: " << r << endl;
    //        cout << "Complete: " << cad.isComplete() << endl;
    //    cad.printSampleTree( cout );
}

void CAD_unittest::testComplete(){}

void CAD_unittest::testSampleList()
{
    // 1st test: sorting
    SampleList l = SampleList();
    l.insert( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( -3 + 4 * x * x, x ),
                                                                 GiNaCRA::OpenInterval( 0, numeric( 3, 2 )))));
    l.insert( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( 2 * x - 1, x ),
                                                                 GiNaCRA::OpenInterval( 0, numeric( 3, 2 )))));
    RationalUnivariatePolynomial p( x * x - 2, x );
    // 2nd test: replacing between different representations
    l = SampleList();
    l.insert( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( p, GiNaCRA::OpenInterval( 0, 3 ))));
    l.insert( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( p, GiNaCRA::OpenInterval( -3, 0 ))));
    l.insert( RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( RationalUnivariatePolynomial( 2 * x - 1, x ), GiNaCRA::OpenInterval( 0, 1 ))));
    l.insert( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( -1 ))));
    SampleList::const_iterator i = l.begin();
    CPPUNIT_ASSERT( RealAlgebraicNumberFactory::isRealAlgebraicNumberIR( *i++ ));
    CPPUNIT_ASSERT( RealAlgebraicNumberFactory::isRealAlgebraicNumberNR( *i++ ));
    CPPUNIT_ASSERT( RealAlgebraicNumberFactory::isRealAlgebraicNumberIR( *i++ ));
    CPPUNIT_ASSERT( RealAlgebraicNumberFactory::isRealAlgebraicNumberIR( *i ));
}

void CAD_unittest::testSamplesStatic()
{
    list<RealAlgebraicNumberPtr> v = list<RealAlgebraicNumberPtr>();
    v.push_back( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( numeric( 1, 2 ))));
    const list<symbol> variables( 1, x );

    SampleList sampleList  = SampleList();
    SampleList sampleList1 = CAD::samples( UnivariatePolynomial( pow( y, 2 ) + pow( x, 2 ) - 1, y ), v, variables, sampleList );
    CPPUNIT_ASSERT_EQUAL( (size_t)5, sampleList1.size() );
    SampleList sampleList2 = CAD::samples( UnivariatePolynomial( y + x - 1, y ), v, variables, sampleList1 );
    CPPUNIT_ASSERT_EQUAL( (size_t)2, sampleList2.size() );    // two additional samples found
    bool once = true;
    while( true )
    {
        bool isRootFlag = false;    // checks the alternation of root and non-root
        for( SampleList::const_iterator i = sampleList1.begin(); i != sampleList1.end(); ++i )
        {
            //                        RealAlgebraicNumberIRPtr irA = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR > ( *i );
            //                        RealAlgebraicNumberNRPtr nrA = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR > ( *i );
            //                        if( irA != 0 )
            //                            cout << static_cast<RealAlgebraicNumberIR> ( *irA ) << "i " << "(isRoot=" << irA->isRoot( ) << ")" << endl;
            //                        else if( nrA != 0 )
            //                            cout << static_cast<numeric> ( *nrA ) << "n " << "(isRoot=" << nrA->isRoot( ) << ")" << endl;
            CPPUNIT_ASSERT_EQUAL( isRootFlag, (*i)->isRoot() );
            isRootFlag = !isRootFlag;
        }
        if( !once )
            break;
        sampleList1.insert( sampleList2.begin(), sampleList2.end() );
        once = false;
    }
}

void CAD_unittest::testSamples()
{
    cad.complete();
    //    vector<RealAlgebraicPoint> s = cad.samples( );
    //    cout << "---" << endl;
    //    for( vector<RealAlgebraicPoint>::const_iterator i = s.begin( ); i != s.end( ); ++i )
    //    {
    //        cout << "Sample: ( ";
    //        //        cout << *i << endl;
    //        for( RealAlgebraicPoint::const_iterator j = i->begin( ); j != i->end( ); ++j )
    //        {
    //            RealAlgebraicNumberIRPtr irA = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR > ( *j );
    //            RealAlgebraicNumberNRPtr nrA = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR > ( *j );
    //            if( irA != 0 )
    //                cout << *irA << " ";
    //            else if( nrA != 0 )
    //                cout << static_cast<numeric> ( *nrA ) << " ";
    //        }
    //        cout << ")" << endl;
    //    }
    //        CPPUNIT_ASSERT( (size_t) 21 <= s.size( ) );
    //    vector<SampleList> sampleLists = cad.SampleLists( );
    //    for( vector<SampleList>::const_iterator j = sampleLists.begin( ); j != sampleLists.end( ); ++j )
    //    {
    //        cout << "Sample list: { ";
    //        for( SampleList::const_iterator i = j->begin( ); i != j->end( ); ++i )
    //        {
    //            print( *i );
    //            cout << " ";
    //        }
    //        cout << " }" << endl;
    //    }
}

void CAD_unittest::testElimination()
{
    GiNaC::symbol x( "x" ), y( "y" ), z( "z" );
    UnivariatePolynomial P( x * x + y * y + z * z - 1, z );
    UnivariatePolynomialSet PP;
    PP.insert( P );
    // This corresponds to example 11.1 a) in "Algorithms in real algebraic geometry" p. 405

    /*
     *UnivariatePolynomialSet Q = GiNaCRA::CAD::eliminationSet( PP, y );
     *CPPUNIT_ASSERT( Q.size() == 1 );
     *for (UnivariatePolynomialSet::iterator it = Q.begin(); it != Q.end(); ++it)
     *    cout << *it << endl;
     *UnivariatePolynomial QQ( x * x + y * y - 1, y );
     *Q.insert( QQ );
     *CPPUNIT_ASSERT( Q.size() == 1 );
     */

    vector<vector<UnivariatePolynomial> > elimSets = cad.eliminationSets();
    for( unsigned i = 0; i != elimSets.size(); ++i )
    {
        for( vector<UnivariatePolynomial>::const_iterator j = elimSets[i].begin(); j != elimSets[i].end(); ++j )
            CPPUNIT_ASSERT_EQUAL( cad.variables()[i], elimSets[i].front().variable() );
        //            cout << "elimset" << i << ": " << *j << endl;
    }
    vector<symbol> v = vector<symbol>();
    v.push_back( y );
    v.push_back( x );
    p1 = UnivariatePolynomial( pow( x - 2, 2 ) + pow( y - 2, 2 ) - 1, x );
    p2 = UnivariatePolynomial( x - y, x );

    UnivariatePolynomialSet s;

    s.insert( p1 );
    s.insert( p2 );
    cad      = CAD( s, v );
    elimSets = cad.eliminationSets();
    for( unsigned i = 0; i != elimSets.size(); ++i )
    {
        for( vector<UnivariatePolynomial>::const_iterator j = elimSets[i].begin(); j != elimSets[i].end(); ++j )
            CPPUNIT_ASSERT_EQUAL( cad.variables()[i], elimSets[i].front().variable() );
        //                    cout << "elimset" << i << ": " << *j << endl;
    }
}

void CAD_unittest::testAddPolynomials()
{
    RealAlgebraicPoint r = RealAlgebraicPoint();
    vector<Constraint> constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, ZERO_SIGN, cad.variables() ));
    CPPUNIT_ASSERT( cad.check( constraints, r ));
    list<UnivariatePolynomial> polys( 1, UnivariatePolynomial( x + y + 2, x ));
    cad.addPolynomials<list<UnivariatePolynomial>::const_iterator>( polys.begin(), polys.end(), cad.variables() );
    CPPUNIT_ASSERT( cad.check( constraints, r ));    // the CAD must contain the previous sample

    //Thoes will fail
    /*
    constraints.push_back( Constraint( polys.back(), ZERO_SIGN, cad.variables() ));
    CPPUNIT_ASSERT( !cad.check( constraints, r ));    // all constraints together cannot have a common zero
    constraints = vector<Constraint>();
    constraints.push_back( Constraint( polys.back(), ZERO_SIGN, cad.variables() ));
    CPPUNIT_ASSERT( cad.check( constraints, r ));    // only the new constraint is of course sat
    */
}
