
/** @file list_polygamma.cc
 *
 * Implementation of list_of_tgamma
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

GINAC_IMPLEMENT_REGISTERED_CLASS(list_of_tgamma, basic)

GINAC_BIND_UNARCHIVER(list_of_tgamma);



  list_of_tgamma::list_of_tgamma() : inherited(), gamma_sequence(_empty_list),
   index(_default_index), expansion_parameter(_default), order(0)
  { 
  }

  void list_of_tgamma::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("gamma_sequence",gamma_sequence);
    node.add_ex("index",index);
    node.add_ex("expansion_parameter",expansion_parameter);

    node.add_ex("order",numeric(order));
  }

  void list_of_tgamma::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("gamma_sequence",gamma_sequence,sym_lst);
    node.find_ex("index",index,sym_lst);
    node.find_ex("expansion_parameter",expansion_parameter,sym_lst);

    ex ex_order;
    node.find_ex("order",ex_order,sym_lst);
    order = ex_to<numeric>(ex_order).to_int();
  }

  int list_of_tgamma::compare_same_type(const basic &other) const
  {
    const list_of_tgamma &o = static_cast<const list_of_tgamma &>(other);

    int cmpval;

    cmpval = index.compare(o.index);

    if( cmpval ) return cmpval;

    cmpval = expansion_parameter.compare(o.expansion_parameter);

    if( cmpval ) return cmpval;

    if ( order != o.order )
      {
	return (order > o.order) ? 1 : -1;
      } 

    return gamma_sequence.compare(o.gamma_sequence);

  }

  // other ctors


  /**
   *
   * Constructor via initialization list. If the list l is non-empty, the members index,
   * expansion_parameter and order are set according to the first entry in the list l. 
   *
   */
  list_of_tgamma::list_of_tgamma(const ex & l) : inherited(), gamma_sequence(l),
   index(_default_index), expansion_parameter(_default), order(0)
  { 
    if ( l.nops() > 0 )
      {
	ex r0 = gamma_sequence.op(0);
	if ( !is_a<ratio_of_tgamma>(r0) ) throw(std::invalid_argument("gamma_sequence must contain ratio_of_tgamma"));
	ratio_of_tgamma rtg = ex_to<ratio_of_tgamma>(r0);

	index = rtg.index;
	expansion_parameter = rtg.expansion_parameter;
	order = rtg.order;
      }
  }


  /**
   *
   * Constructor via initialization list.
   *
   */
  list_of_tgamma::list_of_tgamma(const ex & l, const ex & i, const ex & eps, int o) : inherited(),
   gamma_sequence(l), index(i), expansion_parameter(eps), order(o)
  {  }


  // functions overriding virtual functions from bases classes

  unsigned list_of_tgamma::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= gamma_sequence.gethash();

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

  void list_of_tgamma::print(const print_context & c, unsigned level) const
  {
    unsigned depth = get_depth();

    if (depth == 0) 
      {
	if (is_a<print_latex>(c)) {
	  c.s << "\\mbox{empty_list_of_tgamma}(" ;
	  index.print(c);
	  c.s << ")";
	}
	else if (is_a<print_tree>(c)) 
	  {
	    c.s << std::string(level, ' ') << class_name()
		<< std::hex << ", hash=0x" << hashvalue << ", flags=0x" << flags << std::dec
		<< ", nops=" << nops()
		<< ", order=" << order
		<< ", depth=" << depth
		<< std::endl;
	    gamma_sequence.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	    index.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	    expansion_parameter.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	  } 
	else
	  {
	  c.s << "empty_list_of_tgamma(" ;
	  index.print(c);
	  c.s << ")";
	  }
	return;
      }

    if (is_a<print_latex>(c)) {
      int j;
      for (j=0;j<depth;j++)
	{
	  gamma_sequence.op(j).print(c,mul_precedence);
	}

    } 
    else if (is_a<print_tree>(c)) 
      {
	c.s << std::string(level, ' ') << class_name()
	    << std::hex << ", hash=0x" << hashvalue << ", flags=0x" << flags << std::dec
	    << ", nops=" << nops()
	    << ", order=" << order
	    << ", depth=" << depth
	    << std::endl;
	gamma_sequence.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	index.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	expansion_parameter.print(c, level + static_cast<const print_tree &>(c).delta_indent);
      } 
    else {
      int j;
      if ( depth > 0 )
	{
	  gamma_sequence.op(0).print(c,mul_precedence);
	  for (j=1;j<depth;j++)
	    {
	      c.s << "*";
	      gamma_sequence.op(j).print(c,mul_precedence);
	    }
	}
    }

  }

  /**
   *
   * If the index is an integer, the object is evaluated explicitly.
   *
   */
  ex list_of_tgamma::eval() const
  {

    if ( index.info(info_flags::integer) ) return this->eval_explicit();

    // default
    return this->hold();
  }

  /**
   *
   * If two list_of_tgammas have the same index, they can be merged together.
   *
   * If the difference between the two indices is an integer, we can merge them 
   * according to
   * \f[
   *    \frac{\Gamma(1+d_1\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(1+d_2\varepsilon)}{\Gamma(1+b_2\varepsilon)}
   *    \frac{\Gamma((i+l)+a_1+b_1 \varepsilon)}{\Gamma((i+l)+c_1+d_1 \varepsilon)}
   *    \frac{\Gamma(i+a_2+b_2 \varepsilon)}{\Gamma(i+c_2+d_2 \varepsilon)}
   * \f] \f[
   *   =
   *    \frac{\Gamma(1+d_1\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(1+d_2\varepsilon)}{\Gamma(1+b_2\varepsilon)}
   *    \frac{\Gamma(i+(a_1+l)+b_1 \varepsilon)}{\Gamma(i+(c_1+l)+d_1 \varepsilon)}
   *    \frac{\Gamma(i+a_2+b_2 \varepsilon)}{\Gamma(i+c_2+d_2 \varepsilon)}
   * \f]
   * where \f$ l > 0 \f$. 
   * Note that the algorithm returns a product, where
   * both factors have the "smaller" index.
   *
   */
  ex list_of_tgamma::eval_ncmul(const exvector & v) const
  {
    if ( v.size() <= 1 ) return hold_ncmul(v);

    // at least two list_of_tgammas, take out the last two and multiply them

    ex e1 = v[v.size()-1];
    ex e2 = v[v.size()-2];

    if ( is_a<list_of_tgamma>(e1) && is_a<list_of_tgamma>(e2) )
      {
	exvector s = v;
	s.pop_back();
	s.pop_back();

	const list_of_tgamma& Z1 = ex_to<list_of_tgamma>(e1);
	const list_of_tgamma& Z2 = ex_to<list_of_tgamma>(e2);

	// avoid infinite recursion
	if ( Z1.index.is_equal(Z2.index) )
	  {
	    return ncmul(s)*Z2.concat(e1);
	  }

	// difference is integer
	ex c = Z1.index - Z2.index;
	if ( c.info(info_flags::posint) )
	  {
	    return ncmul(s) * e2 * Z1.shift_index(Z2.index) ;
	  }
	else if ( c.info(info_flags::negint) )
	  {
	    return ncmul(s) * Z2.shift_index(Z1.index) * e1 ;
	  }
      }

    // default
    return hold_ncmul(v);

  }

  ex list_of_tgamma::derivative(const symbol & s) const
  {
    return 0;
  }

  ex list_of_tgamma::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_list_of_tgamma(gamma_sequence.subs(m,options),index.subs(m,options),expansion_parameter.subs(m,options),order);
  }

  // new virtual functions


  /**
   *
   * Explicit evaluation. 
   * The job is delegated to the function nestedsums_helper_expand_lst_tgamma_fct.
   *
   */
  ex list_of_tgamma::eval_explicit() const
  {
    unsigned depth = get_depth();

    if ( index.info(info_flags::integer) )
      {
	if ( depth==0 ) return 1;

	int i;
	lst l1,l2;

	for(i=0;i<depth;i++)
	  {
	    const ratio_of_tgamma& tg = ex_to<ratio_of_tgamma>(gamma_sequence.op(i));
	    l1.append(index+tg.a1+expansion_parameter*tg.b1);
	    l2.append(index+tg.a2+expansion_parameter*tg.b2);
	    l1.append(1+expansion_parameter*tg.b2);
	    l2.append(1+expansion_parameter*tg.b1);
	  }

	return nestedsums_helper_expand_lst_tgamma_fct(l1,l2,expansion_parameter,order);

      } // end if index is integer

    // default
    return this->hold();
  }

  /**
   *
   * Returns the hash key to be used in connection with the class hash_entry.
   *
   */
  unsigned list_of_tgamma::get_key(void) const
  {
    return this->gethash();
  }

  /**
   *
   * Returns an expression which allows a comparison up to equivalence
   * with an entry in a hash map.
   *
   * In this case the comparison is exact and the method returns *this.
   * 
   */
  ex list_of_tgamma::hash_data(void) const
  {
    return *this;
  }

  /**
   *
   * Returns the data which has to be substitued if the comparison with a hash entry
   * is only up to equivalence.
   * 
   * In this case, the comparison is exact, and no data needs to be substituted.
   *
   */
  ex list_of_tgamma::subst_data(void) const
  {
    return 0;
  }

  // non-virual functions

  /**
   *
   * Sets the flag expansion_required for ratio_of_tgamma.
   * The object is then automatically expanded up to the order specified in the
   * member variable order.
   *
   * This function should be called after all possible poles have been taken care of,
   * e.g. all \f$a_1\f$ in the numerator are non-negative.
   *
   * The result is in expanded form.
   *
   */
  ex list_of_tgamma::set_expansion(void) const
  {
    // brute force algorithm would be :
    // - get the total number of poles
    // - increase the order variable for each ratio_of_tgamma by the total number of poles
    // - truncate in the end

    // but : set_expansion should be only called when a1 is non-negative, therefore no poles
    //       and also multiply_via_triangle can be used without modifications

    unsigned depth = get_depth();

    int j;
    ex res = 1;
    ex pre = 1;
    for (j=0;j<depth;j++)
      {
	ex rtg = gamma_sequence.op(j);

	while ( ex_to<ratio_of_tgamma>(rtg).a1.info(info_flags::posint) )
	  {
	    pre = nestedsums_helper_multiply_via_triangle_speedy(pre,
 		   nestedsums_helper_expand(
 		    ex_to<ratio_of_tgamma>(rtg).prefactor_decrease_numerator()),
		   expansion_parameter,order);
	    rtg = ex_to<ratio_of_tgamma>(rtg).decrease_numerator();
	  }

	while ( ex_to<ratio_of_tgamma>(rtg).a1.info(info_flags::negint) )
	  {
	    pre = nestedsums_helper_multiply_via_triangle_speedy(pre,
 		   nestedsums_helper_expand(
 		    ex_to<ratio_of_tgamma>(rtg).prefactor_increase_numerator()),
		   expansion_parameter,order);
	    rtg = ex_to<ratio_of_tgamma>(rtg).increase_numerator();
	  }

	while ( ex_to<ratio_of_tgamma>(rtg).a2.info(info_flags::posint) )
	  {
	    pre = nestedsums_helper_multiply_via_triangle_speedy(pre,
 		   nestedsums_helper_expand(
 		    ex_to<ratio_of_tgamma>(rtg).prefactor_decrease_denominator()),
		   expansion_parameter,order);
	    rtg = ex_to<ratio_of_tgamma>(rtg).decrease_denominator();
	  }

	while ( ex_to<ratio_of_tgamma>(rtg).a2.info(info_flags::negint) )
	  {
	    pre = nestedsums_helper_multiply_via_triangle_speedy(pre,
 		   nestedsums_helper_expand(
 		    ex_to<ratio_of_tgamma>(rtg).prefactor_increase_denominator()),
		   expansion_parameter,order);
	    rtg = ex_to<ratio_of_tgamma>(rtg).increase_denominator();
	  }

	// no a1=0 and a2=0, expansion of rtg already in expanded form
	res = nestedsums_helper_multiply_via_triangle_speedy(res,
 		  ex_to<ratio_of_tgamma>(rtg).set_expansion(),
	          expansion_parameter,order);
      }

    return nestedsums_helper_multiply_via_triangle_speedy(pre,res,
						   expansion_parameter,order);

  }

  /**
   *
   * Sets the member variable index to new_index.
   *
   */
  ex list_of_tgamma::set_index(const ex & new_index) const
  {
    unsigned depth = get_depth();

    int j;
    lst *newlist = new lst();
    newlist->setflag(status_flags::dynallocated);
    for (j=0;j<depth;j++)
      {
	newlist->append(ex_to<ratio_of_tgamma>(gamma_sequence.op(j)).set_index(new_index));
      }

    return create_list_of_tgamma(*newlist,new_index,expansion_parameter,order);
  }

  /**
   *
   * Sets the member variable expansion_parameter to new_eps.
   *
   */
  ex list_of_tgamma::set_expansion_parameter(const ex & new_eps) const
  {
    unsigned depth = get_depth();

    int j;
    lst *newlist = new lst();
    newlist->setflag(status_flags::dynallocated);
    for (j=0;j<depth;j++)
      {
	newlist->append(ex_to<ratio_of_tgamma>(gamma_sequence.op(j)).set_expansion_parameter(new_eps));
      }

    return create_list_of_tgamma(*newlist,index,new_eps,order);
  }

  /**
   *
   * Sets the member variable order to new_order.
   *
   */
  ex list_of_tgamma::set_order(int new_order) const
  {
    unsigned depth = get_depth();

    int j;
    lst *newlist = new lst();
    newlist->setflag(status_flags::dynallocated);
    for (j=0;j<depth;j++)
      {
	newlist->append(ex_to<ratio_of_tgamma>(gamma_sequence.op(j)).set_order(new_order));
      }

    return create_list_of_tgamma(*newlist,index,expansion_parameter,new_order);
  }

  /**
   *
   * Returns
   * \f[
   *    \frac{\Gamma(1+d_1\varepsilon)}{\Gamma(1+b_1\varepsilon)} ...
   *    \frac{\Gamma(1+d_k\varepsilon)}{\Gamma(1+b_k\varepsilon)}
   *    \frac{\Gamma(i+a_1+1+b_1 \varepsilon)}{\Gamma(i+c_1+1+d_1 \varepsilon)} ...
   *    \frac{\Gamma(i+a_k+1+b_k \varepsilon)}{\Gamma(i+c_k+1+d_k \varepsilon)}
   * \f]
   * The order parameter is not changed.
   *
   */
  ex list_of_tgamma::shift_plus_one(void) const
  {
    unsigned depth = get_depth();

    int j;
    lst *newlist = new lst();
    newlist->setflag(status_flags::dynallocated);
    for (j=0;j<depth;j++)
      {
	newlist->append(ex_to<ratio_of_tgamma>(gamma_sequence.op(j)).shift_plus_one());
      }

    return create_list_of_tgamma(*newlist,index,expansion_parameter,order);
  }

  /**
   *
   * Returns
   * \f[
   *    \frac{\Gamma(1+d_1\varepsilon)}{\Gamma(1+b_1\varepsilon)} ...
   *    \frac{\Gamma(1+d_k\varepsilon)}{\Gamma(1+b_k\varepsilon)}
   *    \frac{\Gamma(i+a_1-1+b_1 \varepsilon)}{\Gamma(i+c_1-1+d_1 \varepsilon)} ...
   *    \frac{\Gamma(i+a_k-1+b_k \varepsilon)}{\Gamma(i+c_k-1+d_k \varepsilon)}
   * \f]
   * The order parameter is not changed.
   *
   */
  ex list_of_tgamma::shift_minus_one(void) const
  {
    unsigned depth = get_depth();

    int j;
    lst *newlist = new lst();
    newlist->setflag(status_flags::dynallocated);
    for (j=0;j<depth;j++)
      {
	newlist->append(ex_to<ratio_of_tgamma>(gamma_sequence.op(j)).shift_minus_one());
      }

    return create_list_of_tgamma(*newlist,index,expansion_parameter,order);
  }

  /**
   *
   * Returns
   * \f[
   *    \frac{\Gamma(1+d_1\varepsilon)}{\Gamma(1+b_1\varepsilon)} ...
   *    \frac{\Gamma(1+d_k\varepsilon)}{\Gamma(1+b_k\varepsilon)}
   *    \frac{\Gamma(a_1+1+b_1 \varepsilon)}{\Gamma(c_1+1+d_1 \varepsilon)} ...
   *    \frac{\Gamma(a_k+1+b_k \varepsilon)}{\Gamma(c_k+1+d_k \varepsilon)}
   * \f]
   *
   */
  ex list_of_tgamma::index_eq_one(void) const
  {
    return this->set_index(1);
  }

  /**
   *
   * Returns a list_of_tgamma with
   * \f[
   *    \Gamma(i + a + o + b \varepsilon )
   * \f]
   * with \f$ o = j-i\f$, where \f$i\f$ is the new index and \f$j\f$ is the old index.
   *
   */
  ex list_of_tgamma::shift_index(const ex & new_index) const
  {
    unsigned depth = get_depth();

    ex offset = index - new_index;

    int j;
    lst *newlist = new lst();
    newlist->setflag(status_flags::dynallocated);
    for (j=0;j<depth;j++)
      {
	newlist->append(ex_to<ratio_of_tgamma>(gamma_sequence.op(j)).shift_index(new_index));
      }

    return create_list_of_tgamma(*newlist,new_index,expansion_parameter,order);
  }

  /**
   *
   * Concats two list_of_tgammas.
   *
   */
  ex list_of_tgamma::concat(const ex & l) const
  {
    unsigned depth = get_depth();

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=0;i<depth;i++)
      {
	l_new->append(gamma_sequence.op(i));
      }
    list_of_tgamma ll = ex_to<list_of_tgamma>(l);
    for (i=0;i<ll.get_depth();i++)
      {
	// 24.08.2003 bug fix: have to set the order variable 
	//                     in ratio_of_tgamma
	l_new->append(ex_to<ratio_of_tgamma>(ll.gamma_sequence.op(i)).set_values(
           index,expansion_parameter,order,expand_status::no_eval_to_scalar));
      }

    return create_list_of_tgamma(*l_new,index,expansion_parameter,order);
  }


  /**
   *
   * Returns \f$> 0\f$  if \f$a_j \le 0 \f$, and 0 otherwise.
   *
   */
  int list_of_tgamma::pole_alert(void) const
  {
    unsigned depth = get_depth();

    int j;

    int flag = 0;

    for (j=0;j<depth;j++)
      {
	if ( ex_to<ratio_of_tgamma>(gamma_sequence.op(j)).pole_alert() ) flag++;
      }

    return flag;
  }

  /**
   *
   * Returns \f$> 0\f$ if \f$a_j\f$ or \f$c_j\f$ are not integers, and 0 otherwise.
   *
   */
  int list_of_tgamma::expansion_alert(void) const
  {
    unsigned depth = get_depth();

    int j;

    int flag = 0;

    for (j=0;j<depth;j++)
      {
	if ( ex_to<ratio_of_tgamma>(gamma_sequence.op(j)).expansion_alert() ) flag++;
      }

    return flag;

  }

} // namespace nestedsums

