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
 * @author
 * @since 2010-12-25
 * @version 2010-12-26
 */

//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;

int example3main()
{
    symbol x( "x" );
    RationalUnivariatePolynomial p1( pow( x, 2 ) - 2, x );
    list<RealAlgebraicNumberPtr> sqrt2s = RealAlgebraicNumberFactory::realRoots( p1 );

    RealAlgebraicNumberIRPtr ir1 = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( sqrt2s.back() );
    if( ir1 != 0 )
        cout << "Interval representation of sqrt(2): " << *ir1 << endl;

    RealAlgebraicNumberIRPtr ir2 = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( sqrt2s.front() );
    if( ir2 != 0 )
        cout << "Interval representation of sqrt(2): " << *ir2 << endl;

    RealAlgebraicNumberIR minustwo = *ir2 * *ir1;
    cout << "sqrt(2) * -sqrt(2) = " << minustwo << endl;

    RealAlgebraicNumberIR zero = *ir2 + *ir1;
    cout << "sqrt(2) + -sqrt(2) = " << zero << endl;

    return 0;
}
