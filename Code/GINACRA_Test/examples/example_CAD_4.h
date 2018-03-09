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
 * @since 2012-01-03
 * @version 2012-04-27
 */

//#include <string>
//#include <ctime>
//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;
using namespace GiNaC;

void runTestec4( CADSettings settings );

int example_CAD_4main()
{
    CADSettings setting = CADSettings::getSettings();

    setting.setPreferNonrootSamples( false );
    runTestec4( setting );

    setting.setPreferNonrootSamples( true );
    runTestec4( setting );
    return 0;
}

void runTestec4( CADSettings settings )
{
    symbol x( "x" ), y( "y" );
    vector<symbol> v = vector<symbol>();
    v.push_back( x );
    v.push_back( y );

    UnivariatePolynomial p1( pow( (x - 1), 2 ) + pow( (y - 1), 2 ) - 1, x );
    UnivariatePolynomial p2( x - y, x );

    UnivariatePolynomialSet s;
    s.insert( p1 );
    s.insert( p2 );

    cout << endl << "Initializing " << endl << settings << endl;
    double time = clock();
    CAD cad = CAD( s, v, settings );
    cout << " done in " << ((clock() - time) / CLOCKS_PER_SEC) << " sec." << endl;
    cout << "Elimination set sizes:";
    vector<vector<UnivariatePolynomial> > elimSets = cad.eliminationSets();
    for( unsigned i = 0; i != elimSets.size(); ++i )
        cout << "  Level " << i << ": " << elimSets[i].size();
    cout << endl;
    RealAlgebraicPoint r = RealAlgebraicPoint();
    vector<Constraint> constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, ZERO_SIGN, v ));
    constraints.push_back( Constraint( p2, ZERO_SIGN, v ));

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
}
