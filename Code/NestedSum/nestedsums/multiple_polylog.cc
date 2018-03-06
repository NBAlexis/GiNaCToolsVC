
/** @file multiple_polylog.cc
 *
 * Implementation of multiple polylogs 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(multiple_polylog, Zsum)

GINAC_BIND_UNARCHIVER(multiple_polylog);



  multiple_polylog::multiple_polylog() : inherited(Infinity,_empty_list)
  { 
  }

  void multiple_polylog::archive(archive_node &node) const
  {
    inherited::archive(node);
  }

  void multiple_polylog::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);
  }

  int multiple_polylog::compare_same_type(const basic &other) const
  {
    const multiple_polylog &o = dynamic_cast<const multiple_polylog &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  multiple_polylog::multiple_polylog(const ex & llc) : inherited(Infinity,llc)
  { }

  // functions overriding virtual functions from bases classes
  void multiple_polylog::print(const print_context & c, unsigned level) const
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
	    c.s << "\\mbox{Li}_{" ;
	    for(i=0;i<depth;i++)
	      {
		ex_to<letter>(letter_list.op(i)).get_degree().print(c,mul_precedence); 
	      }
	    c.s << "}(" ;
	    ex_to<letter>(letter_list.op(0)).get_scale().print(c); 
	    for(i=1;i<depth;i++)
	      {
		c.s << "," ;
		ex_to<letter>(letter_list.op(i)).get_scale().print(c); 
	      }
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
	    c.s << "Li(" ;
	    ex_to<letter>(letter_list.op(0)).get_degree().print(c); 
	    for(i=1;i<depth;i++)
	      {
		c.s << "," ;
		ex_to<letter>(letter_list.op(i)).get_degree().print(c); 
	      }
	    c.s << "," ;
	    ex_to<letter>(letter_list.op(0)).get_scale().print(c); 
	    for(i=1;i<depth;i++)
	      {
		c.s << "," ;
		ex_to<letter>(letter_list.op(i)).get_scale().print(c); 
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
	    c.s << "\\mbox{Li}_{" ;
	    for(i=0;i<depth;i++)
	      {
		ex_to<letter>(letter_list.op(intdepth-1-i)).get_degree().print(c,mul_precedence); 
	      }
	    c.s << "}(" ;
	    ex_to<letter>(letter_list.op(intdepth-1)).get_scale().print(c); 
	    for(i=1;i<depth;i++)
	      {
		c.s << "," ;
		ex_to<letter>(letter_list.op(intdepth-1-i)).get_scale().print(c); 
	      }
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
	    c.s << "Li(" ;
	    ex_to<letter>(letter_list.op(intdepth-1)).get_degree().print(c); 
	    for(i=1;i<depth;i++)
	      {
		c.s << "," ;
		ex_to<letter>(letter_list.op(intdepth-1-i)).get_degree().print(c); 
	      }
	    c.s << "," ;
	    ex_to<letter>(letter_list.op(intdepth-1)).get_scale().print(c); 
	    for(i=1;i<depth;i++)
	      {
		c.s << "," ;
		ex_to<letter>(letter_list.op(intdepth-1-i)).get_scale().print(c); 
	      }
	    c.s << ")";
	    if (precedence() <= level) c.s << ")";
	  }
      } // end reversed order
  }

  /**
   *
   * The simplifications are done in the following order:
   *
   * - If all \f$x_j\f$'s are equal to 1, we have a multiple zeta value.
   *
   * - If all \f$x_j\f$'s are equal to 1 except \f$x_1\f$, we have a harmonic polylog.
   * 
   */
  ex multiple_polylog::eval() const
  {
    size_t depth = get_depth();

    // check if multiple polylog simplifies to multiple zeta value
    if ( depth==0 ) return create_multiple_zeta_value(letter_list);
    int i=0;
    while ( is_a<unit_letter>(letter_list.op(i++)) )
      {
	if ( i==depth) return create_multiple_zeta_value(letter_list);
      }

    // check if multiple polylog simplifies to harmonic polylog
    if ( depth > 0 )
      {
	if ( depth==1 ) return create_harmonic_polylog(letter_list);
	i=1;
	while ( is_a<unit_letter>(letter_list.op(i++)) )
	  {
	    if ( i==depth) return create_harmonic_polylog(letter_list);
	  }
      }

    return this->hold();
  }

  // new virtual functions 

  /**
   *
   * This method provides a simple numerical evaluation
   * routine for multiple polylogarithms.
   *
   * Multiple polylogarithms are evaluated as power series
   * up to an upper summation limit _NMAX.
   *
   * This is not a routine designed for performance.
   * It only provides a simple way to check a result
   * for a few selected points.
   *
   */
  ex multiple_polylog::eval_approx() const
  {
    size_t depth = get_depth();

    if ( depth==0 ) return 1;

    if ( depth==1 ) 
      {
	ex res = 0;
	ex x1 = ex_to<letter>(letter_list.op(0)).get_scale();
	ex m1 = ex_to<letter>(letter_list.op(0)).get_degree();
	for (int i1=1; i1 <= _NMAX; i1++)
	  {
	    res += pow(x1,i1) * pow(i1,-m1) ;
	  }
	return res;
      }

    if ( depth==2 ) 
      {
	ex res = 0;
	ex x1 = ex_to<letter>(letter_list.op(0)).get_scale();
	ex m1 = ex_to<letter>(letter_list.op(0)).get_degree();
	ex x2 = ex_to<letter>(letter_list.op(1)).get_scale();
	ex m2 = ex_to<letter>(letter_list.op(1)).get_degree();
	ex x12 = x1*x2;
	for (int i1=1; i1 <= _NMAX-1; i1++)
	  {
	    for ( int i2=1; i2 <= _NMAX-i1; i2++)
	      {
		res += pow(x1,i1) * pow(i1+i2,-m1) 
		  * pow(x12,i2) * pow(i2,-m2) ;
	      }
	  }
	return res;
      }

    if ( depth==3 ) 
      {
	ex res = 0;
	ex x1 = ex_to<letter>(letter_list.op(0)).get_scale();
	ex m1 = ex_to<letter>(letter_list.op(0)).get_degree();
	ex x2 = ex_to<letter>(letter_list.op(1)).get_scale();
	ex m2 = ex_to<letter>(letter_list.op(1)).get_degree();
	ex x3 = ex_to<letter>(letter_list.op(2)).get_scale();
	ex m3 = ex_to<letter>(letter_list.op(2)).get_degree();
	ex x12 = x1*x2;
	ex x123 = x12*x3;
	for (int i1=1; i1 <= _NMAX-2; i1++)
	  {
	    for ( int i2=1; i2 <= _NMAX-i1-1; i2++)
	      {
		for ( int i3=1; i3 <= _NMAX-i1-i2; i3++)
		  {
		    res += pow(x1,i1) * pow(i1+i2+i3,-m1) 
		      * pow(x12,i2) * pow(i2+i3,-m2) 
		      * pow(x123,i3) * pow(i3,-m3) ;
		  }
	      }
	  }
	return res;
      }

    if ( depth==4 ) 
      {
	ex res = 0;
	ex x1 = ex_to<letter>(letter_list.op(0)).get_scale();
	ex m1 = ex_to<letter>(letter_list.op(0)).get_degree();
	ex x2 = ex_to<letter>(letter_list.op(1)).get_scale();
	ex m2 = ex_to<letter>(letter_list.op(1)).get_degree();
	ex x3 = ex_to<letter>(letter_list.op(2)).get_scale();
	ex m3 = ex_to<letter>(letter_list.op(2)).get_degree();
	ex x4 = ex_to<letter>(letter_list.op(3)).get_scale();
	ex m4 = ex_to<letter>(letter_list.op(3)).get_degree();
	ex x12 = x1*x2;
	ex x123 = x12*x3;
	ex x1234 = x123*x4;
	for (int i1=1; i1 <= _NMAX-3; i1++)
	  {
	    for ( int i2=1; i2 <= _NMAX-i1-2; i2++)
	      {
		for ( int i3=1; i3 <= _NMAX-i1-i2-1; i3++)
		  {
		    for ( int i4=1; i4 <= _NMAX-i1-i2-i3; i4++)
		      {
			res += pow(x1,i1) * pow(i1+i2+i3+i4,-m1) 
			  * pow(x12,i2) * pow(i2+i3+i4,-m2)
			  * pow(x123,i3) * pow(i3+i4,-m3)
			  * pow(x1234,i4) * pow(i4,-m4) ;
		      }
		  }
	      }
	  }
	return res;
      }

    // default
    return *this;
  }

  // functions

  /**
   *
   * Evaluates an expression involving multiple polylog
   * with a rough and brute force evaluation routine.
   *
   * This is not a routine designed for performance.
   * It only provides a simple way to check a result
   * for a few selected points.
   *
   * The method eval_approx is called for the rough numerical
   * approximation.
   *
   */
  ex eval_multiple_polylog_approx(const ex & expr)
  {

    if ( is_a<multiple_polylog>(expr)) 
      {
	return ex_to<multiple_polylog>(expr).eval_approx();
      }

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = static_cast<int>(expr.nops());
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( eval_multiple_polylog_approx(expr.op(j)));
	  }

	if ( is_a<add>(expr) )
	  {
	    return (new add(res_exvector))->setflag(status_flags::dynallocated);
	  }
	else if ( is_a<mul>(expr) || is_a<ncmul>(expr) )
	  {
	    return (new ncmul(res_exvector))->setflag(status_flags::dynallocated);
	  }
      }

    // default
    return expr;
  }

} // namespace nestedsums

