
/** @file transcendental_B.cc
 *
 * Implementation of transcendental_sum_type_B
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

GINAC_IMPLEMENT_REGISTERED_CLASS(transcendental_sum_type_B, basic)

GINAC_BIND_UNARCHIVER(transcendental_sum_type_B);



  transcendental_sum_type_B::transcendental_sum_type_B() : inherited(),
   n(_default), index(_default_index), letter(_default), letter_rev(_default), 
   lst_of_gammas(_empty_list_of_tgamma), lst_of_gammas_rev(_empty_list_of_tgamma), 
   subsum(_default), subsum_rev(_default),
   expansion_parameter(_default), order(0), flag_expand_status(expand_status::start)
  { 
  }

  void transcendental_sum_type_B::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("n",n);
    node.add_ex("index",index);
    node.add_ex("letter",letter);
    node.add_ex("letter_rev",letter_rev);
    node.add_ex("lst_of_gammas",lst_of_gammas);
    node.add_ex("lst_of_gammas_rev",lst_of_gammas_rev);
    node.add_ex("subsum",subsum);
    node.add_ex("subsum_rev",subsum_rev);
    node.add_ex("expansion_parameter",expansion_parameter);

    node.add_ex("order",numeric(order));
    node.add_ex("flag_expand_status",numeric(flag_expand_status));
  }

  void transcendental_sum_type_B::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("n",n,sym_lst);
    node.find_ex("index",index,sym_lst);
    node.find_ex("letter",letter,sym_lst);
    node.find_ex("letter_rev",letter_rev,sym_lst);
    node.find_ex("lst_of_gammas",lst_of_gammas,sym_lst);
    node.find_ex("lst_of_gammas_rev",lst_of_gammas_rev,sym_lst);
    node.find_ex("subsum",subsum,sym_lst);
    node.find_ex("subsum_rev",subsum_rev,sym_lst);
    node.find_ex("expansion_parameter",expansion_parameter,sym_lst);

    ex ex_order, ex_flag_expand_status;
    node.find_ex("order",ex_order,sym_lst);
    node.find_ex("flag_expand_status",ex_flag_expand_status,sym_lst);
    order = ex_to<numeric>(ex_order).to_int();
    flag_expand_status = ex_to<numeric>(ex_flag_expand_status).to_int();
  }

  int transcendental_sum_type_B::compare_same_type(const basic &other) const
  {
    const transcendental_sum_type_B &o = static_cast<const transcendental_sum_type_B &>(other);

    int cmpval;

    cmpval = n.compare(o.n);

    if( cmpval ) return cmpval;

    cmpval = index.compare(o.index);

    if( cmpval ) return cmpval;


    cmpval = letter.compare(o.letter);

    if( cmpval ) return cmpval;

    cmpval = lst_of_gammas.compare(o.lst_of_gammas);

    if( cmpval ) return cmpval;

    cmpval = subsum.compare(o.subsum);

    if( cmpval ) return cmpval;


    cmpval = letter_rev.compare(o.letter_rev);

    if( cmpval ) return cmpval;

    cmpval = lst_of_gammas_rev.compare(o.lst_of_gammas_rev);

    if( cmpval ) return cmpval;

    cmpval = subsum_rev.compare(o.subsum_rev);

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
  transcendental_sum_type_B::transcendental_sum_type_B(const ex & nn, const ex & i, const ex & l, const ex & lr, 
						     const ex & v, const ex & vr, const ex & ss, const ex & ssr, 
						     const ex & eps, int o, int f) : 
    inherited(), n(nn), index(i), letter(l), letter_rev(lr),
    lst_of_gammas(v), lst_of_gammas_rev(vr), subsum(ss), subsum_rev(ssr),
    expansion_parameter(eps), order(o), flag_expand_status(f)
  { }


  // functions overriding virtual functions from bases classes

  unsigned transcendental_sum_type_B::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= n.gethash();

      v = rotate_left_31(v);
      v ^= index.gethash();

      v = rotate_left_31(v);
      v ^= letter.gethash();

      v = rotate_left_31(v);
      v ^= letter_rev.gethash();

      v = rotate_left_31(v);
      v ^= lst_of_gammas.gethash();

      v = rotate_left_31(v);
      v ^= lst_of_gammas_rev.gethash();

      v = rotate_left_31(v);
      v ^= subsum.gethash();

      v = rotate_left_31(v);
      v ^= subsum_rev.gethash();

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

  void transcendental_sum_type_B::print(const print_context & c, unsigned level) const
  {
    if (is_a<print_latex>(c)) {
      if (precedence() <= level) c.s << "{(";
      c.s << "\\sum_{" ;
      index.print(c);
      c.s << "= 1}^{";
      n.print(c);
      c.s << "-1}";
      letter.print(c,mul_precedence);
      lst_of_gammas.print(c);
      subsum.print(c,mul_precedence);
      letter_rev.print(c,mul_precedence);
      lst_of_gammas_rev.print(c);
      subsum_rev.print(c,mul_precedence);
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
	n.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	index.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	letter.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	letter_rev.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	lst_of_gammas.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	lst_of_gammas_rev.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	subsum.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	subsum_rev.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	expansion_parameter.print(c, level + static_cast<const print_tree &>(c).delta_indent);
      } 
    else {
      c.s << "sum(" ;
      index.print(c);
      c.s << "= 1..";
      n.print(c);
      c.s << "-1,";
      letter.print(c,mul_precedence);
      if ( ex_to<list_of_tgamma>(lst_of_gammas).get_depth() > 0 )
	{
	  c.s << "*";
	  lst_of_gammas.print(c);
	}
      c.s << "*";
      subsum.print(c,mul_precedence);
      c.s << "*";
      letter_rev.print(c,mul_precedence);
      if ( ex_to<list_of_tgamma>(lst_of_gammas_rev).get_depth() > 0 )
	{
	  c.s << "*";
	  lst_of_gammas_rev.print(c);
	}
      c.s << "*";
      subsum_rev.print(c,mul_precedence);
      c.s << ")";
    }
  }

  /**
   *
   * Simplifications, which are always performed are:
   * 
   * - If subsum is equal to 1, the subsum is replaced with Z(i-1).
   *
   * - If subsum_rev is equal to 1, the subsum_rev is replaced with Z(n-i-1).
   *
   * - If subsum is not of type Zsum, the routine distribute_over_subsum is called.
   * 
   * - If the difference of the upper summation index of the Zsum (in subsum) with the index member is not
   *   an integer, the Zsum is taken out of the sum. The subsum is replaced with Z(i-1).
   *
   * - If subsum_rev is not of type Zsum, the routine distribute_over_subsum_rev is called.
   * 
   * - If the difference of the upper summation index of the Zsum (in subsum_rev) with \f$(n-i)\f$ is not
   *   an integer, the Zsum is taken out of the sum. The subsum_rev is replaced with Z(n-i-1).
   *
   * - If letter is not of type basic_letter, the routine distribute_over_letter is called.
   * 
   * - If the difference of the index of the basic_letter (in letter) with the index member is not
   *   zero, the index in basic_letter is adjusted.
   *
   * - If letter_rev is not of type basic_letter, the routine distribute_over_letter_rev is called.
   * 
   * - If the difference of the index of the basic_letter (in letter_rev) with \f$(n-i)\f$ is not
   *   zero, the index in basic_letter is adjusted.
   *
   * - If the difference of the index of lst_of_gammas with the index member is not
   *   zero, the index in lst_of_gammas is adjusted.
   *
   * - If the difference of the index of lst_of_gammas_rev with \f$(n-i)\f$ is not
   *   zero, the index in lst_of_gammas_rev is adjusted.
   *
   * If flag_expand_status == expand_status::expansion_required, the evaluation routine
   * performs a set of consistency checks:
   *
   * - It adjusts the upper summation limit to index-1 in subsum and to n-index-1 in subsum_rev.
   *   If \f$ o > 0 \f$ the function Zsum::adjust_upper_limit_downwards(index-1) is used.
   *   If \f$ o < 0 \f$ the function shift_plus_one() is called.
   *   If \f$ o' > 0 \f$ the function Zsum::adjust_upper_limit_downwards(n-index-1) is used.
   *   If \f$ o' < 0 \f$ the function shift_plus_one_rev() is called.
   *
   * - It checks, that letter and letter_rev do not give rise to poles 
   *   (e.g. that the offset \f$c\f$ is a non-negative integer or a negative integer 
   *    larger or equal to \f$c \ge -l+o \f$ and
   *    that the offset \f$c'\f$ is a non-negative integer or a negative integer 
   *    larger or equal to \f$c' \ge -l'+o' \f$).
   *
   * - It checks, that the \f$a_j\f$ in the Gamma functions are integers.
   *
   * If one of the tests fails, the object is put into a zombie state.
   *
   * If flag_expand_status == expand_status::check_for_poles, it assures
   * that the Gamma functions in the numerator do not give rise to poles.
   * The functions shift_plus_one() and shift_plus_one_rev() are used.
   *
   * If flag_expand_status == expand_status::expand_gamma_functions, the Gamma functions are expanded
   * into Euler Zagier sums.
   * This is done by setting the expansion_required flag in the ratio_of_tgamma class.
   *
   * If flag_expand_status == expand_status::do_partial_fractioning, the sum is of the form
   * \f[
   *    \sum\limits_{i=1}^{n-1} \frac{x^i}{(i+c)^m} Z(i-1,m_1,...) \frac{y^{n-i}}{(n-i+c')^{m'}} Z(n-i-1,m_1',....)
   * \f]
   * For \f$m=0\f$ we have
   * \f[
   *    x^n \sum\limits_{i=1}^{n-1} \frac{\left(\frac{y}{x}\right)^i}{(i+c')^{m'}} Z(i-1,m_1',...) Z(n-i-1,m_1,...)
   * \f]
   * For \f$m'=0\f$ we have
   * \f[
   *    y^n \sum\limits_{i=1}^{n-1} \frac{\left(\frac{x}{y}\right)^i}{(i+c)^{m}} Z(i-1,m_1,...) Z(n-i-1,m_1',...)
   * \f]
   * For \f$m'<0\f$ we use
   * \f[
   *    (n-i+c') = (n+c') - i
   * \f]
   * For \f$m<0\f$ we use
   * \f[
   *    (i+c) = (n+c) - (n-i)
   * \f]
   * For \f$m>0\f$ and \f$m'>0\f$ we have
   * \f[
   *    \sum\limits_{i=1}^{n-1} \frac{x^i}{(i+c)^m} Z(i-1,m_1,...) \frac{y^{n-i}}{(n-i+c')^{m'}} Z(n-i-1,m_1',....)
   * \f] \f[
   *    = \frac{1}{n+c+c'} \sum\limits_{i=1}^{n-1} \frac{x^i}{(i+c)^{m-1}} Z(i-1,...) \frac{y^{n-i}}{(n-i+c')^{m'}} Z(n-i-1,....)
   * \f] \f[
   *    \mbox{} + \frac{1}{n+c+c'} 
   *            \sum\limits_{i=1}^{n-1} \frac{x^i}{(i+c)^{m}} Z(i-1,...) \frac{y^{n-i}}{(n-i+c')^{m'-1}} Z(n-i-1,....)
   * \f]
   *
   * If flag_expand_status == expand_status::do_outermost_sum, the sum is of the form
   * \f[
   *    \sum\limits_{i=1}^{n-1} \frac{x^i}{(i+c)^m} Z(i-1,m_1,...) Z(n-i-1,m_1',....)
   * \f]
   * If the depth of \f$Z(n-i-1,m_1',....)\f$ is zero, we have a sum of type A with upper summation index \f$(n-1)\f$:
   * \f[
   *    \sum\limits_{i=1}^{n-1} \frac{x^i}{(i+c)^m} Z(i-1,m_1,...) 
   * \f]
   * Otherwise we have the recursion
   * \f[
   *    \sum\limits_{i=1}^{n-1} \frac{x^i}{(i+c)^m} Z(i-1,m_1,...) Z(n-i-1,m_1',....)
   * \f] \f[
   *    = \sum\limits_{j=1}^{n-1} 
   *    \left[ \sum\limits_{i=1}^{j-1} \frac{x^i}{(i+c)^m} Z(i-1,m_1,...) 
   *           \frac{{x_1'}^{j-i}}{(j-i)^{m_1'}} Z(j-i-1,m_2',....)
   *    \right]
   * \f]
   *
   */
  ex transcendental_sum_type_B::eval() const
  {
#ifdef _DEBUG
    if ( _debug_level & 2 ) 
      {
	std::cout << " ---------------------------- " << std::endl;
	std::cout << std::endl;
	std::cout << "entering eval type B" << std::endl;
	std::cout << std::endl;
	std::cout << "n         : " << n << std::endl;
	std::cout << "index     : " << index << std::endl;
	std::cout << "letter    : " << letter << std::endl;
	std::cout << "gammas    : " << lst_of_gammas << std::endl;
	std::cout << "subsum    : " << subsum << std::endl;
	std::cout << "letter_rev: " << letter_rev << std::endl;
	std::cout << "gammas_rev: " << lst_of_gammas_rev << std::endl;
	std::cout << "subsum_rev: " << subsum_rev << std::endl;
      }
#endif // def _DEBUG

    // subsum has to be expanded !!!
    if ( !is_a<Zsum>(subsum) )
      {
	return distribute_over_subsum();
      }

    // assert subsum of type Zsum
    ex diff_indices = ex_to<Zsum>(subsum).get_index() - index;

    if ( !diff_indices.info(info_flags::integer) )
      {
	return subsum * create_transcendental_sum_type_B(n,index,letter,letter_rev,lst_of_gammas,lst_of_gammas_rev,
					       create_Zsum(index-1,lst()),subsum_rev,
					       expansion_parameter,order,flag_expand_status);
      }

    // subsum_rev has to be expanded !!!
    if ( !is_a<Zsum>(subsum_rev) )
      {
	return distribute_over_subsum_rev();
      }

    // assert subsum_rev of type Zsum
    ex diff_indices_rev = ex_to<Zsum>(subsum_rev).get_index() - n + index;

    if ( !diff_indices_rev.info(info_flags::integer) )
      {
	return subsum_rev * create_transcendental_sum_type_B(n,index,letter,letter_rev,lst_of_gammas,lst_of_gammas_rev,
					       subsum,create_Zsum(n-index-1,lst()),
					       expansion_parameter,order,flag_expand_status);
      }

    // letter has to be expanded !!!
    if ( !is_a<basic_letter>(letter) )
      {
	return distribute_over_letter();
      }

    // assert letter of type basic_letter
    // adjust index in letter
    ex diff_indices_letter = ex_to<basic_letter>(letter).get_index() - index;

    if ( !diff_indices_letter.is_zero() )
      {
	return create_transcendental_sum_type_B(n,index,
		ex_to<basic_letter>(letter).shift_index(index),letter_rev,
		lst_of_gammas,lst_of_gammas_rev,subsum,subsum_rev,
		expansion_parameter,order,flag_expand_status);
      }


    // letter_rev has to be expanded !!!
    if ( !is_a<basic_letter>(letter_rev) )
      {
	return distribute_over_letter_rev();
      }

    // assert letter_rev of type basic_letter
    // adjust index in letter_rev
    ex diff_indices_letter_rev = ex_to<basic_letter>(letter_rev).get_index() - n + index;

    if ( !diff_indices_letter_rev.is_zero() )
      {
	return create_transcendental_sum_type_B(n,index,
		letter,ex_to<basic_letter>(letter_rev).shift_index(n-index),
		lst_of_gammas,lst_of_gammas_rev,subsum,subsum_rev,
		expansion_parameter,order,flag_expand_status);
      }


    // adjust index in list_of_tgamma
    if ( ex_to<list_of_tgamma>(lst_of_gammas).get_depth() > 0 )
      {
	ex diff_indices_gamma = ex_to<list_of_tgamma>(lst_of_gammas).get_index() - index;

	if ( !diff_indices_gamma.is_zero() )
	  {
	    return create_transcendental_sum_type_B(n,index,letter,letter_rev,
						ex_to<list_of_tgamma>(lst_of_gammas).shift_index(index),lst_of_gammas_rev,
						subsum,subsum_rev,
						expansion_parameter,order,flag_expand_status);
	  }
      }

    // adjust index in list_of_tgamma_rev
    if ( ex_to<list_of_tgamma>(lst_of_gammas_rev).get_depth() > 0 )
      {
	ex diff_indices_gamma_rev = ex_to<list_of_tgamma>(lst_of_gammas_rev).get_index() - n + index;

	if ( !diff_indices_gamma_rev.is_zero() )
	  {
	    return create_transcendental_sum_type_B(n,index,letter,letter_rev,
						lst_of_gammas,ex_to<list_of_tgamma>(lst_of_gammas_rev).shift_index(n-index),
						subsum,subsum_rev,
						expansion_parameter,order,flag_expand_status);
	  }
      }


    // ---------------
    if ( ( flag_expand_status == expand_status::expansion_required )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_B ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 2 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering expansion_required" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	    std::cout << "letter_rev: " << letter_rev << std::endl;
	    std::cout << "gammas_rev: " << lst_of_gammas_rev << std::endl;
	    std::cout << "subsum_rev: " << subsum_rev << std::endl;
	  }
#endif // def _DEBUG

	int temp_zombie_flag = 0;

	// check for index-1 in subsum 
	ex up_diff = ex_to<Zsum>(subsum).get_index() - index + 1;

	if (up_diff.info(info_flags::posint))
	  {
	    // return adjusted object
	    return create_transcendental_sum_type_B(n,index,letter,letter_rev,lst_of_gammas,lst_of_gammas_rev,
						    ex_to<Zsum>(subsum).adjust_upper_limit_downwards(index-1),
						    subsum_rev,
						    expansion_parameter,order,flag_expand_status);
	  }
	else if (up_diff.info(info_flags::negint))
	  {
	    return this->shift_plus_one();
	  }

	// check that there are no poles in letter
	// offset in subsum already reduced to zero here
	ex c = ex_to<basic_letter>(letter).get_offset();
	if (c.info(info_flags::integer))
	  {
	    if ( c + ex_to<Zsum>(subsum).get_depth() < 0 )
	      {
		temp_zombie_flag = 1;
	      }
	  }
	else // c not an integer
	  {
	    // offset c is symbolic
	    temp_zombie_flag = 1;
	  }

	// check that a_j and c_j in ratio_of_tgamma are integers
	int flag = ex_to<list_of_tgamma>(lst_of_gammas).expansion_alert();

	if ( flag>0 )
	  {
	    // some ratio_of_tgamma cannot be expanded
	    temp_zombie_flag = 1;
	  }


	// check for n-index-1 in subsum_rev
	up_diff = ex_to<Zsum>(subsum_rev).get_index() - n + index + 1;

	if (up_diff.info(info_flags::posint))
	  {
	    // return adjusted object
	    return create_transcendental_sum_type_B(n,index,letter,letter_rev,lst_of_gammas,lst_of_gammas_rev,
						    subsum,
						    ex_to<Zsum>(subsum_rev).adjust_upper_limit_downwards(n-index-1),
						    expansion_parameter,order,flag_expand_status);
	  }
	else if (up_diff.info(info_flags::negint))
	  {
	    return this->shift_plus_one_rev();
	  }

	// check that there are no poles in letter_rev
	// offset in subsum_rev already reduced to zero here
	c = ex_to<basic_letter>(letter_rev).get_offset();
	if (c.info(info_flags::integer))
	  {
	    if ( c + ex_to<Zsum>(subsum_rev).get_depth() < 0 )
	      {
		temp_zombie_flag = 1;
	      }
	  }
	else // c not an integer
	  {
	    // offset c is symbolic
	    temp_zombie_flag = 1;
	  }

	// check that a_j and c_j in ratio_of_tgamma are integers
	flag = ex_to<list_of_tgamma>(lst_of_gammas_rev).expansion_alert();

	if ( flag>0 )
	  {
	    // some ratio_of_tgamma cannot be expanded
	    temp_zombie_flag = 1;
	  }



	// all tests passed ?
	if ( temp_zombie_flag )
	  {
	    flag_expand_status = expand_status::zombie;
	  }
	else
	  {
	    flag_expand_status = expand_status::check_for_poles;
	  }


      } // end if expansion_required

    // ---------------
    if ( ( flag_expand_status == expand_status::check_for_poles )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_B ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 2 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering check_for_poles" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	    std::cout << "letter_rev: " << letter_rev << std::endl;
	    std::cout << "gammas_rev: " << lst_of_gammas_rev << std::endl;
	    std::cout << "subsum_rev: " << subsum_rev << std::endl;
	  }
#endif // def _DEBUG

	// check first for poles in i-part
	int flag = ex_to<list_of_tgamma>(lst_of_gammas).pole_alert();

	if ( flag>0 ) return this->shift_plus_one();

	// now check poles in (n-i)-part
	flag = ex_to<list_of_tgamma>(lst_of_gammas_rev).pole_alert();

	if ( flag>0 ) return this->shift_plus_one_rev();

	// no poles, go to next step
	flag_expand_status = expand_status::expand_gamma_functions;

      } // end if check_for_poles


    // ---------------
    if ( ( flag_expand_status == expand_status::expand_gamma_functions )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_B ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 2 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering expand_gamma_functions" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	    std::cout << "letter_rev: " << letter_rev << std::endl;
	    std::cout << "gammas_rev: " << lst_of_gammas_rev << std::endl;
	    std::cout << "subsum_rev: " << subsum_rev << std::endl;
	  }
#endif // def _DEBUG

	if ( (ex_to<list_of_tgamma>(lst_of_gammas).get_depth() > 0) ||  (ex_to<list_of_tgamma>(lst_of_gammas_rev).get_depth() > 0) )
	  {
	    int i,j;

	    ex pre = ex_to<list_of_tgamma>(lst_of_gammas).set_expansion();
	    pre = pre * subsum;
	    pre = nestedsums_helper_expand(pre);

	    ex pre_rev = ex_to<list_of_tgamma>(lst_of_gammas_rev).set_expansion();
	    pre_rev = pre_rev * subsum_rev;
	    pre_rev = nestedsums_helper_expand(pre_rev);

	    // set up triangle sum 
	    ex res = 0;
	    for (j=0;j<order;j++)
	      {
		for (i=0;i<=j;i++)
		  {
		    res = res + create_transcendental_sum_type_B_and_set_gammas(n,index,letter,letter_rev,
				_empty_list_of_tgamma,_empty_list_of_tgamma,
				nestedsums_helper_coeff(pre,expansion_parameter,i),
				nestedsums_helper_coeff(pre_rev,expansion_parameter,j-i),
				expansion_parameter,order,expand_status::do_partial_fractioning)
		      * pow(expansion_parameter,j);
		  }
	      }

	    return res;
	  }

	// nothing to expand
	flag_expand_status = expand_status::do_partial_fractioning;

      } // end if expand_gamma_functions

    // ---------------
    if ( ( flag_expand_status == expand_status::do_partial_fractioning )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_B ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 2 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering do_partial_fractioning" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	    std::cout << "letter_rev: " << letter_rev << std::endl;
	    std::cout << "gammas_rev: " << lst_of_gammas_rev << std::endl;
	    std::cout << "subsum_rev: " << subsum_rev << std::endl;
	  }
#endif // def _DEBUG

	// we now have 
	//    x^i/(i+c)^m Z(i-1,...) y^(n-i)/(n-i+cp)^mp Z(n-i-1,....)

	const basic_letter& li = ex_to<basic_letter>(letter);
	const basic_letter& lni = ex_to<basic_letter>(letter_rev);

	// recursion start

	if ( lni.get_degree().is_zero() )
	  {
	    if ( lni.get_scale().is_equal(1) )
	      {
		return create_transcendental_sum_type_B(n,index,
							letter,
							_unit_zero_letter.set_index(n-index),
							lst_of_gammas, lst_of_gammas_rev,
							subsum,subsum_rev,
							expansion_parameter,order,expand_status::do_outermost_sum);
	      }
	    else
	      {
		return create_letter(lni.get_scale(),0,n)
		  *create_transcendental_sum_type_B(n,index,create_basic_letter(li.get_scale()/lni.get_scale(),
										li.get_degree(),li.get_offset(),index),
						    _unit_zero_letter.set_index(n-index),
						    lst_of_gammas, lst_of_gammas_rev,
						    subsum,subsum_rev,
						    expansion_parameter,order,expand_status::do_outermost_sum);
	      }
	  }

	if ( li.get_degree().is_zero() )
	  {
	    if ( li.get_scale().is_equal(1) )
	      {
		return create_transcendental_sum_type_B(n,index,
							ex_to<basic_letter>(letter_rev).set_index(index),
							_unit_zero_letter.set_index(n-index),
							lst_of_gammas, lst_of_gammas_rev,
							ex_to<Zsum>(subsum_rev).set_index(index-1),
							ex_to<Zsum>(subsum).set_index(n-index-1),
							expansion_parameter,order,expand_status::do_outermost_sum);
	      }
	    else
	      {
		return create_letter(li.get_scale(),0,n)
		  *create_transcendental_sum_type_B(n,index,create_basic_letter(lni.get_scale()/li.get_scale(),
										lni.get_degree(),lni.get_offset(),index),
						    _unit_zero_letter.set_index(n-index),
						    lst_of_gammas, lst_of_gammas_rev,
						    ex_to<Zsum>(subsum_rev).set_index(index-1),
						    ex_to<Zsum>(subsum).set_index(n-index-1),
						    expansion_parameter,order,expand_status::do_outermost_sum);
	      }
	  }

	// mp<0
	//     (n-i+cp) = (n+cp) - i 
	if ( lni.get_degree() < 0 )
	  {
	    return create_basic_letter((ex) 1, -1, lni.get_offset(), n)
	      *create_transcendental_sum_type_B(n,index,
					       letter,
                                               lni.degree_plus_one(),
					       lst_of_gammas, lst_of_gammas_rev,
					       subsum,subsum_rev,
					       expansion_parameter,order,expand_status::do_partial_fractioning)
	      -create_transcendental_sum_type_B(n,index,
					       letter,
                                               lni.degree_plus_one(),
					       lst_of_gammas, lst_of_gammas_rev,
					       create_unit_letter((ex) -1,index)*subsum,
                                               subsum_rev,
					       expansion_parameter,order,expand_status::do_partial_fractioning);

	  }


	// m<0
	//     (i+c) = (n+c) - (n-i) 
	if ( li.get_degree() < 0 )
	  {
	    return create_basic_letter((ex) 1, -1, li.get_offset(), n)
	      *create_transcendental_sum_type_B(n,index,
                                               li.degree_plus_one(),
                                               letter_rev,
					       lst_of_gammas, lst_of_gammas_rev,
					       subsum,subsum_rev,
					       expansion_parameter,order,expand_status::do_partial_fractioning)
	      -create_transcendental_sum_type_B(n,index,
                                               li.degree_plus_one(),
                                               letter_rev,
					       lst_of_gammas, lst_of_gammas_rev,
					       subsum,
                                               create_unit_letter((ex) -1,n-index)*subsum_rev,
					       expansion_parameter,order,expand_status::do_partial_fractioning);

	  }


	// now m>0 and mp>0

	// closed form for partial fractioning
	int m1 = ex_to<numeric>(li.get_degree()).to_int();
	int m2 = ex_to<numeric>(lni.get_degree()).to_int();

	ex c1 = li.get_offset();
	ex c2 = lni.get_offset();

	ex res = 0 ;

	for (int k=1;k<=m1;k++) 
	  res += binomial(m1+m2-k-1,m2-1)
	    *create_basic_letter((ex) 1,m1+m2-k,c1+c2,n)
	    *create_transcendental_sum_type_B(n,index,
					      create_basic_letter(li.get_scale(),k,c1,index),
					      create_letter(lni.get_scale(),0,n-index),
					      lst_of_gammas, lst_of_gammas_rev,
					      subsum,subsum_rev,
					      expansion_parameter,order,expand_status::do_partial_fractioning);

	for (int k=1;k<=m2;k++) 
	  res += binomial(m1+m2-k-1,m1-1)
	    *create_basic_letter((ex) 1,m1+m2-k,c1+c2,n)
	    *create_transcendental_sum_type_B(n,index,
					      create_letter(li.get_scale(),0,index),
					      create_basic_letter(lni.get_scale(),k,c2,n-index),
					      lst_of_gammas, lst_of_gammas_rev,
					      subsum,subsum_rev,
					      expansion_parameter,order,expand_status::do_partial_fractioning);

	return res;

      } // end if do_partial_fractioning


    // ---------------
    if ( ( flag_expand_status == expand_status::do_outermost_sum )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_B ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 2 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering do_outermost_sum" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	    std::cout << "letter_rev: " << letter_rev << std::endl;
	    std::cout << "gammas_rev: " << lst_of_gammas_rev << std::endl;
	    std::cout << "subsum_rev: " << subsum_rev << std::endl;
	  }
#endif // def _DEBUG

	// we now have 
	//    x^i/(i+c)^m Z(i-1,...) Z(n-i-1,....)

	// recursion start
	if ( ex_to<Zsum>(subsum_rev).get_depth() == 0 )
	  {
	    // reduces to a transcendental sum of type A
	    // upper summation index is n-1
	    return create_transcendental_sum_type_A(n-1,index,letter,lst_of_gammas,subsum,
						   expansion_parameter,order,expand_status::adjust_summation_index);
	  }

	ex flr = ex_to<Zsum>(subsum_rev).get_first_letter();

	// use the new symbol_factory ...
	ex new_index = next_index();

	ex new_letter_rev = ex_to<basic_letter>(flr).set_index(new_index-index);

	ex new_subsum_rev = ex_to<Zsum>(subsum_rev).remove_first_letter(new_index-index-1);

	ex mysubsum = create_transcendental_sum_type_B_and_set_gammas(new_index,index,letter,new_letter_rev,
						      _empty_list_of_tgamma,_empty_list_of_tgamma,
						      subsum,
						      new_subsum_rev,
						      expansion_parameter,order,expand_status::do_partial_fractioning);

	// ensure that the subsum is expanded
	mysubsum = nestedsums_helper_expand(mysubsum);

	// upper summation index is n-1
	return create_transcendental_sum_type_A_and_set_gammas(n-1,new_index,_unit_zero_letter.set_index(new_index),
					       _empty_list_of_tgamma,
					       mysubsum,
					       expansion_parameter,order,expand_status::expansion_required);

      } // end if do_outermost_sum


    // n integer
    if ( n.info(info_flags::integer) ) return this->eval_explicit();

    // default
    //
    // this happens if
    //  - expansion was not required
    //  - or expansion was attempted, but ended in a zombie state

    return this->hold();
  }


  /**
   *
   * No automatic simplifications
   *
   */
  ex transcendental_sum_type_B::eval_ncmul(const exvector & v) const
  {

    // default
    return hold_ncmul(v);

  }

  ex transcendental_sum_type_B::derivative(const symbol & s) const
  {
    return 0;
  }

  ex transcendental_sum_type_B::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_transcendental_sum_type_B(n.subs(m,options),index.subs(m,options),letter.subs(m,options),letter_rev.subs(m,options),
					   lst_of_gammas.subs(m,options),lst_of_gammas_rev.subs(m,options),
					   subsum.subs(m,options),subsum_rev.subs(m,options),
					   expansion_parameter.subs(m,options),order,flag_expand_status);
  }

  // new virtual functions


  // non-virual functions

  /**
   *
   * Sets the flag flag_expand_status to expand_status::expansion_required.
   * The object is then automatically expanded up to the order specified in the
   * member variable order.
   *
   */
  ex transcendental_sum_type_B::set_expansion(void) const
  {
    transcendental_sum_type_B* res = new transcendental_sum_type_B(n,index,letter,letter_rev,
								 lst_of_gammas,lst_of_gammas_rev,subsum,subsum_rev,
								 expansion_parameter,
								 order,expand_status::expansion_required);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * subsum is allowed to contain a sum of products (e.g. an expression in expanded form).
   * Each term can contain scalars, basic_letters, list_of_tgammas, Zsums or Ssums.
   *
   * This routine converts the transcendental_sum_type_B to a canonical form,
   * so that afterwards subsum only contains a Zsum.
   *
   * The algorithm is based on the following steps:
   *
   * - If an object is of type basic_letter and the difference of its index with 
   *   the index member is an integer, it is combined with the letter member.
   *   Otherwise it is taken out of the sum.
   * 
   * - If an object is of type list_of_tgamma and the difference of its index with 
   *   the index member is an integer, it is combined with the lst_of_gammas member.
   *   Otherwise it is taken out of the sum.
   *
   * - If an object is of type Zsum and the difference of its index with 
   *   the index member is an integer, it is stays inside the subsum.
   *   Otherwise it is taken out of the sum.
   *
   * - If an object is of type Ssum and the difference of its index with 
   *   the index member is an integer, it is converted to an Zsum and stays inside the subsum.
   *   Otherwise it is taken out of the sum.
   *
   */
  ex transcendental_sum_type_B::distribute_over_subsum(void) const
  {
    // subsum has to be expanded !!!
    //
    // addition
    if ( is_a<add>(subsum))
      {
	int j;
	ex res = 0;
	for (j=0;j<subsum.nops();j++)
	  {
	    res = res + create_transcendental_sum_type_B(n,index,letter,letter_rev,
							lst_of_gammas,lst_of_gammas_rev,
							subsum.op(j),subsum_rev,
							expansion_parameter,order,flag_expand_status);
	  }
	return res;
      }

    // multiplication
    if ( is_a<mul>(subsum) || is_a<ncmul>(subsum) )
      {
	int j;
	int up_limit = static_cast<int>(subsum.nops());
	exvector prefactor;
	exvector hard_core;
	prefactor.reserve(up_limit);
	hard_core.reserve(up_limit);
	ex newletter = letter;
	ex new_lst_of_gammas = lst_of_gammas;

	for (j=0;j<up_limit;j++)
	  {
	    ex obj = subsum.op(j);

	    if ( is_a<basic_letter>(obj) )
	      {
		const basic_letter& obj_letter = ex_to<basic_letter>(obj);

		ex offset = obj_letter.get_index() - index;

		if ( offset.info(info_flags::integer) )
		  {
		    // ncmul type is basic_letter, therefore expand should be safe
		    newletter = newletter*obj;
		    newletter = newletter.expand();
		  }
		else 
		  {
		    prefactor.push_back(obj);
		  }
	      } // end basic_letter
	    else if ( is_a<list_of_tgamma>(obj) )
	      {
		const list_of_tgamma& obj_list = ex_to<list_of_tgamma>(obj);

		ex offset = obj_list.get_index() - index;

		if ( offset.info(info_flags::integer) )
		  {
		    new_lst_of_gammas = new_lst_of_gammas*obj; 
		  }
		else
		  {
		    prefactor.push_back(obj);
		  }

	      } // end list_of_tgamma
	    else if ( is_a<Zsum>(obj) )
	      {
		const Zsum& obj_subsum = ex_to<Zsum>(obj);

		ex offset = obj_subsum.get_index() - index;

		if ( offset.info(info_flags::integer) )
		  {
		    hard_core.push_back(obj);
		  }
		else
		  {
		    prefactor.push_back(obj);
		  }

	      } // end Zsum
	    else if ( is_a<Ssum>(obj) )
	      {
		const Ssum& obj_subsum = ex_to<Ssum>(obj);

		ex offset = obj_subsum.get_index() - index;

		if ( offset.info(info_flags::integer) )
		  {
		    hard_core.push_back(Ssum_to_Zsum(obj));
		  }
		else
		  {
		    prefactor.push_back(obj);
		  }

	      } // end Ssum
	    else 
	      {
		// default, scalar
		prefactor.push_back(obj);
	      } // end default
	  } // end for j = ...

	ex pre = (new ncmul(prefactor))->setflag(status_flags::dynallocated);
	if ( hard_core.size() == 0 ) hard_core.push_back(create_Zsum(index-1,lst()));
	ex hard = (new ncmul(hard_core))->setflag(status_flags::dynallocated);
	hard = nestedsums_helper_expand(hard);
	ex res = pre*create_transcendental_sum_type_B(n,index,newletter,letter_rev,new_lst_of_gammas,lst_of_gammas_rev,
						     hard,subsum_rev,
						     expansion_parameter,order,flag_expand_status);
	return res;
      } // end distribution over subsum

    // basic letter
    if ( is_a<basic_letter>(subsum))
      {
	const basic_letter& obj_letter = ex_to<basic_letter>(subsum);

	ex offset = obj_letter.get_index() - index;

	if ( offset.info(info_flags::integer) )
	  {
	    ex newletter = letter * subsum;
	    newletter = newletter.expand();
	    return create_transcendental_sum_type_B(n,index,newletter,letter_rev,
		     lst_of_gammas,lst_of_gammas_rev,create_Zsum(index-1,lst()),subsum_rev,
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum * create_transcendental_sum_type_B(n,index,letter,letter_rev,
			     lst_of_gammas,lst_of_gammas_rev,create_Zsum(index-1,lst()),subsum_rev,
			     expansion_parameter,order,flag_expand_status);
	  }
      } // end basic_letter

    // list_of_tgamma
    if ( is_a<list_of_tgamma>(subsum))
      {
	const list_of_tgamma& obj_list = ex_to<list_of_tgamma>(subsum);

	ex offset = obj_list.get_index() - index;

	if ( offset.info(info_flags::integer) )
	  {
	    return create_transcendental_sum_type_B(n,index,letter,letter_rev,
		     lst_of_gammas*subsum,lst_of_gammas_rev,create_Zsum(index-1,lst()),subsum_rev,
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum * create_transcendental_sum_type_B(n,index,letter,letter_rev,
			     lst_of_gammas,lst_of_gammas_rev,create_Zsum(index-1,lst()),subsum_rev,
			     expansion_parameter,order,flag_expand_status);
	  }
      } // end list_of_tgamma

    // Ssum
    if ( is_a<Ssum>(subsum))
      {
	const Ssum& obj = ex_to<Ssum>(subsum);

	ex offset = obj.get_index() - index;

	if ( offset.info(info_flags::integer) )
	  {
	    return create_transcendental_sum_type_B(n,index,letter,letter_rev,
		     lst_of_gammas,lst_of_gammas_rev,nestedsums_helper_expand(Ssum_to_Zsum(subsum)),subsum_rev,
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum * create_transcendental_sum_type_B(n,index,letter,letter_rev,
			     lst_of_gammas,lst_of_gammas_rev,create_Zsum(index-1,lst()),subsum_rev,
			     expansion_parameter,order,flag_expand_status);
	  }
      } // end Ssum

    // default: anything else, take it out of the sum
    if ( !is_a<Zsum>(subsum) )
      {
	return subsum * create_transcendental_sum_type_B(n,index,letter,letter_rev,lst_of_gammas,lst_of_gammas_rev,
							 create_Zsum(index-1,lst()),subsum_rev,
							 expansion_parameter,order,flag_expand_status);
      }

    return this->hold();
  }


  /**
   *
   * subsum_rev is allowed to contain a sum of products (e.g. an expression in expanded form).
   * Each term can contain scalars, basic_letters, list_of_tgammas, Zsums or Ssums.
   *
   * This routine converts the transcendental_sum_type_B to a canonical form,
   * so that afterwards subsum_rev only contains a Zsum.
   *
   * The algorithm is based on the following steps:
   *
   * - If an object is of type basic_letter and the difference of its index with 
   *   \f$(n-i)\f$ is an integer, it is combined with the letter_rev member.
   *   Otherwise it is taken out of the sum.
   * 
   * - If an object is of type list_of_tgamma and the difference of its index with 
   *   \f$(n-i)\f$ is an integer, it is combined with the lst_of_gammas_rev member.
   *   Otherwise it is taken out of the sum.
   *
   * - If an object is of type Zsum and the difference of its index with 
   *   \f$(n-i)\f$ is an integer, it is stays inside the subsum_rev.
   *   Otherwise it is taken out of the sum.
   *
   * - If an object is of type Ssum and the difference of its index with 
   *   \f$(n-i)\f$ is an integer, it is converted to an Zsum and stays inside the subsum_rev.
   *   Otherwise it is taken out of the sum.
   *
   */
  ex transcendental_sum_type_B::distribute_over_subsum_rev(void) const
  {
    // addition
    if ( is_a<add>(subsum_rev))
      {
	int j;
	ex res = 0;
	for (j=0;j<subsum_rev.nops();j++)
	  {
	    res = res + create_transcendental_sum_type_B(n,index,letter,letter_rev,
							lst_of_gammas,lst_of_gammas_rev,
							subsum,subsum_rev.op(j),
							expansion_parameter,order,flag_expand_status);
	  }
	return res;
      }

    // multiplication
    if ( is_a<mul>(subsum_rev) || is_a<ncmul>(subsum_rev) )
      {
	int j;
	int up_limit = static_cast<int>(subsum_rev.nops());
	exvector prefactor;
	exvector hard_core;
	prefactor.reserve(up_limit);
	hard_core.reserve(up_limit);
	ex newletter = letter_rev;
	ex new_lst_of_gammas = lst_of_gammas_rev;

	for (j=0;j<up_limit;j++)
	  {
	    ex obj = subsum_rev.op(j);

	    if ( is_a<basic_letter>(obj) )
	      {
		const basic_letter& obj_letter = ex_to<basic_letter>(obj);

		ex offset = obj_letter.get_index() - n + index;

		if ( offset.info(info_flags::integer) )
		  {
		    // ncmul type is basic_letter, therefore expand should be safe
		    newletter = newletter*obj;
		    newletter = newletter.expand();
		  }
		else 
		  {
		    prefactor.push_back(obj);
		  }
	      } // end basic_letter
	    else if ( is_a<list_of_tgamma>(obj) )
	      {
		const list_of_tgamma& obj_list = ex_to<list_of_tgamma>(obj);

		ex offset = obj_list.get_index() - n + index;

		if ( offset.info(info_flags::integer) )
		  {
		    new_lst_of_gammas = new_lst_of_gammas*obj; 
		  }
		else
		  {
		    prefactor.push_back(obj);
		  }

	      } // end list_of_tgamma
	    else if ( is_a<Zsum>(obj) )
	      {
		const Zsum& obj_subsum = ex_to<Zsum>(obj);

		ex offset = obj_subsum.get_index() - n + index;

		if ( offset.info(info_flags::integer) )
		  {
		    hard_core.push_back(obj);
		  }
		else
		  {
		    prefactor.push_back(obj);
		  }

	      } // end Zsum
	    else if ( is_a<Ssum>(obj) )
	      {
		const Ssum& obj_subsum = ex_to<Ssum>(obj);

		ex offset = obj_subsum.get_index() - n + index;

		if ( offset.info(info_flags::integer) )
		  {
		    hard_core.push_back(Ssum_to_Zsum(obj));
		  }
		else
		  {
		    prefactor.push_back(obj);
		  }

	      } // end Ssum
	    else 
	      {
		// default, scalar
		prefactor.push_back(obj);
	      } // end default
	  } // end for j = ...

	ex pre = (new ncmul(prefactor))->setflag(status_flags::dynallocated);
	if ( hard_core.size() == 0 ) hard_core.push_back(create_Zsum(n-index-1,lst()));
	ex hard = (new ncmul(hard_core))->setflag(status_flags::dynallocated);
	hard = nestedsums_helper_expand(hard);
	ex res = pre*create_transcendental_sum_type_B(n,index,letter,newletter,lst_of_gammas,new_lst_of_gammas,
						     subsum,hard,
						     expansion_parameter,order,flag_expand_status);
	return res;
      } // end distribution over subsum

    // basic letter
    if ( is_a<basic_letter>(subsum_rev))
      {
	const basic_letter& obj_letter = ex_to<basic_letter>(subsum_rev);

	ex offset = obj_letter.get_index() - n + index;

	if ( offset.info(info_flags::integer) )
	  {
	    ex newletter = letter_rev * subsum_rev;
	    newletter = newletter.expand();
	    return create_transcendental_sum_type_B(n,index,letter,newletter,
		     lst_of_gammas,lst_of_gammas_rev,subsum,create_Zsum(n-index-1,lst()),
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum_rev * create_transcendental_sum_type_B(n,index,letter,letter_rev,
			     lst_of_gammas,lst_of_gammas_rev,subsum,create_Zsum(n-index-1,lst()),
			     expansion_parameter,order,flag_expand_status);
	  }
      } // end basic_letter

    // list_of_tgamma
    if ( is_a<list_of_tgamma>(subsum_rev))
      {
	const list_of_tgamma& obj_list = ex_to<list_of_tgamma>(subsum_rev);

	ex offset = obj_list.get_index() - n + index;

	if ( offset.info(info_flags::integer) )
	  {
	    return create_transcendental_sum_type_B(n,index,letter,letter_rev,
		     lst_of_gammas,lst_of_gammas_rev*subsum_rev,subsum,create_Zsum(n-index-1,lst()),
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum_rev * create_transcendental_sum_type_B(n,index,letter,letter_rev,
			     lst_of_gammas,lst_of_gammas_rev,subsum,create_Zsum(n-index-1,lst()),
			     expansion_parameter,order,flag_expand_status);
	  }
      } // end list_of_tgamma

    // Ssum
    if ( is_a<Ssum>(subsum_rev))
      {
	const Ssum& obj = ex_to<Ssum>(subsum_rev);

	ex offset = obj.get_index() - n + index;

	if ( offset.info(info_flags::integer) )
	  {
	    return create_transcendental_sum_type_B(n,index,letter,letter_rev,
		     lst_of_gammas,lst_of_gammas_rev,subsum,nestedsums_helper_expand(Ssum_to_Zsum(subsum_rev)),
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum_rev * create_transcendental_sum_type_B(n,index,letter,letter_rev,
			     lst_of_gammas,lst_of_gammas_rev,subsum,create_Zsum(index-1,lst()),
			     expansion_parameter,order,flag_expand_status);
	  }
      } // end Ssum

    // default: anything else, take it out of the sum
    if ( !is_a<Zsum>(subsum_rev) )
      {
	return subsum_rev * create_transcendental_sum_type_B(n,index,letter,letter_rev,lst_of_gammas,lst_of_gammas_rev,
							     subsum,create_Zsum(n-index-1,lst()),
							     expansion_parameter,order,flag_expand_status);
      }

    return this->hold();
  }


  /**
   *
   * letter is allowed to contain a sum of products (e.g. an expression in expanded form).
   * Each term can contain scalars and basic_letters.
   *
   * This routine converts the transcendental_sum_type_B to a canonical form,
   * so that afterwards letter only contains a basic_letter.
   *
   */
  ex transcendental_sum_type_B::distribute_over_letter(void) const
  {
    // letter has to be expanded !!!
    //
    // addition
    if ( is_a<add>(letter))
      {
	int j;
	ex res = 0;
	for (j=0;j<letter.nops();j++)
	  {
	    res = res + create_transcendental_sum_type_B(n,index,letter.op(j),letter_rev,
							lst_of_gammas,lst_of_gammas_rev,subsum,subsum_rev,
							expansion_parameter,order,flag_expand_status);
	  }
	return res;
      }

    // multiplication
    if ( is_a<mul>(letter) || is_a<ncmul>(letter) )
      {
	int j;
	int up_limit = static_cast<int>(letter.nops());
	exvector prefactor;
	exvector hard_core;
	prefactor.reserve(up_limit);
	hard_core.reserve(up_limit);
	for (j=0;j<up_limit;j++)
	  {
	    if ( is_a<basic_letter>(letter.op(j)) )
	      {
		hard_core.push_back(letter.op(j));
	      } 
	    else 
	      {
		prefactor.push_back(letter.op(j));
	      } 
	  }

	// avoid infinte loop if two letters cannot be multiplied
	if ( hard_core.size() > 1 ) return this->hold();

	ex pre = (new ncmul(prefactor))->setflag(status_flags::dynallocated);
	ex hard = (new ncmul(hard_core))->setflag(status_flags::dynallocated);
	ex res = pre*create_transcendental_sum_type_B(n,index,hard,letter_rev,
						     lst_of_gammas,lst_of_gammas_rev,subsum,subsum_rev,
						     expansion_parameter,order,flag_expand_status);
	return res;
      }

    return this->hold();
  }


  /**
   *
   * letter_rev is allowed to contain a sum of products (e.g. an expression in expanded form).
   * Each term can contain scalars and basic_letters.
   *
   * This routine converts the transcendental_sum_type_B to a canonical form,
   * so that afterwards letter_rev only contains a basic_letter.
   *
   */
  ex transcendental_sum_type_B::distribute_over_letter_rev(void) const
  {
    // addition
    if ( is_a<add>(letter_rev))
      {
	int j;
	ex res = 0;
	for (j=0;j<letter_rev.nops();j++)
	  {
	    res = res + create_transcendental_sum_type_B(n,index,letter,letter_rev.op(j),
							lst_of_gammas,lst_of_gammas_rev,subsum,subsum_rev,
							expansion_parameter,order,flag_expand_status);
	  }
	return res;
      }

    // multiplication
    if ( is_a<mul>(letter_rev) || is_a<ncmul>(letter_rev) )
      {
	int j;
	int up_limit = static_cast<int>(letter_rev.nops());
	exvector prefactor;
	exvector hard_core;
	prefactor.reserve(up_limit);
	hard_core.reserve(up_limit);
	for (j=0;j<up_limit;j++)
	  {
	    if ( is_a<basic_letter>(letter_rev.op(j)) )
	      {
		hard_core.push_back(letter_rev.op(j));
	      } 
	    else 
	      {
		prefactor.push_back(letter_rev.op(j));
	      } 
	  }

	// avoid infinte loop if two letters cannot be multiplied
	if ( hard_core.size() > 1 ) return this->hold();

	ex pre = (new ncmul(prefactor))->setflag(status_flags::dynallocated);
	ex hard = (new ncmul(hard_core))->setflag(status_flags::dynallocated);
	ex res = pre*create_transcendental_sum_type_B(n,index,letter,hard,
						     lst_of_gammas,lst_of_gammas_rev,subsum,subsum_rev,
						     expansion_parameter,order,flag_expand_status);
	return res;
      }

    return this->hold();
  }

  /**
   *
   * Explicit evaluation
   *
   */
  ex transcendental_sum_type_B::eval_explicit() const
  {
    // n is a integer : evaluate the sum
    if ( n.info(info_flags::integer) )
      {
	int i;
	ex res = 0 ;
	ex temp, temp_rev;
	const Zsum& Z = ex_to<Zsum>(subsum);
	const Zsum& Z_rev = ex_to<Zsum>(subsum_rev);

	for (i=1;i<n;i++)
	  {
	    temp = Z.set_index( Z.get_index() - index + i );
	    temp_rev = Z_rev.set_index( Z_rev.get_index() + index - i );
	      if ( (temp != 0) && (temp_rev != 0) ) 
		{
		  res = res 
		  + ex_to<basic_letter>(letter).set_index(i)
		  * temp
		  * ex_to<basic_letter>(letter_rev).set_index(n-i)
		  * temp_rev
		  * nestedsums_helper_multiply_laurent(
                     ex_to<list_of_tgamma>(lst_of_gammas).set_index(i),
                     ex_to<list_of_tgamma>(lst_of_gammas_rev).set_index(n-i),
                     expansion_parameter,order);
		}
	  }
	return res;
      }

    return this->hold();

  }

  /**
   *
   * This routine performs the substitution index -> index - 1.
   * The formula used is
   *  \f[
   *     \sum\limits_{i=1}^{n-1} 
   *       \frac{x^i}{(i+c)^m} 
   *       \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+c_1+d_1\varepsilon)} ...
   *       Z(i-1+o,m_1,...,m_l,x_1,...,x_l)
   *       \cdot
   *       \frac{y^{n-i}}{(n-i+c')^{m'}} 
   *       \frac{\Gamma(n-i+a_1'+b_1'\varepsilon)}{\Gamma(n-i+c_1'+d_1'\varepsilon)} ...
   *       Z(n-i-1+o',m_1',...,m_{l'}',x_1',...,x_{l'}')
   *  \f] \f[
   *  = x \sum\limits_{i=1}^{n-2} 
   *       \frac{x^i}{(i+c+1)^m} 
   *       \frac{\Gamma(i+a_1+1+b_1\varepsilon)}{\Gamma(i+c_1+1+d_1\varepsilon)} ...
   *       Z(i+o,m_1,...,m_l,x_1,...,x_l)
   *       \cdot
   *       \frac{y^{n-1-i}}{(n-1-i+c')^{m'}} 
   *       \frac{\Gamma(n-1-i+a_1'+b_1'\varepsilon)}{\Gamma(n-1-i+c_1'+d_1'\varepsilon)} ...
   *       Z(n-1-i-1+o',m_1',...,m_{l'}',x_1',...,x_{l'}')
   *  \f] \f[
   *     + \frac{x}{(c+1)^m} 
   *       \frac{\Gamma(a_1+1+b_1\varepsilon)}{\Gamma(c_1+1+d_1\varepsilon)} ...
   *       Z(o,m_1,...,m_l,x_1,...,x_l)
   *       \cdot
   *       \frac{y^{n-1}}{(n-1+c')^{m'}} 
   *       \frac{\Gamma(n-1+a_1'+b_1'\varepsilon)}{\Gamma(n-1+c_1'+d_1'\varepsilon)} ...
   *       Z(n-2+o',m_1',...,m_{l'}',x_1',...,x_{l'}')
   *       Z(n-2)
   * \f]
   * This routine is called from eval/expansion_required, and eval/check_for_poles.
   *
   */
  ex transcendental_sum_type_B::shift_plus_one(void) const
  {
    // n = Infinity does not occur

    ex x = ex_to<basic_letter>(letter).get_scale();

    ex term_1 = 0;

    ex temp = create_Zsum( ex_to<Zsum>(subsum).get_index() - index + 1,
			   ex_to<Zsum>(subsum).get_letter_list());

    if ( temp != 0 ) 
      {
	term_1 = x * pow(1+ex_to<basic_letter>(letter).get_offset(),-ex_to<basic_letter>(letter).get_degree())
	  * ex_to<list_of_tgamma>(lst_of_gammas).index_eq_one()
	  * temp
	  * ex_to<basic_letter>(letter_rev).set_index(n-1)
	  * ex_to<list_of_tgamma>(lst_of_gammas_rev).set_index(n-1)
	  * create_Zsum( ex_to<Zsum>(subsum_rev).get_index() + index - 1,
			 ex_to<Zsum>(subsum_rev).get_letter_list())
	  * create_Zsum(n-2,_empty_list);
      }

    // we set the flag back to expansion_required, since we shifted the subsum
    return x*create_transcendental_sum_type_B(n-1,
					      index,
					      ex_to<basic_letter>(letter).shift_plus_one(),
					      ex_to<basic_letter>(letter_rev).set_index(n-1-index),
					      ex_to<list_of_tgamma>(lst_of_gammas).shift_plus_one(),
					      ex_to<list_of_tgamma>(lst_of_gammas_rev).set_index(n-1-index),
					      ex_to<Zsum>(subsum).shift_plus_one(),
					      ex_to<Zsum>(subsum_rev).shift_minus_one(),
					      expansion_parameter,
					      order,
					      expand_status::expansion_required)
      + term_1 ;

  }

  /**
   *
   * This routine takes out the term at index = n - 1.
   * The formula used is
   *  \f[
   *     \sum\limits_{i=1}^{n-1} 
   *       \frac{x^i}{(i+c)^m} 
   *       \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+c_1+d_1\varepsilon)} ...
   *       Z(i-1+o,m_1,...,m_l,x_1,...,x_l)
   *       \cdot
   *       \frac{y^{n-i}}{(n-i+c')^{m'}} 
   *       \frac{\Gamma(n-i+a_1'+b_1'\varepsilon)}{\Gamma(n-i+c_1'+d_1'\varepsilon)} ...
   *       Z(n-i-1+o',m_1',...,m_{l'}',x_1',...,x_{l'}')
   *  \f] \f[
   *  = y \sum\limits_{i=1}^{n-2} 
   *       \frac{x^i}{(i+c)^m} 
   *       \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+c_1+d_1\varepsilon)} ...
   *       Z(i-1+o,m_1,...,m_l,x_1,...,x_l)
   *       \cdot
   *       \frac{y^{n-1-i}}{(n-1-i+c'+1)^{m'}} 
   *       \frac{\Gamma(n-1-i+a_1'+1+b_1'\varepsilon)}{\Gamma(n-1-i+c_1'+1+d_1'\varepsilon)} ...
   *       Z(n-1-i+o',m_1',...,m_{l'}',x_1',...,x_{l'}')
   *  \f] \f[
   *     + \frac{x^{n-1}}{(n-1+c)^m} 
   *       \frac{\Gamma(n-1+a_1+b_1\varepsilon)}{\Gamma(n-1+c_1+d_1\varepsilon)} ...
   *       Z(n-2+o,m_1,...,m_l,x_1,...,x_l)
   *       \cdot
   *       \frac{y}{(1+c')^{m'}} 
   *       \frac{\Gamma(a_1'+1+b_1'\varepsilon)}{\Gamma(c_1'+1+d_1'\varepsilon)} ...
   *       Z(o',m_1',...,m_{l'}',x_1',...,x_{l'}')
   *       Z(n-2)
   * \f]
   * This routine is called from eval/expansion_required, and eval/check_for_poles.
   *
   */
  ex transcendental_sum_type_B::shift_plus_one_rev(void) const
  {
    // n = Infinity does not occur

    ex y = ex_to<basic_letter>(letter_rev).get_scale();

    ex term_1 = 0;

    ex temp = create_Zsum( ex_to<Zsum>(subsum_rev).get_index() + index - n + 1,
			   ex_to<Zsum>(subsum_rev).get_letter_list());

    if ( temp != 0 ) 
      {
	term_1 = y * pow(1+ex_to<basic_letter>(letter_rev).get_offset(),-ex_to<basic_letter>(letter_rev).get_degree())
	  * ex_to<list_of_tgamma>(lst_of_gammas_rev).index_eq_one()
	  * temp
	  * ex_to<basic_letter>(letter).set_index(n-1)
	  * ex_to<list_of_tgamma>(lst_of_gammas).set_index(n-1)
	  * create_Zsum( ex_to<Zsum>(subsum).get_index() - index + n - 1,
			 ex_to<Zsum>(subsum).get_letter_list())
	  * create_Zsum(n-2,_empty_list);
      }

    // we set the flag back to expansion_required, since we shifted the subsum
    return y*create_transcendental_sum_type_B(n-1,
					      index,
					      letter,
					      ex_to<basic_letter>(
	 					 ex_to<basic_letter>(letter_rev).shift_plus_one()).set_index(n-1-index),
					      lst_of_gammas,
					      ex_to<list_of_tgamma>(
						   ex_to<list_of_tgamma>(lst_of_gammas_rev).shift_plus_one()).set_index(n-1-index),
					      subsum,
					      subsum_rev,
					      expansion_parameter,
					      order,
					      expand_status::expansion_required)
      + term_1 ;

  }

  // utility functions

  /**
   *
   * Stop and go
   *
   */
  ex create_transcendental_sum_type_B_and_expand(const ex & nn, const ex & i, const ex & l, const ex & lr, 
					       const ex & v, const ex & vr, const ex & ss, const ex & ssr, 
					       const ex & eps, int o)
  {
      // stop and go
      _nestedsums_evaluation_veto_type_B = expand_status::do_outermost_sum;
      ex expr = 
	create_transcendental_sum_type_B_and_set_gammas(nn,i,l,lr,v,vr,ss,ssr,eps,o,
							expand_status::expansion_required);
      expr = nestedsums_helper_sort(expr,lst{eps});

      _nestedsums_evaluation_veto_type_B = expand_status::zombie;
      expr = nestedsums_helper_eval(expr);

      return expr;
  }

} // namespace nestedsums

