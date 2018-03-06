
/** @file polygamma.cc
 *
 * Implementation of ratio_of_tgamma
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
#include "utils.h"

#ifdef _DEBUG
#include <ctime>
#endif // def _DEBUG

namespace nestedsums {

using namespace GiNaC;

GINAC_IMPLEMENT_REGISTERED_CLASS(ratio_of_tgamma, basic)

GINAC_BIND_UNARCHIVER(ratio_of_tgamma);



  ratio_of_tgamma::ratio_of_tgamma() : inherited(),
   a1(0), b1(0), a2(0), b2(0), index(_default_index), expansion_parameter(_default),
   order(0), flag_expand_status(expand_status::no_eval_to_scalar)
  { 
  }

  void ratio_of_tgamma::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("a1",a1);
    node.add_ex("b1",b1);
    node.add_ex("a2",a2);
    node.add_ex("b2",b2);
    node.add_ex("index",index);
    node.add_ex("expansion_parameter",expansion_parameter);

    node.add_ex("order",numeric(order));
    node.add_ex("flag_expand_status",numeric(flag_expand_status));
  }

  void ratio_of_tgamma::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("a1",a1,sym_lst);
    node.find_ex("b1",b1,sym_lst);
    node.find_ex("a2",a2,sym_lst);
    node.find_ex("b2",b2,sym_lst);
    node.find_ex("index",index,sym_lst);
    node.find_ex("expansion_parameter",expansion_parameter,sym_lst);

    ex ex_order, ex_flag_expand_status;
    node.find_ex("order",ex_order,sym_lst);
    node.find_ex("flag_expand_status",ex_flag_expand_status,sym_lst);
    order = ex_to<numeric>(ex_order).to_int();
    flag_expand_status = ex_to<numeric>(ex_flag_expand_status).to_int();
  }

  int ratio_of_tgamma::compare_same_type(const basic &other) const
  {
    const ratio_of_tgamma &o = static_cast<const ratio_of_tgamma &>(other);

    int cmpval;

    cmpval = index.compare(o.index);

    if( cmpval ) return cmpval;


    cmpval = a1.compare(o.a1);

    if( cmpval ) return cmpval;

    cmpval = a2.compare(o.a2);

    if( cmpval ) return cmpval;

    cmpval = b1.compare(o.b1);

    if( cmpval ) return cmpval;

    cmpval = b2.compare(o.b2);

    if( cmpval ) return cmpval;


    if ( order != o.order )
      {
	return (order > o.order) ? 1 : -1;
      } 

    if ( flag_expand_status != o.flag_expand_status )
      {
	return (flag_expand_status > o.flag_expand_status) ? 1 : -1;
      } 

    return expansion_parameter.compare(o.expansion_parameter);

  }

  // other ctors

  ratio_of_tgamma::ratio_of_tgamma(const ex & aa1, const ex & bb1, const ex & aa2, const ex & bb2) : 
    inherited(), a1(aa1), b1(bb1), a2(aa2), b2(bb2), 
    index(_default_index), expansion_parameter(_default), order(0), 
    flag_expand_status(expand_status::no_eval_to_scalar)
  { }

  ratio_of_tgamma::ratio_of_tgamma(const ex & aa1, const ex & bb1, const ex & aa2, const ex & bb2, 
				   const ex & i, const ex & eps, 
				   int o, int f) : inherited(),
						   a1(aa1), b1(bb1), a2(aa2), b2(bb2),
						   index(i), expansion_parameter(eps),
						   order(o), flag_expand_status(f)
  { }


  // functions overriding virtual functions from bases classes

  unsigned ratio_of_tgamma::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= a1.gethash();

      v = rotate_left_31(v);
      v ^= b1.gethash();

      v = rotate_left_31(v);
      v ^= a2.gethash();

      v = rotate_left_31(v);
      v ^= b2.gethash();

      v = rotate_left_31(v);
      v ^= index.gethash();

      v = rotate_left_31(v);
      v ^= expansion_parameter.gethash();

      // mask out numeric hashes:
      v &= 0x7FFFFFFFU;
	
      // store calculated hash value only if object is already evaluated
      if (flags & status_flags::evaluated) 
	{
	  setflag(status_flags::hash_calculated);
	  hashvalue = v;
	}

      return v;
    }

  void ratio_of_tgamma::print(const print_context & c, unsigned level) const
  {
	if (is_a<print_latex>(c)) {
	  c.s << "\\frac{\\Gamma(1+";
	  b2.print(c,mul_precedence);
	  c.s << " " ;
	  expansion_parameter.print(c,mul_precedence);
	  c.s << ")}{\\Gamma(1+";
	  b1.print(c,mul_precedence);
	  c.s << " " ;
	  expansion_parameter.print(c,mul_precedence);
	  c.s << ")}";
	  c.s << "\\frac{\\Gamma(";
	  index.print(c,add_precedence);
	  c.s << "+";
	  a1.print(c,add_precedence);
	  c.s << "+";
	  b1.print(c,mul_precedence);
	  c.s << " " ;
	  expansion_parameter.print(c,mul_precedence);
	  c.s << ")}{\\Gamma(";
	  index.print(c,add_precedence);
	  c.s << "+";
	  a2.print(c,add_precedence);
	  c.s << "+";
	  b2.print(c,mul_precedence);
	  c.s << " " ;
	  expansion_parameter.print(c,mul_precedence);
	  c.s << ")}";
	} 	
	else if (is_a<print_tree>(c)) 
	  {
	    c.s << std::string(level, ' ') << class_name()
		<< std::hex << ", hash=0x" << hashvalue << ", flags=0x" << flags << std::dec
		<< ", nops=" << nops()
		<< ", order=" << order
		<< ", flag_expand_status=" << flag_expand_status
		<< std::endl;
	    a1.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	    b1.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	    a2.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	    b2.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	    index.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	    expansion_parameter.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	  } else {
	  c.s << "Gamma(1+";
	  b2.print(c,mul_precedence);
	  c.s << "*" ;
	  expansion_parameter.print(c,mul_precedence);
	  c.s << ")/Gamma(1+";
	  b1.print(c,mul_precedence);
	  c.s << "*" ;
	  expansion_parameter.print(c,mul_precedence);
	  c.s << ")*";
	  c.s << "Gamma(";
	  index.print(c,add_precedence);
	  c.s << "+";
	  a1.print(c,add_precedence);
	  c.s << "+";
	  b1.print(c,mul_precedence);
	  c.s << "*" ;
	  expansion_parameter.print(c,mul_precedence);
	  c.s << ")/Gamma(";
	  index.print(c,add_precedence);
	  c.s << "+";
	  a2.print(c,add_precedence);
	  c.s << "+";
	  b2.print(c,mul_precedence);
	  c.s << "*" ;
	  expansion_parameter.print(c,mul_precedence);
	  c.s << ")";
	}

  }

  /**
   *
   * If the flag flag_expand_status is set, the object is expanded in \f$\varepsilon\f$.
   *
   * If \f$a_1\f$ and \f$a_2\f$ are zero, we have
   * \f[
   *    \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(i+b_1\varepsilon)}{\Gamma(i+b_2\varepsilon)}
   *   = \frac{ 1 + b_1 \varepsilon Z_1(i-1) + ...}{1 + b_2 \varepsilon Z_1(i-1) + ...}
   * \f]
   * Here the formula 
   * \f[
   * \left( 1 + \varepsilon Z_1(i-1) + \varepsilon^2 Z_{11}(i-1) + ... \right)^{-1}
   * = 1 - \varepsilon S_1(i-1) + \varepsilon^2 S_{11}(i-1) - ...
   * \f]
   * is useful.
   *
   * If \f$a_1 > 0\f$ we have
   * \f[
   *    \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+a_2+b_2\varepsilon)}
   *    = \left( i + a_1 -1 + b_1 \varepsilon \right)
   *        \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *        \frac{\Gamma(i+a_1-1+b_1\varepsilon)}{\Gamma(i+a_2+b_2\varepsilon)}
   * \f]
   * \f$i\f$ is interpreted as unit_letter(-1,index). The order parameter of ratio_of_tgamma
   * of the \f$b_1 \varepsilon\f$ term is decreased by one due to the explicit presence of \f$\varepsilon\f$.
   *
   * If \f$a_1 < 0\f$ we have
   * \f[
   *    \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+a_2+b_2\varepsilon)}
   *    = \sum\limits_{j=0}^\infty \frac{1}{(i+a_1)^{j+1}} \left(-b_1\right)^j \varepsilon^j
   *        \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *        \frac{\Gamma(i+a_1+1+b_1\varepsilon)}{\Gamma(i+a_2+b_2\varepsilon)}
   * \f]
   * The order parameter is adjusted according to the prefactors of \f$\varepsilon\f$.
   * Note that this formula might give rise to poles for \f$i+a_1=0\f$. 
   * These possible poles have to be dealt with at a higher level.
   *
   * If \f$a_2 > 0\f$ we have
   * \f[
   *    \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+a_2+b_2\varepsilon)}
   *    = \sum\limits_{j=0}^\infty \frac{1}{(i+a_2-1)^{j+1}} \left(-b_2\right)^j \varepsilon^j
   *        \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *        \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+a_2-1+b_2\varepsilon)}
   * \f]
   * The order parameter is adjusted according to the prefactors of \f$\varepsilon\f$.
   *
   * If \f$a_2 < 0\f$ we have
   * \f[
   *    \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+a_2+b_2\varepsilon)}
   *    = \left( i + a_2 + b_2 \varepsilon \right)
   *        \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *        \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+a_2+1+b_2\varepsilon)}
   * \f]
   * The order parameter is adjusted according to the prefactors of \f$\varepsilon\f$.
   *
   * The return type is either Zsum or basic_letter * Zsum.
   * If \f$a_1 \ge 0 \f$ we do not get any poles.
   *
   * If the index is an integer and the status flag not equal to no_eval_to_scalar, the object is evaluated explicitly.
   *
   */
  ex ratio_of_tgamma::eval() const
  {

    if ( flag_expand_status==expand_status::expansion_required )
      {
	if ( a1.info(info_flags::integer) && a2.info(info_flags::integer) )
	  {
	    // standard form 
	    if ( (a1.is_zero()) && (a2.is_zero()) )
	      {
		// need at least order=1 for a non-zero result
		if ( order < 1 ) return 0;

		int j;
		// j=0 term separate to avoid problems with 0^0
		// have to create a unit in the algebra
		ex numerator = create_Euler_Zagier_sum(index-1,_empty_list);
		ex denominator = create_Euler_Zagier_sum(index-1,_empty_list);
		for (j=1;j<order;j++)
		  {
		    numerator = numerator+ GiNaC::pow(b1,j)*GiNaC::pow(expansion_parameter,j)
		      *create_Euler_Zagier_sum_with_ones(index-1,j);
		    denominator = denominator+ GiNaC::pow(-1,j)*GiNaC::pow(b2,j)*GiNaC::pow(expansion_parameter,j)
		      *convert_Ssum_to_Zsum(create_harmonic_sum_with_ones(index-1,j));
		  }

		// we don't get any poles here
		return nestedsums_helper_multiply_via_triangle(numerator,denominator,expansion_parameter,order);

	      }

	    // reduce a1
	    if ( a1.info(info_flags::posint) )
	      {
		ex new_ratio = decrease_numerator();
		return create_unit_letter(-1,index)*new_ratio
		  + (a1-1)*new_ratio
		  + b1*expansion_parameter*decrease_numerator(-1);
	      }

	    if ( a1.info(info_flags::negint) )
	      {
		// case index  > -a1
		//
		// better handle this case already before expansion_required is set
		int j;
		ex res = create_basic_letter(1,1,a1,index)*increase_numerator();
		for (j=1;j<order;j++)
		  {
		    res = res + GiNaC::pow(expansion_parameter,j)*GiNaC::pow(-1,j)*GiNaC::pow(b1,j)
		      *create_basic_letter(1,j+1,a1,index)*increase_numerator(-j);
		  }
		return res;
	      }

	    // reduce a2
	    if ( a2.info(info_flags::posint) )
	      {
		// case i > 1 - a2
		// for i>0 and a2>0 always true
		int j;
		ex res = create_basic_letter(1,1,a2-1,index)*decrease_denominator();
		for (j=1;j<order;j++)
		  {
		    res = res + GiNaC::pow(expansion_parameter,j)*GiNaC::pow(-1,j)*GiNaC::pow(b2,j)
		      *create_basic_letter(1,j+1,a2-1,index)*decrease_denominator(-j);
		  }
		return res;
	      }

	    if ( a2.info(info_flags::negint) )
	      {
		ex new_ratio = increase_denominator();
		return create_unit_letter(-1,index)*new_ratio
		  + a2*new_ratio
		  + b2*expansion_parameter*increase_denominator(-1);
	      }

	  } // end if a1 and a2 integer

      } // end if expansion_required

    if ( ( index.info(info_flags::integer) ) 
	 && (flag_expand_status != expand_status::no_eval_to_scalar)) return this->eval_explicit();

    // default
    return this->hold();

  }

  /**
   *
   * No automatic simplifications
   *
   */
  ex ratio_of_tgamma::eval_ncmul(const exvector & v) const
  {
    // default
    return hold_ncmul(v);
  }

  ex ratio_of_tgamma::derivative(const symbol & s) const
  {
    return 0;
  }

  ex ratio_of_tgamma::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_ratio_of_tgamma(a1.subs(m,options),b1.subs(m,options),a2.subs(m,options),b2.subs(m,options),index.subs(m,options),
				  expansion_parameter.subs(m,options),order,flag_expand_status);
  }

  // new virtual functions


  /**
   *
   * Explicit evaluation with the help of nestedsums_helper_expand_tgamma_fct.
   *
   */
  ex ratio_of_tgamma::eval_explicit() const
  {
    if ( index.info(info_flags::integer) )
      {
	return nestedsums_helper_expand_lst_tgamma_fct(
	       lst{index+a1+b1*expansion_parameter,1+b2*expansion_parameter},
	       lst{index+a2+b2*expansion_parameter,1+b1*expansion_parameter},
						       expansion_parameter,order);
      } // end if index is integer

    // default
    return this->hold();
  }

  // non-virual functions

  /**
   *
   * Sets the flag expansion_required.
   * The object is then automatically expanded up to the order specified in the
   * member variable order.
   *
   */
  ex ratio_of_tgamma::set_expansion(void) const
  {
    ratio_of_tgamma* res = new ratio_of_tgamma(a1,b1,a2,b2,index,expansion_parameter,order,expand_status::expansion_required);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Sets the member variable index to new_index.
   *
   */
  ex ratio_of_tgamma::set_index(const ex & new_index) const
  {
    ratio_of_tgamma* res = new ratio_of_tgamma(a1,b1,a2,b2,new_index,expansion_parameter,order,flag_expand_status);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Sets the member variable expansion_parameter to new_eps.
   *
   */
  ex ratio_of_tgamma::set_expansion_parameter(const ex & new_eps) const
  {
    ratio_of_tgamma* res = new ratio_of_tgamma(a1,b1,a2,b2,index,new_eps,order,flag_expand_status);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Sets the member variable order to new_order.
   *
   */
  ex ratio_of_tgamma::set_order(int new_order) const
  {
    ratio_of_tgamma* res = new ratio_of_tgamma(a1,b1,a2,b2,index,expansion_parameter,new_order,flag_expand_status);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Sets the member variable flag_expand_status to new_flag
   *
   */
  ex ratio_of_tgamma::set_flag(int new_flag) const
  {
    ratio_of_tgamma* res = new ratio_of_tgamma(a1,b1,a2,b2,index,expansion_parameter,order,new_flag);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Sets the member variables index, expansion_parameter and order to new values.
   *
   */
  ex ratio_of_tgamma::set_values(const ex & new_index, const ex & new_eps, int new_order, int new_flag) const
  {
    ratio_of_tgamma* res = new ratio_of_tgamma(a1,b1,a2,b2,new_index,new_eps,new_order,new_flag);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Returns the index.
   *
   */
  ex ratio_of_tgamma::get_index(void) const
  {
    return index;
  }

  /**
   *
   * Returns
   *  \f[
   *     \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *     \frac{\Gamma(i+a_1+1+b_1\varepsilon)}{\Gamma(i+a_2+b_2\varepsilon)}
   *  \f]
   *
   * The order variable is adjusted according to
   * order = order + shift_order.
   *
   */
  ex ratio_of_tgamma::increase_numerator(int shift_order) const
  {
    if ( (order+shift_order) == 0 ) return 0;

    ratio_of_tgamma* res = new ratio_of_tgamma(a1+1,b1,a2,b2,index,expansion_parameter,order+shift_order,flag_expand_status);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Returns
   *  \f[
   *     \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *     \frac{\Gamma(i+a_1-1+b_1\varepsilon)}{\Gamma(i+a_2+b_2\varepsilon)}
   *  \f]
   *
   * The order variable is adjusted according to
   * order = order + shift_order.
   *
   */
  ex ratio_of_tgamma::decrease_numerator(int shift_order) const
  {
    if ( (order+shift_order) == 0 ) return 0;

    ratio_of_tgamma* res = new ratio_of_tgamma(a1-1,b1,a2,b2,index,expansion_parameter,order+shift_order,flag_expand_status);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Returns
   *  \f[
   *     \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *     \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+a_2+1+b_2\varepsilon)}
   *  \f]
   *
   * The order variable is adjusted according to
   * order = order + shift_order.
   *
   */
  ex ratio_of_tgamma::increase_denominator(int shift_order) const
  {
    if ( (order+shift_order) == 0 ) return 0;

    ratio_of_tgamma* res = new ratio_of_tgamma(a1,b1,a2+1,b2,index,expansion_parameter,order+shift_order,flag_expand_status);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Returns
   *  \f[
   *     \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *     \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+a_2-1+b_2\varepsilon)}
   *  \f]
   *
   * The order variable is adjusted according to
   * order = order + shift_order.
   *
   */
  ex ratio_of_tgamma::decrease_denominator(int shift_order) const
  {
    if ( (order+shift_order) == 0 ) return 0;

    ratio_of_tgamma* res = new ratio_of_tgamma(a1,b1,a2-1,b2,index,expansion_parameter,order+shift_order,flag_expand_status);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Returns
   * \f[
   *    \sum\limits_{j=0}^\infty \frac{1}{(i+a_1)^{j+1}} \left(-b_1\right)^j \varepsilon^j
   * \f]
   *
   */
  ex ratio_of_tgamma::prefactor_increase_numerator(void) const
  {
    // case index  > -a1
    //
    // better handle this case already before expansion_required is set
    int j;
    ex res = create_basic_letter(1,1,a1,index);
    for (j=1;j<order;j++)
      {
	res = res + GiNaC::pow(expansion_parameter,j)*GiNaC::pow(-1,j)*GiNaC::pow(b1,j)
	  *create_basic_letter(1,j+1,a1,index);
      }
    return res;
  }

  /**
   *
   * Returns
   * \f[
   *     \left(i + a_1-1 \right) +b_1 \varepsilon  i^0
   * \f]
   *
   */
  ex ratio_of_tgamma::prefactor_decrease_numerator(void) const
  {
    return create_basic_letter((ex) 1, -1, a1-1, index)
      + b1*expansion_parameter * create_unit_letter((ex) 0,index);
  }

  /**
   *
   * Returns
   * \f[
   *    i + a_2 i^0 + b_2 \varepsilon i^0
   * \f]
   */
  ex ratio_of_tgamma::prefactor_increase_denominator(void) const
  {
    // 07.03.2002  (i+a2) + b2 eps i^0 -> i + a2 i^0 + b2 eps i^0
    return create_letter((ex) 1, -1, index)
      + a2 * create_unit_letter((ex) 0,index)
      + b2*expansion_parameter * create_unit_letter((ex) 0,index);
  }

  /**
   *
   * Returns
   * \f[
   *    \sum\limits_{j=0}^\infty \frac{1}{(i+a_2-1)^{j+1}} \left(-b_2\right)^j \varepsilon^j
   * \f]
   *
   */
  ex ratio_of_tgamma::prefactor_decrease_denominator(void) const
  {
    // case i > 1 - a2
    // for i>0 and a2>0 always true
    int j;
    ex res = create_basic_letter(1,1,a2-1,index);
    for (j=1;j<order;j++)
      {
	res = res + GiNaC::pow(expansion_parameter,j)*GiNaC::pow(-1,j)*GiNaC::pow(b2,j)
	  *create_basic_letter(1,j+1,a2-1,index);
      }
    return res;
  }

  /**
   *
   * Returns
   * \f[
   *    \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(i+a_1+1+b_1 \varepsilon)}{\Gamma(i+a_2+1+b_2 \varepsilon)}
   * \f]
   * The order parameter is not changed.
   *
   */
  ex ratio_of_tgamma::shift_plus_one(void) const
  {
    ratio_of_tgamma* res = new ratio_of_tgamma(a1+1,b1,a2+1,b2,index,expansion_parameter,order,flag_expand_status);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Returns
   * \f[
   *    \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(i+a_1-1+b_1 \varepsilon)}{\Gamma(i+a_2-1+b_2 \varepsilon)}
   * \f]
   * The order parameter is not changed.
   *
   */
  ex ratio_of_tgamma::shift_minus_one(void) const
  {
    ratio_of_tgamma* res = new ratio_of_tgamma(a1-1,b1,a2-1,b2,index,expansion_parameter,order,flag_expand_status);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Returns the expansions of
   * \f[
   *    \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(a_1+1+b_1 \varepsilon)}{\Gamma(a_2+1+b_2 \varepsilon)}
   * \f]
   * up to order + shift_order.
   *
   */
  ex ratio_of_tgamma::index_eq_one(void) const
  {
    return this->set_index(1);
  }

  /**
   *
   * Returns a ratio_of_tgamma with
   * \f[
   *    \Gamma(i + a + o + b \varepsilon )
   * \f]
   * with \f$ o = j-i\f$, where \f$i\f$ is the new index and \f$j\f$ is the old index.
   *
   */
  ex ratio_of_tgamma::shift_index(const ex & new_index) const
  {
    ex offset = index - new_index;

    return create_ratio_of_tgamma(a1+offset,b1,a2+offset,b2,new_index,expansion_parameter,order,flag_expand_status);
  }

  /**
   *
   * Returns 1 if \f$a_1 < 0 \f$, and 0 otherwise.
   *
   */
  int ratio_of_tgamma::pole_alert(void) const
  {
    if ( a1.info(info_flags::negint) ) return 1;

    return 0;
  }

  /**
   *
   * Returns 1 if \f$a_1\f$ or \f$a_2\f$ are not integers, and 0 otherwise.
   *
   */
  int ratio_of_tgamma::expansion_alert(void) const
  {
    if ( a1.info(info_flags::integer) && a2.info(info_flags::integer) ) return 0;

    return 1;
  }

  // utility functions

  /**
   *
   * Sets the status flag of ratio_of_tgamma objects to eval_to_scalar.
   * Ratio_of_tgamma objects with integer index are then evaluated explicitly.
   * 
   */
  ex eval_ratio_of_tgamma_to_scalar(const ex & expr)
  {

    if ( is_a<ratio_of_tgamma>(expr)) 
      {
	return ex_to<ratio_of_tgamma>(expr).set_flag(expand_status::eval_to_scalar);
      }

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = static_cast<int>(expr.nops());
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( eval_ratio_of_tgamma_to_scalar(expr.op(j)));
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

