
/** @file nielsen_polylog.cc
 *
 * Implementation of Nielsen's polylogs 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(nielsen_polylog, harmonic_polylog)

GINAC_BIND_UNARCHIVER(nielsen_polylog);



  nielsen_polylog::nielsen_polylog() : inherited()
  { 
  }

  void nielsen_polylog::archive(archive_node &node) const
  {
    inherited::archive(node);
  }

  void nielsen_polylog::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);
    Zsum::read_archive(node, sym_lst);
  }

  int nielsen_polylog::compare_same_type(const basic &other) const
  {
    const nielsen_polylog &o = dynamic_cast<const nielsen_polylog &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  nielsen_polylog::nielsen_polylog(const ex & llc) : inherited(llc),
    Zsum(Infinity,llc)
  { }


  // functions overriding virtual functions from bases classes
  void nielsen_polylog::print(const print_context & c, unsigned level) const
  {
    if ( _print_format & print_format::no_nielsen_polylog ) return multiple_polylog::print(c,level);

    unsigned depth = get_depth();

    // empty sum equals 1
    if (depth == 0) 
      {
	if (is_a<print_latex>(c)) 
	  {
	    if (precedence() <= level) c.s << "{(";
	    c.s << "Z(" ;
	    n.print(c);
	    c.s << ")";
	    if (precedence() <= level) c.s << ")}";
	  }
	else if (is_a<print_tree>(c)) 
	  {
	    inherited::print(c, level);
	  }
	else
	  {
	    if (precedence() <= level) c.s << "(";
	    c.s << "Z(" ;
	    n.print(c);
	    c.s << ")";
	    if (precedence() <= level) c.s << ")";
	  }
	return;
      }

    int i;
    ex temp_depth = depth;

    if (is_a<print_latex>(c))
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "\\mbox{S}_{" ;
	ex nn = ex_to<letter>(letter_list.op(0)).get_degree() - 1;
	nn.print(c,mul_precedence); 
	c.s << ",";
	temp_depth.print(c);
	c.s << "}(" ;
	ex_to<letter>(letter_list.op(0)).get_scale().print(c); 
	c.s << ")";
	if (precedence() <= level) c.s << ")}";
	}
    else if (is_a<print_tree>(c)) 
      {
	inherited::print(c, level);
      }
    else
      {
	if (precedence() <= level) c.s << "(";
	c.s << "S(" ;
	ex nn = ex_to<letter>(letter_list.op(0)).get_degree() - 1;
	nn.print(c,mul_precedence); 
	c.s << ",";
	temp_depth.print(c);
	c.s << ",";
	ex_to<letter>(letter_list.op(0)).get_scale().print(c); 
	c.s << ")";
	if (precedence() <= level) c.s << ")";
      }
  }

  /**
   *
   * The simplifications are done in the following order:
   *
   * - If the depth equals 1, we have a classical polylog.
   *
   */
  ex nielsen_polylog::eval() const
  {
    // check if Nielsen polylog simplifies to a classical polylog
    if ( get_depth() == 1 ) return create_classical_polylog(letter_list);

    return this->hold();

  }

} // namespace nestedsums

