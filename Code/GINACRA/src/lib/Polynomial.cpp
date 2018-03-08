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


//#include "Polynomial.h"

using GiNaC::is_exactly_a;
using GiNaC::ex;
using GiNaC::add;
using GiNaC::mul;
using GiNaC::power;
using GiNaC::symbol;
using GiNaC::numeric;

/**
 * Implementation of the class Polynomial.
 *
 * @author Ulrich Loup
 * @since 2011-11-03
 * @version 2012-03-19
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

namespace GiNaCRA
{
    //////////////////////////
    // Con- and destructors //
    //////////////////////////

    Polynomial::Polynomial( const ex& p ) throw ( std::invalid_argument ):
        ex( p )
    {
        if( !(is_exactly_a<add>( *this ) || is_exactly_a<mul>( *this ) || is_exactly_a<power>( *this ) || is_exactly_a<symbol>( *this )
                || is_exactly_a<numeric>( *this ) || this->info( GiNaC::info_flags::numeric )))
            throw std::invalid_argument( "Specified expression is no polynomial." );
    }

}    // namespace GiNaC

