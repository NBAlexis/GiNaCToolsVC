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


#include "Groebner_unittest.h"
#include "VariableListPool.h"
#include "MultivariateMonomialMR_unittest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( Groebner_unittest );

using namespace GiNaCRA;

Groebner_unittest::Groebner_unittest(){}

void Groebner_unittest::setUp()
{
    std::vector<pui> q1;
    q1.push_back( pui( 1, 1 ));
    q1.push_back( pui( 2, 1 ));
    std::vector<pui> q2;
    q2.push_back( pui( 1, 2 ));
    q2.push_back( pui( 2, 1 ));
    MultivariateMonomialMR a1, xy, a3, a4, x, x2;
    a1 = MultivariateMonomialMR( 1, 3 );
    xy = MultivariateMonomialMR( q1.begin(), q1.end() );
    a3 = MultivariateMonomialMR( q2.begin(), q2.end() );
    a4 = MultivariateMonomialMR( 2, 2 );
    x  = MultivariateMonomialMR( 1, 1 );

    u1 = MultivariateTermMR( a1 );
    u2 = MultivariateTermMR( xy, -2 );
    u3 = MultivariateTermMR( a3 );
    u4 = MultivariateTermMR( a4, -2 );
    u5 = MultivariateTermMR( x );
    std::set<MultivariateTermMR, MonomMRCompare> fs1 = std::set<MultivariateTermMR, MonomMRCompare>( MonomMRCompare() );
    fs1.insert( u1 );
    fs1.insert( u2 );
    f1 = MultivariatePolynomialMR( fs1.begin(), fs1.end(), MonomMRCompare() );

    std::set<MultivariateTermMR, MonomMRCompare> fs2 = std::set<MultivariateTermMR, MonomMRCompare>( MonomMRCompare() );
    fs2.insert( u3 );
    fs2.insert( u4 );
    fs2.insert( u5 );
    f2 = MultivariatePolynomialMR( fs2.begin(), fs2.end(), MonomMRCompare() );

}

void Groebner_unittest::tearDown(){}

void Groebner_unittest::testGroebner()
{
    MonomMRCompare lex   = MonomMRCompare( &MultivariateMonomialMR::LexCompare );
    MonomMRCompare grlex = MonomMRCompare( &MultivariateMonomialMR::GrLexCompare );
    //    MonomMRCompare grrevlex = MonomMRCompare( &MultivariateMonomialMR::GrRevLexCompare );
    symbol x = VariableListPool::getVariableSymbol( 0 );
    symbol y = VariableListPool::getVariableSymbol( 1 );
    symbol z = VariableListPool::getVariableSymbol( 2 );

    std::list<MultivariatePolynomialMR> l;
    l.push_back( f1 );
    l.push_back( f2 );
    Groebner g = Groebner( l.begin(), l.end() );
    g.solve();
    g.reduce();
    //  g.print();
    CPPUNIT_ASSERT( true );

    MultivariatePolynomialMR g1 = MultivariatePolynomialMR( x * z - y * y, grlex );
    MultivariatePolynomialMR g2 = MultivariatePolynomialMR( x * x * x - z * z, grlex );
    Groebner h                  = Groebner( g1, g2 );
    h.solve();
    h.reduce();
    //  h.print();
    CPPUNIT_ASSERT( true );

    MultivariatePolynomialMR g3 = MultivariatePolynomialMR( pow( x, 5 ) + pow( y, 4 ) + pow( z, 3 ) - 1, grlex );
    MultivariatePolynomialMR g4 = MultivariatePolynomialMR( pow( x, 3 ) + pow( y, 2 ) + pow( z, 2 ) - 1, grlex );
    //std::cout << g3 << std::endl;
    //std::cout << g4 << std::endl;
    Groebner h1 = Groebner( g3, g4 );
    h1.solve();
    h1.reduce();
    //  h1.print();
    CPPUNIT_ASSERT( true );

    MultivariatePolynomialMR g5 = MultivariatePolynomialMR( x * x + 2 * x * y * y, lex );
    MultivariatePolynomialMR g6 = MultivariatePolynomialMR( x * y + 2 * pow( y, 3 ) - 1, lex );
    Groebner h2                 = Groebner( g5, g6 );
    h2.solve();
    h2.reduce();
    //  h2.print();
    //    CPPUNIT_ASSERT();

    MultivariatePolynomialMR g7 = MultivariatePolynomialMR( 144 * pow( y, 2 ) + 96 * pow( x, 2 ) * y + 9 * pow( x, 4 ) + 105 * pow( x, 2 ) + 70 * x
                                                            - 98, grlex );
    MultivariatePolynomialMR g8 = MultivariatePolynomialMR( x * pow( y, 2 ) + 6 * x * y + pow( x, 3 ) + 9 * x, grlex );
    Groebner h3                 = Groebner( g7, g8 );
    //    CPPUNIT_ASSERT_EQUAL();
    h3.solve();
    h3.reduce();
    CPPUNIT_ASSERT( h3.hasBeenReduced() );
    //  h3.print();

    MultivariatePolynomialMR g9  = MultivariatePolynomialMR( (x - 1) * (x - 3) * (x - 4) * (x - 6) * (y - 4) * z, grlex );
    MultivariatePolynomialMR g10 = MultivariatePolynomialMR( (x - 2) * (x - 2) * (x - 5) * (x - 8) * (y - 4), grlex );
    MultivariatePolynomialMR g11 = MultivariatePolynomialMR( (x - 7) * (x - 7) * (x - 9) * (x - 10) * z * z * (z - 3), grlex );

    Groebner h4                  = Groebner( g9, g10, g11 );
    CPPUNIT_ASSERT( !h4.hasBeenReduced() );
    h4.solve();
    h4.reduce();
    //h4.print();
    CPPUNIT_ASSERT( h4.hasBeenReduced() );

    MultivariatePolynomialMR g12 = MultivariatePolynomialMR( (x + y + 1), grlex );
    MultivariatePolynomialMR g13 = MultivariatePolynomialMR( (x + z + 1), grlex );
    Groebner h5                  = Groebner( g12, g13 );
    CPPUNIT_ASSERT( !h5.hasBeenReduced() );
    h5.solve();
    h5.reduce();
    //  h5.print();
    CPPUNIT_ASSERT( h5.hasBeenReduced() );

    MultivariatePolynomialMR g14 = MultivariatePolynomialMR( (x - z), grlex );
    MultivariatePolynomialMR g15 = MultivariatePolynomialMR( (y + 1), grlex );
    Groebner h6                  = Groebner( g14, g15 );
    CPPUNIT_ASSERT( !h6.hasBeenReduced() );
    h6.solve();
    h6.reduce();
    CPPUNIT_ASSERT( !h6.hasBeenReduced() );
}
