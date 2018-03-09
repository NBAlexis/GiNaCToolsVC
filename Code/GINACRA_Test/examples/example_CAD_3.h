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
 * Compile with:
 * g++ -lcln -lginac -lginacra -o example example_CAD_3.cpp
 * @author Ulrich Loup
 * @since 2011-12-31
 * @version 2012-01-12
 */

//#include <string>
//#include <ctime>
//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;
using namespace GiNaC;

int example_CAD_3main()
{
    symbol x( "x" ), y( "y" );
    vector<symbol> v = vector<symbol>();
    v.push_back( x );
    v.push_back( y );

    UnivariatePolynomial p1( pow( x, 2 ) + pow( y, 2 ) - 1, x );
    UnivariatePolynomial p2( x + y - 1, x );
    UnivariatePolynomial p3( y - x + 2, x );
    UnivariatePolynomial p4( pow( x, 2 ) + pow( y, 2 ) - 3, x );

    UnivariatePolynomialSet s;
    s.insert( p1 );
    s.insert( p2 );
    s.insert( p3 );
    s.insert( p4 );

    cout << "Initializing (elimination processing)...";
    double startTime = clock();
    CAD cad = CAD( s, v );
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

    RealAlgebraicPoint r = RealAlgebraicPoint();
    vector<Constraint> constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, POSITIVE_SIGN, v ));
    constraints.push_back( Constraint( p2, ZERO_SIGN, v ));
    constraints.push_back( Constraint( p3, ZERO_SIGN, v ));
    constraints.push_back( Constraint( p4, NEGATIVE_SIGN, v ));

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
