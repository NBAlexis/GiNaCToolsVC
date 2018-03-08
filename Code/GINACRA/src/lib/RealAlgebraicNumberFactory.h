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


#ifndef GINACRA_REALALGEBRAICNUMBERFACTORY_H
#define GINACRA_REALALGEBRAICNUMBERFACTORY_H

//#include <tr1/memory>
//
//#include "settings.h"
//#include "RealAlgebraicNumber.h"
//#include "RealAlgebraicNumberIR.h"
//#include "RealAlgebraicNumberNR.h"

namespace GiNaCRA
{
    //////////////
    // Typedefs //
    //////////////

    typedef std::map<symbol, RealAlgebraicNumberIRPtr, GiNaC::ex_is_less> evalmap;

    /**
     * A class providing useful static methods which produce instances of RealAlgebraicNumberIR.
     *
     * @since 2011-10-18
     * @version 2012-03-15
     * @author Joachim Redies
     * @author Ulrich Loup
     */
    class GINACRA_API RealAlgebraicNumberFactory
    {
        public:

            ////////////
            // Common //
            ////////////

            /**
             * Tests if the objects encapsulated by the pointers
             * are equal.
             * @param a smart pointer to a real algebraic number
             * @param b smart pointer to a real algebraic number
             * @return true if <code>a == b</code> otherwise false
             */
            static bool equal( const RealAlgebraicNumberPtr& a, const RealAlgebraicNumberPtr& b );

            /**
             * Compares the objects encapsulated by the pointers
             * and returns true if <code>a</code> is less than <code>b</code> regardless of the type.
             * @param a smart pointer to a real algebraic number
             * @param b smart pointer to a real algebraic number
             * @return true if <code>a < b</code> otherwise false
             */
            static bool less( const RealAlgebraicNumberPtr& a, const RealAlgebraicNumberPtr& b );

            /**
             * Checks whether <code>a</code> is a pointer to a numeric representation.
             * @return true if it is a numeric representation otherwise false.
             */
            static bool isRealAlgebraicNumberNR( const RealAlgebraicNumberPtr& a );

            /**
             * Checks whether <code>a</code> is a pointer to a interval representation.
             * @return true if it is a interval representation otherwise false.
             */
            static bool isRealAlgebraicNumberIR( const RealAlgebraicNumberPtr& a );

            ////////////////
            // Real Roots //
            ////////////////

            /**
             * Isolates the real roots of the given rational univariate polynomial.
             *
             * Note that the contents of p can be changed due to a normalization within the RealAlgebraicNumberIR constructor.
             *
             * @param p rational univariate polynomial
             * @param pivoting strategy selection according to RealAlgebraicNumberSettings::IsolationStrategy (standard option is RealAlgebraicNumberSettings::DEFAULT_ISOLATIONSTRATEGY)
             * @return list containing the real roots of the given polynomial
             */
            static list<RealAlgebraicNumberPtr> realRoots( const RationalUnivariatePolynomial& p,
                                                           RealAlgebraicNumberSettings::IsolationStrategy pivoting = RealAlgebraicNumberSettings::DEFAULT_ISOLATIONSTRATEGY );

            /**
             * Isolates the real roots of the given univariate polynomial by evaluating its parameterized coefficients according to the given evalmap map.
             *
             * @param p possibly parameterized univariate polynomial
             * @param m evaluation map for the coefficients of p
             * @param pivoting strategy selection according to RealAlgebraicNumberSettings::IsolationStrategy (standard option is RealAlgebraicNumberSettings::DEFAULT_ISOLATIONSTRATEGY)
             * @return list containing the real roots of the given polynomial, which is evaluated according to the given evalmap map
             */
            static list<RealAlgebraicNumberPtr> realRootsEval( const UnivariatePolynomial& p,
                                                               const evalmap& m,
                                                               RealAlgebraicNumberSettings::IsolationStrategy pivoting = RealAlgebraicNumberSettings::DEFAULT_ISOLATIONSTRATEGY )
                    throw ( invalid_argument );

            /**
             * Isolates the real roots of the given univariate polynomial by evaluating its parameterized coefficients according to the given evalmap map.
             *
             * @param p possibly parameterized univariate polynomial
             * @param a vector with interval-represented RealAlgebraicNumbers
             * @param v the variables for evaluation corresponding to the real algebraic point
             * @param pivoting strategy selection according to RealAlgebraicNumberSettings::IsolationStrategy (standard option is RealAlgebraicNumberSettings::DEFAULT_ISOLATIONSTRATEGY)
             * @return list containing the real roots of the given polynomial, which is evaluated according to the given variables/numbers
             */
            static list<RealAlgebraicNumberPtr> realRootsEval( const UnivariatePolynomial& p,
                                                               const vector<RealAlgebraicNumberIRPtr>& a,
                                                               const vector<symbol>& v,
                                                               RealAlgebraicNumberSettings::IsolationStrategy pivoting = RealAlgebraicNumberSettings::DEFAULT_ISOLATIONSTRATEGY )
                    throw ( invalid_argument );

            /**
             * Computes the list of common real roots of the given list of rational univariate polynomials.
             *
             * Note that the contents of the polynomials in l can be changed due to a normalization within the RealAlgebraicNumberIR constructor.
             *
             * @param l list of rational univariate polynomials
             * @return vector containing the common real roots of the given list of polynomials
             */
            static list<RealAlgebraicNumberPtr> commonRealRoots( const list<RationalUnivariatePolynomial>& l );

            /**
             * Evaluates the given polynomial p in <code>variables</code>,
             * at the given vector of <code>RealAlgeraicNumberIR</code>s <code>r</code> by substituting all variables.
             * <code>r</code> shall only contain <code>RealAlgebraicNumberIRPtr</code>.
             * <p>
             * The algorithm assumes that the variables in <code>variables</code> are all variables occurring in <code>p</code>.
             * </p>
             * @param p polynomial to be evaluated in the given variables.
             * @param a vector with interval-represented RealAlgebraicNumbers
             * @param v the variables for evaluation corresponding to the real algebraic point
             * @return Real algebraic number representing the value of <code>p</code> evaluated at <code>r</code>
             * @see Constraint::satisfiedBy and CAD::samples for usages of this method
             */
            static const RealAlgebraicNumberPtr evaluateIR( const UnivariatePolynomial& p,
                                                            const vector<RealAlgebraicNumberIRPtr>& a,
                                                            const vector<symbol>& v )
                    throw ( invalid_argument );

            /**
             * Evaluates the coefficients of the given polynomial p, univariate in a variable <i>not</i> occurring in <code>variables</code>,
             * at the given vector of <code>RealAlgeraicNumberIR</code>s <code>r</code> by substituting all variables.
             * <code>r</code> shall only contain <code>RealAlgebraicNumberIRPtr</code>.
             * <p>
             * Note that variable i is replaced with an appropriate numeric value corresponding to the i-th <code>RealAlgeraicNumberIR</code>.
             * The algorithm assumes that all variables in <code>variables</code> are coefficient variables.
             * </p>
             * @param p polynomial to be evaluated in the given variables. This should be a univariate polynomial in a variable <i>not</i> occurring in <code>variables</code>.
             * @param m map assigning each variable of <code>p</code> an interval-represented RealAlgebraicNumber
             * @return Real algebraic number representing the value of <code>p</code> evaluated according to <code>m</code>
             * @see Constraint::satisfiedBy and CAD::samples for usages of this method
             */
            static const RealAlgebraicNumberPtr evaluateIR( const UnivariatePolynomial& p, const evalmap m ) throw ( invalid_argument );

        private:

            /////////////////////////
            // Auxiliary Functions //
            /////////////////////////

            /** Helping method to find the real roots of a polynomial recursively.
             * This method offers several solving strategies available by setting the argument <code>pivoting</code>.
             * All have in common that 0 is returned as <code>RealAlgebraicNumberNR</code> if it happens to be a valid root. For details on the strategies @see
             * @param varMinLeft number of sign variations of seq at the minimal left endpoint
             * @param p polynomial whose roots are searched
             * @param seq standard Sturm of p
             * @param i isolating interval which shall be searched for real roots recursively
             * @param offset the number of roots to subtract from the actual root count in the interval <code>i</code>. The standard value is 0 which also holds for the initial call by the Cauchy bounds. The offset should be set to <code>(p.sgn(i.Left()) == GiNaC::ZERO_SIGN) + (p.sgn(i.Right()) == GiNaC::ZERO_SIGN)</code>.
             * @param roots list of roots found so far
             * @param pivoting strategy selection according to RealAlgebraicNumberSettings::IsolationStrategy
             */
            static void searchRealRoots( const unsigned varMinLeft,
                                         const RationalUnivariatePolynomial& p,
                                         const list<RationalUnivariatePolynomial>& seq,
                                         const OpenInterval& i,
                                         list<RealAlgebraicNumberPtr>* roots,
                                         unsigned offset,
                                         RealAlgebraicNumberSettings::IsolationStrategy pivoting );

    };

}    // namespace GiNaC

#endif /** GINACRA_REALALGEBRAICNUMBERFACTORY_H_ */
