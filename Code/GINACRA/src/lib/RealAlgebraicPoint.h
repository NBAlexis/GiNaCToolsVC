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


#ifndef GINACRA_REALALGEBRAICPOINT_H
#define GINACRA_REALALGEBRAICPOINT_H

//#include <ginac/ginac.h>

//#include "utilities.h"
//#include "RealAlgebraicNumber.h"
//#include "RealAlgebraicNumberFactory.h"
//#include "Polynomial.h"

using GiNaC::symbol_is_lesseq_lex;

namespace GiNaCRA
{
    /**
     * @author Joachim Redies
     * @author Ulrich Loup
     * @since 2011-10-26
     * @version 2011-12-29
     *
     * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
     */

    class GINACRA_API RealAlgebraicPoint:
        public vector<RealAlgebraicNumberPtr>
    {
        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Creates an empty Point of dimension 0.
             */
            RealAlgebraicPoint():
                vector<RealAlgebraicNumberPtr>()
            {}

            /**
             * Copy constructor.
             * @param r
             */
            RealAlgebraicPoint( const RealAlgebraicPoint& r ):
                vector<RealAlgebraicNumberPtr>( r )
            {}

            /**
             * Constructor reserving a given dimension.
             * @param size
             */
            RealAlgebraicPoint( size_t size ):
                vector<RealAlgebraicNumberPtr>( size )
            {}

            /**
             * Creates a real algebraic point with the specified components.
             * @param v pointers to real algebraic numbers
             */
            RealAlgebraicPoint( const vector<RealAlgebraicNumberPtr>& v ):
                vector<RealAlgebraicNumberPtr>( v )
            {}

            /**
             * Creates a real algebraic point with the specified components from a list.
             * @param v pointers to real algebraic numbers
             */
            RealAlgebraicPoint( const list<RealAlgebraicNumberPtr>& v ):
                vector<RealAlgebraicNumberPtr>( v.begin(), v.end() )
            {}

            ////////////////
            // Operations //
            ////////////////

            /** Gives the number of components of this point.
             * @return the dimension of this point
             */
            const unsigned dim() const;

            /**
             * Conjoins a point with a real algebraic number and returns the conjoined point as new object.
             * e.g.: a point of dimension n conjoined with
             * a real algebraic number is a point of dimension
             * n+1.
             * @param r additional dimension given as real algebraic number
             * @return real algebraic point with higher dimension
             */
            RealAlgebraicPoint conjoin( const RealAlgebraicNumberPtr& r );

    };

}    // namespace GiNaC

#endif
