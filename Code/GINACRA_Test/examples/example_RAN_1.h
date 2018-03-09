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
 * g++ -lcln -lginac -lginacra -o example example_RAN_1.cpp
 * @author Ulrich Loup
 * @since 2012-01-05
 * @version 2012-01-05
 */

//#include <string>
//#include <ctime>
//#include <iostream>
//#include <typeinfo>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaCRA;
using namespace GiNaC;

int example_RAN_1main()
{
    symbol x( "x" ), y( "y" );
    vector<symbol> v = vector<symbol>();
    v.push_back( x );
    v.push_back( y );

    RationalUnivariatePolynomial p1( pow( (x - 1), 2 ) - 2, x );
    RationalUnivariatePolynomial p2( y * y - 2, y );

    list<RealAlgebraicNumberPtr> roots = RealAlgebraicNumberFactory::realRoots( p1 );
    cout << "Real roots to compute with (" << roots.size() << "):";
    for( list<RealAlgebraicNumberPtr>::const_iterator r = roots.begin(); r != roots.end(); ++r )
    {
        print( *r, cout << "  " );
        cout << "[numeric: " << ((*r)->approximateValue()) << "]" << endl;
    }
    cout << endl;

    RealAlgebraicNumberIR r1 = *std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( roots.front() );
    RealAlgebraicNumberIR r2 = *std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( roots.back() );
    cout << "Polynomial: " << p2 << endl;
    ex p2SubstitutedR1 = p2.subs( lst( p2.variable() ), (lst( r1 )));
    cout << "Substituted y by first root: " << p2SubstitutedR1 << endl;
    cout << "Numeric value: " << p2SubstitutedR1.evalf() << endl;
    cout << "Finer numeric value: " << p2SubstitutedR1.evalf( 8 ) << endl;
    ex p2SubstitutedR2 = p2.subs( lst( p2.variable() ), (lst( r2 )));
    cout << "Substituted y by first root: " << p2SubstitutedR2 << endl;
    cout << "Numeric value: " << p2SubstitutedR2.evalf() << endl;
    cout << "Finer numeric value: " << p2SubstitutedR2.evalf( 8 ) << endl << endl;

    ex test = x * y + 2;
    cout << "TEST: " << test << endl;
    cout << "TEST has sin: " << test.has( sin( GiNaC::wildcard() )) << endl;
    cout << "typeid of " << r1 << " contains RealAlgebraicNumber: " << (string( typeid( &r1 ).name() ).find( "RealAlgenraicNumber" ) == string::npos)
         << endl;
    cout << "typeid of " << r1 << " is " << typeid( &r1 ).name() << " and contains RealAlgebraicNumber: "
         << (string( typeid( &r1 ).name() ).find( "RealAlgenraicNumber" ) == string::npos) << endl;
    cout << "begin() of r1^2: " << *pow( r1, 2 ).begin() << endl;
    cout << "end() of r1^2: " << *pow( r1, 2 ).end() << endl;
    ex powerR1 = r1 ^ 2;
    cout << "r1^2: " << powerR1 + r2 << endl << endl;

    UnivariatePolynomial p3 = UnivariatePolynomial( x * x * y * y - 2 * x - 1, y );
    cout << "Polynomial: " << p3 << endl;
    UnivariatePolynomial p3Substituted = UnivariatePolynomial( p3.subs( lst( y ), (lst( r2 ))), x, false );
    cout << "Substituted y by r1: " << p3Substituted << endl;
    UnivariatePolynomial p3SubstitutedDiff = p3Substituted.diff();
    cout << "x-Derivative: " << p3SubstitutedDiff << endl;
    cout << "Polynomial modulo x-Derivative: " << (p3Substituted % p3SubstitutedDiff) << endl;

    cout << "Sturm sequence: " << endl;
    list<UnivariatePolynomial> seq = UnivariatePolynomial::standardSturmSequence( p3Substituted, p3SubstitutedDiff );
    for( list<UnivariatePolynomial>::const_iterator i = seq.begin(); i != seq.end(); ++i )
        cout << "  " << *i << endl;
    cout << "Absolute value of " << seq.front().subs( lst( x ), (lst( r2 ))) << ": " << abs( seq.front().subs( lst( x ), (lst( r2 )))) << endl;

    //    cout << "Exact evaluation of the subexpressions " << endl;
    //    for( const_iterator i = p2SubstitutedR1.begin( ); i != p2SubstitutedR1.end( ); ++i )
    //        cout << "  " << *i << ": " << endl;
    //    const_iterator i = p2SubstitutedR1.begin( );
    //    cout << "Power of IRs:" << *i->begin() << ": " << endl;
    //    numeric p2SubstitutedR1  = p2SubstitutedR1Evaluated;
    //    for(const_iterator i = p2SubstitutedR1.begin(); i != p2SubstitutedR1.end(); ++i )
    //        cout << "  " << *i << ": " << endl;
}
