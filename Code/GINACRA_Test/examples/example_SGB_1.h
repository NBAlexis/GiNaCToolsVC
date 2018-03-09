#if 0
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
 * g++ -lcln -lginac -lginacra -o SpecialGroebnerBasis_example1 SpecialGroebnerBasis_example1.cpp
 * @author Ulrich Loup
 * @since 2010-05-05
 * @version 2010-05-05
 */

//#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaC;

//const string VERSION = "2010-05-05";
//const string SUPPORT = "Ulrich Loup <loup* @cs.rwth-aachen.de>";

//////////////////
// Main program //
//////////////////

int example_SGB_1main()
{
    cout << endl;
    cout << " GiNaCRA Example on MultivariatePolynomial computations with special Groebner basis, version " << VERSION << endl << "";
    cout << " Support: " << SUPPORT << endl << endl;

    GiNaC::symbol  x( "x" ), y( "y" );
    vector<symbol> l = vector<symbol>();
    l.push_back( x );
    l.push_back( y );
    MultivariatePolynomial<ex_is_lesseq_deggrlex>        p1( x * x - 4, l );
    MultivariatePolynomial<ex_is_lesseq_deggrlex>        p2( y * y - x * y + 1, l );
    list<MultivariatePolynomial<ex_is_lesseq_deggrlex> > gb = list<MultivariatePolynomial<ex_is_lesseq_deggrlex> >();
    gb.push_back( p1 );
    gb.push_back( p2 );
    cout << "Special Groebner Basis:" << endl;
    for( list<MultivariatePolynomial<ex_is_lesseq_deggrlex> >::const_iterator i = gb.begin(); i != gb.end(); ++i )
        cout << "  " << *i << endl;
    const list<MultivariateMonomial<ex_is_lesseq_deggrlex> > monomials =
        MultivariateMonomial<ex_is_lesseq_deggrlex>::monomialsUnderTheStaircase( gb );
    const list<MultivariateMonomial<ex_is_lesseq_deggrlex> > corners = MultivariateMonomial<ex_is_lesseq_deggrlex>::cornersOfTheStaircase( gb );
    cout << "Monomials under the Staircase:" << endl;
    for( list<MultivariateMonomial<ex_is_lesseq_deggrlex> >::const_iterator i = monomials.begin(); i != monomials.end(); ++i )
        cout << "  " << *i << endl;
    cout << "Corners of the Staircase:" << endl;
    for( list<MultivariateMonomial<ex_is_lesseq_deggrlex> >::const_iterator i = corners.begin(); i != corners.end(); ++i )
        cout << "  " << *i << endl;
    cout << "Example finished." << endl << endl;
    return 0;
}
#endif