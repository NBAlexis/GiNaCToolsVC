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
 * @file RealAlgebraicNumberNR.cpp
 *
 * Implementation of the class RealAlgebraicNumber in numeric representation.
 *
 * @author Joachim Redies
 * @author Ulrich Loup
 * @since 2011-11-25
 * @version 2012-05-02
 */

//#include "RealAlgebraicNumberNR.h"

using GiNaC::ZERO_SIGN;
using GiNaC::POSITIVE_SIGN;
using GiNaC::NEGATIVE_SIGN;

namespace GiNaCRA
{
    //////////////////////////
    // Con- and destructors //
    //////////////////////////

    RealAlgebraicNumberNR::RealAlgebraicNumberNR( const numeric& n, bool isRoot ):
        RealAlgebraicNumber( isRoot, true, n ),
        numeric( n )
    {
        mValue = *this;
    }

    RealAlgebraicNumberNR::RealAlgebraicNumberNR( const RealAlgebraicNumberNR& n ):
        RealAlgebraicNumber( n.isRoot(), true, static_cast<numeric>(n) ),
        numeric( static_cast<numeric>(n) )
    {
        mValue = *this;
    }

    ////////////////
    // Operations //
    ////////////////

    GiNaC::sign RealAlgebraicNumberNR::sgn() const
    {
        if( *this == 0 )
            return ZERO_SIGN;
        else if( *this > 0 )
            return POSITIVE_SIGN;
        else
            return NEGATIVE_SIGN;
    }

    GiNaC::sign RealAlgebraicNumberNR::sgn( const RationalUnivariatePolynomial& p ) const
    {
        switch( p.sgn( *this ))
        {
            case 0:
                return ZERO_SIGN;
            case 1:
                return POSITIVE_SIGN;
            case -1:
                return NEGATIVE_SIGN;
        }
        return NEGATIVE_SIGN;
    }

    /////////////////////////
    // Methods from basic  //
    /////////////////////////

    void RealAlgebraicNumberNR::do_print( const print_context& c, unsigned level ) const
    {
        numeric::do_print( c, level );
        c.s << (mIsRoot ? "~" : "");
    }

}    // namespace GiNaC

