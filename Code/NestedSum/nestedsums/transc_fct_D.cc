
/** @file transc_fct_D.cc
 *
 * Implementation of transcendental_fct_type_D
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

GINAC_IMPLEMENT_REGISTERED_CLASS(transcendental_fct_type_D, basic)

GINAC_BIND_UNARCHIVER(transcendental_fct_type_D);


  transcendental_fct_type_D::transcendental_fct_type_D() : inherited(),
   x1(_default), x2(_default), i_num(_empty_list), i_denom(_empty_list), 
   j_num(_empty_list), j_denom(_empty_list),
   ij_num(_empty_list), ij_denom(_empty_list),
   pre_num(_empty_list), pre_denom(_empty_list),
   expansion_parameter(_default), order(0), flag_expand_status(expand_status::start)
  { 
  }

  void transcendental_fct_type_D::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("x1",x1);
    node.add_ex("x2",x2);
    node.add_ex("i_num",i_num);
    node.add_ex("i_denom",i_denom);
    node.add_ex("j_num",j_num);
    node.add_ex("j_denom",j_denom);
    node.add_ex("ij_num",ij_num);
    node.add_ex("ij_denom",ij_denom);
    node.add_ex("pre_num",pre_num);
    node.add_ex("pre_denom",pre_denom);
    node.add_ex("expansion_parameter",expansion_parameter);

    node.add_ex("order",numeric(order));
    node.add_ex("flag_expand_status",numeric(flag_expand_status));
  }

  void transcendental_fct_type_D::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("x1",x1,sym_lst);
    node.find_ex("x2",x2,sym_lst);
    node.find_ex("i_num",i_num,sym_lst);
    node.find_ex("i_denom",i_denom,sym_lst);
    node.find_ex("j_num",j_num,sym_lst);
    node.find_ex("j_denom",j_denom,sym_lst);
    node.find_ex("ij_num",ij_num,sym_lst);
    node.find_ex("ij_denom",ij_denom,sym_lst);
    node.find_ex("pre_num",pre_num,sym_lst);
    node.find_ex("pre_denom",pre_denom,sym_lst);
    node.find_ex("expansion_parameter",expansion_parameter,sym_lst);

    ex ex_order, ex_flag_expand_status;
    node.find_ex("order",ex_order,sym_lst);
    node.find_ex("flag_expand_status",ex_flag_expand_status,sym_lst);
    order = ex_to<numeric>(ex_order).to_int();
    flag_expand_status = ex_to<numeric>(ex_flag_expand_status).to_int();
  }

  int transcendental_fct_type_D::compare_same_type(const basic &other) const
  {
    const transcendental_fct_type_D &o = static_cast<const transcendental_fct_type_D &>(other);

    int cmpval;

    cmpval = x1.compare(o.x1);

    if( cmpval ) return cmpval;

    cmpval = x2.compare(o.x2);

    if( cmpval ) return cmpval;

    cmpval = i_num.compare(o.i_num);

    if( cmpval ) return cmpval;

    cmpval = i_denom.compare(o.i_denom);

    if( cmpval ) return cmpval;

    cmpval = j_num.compare(o.j_num);

    if( cmpval ) return cmpval;

    cmpval = j_denom.compare(o.j_denom);

    if( cmpval ) return cmpval;

    cmpval = ij_num.compare(o.ij_num);

    if( cmpval ) return cmpval;

    cmpval = ij_denom.compare(o.ij_denom);

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
  transcendental_fct_type_D::transcendental_fct_type_D(const ex & xx1, const ex & xx2, const ex & ii_num, const ex & ii_denom, 
						       const ex & jj_num, const ex & jj_denom,
						       const ex & iijj_num, const ex & iijj_denom, 
						       const ex & pp_num, const ex & pp_denom) : 
    inherited(), 
    x1(xx1), x2(xx2), i_num(ii_num), i_denom(ii_denom), 
    j_num(jj_num), j_denom(jj_denom),
    ij_num(iijj_num), ij_denom(iijj_denom),
    pre_num(pp_num), pre_denom(pp_denom),
    expansion_parameter(_default), order(0), flag_expand_status(expand_status::start)
  { }

  transcendental_fct_type_D::transcendental_fct_type_D(const ex & xx1, const ex & xx2, const ex & ii_num, const ex & ii_denom, 
						       const ex & jj_num, const ex & jj_denom,
						       const ex & iijj_num, const ex & iijj_denom, 
						       const ex & pp_num, const ex & pp_denom, const ex & eps, int o, int f) : 
    inherited(), 
    x1(xx1), x2(xx2), i_num(ii_num), i_denom(ii_denom), 
    j_num(jj_num), j_denom(jj_denom),
    ij_num(iijj_num), ij_denom(iijj_denom),
    pre_num(pp_num), pre_denom(pp_denom),
    expansion_parameter(eps), order(o), flag_expand_status(f)
  { }

  // functions overriding virtual functions from bases classes

  unsigned transcendental_fct_type_D::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= x1.gethash();

      v = rotate_left_31(v);
      v ^= x2.gethash();

      v = rotate_left_31(v);
      v ^= i_num.gethash();

      v = rotate_left_31(v);
      v ^= i_denom.gethash();

      v = rotate_left_31(v);
      v ^= j_num.gethash();

      v = rotate_left_31(v);
      v ^= j_denom.gethash();

      v = rotate_left_31(v);
      v ^= ij_num.gethash();

      v = rotate_left_31(v);
      v ^= ij_denom.gethash();

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

  void transcendental_fct_type_D::print(const print_context & c, unsigned level) const
  {
    if (is_a<print_latex>(c)) {
      if (precedence() <= level) c.s << "{(";
      c.s << "\\mbox{TFD}(" ;
      x1.print(c);
      c.s << ",";
      x2.print(c);
      c.s << ",";
      i_num.print(c);
      c.s << ",";
      i_denom.print(c);
      c.s << ",";
      j_num.print(c);
      c.s << ",";
      j_denom.print(c);
      c.s << ",";
      ij_num.print(c);
      c.s << ",";
      ij_denom.print(c);
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
	x1.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	x2.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	i_num.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	i_denom.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	j_num.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	j_denom.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	ij_num.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	ij_denom.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	pre_num.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	pre_denom.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	expansion_parameter.print(c, level + static_cast<const print_tree &>(c).delta_indent);
      } 
    else {
      c.s << "TFD(" ;
      x1.print(c);
      c.s << ",";
      x2.print(c);
      c.s << ",";
      i_num.print(c);
      c.s << ",";
      i_denom.print(c);
      c.s << ",";
      j_num.print(c);
      c.s << ",";
      j_denom.print(c);
      c.s << ",";
      ij_num.print(c);
      c.s << ",";
      ij_denom.print(c);
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
  ex transcendental_fct_type_D::eval() const
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
	ex index, sum_A, index_n, sum_n;

	lst lst_pre_num = ex_to<lst>(pre_num);
	lst lst_pre_denom = ex_to<lst>(pre_denom);

	lst lst_i_num = ex_to<lst>(i_num);
	lst lst_i_denom = ex_to<lst>(i_denom);

	lst lst_j_num = ex_to<lst>(j_num);
	lst lst_j_denom = ex_to<lst>(j_denom);

	lst lst_ij_num = ex_to<lst>(ij_num);
	lst lst_ij_denom = ex_to<lst>(ij_denom);
	lst_ij_denom.append(1);

#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_D, part 1, time in seconds : " << difftime(time_end,time_start) << std::endl;
#endif // def _DEBUG
	
	// ---------------------------------------
	// term i=0 j=0

#ifdef _DEBUG
	// measuring time starts here
	time(&time_start);
#endif // def _DEBUG

	lst t_00_pre_num = lst_pre_num;
	lst t_00_pre_denom = lst_pre_denom;

	for ( k=0;k<lst_i_num.nops();k++)
	  {
	    t_00_pre_num.append(lst_i_num.op(k));
	    t_00_pre_denom.append(lst_i_denom.op(k));
	  }
	for ( k=0;k<lst_j_num.nops();k++)
	  {
	    t_00_pre_num.append(lst_j_num.op(k));
	    t_00_pre_denom.append(lst_j_denom.op(k));
	  }
	for ( k=0;k<lst_ij_num.nops();k++)
	  {
	    t_00_pre_num.append(lst_ij_num.op(k));
	    t_00_pre_denom.append(lst_ij_denom.op(k));
	  }

	ex term_00 = create_Zsum(Infinity,_empty_list)
	  * nestedsums_helper_expand_lst_tgamma_fct(t_00_pre_num, t_00_pre_denom, expansion_parameter, order);

#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_D, part 2, time in seconds : " << difftime(time_end,time_start) << std::endl;
#endif // def _DEBUG
	
	// ---------------------------------------
	// term i>0 j=0

#ifdef _DEBUG
	// measuring time starts here
	time(&time_start);
#endif // def _DEBUG

	// prefactor
	lst t_10_pre_num = lst_pre_num;
	lst t_10_pre_denom = lst_pre_denom;

	for ( k=0;k<lst_j_num.nops();k++)
	  {
	    t_10_pre_num.append(lst_j_num.op(k));
	    t_10_pre_denom.append(lst_j_denom.op(k));
	  }

	// gamma sequence
	lst t_10_gammas;
	for ( k=0;k<lst_i_num.nops();k++)
	  {
	    temp_num = nestedsums_helper_expand(lst_i_num.op(k));
	    temp_num = temp_num.collect(expansion_parameter);

	    temp_denom = nestedsums_helper_expand(lst_i_denom.op(k));
	    temp_denom = temp_denom.collect(expansion_parameter);

	    t_10_pre_num.append(1+temp_num.coeff(expansion_parameter,1)*expansion_parameter);
	    t_10_pre_denom.append(1+temp_denom.coeff(expansion_parameter,1)*expansion_parameter);

	    t_10_gammas.append(create_ratio_of_tgamma(temp_num.coeff(expansion_parameter,0), 
						      temp_num.coeff(expansion_parameter,1),
						      temp_denom.coeff(expansion_parameter,0),
						      temp_denom.coeff(expansion_parameter,1) ));
	  }
	for ( k=0;k<lst_ij_num.nops();k++)
	  {
	    temp_num = nestedsums_helper_expand(lst_ij_num.op(k));
	    temp_num = temp_num.collect(expansion_parameter);

	    temp_denom = nestedsums_helper_expand(lst_ij_denom.op(k));
	    temp_denom = temp_denom.collect(expansion_parameter);

	    t_10_pre_num.append(1+temp_num.coeff(expansion_parameter,1)*expansion_parameter);
	    t_10_pre_denom.append(1+temp_denom.coeff(expansion_parameter,1)*expansion_parameter);

	    t_10_gammas.append(create_ratio_of_tgamma(temp_num.coeff(expansion_parameter,0), 
						      temp_num.coeff(expansion_parameter,1),
						      temp_denom.coeff(expansion_parameter,0),
						      temp_denom.coeff(expansion_parameter,1) ));
	  }

	ex term_10_pre = nestedsums_helper_expand_lst_tgamma_fct(t_10_pre_num, t_10_pre_denom, expansion_parameter, order);
	pre_low_degree = nestedsums_helper_ldegree(term_10_pre,expansion_parameter);

	// construct transcendental sum type A
	index = next_index();

	sum_A = create_transcendental_sum_type_A_and_expand(Infinity,index,
							    create_letter(x1,0,index),
							    create_list_of_tgamma(t_10_gammas),
							    create_Zsum(index-1,_empty_list),
							    expansion_parameter,order-pre_low_degree);

	sum_A = nestedsums_helper_expand(sum_A);
	sum_low_degree = nestedsums_helper_ldegree(sum_A,expansion_parameter);

	// recalculate prefactor
	// necesarry if sum_A yields poles in 1/eps
	term_10_pre = nestedsums_helper_expand_lst_tgamma_fct(t_10_pre_num, t_10_pre_denom, 
							      expansion_parameter, order-sum_low_degree);

	ex term_10 = nestedsums_helper_multiply_laurent_speedy(term_10_pre, sum_A, expansion_parameter, order);

#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_D, part 3, time in seconds : " << difftime(time_end,time_start) << std::endl;
#endif // def _DEBUG
	
	// ---------------------------------------
	// term i=0 j>0

#ifdef _DEBUG
	// measuring time starts here
	time(&time_start);
#endif // def _DEBUG

	// prefactor
	lst t_01_pre_num = lst_pre_num;
	lst t_01_pre_denom = lst_pre_denom;

	for ( k=0;k<lst_i_num.nops();k++)
	  {
	    t_01_pre_num.append(lst_i_num.op(k));
	    t_01_pre_denom.append(lst_i_denom.op(k));
	  }

	// gamma sequence
	lst t_01_gammas;
	for ( k=0;k<lst_j_num.nops();k++)
	  {
	    temp_num = nestedsums_helper_expand(lst_j_num.op(k));
	    temp_num = temp_num.collect(expansion_parameter);

	    temp_denom = nestedsums_helper_expand(lst_j_denom.op(k));
	    temp_denom = temp_denom.collect(expansion_parameter);

	    t_01_pre_num.append(1+temp_num.coeff(expansion_parameter,1)*expansion_parameter);
	    t_01_pre_denom.append(1+temp_denom.coeff(expansion_parameter,1)*expansion_parameter);

	    t_01_gammas.append(create_ratio_of_tgamma(temp_num.coeff(expansion_parameter,0), 
						      temp_num.coeff(expansion_parameter,1),
						      temp_denom.coeff(expansion_parameter,0),
						      temp_denom.coeff(expansion_parameter,1) ));
	  }
	for ( k=0;k<lst_ij_num.nops();k++)
	  {
	    temp_num = nestedsums_helper_expand(lst_ij_num.op(k));
	    temp_num = temp_num.collect(expansion_parameter);

	    temp_denom = nestedsums_helper_expand(lst_ij_denom.op(k));
	    temp_denom = temp_denom.collect(expansion_parameter);

	    t_01_pre_num.append(1+temp_num.coeff(expansion_parameter,1)*expansion_parameter);
	    t_01_pre_denom.append(1+temp_denom.coeff(expansion_parameter,1)*expansion_parameter);

	    t_01_gammas.append(create_ratio_of_tgamma(temp_num.coeff(expansion_parameter,0), 
						      temp_num.coeff(expansion_parameter,1),
						      temp_denom.coeff(expansion_parameter,0),
						      temp_denom.coeff(expansion_parameter,1) ));
	  }

	ex term_01_pre = nestedsums_helper_expand_lst_tgamma_fct(t_01_pre_num, t_01_pre_denom, expansion_parameter, order);
	pre_low_degree = nestedsums_helper_ldegree(term_01_pre,expansion_parameter);

	// construct transcendental sum type A
	index = next_index();

	sum_A = create_transcendental_sum_type_A_and_expand(Infinity,index,
							    create_letter(x2,0,index),
							    create_list_of_tgamma(t_01_gammas),
							    create_Zsum(index-1,_empty_list),
							    expansion_parameter,order-pre_low_degree);

	sum_A = nestedsums_helper_expand(sum_A);
	sum_low_degree = nestedsums_helper_ldegree(sum_A,expansion_parameter);

	// recalculate prefactor
	// necesarry if sum_A yields poles in 1/eps
	term_01_pre = nestedsums_helper_expand_lst_tgamma_fct(t_01_pre_num, t_01_pre_denom, 
							      expansion_parameter, order-sum_low_degree);

	ex term_01 = nestedsums_helper_multiply_laurent_speedy(term_01_pre, sum_A, expansion_parameter, order);

#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_D, part 4, time in seconds : " << difftime(time_end,time_start) << std::endl;
#endif // def _DEBUG
	
	// ---------------------------------------
	// term i>0 j>0

#ifdef _DEBUG
	// measuring time starts here
	time(&time_start);
#endif // def _DEBUG

	// prefactor
	lst t_11_pre_num = lst_pre_num;
	lst t_11_pre_denom = lst_pre_denom;

	// gamma sequences
	lst t_11_gammas_n, t_11_gammas_i, t_11_gammas_ni;
	int flag_n = 0;
	for ( k=0;k<lst_ij_num.nops();k++)
	  {
	    temp_num = nestedsums_helper_expand(lst_ij_num.op(k));
	    temp_num = temp_num.collect(expansion_parameter);

	    temp_denom = nestedsums_helper_expand(lst_ij_denom.op(k));
	    temp_denom = temp_denom.collect(expansion_parameter);

	    t_11_pre_num.append(1+temp_num.coeff(expansion_parameter,1)*expansion_parameter);
	    t_11_pre_denom.append(1+temp_denom.coeff(expansion_parameter,1)*expansion_parameter);

	    t_11_gammas_n.append(create_ratio_of_tgamma(temp_num.coeff(expansion_parameter,0), 
							temp_num.coeff(expansion_parameter,1),
							temp_denom.coeff(expansion_parameter,0),
							temp_denom.coeff(expansion_parameter,1) ));

	    // get number of possible poles of t_11_gammas_n
	    if ( temp_num.coeff(expansion_parameter,0).info(info_flags::negint) ) flag_n++;

	  }

	// poles for n=1,... ?
	if (flag_n) return convert_Zsums_to_standard_form(term_00 + term_10 + term_01 + this->shift_plus_one(), lst{expansion_parameter});

	for ( k=0;k<lst_i_num.nops();k++)
	  {
	    temp_num = nestedsums_helper_expand(lst_i_num.op(k));
	    temp_num = temp_num.collect(expansion_parameter);

	    temp_denom = nestedsums_helper_expand(lst_i_denom.op(k));
	    temp_denom = temp_denom.collect(expansion_parameter);

	    t_11_pre_num.append(1+temp_num.coeff(expansion_parameter,1)*expansion_parameter);
	    t_11_pre_denom.append(1+temp_denom.coeff(expansion_parameter,1)*expansion_parameter);

	    t_11_gammas_i.append(create_ratio_of_tgamma(temp_num.coeff(expansion_parameter,0), 
							temp_num.coeff(expansion_parameter,1),
							temp_denom.coeff(expansion_parameter,0),
							temp_denom.coeff(expansion_parameter,1) ));
	  }
	for ( k=0;k<lst_j_num.nops();k++)
	  {
	    temp_num = nestedsums_helper_expand(lst_j_num.op(k));
	    temp_num = temp_num.collect(expansion_parameter);

	    temp_denom = nestedsums_helper_expand(lst_j_denom.op(k));
	    temp_denom = temp_denom.collect(expansion_parameter);

	    t_11_pre_num.append(1+temp_num.coeff(expansion_parameter,1)*expansion_parameter);
	    t_11_pre_denom.append(1+temp_denom.coeff(expansion_parameter,1)*expansion_parameter);

	    t_11_gammas_ni.append(create_ratio_of_tgamma(temp_num.coeff(expansion_parameter,0), 
							 temp_num.coeff(expansion_parameter,1),
							 temp_denom.coeff(expansion_parameter,0),
							 temp_denom.coeff(expansion_parameter,1) ));
	  }

	ex term_11_pre = nestedsums_helper_expand_lst_tgamma_fct(t_11_pre_num, t_11_pre_denom, expansion_parameter, order);
	pre_low_degree = nestedsums_helper_ldegree(term_11_pre,expansion_parameter);

	index = next_index();
	index_n = next_index();

	// order shifted by pre_low_degree and flag_n
	sum_n = create_transcendental_sum_type_D_and_expand(index_n,index,
							    create_letter(-x1,0,index),
							    create_letter(x2,0,index_n-index),
							    create_list_of_tgamma(t_11_gammas_i),
							    create_list_of_tgamma(t_11_gammas_ni),
							    create_Ssum(index,_empty_list),
							    create_Ssum(index_n-index,_empty_list),
							    expansion_parameter,order-pre_low_degree-flag_n);

	sum_n = nestedsums_helper_expand(sum_n);
	sum_low_degree = nestedsums_helper_ldegree(sum_n,expansion_parameter);

#ifdef _DEBUG
	time(&time_end);
	std::cout << "transcendental_fct_type_D, part 5, time in seconds : " << difftime(time_end,time_start) << std::endl;
	time(&time_start);
#endif // def _DEBUG

	// set up triangle sum 
	sum_A = 0;
	for (k=sum_low_degree;k<order-pre_low_degree-flag_n;k++)
	  {
	    ex subsum = nestedsums_helper_coeff(sum_n,expansion_parameter,k);
	    subsum = nestedsums_helper_sort(subsum);

	    // order shifted by pre_low_degree and k
	    sum_A = sum_A - 
	      create_transcendental_sum_type_A_and_expand(Infinity,index_n,
							  create_unit_letter((ex) 0,index_n),
							  create_list_of_tgamma(t_11_gammas_n),
							  subsum,
							  expansion_parameter,order-pre_low_degree-k)
	      * pow(expansion_parameter,k);
	  }

	sum_A = nestedsums_helper_expand(sum_A);
	sum_low_degree = nestedsums_helper_ldegree(sum_A,expansion_parameter);


	// recalculate prefactor
	// necesarry if sum_A yields poles in 1/eps
	term_11_pre = nestedsums_helper_expand_lst_tgamma_fct(t_11_pre_num, t_11_pre_denom, 
							      expansion_parameter, order-sum_low_degree);

	ex term_11 = nestedsums_helper_multiply_laurent_speedy(term_11_pre, sum_A, expansion_parameter, order);


#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_D, part 6, time in seconds : " << difftime(time_end,time_start) << std::endl;
	time(&time_start);
#endif // def _DEBUG
	
	// ---------------------------------------------------
	// done

	ex res = convert_Zsums_to_standard_form(term_00 + term_10 + term_01 + term_11, lst{expansion_parameter});

#ifdef _DEBUG
	// measuring time end here
	time(&time_end);
	std::cout << "transcendental_fct_type_D, part 7, time in seconds : " << difftime(time_end,time_start) << std::endl;
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
  ex transcendental_fct_type_D::eval_ncmul(const exvector & v) const
  {

    // default
    return hold_ncmul(v);

  }

  ex transcendental_fct_type_D::derivative(const symbol & s) const
  {
    return 0;
  }

  ex transcendental_fct_type_D::subs(const exmap & m, unsigned options) const
  {
	exmap::const_iterator it = m.find(*this);
	if (it != m.end())
		return it->second;

    return create_transcendental_fct_type_D(x1.subs(m,options),x2.subs(m,options),
					    i_num.subs(m,options),i_denom.subs(m,options),
					    j_num.subs(m,options),j_denom.subs(m,options),
					    ij_num.subs(m,options),ij_denom.subs(m,options),
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
  ex transcendental_fct_type_D::set_expansion(const ex & eps, int o) const
  {
    transcendental_fct_type_D* res = new transcendental_fct_type_D(x1,x2,i_num,i_denom,
								   j_num,j_denom,ij_num,ij_denom,
								   pre_num,pre_denom,
								   eps,o,expand_status::expansion_required);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * Casts a sum of the form 
   *  \f[
   *     \frac{\Gamma(d_1) ... \Gamma(d_n)}{\Gamma(d_1') ... \Gamma(d_{n'}')} 
   *      \sum\limits_{i=1}^\infty \sum\limits_{j=1}^\infty 
   *       \frac{\Gamma(i+a_1) ... \Gamma(i+a_k)}{\Gamma(i+a_1') ... \Gamma(i+a_{k}')} 
   *       \frac{\Gamma(j+b_1) ... \Gamma(j+b_l)}{\Gamma(j+b_1') ... \Gamma(j+b_{l}')} 
   *       \frac{\Gamma(i+j+c_1) ... \Gamma(i+j+c_m)}{\Gamma(i+j+c_1') ... \Gamma(i+j+c_{m-1}')} 
   *      \frac{x_1^i}{i!} \frac{x_2^j}{j!}
   *  \f]
   * into the form of transcendental_fct_type_D by making the change of variables
   * \f[
   *    i' = i-1
   * \f] \f[
   *    j' = j-1
   * \f]
   */
  ex transcendental_fct_type_D::shift_plus_one(void) const
  {
    int k;

    lst new_i_num = lst();
    for ( k=0;k<i_num.nops();k++) new_i_num.append( i_num.op(k) + 1 );
    new_i_num.append(1);

    lst new_i_denom = lst();
    for ( k=0;k<i_denom.nops();k++) new_i_denom.append( i_denom.op(k) + 1 );
    new_i_denom.append(2);

    lst new_j_num = lst();
    for ( k=0;k<j_num.nops();k++) new_j_num.append( j_num.op(k) + 1 );
    new_j_num.append(1);

    lst new_j_denom = lst();
    for ( k=0;k<j_denom.nops();k++) new_j_denom.append( j_denom.op(k) + 1 );
    new_j_denom.append(2);

    lst new_ij_num = lst();
    for ( k=0;k<ij_num.nops();k++) new_ij_num.append( ij_num.op(k) + 2 );

    lst new_ij_denom = lst();
    for ( k=0;k<ij_denom.nops();k++) new_ij_denom.append( ij_denom.op(k) + 2 );

    return x1*x2*create_transcendental_fct_type_D(x1,x2,
						  new_i_num,new_i_denom,
						  new_j_num,new_j_denom,
						  new_ij_num,new_ij_denom,
						  pre_num,pre_denom,
						  expansion_parameter,order,flag_expand_status);
  }

} // namespace nestedsums

