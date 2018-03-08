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


//#include "MultivariateCoefficientMR.h"

namespace GiNaCRA
{
    MultivariateCoefficientMR::MultivariateCoefficientMR():
        mCoefficient()
    {}

    MultivariateCoefficientMR::MultivariateCoefficientMR( const GiNaC::ex& expr ):
        mCoefficient( expr )
    {}

    bool operator ==( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 )
    {
        return m1.mCoefficient == m2.mCoefficient;
    }

    const MultivariateCoefficientMR operator *( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 )
    {
        return m1.mCoefficient * m2.mCoefficient;
    }

    const MultivariateCoefficientMR operator +( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 )
    {
        return m1.mCoefficient + m2.mCoefficient;
    }

    const MultivariateCoefficientMR operator -( const MultivariateCoefficientMR& m1 )
    {
        return MultivariateCoefficientMR( -1 * m1.mCoefficient );
    }

    const MultivariateCoefficientMR operator -( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 )
    {
        return m1.mCoefficient - m2.mCoefficient;
    }

    const MultivariateCoefficientMR operator /( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 )
    {
        return m1.mCoefficient / m2.mCoefficient;
    }

    std::ostream& operator <<( std::ostream& os, const MultivariateCoefficientMR& m1 )
    {
        return os << m1.mCoefficient;
    }
}
