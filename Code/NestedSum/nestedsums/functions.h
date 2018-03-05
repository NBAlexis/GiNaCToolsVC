/** @file functions.h
 *
 *  Implements some special functions and conversions to and from nestedsums Z-sums
 *
 */

/*  
 *  Copyright (C) 2001-2017 Stefan Weinzierl
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#ifndef __NESTEDSUMS_FUNCTIONS_H__
#define __NESTEDSUMS_FUNCTIONS_H__

//#include "ginac/ginac.h"

namespace nestedsums {

// Harmonic sums
// first parameter is a GiNaC::lst holding the degrees, second parameter is the index
DECLARE_FUNCTION_2P(Harmonic_sum)


// Euler-Zagier sums
// first parameter is a GiNaC::lst holding the degrees, second parameter holds the index
DECLARE_FUNCTION_2P(EulerZagier_sum)


// S sums to infinity
// like the nestedsums object, arguments are in same order
DECLARE_FUNCTION_2P(S_sum_infinity)


// S sums
// like the nestedsums object, arguments are in same order
DECLARE_FUNCTION_3P(S_sum)


// Z sums
// like the nestedsums object, arguments are in same order
DECLARE_FUNCTION_3P(Z_sum)


// converts in an expression the ginac functions to the equivalent nestedsums objects
extern NESTEDSUMS_API GiNaC::ex convert_to_nestedsums(const GiNaC::ex & e);


// converts in an expression the nestedsums objects to the equivalent ginac functions
extern NESTEDSUMS_API GiNaC::ex convert_to_ginac_functions(const GiNaC::ex & e);

//move from functions.cc to .h because static is not allowed.
extern NESTEDSUMS_API GiNaC::ex Harmonic_sum_eval(const GiNaC::ex& x1, const GiNaC::ex& x2);

extern NESTEDSUMS_API GiNaC::ex EulerZagier_sum_eval(const GiNaC::ex& x1, const GiNaC::ex& x2);

extern NESTEDSUMS_API GiNaC::ex S_sum_infinity_eval(const GiNaC::ex& x1, const GiNaC::ex& x2);

extern NESTEDSUMS_API GiNaC::ex S_sum_eval(const GiNaC::ex& x1, const GiNaC::ex& x2, const GiNaC::ex& x3);

extern NESTEDSUMS_API GiNaC::ex Z_sum_eval(const GiNaC::ex& x1, const GiNaC::ex& x2, const GiNaC::ex& x3);

} // namespace nestedsums


#endif // __NESTEDSUMS_FUNCTIONS_H__

