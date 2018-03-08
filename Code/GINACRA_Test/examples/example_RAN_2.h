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
 * g++ -lcln -lginac -lginacra -o example_RAN_2 example_RAN_2.cpp
 * @author Joachim Redies
 * @since 2011-05-09
 * @version 2010-05-09
 */

#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaC;
using namespace GiNaCRA;

#include <string>
#include <ctime>

int main( int argc, char** argv )
{
    symbol x( "x" );
    string s = "x";
    ex e( (x - 1) * (x - 2) * (x - 3) * (x - 4) * (x - 5) * (x - 6) * (x - 7) * (x - 8) * (x - 9) * (x - 10) * (x - 11) * (x - 12) * (x - 13)
          * (x - 14) * (x - 15) * (x - 16) * (x - 17) * (x - 18) * (x - 19) * (x - 20) * (x - 21) * (x - 22) * (x - 23) * (x - 24) * (x - 25)
          * (x - 26) * (x - 27) );
    RationalUnivariatePolynomial p( e.expand(), x );
    double                       startTime = clock();
    list<RealAlgebraicNumberPtr> roots     = RealAlgebraicNumberFactory::realRoots( p );
    cout << "Time for Root Elimination: " << (clock() - startTime) / CLOCKS_PER_SEC << endl;
    cout << p << " has " << roots.size() << " real roots:" << endl;

    startTime = clock();

    const numeric err = 0.00000001;
    for( list<RealAlgebraicNumberPtr>::iterator root = roots.begin(); root != roots.end(); ++root )
    {
        RealAlgebraicNumberIRPtr rootIR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *root );
        if( rootIR != 0 )
        {
            rootIR->refine( err );
            cout << rootIR << endl;
        }
    }

    cout << "Time for Approxmiation with sturm/bisection: " << (clock() - startTime) / CLOCKS_PER_SEC << endl;
    return 0;
}
