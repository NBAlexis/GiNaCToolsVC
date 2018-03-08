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


#ifndef GINACRA_POLYNOMIAL_H
#define GINACRA_POLYNOMIAL_H

//#include <ginac/ginac.h>
#include <stdexcept>

using GiNaC::ex;

namespace GiNaCRA
{
    /**
     * A class for a polynomial in general serving as an abstract superclass of both multivariate and univariate polynomials.
     * All expressions being polynomials are <strong>not</strong> expanded or simplified by any means since this is could influence the semantics of specializations such as UnivariatePolynomial which collect terms for the main variables.
     *
     * @author Ulrich Loup
     * @since 2011-11-03
     * @version 2011-11-05
     *
     * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
     */

    class GINACRA_API Polynomial:
        public ex
    {
        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Constructs a polynomial being a standard expression.
             */
            Polynomial():
                ex()
            {}

            /**
             * Constructs a polynomial from an expression by checking for being a proper polynomial.
             * @param p polynomial
             */
            Polynomial( const ex& p ) throw ( std::invalid_argument );

    };    // class Polynomial

}    // namespace GiNaC

#endif
