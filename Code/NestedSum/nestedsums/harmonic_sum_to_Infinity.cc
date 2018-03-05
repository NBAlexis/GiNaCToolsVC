
/** @file harmonic_sum_to_Infinity.cc
 *
 * Implementation of harmonic sums to Inifinty
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

#include <iostream>
#include <stdexcept>
#include "nestedsum_private.h"

#ifdef _DEBUG
#include <ctime>
#endif // def _DEBUG

namespace nestedsums {

using namespace GiNaC;

GINAC_IMPLEMENT_REGISTERED_CLASS(harmonic_sum_to_Infinity, Ssum_to_Infinity)

GINAC_BIND_UNARCHIVER(harmonic_sum_to_Infinity);



  harmonic_sum_to_Infinity::harmonic_sum_to_Infinity() : inherited()
  { 
  }

  void harmonic_sum_to_Infinity::archive(archive_node &node) const
  {
    inherited::archive(node);
  }

  void harmonic_sum_to_Infinity::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);
  }

  int harmonic_sum_to_Infinity::compare_same_type(const basic &other) const
  {
    const harmonic_sum_to_Infinity &o = dynamic_cast<const harmonic_sum_to_Infinity &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  harmonic_sum_to_Infinity::harmonic_sum_to_Infinity(const ex & llc) : Ssum(Infinity,llc)
  { }

  // functions overriding virtual functions from bases classes
  return_type_t harmonic_sum_to_Infinity::return_type_tinfo() const 
  {
    return _default_Ssum_to_Infinity.return_type_tinfo();
  }

  void harmonic_sum_to_Infinity::print(const print_context & c, unsigned level) const
  {
    harmonic_sum::print(c,level);
  }

  /**
   *
   * No simplifications implemented.
   * 
   */
  ex harmonic_sum_to_Infinity::eval() const
  {

    return this->hold();

  }

} // namespace nestedsums

