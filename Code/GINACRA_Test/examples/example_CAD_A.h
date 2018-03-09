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
 * Example file for testing the GiNaC Real Algebra package.
 *
 * @author Ulrich Loup
 * @since 2012-05-18
 * @version 2012-05-18
 */

//#include <string>
//#include <ctime>
//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;
using namespace GiNaC;

void runTest( vector<GiNaC::sign> signs, CADSettings settings );

int example_CAD_Amain()
{
    CADSettings s1 = CADSettings::getSettings();
    s1.setPreferNonrootSamples( false );
    CADSettings s2 = CADSettings::getSettings();
    s2.setPreferNonrootSamples( true );

    vector<GiNaC::sign> zero_signs = vector<GiNaC::sign>( 3, GiNaC::ZERO_SIGN );
    //    runTest( zero_signs, CADSettings::getSettings() );
    //    runTest( zero_signs, CADSettings::getSettings( LOWDEG_CADSETTING & ODDDEG_CADSETTING ) );
    //    runTest( zero_signs, CADSettings::getSettings( LOWDEG_CADSETTING & EVENDEG_CADSETTING) );
    runTest( zero_signs, s1 );
    runTest( zero_signs, s2 );
    //    runTest( zero_signs, CADSettings::getSettings( LOWDEG_CADSETTING & ODDDEG_CADSETTING, RealAlgebraicNumberSettings::SIMPLE_ISOLATIONSTRATEGY ) );
    //    runTest( zero_signs, CADSettings::getSettings() );

    return 0;
}

void runTest( vector<GiNaC::sign> signs, CADSettings settings )
{
    symbol x( "x" ), y( "y" ), z( "z" );
    vector<symbol> v = vector<symbol>();
    v.push_back( x );
    v.push_back( y );
    v.push_back( z );

    //    UnivariatePolynomial p1( 144 * pow( y, 2 ) + 96 * pow( x, 2 ) * y + 9 * pow( x, 4 ) + 105 * pow( x, 2 ) + 70 * x - 98, x );
    //    UnivariatePolynomial p2( x * pow( y, 2 ) + 6 * x * y + pow( x, 3 ) + 9 * x, x );
    UnivariatePolynomial p1( x + y + z - numeric( 1, 3 ), x );
    UnivariatePolynomial p2( x - y + z - numeric( 1, 5 ), x );
    UnivariatePolynomial p3( x + y - z - numeric( 1, 7 ), x );

    UnivariatePolynomialSet s;
    s.insert( p1 );
    s.insert( p2 );
    s.insert( p3 );

    cout << endl << "Initializing " << endl << settings << endl;
    double time = clock();
    CAD cad = CAD( s, v, settings );
    cout << " done in " << ((clock() - time) / CLOCKS_PER_SEC) << " sec." << endl;
    cout << "Elimination set sizes:";
    vector<vector<UnivariatePolynomial> > elimSets = cad.eliminationSets();
    for( unsigned i = 0; i != elimSets.size(); ++i )
        cout << "  Level " << i << ": " << elimSets[i].size();
    cout << endl;
    for( unsigned i = 0; i != elimSets.size(); ++i )
    {
        cout << "  Level " << i << " (" << elimSets[i].size() << "): ";
        for( vector<UnivariatePolynomial>::const_iterator j = elimSets[i].begin(); j != elimSets[i].end(); ++j )
            cout << *j << "   ";
        cout << endl;
    }
    RealAlgebraicPoint r = RealAlgebraicPoint();
    vector<Constraint> constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, signs[0], v ));
    constraints.push_back( Constraint( p2, signs[1], v ));
    constraints.push_back( Constraint( p3, signs[2], v ));

    RealAlgebraicPoint solution = RealAlgebraicPoint();
    solution.push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( numeric( 6, 35 ))));
    solution.push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( numeric( 1, 15 ))));
    solution.push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( numeric( 2, 21 ))));
    bool sat = true;
    for( unsigned k = 0; k != 3; ++k )
        sat = sat && constraints[k].satisfiedBy( solution );
    string satString = sat ? "satisfied" : "unsatisfied";
    cout << "Solving the system" << endl;
    for( vector<Constraint>::const_iterator i = constraints.begin(); i != constraints.end(); ++i )
        cout << "  " << *i << endl;
    cout << "being " << satString << " by " << solution << " by computing a CAD..." << endl;
    time = clock();
    bool result = cad.check( constraints, r );
    time = clock() - time;
    cout << "Result: " << result << endl;
    cout << "Sample: " << r << endl;
    cout << "#Samples computed: " << cad.samples().size() << endl;
    cout << "CAD complete: " << cad.isComplete() << endl;
    cout << "Computation time: " << (time / CLOCKS_PER_SEC) << " sec" << endl;
    //    cout << "Sample tree:" << endl;
    //    cad.printSampleTree();
}
