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
 * @since 2012-02-01
 * @version 2012-04-19
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
    symbol x( "x" ), y( "y" ), r1( "r1" ), r2( "r2" );
    vector<symbol> v = vector<symbol>();
    v.push_back( r1 );
    v.push_back( r2 );
    v.push_back( x );
    v.push_back( y );

    UnivariatePolynomial p1( pow( x - 3, 2 ) + pow( y - 3, 2 ) - r1, r1 );

    UnivariatePolynomialSet s;
    s.insert( p1 );

    cout << "Initializing (elimination processing)..." << endl;
    double startTime = clock();
    CAD cad = CAD( s, v );
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

    RealAlgebraicPoint r = RealAlgebraicPoint();
    vector<Constraint> constraints = vector<Constraint>();
    constraints.push_back( Constraint( p1, NEGATIVE_SIGN, v ));

    cout << "Solving the system" << endl;
    for( vector<Constraint>::const_iterator i = constraints.begin(); i != constraints.end(); ++i )
        cout << "  " << *i << endl;
    cout << "by computing a CAD..." << endl;
    startTime = clock();
    cout << "Result: " << cad.check( constraints, r ) << endl;
    cout << "Sample: " << r << endl;
    cout << "Computation time: " << ((clock() - startTime) / CLOCKS_PER_SEC) << " sec" << endl;
    cout << "Sample tree: " << endl;
    cad.printSampleTree();

    UnivariatePolynomial p2( pow( x + 3, 2 ) + pow( y + 3, 2 ) - r2, r1 );
    constraints.push_back( Constraint( p2, NEGATIVE_SIGN, v ));
    cout << "Adding the polynomial " << p2 << "..." << endl;
    cad.addPolynomial( p2, v );
    cout << "Elimination sets: " << endl;
    elimSets = cad.eliminationSets();
    for( unsigned i = 0; i != elimSets.size(); ++i )
    {
        cout << "  Level " << i << ": ";
        for( vector<UnivariatePolynomial>::const_iterator j = elimSets[i].begin(); j != elimSets[i].end(); ++j )
            cout << *j << "   ";
        cout << endl;
    }
    cout << "Checking the extended system" << endl;
    for( vector<Constraint>::const_iterator i = constraints.begin(); i != constraints.end(); ++i )
        cout << "  " << *i << endl;
    startTime = clock();
    cout << "Result: " << cad.check( constraints, r ) << endl;
    cout << "Sample: " << r << endl;
    cout << "Computation time: " << ((clock() - startTime) / CLOCKS_PER_SEC) << " sec" << endl;

    UnivariatePolynomial p3( r1 - 4, r1 );
    constraints.push_back( Constraint( p3, POSITIVE_SIGN, v ));
    cout << "Adding the polynomial " << p3 << "..." << endl;
    cad.addPolynomial( p3, v );
    cout << "Elimination sets: " << endl;
    elimSets = cad.eliminationSets();
    for( unsigned i = 0; i != elimSets.size(); ++i )
    {
        cout << "  Level " << i << ": ";
        for( vector<UnivariatePolynomial>::const_iterator j = elimSets[i].begin(); j != elimSets[i].end(); ++j )
            cout << *j << "   ";
        cout << endl;
    }
    cout << "Checking the extended system" << endl;
    for( vector<Constraint>::const_iterator i = constraints.begin(); i != constraints.end(); ++i )
        cout << "  " << *i << endl;
    startTime = clock();
    cout << "Result: " << cad.check( constraints, r ) << endl;
    cout << "Sample: " << r << endl;
    cout << "Computation time: " << ((clock() - startTime) / CLOCKS_PER_SEC) << " sec" << endl;

    UnivariatePolynomial p4( r2 - 4, r1 );
    constraints.push_back( Constraint( p4, POSITIVE_SIGN, v ));
    cout << "Adding the polynomial " << p4 << "..." << endl;
    cad.addPolynomial( p4, v );
    cout << "Elimination sets: " << endl;
    elimSets = cad.eliminationSets();
    for( unsigned i = 0; i != elimSets.size(); ++i )
    {
        cout << "  Level " << i << ": ";
        for( vector<UnivariatePolynomial>::const_iterator j = elimSets[i].begin(); j != elimSets[i].end(); ++j )
            cout << *j << "   ";
        cout << endl;
    }
    cout << "Checking the extended system" << endl;
    for( vector<Constraint>::const_iterator i = constraints.begin(); i != constraints.end(); ++i )
        cout << "  " << *i << endl;
    startTime = clock();
    cout << "Result: " << cad.check( constraints, r ) << endl;
    cout << "Sample: " << r << endl;
    cout << "Computation time: " << ((clock() - startTime) / CLOCKS_PER_SEC) << " sec" << endl;

    //    cout << "Sample tree:" << endl;
    //    cad.printSampleTree();
    //    cout << "All samples:" << endl;
    //    vector<RealAlgebraicPoint> samples = cad.samples();
    //    for( vector<RealAlgebraicPoint>::const_iterator i = samples.begin(); i != samples.end(); ++i )
    //        cout << "  " << *i << endl;
    return 0;
}
