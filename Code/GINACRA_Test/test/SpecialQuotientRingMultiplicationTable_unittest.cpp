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


// #define GINACRA_MULTIVARIATEPOLYNOMIALTEST_DEBUG

/**
 * Unit tests for the class SpecialQuotientRingMultiplicationTable.
 *
 * @author Ulrich Loup
 * @since 2011-07-12
 * @version 2011-10-25
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

#include "SpecialQuotientRingMultiplicationTable_unittest.h"

// test suite
CPPUNIT_TEST_SUITE_REGISTRATION( SpecialQuotientRingMultiplicationTableTest );

void SpecialQuotientRingMultiplicationTableTest::setUp()
{
#ifdef GINACRA_MULTIVARIATEPOLYNOMIALTEST_DEBUG
    cout << "SpecialQuotientRingMultiplicationTableTest::setUp()" << endl;
#endif
    x = symbol( "x" );
    y = symbol( "y" );
    l = vector<symbol>();
    l.push_back( x );
    l.push_back( y );
    p0 = MultivariatePolynomial<ex_is_less_deggrlex>( ex( 0 ), l );
    p1 = MultivariatePolynomial<ex_is_less_deggrlex>( x * x - y, l );
    p2 = MultivariatePolynomial<ex_is_less_deggrlex>( 2 * x, l );
    p3 = MultivariatePolynomial<ex_is_less_deggrlex>( y - x * x, l );
    p4 = MultivariatePolynomial<ex_is_less_deggrlex>( y * y * y, l );
}

void SpecialQuotientRingMultiplicationTableTest::tearDown(){}

void SpecialQuotientRingMultiplicationTableTest::testConstructor()
{
    list<MultivariatePolynomial<ex_is_less_deggrlex> >          gb = MultivariatePolynomialFactory::synthesizeSpecialGroebnerBasis( p1, 1, EPSILON );
    SpecialQuotientRingMultiplicationTable<ex_is_less_deggrlex> T1 = SpecialQuotientRingMultiplicationTable<ex_is_less_deggrlex>( p1 );
    SpecialQuotientRingMultiplicationTable<ex_is_less_deggrlex> T2 = SpecialQuotientRingMultiplicationTable<ex_is_less_deggrlex>( gb );
    CPPUNIT_ASSERT_EQUAL( T1, T2 );
    // cout << endl;
    // cout << T1 << endl;
    // cout << T2 << endl;
}

void SpecialQuotientRingMultiplicationTableTest::testProduct()
{
    SpecialQuotientRingMultiplicationTable<ex_is_less_deggrlex> T1 = SpecialQuotientRingMultiplicationTable<ex_is_less_deggrlex>( p1 );
    T1.product( 1, 1 );
}

void SpecialQuotientRingMultiplicationTableTest::testTrace()
{
    SpecialQuotientRingMultiplicationTable<ex_is_less_deggrlex> T1 = SpecialQuotientRingMultiplicationTable<ex_is_less_deggrlex>( p1 );
    // compare trace to naive trace computation
    // MultivariatePolynomial<ex_is_less_deggrlex> p = MultivariatePolynomialFactory::generalPositionTemplate<ex_is_less_deggrlex>(l, 4, 1);

    // vector< MultivariateTerm<ex_is_less_deggrlex> > basis = T1.TermsUnderTheStaircase();
    // list< MultivariatePolynomial<ex_is_less_deggrlex> > groebnerBasis = T1.GroebnerBasis();
    // ex trace_naive = ex(0);
    // int i = 0;
    // for( typename vector< MultivariateTerm<ex_is_less_deggrlex> >::const_iterator m1 = basis.begin(); m1 != basis.end(); ++m1 )
    // {
    //  MultivariatePolynomial<ex_is_less_deggrlex> nf = (p * *m1).normalForm(groebnerBasis);
    //  int j = 0;
    //  for( typename vector< MultivariateTerm<ex_is_less_deggrlex> >::const_iterator m2 = basis.begin(); m2 != basis.end(); ++m2 )
    //  {
    //      if( nf.lmon() == m2->lmon() )
    //      {
    //          if( i == j ) // only add diagonal entries
    //          {   
    //              ex lcoeff = ex(1);
    //              divide(nf.lcoeff(), m2->lcoeff(), lcoeff);
    //              if( !divide(nf.lcoeff(), m2->lcoeff(), lcoeff) )
    //                  throw invalid_argument("SpecialQuotientRingMultiplicationTableTest::testTrace: Conceptional error: products of basis elements cannot be expressed by linear combinations of basis elements.");
    //              trace_naive += lcoeff;
    //          }
    //          nf.trunc();
    //      }
    //      if( nf.isZero() )
    //          break;
    //      ++j;
    //  }
    //  ++i;
    // }
    // CPPUNIT_ASSERT_EQUAL( static_cast<ex>(T1.trace(p1)), trace_naive );
    // for(int e = 1; e != 10; e++)
    //  for(int i = 1; i != 10; i++)
    //      cout << "Trace: " << T1.generalPositionTemplatePowerTrace(i, e) << endl;
    //  cout << "Trace: " << T1.trace(p1) << endl;
    //  cout << "Trace: " << T1.trace(p2) << endl;
    //  cout << "Trace: " << T1.trace(p3) << endl;
    //  cout << "Trace: " << T1.trace(p4) << endl;
}
