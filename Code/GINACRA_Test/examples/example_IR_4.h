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
 * Example file for testing the GiNaC Real Algebra package using very less lines of code.
 *
 * Compile with:
 * g++ -lcln -lginac -lginacra -o example_IR_4 example_IR_4.cpp
 * @author Ulrich Loup
 * @author
 * @since 2010-12-22
 * @version 2010-12-22
 */

#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaC;
using namespace GiNaCRA;

int main( int argc, char** argv )
{
    symbol x( "x" );    // main variable of the GiNaCRA polynomial
    RationalUnivariatePolynomial p( -15015 + 12673 * x - 3954 * pow( x, 2 ) + 574 * pow( x, 3 ) - 39 * pow( x, 4 ) + pow( x, 5 ), x );
    list<RealAlgebraicNumberPtr> roots = RealAlgebraicNumberFactory::realRoots( p );
    cout << "The rational univariate polynomial " << p << " has " << roots.size() << " real roots:" << endl;
    for( list<RealAlgebraicNumberPtr>::const_iterator root = roots.begin(); root != roots.end(); ++root )
    {
        cout << " " << *root << endl;
        if( (*root)->sgn( p ) != 0 )
            return 1;    // root was found mistakenly
    }
    return 0;
}
