
/** @file harmonic_polylog.cc
 *
 * Implementation of harmonic polylogs 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(harmonic_polylog, multiple_polylog)

GINAC_BIND_UNARCHIVER(harmonic_polylog);



  harmonic_polylog::harmonic_polylog() : inherited()
  { 
  }

  void harmonic_polylog::archive(archive_node &node) const
  {
    inherited::archive(node);
  }

  void harmonic_polylog::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);
    Zsum::read_archive(node, sym_lst);
  }

  int harmonic_polylog::compare_same_type(const basic &other) const
  {
    const harmonic_polylog &o = dynamic_cast<const harmonic_polylog &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  harmonic_polylog::harmonic_polylog(const ex & llc) : inherited(llc),
    Zsum(Infinity,llc)
  { }

  // functions overriding virtual functions from bases classes
  return_type_t harmonic_polylog::return_type_tinfo() const 
  {
    return _default_multiple_polylog.return_type_tinfo();
  }

  void harmonic_polylog::print(const print_context & c, unsigned level) const
  {
    if ( _print_format & print_format::no_harmonic_polylog ) return multiple_polylog::print(c,level);

    size_t depth = get_depth();

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

    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "\\mbox{H}_{" ;
	for(i=0;i<depth;i++)
	  {
	    ex_to<letter>(letter_list.op(i)).get_degree().print(c,mul_precedence); 
	  }
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
	c.s << "H(" ;
	ex_to<letter>(letter_list.op(0)).get_degree().print(c); 
	for(i=1;i<depth;i++)
	  {
	    c.s << "," ;
	    ex_to<letter>(letter_list.op(i)).get_degree().print(c); 
	  }
	c.s << "," ;
	ex_to<letter>(letter_list.op(0)).get_scale().print(c); 
	c.s << ")";
	if (precedence() <= level) c.s << ")";
      }
  }

  /**
   *
   * The simplifications are done in the following order:
   *
   * - If all degrees are equal to 1 except the first one, we have a Nielsen polylog.
   *
   */
  ex harmonic_polylog::eval() const
  {
    size_t depth = get_depth();

    // check if harmonic polylog simplifies to a Nielsen polylog
    if ( depth > 0 )
      {
	if ( depth==1 ) return create_nielsen_polylog(letter_list);
	int i=1;
	while ( ex_to<letter>(letter_list.op(i++)).get_degree().is_equal(1) )
	  {
	    if ( i==depth) return create_nielsen_polylog(letter_list);
	  }
      }

    return this->hold();
  }

} // namespace nestedsums

