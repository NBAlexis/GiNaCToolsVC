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
 * @since 2012-01-25
 * @version 2012-04-23
 */

//#include <string>
//#include <ctime>
//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;
using namespace GiNaC;

int example_CAD_6main()
{
    symbol x( "x" ), y( "y" ), z( "z" );
    vector<symbol> v = vector<symbol>();
    v.push_back( x );
    v.push_back( y );
    v.push_back( z );

    UnivariatePolynomial p1( pow( x, 2 ) + pow( y, 2 ) + pow( z, 2 ) - 1, x );
    UnivariatePolynomial p2( x * x + y * y, x );
    UnivariatePolynomial p3( z * z * z - numeric( 1, 2 ), x );

    UnivariatePolynomialSet s;
    s.insert( p1 );
    s.insert( p2 );
    s.insert( p3 );

    cout << "Initializing (elimination processing)...";
    double startTime = clock();
    CADSettings setting = CADSettings::getSettings( LOWDEG_CADSETTING );
    setting.setPreferNonrootSamples( true );
    CAD cad = CAD( s, v, setting );
    cout << " done in " << ((clock() - startTime) / CLOCKS_PER_SEC) << " sec." << endl;
    cout << "Elimination sets: " << endl;
    vector<vector<UnivariatePolynomial> > elimSets = cad.eliminationSets();
    for( unsigned i = 0; i != elimSets.size(); ++i )
    {
        cout << "  Level " << i << " (" << elimSets[i].size() << "): ";
        for( vector<UnivariatePolynomial>::const_iterator j = elimSets[i].begin(); j != elimSets[i].end(); ++j )
            cout << *j << "   ";
        cout << endl;
    }

    /* Desired:
     * Level 0: z**3 - 1/2(x),  x**2 + y**2 + z**2 - 1(x),  x**2 + y**2(x)
     * Level 1: y**2 + z**2 - 1(y),  z**3 - 1/2(y),  y**2 + z**2 - 1(y),  y**2(y),  y**2(y)
     * Level 2: z**2 - 1(z),  z**3 - 1/2(z),  z**2 - 1(z)
     */

    RealAlgebraicPoint r = RealAlgebraicPoint();
    vector<Constraint> constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, NEGATIVE_SIGN, v ));
    constraints.push_back( Constraint( p2, POSITIVE_SIGN, v ));
    constraints.push_back( Constraint( p3, POSITIVE_SIGN, v ));

    cout << "Solving the system " << endl;
    for( vector<Constraint>::const_iterator i = constraints.begin(); i != constraints.end(); ++i )
        cout << "  " << *i << endl;
    cout << "by computing a CAD..." << endl;
    startTime = clock();
    //    cout << "Complete CAD! " << endl;
    //    cad.complete();
    cout << "Result: " << cad.check( constraints, r ) << endl;
    cout << "Sample: " << r << endl;
    cout << "CAD complete: " << cad.isComplete() << " (" << cad.samples().size() << " samples)" << endl;
    cout << "Computation time: " << ((clock() - startTime) / CLOCKS_PER_SEC) << " sec" << endl;

    RealAlgebraicPoint solution = RealAlgebraicPoint();
    solution.push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( GiNaC::ZERO )));
    solution.push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( numeric( 1, 8 ))));
    solution.push_back( RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( numeric( 7, 8 ))));
    bool sat = true;
    for( unsigned k = 0; k != 3; ++k )
        sat = sat && constraints[k].satisfiedBy( solution );
    string satString = sat ? "satisfied" : "unsatisfied";
    cout << "With " << solution << ", the system is " << satString << "." << endl;

    //    cout << "Sample tree:" << endl;
    //    cad.printSampleTree();
    //    vector<RealAlgebraicPoint> samples = cad.samples();
    //    cout << "All samples (" << samples.size() << "):" << endl;
    //    for( vector<RealAlgebraicPoint>::const_iterator i = samples.begin(); i != samples.end(); ++i )
    //        cout << "  " << *i << endl;
    return 0;
}
