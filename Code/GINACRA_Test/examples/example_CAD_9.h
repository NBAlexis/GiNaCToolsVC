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
 * @since 2012-03-22
 * @version 2012-04-16
 */

#include <string>
#include <ctime>
#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;
using namespace GiNaC;

int main( int argc, char** argv )
{
    symbol x( "x" ), y( "y" );
    vector<symbol> v = vector<symbol>();
    v.push_back( x );
    v.push_back( y );

    UnivariatePolynomial p1( 144 * pow( y, 2 ) + 96 * pow( x, 2 ) * y + 9 * pow( x, 4 ) + 105 * pow( x, 2 ) + 70 * x - 98, x );
    UnivariatePolynomial p2( x * pow( y, 2 ) + 6 * x * y + pow( x, 3 ) + 9 * x, x );

    UnivariatePolynomialSet s;
    s.insert( p1 );
    s.insert( p2 );

    cout << "Initializing (elimination processing)...";
    double startTime = clock();
    CAD cad = CAD( s, v, CADSettings::getSettings( GROEBNER_CADSETTING | REALROOTCOUNT_CADSETTING ));
    cout << " done in " << ((clock() - startTime) / CLOCKS_PER_SEC) << " sec." << endl;
    cout << "Elimination sets: " << endl;
    vector<vector<UnivariatePolynomial> > elimSets = cad.eliminationSets();
    for( unsigned i = 0; i != elimSets.size(); ++i )
    {
        cout << "  Level " << i << ": ";
        for( vector<UnivariatePolynomial>::const_iterator j = elimSets[i].begin(); j != elimSets[i].end(); ++j )
            cout << *j << "   ";
        cout << endl;
    }
    //
    //    cout << "Completing (computing all samples)..." << endl;
    //    startTime = clock();
    //    cad.complete();
    //    cout << " done in " << ((clock() - startTime) / CLOCKS_PER_SEC) << " sec. Samples found: " << cad.samples().size() << endl;

    //
    RealAlgebraicPoint r = RealAlgebraicPoint();
    vector<Constraint> constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, ZERO_SIGN, v ));
    constraints.push_back( Constraint( p2, ZERO_SIGN, v ));

    cout << "Solving the system " << endl;
    for( vector<Constraint>::const_iterator i = constraints.begin(); i != constraints.end(); ++i )
        cout << "  " << *i << endl;
    cout << "by computing a CAD..." << endl;
    startTime = clock();
    cout << "Result: " << cad.check( constraints, r ) << endl;
    cout << "Sample: " << r << endl;
    cout << "Computation time: " << ((clock() - startTime) / CLOCKS_PER_SEC) << " sec" << endl;
    return 0;
}
