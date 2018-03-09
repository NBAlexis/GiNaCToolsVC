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
 * g++ -lcln -lginac -lginacra -o example example_CAD_7.cpp
 * @author Joachm Redies
 * @since 2012-01-30
 * @version 2012-01-30
 */

//#include <string>
//#include <ctime>
//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;
using namespace GiNaC;

int example_CAD_7main()
{
    symbol x( "x" ), y( "y" );
    vector<symbol> v = vector<symbol>();
    v.push_back( x );
    v.push_back( y );

    UnivariatePolynomial p2( x + y - 1, x );
    UnivariatePolynomial p3( y - x + 2, x );

    /* This example exposes a bug in Algorithm 11.1 of ISBN 0-387-94090-1 and ISBN-13: 978-3642069642:
     * Following Alg. 11.1, R_ should be excluded from the elimination result, but it actually is important to find the solution point (-1/2, 3/2).
     */
    UnivariatePolynomial R_ = UnivariatePolynomial( p2.lcoeff() * p3 - p3.lcoeff() * p2, x );
    //    cout << R_ << ".deg=" << R_.degree() << endl;
    list<UnivariatePolynomial> l = UnivariatePolynomial::subresultants( p2, R_ );
    for( list<UnivariatePolynomial>::iterator it = l.begin(); it != l.end(); ++it )
        cout << *it << endl;

    return 0;
}
