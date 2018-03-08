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


#ifndef GINACRA_REALALGEBRAICNUMBER_H
#define GINACRA_REALALGEBRAICNUMBER_H

//#include <ginac/ginac.h>
//#include <tr1/memory>

//#include "RationalUnivariatePolynomial.h"
//#include "constants.h"

namespace GiNaCRA
{
    /**
     * This class encapsulates several representations of real algebraic numbers and provides crucial operations such as arithmetic, ordering or sign determination on them.
     *
     * @author Joachim Redies
     * @author Ulrich Loup
     * @since 2011-10-03
     * @version 2012-05-02
     */
    class GINACRA_API RealAlgebraicNumber
    {
        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Constructs a real algebraic number with a specified marking as to whether this number stems from a real root computation or not.
             * @param isRoot true marks this real algebraic number to stem from a root computation
             * @param isNumeric true marks this real algebraic number to be representable as an exact numeric (standard is false)
             * @param value the exact numeric value of this number if available, otherwise mIsNumeric is false and mValue 0
             */
            RealAlgebraicNumber( bool isRoot, bool isNumeric = false, const numeric& value = 0 );

            /**
             * Destructor.
             */
            ~RealAlgebraicNumber();

            /**
             * Clone-"Constructor"
             */
            virtual std::tr1::shared_ptr<RealAlgebraicNumber> clone() const
            {
                return std::tr1::shared_ptr<RealAlgebraicNumber>( new RealAlgebraicNumber( *this ));
            }

            ///////////////
            // Selectors //
            ///////////////

            /**
             * @return the flag marking whether the real algebraic number stems from a root computation or not
             */
            const bool isRoot() const
            {
                return mIsRoot;
            }

            /**
             * Set the flag marking whether the real algebraic number stems from a root computation or not.
             * @param isRoot
             */
            void setIsRoot( bool isRoot )
            {
                mIsRoot = isRoot;
            }

            /**
             * Returns true if an exact numeric representation was found during the refinements.
             * @return <code>true</code> if an exact numeric representation was found during the refinements, <code>false</code> otherwise.
             */
            bool isNumeric() const
            {
                return mIsNumeric;
            }

            /** Gives an exact numeric representation of this real algebraic number which could have been found during the refinement steps.
             * The method returns 0 if the value was never set during refinement.
             * @return an exact numeric representation of this real algebraic number which could have been found during the refinement steps
             */
            const numeric value() const
            {
                return mValue;
            }

            ///////////////
            // Operators //
            ///////////////

            // assignment operators

            /**
             * This real algebraic number gets all values of the other.
             * @param o other real algebraic number
             */
            virtual const RealAlgebraicNumber& operator = ( const RealAlgebraicNumber& o )
            {
                mIsRoot = o.mIsRoot;
                return *this;
            }

            ////////////////
            // Operations //
            ////////////////

            /**
             * Returns sign (GiNaC::ZERO_SIGN, GiNaC::POSITIVE_SIGN, GiNaC::NEGATIVE_SIGN) of this real algebraic number.
             * @return sign of this real algebraic number.
             */
            virtual GiNaC::sign sgn() const;

            /**
             * Returns sign (GiNaC::ZERO_SIGN, GiNaC::POSITIVE_SIGN, GiNaC::NEGATIVE_SIGN) of the specified univariate polynomial at this real algebraic number.
             * @param p rational univariate polynomial
             * @return sign of the univariate polynomial at this real algebraic number.
             */
            virtual GiNaC::sign sgn( const RationalUnivariatePolynomial& p ) const;

            /** Computes a numeric value for this real algebraic number approximating it.
             * @complexity constant
             * @return a numeric value for this real algebraic number approximating it
             */
            virtual const numeric approximateValue() const;

        protected:

            ////////////////
            // Attributes //
            ////////////////

            /// flag indicating whether this number represents a root of a polynomial or an intermediate point
            bool mIsRoot;
            /// flag indicating whether this number is representable by a numeric
            bool mIsNumeric;
            /// the exact numeric value of this number if available, otherwise mIsNumeric is false and mValue 0
            numeric mValue;
    };

    ///////////
    // TYPES //
    ///////////

    /// smart pointer (shared) to a RealAlgebraicNumber object
    typedef std::tr1::shared_ptr<RealAlgebraicNumber> RealAlgebraicNumberPtr;

    /// Hash function for the unordered real-algebraic number pointer set.
    struct GINACRA_API RealAlgebraicNumberPtrHasher
    {
        size_t operator ()( RealAlgebraicNumberPtr p ) const
        {
            return (size_t)p.get();
        }
    };

}

#endif
