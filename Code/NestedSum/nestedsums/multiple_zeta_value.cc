
/** @file multiple_zeta_value.cc
 *
 * Implementation of multiple zeta values
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

GINAC_IMPLEMENT_REGISTERED_CLASS(multiple_zeta_value, multiple_polylog)

GINAC_BIND_UNARCHIVER(multiple_zeta_value);



  multiple_zeta_value::multiple_zeta_value() : inherited()
  { 
  }

  void multiple_zeta_value::archive(archive_node &node) const
  {
    inherited::archive(node);
  }

  void multiple_zeta_value::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);
  }

  int multiple_zeta_value::compare_same_type(const basic &other) const
  {
    const multiple_zeta_value &o = dynamic_cast<const multiple_zeta_value &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  multiple_zeta_value::multiple_zeta_value(const ex & llc) : Zsum(Infinity,llc)
  { }

  // functions overriding virtual functions from bases classes
  return_type_t multiple_zeta_value::return_type_tinfo() const 
  {
    return _default_multiple_polylog.return_type_tinfo();
  }

  void multiple_zeta_value::print(const print_context & c, unsigned level) const
  {
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
    int intdepth = ex_to<numeric>(depth).to_int();

    if ( _print_format & print_format::no_reversed_order ) 
      {
	if (is_a<print_latex>(c)) 
	  {
	    if (precedence() <= level) c.s << "{(";
	    c.s << "\\zeta_{" ;
	    for(i=0;i<depth;i++)
	      {
		ex_to<letter>(letter_list.op(i)).get_degree().print(c,mul_precedence); 
	      }
	    c.s << "}" ;
	    if (precedence() <= level) c.s << ")}";
	  }
	else if (is_a<print_tree>(c)) 
	  {
	    inherited::print(c, level);
	  }
	else
	  {
	    if (precedence() <= level) c.s << "(";
	    c.s << "zeta(" ;
	    ex_to<letter>(letter_list.op(0)).get_degree().print(c); 
	    for(i=1;i<depth;i++)
	      {
		c.s << "," ;
		ex_to<letter>(letter_list.op(i)).get_degree().print(c); 
	      }
	    c.s << ")";
	    if (precedence() <= level) c.s << ")";
	  }
      }
    else // reversed order
      {
	if (is_a<print_latex>(c)) 
	  {
	    if (precedence() <= level) c.s << "{(";
	    c.s << "\\zeta_{" ;
	    for(i=0;i<depth;i++)
	      {
		ex_to<letter>(letter_list.op(intdepth-1-i)).get_degree().print(c,mul_precedence); 
	      }
	    c.s << "}" ;
	    if (precedence() <= level) c.s << ")}";
	  }
	else if (is_a<print_tree>(c)) 
	  {
	    inherited::print(c, level);
	  }
	else
	  {
	    if (precedence() <= level) c.s << "(";
	    c.s << "zeta(" ;
	    ex_to<letter>(letter_list.op(intdepth-1)).get_degree().print(c); 
	    for(i=1;i<depth;i++)
	      {
		c.s << "," ;
		ex_to<letter>(letter_list.op(intdepth-1-i)).get_degree().print(c); 
	      }
	    c.s << ")";
	    if (precedence() <= level) c.s << ")";
	  }
      } // reversed order
  }

  /**
   *
   * No simplifications implemented for multiple zeta values.
   * 
   */
  ex multiple_zeta_value::eval() const
  {

    return this->hold();

  }

} // namespace nestedsums

