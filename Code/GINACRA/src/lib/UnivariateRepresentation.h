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


#ifndef GINACRA_UNIVARIATEREPRESENTATION_H
#define GINACRA_UNIVARIATEREPRESENTATION_H

//#include <ginac/flags.h>
//#include <ginac/registrar.h>
//#include <ginac/ginac.h>
#include <stdexcept>
//
//#include "RationalUnivariatePolynomial.h"
//#include "operators.h"

//WHY IS THE NAMESPACE DIFFERENT???
namespace GiNaCRA
{
    /**
     * An implementation of a multi dimensional real algebraic number providing arithmetic and relational operations.
     * @todo Write comprehensive description of how real algebraic number is represented via univariate representation and how the other features like getOrder() etc. are implemented.
     *
     * @author Ulrich Loup
     * @since 2011-04-30
     * @version 2011-10-30
     * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
     *
     * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
     */
    class GINACRA_API UnivariateRepresentation:
        public GiNaC::basic
    {
        // Call GiNaC macro (registrar.h) for initiating the implementation into the basic type.
        GINAC_DECLARE_REGISTERED_CLASS(UnivariateRepresentation, GiNaC::basic)

        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             *
             *
             * @param rootSource
             * @param denominator
             * @param numerators
             * @param variables
             */
            UnivariateRepresentation( const RationalUnivariatePolynomial& rootSource,
                                      const RationalUnivariatePolynomial& denominator,
                                      const list<RationalUnivariatePolynomial>& numerators,
                                      const std::vector<GiNaC::symbol>& variables )
                    throw (std::invalid_argument );

            ~UnivariateRepresentation();

            ///////////////
            // Selectors //
            ///////////////

            /**
             *
             * @return polynomial being the source of the roots for evaluating with the rational functions
             */
            const RationalUnivariatePolynomial RootSource() const;

            /**
             *
             * @return the denominator of the rational functions
             */
            const RationalUnivariatePolynomial Denominator() const;

            /**
             *
             * @return polynomial being the numerators of the rational functions
             */
            const list<RationalUnivariatePolynomial> Numerators() const;

            ///////////////
            // Operators //
            ///////////////

            // // binary arithmetic operators
            // const UnivariateRepresentation operator+(UnivariateRepresentation);
            // const UnivariateRepresentation operator-(UnivariateRepresentation);
            // const UnivariateRepresentation operator*(UnivariateRepresentation);
            // const UnivariateRepresentation operator/(UnivariateRepresentation);

            // // unary arithmetic operators
            // const UnivariateRepresentation operator-();

            // relational operators
            // const bool operator==(const UnivariateRepresentation&);
            // const bool operator!=(const UnivariateRepresentation&);
            // const bool operator<(const UnivariateRepresentation&);
            // const bool operator>(const UnivariateRepresentation&);
            // const bool operator<=(const UnivariateRepresentation&);
            // const bool operator>=(const UnivariateRepresentation&);

            // assignment operators

            /**
             * This number gets all values of the other.
             */
            // const UnivariateRepresentation& operator=(const UnivariateRepresentation&);

            ////////////////
            // Operations //
            ////////////////

            ///////////////////////////
            // Arithmetic Operations //
            ///////////////////////////

            /** Adds two real algebraic numbers and returns a reference to their sum, allocated on the heap.
             * @param o
             * @return sum allocated on the heap
             */
            const UnivariateRepresentation add( UnivariateRepresentation o ) throw (std::invalid_argument );

            /** Returns the negative value, allocated on the heap.
             * @return negative value allocated on the heap
             */
            const UnivariateRepresentation minus() const;

            /** Multiplies two real algebraic numbers and returns a reference to their product, allocated on the heap.
             * @param o
             * @return product allocated on the heap
             */
            const UnivariateRepresentation mul( UnivariateRepresentation o ) throw (std::invalid_argument );

            /** Returns the inverse, allocated on the heap.
             * @return inverse value allocated on the heap
             */
            const UnivariateRepresentation inverse() const throw (std::invalid_argument );

            ////////////////////
            // Static Methods //
            ////////////////////

        protected:

            ////////////////////////
            // Methods from basic //
            ////////////////////////

            bool is_equal_same_type( const GiNaC::basic& other );
            void do_print( const print_context& c, unsigned level = 0 ) const;
            GiNaC::ex eval( int level = 0 ) const;
            // unsigned calchash() const;

        private:

            ////////////////
            // Attributes //
            ////////////////

            RationalUnivariatePolynomial       mRootSource;
            RationalUnivariatePolynomial       mDenominator;    // mDenominator and mRootSource are coprime, i.e., they have a nonzero gcd
            std::list<RationalUnivariatePolynomial> mNumerators;
            std::vector<GiNaC::symbol>                     mVariables;

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            ////////////////
            // Operations //
            ////////////////

            ///////////////////////////
            // Relational Operations //
            ///////////////////////////

    };

}    // namespace GiNaC

#endif
