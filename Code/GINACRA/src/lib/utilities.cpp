#include "ginacra_private.h"
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
 * Implementation of utilities.h.
 *
 * @author Ulrich Loup
 * @since 2010-11-01
 * @version 2012-05-14
 *
 */

#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

#include "utilities.h"

namespace GiNaC
{
    const ex prod( const lst& l ) throw ( invalid_argument )
    {
        lst::const_iterator i = l.begin();
        ex prod = *i;    // invariant: prod is the product of the elements of l traversed so far
        ++i;
        for( ; i != l.end(); ++i )
            prod *= *i;
        return prod;
    }

    const ex lcm( const lst& l ) throw ( invalid_argument )
    {
        lst::const_iterator i = l.begin();
        ex currentLcm = *i;    // invariant: currentLcm is the lcm of the elements of l traversed so far
        ++i;
        for( ; i != l.end(); ++i )
            currentLcm = lcm( currentLcm, *i );
        return currentLcm;
    }

    long lcm( long a, long b )
    {
        long temp = gcd( a, b );
        return temp ? (a / temp * b) : 0;
    }

    long gcd( long a, long b )
    {
        assert( a != 0 );
        while( true )
        {
            a = a % b;
            if( a == 0 )
                return b;
            b = b % a;
            if( b == 0 )
                return a;
        }
    }

    long numerator( long a, long b )
    {
        return a / gcd( a, b );
    }

    long denominator( long a, long b )
    {
        return b / gcd( a, b );
    }

    bool is_constant( const ex& polynomial, const vector<symbol>& symbolLst )
    {
        for( vector<symbol>::const_iterator it = symbolLst.begin(); it != symbolLst.end(); ++it )
            if( polynomial.degree( *it ) != 0 )
                return false;
        return true;
    }

    bool is_rational_polynomial( const ex& p, const symbol& x )
    {
        for( int i = p.ldegree( x ); i <= p.degree( x ); ++i )
        {
            ex c = p.coeff( x, i );
            if( !(is_exactly_a<numeric>( c ) && ex_to<numeric>( c ).is_rational()))
                return false;
        }
        if( !p.info( info_flags::rational_polynomial ))
            return false;
        return true;
    }

    bool is_realalgebraic_polynomial( const ex& p, const symbol& x )
    {
        for( int i = p.ldegree( x ); i <= p.degree( x ); ++i )
        {
            if( !is_realalgebraic_term( p.coeff( x, i )))
                return false;
        }
        return true;
    }

    bool is_realalgebraic_term( const ex& p )
    {
        if( p.info( GiNaC::info_flags::numeric )
         && (p.info( GiNaC::info_flags::rational ) 
         || (p.info( GiNaC::info_flags::real ) 
             //&& p.info( GiNaC::info_flags::algebraic ) //Attention HERE!!
             )))
        {
            return true;
        }
        else if( GiNaC::is_exactly_a<GiNaC::power>( p ))
        {
            if( !is_realalgebraic_term( *p.begin() ))
                return false;
            return true;
        }
        else if( GiNaC::is_exactly_a<GiNaC::add>( p ) || GiNaC::is_exactly_a<GiNaC::mul>( p ) || GiNaC::is_exactly_a<GiNaC::ncmul>( p )
                 || GiNaC::is_exactly_a<GiNaC::pseries>( p ))
        {
            for( const_iterator i = p.begin(); i != p.end(); ++i )
                if( !is_realalgebraic_term( *i ))
                    return false;
            return true;
        }
        return false;
    }

    sign sgn( const numeric& n )
    {
        return n == 0 ? ZERO_SIGN : n > 0 ? POSITIVE_SIGN : NEGATIVE_SIGN;
    }

    const ex monpart( const ex& polynomial, const vector<symbol>& symbolLst )
    {
        ex coefficient = ex( 1 );
        ex monomial    = ex( 1 );
        isolateByVariables( polynomial, symbolLst, coefficient, monomial );
        return monomial;
    }

    const ex coeffpart( const ex& polynomial, const vector<symbol>& symbolLst )
    {
        ex coefficient = ex( 1 );
        ex monomial    = ex( 1 );
        isolateByVariables( polynomial, symbolLst, coefficient, monomial );
        return coefficient;
    }

    void isolateByVariables( const ex& polynomial, const vector<symbol>& symbolLst, ex& coefficient, ex& monomial )
    {
        coefficient = ex( 1 );
        monomial    = ex( 1 );

        // isolate monomial and coefficient in case polynomial has only one term

        if( is_constant( polynomial, symbolLst ))
        {    // polynomial is constant in the current list of variables, so is a coefficient with the 1 monomial
            coefficient = polynomial;
        }
        else if( is_exactly_a<GiNaC::mul>( polynomial ))    // GiNaC::mul because of overriding the name "mul" by the current function
        {    // polynomial is just a product
            for( const_iterator j = polynomial.begin(); j != polynomial.end(); ++j )    // iterate through the possible powers
            {
                vector<symbol>::const_iterator s = symbolLst.begin();
                for( ; s != symbolLst.end(); ++s )    // only take symbols given in the list (all other things are coefficient)
                {
                    if( j->degree( *s ) > 0 )
                    {
                        monomial = monomial * *j;
                        break;
                    }
                }
                if( s == symbolLst.end() )    // current power is not build upon a variable, so it belongs to the coefficient
                    coefficient = coefficient * *j;
            }
        }
        else if( GiNaC::is_exactly_a<GiNaC::power>( polynomial ) || GiNaC::is_exactly_a<GiNaC::symbol>( polynomial ))
        {
            vector<symbol>::const_iterator s = symbolLst.begin();
            for( ; s != symbolLst.end(); ++s )    // only take symbols given in the list (all other things are coefficient)
            {
                if( polynomial.degree( *s ) > 0 )
                {
                    monomial = polynomial;
                    return;
                }
            }
            coefficient = polynomial;
        }
        else if( is_exactly_a<numeric>( polynomial ))
            coefficient = polynomial;
        else if( polynomial.is_zero() )
            coefficient = ex( 0 );
        // in all other cases, the polynomial has several terms
    }

    const GiNaC::ex rationalize( const GiNaC::ex& p, const vector<GiNaC::symbol>& symbolLst )
    {
        GiNaC::ex pExpanded = p.expand();
        if( GiNaC::is_exactly_a<GiNaC::add>( pExpanded ))
        {
            GiNaC::ex pRational;
            for( GiNaC::const_iterator i = p.begin(); i != p.end(); ++i )    // iterate through the summands
                pRational += rationalize( *i, symbolLst );
            return pRational;
        }
        GiNaC::ex coefficient = ex( 1 );
        GiNaC::ex monomial    = ex( 1 );
        isolateByVariables( p, symbolLst, coefficient, monomial );
        assert( GiNaC::is_exactly_a<GiNaC::numeric>( coefficient ));
        GiNaC::numeric coefficientNum = GiNaC::ex_to<numeric>( coefficient );
        if( !coefficientNum.is_rational() )
            return rationalize( coefficientNum ) * monomial;
        return coefficientNum * monomial;
    }

    const GiNaC::ex rationalize( const GiNaC::ex& p, const GiNaC::symbol& s )
    {
        return rationalize( p, vector<GiNaC::symbol>( 1, s ));
    }

    const GiNaC::numeric rationalize( const GiNaC::numeric& n )
    {
        return numeric( cln::rationalize( n.to_double() ));
    }

    const vector<symbol> sortVariables( const vector<symbol>& l )
    {
        vector<symbol> newL = vector<symbol>( l.begin(), l.end() );
        sort( newL.begin(), newL.end(), symbol_is_less_lex );
        return newL;
    }

    bool symbol_is_lesseq_lex( const symbol& a, const symbol& b )
    {
        stringstream sA, sB;
        sA << a;
        sB << b;
        return sA.str().compare( sB.str() ) <= 0;
    }

    bool symbol_is_less_lex( const symbol& a, const symbol& b )
    {
        stringstream sA, sB;
        sA << a;
        sB << b;
        return sA.str().compare( sB.str() ) <= 0;
    }

    const map<int, ex> signedSubresultants( const ex& A, const ex& B, const symbol& sym )
    {
        ex P      = A;
        ex Q      = B;
        ex ex_sym = sym;    // avoid complicated casts like symbol -> ex
        int p = P.degree( ex_sym );
        int q = Q.degree( ex_sym );
        ex a             = P.lcoeff( ex_sym );    // leading coefficient of P
        ex b             = Q.lcoeff( ex_sym );    // leading coefficient of Q
        ex epsilon_p_q_1 = pow( (-1), (p - q - 1) * (p - q - 1 + 1) / 2 );

        int          j, k;
        map<int, ex> H;
        map<int, ex> h;
        map<int, ex> h_;

        if( p > q )
        {
            j        = q;
            h[q]     = epsilon_p_q_1 * pow( b, p - q );
            H[q]     = epsilon_p_q_1 * pow( b, p - q - 1 ) * Q;
            H[q - 1] = -rem( b * h[q] * P, Q, ex_sym, false );
        }

        else if( p == q )
        {
            j        = q;
            h[q]     = 1;
            H[q - 1] = -rem( b * P, Q, ex_sym );
        }

        else    // p < q
        {
            j        = p;
            h[p]     = pow( a, q - p );
            H[p]     = pow( a, q - p - 1 ) * P;
            H[p - 1] = -rem( a * h[p] * Q, P, ex_sym, false );
        }

        map<int, ex>::const_iterator itti = H.find( j - 1 );
        if( itti != H.end() && H[j - 1] == 0 )
            return H;
        else
        {
            k = H[j - 1].degree( ex_sym );
            while( true )
            {
                if( k == j - 1 )
                {
                    // The following line is missing in the paper
                    // but the algorithm is not working
                    // without it. If it is missing
                    // h[j-1] is just initialized with 0.
                    // See the definition of h on page 5 in the paper !
                    h[j - 1] = H[j - 1].lcoeff( ex_sym );
                    //H[k-1] = -rem(pow(h[j-1], 2) * H[j], H[j-1], ex_sym, false) / pow(h[j], 2);
                    if( !divide( -rem( pow( h[j - 1], 2 ) * H[j], H[j - 1], ex_sym, false ), pow( h[j], 2 ), H[k - 1] ))
                        assert( false == true );    // Division Error!

                    if( p == q && q == j )
                    {
                        //H[q-2] = -rem(pow(h[q-1], 2) * Q, H[q-1], ex_sym, false) / b;
                        if( !divide( -rem( pow( h[q - 1], 2 ) * Q, H[q - 1], ex_sym, false ), b, H[q - 2] ))
                            assert( false == true );    // Division Error!
                    }
                }

                if( k < j - 1 )
                {
                    h_[j - 1] = H[j - 1].lcoeff( ex_sym );

                    for( int delta = 1; delta <= j - k - 1; delta++ )
                    {
                        //h_[j-delta-1] = pow(-1, delta) * (h_[j-1] * h_[j-delta]) / h[j];
                        if( !divide( pow( -1, delta ) * (h_[j - 1] * h_[j - delta]), h[j], h_[j - delta - 1] ))
                            assert( false == true );    // Division Error!
                    }

                    h[k] = h_[k];

                    //H[k] = (h[k] * H[j-1])/h_[j-1];
                    if( !divide( (h[k] * H[j - 1]), h_[j - 1], H[k] ))
                        assert( false == true );    // Division Error!

                    //H[k-1] = -rem(h_[j-1] * h[k] * H[j], H[j-1], ex_sym, false) / pow(h[j], 2);
                    if( !divide( -rem( h_[j - 1] * h[k] * H[j], H[j - 1], ex_sym, false ), pow( h[j], 2 ), H[k - 1] ))
                        assert( false == true );    // Division Error!

                    if( p == q && q == j )
                    {
                        //H[k-1] = -rem(h_[q-1] * h[k] * Q, H[j-1], ex_sym, false) / b;
                        if( !divide( -rem( h_[q - 1] * h[k] * Q, H[j - 1], ex_sym, false ), b, H[k - 1] ))
                            assert( false == true );    // Division Error!
                    }
                }

                itti = H.find( k - 1 );

                if( itti != H.end() && H[k - 1] == 0 )
                    return H;

                else
                {
                    j = k;
                    k = H[k - 1].degree( ex_sym );
                }
            }
        }

        return H;
    }

    const vector<ex> signedSubresultantsCoefficients( const ex& A, const ex& B, const symbol& sym ) throw ( invalid_argument )
    {
        ex ex_x = sym;
        int a = A.degree( ex_x );
        // may if (a < b && a != 0 && b != 0) ??
        //if( a <= b )    // VERY DANGEROUS USE !!
        //    throw invalid_argument( "The degree of A must be greater than the degree of B!" );
        //else
        //{
        map<int, ex> H = signedSubresultants( A, B, sym );
        vector<ex>   sRes( a + 1 );
        for( int i = 0; i < a; i++ )
            sRes[i] = ex( H[i].coeff( ex_x, i ));
        sRes[a] = ex( A.coeff( ex_x, a ));
        return sRes;
        //}
    }

}    // namespace GiNaC

