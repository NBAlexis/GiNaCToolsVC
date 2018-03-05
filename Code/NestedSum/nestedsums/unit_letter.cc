
/** @file unit_letter.cc
 *
 * Implementation of unit_letter
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

GINAC_IMPLEMENT_REGISTERED_CLASS(unit_letter, letter)

GINAC_BIND_UNARCHIVER(unit_letter);



  unit_letter::unit_letter() : inherited(1,_default)
  { 
  }

  void unit_letter::archive(archive_node &node) const
  {
    inherited::archive(node);
  }

  void unit_letter::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);
  }

  int unit_letter::compare_same_type(const basic &other) const
  {
    const unit_letter &o = static_cast<const unit_letter &>(other);

    int cmpval = index.compare(o.index);

    if( cmpval ) return cmpval;

    return degree.compare(o.degree);
  }

  // other ctors
  unit_letter::unit_letter(const ex & d) : inherited(1,d)
  { }

  unit_letter::unit_letter(const ex & d, const ex & i) : inherited(1,d,i)
  { }

  // functions overriding virtual functions from bases classes
  void unit_letter::print(const print_context & c, unsigned level) const
  {
    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "\\frac{1}{";
	index.print(c,pow_precedence);
	c.s << "^{";
	degree.print(c,pow_precedence);
	c.s << "}}";
	if (precedence() <= level) c.s << ")}";
      } 
    else if (is_a<print_tree>(c)) 
      {
	inherited::print(c, level);
      } 
    else 
      {
	if (precedence() <= level) c.s << "(";
	c.s << "1";
	c.s << "/";
	index.print(c,pow_precedence);
	c.s << "^";
	degree.print(c,pow_precedence);
	if (precedence() <= level) c.s << ")";
      }
  }

  /**
   *
   * If the index is an integer, the object is evaluated explicitly.
   *
   */
  ex unit_letter::eval() const
  {

    if ( index.info(info_flags::integer) ) return this->eval_explicit();

    return this->hold();

  }

  /**
   *
   * Assumes that the indices are the same or equal to the default one.
   *
   *  The multiplication is performed according to
   *     \f[
   *        \frac{1}{i^{m_1}} \frac{1}{i^{m_2}} = \frac{1}{i^{m_1+m_2}}
   *     \f]
   *  and returns directly a unit_letter.
   *
   *  The result gets the index from the first letter, if this one differs from _default_index,
   *  otherwise the result gets the index from the second letter.
   *
   */
  ex unit_letter::concat_speedy(const ex & l) const
  {
    // second argument not a unit_letter ?
    if ( !is_a<unit_letter>(l) ) return letter::concat_speedy(l);

    const unit_letter& bl = ex_to<unit_letter>(l);

    // the indicies are now the same or equal to the default one
    ex new_index;
    if ( index.is_equal(_default_index) ) 
      {
	new_index = (bl.index);
      }
    else
      {
	new_index = index;
      }

    return create_unit_letter(degree+(bl.degree),new_index);

  }

} // namespace nestedsums

