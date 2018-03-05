/** @file transcendental_A.cc
 *
 * Implementation of transcendental_sum_type_A
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

GINAC_IMPLEMENT_REGISTERED_CLASS(transcendental_sum_type_A, basic)

GINAC_BIND_UNARCHIVER(transcendental_sum_type_A);



  transcendental_sum_type_A::transcendental_sum_type_A() : inherited(),
   n(_default), index(_default_index), letter(_default), lst_of_gammas(_empty_list_of_tgamma), subsum(_default),
   expansion_parameter(_default), order(0), flag_expand_status(expand_status::start)
  { 
  }

  void transcendental_sum_type_A::archive(archive_node &node) const
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

  void transcendental_sum_type_A::read_archive(const archive_node &node, lst &sym_lst)
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

  int transcendental_sum_type_A::compare_same_type(const basic &other) const
  {
    const transcendental_sum_type_A &o = static_cast<const transcendental_sum_type_A &>(other);

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
  transcendental_sum_type_A::transcendental_sum_type_A(const ex & nn, const ex & i, const ex & l, const ex & v,
						     const ex & ss, const ex & eps, int o, int f) : 
    inherited(), n(nn), index(i), letter(l), lst_of_gammas(v), subsum(ss),
    expansion_parameter(eps), order(o), flag_expand_status(f)
  { }


  // functions overriding virtual functions from bases classes

  unsigned transcendental_sum_type_A::calchash(void) const
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

  void transcendental_sum_type_A::print(const print_context & c, unsigned level) const
  {
    if (is_a<print_latex>(c)) {
      if (precedence() <= level) c.s << "{(";
      c.s << "\\sum_{" ;
      index.print(c);
      c.s << "= 1}^{";
      n.print(c);
      c.s << "}";
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
      c.s << ",";
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
   * - If subsum is equal to 1, the subsum is replaced with Z(i-1).
   *
   * - If subsum is not of type Zsum, the routine distribute_over_subsum is called.
   * 
   * - If the difference of the upper summation index of the Zsum with the index member is not
   *   an integer, the Zsum is taken out of the sum. The subsum is replaced with Z(i-1).
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
   * - It adjusts the upper summation limit in subsum to index-1. 
   *   If \f$ o > 0 \f$ the function Zsum::adjust_upper_limit_downwards(index-1) is used.
   *   If \f$ o < 0 \f$ the function shift_plus_one() is called.
   *
   * - It checks, that letter does not give rise to poles 
   *   (e.g. that the offset \f$c\f$ is a non-negative integer or a negative integer 
   *    larger or equal to \f$c \ge -l+o \f$).
   *
   * - It checks, that the \f$a_j\f$ in the Gamma functions are integers.
   *
   * If one of the tests fails, the object is put into a zombie state.
   *
   * If flag_expand_status == expand_status::check_for_poles, it assures
   * that the Gamma functions in the numerator do not give rise to poles (by taking out
   * the critical part and shifting the summation index).
   * The function shift_plus_one() is used.
   *
   * If flag_expand_status == expand_status::expand_gamma_functions, the Gamma functions are expanded
   * into Euler Zagier sums.
   * This is done by setting the expansion_required flag in the ratio_of_tgamma class.
   *
   * 
   * If flag_expand_status == expand_status::adjust_summation_index, we deal with sums of the form
   * \f[
   *     \sum\limits_{i=1}^n \frac{x^i}{(i+c)^m} Z(i-1,...)
   * \f]
   * Here eval adjusts the offset.
   * In the case \f$c > 0\f$ the function shift_minus_one() is called.
   * The function shift_minus_one() does not change the upper summation limit of the subsum
   * (this avoids an infinite recursion).
   * In the case \f$c < 0\f$ shift_plus_one() is called.
   *
   * If flag_expand_status == expand_status::evaluated, the sum is in the form
   * \f[
   *     \sum\limits_{i=1}^n \frac{x^i}{i^m} Z(i-1,...)
   * \f]
   * and is converted to a Zsum.
   * 
   *
   */
  ex transcendental_sum_type_A::eval() const
  {
#ifdef _DEBUG
    if ( _debug_level & 1 ) 
      {
	std::cout << " ---------------------------- " << std::endl;
	std::cout << std::endl;
	std::cout << "entering eval type A" << std::endl;
	std::cout << std::endl;
	std::cout << "n         : " << n << std::endl;
	std::cout << "index     : " << index << std::endl;
	std::cout << "letter    : " << letter << std::endl;
	std::cout << "gammas    : " << lst_of_gammas << std::endl;
	std::cout << "subsum    : " << subsum << std::endl;
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
	return subsum * create_transcendental_sum_type_A(n,index,letter,lst_of_gammas,create_Zsum(index-1,lst()),
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
	return create_transcendental_sum_type_A(n,index,ex_to<basic_letter>(letter).shift_index(index),lst_of_gammas,subsum,
		expansion_parameter,order,flag_expand_status);
      }


    // adjust index in list_of_tgamma
    if ( ex_to<list_of_tgamma>(lst_of_gammas).get_depth() > 0 )
      {
	ex diff_indices_gamma = ex_to<list_of_tgamma>(lst_of_gammas).get_index() - index;

	if ( !diff_indices_gamma.is_zero() )
	  {
	    return create_transcendental_sum_type_A(n,index,letter,ex_to<list_of_tgamma>(lst_of_gammas).shift_index(index),subsum,
					       expansion_parameter,order,flag_expand_status);
	  }
      }


    // ---------------
    if ( ( flag_expand_status == expand_status::expansion_required )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_A ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 1 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering expansion_required " << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	int temp_zombie_flag = 0;

	// check for index-1 in subsum 
	ex up_diff = ex_to<Zsum>(subsum).get_index() - index + 1;

	if (up_diff.info(info_flags::posint))
	  {
	    // return adjusted object
	    return create_transcendental_sum_type_A(n,index,letter,lst_of_gammas,
					       ex_to<Zsum>(subsum).adjust_upper_limit_downwards(index-1),
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
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_A ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 1 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering check_for_poles " << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	// subsum contains exactly one Zsum
	int flag = ex_to<list_of_tgamma>(lst_of_gammas).pole_alert();

	if ( flag>0 ) return this->shift_plus_one();

	// no poles, go to next step
	flag_expand_status = expand_status::expand_gamma_functions;

      } // end if check_for_poles


    // ---------------
    if ( ( flag_expand_status == expand_status::expand_gamma_functions )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_A ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 1 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering expand_gamma_functions " << std::endl;
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
	    ex pre;
	    
	    if (_flag_table_list_of_tgamma) // use hash tables 
	      {
		const list_of_tgamma& obj = ex_to<list_of_tgamma>(lst_of_gammas);
		unsigned key = obj.get_key();

		std::map<unsigned, ex>::iterator p = _table_list_of_tgamma.find(key);
		if ( p != _table_list_of_tgamma.end() )
		  {
		    const hash_entry& he = ex_to<hash_entry>( p->second );

		    if ( he.hash_data().is_equal( obj.hash_data() ) )
		      {
			_count_table_list_of_tgamma++;
			pre = ( he.return_value( obj.subst_data() ) );
		      }
		    else
		      {
			pre = obj.set_expansion();
		      }
		  }
		else
		  {
		    pre = obj.set_expansion();
		    _table_list_of_tgamma[key] = create_hash_entry( lst_of_gammas, 0, pre, 0 );
		  }
	      }
	    else // don't use hash tables
	      {
		pre = ex_to<list_of_tgamma>(lst_of_gammas).set_expansion();
	      }

	    pre = pre * subsum;
	    pre = nestedsums_helper_expand(pre);

	    return create_transcendental_sum_type_A_and_set_gammas(n,index,letter,_empty_list_of_tgamma,pre,
					   expansion_parameter,order,expand_status::adjust_summation_index);
	  }

	// nothing to expand
	flag_expand_status = expand_status::adjust_summation_index;

      } // end if expand_gamma_functions


    // ---------------
    if ( ( flag_expand_status == expand_status::adjust_summation_index )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_A ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 1 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering adjust_summation_index " << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	// have sum(i=1..n, x^i / (i+c)^m Z(i-1,...)

	ex res;
	    
	if (_flag_table_transcendental_sum_type_A) // use hash tables 
	  {
	    unsigned key = this->get_key();

	    std::map<unsigned, ex>::iterator p = _table_transcendental_sum_type_A.find(key);
	    if ( p != _table_transcendental_sum_type_A.end() )
	      {
		const hash_entry& he = ex_to<hash_entry>( p->second );

		if ( he.hash_data().is_equal( this->hash_data() ) )
		  {
		    _count_table_transcendental_sum_type_A++;
		    return he.return_value( this->subst_data() );
		  }
		else
		  {
		    flag_expand_status = expand_status::hash_checked;
		  }
	      }
	    else
	      {
		res = create_transcendental_sum_type_A(n,index,letter,lst_of_gammas,subsum,
						       expansion_parameter,order,
						       expand_status::hash_checked);
		_table_transcendental_sum_type_A[key] = create_hash_entry( this->hash_data(), 0, res, 0 );

		return res;
	      }
	  }
	else // don't use hash tables
	  {
	    flag_expand_status = expand_status::hash_checked;
	  }

      } // end if adjust_summation_index

    // ---------------
    if ( ( flag_expand_status == expand_status::hash_checked )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_A ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 1 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering hash_checked " << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	// have sum(i=1..n, x^i / (i+c)^m Z(i-1,...)

	ex c = ex_to<basic_letter>(letter).get_offset();

	if (c.info(info_flags::posint))
	  {

	    return this->shift_minus_one();

	  } // end if c posint
	else if (c.info(info_flags::negint))
	  {

	    return this->shift_plus_one();

	  } // end if c negint

	//  c = 0

	flag_expand_status = expand_status::evaluated;

      } // end if hash_checked


    // ---------------
    if ( ( flag_expand_status == expand_status::evaluated )
	 && ( flag_expand_status < _nestedsums_evaluation_veto_type_A ) )
      {
#ifdef _DEBUG
	if ( _debug_level & 1 ) 
	  {
	    std::cout << std::endl;
	    std::cout << "entering evaluated " << std::endl;
	    std::cout << std::endl;
	    std::cout << "n         : " << n << std::endl;
	    std::cout << "index     : " << index << std::endl;
	    std::cout << "letter    : " << letter << std::endl;
	    std::cout << "gammas    : " << lst_of_gammas << std::endl;
	    std::cout << "subsum    : " << subsum << std::endl;
	  }
#endif // def _DEBUG

	// lst_of_gammas is empty
	// subsum contains exactly one Zsum with upper summation index (index-1)

	return ex_to<Zsum>(subsum).prepend_letter(n,ex_to<basic_letter>(letter).forget_index());

      } // end if evaluated


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
  ex transcendental_sum_type_A::eval_ncmul(const exvector & v) const
  {

    // default
    return hold_ncmul(v);

  }

  ex transcendental_sum_type_A::derivative(const symbol & s) const
  {
    return 0;
  }

  ex transcendental_sum_type_A::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_transcendental_sum_type_A(n.subs(m,options),index.subs(m,options),letter.subs(m,options),lst_of_gammas.subs(m,options),
					   subsum.subs(m,options),expansion_parameter.subs(m,options),order,flag_expand_status);
  }

  // new virtual functions

  /**
   *
   * The hash key is calculated from the hash_data.
   *
   */
  unsigned transcendental_sum_type_A::get_key(void) const
  {
    return this->hash_data().gethash();
  }

  /**
   *
   * The summation index is a redundant variable and
   * does not influence the hash_data.
   *
   */
  ex transcendental_sum_type_A::hash_data(void) const
  {
    return lst{n,
	       ex_to<basic_letter>(letter).forget_index(),
	       ex_to<Zsum>(subsum).get_letter_list()
	       };
  }

  /**
   *
   * No substitutions necessary.
   *
   */
  ex transcendental_sum_type_A::subst_data(void) const
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
  ex transcendental_sum_type_A::set_expansion(void) const
  {
    transcendental_sum_type_A* res = new transcendental_sum_type_A(n,index,letter,lst_of_gammas,subsum,expansion_parameter,
								 order,expand_status::expansion_required);
    res->setflag(status_flags::dynallocated);
    return *res;
  }

  /**
   *
   * subsum is allowed to contain a sum of products (e.g. an expression in expanded form).
   * Each term can contain scalars, basic_letters, list_of_tgammas, Zsums or Ssums.
   *
   * This routine converts the transcendental_sum_type_A to a canonical form,
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
  ex transcendental_sum_type_A::distribute_over_subsum(void) const
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
	    res = res + create_transcendental_sum_type_A(n,index,letter,lst_of_gammas,subsum.op(j),
							expansion_parameter,order,flag_expand_status);
	  }
	return res;
      }

    // multiplication
    if ( is_a<mul>(subsum) || is_a<ncmul>(subsum) )
      {
	int j;
	int up_limit = subsum.nops();
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
	ex res = pre*create_transcendental_sum_type_A(n,index,newletter,new_lst_of_gammas,hard,
						     expansion_parameter,order,flag_expand_status);
	return res;
      }
    // end distribution over subsum

    // basic letter
    if ( is_a<basic_letter>(subsum))
      {
	const basic_letter& obj_letter = ex_to<basic_letter>(subsum);

	ex offset = obj_letter.get_index() - index;

	if ( offset.info(info_flags::integer) )
	  {
	    ex newletter = letter * subsum;
	    newletter = newletter.expand();
	    return create_transcendental_sum_type_A(n,index,newletter,
		     lst_of_gammas,create_Zsum(index-1,lst()),
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum * create_transcendental_sum_type_A(n,index,letter,
			     lst_of_gammas,create_Zsum(index-1,lst()),
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
	    return create_transcendental_sum_type_A(n,index,letter,
		     lst_of_gammas*subsum,create_Zsum(index-1,lst()),
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum * create_transcendental_sum_type_A(n,index,letter,
			     lst_of_gammas,create_Zsum(index-1,lst()),
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
	    return create_transcendental_sum_type_A(n,index,letter,
		     lst_of_gammas,nestedsums_helper_expand(Ssum_to_Zsum(subsum)),
		     expansion_parameter,order,flag_expand_status);
	  }
	else
	  {
	    return subsum * create_transcendental_sum_type_A(n,index,letter,
			     lst_of_gammas,create_Zsum(index-1,lst()),
			     expansion_parameter,order,flag_expand_status);
	  }
      } // end Ssum

    // default: anything else, take it out of the sum
    if ( !is_a<Zsum>(subsum) )
      {
	return subsum * create_transcendental_sum_type_A(n,index,letter,lst_of_gammas,create_Zsum(index-1,lst()),
							 expansion_parameter,order,flag_expand_status);
      }

    return this->hold();
  }


  /**
   *
   * letter is allowed to contain a sum of products (e.g. an expression in expanded form).
   * Each term can contain scalars and basic_letters.
   *
   * This routine converts the transcendental_sum_type_A to a canonical form,
   * so that afterwards letter only contains a basic_letter.
   *
   */
  ex transcendental_sum_type_A::distribute_over_letter(void) const
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
	    res = res + create_transcendental_sum_type_A(n,index,letter.op(j),lst_of_gammas,subsum,
							expansion_parameter,order,flag_expand_status);
	  }
	return res;
      }

    // multiplication
    if ( is_a<mul>(letter) || is_a<ncmul>(letter) )
      {
	int j;
	int up_limit = letter.nops();
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
	ex res = pre*create_transcendental_sum_type_A(n,index,hard,lst_of_gammas,subsum,
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
  ex transcendental_sum_type_A::eval_explicit() const
  {
    // n is a integer : evaluate the sum
    if ( n.info(info_flags::integer) )
      {
	int i;
	ex res = 0 ;
	ex temp;
	const Zsum& Z = ex_to<Zsum>(subsum);

	for (i=1;i<=n;i++)
	  {
	    temp = Z.set_index( Z.get_index() - index + i );
	      if ( temp != 0 ) 
		{
		  res = res 
		  + ex_to<basic_letter>(letter).set_index(i)
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
   * \f[
   *   \sum_{i=1}^n \frac{x^i}{(i+c)^m} \frac{\Gamma(i+a_1+b_1 \varepsilon)}{\Gamma(i+c_1+d_1 \varepsilon)} ...
   *     Z(i+o-1;...)
   * \f] \f[
   *   =
   *   x \sum_{i=1}^n \frac{x^i}{(i+c+1)^m} \frac{\Gamma(i+a_1+1+b_1 \varepsilon)}{\Gamma(i+c_1+1+d_1 \varepsilon)} ...
   *     Z(i+o;...)
   * \f] \f[
   *   + \frac{x}{(c+1)^m} \frac{\Gamma(a_1+1+b_1 \varepsilon)}{\Gamma(c_1+1+d_1 \varepsilon)} ...
   *     Z(o;...) Z(n-1)
   * \f] \f[
   *   \mbox{} - x \frac{x^n}{(n+c+1)^m} \frac{\Gamma(n+a_1+1+b_1 \varepsilon)}{\Gamma(n+c_1+1+d_1 \varepsilon)} ...
   *     Z(n+o;...) Z(n-1)
   * \f]
   * This routine is called from eval/expansion_required, eval/check_for_poles and eval/adjust_summation_index.
   *
   */
  ex transcendental_sum_type_A::shift_plus_one(void) const
  {
    ex x = ex_to<basic_letter>(letter).get_scale();

    ex term_1 = 0;
    ex term_n = 0;

    ex temp = create_Zsum( ex_to<Zsum>(subsum).get_index() - index + 1,
			   ex_to<Zsum>(subsum).get_letter_list());

    if ( temp != 0 ) 
      {
	if ( !n.is_equal(Infinity))
	  {
	    term_1 = x * pow(1+ex_to<basic_letter>(letter).get_offset(),-ex_to<basic_letter>(letter).get_degree())
	      * ex_to<list_of_tgamma>(lst_of_gammas).index_eq_one()
	      * temp
	      * create_Zsum(n-1,_empty_list);
	  }
	else 
	  {
	    // n==Infinity : no Z(n-1) but Z(Infinity)
	    term_1 = x * pow(1+ex_to<basic_letter>(letter).get_offset(),-ex_to<basic_letter>(letter).get_degree())
	      * ex_to<list_of_tgamma>(lst_of_gammas).index_eq_one()
	      * temp
	      * create_Zsum(Infinity,_empty_list);
	  }
      }

    if ( !n.is_equal(Infinity))
      {
	term_n = x * ex_to<basic_letter>(ex_to<basic_letter>(letter).shift_plus_one()).set_index(n)
	  *ex_to<list_of_tgamma>(lst_of_gammas).set_index(n+1)
	  *create_Zsum( ex_to<Zsum>(subsum).get_index() - index + n + 1,
			ex_to<Zsum>(subsum).get_letter_list())
	  *create_Zsum(n-1,_empty_list);
      }

    // we set the flag back to expansion_required, since we shifted the subsum
    return x*create_transcendental_sum_type_A(n,
					      index,
					      ex_to<basic_letter>(letter).shift_plus_one(),
					      ex_to<list_of_tgamma>(lst_of_gammas).shift_plus_one(),
					      ex_to<Zsum>(subsum).shift_plus_one(),
					      expansion_parameter,
					      order,
					      expand_status::expansion_required)
      + term_1 - term_n ;
  }


  /**
   *
   * This routine assumes sums of the form
   * \f[
   *     \sum\limits_{i=1}^n \frac{x^i}{(i+c)^m} Z(i-1,...)
   * \f]
   * and performs the substitution index -> index + 1.
   *
   * If \f$m \le 0 \f$ we use the binomial formula
   * \f[
   *     \sum\limits_{i=1}^n \frac{x^i}{(i+c)^m} Z(i-1,...)
   *    =
   *     \sum\limits_{j=0}^{-m}
   *       \left( \begin{array}{c} -m \\ j \\ \end{array} \right)
   *       c^{-m-j}
   *     \sum\limits_{i=1}^n \frac{x^i}{i^{-j}} Z(i-1,...)
   * \f]
   *
   * If the depth of the subsum is zero, we have
   * \f[
   *    \sum\limits_{i=1}^n \frac{x^i}{(i+c)^m}
   *     =
   *       \frac{1}{x} \sum\limits_{i=1}^n \frac{x^i}{(i+c-1)^m}
   *       \mbox{} - \frac{1}{c^m} Z(n-1) + \frac{x^n}{(n+c)^m} Z(n-1)
   * \f]
   * The last term contributes only if \f$n\f$ is not equal to infinity.
   *
   * If the depth of the subsum is not equal to zero and \f$n \neq \infty \f$, we have
   * \f[
   *     \sum\limits_{i=1}^n \frac{x^i}{(i+c)^m} Z(i-1,...)
   *      =
   *       \frac{1}{x} \sum\limits_{i=1}^n \frac{x^i}{(i+c-1)^m} Z(i-1,...)
   *       \mbox{} - \sum\limits_{i=1}^{n-1} \frac{x^i}{(i+c)^m} \frac{x_1^i}{i^{m_1}} Z(i-1,m_2,...)
   *       \mbox{} + \frac{x^n}{(n+c)^m} Z(n-1,...) 
   * \f]
   * If \f$n = \infty \f$ we have instead
   * \f[
   *     \sum\limits_{i=1}^n \frac{x^i}{(i+c)^m} Z(i-1,...)
   *      =
   *       \frac{1}{x} \sum\limits_{i=1}^n \frac{x^i}{(i+c-1)^m} Z(i-1,...)
   *       \mbox{} - \sum\limits_{i=1}^{n} \frac{x^i}{(i+c)^m} \frac{x_1^i}{i^{m_1}} Z(i-1,m_2,...)
   * \f]
   *
   * This routine is called from eval/adjust_summation_index only for \f$c>0\f$.
   *
   */
  ex transcendental_sum_type_A::shift_minus_one(void) const
  {
    // called from adjust_summation_index
    //
    // have sum_{i=1}^n x^i/(i+c)^m Z(i-1,...) with c>0

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
		  *create_transcendental_sum_type_A(n,index,
						    create_letter(x,-j,index),
						    lst_of_gammas,
						    subsum,
						    expansion_parameter,
						    order,
						    flag_expand_status);
	      }

	return res ;

      } // end if m<=0

    if ( ex_to<Zsum>(subsum).get_depth() == 0)
      {
	ex term_1,term_n;

	if ( n.is_equal(Infinity))
	  {
	    term_1 = pow(ex_to<basic_letter>(letter).get_offset(),-ex_to<basic_letter>(letter).get_degree())
	      * create_Zsum(Infinity,_empty_list);
	    term_n = 0;
	  }
	else
	  {
	    term_1 = pow(ex_to<basic_letter>(letter).get_offset(),-ex_to<basic_letter>(letter).get_degree())
	      * create_Zsum(n-1,_empty_list);
	    term_n = ex_to<basic_letter>(letter).set_index(n)
	      *create_Zsum(n-1,_empty_list);
	  }

	// do not change expand status (remains adjust_summation_index)
	return pow(x,-1)*create_transcendental_sum_type_A(n,
							  index,
							  ex_to<basic_letter>(letter).shift_minus_one(),
							  lst_of_gammas,
							  subsum,
							  expansion_parameter,
							  order,
							  flag_expand_status)
	  - term_1 + term_n ;

      } // subsum.depth = 0


    // subsum.depth <> 0 now

    const Zsum& Z0 = ex_to<Zsum>(subsum);
    ex Z1 = Z0.remove_first_letter();

    ex l1 = ex_to<basic_letter>(Z0.get_first_letter()).set_index(index);

    ex term_n;
    ex sum_2;

    if ( n.is_equal(Infinity))
      {
	term_n = 0;
	sum_2 = create_transcendental_sum_type_A(n,
				       index,
				       letter * l1,
				       lst_of_gammas,
				       Z1,
				       expansion_parameter,
				       order,
				       flag_expand_status);
      }
    else
      {
	term_n = ex_to<basic_letter>(letter).set_index(n)
	  *ex_to<Zsum>(subsum).set_index(n-1);
	sum_2 = create_transcendental_sum_type_A(n-1,
				       index,
				       letter * l1,
				       lst_of_gammas,
				       Z1,
				       expansion_parameter,
				       order,
				       flag_expand_status);
      }
    
    // do not change expand status (remains adjust_summation_index)
    return pow(x,-1)*create_transcendental_sum_type_A(n,
						      index,
						      ex_to<basic_letter>(letter).shift_minus_one(),
						      lst_of_gammas,
						      subsum,
						      expansion_parameter,
						      order,
						      flag_expand_status)
      - sum_2 + term_n ;
  }

  // utility functions

  /**
   *
   * Stop and go
   *
   */
  ex create_transcendental_sum_type_A_and_expand(const ex & nn, const ex & i, 
						 const ex & l, const ex & v, const ex & ss, 
						 const ex & eps, int o)
    {
      // stop and go
      _nestedsums_evaluation_veto_type_A = expand_status::expand_gamma_functions;
      ex expr = 
	create_transcendental_sum_type_A_and_set_gammas(nn,i,l,v,ss,eps,o,
							expand_status::expansion_required);
      expr = nestedsums_helper_sort(expr,lst{eps});

      _nestedsums_evaluation_veto_type_A = expand_status::adjust_summation_index;
      expr = nestedsums_helper_eval(expr);
      expr = nestedsums_helper_sort(expr,lst{eps});

      _nestedsums_evaluation_veto_type_A = expand_status::zombie;
      expr = nestedsums_helper_eval(expr);

      return expr;
    }

} // namespace nestedsums

