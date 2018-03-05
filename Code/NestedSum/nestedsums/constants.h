
/** @file constants.h
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

#ifndef __NESTEDSUMS_CONSTANTS_H__
#define __NESTEDSUMS_CONSTANTS_H__

//#include "ginac/ginac.h"

#include "symbol_factory.h"

namespace nestedsums {

 extern NESTEDSUMS_API const int nestedsums_version_major;
 extern NESTEDSUMS_API const int nestedsums_version_minor;
 extern NESTEDSUMS_API const int nestedsums_version_micro;

 extern NESTEDSUMS_API const GiNaC::symbol Infinity;

 const int add_precedence = 40;
 const int mul_precedence = 50;
 const int pow_precedence = 60;

 // globals used internally

 extern NESTEDSUMS_API int _debug_level;
 extern NESTEDSUMS_API int _nestedsums_evaluation_veto;
 extern NESTEDSUMS_API int _nestedsums_evaluation_veto_type_A;
 extern NESTEDSUMS_API int _nestedsums_evaluation_veto_type_B;
 extern NESTEDSUMS_API int _nestedsums_evaluation_veto_type_C;
 extern NESTEDSUMS_API int _nestedsums_evaluation_veto_type_D;

 extern NESTEDSUMS_API int _NMAX;

 extern NESTEDSUMS_API int _print_format;

 extern NESTEDSUMS_API const GiNaC::symbol _default;
 extern NESTEDSUMS_API const GiNaC::symbol _default_index;
 extern NESTEDSUMS_API const GiNaC::lst _empty_list;

 extern NESTEDSUMS_API const unit_letter _unit_zero_letter;
 extern NESTEDSUMS_API const unit_letter _unit_one_letter;

 extern NESTEDSUMS_API const list_of_tgamma _empty_list_of_tgamma;

 // needed for correct RTTI
 extern NESTEDSUMS_API const basic_letter _default_basic_letter;
 extern NESTEDSUMS_API const Zsum _default_Zsum;
 extern NESTEDSUMS_API const multiple_polylog _default_multiple_polylog;
 extern NESTEDSUMS_API const Ssum _default_Ssum;
 extern NESTEDSUMS_API const Ssum_to_Infinity _default_Ssum_to_Infinity;

 // hash tables

 extern NESTEDSUMS_API std::map<unsigned, GiNaC::ex> _table_list_of_tgamma;
 extern NESTEDSUMS_API int _flag_table_list_of_tgamma;
 extern NESTEDSUMS_API int _count_table_list_of_tgamma;

 extern NESTEDSUMS_API std::map<unsigned, GiNaC::ex> _table_transcendental_sum_type_A;
 extern NESTEDSUMS_API int _flag_table_transcendental_sum_type_A;
 extern NESTEDSUMS_API int _count_table_transcendental_sum_type_A;

 extern NESTEDSUMS_API std::map<unsigned, GiNaC::ex> _table_transcendental_sum_type_C;
 extern NESTEDSUMS_API int _flag_table_transcendental_sum_type_C;
 extern NESTEDSUMS_API int _count_table_transcendental_sum_type_C;

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_CONSTANTS_H__

