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


// #define GINACRA_INTERVALREPRESENTATION_DEBUG

/**
 *
 * @author Ulrich Loup
 * @since 2011-04-30
 * @version 2011-04-30
 * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

//#include "UnivariateRepresentation.h"

namespace GiNaCRA
{
    // Call GiNaC macro (registrar.h) for completing the implementation into the basic type.
    GINAC_IMPLEMENT_REGISTERED_CLASS_OPT(UnivariateRepresentation, GiNaC::basic, print_func<print_context>( &UnivariateRepresentation::do_print ))

    //////////////////////////
    // Con- and destructors //
    //////////////////////////
    UnivariateRepresentation::~UnivariateRepresentation(void) { ; }

    ///////////////
    // Selectors //
    ///////////////

    /////////////////////////
    // Methods from basic  //
    /////////////////////////

    // // * @todo
    int UnivariateRepresentation::compare_same_type(const basic & other) const
    {
        //UnivariateRepresentation o = static_cast<const UnivariateRepresentation &>(other);
        //// the following is correct since always l <= r
        //if (mInterval == o.mInterval)
        //    return 0;
        //else if (mInterval <= o.mInterval)
        //    return -1;
        //else if (mInterval >= o.mInterval)
        //    return 1;
        //return 0;
        // return this->compare(other);
        return 1;
    }

    // // * @todo
    // bool UnivariateRepresentation::is_equal_same_type(const basic & other)
    // {
    //  UnivariateRepresentation o = static_cast<const UnivariateRepresentation &>(other);
    //  return this->isEqual(o);
    // }

     void UnivariateRepresentation::do_print(const print_context & c, unsigned level) const
     {
      // print_context::s is a reference to an ostream
      c.s << '{' << " UnivariateRepresentation::do_print not implemented yet" << '}';
     }

    // ex UnivariateRepresentation::eval(int level) const
    // {
    //  // this->refine(); up to a certain bound ?
    //  return this->hold();
    // }

    ///////////////
    // Operators //
    ///////////////

    // arithmetic operators

    // relational operators

    // assignment operators

    // const UnivariateRepresentation& UnivariateRepresentation::operator=(const UnivariateRepresentation& o)
    // {
    //     mInterval = o.mInterval;
    //     mPolynomial = o.mPolynomial;
    //     mSturmSequence = o.mSturmSequence;
    //     mOrder = o.mOrder;
    //     return *this;
    // }

    ////////////////
    // Operations //
    ////////////////

    ///////////////////////////
    // Arithmetic Operations //
    ///////////////////////////

    ///////////////////////////
    // Relational Operations //
    ///////////////////////////

    ////////////////////
    // Static Methods //
    ////////////////////
     

}    // namespace GiNaC

