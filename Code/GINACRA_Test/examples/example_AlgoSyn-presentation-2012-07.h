
#include <iostream>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaC;
using namespace GiNaCRA;

int main( int argc, char** argv )
{
    symbol x( "x" );

    // First polynomial and its real roots
    RationalUnivariatePolynomial p1( pow( x, 8 ) - 2, x );
    list<RealAlgebraicNumberPtr> roots = RealAlgebraicNumberFactory::realRoots( p1 );
    cout << p1 << " has " << roots.size() << " real roots:" << endl;
    for( list<RealAlgebraicNumberPtr>::const_iterator i = roots.begin(); i != roots.end(); ++i )
        cout << *i << endl;

    // Approximate value output
    cout << "Approx. values of real roots of " << p1 << ": " << endl;
    for( list<RealAlgebraicNumberPtr>::const_iterator i = roots.begin(); i != roots.end(); ++i )
        cout << (*i)->approximateValue() << endl;
    RealAlgebraicNumberPtr a = roots.front();    // negative
    cout << "a = " << a << endl;
    RealAlgebraicNumberPtr b = roots.back();    // positive
    cout << "b = " << b << endl;
    if( a == -b )
        cout << "Symmetric roots!" << endl;
    cout << endl;

    // Second polynomial and its real roots
    RationalUnivariatePolynomial p2( pow( x, 2 ) - 2, x );
    list<RealAlgebraicNumberPtr> sqrt2s = RealAlgebraicNumberFactory::realRoots( p2 );
    // Evaluation with first polynomial
    cout << "Sign of " << p2 << " at " << "a: " << a->sgn( p2 ) << endl;
    cout << "Sign of " << p2 << " at " << "b: " << b->sgn( p2 ) << endl;
    cout << "Approx. values real roots of " << p2 << ": " << endl;
    for( list<RealAlgebraicNumberPtr>::const_iterator i = sqrt2s.begin(); i != sqrt2s.end(); ++i )
        cout << (*i)->approximateValue() << endl;
    cout << endl;
    return 0;
}
