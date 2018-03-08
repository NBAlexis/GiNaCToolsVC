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
 * g++ -lcln -lginac -lginacra -o example3 example3.cpp
 * @author Ulrich Loup
 * @since 2010-12-25
 * @version 2011-11-26
 */

#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;

int main( int argc, char** argv )
{
    symbol x( "x" ), y( "y" );
    OpenInterval i1( -1, 1 );
    OpenInterval i2( 2, 5 );
    ex t( i1 * x + i2 * y );
    cout << "linear Polynomial: " << t << endl;
    cout << "x-Derivative: " << t.subs( x == 2 * x ) << endl;
    cout << "y-Derivative: " << t.diff( y ) << endl;
    ex p( i1 * pow( x, 2 ) + i2 * y );
    cout << endl;
    cout << "non-linear Polynomial: " << p << endl;
    cout << "x-Derivative: " << p.diff( x ) << endl;
    cout << "y-Derivative: " << p.diff( y ) << endl;
    cout << endl;
    ex q( i1 * pow( x, 2 ) * pow( y, 3 ) + i2 * y * x + y );
    cout << "other non-linear Polynomial: " << q << endl;
    cout << "x-Derivative: " << q.diff( x ) << endl;
    cout << "y-Derivative: " << q.diff( y ) << endl;
    cout << endl;
    cout << "Interval arithmetic: " << i1 << " + " << i2 << " = " << i1 + i2 << endl;
    return 0;
}
