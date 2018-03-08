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
 * @author Ulrich Loup
 * @since 2012-03-12
 * @version 2012-03-13
 */

#include <iostream>
#include <ctime>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaC;
using namespace GiNaCRA;

int main( int argc, char** argv )
{
    cout << "Comparing times of gcd computations (relevant for RealAlgebraicNumberIR::refine())..." << endl;
    srand( time( NULL ));
    double time1 = clock();
    for( numeric i = 100; i != 10000; ++i )
        for( numeric j = 100; j != 10000; ++j )
            GiNaC::gcd( numeric( i ), numeric( j ));
    time1 = clock() - time1;
    cout << "  " << time1 / CLOCKS_PER_SEC << " sec by gcd on GiNaC::numeric" << endl;
    double time2 = clock();
    for( long i = 100; i != 10000; ++i )
        for( long j = 100; j != 10000; ++j )
            GiNaC::gcd( i, j );
    time2 = clock() - time2;
    cout << "  " << time2 / CLOCKS_PER_SEC << " sec by gcd on long" << endl;
    cout << "Improvement factor: " << (time1 / time2) << endl;
    //    
    //    RationalUnivariatePolynomial p( pow( x, 5 ) - 3 * pow( x, 4 ) + pow( x, 3 ) - pow( x, 2 ) + 2 * x - 2, x );
    //    RationalUnivariatePolynomial p( pow( x, 2 ) - 5, x );
    //    cout << "Example for factoring a real algebraic polynomial." << endl << endl;
    //    RealAlgebraicNumberIR r = *std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( RealAlgebraicNumberFactory::realRoots( p ).front() );
    //    cout << "r = " << r << endl << endl;
    //
    //    RationalUnivariatePolynomial q( 2 * pow( y - r, 3 ), y );
    //    cout << "q := 2(y - r)^3 = " << q << endl << endl;
    //    exmap m;
    //    m[x] = y;
    //    cout << "q / " << r.polynomial().subs( m ) << " = " << q.quo( RationalUnivariatePolynomial( r.polynomial().subs( m ), y )) << endl << endl;
    //    cout << "q' = " << q.diff() << endl << endl;
    //    cout << "rem(q, q') = " << q.rem( q.diff() ) << endl << endl;
    //    RationalUnivariatePolynomial g = q.gcd( q.diff() );
    //    cout << "gcd(q, q') = " << g << endl << endl;
    //    cout << "q / gcd(q, q') = " << q / g << endl << endl;
    //    cout << "Standard Sturm sequence of q and q':" << endl;
    //    list<RationalUnivariatePolynomial> seq = RationalUnivariatePolynomial::standardSturmSequence( q, q.diff() );
    //    for( list<RationalUnivariatePolynomial>::const_iterator i = seq.begin(); i != seq.end(); ++i )
    //        cout << "  " << *i << endl;
    //    cout << endl;
    //    RealAlgebraicNumberIR rr = *std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( RealAlgebraicNumberFactory::realRoots( q ).front() );
    //    cout << "Real root of q: r' = " << rr << endl << endl;
    //    RationalUnivariatePolynomial( y - rr, y );
    //    cout << "q / (y - r') = " << q.quo( ) << endl << endl;

    return 0;
}
