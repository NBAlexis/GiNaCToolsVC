
/** @file flags.h
 *
 * Flags
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

#ifndef __NESTEDSUMS_FLAGS_H__
#define __NESTEDSUMS_FLAGS_H__

////#include "ginac/ginac.h"

namespace nestedsums {

  /// Flags for the status of the expansion
  class NESTEDSUMS_API expand_status {

  public:
    enum {
      start,
      expansion_required,
      check_for_poles,
      expand_gamma_functions,
      do_partial_fractioning,
      adjust_summation_index,
      hash_checked,
      do_outermost_sum,
      do_hoelder_convolution,
      hoelder_hash_checked,
      evaluated,
      no_eval_to_scalar,
      eval_to_scalar,
      zombie
    };
  };

  /// Flags for the nestedsum_helper_expand function
  class NESTEDSUMS_API expand_request {

  public:
    enum {
      start            = 0x0000,
      power            = 0x0001,
      member_variables = 0x0002,
      one_level        = 0x0004
    };
  };

  /// Flags for the print format for polylogs
  class NESTEDSUMS_API print_format {

  public:
    enum {
      standard             = 0x0000,
      no_harmonic_polylog  = 0x0001,
      no_nielsen_polylog   = 0x0002,
      no_classical_polylog = 0x0004,
      no_special_cases     = 0x0007,
      no_reversed_order    = 0x0008
    };
  };

  /// Additional status flags
 class NESTEDSUMS_API nestedsums_status_flags {
 public:
   enum {
     expanded        = 0x1004
   };
 };

} // namespace nestedsums

//////////////////////////////////////////////////////////////////////////
//For warning C4250

//#define NestedSum_DeclareOverrideExplicitly_P0(funcname) \
//   GiNaC::ex funcname(void) const override { return inherited::funcname(); }
//
//#define NestedSum_DeclareOverrideExplicitly_P1(funcname, param1, param1type) \
//   GiNaC::ex funcname(const param1type & param1) const override { return inherited::funcname(param1); }
//
//#define NestedSum_DeclareOverrideExplicitly_P1V(funcname, param1, param1type) \
//   GiNaC::ex funcname(param1type param1) const override { return inherited::funcname(param1); }
//
//#define NestedSum_DeclareOverrideExplicitly_P1VD(funcname, param1, param1type, param1default) \
//   GiNaC::ex funcname(param1type param1 = param1default) const override { return inherited::funcname(param1); }
//
//#define NestedSum_DeclareOverrideExplicitly_P2(funcname, param1, param1type, param2, param2type) \
//   GiNaC::ex funcname(const param1type & param1, const param2type & param2) const override { return inherited::funcname(param1, param2); }
//
//#define NestedSum_DeclareOverrideExplicitly_P3(funcname, param1, param1type, param2, param2type, param3, param3type) \
//   GiNaC::ex funcname(const param1type & param1, const param2type & param2, const param3type & param3) const override { return inherited::funcname(param1, param2, param3); }
//
//#define NestedSum_DeclareOverrideExplicitly_Zsum() \
//    NestedSum_DeclareOverrideExplicitly_P2(convert_to_Ssum_exvector, Z0, GiNaC::exvector, Z1, GiNaC::exvector) \
//    NestedSum_DeclareOverrideExplicitly_P3(shuffle_exvector, Z0, GiNaC::exvector, Z1, GiNaC::exvector, Z2, GiNaC::exvector) \
//    NestedSum_DeclareOverrideExplicitly_P1(set_index, i, GiNaC::ex) \
//    NestedSum_DeclareOverrideExplicitly_P0(shift_plus_one) \
//    NestedSum_DeclareOverrideExplicitly_P0(shift_minus_one) \
//    NestedSum_DeclareOverrideExplicitly_P1(adjust_upper_limit_downwards, i, GiNaC::ex) \
//    NestedSum_DeclareOverrideExplicitly_P1(adjust_upper_limit_upwards, i, GiNaC::ex) \
//    NestedSum_DeclareOverrideExplicitly_P0(adjust_upper_limit_plus_one) \
//    NestedSum_DeclareOverrideExplicitly_P0(index_eq_one) \
//    NestedSum_DeclareOverrideExplicitly_P1V(get_head, k, int) \
//    NestedSum_DeclareOverrideExplicitly_P1V(get_tail, k, int) \
//    NestedSum_DeclareOverrideExplicitly_P0(antipode) \
//    NestedSum_DeclareOverrideExplicitly_P1VD(expand_members, level, int, 0) \
//    NestedSum_DeclareOverrideExplicitly_P0(eval_explicit) \
//    NestedSum_DeclareOverrideExplicitly_P0(get_first_letter) \
//    NestedSum_DeclareOverrideExplicitly_P0(remove_first_letter) \
//    NestedSum_DeclareOverrideExplicitly_P1(remove_first_letter, nc, GiNaC::ex) \
//    NestedSum_DeclareOverrideExplicitly_P1(prepend_letter, lc, GiNaC::ex) \
//    NestedSum_DeclareOverrideExplicitly_P2(prepend_letter, nc, GiNaC::ex, lc, GiNaC::ex) \
//    NestedSum_DeclareOverrideExplicitly_P1(append_letter, lc, GiNaC::ex) \
//    NestedSum_DeclareOverrideExplicitly_P1(append_letter_list, lc, GiNaC::ex) 

    

#endif // ndef __NESTEDSUMS_FLAGS_H__









