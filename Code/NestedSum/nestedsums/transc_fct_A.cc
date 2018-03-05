
/** @file transc_fct_A.cc
 *
 * Implementation of transcendental_fct_type_A
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

GINAC_IMPLEMENT_REGISTERED_CLASS(transcendental_fct_type_A, basic)

GINAC_BIND_UNARCHIVER(transcendental_fct_type_A);


  transcendental_fct_type_A::transcendental_fct_type_A() : inherited(),
   x(_default), i_num(_empty_list), i_denom(_empty_list), pre_num(_empty_list), pre_denom(_empty_list),
   expansion_parameter(_default), order(0), flag_expand_status(expand_status::start)
  { 
  }

  void transcendental_fct_type_A::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("x",x);
    node.add_ex("i_num",i_num);
    node.add_ex("i_denom",i_denom);
    node.add_ex("pre_num",pre_num);
    node.add_ex("pre_denom",pre_denom);
    node.add_ex("expansion_parameter",expansion_parameter);

    node.add_ex("order",numeric(order));
    node.add_ex("flag_expand_status",numeric(flag_expand_status));
  }

  void transcendental_fct_type_A::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("x",x,sym_lst);
    node.find_ex("i_num",i_num,sym_lst);
    node.find_ex("i_denom",i_denom,sym_lst);
    node.find_ex("pre_num",pre_num,sym_lst);
    node.find_ex("pre_denom",pre_denom,sym_lst);
    node.find_ex("expansion_parameter",expansion_parameter,sym_lst);

    ex ex_order, ex_flag_expand_status;
    node.find_ex("order",ex_order,sym_lst);
    node.find_ex("flag_expand_status",ex_flag_expand_status,sym_lst);
    order = ex_to<numeric>(ex_order).to_int();
    flag_expand_status = ex_to<numeric>(ex_flag_expand_status).to_int();
  }

  int transcendental_fct_type_A::compare_same_type(const basic &other) const
  {
    const transcendental_fct_type_A &o = static_cast<const transcendental_fct_type_A &>(other);

    int cmpval;

    cmpval = x.compare(o.x);

    if( cmpval ) return cmpval;

    cmpval = i_num.compare(o.i_num);

    if( cmpval ) return cmpval;

    cmpval = i_denom.compare(o.i_denom);

    if( cmpval ) return cmpval;

    cmpval = pre_num.compare(o.pre_num);

    if( cmpval ) return cmpval;

    cmpval = pre_denom.compare(o.pre_denom);

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
  transcendental_fct_type_A::transcendental_fct_type_A(const ex & xx, const ex & ii_num, const ex & ii_denom, const ex & pp_num, const ex & pp_denom) : 
    inherited(), 
   x(xx), i_num(ii_num), i_denom(ii_denom), pre_num(pp_num), pre_denom(pp_denom),
   expansion_parameter(_default), order(0), flag_expand_status(expand_status::start)
  { }

  transcendental_fct_type_A::transcendental_fct_type_A(const ex & xx, const ex & ii_num, const ex & ii_denom, const ex & pp_num, const ex & pp_denom, const ex & eps, int o, int f) : 
    inherited(), 
   x(xx), i_num(ii_num), i_denom(ii_denom), pre_num(pp_num), pre_denom(pp_denom),
   expansion_parameter(eps), order(o), flag_expand_status(f)
  { }

  // functions overriding virtual functions from bases classes

  unsigned transcendental_fct_type_A::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= x.gethash();

      v = rotate_left_31(v);
      v ^= i_num.gethash();

      v = rotate_left_31(v);
      v ^= i_denom.gethash();

      v = rotate_left_31(v);
      v ^= pre_num.gethash();

      v = rotate_left_31(v);
      v ^= pre_denom.gethash();

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

  void transcendental_fct_type_A::print(const print_context & c, unsigned level) const
  {
    if (is_a<print_latex>(c)) {
      if (precedence() <= level) c.s << "{(";
      c.s << "\\mbox{TFA}(" ;
      x.print(c);
      c.s << ",";
      i_num.print(c);
      c.s << ",";
      i_denom.print(c);
      c.s << ",";
      pre_num.print(c);
      c.s << ",";
      pre_denom.print(c);
      c.s << ")";
      if (precedence() <= level) c.s << ")}";
    } 
    else if (is_a<print_tree>(c)) 
      {
	c.s << std::string(level, ' ') << class_name()
	    << std::hex << ", hash=0x" << hashvalue << ", flags=0x" << flags << std::dec
	    << ", nops=" << nops()
	    << ", order=" << order
	    << ", flag_expand_status=" << flag_expand_status
	    << std::endl;
	x.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	i_num.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	i_denom.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	pre_num.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	pre_denom.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	expansion_parameter.print(c, level + static_cast<const print_tree &>(c).delta_indent);
      } 
    else {
      c.s << "TFA(" ;
      x.print(c);
      c.s << ",";
      i_num.print(c);
      c.s << ",";
      i_denom.print(c);
      c.s << ",";
      pre_num.print(c);
      c.s << ",";
      pre_denom.print(c);
      c.s << ")";
    }
  }

  /**
   *
   * Evaluation: If flag_expand_status is set, the object is expanded
   * in \f$\varepsilon\f$.
   *
   * The result is converted to a standard form, using convert_Zsums_to_standard_form.
   *
   */
  ex transcendental_fct_type_A::eval() const
  {
#ifdef _DEBUG
    time_t time_start;
    time_t time_end;
#endif // def _DEBUG

    // ---------------
    if ( ( flag_expand_status == expand_status::expansion_required )
	 && ( flag_expand_status < _nestedsums_evaluation_veto ) )
      {
#ifdef _DEBUG
	// measuring time starts here
	time(&time_start);
#endif // def _DEBUG

	int k;
	int pre_low_degree,sum_low_degree;
	ex temp_num, temp_denom;
	ex index, sum_A;

	lst lst_pre_num = ex_to<lst>(pre_num);
	lst lst_pre_denom = ex_to<lst>(pre_denom);

	lst lst_i_num = ex_to<lst>(i_num);
	lst lst_i_denom = ex_to<lst>(i_denom);
	lst_i_denom.append(1);

#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_A, part 1, time in seconds : " << difftime(time_end,time_start) << std::endl;
#endif // def _DEBUG
	
	// ---------------------------------------
	// term i=0 

#ifdef _DEBUG
	// measuring time starts here
	time(&time_start);
#endif // def _DEBUG

	lst t_0_pre_num = lst_pre_num;
	lst t_0_pre_denom = lst_pre_denom;

	for ( k=0;k<lst_i_num.nops();k++)
	  {
	    t_0_pre_num.append(lst_i_num.op(k));
	    t_0_pre_denom.append(lst_i_denom.op(k));
	  }

	ex term_0 = create_Zsum(Infinity,_empty_list)
	  * nestedsums_helper_expand_lst_tgamma_fct(t_0_pre_num, t_0_pre_denom, expansion_parameter, order);

#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_A, part 2, time in seconds : " << difftime(time_end,time_start) << std::endl;
#endif // def _DEBUG
	
	// ---------------------------------------
	// term i>0

#ifdef _DEBUG
	// measuring time starts here
	time(&time_start);
#endif // def _DEBUG

	// prefactor
	lst t_1_pre_num = lst_pre_num;
	lst t_1_pre_denom = lst_pre_denom;

	// gamma sequence
	lst t_1_gammas;
	for ( k=0;k<lst_i_num.nops();k++)
	  {
	    temp_num = nestedsums_helper_expand(lst_i_num.op(k));
	    temp_num = temp_num.collect(expansion_parameter);

	    temp_denom = nestedsums_helper_expand(lst_i_denom.op(k));
	    temp_denom = temp_denom.collect(expansion_parameter);

	    t_1_pre_num.append(1+temp_num.coeff(expansion_parameter,1)*expansion_parameter);
	    t_1_pre_denom.append(1+temp_denom.coeff(expansion_parameter,1)*expansion_parameter);

	    t_1_gammas.append(create_ratio_of_tgamma(temp_num.coeff(expansion_parameter,0), 
						     temp_num.coeff(expansion_parameter,1),
						     temp_denom.coeff(expansion_parameter,0),
						     temp_denom.coeff(expansion_parameter,1) ));
	  }

	ex term_1_pre = nestedsums_helper_expand_lst_tgamma_fct(t_1_pre_num, t_1_pre_denom, expansion_parameter, order);
	pre_low_degree = nestedsums_helper_ldegree(term_1_pre,expansion_parameter);

	// construct transcendental sum type A
	index = next_index();

	sum_A = create_transcendental_sum_type_A_and_expand(Infinity,index,
							    create_letter(x,0,index),
							    create_list_of_tgamma(t_1_gammas),
							    create_Zsum(index-1,_empty_list),
							    expansion_parameter,order-pre_low_degree);

	sum_A = nestedsums_helper_expand(sum_A);
	sum_low_degree = nestedsums_helper_ldegree(sum_A,expansion_parameter);

	// recalculate prefactor
	// necesarry if sum_A yields poles in 1/eps
	term_1_pre = nestedsums_helper_expand_lst_tgamma_fct(t_1_pre_num, t_1_pre_denom, 
							     expansion_parameter, order-sum_low_degree);

	ex term_1 = nestedsums_helper_multiply_laurent_speedy(term_1_pre, sum_A, expansion_parameter, order);

#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_A, part 3, time in seconds : " << difftime(time_end,time_start) << std::endl;
	time(&time_start);
#endif // def _DEBUG
	
	// ---------------------------------------------------
	// done

	ex res = convert_Zsums_to_standard_form(term_0 + term_1, lst{expansion_parameter});

#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_A, part 4, time in seconds : " << difftime(time_end,time_start) << std::endl;
#endif // def _DEBUG

	return res;

      } // end if expansion_required


    // default
    return this->hold();

  }

  /**
   *
   * No automatic simplifications
   *
   */
  ex transcendental_fct_type_A::eval_ncmul(const exvector & v) const
  {

    // default
    return hold_ncmul(v);

  }

  ex transcendental_fct_type_A::derivative(const symbol & s) const
  {
    return 0;
  }

  ex transcendental_fct_type_A::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_transcendental_fct_type_A(x.subs(m,options),
					    i_num.subs(m,options),i_denom.subs(m,options),
					    pre_num.subs(m,options),pre_denom.subs(m,options),
					    expansion_parameter.subs(m,options),order,flag_expand_status);
  }

  // new virtual functions

  // non-virual functions

  /**
   *
   * Sets the flag flag_expand_status to expand_status::expansion_required.
   * The object is then automatically expanded up to the specified order.
   *
   */
  ex transcendental_fct_type_A::set_expansion(const ex & eps, int o) const
  {
    transcendental_fct_type_A* res = new transcendental_fct_type_A(x,i_num,i_denom,pre_num,pre_denom,
								   eps,o,expand_status::expansion_required);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

} // namespace nestedsums

