
/** @file Ssum_to_Infinity.cc
 *
 * Implementation of Ssums to Infinity
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

GINAC_IMPLEMENT_REGISTERED_CLASS(Ssum_to_Infinity, Ssum)

GINAC_BIND_UNARCHIVER(Ssum_to_Infinity);



  Ssum_to_Infinity::Ssum_to_Infinity() : inherited(Infinity,_empty_list)
  { 
  }

  void Ssum_to_Infinity::archive(archive_node &node) const
  {
    inherited::archive(node);
  }

  void Ssum_to_Infinity::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);
  }

  int Ssum_to_Infinity::compare_same_type(const basic &other) const
  {
    const Ssum_to_Infinity &o = dynamic_cast<const Ssum_to_Infinity &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  Ssum_to_Infinity::Ssum_to_Infinity(const ex & llc) : inherited(Infinity,llc)
  { }

  // functions overriding virtual functions from bases classes

  /**
   *
   * The simplifications are done in the following order:
   *
   * - If all \f$x_j\f$'s are equal to 1, we have a harmonic sum to infinity.
   *
   */
  ex Ssum_to_Infinity::eval() const
  {
    unsigned depth = get_depth();

    // check if simplifies to harmonic sum to Infinity
    if ( depth==0 ) return create_harmonic_sum_to_Infinity(letter_list);
    int i=0;
    while ( is_a<unit_letter>(letter_list.op(i++).eval()) )
      {
	if ( i==depth) return create_harmonic_sum_to_Infinity(letter_list);
      }

    return this->hold();

  }

} // namespace nestedsums

