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
 * g++ -lcln -lginac -lginacra -o example_IR_3 example_IR_3.cpp
 * @author Ulrich Loup
 * @since 2011-10-17
 * @version 2011-10-17
 */

//#include <ctime>
//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaC;
using namespace GiNaCRA;

//const string VERSION = "2011-10-17";
//const string SUPPORT = "Ulrich Loup <loup* @cs.rwth-aachen.de>";

//////////////////
// Main program //
//////////////////

int example_IR_3main()
{
    cout << endl;
    cout << " GiNaCRA Example on RealAlgebraicNumberPtr from [Davenport et al. 1987] Version " << VERSION << endl << "";
    cout << " Support: " << SUPPORT << endl << endl;

    GiNaC::symbol x( "x" );    // main variable of the GiNaCRA polynomial
    RationalUnivariatePolynomial
    p1 = RationalUnivariatePolynomial( pow( x, 3 ) + pow( x, 5 ) - numeric( 27, 5 ) - pow( x, 5 ) + numeric( 32, 5 ), x );
    RationalUnivariatePolynomial
    p2 = RationalUnivariatePolynomial( (-pow( pow( x, 5 ) - 9, 2 ) + pow( x, 5 ) - 3 + 1) * (pow( x, 5 ) - numeric( 1, 25 )), x );

    cout << "Computing the real roots of " << p1 << "...";
    double                       startTime = clock();
    list<RealAlgebraicNumberPtr> roots1    = RealAlgebraicNumberFactory::realRoots( p1 );
    cout << " done in " << (clock() - startTime) / CLOCKS_PER_SEC << " sec (found " << roots1.size() << " real root)." << endl;
    RealAlgebraicNumberPtr r1 = roots1.front();

    cout << "Computing the real roots of " << p2 << "...";
    startTime = clock();
    list<RealAlgebraicNumberPtr> roots2 = RealAlgebraicNumberFactory::realRoots( p2 );
    for( list<RealAlgebraicNumberPtr>::const_iterator i = roots2.begin(); i != roots2.end(); ++i )
        cout << "root " << *i << endl;
    cout << " done in " << (clock() - startTime) / CLOCKS_PER_SEC << " sec (found " << roots2.size() << " real root)." << endl;
    RealAlgebraicNumberPtr r2 = roots2.front();

    cout << "Testing the real roots for equality: " << r1 << " == " << r2 << "...";
    startTime = clock();
    bool equal = (r1 == r2);
    cout << " done in " << (clock() - startTime) / CLOCKS_PER_SEC << " sec (result: " << equal << ")." << endl;
    return 0;
}
