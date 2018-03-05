
/** @file constants.cc
 *
 * Global constants
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

#include "nestedsum_private.h"
#include "version.h"

#ifdef _DEBUG
#include <iostream>
#include <ctime>
#endif // def _DEBUG

namespace nestedsums {

using namespace GiNaC;

  /**
   *  Version information 
   */
  const int nestedsums_version_major = NESTEDSUMS_MAJOR;
  const int nestedsums_version_minor = NESTEDSUMS_MINOR;
  const int nestedsums_version_micro = NESTEDSUMS_MICRO;

  /** 
   * A global constant to represent infinity
   */ 
 extern const symbol Infinity("Infinity","\\infty");

  /**
   *
   * A global variable which allows additional information to be printed out
   * for debugging.
   * If bit 0 is set, additional information during the evaluation of sums
   * of type A is printed.
   * If bit 1 is set, additional information during the evaluation of sums
   * of type B is printed.
   * If bit 2 is set, additional information during the evaluation of sums
   * of type C is printed.
   * If bit 3 is set, additional information during the evaluation of sums
   * of type D is printed.
   *
   * If bit 4 is set, additional information for Csum::convert_to_Ssum
   * is printed.
   * If bit 5 is set, additional information for Bsum::convert_to_Ssum
   * is printed.
   *
   */
 int _debug_level = 0;

 /**
   * A global variable to stop evaluation at a certian stage
   */
 int _nestedsums_evaluation_veto = expand_status::zombie;

 /**
   * A global variable to stop evaluation for sums of type A at a certian stage
   */
 int _nestedsums_evaluation_veto_type_A = expand_status::zombie;

 /**
   * A global variable to stop evaluation for sums of type B at a certian stage
   */
 int _nestedsums_evaluation_veto_type_B = expand_status::zombie;

 /**
   * A global variable to stop evaluation for sums of type C at a certian stage
   */
 int _nestedsums_evaluation_veto_type_C = expand_status::zombie;

 /**
   * A global variable to stop evaluation for sums of type D at a certian stage
   */
 int _nestedsums_evaluation_veto_type_D = expand_status::zombie;

 /**
   * 
   */
 int _NMAX = 10;

  /**
   *
   */
 int _print_format = 0;

  /** 
   * A global constant to represent an unspecified symbol, 
   * used in default ctors.
   */ 
 extern const symbol _default("default");

  /** 
   * A global constant to represent an unspecified summation index
   */ 
 extern const symbol _default_index("dummy");

 /**
  *
  * A global variable for an empty list.
  *
  */
 extern const lst _empty_list = lst();

   /**
   * ONE in the algebra of letters, e.g. 
   * \f[
   *    \frac{1}{i^0}
   * \f]
   */
 extern const unit_letter _unit_zero_letter = unit_letter((ex) 0);

  /**
   * The unit letter of weight 1, e.g.
   * \f[
   *    \frac{1}{i^1}
   * \f]
   */
 extern const unit_letter _unit_one_letter = unit_letter((ex) 1);

 /**
  *
  * A global variable for an empty list of ratio_of_tgamma's.
  *
  */
 extern const list_of_tgamma _empty_list_of_tgamma = list_of_tgamma();

 extern const basic_letter _default_basic_letter = basic_letter();
 extern const Zsum _default_Zsum = Zsum();
 extern const multiple_polylog _default_multiple_polylog = multiple_polylog();
 extern const Ssum _default_Ssum = Ssum();
 extern const Ssum_to_Infinity _default_Ssum_to_Infinity = Ssum_to_Infinity();


 // hash tables

 std::map<unsigned, ex> _table_list_of_tgamma;
 int _flag_table_list_of_tgamma = 1;
 int _count_table_list_of_tgamma = 0;

 std::map<unsigned, ex> _table_transcendental_sum_type_A;
 int _flag_table_transcendental_sum_type_A = 1;
 int _count_table_transcendental_sum_type_A = 0;

 std::map<unsigned, ex> _table_transcendental_sum_type_C;
 int _flag_table_transcendental_sum_type_C = 1;
 int _count_table_transcendental_sum_type_C = 0;

} // namespace nestedsums
