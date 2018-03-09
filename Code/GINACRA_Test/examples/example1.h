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
 * g++ -lcln -lginac -lginacra -o example1 example1.cpp
 * @author Ulrich Loup
 * @author
 * @since 2010-12-25
 * @version 2010-12-26
 */

//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;

int example1main()
{
    symbol x( "x" );
    ex e( -15015 + 12673 * x - 3954 * pow( x, 2 ) + 574 * pow( x, 3 ) - 39 * pow( x, 4 ) + pow( x, 5 ));
    RationalUnivariatePolynomial p( e, x );
    list<RealAlgebraicNumberPtr> roots = RealAlgebraicNumberFactory::realRoots( p );
    cout << p << " has " << roots.size() << " real roots:" << endl;

    for( list<RealAlgebraicNumberPtr>::const_iterator root = roots.begin(); root != roots.end(); ++root )
    {
        RealAlgebraicNumberIRPtr ir = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *root );
        if( ir != 0 )
            cout << *ir << endl;
        RealAlgebraicNumberNRPtr nr = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *root );
        if( nr != 0 )
            cout << *nr << endl;
    }

    cout << "List of refined intervals for the roots:" << endl;
    for( list<RealAlgebraicNumberPtr>::iterator root = roots.begin(); root != roots.end(); ++root )
    {
        RealAlgebraicNumberIRPtr ir = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *root );
        if( ir != 0 )
        {
            for( int i = 0; i < 10; i++ )
                ir->refine();
            cout << *ir << endl;
        }

        RealAlgebraicNumberNRPtr nr = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *root );
        if( nr != 0 )
            cout << *nr << endl;
    }
    return 0;
}
