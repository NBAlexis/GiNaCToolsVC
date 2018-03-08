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
 * @file operators.cpp
 *
 * Collection of some operators for classes derived from ex.
 *
 * @author Ulrich Loup
 * @since 2010-09-20
 * @version 2012-04-20
 */

#include <assert.h>
//
//#include "OpenInterval.h"
//#include "RealAlgebraicNumber.h"
//#include "RealAlgebraicNumberIR.h"
//#include "RealAlgebraicNumberNR.h"
//#include "RealAlgebraicNumberFactory.h"
//#include "UnivariatePolynomial.h"
//#include "UnivariatePolynomialSet.h"
//#include "Constraint.h"

using GiNaC::ex_to;
using GiNaC::is_exactly_a;
using GiNaC::ZERO_SIGN;
using GiNaC::POSITIVE_SIGN;
using GiNaC::NEGATIVE_SIGN;

namespace GiNaCRA
{
    ////////////
    // Common //
    ////////////

    const GiNaC::numeric abs( const ex& lh )
    {
        if( GiNaC::is_exactly_a<numeric>( lh ))
            return GiNaC::abs( ex_to<numeric>( lh ));
        if( GiNaC::is_a<RealAlgebraicNumberIR>( lh ))
            return std::max<GiNaC::numeric>( GiNaC::abs( GiNaC::ex_to<RealAlgebraicNumberIR>( lh ).interval().left() ),
                                        GiNaC::abs( GiNaC::ex_to<RealAlgebraicNumberIR>( lh ).interval().right() ));
        return 0;
    }

    //////////////////
    // OpenInterval //
    //////////////////

    // binary arithmetic operators of OpenInterval

    const OpenInterval operator +( const OpenInterval& lh, const OpenInterval& rh )
    {
        return lh.add( rh );
    }

    const OpenInterval operator -( const OpenInterval& lh, const OpenInterval& rh )
    {
        return lh.add( rh.minus() );
    }

    const OpenInterval operator *( const OpenInterval& lh, const OpenInterval& rh )
    {
        return lh.mul( rh );
    }

    // unary arithmetic operators of OpenInterval

    const OpenInterval operator -( const OpenInterval& lh )
    {
        return lh.minus();
    }

    // relational operators

    const bool operator ==( const OpenInterval& lh, const OpenInterval& rh )
    {
        return lh.isEqual( rh );
    }

    const bool operator !=( const OpenInterval& lh, const OpenInterval& rh )
    {
        return !lh.isEqual( rh );
    }

    const bool operator <=( const OpenInterval& lh, const OpenInterval& rh )
    {
        return lh.isLess( rh );
    }

    const bool operator >=( const OpenInterval& lh, const OpenInterval& rh )
    {
        return lh.isGreater( rh );
    }

    // mixed arithmetic operators

    const OpenInterval operator +( const OpenInterval& lh, const GiNaC::numeric& rh )
    {
        return OpenInterval( lh.left() + rh, lh.right() + rh );
    }

    const OpenInterval operator +( const GiNaC::numeric& lh, const OpenInterval& rh )
    {
        return OpenInterval( rh.left() + lh, rh.right() + lh );
    }

    const OpenInterval operator -( const OpenInterval& lh, const GiNaC::numeric& rh )
    {
        return lh + (-rh);
    }

    const OpenInterval operator -( const GiNaC::numeric& lh, const OpenInterval& rh )
    {
        return (-lh) + rh;
    }

    const OpenInterval operator *( const OpenInterval& lh, const GiNaC::numeric& rh )
    {
        numeric l   = lh.left() * rh;
        numeric r   = lh.right() * rh;
        numeric min = std::min<numeric>( l, r );
        numeric max = std::max<numeric>( l, r );
        return OpenInterval( min, max );
    }

    const OpenInterval operator *( const GiNaC::numeric& lh, const OpenInterval& rh )
    {
        return rh * lh;
    }

    const OpenInterval operator /( const OpenInterval& lh, const GiNaC::numeric& rh ) throw ( overflow_error )
    {
        if( rh == 0 )
            throw (overflow_error( "Division by interval containing zero not allowed." ));
        numeric l   = lh.left() / rh;
        numeric r   = lh.right() / rh;
        numeric min = std::min<numeric>( l, r );
        numeric max = std::max<numeric>( l, r );
        return OpenInterval( min, max );
    }

    const OpenInterval operator /( const GiNaC::numeric& lh, const OpenInterval& rh ) throw ( overflow_error )
    {
        if( rh.contains( 0 ))
            throw (overflow_error( "Division by interval containing zero not allowed." ));
        numeric l   = lh / rh.left();
        numeric r   = lh / rh.right();
        numeric min = std::min<numeric>( l, r );
        numeric max = std::max<numeric>( l, r );
        return OpenInterval( min, max );
    }

    //////////////////////////
    // UnivariatePolynomial //
    //////////////////////////

    // binary arithmetic operators of UnivariatePolynomial

    const UnivariatePolynomial operator +( const UnivariatePolynomial& lh, const UnivariatePolynomial& rh )
    {
        return lh.add( rh );
    }

    const UnivariatePolynomial operator -( const UnivariatePolynomial& lh, const UnivariatePolynomial& rh )
    {
        return lh.sub( rh );
    }

    const UnivariatePolynomial operator *( const UnivariatePolynomial& lh, const UnivariatePolynomial& rh )
    {
        return lh.mul( rh );
    }

    const UnivariatePolynomial operator /( const UnivariatePolynomial& lh, const UnivariatePolynomial& rh )
    {
        return lh.quo( rh );
    }

    const UnivariatePolynomial operator %( const UnivariatePolynomial& lh, const UnivariatePolynomial& rh )
    {
        return lh.rem( rh );
    }

    // binary arithmetic operators of RationalUnivariatePolynomial

    const RationalUnivariatePolynomial operator +( const RationalUnivariatePolynomial& lh, const RationalUnivariatePolynomial& rh )
    {
        return RationalUnivariatePolynomial( static_cast<ex>(lh)+static_cast<ex>(rh), lh.variable() );
    }

    const RationalUnivariatePolynomial operator -( const RationalUnivariatePolynomial& lh, const RationalUnivariatePolynomial& rh )
    {
        return RationalUnivariatePolynomial( static_cast<ex>(lh)-static_cast<ex>(rh), lh.variable() );
    }

    const RationalUnivariatePolynomial operator *( const RationalUnivariatePolynomial& lh, const RationalUnivariatePolynomial& rh )
    {
        return RationalUnivariatePolynomial( static_cast<ex>(lh)*static_cast<ex>(rh), lh.variable() );
    }

    const RationalUnivariatePolynomial operator /( const RationalUnivariatePolynomial& lh, const RationalUnivariatePolynomial& rh )
    {
        return lh.quo( rh );
    }

    const RationalUnivariatePolynomial operator %( const RationalUnivariatePolynomial& lh, const RationalUnivariatePolynomial& rh )
    {
        return lh.rem( rh );
        //    return RationalUnivariatePolynomial( GiNaC::rem( *this, o, mVariable ), mVariable );
    }

    // unary arithmetic operators of UnivariatePolynomial

    const UnivariatePolynomial operator -( const UnivariatePolynomial& lh )
    {
        return UnivariatePolynomial( -static_cast<ex>(lh), lh.variable(), lh.enabledPolynomialCheck() );
    }

    const RationalUnivariatePolynomial operator -( const RationalUnivariatePolynomial& lh )
    {
        return RationalUnivariatePolynomial( -static_cast<ex>(lh), lh.variable() );
    }

    // relational operators of UnivariatePolynomial

    const bool operator ==( const UnivariatePolynomial& lh, const UnivariatePolynomial& rh )
    {
        return lh.isEqual( rh );
    }

    const bool operator !=( const UnivariatePolynomial& lh, const UnivariatePolynomial& rh )
    {
        return !lh.isEqual( rh );
    }

    /////////////////////////////
    // UnivariatePolynomialSet //
    /////////////////////////////

    std::ostream& operator <<( std::ostream& os, const UnivariatePolynomialSet& s )
    {
        os << "{";
        for( UnivariatePolynomialSet::const_iterator i = s.begin(); i != s.end(); ++i )
            os << " " << static_cast<UnivariatePolynomial>(*i);
        os << " }";
        return os;
    }

    ///////////////////////////
    // RealAlgebraicNumberIR //
    ///////////////////////////

    // binary arithmetic operators

    RealAlgebraicNumberIR& operator +( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        return lh.add( rh );
    }

    RealAlgebraicNumberIR& operator -( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        RealAlgebraicNumberIR rhMinus = rh.minus();
        return lh.add( rhMinus );
    }

    RealAlgebraicNumberIR& operator *( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        return lh.mul( rh );
    }

    RealAlgebraicNumberIR& operator /( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        RealAlgebraicNumberIR rhInverse = rh.inverse();
        return lh.mul( rhInverse );
    }

    RealAlgebraicNumberIR& operator ^( RealAlgebraicNumberIR& base, int exponent )
    {
        return base.pow( exponent );
    }

    // unary arithmetic operators

    RealAlgebraicNumberIR& operator -( RealAlgebraicNumberIR& lh )
    {
        return lh.minus();
    }

    // relational operators

    const bool operator ==( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        return lh.isEqual( rh );
    }

    const bool operator ==( const RealAlgebraicNumberIR& lh, const RealAlgebraicNumberIR& rh )
    {
        RealAlgebraicNumberIR lhRef = lh;
        RealAlgebraicNumberIR rhRef = rh;
        return lhRef.isEqual( rhRef );
    }

    const bool operator !=( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        return !lh.isEqual( rh );
    }

    const bool operator <( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        return lh.isLess( rh );
    }

    const bool operator >( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        return !lh.isEqual( rh ) &&!lh.isLessWhileUnequal( rh );
    }

    const bool operator <=( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        return lh.isEqual( rh ) || lh.isLessWhileUnequal( rh );
    }

    const bool operator >=( RealAlgebraicNumberIR& lh, RealAlgebraicNumberIR& rh )
    {
        return !lh.isLess( rh );
    }

    // mixed arithmetic operators

    RealAlgebraicNumberIR& operator +( const GiNaC::numeric& lh, RealAlgebraicNumberIR& rh )
    {
        RationalUnivariatePolynomial p( rh.polynomial().subs( rh.polynomial().variable() == (rh.polynomial().variable() - lh) ),
                                        rh.polynomial().variable() );
        while( RationalUnivariatePolynomial::countRealRoots( p, rh.interval() + lh ) != 1 )    // refine rh until a unique number representation is found
            rh.refine();
        return *new RealAlgebraicNumberIR( p, rh.interval() + lh );
    }

    RealAlgebraicNumberIR& operator +( RealAlgebraicNumberIR& lh, const GiNaC::numeric& rh )
    {
        RationalUnivariatePolynomial p( lh.polynomial().subs( lh.polynomial().variable() == (lh.polynomial().variable() - rh) ),
                                        lh.polynomial().variable() );
        while( RationalUnivariatePolynomial::countRealRoots( p, rh + lh.interval() ) != 1 )    // refine rh until a unique number representation is found
            lh.refine();
        return *new RealAlgebraicNumberIR( p, rh + lh.interval() );
    }

    RealAlgebraicNumberIR& operator -( const GiNaC::numeric& lh, RealAlgebraicNumberIR& rh )
    {
        RationalUnivariatePolynomial p( rh.polynomial().subs( rh.polynomial().variable() == (rh.polynomial().variable() + lh) ),
                                        rh.polynomial().variable() );
        while( RationalUnivariatePolynomial::countRealRoots( p, rh.interval() - lh ) != 1 )    // refine rh until a unique number representation is found
            rh.refine();
        return *new RealAlgebraicNumberIR( p, rh.interval() - lh );
    }

    RealAlgebraicNumberIR& operator -( RealAlgebraicNumberIR& lh, const GiNaC::numeric& rh )
    {
        RationalUnivariatePolynomial p( lh.polynomial().subs( lh.polynomial().variable() == (lh.polynomial().variable() + rh) ),
                                        lh.polynomial().variable() );
        while( RationalUnivariatePolynomial::countRealRoots( p, rh - lh.interval() ) != 1 )    // refine rh until a unique number representation is found
            lh.refine();
        return *new RealAlgebraicNumberIR( p, rh - lh.interval() );
    }

    RealAlgebraicNumberIR& operator *( const GiNaC::numeric& lh, RealAlgebraicNumberIR& rh )
    {
        if( lh == 0 )
            return *RealAlgebraicNumberIR::zero( rh.polynomial().variable() );
        RationalUnivariatePolynomial p( rh.polynomial().subs( rh.polynomial().variable() == (rh.polynomial().variable() * lh.inverse())),
                                        rh.polynomial().variable() );
        while( RationalUnivariatePolynomial::countRealRoots( p, rh.interval() * lh ) != 1 )    // refine rh until a unique number representation is found
            rh.refine();
        return *new RealAlgebraicNumberIR( p, rh.interval() * lh );
    }

    RealAlgebraicNumberIR& operator *( RealAlgebraicNumberIR& lh, const GiNaC::numeric& rh )
    {
        if( rh == 0 )
            return *RealAlgebraicNumberIR::zero( lh.polynomial().variable() );
        RationalUnivariatePolynomial p( lh.polynomial().subs( lh.polynomial().variable() == (lh.polynomial().variable() * rh.inverse())),
                                        lh.polynomial().variable() );
        while( RationalUnivariatePolynomial::countRealRoots( p, rh * lh.interval() ) != 1 )    // refine rh until a unique number representation is found
            lh.refine();
        return *new RealAlgebraicNumberIR( p, rh * lh.interval() );
    }

    RealAlgebraicNumberIR& operator /( const GiNaC::numeric& lh, RealAlgebraicNumberIR& rh )
    {
        return lh * rh.inverse();
    }

    RealAlgebraicNumberIR& operator /( RealAlgebraicNumberIR& lh, const GiNaC::numeric& rh )
    {
        return lh * rh.inverse();
    }

    /////////////////////////
    // RealAlgebraicNumber //
    /////////////////////////

    // basic operator

    RealAlgebraicNumberPtr binaryOperator( const RealAlgebraicNumberPtr& lh, const RealAlgebraicNumberPtr& rh, RealAlgebraicNumberIR&( *opIRIR )( RealAlgebraicNumberIR&, RealAlgebraicNumberIR& ), RealAlgebraicNumberIR&( *opIRNR )( RealAlgebraicNumberIR&, const numeric&), const numeric( *opNRNR )(const numeric&, const numeric&) )
    {
        RealAlgebraicNumberIRPtr lhIR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( lh );
        RealAlgebraicNumberIRPtr rhIR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( rh );
        if( lhIR == 0 )
        {
            RealAlgebraicNumberNRPtr lhNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( lh );
            if( rhIR == 0 )
            {
                RealAlgebraicNumberNRPtr rhNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( rh );
                return RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( (*opNRNR)( *lhNR, *rhNR )));
            }
            else
            {
                RealAlgebraicNumberIR sum = (*opIRNR)( *rhIR, *lhNR );
                if( sum.isNumeric() )
                    return RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( sum.value() ));
                return RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( sum ));
            }
        }
        if( rhIR == 0 )
        {
            RealAlgebraicNumberNRPtr rhNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( rh );
            RealAlgebraicNumberIR sum     = (*opIRNR)( *lhIR, *rhNR );
            if( sum.isNumeric() )
                return RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( sum.value() ));
            return RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( sum ));
        }
        else
        {
            RealAlgebraicNumberIR sum = (*opIRIR)( *lhIR, *rhIR );
            if( sum.isNumeric() )
                return RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( sum.value() ));
            return RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( sum ));
        }
    }

    // binary arithmetic operators

    RealAlgebraicNumberPtr operator +( const RealAlgebraicNumberPtr& lh, const RealAlgebraicNumberPtr& rh )
    {
        return binaryOperator( lh, rh, operator +, operator +, GiNaC::operator + );
    }

    RealAlgebraicNumberPtr operator -( const RealAlgebraicNumberPtr& lh, const RealAlgebraicNumberPtr& rh )
    {
        return binaryOperator( lh, -rh, operator +, operator +, GiNaC::operator + );
    }

    RealAlgebraicNumberPtr operator *( const RealAlgebraicNumberPtr& lh, const RealAlgebraicNumberPtr& rh )
    {
        return binaryOperator( lh, rh, operator *, operator *, GiNaC::operator * );
    }

    RealAlgebraicNumberPtr operator /( const RealAlgebraicNumberPtr& lh, const RealAlgebraicNumberPtr& rh )
    {
        return binaryOperator( lh, rh, operator /, operator /, GiNaC::operator / );
    }

    RealAlgebraicNumberPtr operator ^( const RealAlgebraicNumberPtr& base, int exponent )
    {
        RealAlgebraicNumberIRPtr baseIR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( base );
        if( baseIR == 0 )
            return RealAlgebraicNumberPtr( new RealAlgebraicNumberNR(
                std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( base )->power( exponent )));
        if( baseIR->isNumeric() )
            return RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( baseIR->value().power( exponent )));
        return RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( baseIR->pow( exponent )));
    }

    // unary arithmetic operators

    RealAlgebraicNumberPtr operator -( const RealAlgebraicNumberPtr& lh )
    {
        RealAlgebraicNumberIRPtr lhIR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( lh );
        if( lhIR == 0 )
            return RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( -*std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( lh )));
        if( lhIR->isNumeric() )
            return RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( -lhIR->value() ));
        return RealAlgebraicNumberPtr( new RealAlgebraicNumberIR( -*lhIR ));
    }

    // relational operators

    const bool operator ==( const RealAlgebraicNumberPtr& a, const RealAlgebraicNumberPtr& b )
    {
        return RealAlgebraicNumberFactory::equal( a, b );
    }

    const bool operator !=( const RealAlgebraicNumberPtr& a, const RealAlgebraicNumberPtr& b )
    {
        return !RealAlgebraicNumberFactory::equal( a, b );
    }

    const bool operator <( const RealAlgebraicNumberPtr& a, const RealAlgebraicNumberPtr& b )
    {
        return RealAlgebraicNumberFactory::less( a, b );
    }

    std::ostream& operator <<( std::ostream& os, const RealAlgebraicNumberPtr& a )
    {
        print( a, os );
        return os;
    }

    // workaround until operator<< works

    void print( const RealAlgebraicNumberPtr& a, std::ostream& os )
    {
        RealAlgebraicNumberIRPtr irA = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( a );
        RealAlgebraicNumberNRPtr nrA = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( a );
        if( irA != 0 )
            std::cout << *irA;
        else if( nrA != 0 )
            std::cout << static_cast<RealAlgebraicNumberNR>(*nrA);

        else
            std::cout << "NaN";
        //        assert( false ); // This case should never occur! If it still occurs, there might be a segfault somewhere.
    }

    ////////////////////////
    // RealAlgebraicPoint //
    ////////////////////////

    std::ostream& operator <<( std::ostream& os, const RealAlgebraicPoint& r )
    {
        os << "(";
        for( RealAlgebraicPoint::const_iterator i = r.begin(); i != r.end(); ++i )
            print( *i, os << " " );
        os << " )";
        return os;
    }

    ////////////////
    // Constraint //
    ////////////////

    // relational operators

    const bool operator ==( const Constraint& a, const Constraint& b )
    {
        return a.poly() == b.poly() && a.sign() == b.sign();    // Vriables do not need to be checked since they are uniquely defined in GiNaC and therefore checked by the ex check.
    }

    // streaming operators

    std::ostream& operator <<( std::ostream& os, const Constraint& a )
    {
        GiNaC::sign s = a.sign();
        os << a.poly() << (s == ZERO_SIGN ? " = 0" : s == POSITIVE_SIGN ? " > 0" : " < 0");
        vector<symbol> variables = a.variables();
        os << "(" << variables.front();
        for( unsigned i = 1; i != variables.size(); ++i )
            os << ", " << variables[i];
        return os << ")";
    }

}    // namespace GiNaC

