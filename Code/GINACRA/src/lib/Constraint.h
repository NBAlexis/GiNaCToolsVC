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


#ifndef GINACRA_CONSTRAINT_H
#define GINACRA_CONSTRAINT_H

//#include "constants.h"
//#include "Polynomial.h"
//#include "RealAlgebraicPoint.h"

using std::invalid_argument;
using GiNaC::symbol;

namespace GiNaCRA
{
    /**
     * A class representing a condition on a Constraint as to whether its sign is negative (GiNaCRA::NEGATIVE_SIGN), positive (GiNaCRA::POSITVIE_SIGN) or zero (GiNaCRA::ZERO_SIGN). This class is serving as an abstract superclass of both multivariate and univariate constraints.
     *
     * @author Ulrich Loup
     * @since 2011-12-05
     * @version 2012-04-17
     */

    class GINACRA_API Constraint
    {
        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Standard constructor.
             */
            Constraint():
                mPoly(),
                mSign(),
                mVariables(),
                mNegated( false )
            {}

            /**
             * Constructs a constraint represented as a sign condition <code>p.sgn(...) == s</code> or a negated sign condition <code>p.sgn(...) != s</code>.
             * @param p polynomial compared
             * @param s sign comparing the sign of the polynomial to GiNaCRA::ZERO_SIGN, GiNaCRA::POSITVIE_SIGN, or GiNaCRA::NEGATIVE_SIGN.
             * @param v the variables of the polynomial
             * @param negated if set to <code>true</code>, <code>satisfiedBy</code> checks the negation of the specified sign condition. If otherwise <code>false</code> is specified (standard value), <code>satisfiedBy</code> checks the sign condition as specified.
             */
            Constraint( const Polynomial& p, const GiNaC::sign s, const vector<symbol> v, bool negated = false ):
                mPoly( p ),
                mSign( s ),
                mVariables( checkVariables( p, v )),
                mNegated( negated )
            {}

            ///////////////
            // Selectors //
            ///////////////

            /**
             * @return the polynomial of the constraint
             */
            const Polynomial poly() const
            {
                return mPoly;
            }

            /**
             * @return the polynomial of the constraint
             */
            const GiNaC::sign sign() const
            {
                return mSign;
            }

            /**
             * @return the list of variables of this constraint
             */
            const vector<symbol> variables() const
            {
                return mVariables;
            }

            ////////////////
            // Operations //
            ////////////////

            /**
             * Test if the given point satisfies this constraint. The variables of this constraint are substituted by the components of r in ascending order until all variables are substituted, even if r is larger.
             * @param r test point
             * @return false if the constraint was not satisfied by the given point, true otherwise.
             * @throw exception if the point has a too small dimension
             */
            bool satisfiedBy( const RealAlgebraicPoint& r ) const;

        private:

            ////////////////
            // Attributes //
            ////////////////

            Polynomial     mPoly;
            GiNaC::sign    mSign;
            vector<symbol> mVariables;
            bool           mNegated;

            ///////////////////////
            // Auxiliary methods //
            ///////////////////////

            /**
             * Verifies whether this constraint is solely constructed over the given variables.
             * @param p polynomial
             * @param v list of variables
             * @return v if the check was successful
             * @throw invalid_argument if there is another variable in the constraint so it cannot be checked for satisfiability
             */
            const vector<symbol> checkVariables( const Polynomial& p, const vector<symbol>& v ) const throw ( invalid_argument );

    };    // class Constraint

}    // namespace GiNaCRA

#endif
