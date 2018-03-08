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


// #define GINACRA_UNIVARIATEPOLYNOMIAL_DEBUG

/**
 * Implementation of the class UnivariatePolynomial.
 *
 * @author Ulrich Loup
 * @since 2010-08-03
 * @version 2012-04-19
 * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
 */

#include <assert.h>
//
//#include "UnivariatePolynomial.h"
//#include "operators.h"
//#include "RealAlgebraicNumberIR.h"

using GiNaC::ex;
using GiNaC::is_exactly_a;

namespace GiNaCRA
{
    //////////////////////////
    // Con- and destructors //
    //////////////////////////

    UnivariatePolynomial::UnivariatePolynomial( const ex& p, const symbol& s, bool enableCheck ) throw ( invalid_argument ):
        Polynomial( p.expand().collect( s )),
        mVariable( s ),
        mEnabledPolynomialCheck( enableCheck )
    {
        if( enableCheck &&!this->is_polynomial( s ))
            throw invalid_argument( "Specified expression is no polynomial in the given variable." );
    }

    /////////////////////
    // Methods from ex //
    /////////////////////

    void UnivariatePolynomial::do_print( const print_context& c, unsigned level ) const
    {
        c.s << static_cast<ex>(*this) << '(' << mVariable << ')';
    }

    ///////////////
    // Operators //
    ///////////////

    // assignment operators

    const UnivariatePolynomial& UnivariatePolynomial::operator = ( const UnivariatePolynomial& o )
    {
        ex::operator = ( o );
        mVariable               = o.mVariable;
        mEnabledPolynomialCheck = o.mEnabledPolynomialCheck;
        return *this;
    }

    const UnivariatePolynomial& UnivariatePolynomial::operator = ( const ex& o )
    {
        ex oNorm = ex( o );
        ex::operator = ( oNorm );
        // convention: new polynomial has current main variable
        return *this;
    }

    ////////////////
    // Operations //
    ////////////////

    UnivariatePolynomial UnivariatePolynomial::trunc() const
    {
        ex e    = *this;
        ex ex_s = this->variable();
        if( e.degree( ex_s ) == 0 )
            return *this;
        else
            return UnivariatePolynomial( e - e.lcoeff( ex_s ) * pow( this->variable(), e.degree( ex_s )), this->variable(), mEnabledPolynomialCheck );
    }

    UnivariatePolynomial UnivariatePolynomial::sepapart() const
    {
        if( isConstant() )    // prevent division by zero
            return UnivariatePolynomial( 0, mVariable );
        // @see Lemma 10.13 in ISBN 0-387-94090-1
        return UnivariatePolynomial( this->quo( this->gcd( this->diff().primpart() )), mVariable, mEnabledPolynomialCheck ).primpart();
    }

    UnivariatePolynomial UnivariatePolynomial::nonzeropart() const
    {
        int l = ldegree();
        symbol variable = mVariable;
        ex result       = coeff( l );
        for( int d = l + 1; d <= degree(); ++d )
            result += coeff( d ) * pow( variable, d - l );
        return UnivariatePolynomial( result, variable );
    }

    ///////////////////////////
    // Arithmetic Operations //
    ///////////////////////////

    const list<UnivariatePolynomial> UnivariatePolynomial::subresultants( const UnivariatePolynomial& p,
                                                                          const UnivariatePolynomial& q,
                                                                          const subresultantStrategy strategy )
    {
        // INIT: Check and normalize input, initialize local variables
        if( !p.isCompatible( q ))
            throw invalid_argument( "Symbols of the two univariate polynomials do not match." );
        std::list<UnivariatePolynomial> subresultants = std::list<UnivariatePolynomial>();    // the desired list of subresultants
        symbol variable = p.mVariable;

        UnivariatePolynomial a, b;    // a shall receive the smaller-degree polynomial
        if( p.degree() < q.degree() )
        {
            a = q;
            b = p;
        }
        else
        {
            a = p;
            b = q;
        }

        // aDeg >= bDeg shall hold, so switch in case it does not hold
        if( b.isZero() )
            return list<UnivariatePolynomial>( 1, a );
        // initiate with input polynomials
        subresultants.push_front( a );
        subresultants.push_front( b );
        //            if( aDeg < 2 )
        //                return subresultants;
        UnivariatePolynomial tmp = UnivariatePolynomial( b );    // the smaller degree
        b                        = UnivariatePolynomial( GiNaC::prem( a, -b, variable, false ), variable, false );
        a                        = tmp;

        int aDeg = a.degree();
        int bDeg = b.degree();
        ex subresLcoeff = GiNaC::pow( a.lcoeff(), aDeg - bDeg );    // initialized on the basis of the smaller-degree polynomial

        // MAIN: start main loop containing different computation strategies
        while( true )
        {
            if( b.isZero() )
                return subresultants;
            aDeg = a.degree();
            bDeg = b.degree();
            subresultants.push_front( b );
            int delta = aDeg - bDeg;
            UnivariatePolynomial c = b;
            if( delta > 1 )
            {    // compute c
                switch( strategy )
                {
                    case GENERIC_SUBRESULTANTSTRATEGY:
                    {
                        ex reductionCoeff;
                        GiNaC::divide( GiNaC::pow( b.lcoeff(), delta - 1 ), GiNaC::pow( subresLcoeff, delta - 1 ), reductionCoeff, false );
                        c = UnivariatePolynomial( reductionCoeff * b, variable, false );
                        break;
                    }
                    case LAZARDS_SUBRESULTANTSTRATEGY:
                        /// @todo implement using page 151 of the above mentioned article
                        break;
                    case DUCOS_SUBRESULTANTSTRATEGY:
                        /// @todo implement using page 154 of the above mentioned article
                        break;
                }
                subresultants.push_front( c );
            }
            // else: c == b
            if( bDeg == 0 )
                return subresultants;
            switch( strategy )
            {
                case GENERIC_SUBRESULTANTSTRATEGY:
                {
                    ex reducedNewB;
                    GiNaC::divide( GiNaC::prem( a, -b, variable, false ), GiNaC::pow( subresLcoeff, delta ) * a.lcoeff(), reducedNewB, false );
                    b = UnivariatePolynomial( reducedNewB, variable, false );
                    break;
                }
                case LAZARDS_SUBRESULTANTSTRATEGY:
                    /// @todo implement using page 151 of the above mentioned article
                    break;
                case DUCOS_SUBRESULTANTSTRATEGY:
                    /// @todo implement using page 154 of the above mentioned article
                    break;
            }
            a            = c;
            subresLcoeff = a.lcoeff();
        }
    }

    const vector<ex> UnivariatePolynomial::subresultantCoefficients( const UnivariatePolynomial& a,
                                                                     const UnivariatePolynomial& b,
                                                                     const subresultantStrategy strategy )
    {
        list<UnivariatePolynomial> subres       = UnivariatePolynomial::subresultants( a, b, strategy );
        vector<ex>                 subresCoeffs = vector<ex>();
        for( list<UnivariatePolynomial>::const_iterator s = subres.begin(); s != subres.end(); ++s )
            subresCoeffs.push_back( s->lcoeff() );
        return subresCoeffs;
    }

    const vector<ex> UnivariatePolynomial::principalSubresultantCoefficients( const UnivariatePolynomial& a,
                                                                              const UnivariatePolynomial& b,
                                                                              const subresultantStrategy strategy )
    {
        list<UnivariatePolynomial> subres       = UnivariatePolynomial::subresultants( a, b, strategy );
        vector<ex>                 subresCoeffs = vector<ex>( subres.size() );
        int                        i            = 0;
        for( list<UnivariatePolynomial>::const_iterator s = subres.begin(); s != subres.end(); ++s )
        {
            if( s->degree() < i )
                break;    // this and all further subresultants won't have a non-zero i-th coefficient
            subresCoeffs[i] = s->coeff( i );
            ++i;
        }
        subresCoeffs.resize( i );
        return subresCoeffs;
    }

    ///////////////////////////
    // Relational Operations //
    ///////////////////////////

    ////////////////////
    // Static Methods //
    ////////////////////

    list<UnivariatePolynomial> UnivariatePolynomial::standardSturmSequence( const UnivariatePolynomial& a,
                                                                            const UnivariatePolynomial& b )
            throw ( invalid_argument )
    {
        if( !a.isCompatible( b ))
            throw invalid_argument( "Symbols of the two univariate polynomials do not match." );
        list<UnivariatePolynomial> seq = list<UnivariatePolynomial>();    // Sturm sequence to compute
        ex p            = a, q = b;
        symbol variable = a.mVariable;
        seq.push_back( a );
        while( !q.is_zero() )
        {
            seq.push_back( UnivariatePolynomial( q, variable ));
            q = -(GiNaC::rem( p, q, variable ));
            p = seq.back();
        }
        return seq;
    }

    bool UnivariatePolynomial::univariatePolynomialIsLess( const UnivariatePolynomial& a, const UnivariatePolynomial& b )
    {
        return !a.isEqual( b ) && a.compare( b ) < 0;
    }

    bool UnivariatePolynomial::univariatePolynomialIsLessLowDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b )
    {
        return a.degree() < b.degree() || (a.degree() == b.degree() && univariatePolynomialIsLess( a, b ));
    }

    bool UnivariatePolynomial::univariatePolynomialIsLessOddDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b )
    {
        return GiNaC::is_odd( a.degree() ) || (a.degree() == b.degree() && univariatePolynomialIsLess( a, b ));
        GiNaC::is_odd( a.degree() ) || a.compare( b ) < 0;
    }

    bool UnivariatePolynomial::univariatePolynomialIsLessOddLowDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b )
    {
        return (a.degree() < b.degree() && GiNaC::is_odd( a.degree() )) || (a.degree() == b.degree() && univariatePolynomialIsLess( a, b ));
        GiNaC::is_odd( a.degree() ) || a.compare( b ) < 0;
    }

    bool UnivariatePolynomial::univariatePolynomialIsLessEvenDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b )
    {
        return GiNaC::is_even( a.degree() ) || (a.degree() == b.degree() && univariatePolynomialIsLess( a, b ));
    }

    bool UnivariatePolynomial::univariatePolynomialIsLessEvenLowDeg( const UnivariatePolynomial& a, const UnivariatePolynomial& b )
    {
        return (a.degree() < b.degree() && GiNaC::is_even( a.degree() )) || (a.degree() == b.degree() && univariatePolynomialIsLess( a, b ));
    }
}    // namespace GiNaC

