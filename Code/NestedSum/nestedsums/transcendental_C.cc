
/** @file transcendental_C.cc
 *
 * Implementation of transcendental_sum_type_C
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

GINAC_IMPLEMENT_REGISTERED_CLASS(transcendental_sum_type_C, basic)

GINAC_BIND_UNARCHIVER(transcendental_sum_type_C);



  transcendental_sum_type_C::transcendental_sum_type_C() : inherited(),
   n(_default), index(_default_index), letter(_default), lst_of_gammas(_empty_list_of_tgamma), subsum(_default),
   expansion_parameter(_default), order(0), flag_expand_status(expand_status::start)
  { 
  }

  void transcendental_sum_type_C::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("n",n);
    node.add_ex("index",index);
    node.add_ex("letter",letter);
    node.add_ex("lst_of_gammas",lst_of_gammas);
    node.add_ex("subsum",subsum);
    node.add_ex("expansion_parameter",expansion_parameter);

    node.add_ex("order",numeric(order));
    node.add_ex("flag_expand_status",numeric(flag_expand_status));
  }

  void transcendental_sum_type_C::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("n",n,sym_lst);
    node.find_ex("index",index,sym_lst);
    node.find_ex("letter",letter,sym_lst);
    node.find_ex("lst_of_gammas",lst_of_gammas,sym_lst);
    node.find_ex("subsum",subsum,sym_lst);
    node.find_ex("expansion_parameter",expansion_parameter,sym_lst);

    ex ex_order, ex_flag_expand_status;
    node.find_ex("order",ex_order,sym_lst);
    node.find_ex("flag_expand_status",ex_flag_expand_status,sym_lst);
    order = ex_to<numeric>(ex_order).to_int();
    flag_expand_status = ex_to<numeric>(ex_flag_expand_status).to_int();
  }

  int transcendental_sum_type_C::compare_same_type(const basic &other) const
  {
    const transcendental_sum_type_C &o = static_cast<const transcendental_sum_type_C &>(other);

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
  transcendental_sum_type_C::transcendental_sum_type_C(const ex & nn, const ex & i, const ex & l, const ex & v,
						     const ex & ss, const ex & eps, int o, int f) : 
    inherited(), n(nn), index(i), letter(l), lst_of_gammas(v), subsum(ss),
    expansion_parameter(eps), order(o), flag_expand_status(f)
  { }

  // functions overriding virtual functions from bases classes

  unsigned transcendental_sum_type_C::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= n.gethash();

      v = rotate_left_31(v);
      v ^= index.gethash();

      v = rotate_left_31(v);
      v ^= letter.gethash();

      v = rotate_left_31(v);
      v ^= lst_of_gammas.gethash();

      v = rotate_left_31(v);
      v ^= subsum.gethash();

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

  void transcendental_sum_type_C::print(const print_context & c, unsigned level) const
  {
    if (is_a<print_latex>(c)) {
      if (precedence() <= level) c.s << "{(";
      c.s << "\\sum_{" ;
      index.print(c);
      c.s << "= 1}^{";
      n.print(c);
      c.s << "} C ";
      letter.print(c,mul_precedence);
      lst_of_gammas.print(c);
      subsum.print(c,mul_precedence);
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
	lst_of_gammas.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	subsum.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	expansion_parameter.print(c, level + static_cast<const print_tree &>(c).delta_indent);
      } 
    else {
      c.s << "sum(" ;
      index.print(c);
      c.s << "= 1..";
      n.print(c);
      c.s << ", C ";
      letter.print(c,mul_precedence);
      if ( ex_to<list_of_tgamma>(lst_of_gammas).get_depth() > 0 )
	{
	  c.s << "*";
	  lst_of_gammas.print(c);
	}
      c.s << "*";
      subsum.print(c,mul_precedence);
      c.s << ")";
    }
  }

  /**
   *
   * Simplifications, which are always performed are:
   * 
   * - If subsum is equal to 1, the subsum is replaced with S(i).
   *
   * - If subsum is not of type Ssum, the routine distribute_over_subsum is called.
   * 
   * - If the difference of the upper summation index of the Ssum with the index member is not
   *   an integer, the Ssum is taken out of the sum. The subsum is replaced with S(i).
   *
   * - If letter is not of type basic_letter, the routine distribute_over_letter is called.
   * 
   * - If the difference of the index of the basic_letter with the index member is not
   *   zero, the index in basic_letter is adjusted.
   *
   * - If the difference of the index of lst_of_gammas with the index member is not
   *   zero, the index in lst_of_gammas is adjusted.
   *
   * If flag_expand_status == expand_status::expansion_required, the evaluation routine
   * performs a set of consistency checks:
   *
   * - It adjusts the upper summation limit in subsum to index. 
   *   If \f$ o > 0 \f$ the function Ssum::adjust_upper_limit_downwards(index) is used.
   *   If \f$ o < 0 \f$ the function shift_plus_one() is called.
   *
   * - It checks, that letter does not give rise to poles 
   *   (e.g. that the offset \f$c\f$ is a non-negative integer or a negative integer 
   *    larger or equal to \f$c \ge o \f$).
   *
   *
   * - It checks, that the \f$a_j\f$ in the Gamma functions are integers.
   *
   * If one of the tests fails, the object is put into a zombie state.
   *
   * If flag_expand_status == expand_status::check_for_poles, it assures
   * that the Gamma functions in the numerator do not give rise to poles.
   * The function shift_plus_one() is used.
   *
   * If flag_expand_status == expand_status::expand_gamma_functions, the Gamma functions are expanded
   * into Euler Zagier sums.
   * This is done by setting the expansion_required flag in the ratio_of_tgamma class.
   * 
   * If flag_expand_status == expand_status::adjust_summation_index, we deal with sums of the form
   * \f[
   *     \mbox{} - \sum\limits_{i=1}^n 
   *       \left( \begin{array}{c} n \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *      \frac{x^i}{(i+c)^m} S(i,...)
   * \f]
   * with \f$c \ge 0\f$.
   * Here eval adjusts the offset.
   * In the case \f$c > 0\f$ the function shift_minus_one() is called.
   * The function shift_minus_one() does not change the upper summation limit of the subsum
   * (this avoids an infinite recursion).
   *
   * If flag_expand_status == expand_status::do_hoelder_convolution, we deal with sums of the form
   * \f[
   *     \mbox{} - \sum\limits_{i=1}^n 
   *       \left( \begin{array}{c} n \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *      \frac{x^i}{i^m} S(i,...)
   * \f]
   * The S-sum is first brought to a standard form, which ensures that negative degrees are removed.
   * The function Ssum::remove_negative_degrees() is used for that.
   * We then check if \f$m\f$ is negative.
   * In that case the function shift_plus_one() is called. 
   * We then can assume that \f$m\f$ is non-negative and that the subsum does not contain negative degrees.
   * \f$S(i,...)\f$ is then rewritten as
   * \f[
   *    S(i;m_1,...,m_k;x_1,...,x_k) 
   * \f] \f[
   *    = S(N;m_1,...,m_k;x_1,...,x_k) 
   * \f] \f[
   *     \mbox{} - S(N;m_2,...,m_k;x_2,...,x_k) \cdot 
   *          \left( \sum\limits_{i_1=i+1}^N 
   *                    \frac{x_1^{i_1}}{i_1^{m_1}} \right)
   * \f] \f[
   *     + S(N;m_3,...,m_k;x_3,...,x_k) \cdot 
   *          \left( \sum\limits_{i_1=i+1}^N \sum\limits_{i_2=i_1+1}^N 
   *                 \frac{x_1^{i_1}}{i_1^{m_1}} \frac{x_2^{i_2}}{i_2^{m_2}} \right) 
   * \f] \f[
   *     \mbox{}  - ... + (-1)^k \cdot \left(\sum\limits_{i_1=i+1}^N \sum\limits_{i_2=i_1+1}^N 
   *                                      ... \sum\limits_{i_k=i_{k-1}+1}^N 
   *                                    \frac{x_1^{i_1}}{i_1^{m_1}} 
   *                                    \frac{x_2^{i_2}}{i_2^{m_2}} ...
   *                                    \frac{x_k^{i_k}}{i_k^{m_k}} \right)
   * \f]
   * Each term is a product of a Ssum at infinity and a sum of type "Csum".
   * The Ssum at infinity is converted to a Zsum at infinity and expressed in terms of multiple
   * polylogarithms.
   * The evaluation of the Csum is done in its proper evaluation routine.
   *
   */
  ex transcendental_sum_type_C::eval() const
  {
#ifdef _DEBUG
    if ( _debug_level & 4 ) 
      {
	std::cout << " ---------------------------- " << std::endl;
	std::cout << std::endl;
	std::cout << "entering eval type C" << std::endl;
	std::cout << std::endl;
	std::cout << "n         : " << n << std::endl;
	std::cout << "index     : " << index << std::endl;
	std::cout << "letter    : " << letter << std::endl;
	std::cout << "gammas    : " << lst_of_gammas << std::endl;
	std::cout << "subsum    : " << subsum << std::endl;
      }
#endif // def _DEBUG

    // subsum has to be expanded !!!
    if ( !is_a<Ssum>(subsum) )
      {
	return distribute_over_subsum();
      }

    // assert subsum of type Ssum
    ex diff_indices = ex_to<Ssum>(subsum).get_index() - index;

    if ( !diff_indices.info(info_flags::integer) )
      {
	return subsum * create_transcendental_sum_type_C(n,index,letter,lst_of_gammas,create_Ssum(index,lst()),
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
	return create_transcendental_sum_type_C(n,index,ex_to<basic_letter>(letter).shift_index(index),lst_of_gammas,subsum,
		expansion_parameter,order,flag_expand_status);
      }


    // adjust index in list_of_tgamma
    if ( ex_to<list_of_tgamma>(lst_of_gammas).get_depth() > 0 )
      {
	ex diff_indices_gamma = ex_to<list_of_tgamma>(lst_of_gammas).get_index() - index;

	if ( !diff_indices_gamma.is_zero() )
	  {
	    return create_transcendental_sum_type_C(n,index,letter,ex_to<list_of_tgamma>(lst_of_gammas).shift_index(index),subsum,
					       expansion_parameter,order,flag_expand_status);
	  }
      }

    // ---------------
    if ( ( flag_expand_status == expand_status::expansion_required )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_C ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 4 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering expansion_required" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	int temp_zombie_flag = 0;

	// check for index in subsum 
	ex up_diff = ex_to<Ssum>(subsum).get_index() - index ;

	if (up_diff.info(info_flags::posint))
	  {
	    // return adjusted object
	    return create_transcendental_sum_type_C(n,index,letter,lst_of_gammas,
						    ex_to<Ssum>(subsum).adjust_upper_limit_downwards(index),
						    expansion_parameter,order,flag_expand_status);
	  }
	else if (up_diff.info(info_flags::negint))
	  {

	    return this->shift_plus_one();

	  } // updiff negint


	// check that there are no poles in letter
	// offset in subsum already reduced to zero here
	ex c = ex_to<basic_letter>(letter).get_offset();
	if (c.info(info_flags::integer))
	  {
	    if (c.info(info_flags::negint))
	      {
		// c is negative
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
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_C ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 4 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering check_for_poles" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	int flag = ex_to<list_of_tgamma>(lst_of_gammas).pole_alert();

	if ( flag>0 ) return this->shift_plus_one();

	// no poles, go to next step
	flag_expand_status = expand_status::expand_gamma_functions;

      } // end if check_for_poles

    // ---------------
    if ( ( flag_expand_status == expand_status::expand_gamma_functions )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_C ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 4 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering expand_gamma_functions" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	if ( ex_to<list_of_tgamma>(lst_of_gammas).get_depth() > 0 )
	  {
	    ex pre = ex_to<list_of_tgamma>(lst_of_gammas).set_expansion();
	    pre = Zsum_to_Ssum(pre);
	    pre = shift_upper_limit_plus_one_for_Ssum(pre);
	    pre = pre * subsum;
	    pre = nestedsums_helper_expand(pre);

	    return create_transcendental_sum_type_C_and_set_gammas(n,index,letter,_empty_list_of_tgamma,pre,
					       expansion_parameter,order,expand_status::adjust_summation_index);
	  }

	// nothing to expand
	flag_expand_status = expand_status::adjust_summation_index;

      } // end if expand_gamma_functions


    // ---------------
    if ( ( flag_expand_status == expand_status::adjust_summation_index )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_C ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 4 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering adjust_summation_index" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	// have   C circ x^n/(n+c)^m S(n,...) 

	ex c = ex_to<basic_letter>(letter).get_offset();

	if (c.info(info_flags::posint)) return this->shift_minus_one();

	//  c = 0
	flag_expand_status = expand_status::do_hoelder_convolution;

      } // end if adjust_summation_index


    // ---------------
    if ( ( flag_expand_status == expand_status::do_hoelder_convolution )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_C ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 4 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering do_hoelder_convolution" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	ex res;
	    
	if (_flag_table_transcendental_sum_type_C) // use hash tables 
	  {
	    unsigned key = this->get_key();

	    std::map<unsigned, ex>::iterator p = _table_transcendental_sum_type_C.find(key);
	    if ( p != _table_transcendental_sum_type_C.end() )
	      {
		const hash_entry& he = ex_to<hash_entry>( p->second );

		if ( he.hash_data().is_equal( this->hash_data() ) )
		  {
		    _count_table_transcendental_sum_type_C++;
		    return he.return_value( this->subst_data() );
		  }
		else
		  {
		    flag_expand_status = expand_status::hoelder_hash_checked;
		  }
	      }
	    else
	      {
		res = create_transcendental_sum_type_C(n,index,letter,lst_of_gammas,subsum,
						       expansion_parameter,order,
						       expand_status::hoelder_hash_checked);
		_table_transcendental_sum_type_C[key] = create_hash_entry( this->hash_data(), 0, res, 0 );

		return res;
	      }
	  }
	else // don't use hash tables
	  {
	    flag_expand_status = expand_status::hoelder_hash_checked;
	  }

      } // end if do_hoelder_convolution

    // ---------------
    if ( ( flag_expand_status == expand_status::hoelder_hash_checked )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_C ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 4 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering hoelder_hash_checked" << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	// have   C circ x^n/n^m S(n,...) 

	// assure that Ssum is in standard form
	// 03.11.2001 removes also degree zero for x<>1 now
	// 21.01.2002 nestedsums_helper_expand is called
	//            flag set to expansion_required
	if ( ex_to<Ssum>(subsum).flag_remove_negative_degrees() )
	  {
	    return create_transcendental_sum_type_C(n,index,
						   letter,
						   lst_of_gammas,
						    nestedsums_helper_expand(
									   ex_to<Ssum>(subsum).remove_negative_degrees()),
						   expansion_parameter,order,
						   expand_status::expansion_required);
	  }

        // m negative ?
	if ( ex_to<basic_letter>(letter).get_degree() < 0 ) return this->shift_plus_one();

        // m non-negative now
	int i,j;
	ex res = 0;

	ex l_temp = ex_to<Ssum>(subsum).get_letter_list();

	for (j=0;j<=l_temp.nops();j++)
	  {
	    // C_list contains at least x0-letter
	    exvector S_list;
	    exvector C_list;
	    S_list.reserve(l_temp.nops()-j);
	    C_list.reserve(j+1);

	    //	    C_list.push_back(ex_to<letter>(letter).forget_index());
	    C_list.push_back(ex_to<basic_letter>(letter).forget_index());
	    /*
	    C_list.push_back(
                  create_letter(ex_to<basic_letter>(letter).get_scale(),
                                ex_to<basic_letter>(letter).get_degree() ));
	    */

	    for (i=j;i<l_temp.nops();i++)
	      {
		S_list.push_back(l_temp.op(i));
	      }

	    for (i=0;i<j;i++)
	      {
		C_list.push_back(l_temp.op(i));
	      }

	    res = res 
	      + nestedsums_helper_expand(
              GiNaC::pow(-1,j)
		 *create_Ssum_from_exvector(Infinity,S_list)
		 *convert_Csum_to_Ssum(create_Csum_from_exvector(n,C_list)) )
	      ;
	  }

	// 28.12.2001 remove_trivial_Ssum commented out
	//	res = remove_trivial_Ssum(res);
	res = Ssum_to_Zsum(res);
	return res;

      } // end if do_hoelder_convolution


    // n integer
    if ( n.info(info_flags::integer) ) return this->eval_explicit();

    // default
    return this->hold();

  }


  /**
   *
   * No automatic simplifications
   *
   */
  ex transcendental_sum_type_C::eval_ncmul(const exvector & v) const
  {

    // default
    return hold_ncmul(v);

  }

  ex transcendental_sum_type_C::derivative(const symbol & s) const
  {
    return 0;
  }

  ex transcendental_sum_type_C::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_transcendental_sum_type_C(n.subs(m,options),index.subs(m,options),letter.subs(m,options),lst_of_gammas.subs(m,options),
					   subsum.subs(m,options),expansion_parameter.subs(m,options),order,flag_expand_status);
  }

  // new virtual functions

  /**
   *
   * The hash key is calculated from the hash_data.
   *
   */
  unsigned transcendental_sum_type_C::get_key(void) const
  {
    return this->hash_data().gethash();
  }

  /**
   *
   * The summation index is a redundant variable and
   * does not influence the hash_data.
   *
   */
  ex transcendental_sum_type_C::hash_data(void) const
  {
    return lst{n,
	       ex_to<basic_letter>(letter).forget_index(),
	       ex_to<Ssum>(subsum).get_letter_list()
	       };
  }

  /**
   *
   * No substitutions necessary.
   *
   */
  ex transcendental_sum_type_C::subst_data(void) const
  {
    return 0;
  }


  // non-virual functions

  /**
   *
   * Sets the flag flag_expand_status to expand_status::expansion_required.
   * The object is then automatically expanded up to the order specified in the
   * member variable order.
   *
   */
  ex transcendental_sum_type_C::set_expansion(void) const
  {
    transcendental_sum_type_C* res = new transcendental_sum_type_C(n,index,letter,lst_of_gammas,subsum,expansion_parameter,
								 order,expand_status::expansion_required);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * subsum is allowed to contain a sum of products (e.g. an expression in expanded form).
   * Each term can contain scalars, basic_letters, list_of_tgammas, Zsums or Ssums.
   *
   * This routine converts the transcendental_sum_type_C to a canonical form,
   * so that afterwards subsum only contains a Ssum.
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
   * - If an object is of type Ssum and the difference of its index with 
   *   the index member is an integer, it is stays inside the subsum.
   *   Otherwise it is taken out of the sum.
   *
   * - If an object is of type Zsum and the difference of its index with 
   *   the index member is an integer, it is converted to an Ssum and stays inside the subsum.
   *   Otherwise it is taken out of the sum.
   *
   */
  ex transcendental_sum_type_C::distribute_over_subsum(void) const
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
	    res = res + create_transcendental_sum_type_C(n,index,letter,lst_of_gammas,subsum.op(j),
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
	    else if ( is_a<Ssum>(obj) )
	      {
		const Ssum& obj_subsum = ex_to<Ssum>(obj);

		ex offset = obj_subsum.get_index() - index;

		if ( offset.info(info_flags::integer) )
		  {
		    hard_core.push_back(obj);
		  }
		else
		  {
		    prefactor.push_back(obj);
		  }

	      } // end Ssum
	    else if ( is_a<Zsum>(obj) )
	      {
		const Zsum& obj_subsum = ex_to<Zsum>(obj);

		ex offset = obj_subsum.get_index() - index;

		if ( offset.info(info_flags::integer) )
		  {
		    hard_core.push_back(Zsum_to_Ssum(obj));
		  }
		else
		  {
		    prefactor.push_back(obj);
		  }

	      } // end Zsum
	    else 
	      {
		// default, scalar
		prefactor.push_back(obj);
	      } // end default
	  } // end for j = ...

	ex pre = (new ncmul(prefactor))->setflag(status_flags::dynallocated);
	if ( hard_core.size() == 0 ) hard_core.push_back(create_Ssum(index,lst()));
	ex hard = (new ncmul(hard_core))->setflag(status_flags::dynallocated);
	hard = nestedsums_helper_expand(hard);
	ex res = pre*create_transcendental_sum_type_C(n,index,newletter,new_lst_of_gammas,hard,
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
	    return create_transcendental_sum_type_C(n,index,newletter,
		     lst_of_gammas,create_Ssum(index,lst()),
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum * create_transcendental_sum_type_C(n,index,letter,
			     lst_of_gammas,create_Ssum(index,lst()),
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
	    return create_transcendental_sum_type_C(n,index,letter,
		     lst_of_gammas*subsum,create_Ssum(index,lst()),
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum * create_transcendental_sum_type_C(n,index,letter,
			     lst_of_gammas,create_Ssum(index,lst()),
			     expansion_parameter,order,flag_expand_status);
	  }
      } // end list_of_tgamma

    // Zsum
    if ( is_a<Zsum>(subsum))
      {
	const Zsum& obj = ex_to<Zsum>(subsum);

	ex offset = obj.get_index() - index;

	if ( offset.info(info_flags::integer) )
	  {
	    return create_transcendental_sum_type_C(n,index,letter,
		     lst_of_gammas,nestedsums_helper_expand(Zsum_to_Ssum(subsum)),
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum * create_transcendental_sum_type_C(n,index,letter,
			     lst_of_gammas,create_Ssum(index,lst()),
			     expansion_parameter,order,flag_expand_status);
	  }
      } // end Zsum

    // default: anything else, take it out of the sum
    if ( !is_a<Ssum>(subsum) )
      {
	return subsum * create_transcendental_sum_type_C(n,index,letter,lst_of_gammas,create_Ssum(index,lst()),
							 expansion_parameter,order,flag_expand_status);
      }

    return this->hold();
  }


  /**
   *
   * letter is allowed to contain a sum of products (e.g. an expression in expanded form).
   * Each term can contain scalars and basic_letters.
   *
   * This routine converts the transcendental_sum_type_C to a canonical form,
   * so that afterwards letter only contains a basic_letter.
   *
   */
  ex transcendental_sum_type_C::distribute_over_letter(void) const
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
	    res = res + create_transcendental_sum_type_C(n,index,letter.op(j),lst_of_gammas,subsum,
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
	ex res = pre*create_transcendental_sum_type_C(n,index,hard,lst_of_gammas,subsum,
						     expansion_parameter,order,flag_expand_status);
	return res;
      }
    // end distribution over letter

    return this->hold();
  }

  /**
   *
   * Explicit evaluation
   *
   */
  ex transcendental_sum_type_C::eval_explicit() const
  {
    // n is a integer : evaluate the sum
    if ( n.info(info_flags::integer) )
      {
	int i;
	ex res = 0 ;
	ex temp;
	const Ssum& Z = ex_to<Ssum>(subsum);

	for (i=1;i<=n;i++)
	  {
	    temp = Z.set_index( Z.get_index() - index + i );
	      if ( temp != 0 ) 
		{
		  res = res 
		  - binomial(n,i) * GiNaC::pow(-1,i)
		  * ex_to<basic_letter>(letter).set_index(i)
		  * ex_to<list_of_tgamma>(lst_of_gammas).set_index(i)
		  * temp;
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
   *     \mbox{} - \sum\limits_{i=1}^{n} 
   *       \left( \begin{array}{c} n \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *       \frac{x^i}{(i+c)^m} 
   *       \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+c_1+d_1\varepsilon)} ...
   *       S(i+o,m_1,...,m_l,x_1,...,x_l)
   *  \f] \f[
   *    = (-x) n (-1)
   *     \sum\limits_{i=1}^{n-1} 
   *       \left( \begin{array}{c} n-1 \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *       \frac{x^i}{(i+c+1)^m} 
   *       \frac{\Gamma(i+a_1+1+b_1\varepsilon)}{\Gamma(i+c_1+1+d_1\varepsilon)} ...
   *       \frac{1}{i+1}
   *       S(i+o+1,m_1,...,m_l,x_1,...,x_l)
   *  \f] \f[
   *   + n \frac{x}{(c+1)^m} 
   *       \frac{\Gamma(a_1+1+b_1\varepsilon)}{\Gamma(c_1+1+d_1\varepsilon)} ...
   *       S(o+1,m_1,...,m_l,x_1,...,x_l)
   *       Z(n-1) 
   *  \f]
   *
   */
  ex transcendental_sum_type_C::shift_plus_one(void) const
  {
    ex x = ex_to<basic_letter>(letter).get_scale();

    ex term_1 = 0;

    ex temp = create_Ssum( ex_to<Ssum>(subsum).get_index() - index + 1,
			   ex_to<Ssum>(subsum).get_letter_list());

    if ( temp != 0 ) 
      {
	term_1 = x * pow(1+ex_to<basic_letter>(letter).get_offset(),-ex_to<basic_letter>(letter).get_degree())
	  * ex_to<list_of_tgamma>(lst_of_gammas).index_eq_one()
	  * create_unit_letter(-1,n)
	  * temp
	  * create_Zsum(n-1,_empty_list);
      }

    // we set the flag back to expansion_required, since we shifted the subsum
    return -x * create_unit_letter(-1,n)
      *create_transcendental_sum_type_C(n-1,index,
					ex_to<basic_letter>(letter).shift_plus_one(),
					ex_to<list_of_tgamma>(lst_of_gammas).shift_plus_one(),
					create_basic_letter(1,1,1,index)
					*ex_to<Ssum>(subsum).shift_plus_one(),
					expansion_parameter,
					order,
					expand_status::expansion_required)
      + term_1 ;

  }


  /**
   *
   * This routine assumes sums of the form
   * \f[
   *     \mbox{} - \sum\limits_{i=1}^n 
   *       \left( \begin{array}{c} n \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *       \frac{x^i}{(i+c)^m} S(i,...)
   * \f]
   * and performs the substitution index -> index + 1.
   *
   * If \f$m \le 0 \f$ we use the binomial formula
   * \f[
   *     \mbox{} - \sum\limits_{i=1}^n 
   *       \left( \begin{array}{c} n \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *       \frac{x^i}{(i+c)^m} S(i,...)
   * \f] \f[
   *    =
   *     \sum\limits_{j=0}^{-m}
   *       \left( \begin{array}{c} -m \\ j \\ \end{array} \right)
   *       c^{-m-j}
   *     \mbox{} (-1) \sum\limits_{i=1}^n 
   *       \left( \begin{array}{c} n \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *       \frac{x^i}{i^{-j}} S(i,...)
   * \f]
   *
   * If the depth of the subsum is zero, we have
   * \f[
   *     \mbox{} - \sum\limits_{i=1}^n 
   *       \left( \begin{array}{c} n \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *       \frac{x^i}{(i+c)^m} S(i)
   * \f] \f[
   *     =
   *       \mbox{} - \frac{1}{x} \frac{1}{n+1} Z(n-1) 
   *         (-1) \sum\limits_{i=1}^{n+1}
   *       \left( \begin{array}{c} n+1 \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *              \frac{x^i}{(i+c-1)^m} i S(i)
   *       + \frac{1}{c^m} Z(n-1)
   * \f]
   *
   * If the depth of the subsum is not equal to zero, we have
   * \f[
   *     \mbox{} - \sum\limits_{i=1}^n 
   *       \left( \begin{array}{c} n \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *       \frac{x^i}{(i+c)^m} S(i,...)
   * \f] \f[
   *     =
   *       \mbox{} - \frac{1}{x} \frac{1}{n+1} Z(n-1)
   *         (-1) \sum\limits_{i=1}^{n+1}
   *       \left( \begin{array}{c} n+1 \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *              \frac{x^i}{(i+c-1)^m} i S(i,...)
   * \f] \f[
   *       + \frac{1}{x} \frac{1}{n+1} Z(n-1)
   *         (-1) \sum\limits_{i=1}^{n+1}
   *       \left( \begin{array}{c} n+1 \\ i \\ \end{array} \right)
   *       \left( -1 \right)^i
   *              \frac{x^i}{(i+c-1)^m} \frac{x_1^i}{i^{m_1-1}}  S(i;m_2,...)
   * \f]
   *
   * This routine is called from eval/adjust_summation_index only for \f$c>0\f$.
   *
   */
  ex transcendental_sum_type_C::shift_minus_one(void) const
  {
    // called from adjust_summation_index
    //
    // have  - sum_{i=1}^n binom(n,i) (-1)^i x^i/(i+c)^m S(i,...) with c>0

    ex x = ex_to<basic_letter>(letter).get_scale();

    ex m = ex_to<basic_letter>(letter).get_degree();

    // check if m is negative or zero
    if ( (m.info(info_flags::negint)) || ( m.is_zero() ) )
      {
	ex res = 0 ;
	ex m_neg = -m;

	int j;
	for ( j=0;j<=m_neg;j++ )
	      {
		// do not change expand status (remains adjust_summation_index)
		res = res + binomial(m_neg,j) * pow( ex_to<basic_letter>(letter).get_offset(), m_neg-j)
		  *create_transcendental_sum_type_C(n,index,
						    create_letter(x,-j,index),
						    lst_of_gammas,
						    subsum,
						    expansion_parameter,
						    order,
						    flag_expand_status);
	      }

	return res ;

      } // end if m<=0

    if ( ex_to<Ssum>(subsum).get_depth() == 0)
      {
	ex term_1 = -pow(ex_to<basic_letter>(letter).get_offset(),-ex_to<basic_letter>(letter).get_degree())
	      * create_Zsum(n-1,_empty_list);

	// do not change expand status (remains adjust_summation_index)
	return -pow(x,-1) * create_unit_letter(1,n+1)
	  * create_Zsum(n-1,_empty_list)
	  * create_transcendental_sum_type_C(n+1,index,
					     ex_to<basic_letter>(letter).shift_minus_one()
					     * create_unit_letter(-1,index),
					     lst_of_gammas,
					     subsum,
					     expansion_parameter,order,
					     flag_expand_status)
	  - term_1 ;

      } // subsum.depth = 0


    // subsum.depth <> 0 now

    const Ssum& Z0 = ex_to<Ssum>(subsum);
    ex Z1 = Z0.remove_first_letter();

    ex l1 = ex_to<basic_letter>(ex_to<basic_letter>(Z0.get_first_letter()).degree_minus_one()).set_index(index);

    // do not change expand status (remains adjust_summation_index)
    return -pow(x,-1) * create_unit_letter(1,n+1)
	  * create_Zsum(n-1,_empty_list)
	  * create_transcendental_sum_type_C(n+1,index,
					     ex_to<basic_letter>(letter).shift_minus_one()
					     * create_unit_letter(-1,index),
					     lst_of_gammas,
					     subsum,
					     expansion_parameter,order,
					     flag_expand_status)
      + pow(x,-1) * create_unit_letter(1,n+1)
	  * create_Zsum(n-1,_empty_list)
	  * create_transcendental_sum_type_C(n+1,index,
					     ex_to<basic_letter>(letter).shift_minus_one() * l1,
					     lst_of_gammas,
					     Z1,
					     expansion_parameter,order,
					     flag_expand_status)
      ;
    
  }

  // utility functions

  /**
   *
   * Stop and go
   *
   */
  ex create_transcendental_sum_type_C_and_expand(const ex & nn, const ex & i, const ex & l, 
						 const ex & v, const ex & ss, 
						 const ex & eps, int o)
    {
      // stop and go
      _nestedsums_evaluation_veto_type_C = expand_status::do_hoelder_convolution;
      ex expr = 
	create_transcendental_sum_type_C_and_set_gammas(nn,i,l,v,ss,eps,o,
							expand_status::expansion_required);
      expr = nestedsums_helper_sort(expr,lst{eps});

      _nestedsums_evaluation_veto_type_C = expand_status::zombie;
      expr = nestedsums_helper_eval(expr);

      return expr;
    }

} // namespace nestedsums

