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
 * g++ -lcln -lginac -lginacra -o example2 example2.cpp
 * @author Ulrich Loup
 * @author
 * @since 2010-12-25
 * @version 2010-12-26
 */

#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;

int main( int argc, char** argv )
{
    symbol x( "x" );
    ex e1( -15015 + 12673 * x - 3954 * pow( x, 2 ) + 574 * pow( x, 3 ) - 39 * pow( x, 4 ) + pow( x, 5 ));
    ex e2( -1155 + 886 * x - 236 * pow( x, 2 ) + 26 * pow( x, 3 ) - pow( x, 4 ));
    list<RationalUnivariatePolynomial> l = list<RationalUnivariatePolynomial>();
    l.push_back( RationalUnivariatePolynomial( e1, x ));
    l.push_back( RationalUnivariatePolynomial( e2, x ));

    list<RealAlgebraicNumberPtr> roots = RealAlgebraicNumberFactory::commonRealRoots( l );
    cout << l.front() << " and " << l.back() << endl << "have " << roots.size() << " common real roots:" << endl;

    for( list<RealAlgebraicNumberPtr>::const_iterator root = roots.begin(); root != roots.end(); ++root )
    {
        RealAlgebraicNumberIRPtr ir = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *root );
        if( ir != 0 )
            cout << *ir << endl;
        RealAlgebraicNumberNRPtr nr = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *root );
        if( nr != 0 )
            cout << *nr << endl;
    }

    return 0;
}
