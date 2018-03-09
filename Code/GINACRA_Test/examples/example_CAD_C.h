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
 * @since 2012-05-19
 * @version 2012-05-19
 * @see smtlib 2 benchmarks
 */

//#include <string>
//#include <ctime>
//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;
using namespace GiNaC;

void runTestec( CADSettings settings );

int example_CAD_Cmain()
{
    CADSettings s1 = CADSettings::getSettings();
    //    s1.setPreferNonrootSamples( false );

    runTestec( s1 );
    return 0;
}

void runTestec( CADSettings settings )
{
    symbol a( "p_2" ), b( "p_3" ), c( "p_4" ), d( "p_0" ), x( "height_0" ), y( "delta_0" ), z( "bounce_1" ), w( "bounce_5" );

    UnivariatePolynomial p1( -a, a );
    UnivariatePolynomial p2( -b, a );
    UnivariatePolynomial p3( -c, a );
    UnivariatePolynomial p4( -80 + x, a );
    UnivariatePolynomial p5( -200 + x, a );
    UnivariatePolynomial p6( 1 - 10 * y, a );
    UnivariatePolynomial p7( -1 + 5 * y, a );
    UnivariatePolynomial p8( -d, a );
    UnivariatePolynomial p9( 1 - z, a );
    UnivariatePolynomial pA( -w, a );

    vector<symbol> v = vector<symbol>();
    v.push_back( a );
    v.push_back( b );
    v.push_back( c );
    v.push_back( d );
    v.push_back( x );
    v.push_back( y );
    v.push_back( z );
    v.push_back( w );

    UnivariatePolynomialSet s;
    s.insert( p1 );
    s.insert( p2 );
    s.insert( p3 );
    s.insert( p4 );
    s.insert( p5 );
    s.insert( p6 );
    s.insert( p7 );
    s.insert( p8 );
    s.insert( p9 );
    s.insert( pA );

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
    constraints.push_back( Constraint( p1, GiNaC::POSITIVE_SIGN, v ));
    constraints.push_back( Constraint( p2, GiNaC::POSITIVE_SIGN, v ));
    constraints.push_back( Constraint( p3, GiNaC::POSITIVE_SIGN, v ));
    constraints.push_back( Constraint( p4, GiNaC::POSITIVE_SIGN, v ));
    constraints.push_back( Constraint( p5, GiNaC::POSITIVE_SIGN, v ));
    constraints.push_back( Constraint( p6, GiNaC::POSITIVE_SIGN, v ));
    constraints.push_back( Constraint( p7, GiNaC::POSITIVE_SIGN, v ));
    constraints.push_back( Constraint( p8, GiNaC::ZERO_SIGN, v ));
    constraints.push_back( Constraint( p9, GiNaC::ZERO_SIGN, v ));
    constraints.push_back( Constraint( pA, GiNaC::ZERO_SIGN, v ));

    cout << "Solving the system" << endl;
    for( vector<Constraint>::const_iterator i = constraints.begin(); i != constraints.end(); ++i )
        cout << "  " << *i << endl;
    cout << "by computing a CAD..." << endl;
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
