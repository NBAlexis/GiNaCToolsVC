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


/*
 * @author: Joachim Redies
 * @author: Ulrich Loup
 * @since: 2011-10-25
 * @version: 2012-05-02
 */

//#include "RealAlgebraicNumber.h"
//#include "RealAlgebraicNumberFactory.h" // for the methods working on both representations

using GiNaC::ZERO_SIGN;

namespace GiNaCRA
{
    //////////////////////////
    // Con- and destructors //
    //////////////////////////

    RealAlgebraicNumber::RealAlgebraicNumber( bool isRoot, bool isNumeric, const numeric& value ):
        mIsRoot( isRoot ),
        mIsNumeric( isNumeric ),
        mValue( value )
    {}

    RealAlgebraicNumber::~RealAlgebraicNumber(){}

    ////////////////
    // Operations //
    ////////////////

    GiNaC::sign RealAlgebraicNumber::sgn() const
    {
        return ZERO_SIGN;
    }

    GiNaC::sign RealAlgebraicNumber::sgn( const RationalUnivariatePolynomial& p ) const
    {
        return ZERO_SIGN;
    }

    const numeric RealAlgebraicNumber::approximateValue() const
    {
        return 0;
    }
}    // namespace GiNaC

