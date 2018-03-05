
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

#endif // ndef __NESTEDSUMS_FLAGS_H__









