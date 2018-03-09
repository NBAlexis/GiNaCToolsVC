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


//#include <iostream>
//#include <assert.h>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaC;

/**
 * Application testing real root isolation of a multivariate triangular system.
 *
 * @author Ulrich Loup
 * @since 2010-04-12
 * @version 2010-04-16
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */
int example_NFM2011presentationmain()
{
    symbol x( "x" ), y( "y" );
    // (x-1) * (pow(x, 2)-2) * (x-3) * (pow(x,2)+1) * (x+1)
    UnivariatePolynomial p1( pow( x, 7 ) - 3 * pow( x, 6 ) - 2 * pow( x, 5 ) + 6 * pow( x, 4 ) - pow( x, 3 ) + 3 * pow( x, 2 ) + 2 * x - 6,
                             x ), p2( pow( 5 * y - 1, 2 ) + 3 * x - 1, y );

    cout << endl << "Compute the common real roots of " << endl << p1 << endl << " and" << endl << p2 << "." << endl << endl;
    list<pair<RealAlgebraicNumberIR, RealAlgebraicNumberIR> > commonRoots = list<pair<RealAlgebraicNumberIR, RealAlgebraicNumberIR> >();

    // compute real roots of p1 directly
    list<RealAlgebraicNumberIR> roots1 = RealAlgebraicNumberIRFactory::realRoots( RationalUnivariatePolynomial( p1 ));
    cout << p1 << " has " << roots1.size() << " real roots:" << endl;
    for( list<RealAlgebraicNumberIR>::const_iterator i = roots1.begin(); i != roots1.end(); ++i )
        cout << *i << endl;

    cout << endl;
    // compute real roots of p2 stepwise using the roots of p1
    RationalUnivariatePolynomial rem = RationalUnivariatePolynomial( p2 % p2.diff().primpart(), x );
    cout << "Remainder of " << p2 << " modulo its derivative: " << rem << endl;
    assert( rem != 0 );
    for( list<RealAlgebraicNumberIR>::const_iterator i = roots1.begin(); i != roots1.end(); ++i )
    {
        RationalUnivariatePolynomial sepapart;
        int                          sign = i->sgn( rem );
        cout << "Sign of " << rem << " at " << *i << ": " << sign << endl;
        switch( sign )
        {
            case 0:
                sepapart = RationalUnivariatePolynomial( p2 - rem, y );
                break;
            case -1:
                sepapart = RationalUnivariatePolynomial( p2.subs( x == i->Interval().Left() ), y );
                break;
            case 1:
                sepapart = RationalUnivariatePolynomial( p2.subs( x == i->Interval().Right() ), y );
                break;
        }
        cout << "==> Separable part: " << sepapart << endl;
        list<RealAlgebraicNumberIR> roots2 = RealAlgebraicNumberIRFactory::realRoots( sepapart );
        cout << "==> Found " << roots2.size() << " new common real root(s) " << endl;
        for( list<RealAlgebraicNumberIR>::const_iterator j = roots2.begin(); j != roots2.end(); ++j )
        {
            cout << "   ****   (" << *i << "," << endl << "           " << *j << ")" << endl;
            commonRoots.push_back( pair<RealAlgebraicNumberIR, RealAlgebraicNumberIR>( *i, *j ));
        }
    }
    cout << endl << "Found altogether " << commonRoots.size() << " common roots (precise up to an error of 0.001): " << endl;
    for( list<pair<RealAlgebraicNumberIR, RealAlgebraicNumberIR> >::iterator i = commonRoots.begin(); i != commonRoots.end(); ++i )
    {
        i->first.refine( 0.001 );
        i->second.refine( 0.001 );
        cout << "( " << i->first.approximateValue() << ", " << i->second.approximateValue() << " )" << endl;
    }
    cout << endl;
    return 0;
}
