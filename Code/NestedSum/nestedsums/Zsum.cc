
/** @file Zsum.cc
 *
 * Implementation of Zsums 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(Zsum, basic)

GINAC_BIND_UNARCHIVER(Zsum);



  Zsum::Zsum() : inherited(),
   n(_default), letter_list(_empty_list)
  { 
  }

  void Zsum::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("n",n);
    node.add_ex("letter_list",letter_list);
  }

  void Zsum::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("n",n,sym_lst);
    node.find_ex("letter_list",letter_list,sym_lst);
  }

  int Zsum::compare_same_type(const basic &other) const
  {
    const Zsum &o = static_cast<const Zsum &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  Zsum::Zsum(const ex & nc) : inherited(), n(nc), letter_list(_empty_list)
  { }

  Zsum::Zsum(const ex & nc, const ex & llc) : inherited(), n(nc), letter_list(llc)
  { }


  // functions overriding virtual functions from bases classes

  unsigned Zsum::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= n.gethash();

      v = rotate_left_31(v);
      v ^= letter_list.gethash();

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

  void Zsum::print(const print_context & c, unsigned level) const
  {
    unsigned depth = get_depth();

    int i;

    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "Z(" ;
	n.print(c);
	for(i=0;i<depth;i++)
	  {
	    c.s << "," ;
	    ex_to<letter>(letter_list.op(i)).get_degree().print(c); 
	  }
	for(i=0;i<depth;i++)
	  {
	    c.s << "," ;
	    ex_to<letter>(letter_list.op(i)).get_scale().print(c); 
	  }
	c.s << ")";
	if (precedence() <= level) c.s << ")}";
      }
    else if (is_a<print_tree>(c)) 
      {
	c.s << std::string(level, ' ') << class_name()
	    << std::hex << ", hash=0x" << hashvalue << ", flags=0x" << flags << std::dec
	    << ", nops=" << nops()
	    << ", depth=" << depth
	    << std::endl;
	n.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	letter_list.print(c, level + static_cast<const print_tree &>(c).delta_indent);
      }
    else
      {
	if (precedence() <= level) c.s << "(";
	c.s << "Z(" ;
	n.print(c);
	for(i=0;i<depth;i++)
	  {
	    c.s << "," ;
	    ex_to<letter>(letter_list.op(i)).get_degree().print(c); 
	  }
	for(i=0;i<depth;i++)
	  {
	    c.s << "," ;
	    ex_to<letter>(letter_list.op(i)).get_scale().print(c); 
	  }
	c.s << ")";
	if (precedence() <= level) c.s << ")";
      }
  }

  /**
   *
   * The simplifications are done in the following order:
   *
   * - If the upper summation limit is equal to infinity, we have a multiple polylog.
   *
   * - If all \f$x_j\f$'s are equal to 1, we have a Euler-Zagier sum.
   *
   * - If the upper summation index is an integer, perform the sum explicitly.
   * 
   */
  ex Zsum::eval() const
  {
    // check if Zsum simplifies to multiple polylog
    if ( n.is_equal(Infinity) ) return create_multiple_polylog(letter_list);

    // check if Zsum simplifies to Euler-Zagier sum
    unsigned depth = get_depth();

    if ( depth==0 ) return create_Euler_Zagier_sum(n,letter_list);
    int i=0;
    while ( is_a<unit_letter>(letter_list.op(i++)) )
      {
	if ( i==depth) return create_Euler_Zagier_sum(n,letter_list);
      }

    // n integer
    if ( n.info(info_flags::integer) ) return this->eval_explicit();

    return this->hold();
  }

  /**
   *
   * A product of Zsums is simplified, if the last two have the same
   * upper summation index. The function shuffle_Zsum is called for the multiplication.
   *
   * A product is also simplified if the difference between the two upper summation indices is an integer.
   * The factor with the "larger" upper summation index is converted to the "smaller" index with the help
   * of the function Zsum::adjust_upper_limit_downwards.
   * Note that the algorithm returns a product, where
   * both factors have the "smaller" index.
   *
   */
  ex Zsum::eval_ncmul(const exvector & v) const
  {
    if ( v.size() <= 1 ) return hold_ncmul(v);

    // at least two Zsums, take out the last two and multiply them

    ex e1 = v[v.size()-1];
    ex e2 = v[v.size()-2];

    if ( is_a<Zsum>(e1) && is_a<Zsum>(e2) )
      {
	exvector s = v;
	s.pop_back();
	s.pop_back();

	const Zsum& Z1 = ex_to<Zsum>(e1);
	const Zsum& Z2 = ex_to<Zsum>(e2);

	// avoid infinite recursion
	if ( Z1.n.is_equal(Z2.n) )
	  {
	    // we want the friend function shuffle here
	    return ncmul(s)*shuffle_Zsum(e2,e1);
	  }

	// difference is integer
	ex c = Z1.n - Z2.n;
	if ( c.info(info_flags::posint) )
	  {
	    return nestedsums_helper_expand( ncmul(s) * e2 * Z1.adjust_upper_limit_downwards(Z2.n) );
	  }
	else if ( c.info(info_flags::negint) )
	  {
	    return nestedsums_helper_expand( ncmul(s) * Z2.adjust_upper_limit_downwards(Z1.n) * e1 );
	  }

	// Z(Infinity) is always 1
	if ( Z1.n.is_equal(Infinity) && (Z1.get_depth()==0) ) 
	  {
	    s.push_back(e2);
	    return ncmul(s);
	  }
	if ( Z2.n.is_equal(Infinity) && (Z2.get_depth()==0) ) 
	  {
	    s.push_back(e1);
	    return ncmul(s);
	  }

      }

    // default
    return hold_ncmul(v);

  }

  ex Zsum::derivative(const symbol & s) const
  {
    return 0;
  }

  ex Zsum::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_Zsum(n.subs(m,options),letter_list.subs(m,options));
  }

  // new virtual functions

  /**
   *
   * Method to convert a Zsum to a Ssum. 
   *
   * An efficient version for the conversion to Ssums, based
   * on exvector (e.g. std::vector<GiNaC::ex> ).
   * Z0 contains the result.
   * Z1 is reversed order, so that we can use pop_back.
   *
   * The basic formula is 
   * \f[
   *    Z(n;m_1,...;x_1,...) = \sum\limits_{i=1}^n \frac{x_1^i}{i^{m_1}} Z(i;m_2,...;x_2,...)
   *     \mbox{} - Z(n;m_1+m_2,...;x_1 x_2, ...)
   * \f]
   *
   */ 
  ex Zsum::convert_to_Ssum_exvector(const exvector & Z0, const exvector & Z1) const
  {

    // recursion start
    if ( Z1.size()==0 )
      {
	return create_Ssum_from_exvector(n,Z0);
      }

    if ( Z1.size()==1 )
      {
	exvector ZZ0 = Z0;
	// use the reverse iterator
	ZZ0.insert(ZZ0.end(),Z1.rbegin(),Z1.rend());
	return create_Ssum_from_exvector(n,ZZ0);
      }

    // Z1 has now at least two elements
    ex x1 = Z1[Z1.size()-1];
    ex x2 = Z1[Z1.size()-2];

    exvector ZZ01 = Z0;
    ZZ01.push_back(x1);

    exvector ZZ2 = Z1;
    ZZ2.pop_back();

    exvector ZZ3 = ZZ2;
    ZZ3.pop_back();

    ZZ3.push_back(ex_to<letter>(x1).concat_speedy(x2));

    return convert_to_Ssum_exvector(ZZ01,ZZ2)
          -convert_to_Ssum_exvector(Z0,ZZ3);

  }

  /**
   *
   * Method to multiply two Zsums.
   *
   * An efficient version for the multiplication of Zsums, based
   * on exvector (e.g. std::vector<GiNaC::ex> ).
   * Z0 contains the result.
   * Z1 and Z2 are in reversed order, so that we can use pop_back.
   *
   * The basic formula is 
   * \f[
   *    Z(n;m_1,...;x_1,...) Z(n;m_1',...;x_1',...) 
   *      = \sum\limits_{i=1}^n \frac{x_1^i}{i^{m_1}} Z(i-1;m_2,...;x_2,...) Z(i-1;m_1',...;x_1',...)
   * \f] \f[
   *      \mbox{} + \sum\limits_{i=1}^n \frac{{x_1'}^i}{i^{m_1'}} Z(i-1;m_1,...;x_1,...) Z(i-1;m_2',...;x_2',...)
   *      \mbox{} + \sum\limits_{i=1}^n \frac{(x_1 {x_1'})^i}{i^{m_1+m_1'}} Z(i-1;m_2,...;x_2,...) Z(i-1;m_2',...;x_2',...)
   * \f]
   *
   */ 
  ex Zsum::shuffle_exvector(const exvector & Z0, const exvector & Z1, const exvector & Z2) const
    {
      if ( Z1.size()==0 && Z2.size()==0) 
	{
	  return create_Zsum_from_exvector(n,Z0);
	}

      if ( Z2.size()==0) 
	{
	  exvector ZZ0 = Z0;
	  // use the reverse iterator
	  ZZ0.insert(ZZ0.end(),Z1.rbegin(),Z1.rend());
	  return create_Zsum_from_exvector(n,ZZ0);
	}

      if ( Z1.size()==0) 
	{
	  exvector ZZ0 = Z0;
	  // use the reverse iterator
	  ZZ0.insert(ZZ0.end(),Z2.rbegin(),Z2.rend());
	  return create_Zsum_from_exvector(n,ZZ0);
	}

      ex x1 = Z1[Z1.size()-1];
      ex x2 = Z2[Z2.size()-1];

      exvector ZZ01 = Z0;
      exvector ZZ02 = Z0;
      exvector ZZ012 = Z0;

      exvector Z1_removed = Z1;
      exvector Z2_removed = Z2;

      ZZ01.push_back(x1);
      ZZ02.push_back(x2);
      ZZ012.push_back(ex_to<letter>(x1).concat_speedy(x2));

      Z1_removed.pop_back();
      Z2_removed.pop_back();

      return shuffle_exvector(ZZ01,Z1_removed,Z2)
            +shuffle_exvector(ZZ02,Z1,Z2_removed)
            +shuffle_exvector(ZZ012,Z1_removed,Z2_removed);
    }

  /**
   *
   * Returns the first letter from the letter_list.
   *
   */
  ex Zsum::get_first_letter(void) const
  {
    if (get_depth()==0)
      throw(std::logic_error("empty sum"));

    return letter_list.op(0);
  }

  /**
   *
   * Returns a Zsum with the first letter removed from the letter_list.
   *
   */
  ex Zsum::remove_first_letter(void) const
  {
    unsigned depth = get_depth();

    if (depth==0)
      throw(std::logic_error("empty sum"));

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=1;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }

    return create_Zsum(n,*l_new);
  }

  /**
   *
   * Returns a Zsum with the first letter removed from the letter_list
   * and the upper summation index set to nc.
   *
   */
  ex Zsum::remove_first_letter(const ex & nc) const
  {
    unsigned depth = get_depth();

    if (depth==0)
      throw(std::logic_error("empty sum"));

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=1;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }

    return create_Zsum(nc,*l_new);
  }

  /**
   *
   * Prepends the letter lc to the letter_list.
   *
   */ 
  ex Zsum::prepend_letter(const ex & lc) const
  {
    unsigned depth = get_depth();

    if (!is_a<letter>(lc))
      throw(std::invalid_argument("argument must be a letter"));

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    l_new->append(lc);
    for (i=0;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }

    return create_Zsum(n,*l_new);
  }

  /**
   *
   * Prepends the letter lc to the letter_list and sets
   * the upper summation index to nc.
   *
   */ 
  ex Zsum::prepend_letter(const ex & nc, const ex & lc) const
  {
    unsigned depth = get_depth();

    if (!is_a<letter>(lc))
      throw(std::invalid_argument("argument must be a letter"));

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    l_new->append(lc);
    for (i=0;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }

    return create_Zsum(nc,*l_new);
  }

  /**
   *
   * Appends the letter lc to the letter_list.
   *
   */ 
  ex Zsum::append_letter(const ex & lc) const
  {
    unsigned depth = get_depth();

    if (!is_a<letter>(lc))
      throw(std::invalid_argument("argument must be a letter"));

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=0;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }
    l_new->append(lc);

    return create_Zsum(n,*l_new);
  }

  /**
   *
   * Appends the list lc to the letter_list.
   *
   */ 
  ex Zsum::append_letter_list(const ex & lc) const
  {
    unsigned depth = get_depth();

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=0;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }
    for (i=0;i<lc.nops();i++)
      {
	l_new->append(lc.op(i));
      }

    return create_Zsum(n,*l_new);
  }

  /**
   *
   * Creates a Ssum with the same upper summation index and the
   * same letter_list.
   *
   * This is a crude cast, something like reinterpret_cast.
   *
   */
  ex Zsum::cast_to_Ssum(void) const
  {
    return create_Ssum(n,letter_list);
  }

  /**
   *
   * Sets the upper summation index to \f$i\f$
   *
   */
  ex Zsum::set_index(const ex & i) const
  {
    return create_Zsum(i,letter_list);
  }

  /**
   *
   * Returns \f$Z(n+1,m_1,...,x_1,...)\f$
   *
   */
  ex Zsum::shift_plus_one(void) const
  {
    return create_Zsum(n+1,letter_list);
  }

  /**
   *
   * Returns \f$Z(n-1,m_1,...,x_1,...)\f$
   *
   */
  ex Zsum::shift_minus_one(void) const
  {
    return create_Zsum(n-1,letter_list);
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ down to \f$i\f$, e.g.
   * \f[
   *     Z(n;m_1,...;x_1,...) = Z(i;m_1,...;x_1,...) 
   *      + \sum\limits_{j=1}^{n-i} x_1^j \frac{x_1^i}{(i+j)^{m_1}} Z(i-1+j;m_2,...;x_2,...)
   * \f] 
   * with \f$n > i \f$.
   *
   * For the empty sum we have
   * \f[
   *     Z(n) = Z(i)
   * \f]
   *
   * This routine assumes \f$ i \ge 0 \f$.
   *
   */
  ex Zsum::adjust_upper_limit_downwards(const ex & i) const
  {
    // Z(n,...) = Z(i,...) + sum_(j=1..n-i) x1^j basic_letter(x1,m1,j) Z(i+j-1,...)

    if (get_depth()==0) return create_Zsum(i,lst());

    const basic_letter& l1 = ex_to<basic_letter>(letter_list.op(0));

    ex x1 = l1.get_scale();
    ex m1 = l1.get_degree();

    ex res = create_Zsum(i,letter_list);

    for (int j=1;j<n-i+1;j++)
      {
	res = res + pow(x1,j) * create_basic_letter(x1,m1,j,i) * (this->remove_first_letter(i+j-1));
      }
    return res;
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ up to \f$i\f$, e.g.
   * \f[
   *     Z(n;m_1,...;x_1,...) = Z(i;m_1,...;x_1,...) 
   *      \mbox{} - \sum\limits_{j=0}^{i-n-1} x_1^{-j} \frac{x_1^i}{(i-j)^{m_1}} Z(i-j-1;m_2,...;x_2,...)
   * \f] 
   * with \f$n < i \f$.
   *
   * For the empty sum we have
   * \f[
   *     Z(n) = Z(i)
   * \f]
   *
   * This routine assumes \f$ n \ge 0 \f$.
   *
   *
   * This routine might give rise to poles for some values of \f$i\f$ and should be used with care.
   *
   */
  ex Zsum::adjust_upper_limit_upwards(const ex & i) const
  {
    // this routine might give rise to poles

    if (get_depth()==0) return create_Zsum(i,lst());

    const basic_letter& l1 = ex_to<basic_letter>(letter_list.op(0));

    ex x1 = l1.get_scale();
    ex m1 = l1.get_degree();

    ex res = create_Zsum(i,letter_list);

    for (int j=0;j<i-n;j++)
      {
	res = res - pow(x1,-j) * create_basic_letter(x1,m1,-j,i) * (this->remove_first_letter(i-j-1));
      }
    return res;
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ to \f$n+1\f$, e.g.
   * \f[
   *     Z(n;m_1,...;x_1,...) = Z(n+1;m_1,...;x_1,...) 
   *      \mbox{} - \frac{x_1^{n+1}}{(n+1)^{m_1}} Z(n;m_2,...;x_2,...).
   * \f] 
   *
   */
  ex Zsum::adjust_upper_limit_plus_one(void) const
  {
    if (get_depth()==0) return create_Zsum(n+1,lst());

    const basic_letter& l1 = ex_to<basic_letter>(letter_list.op(0));

    ex x1 = l1.get_scale();
    ex m1 = l1.get_degree();

    return create_Zsum(n+1,letter_list)
      - create_letter(x1,m1,n+1) * (this->remove_first_letter());
  }

  /**
   *
   * Returns
   * \f[
   *     Z(1;m_1,...,m_k;x_1,...,x_k) = 0
   * \f]
   * for \f$k>1\f$. For \f$k=1\f$ it returns
   * \f[
   *    x_1
   * \f]
   * and for \f$k=0\f$ we have
   * \f[
   *    1
   * \f]
   *
   */
  ex Zsum::index_eq_one(void) const
  {
    // this can be done better
    return this->set_index(1);
  }

  /**
   *
   * Returns from the Z-sum \f$ Z(n;m_1,...,m_l;x_1,...,x_l) \f$ the head
   * \f$ Z(n;m_1,...,m_{k-1};x_1,...,x_{k-1}) \f$.
   *
   */
  ex Zsum::get_head(int k) const
  {
    unsigned depth = get_depth();

    if ( k > depth )
      throw(std::invalid_argument("argument cannot be larger then the depth"));

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=0;i<k;i++)
      {
	l_new->append(letter_list.op(i));
      }

    return create_Zsum(n,*l_new);
  }

  /**
   *
   * Returns from the Z-sum \f$ Z(n;m_1,...,m_l;x_1,...,x_l) \f$ the tail
   * \f$ Z(n;m_k,...,m_l;x_k,...,x_l) \f$.
   *
   */
  ex Zsum::get_tail(int k) const
  {
    unsigned depth = get_depth();

    if ( k > depth )
      throw(std::invalid_argument("argument cannot be larger then the depth"));

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=k;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }

    return create_Zsum(n,*l_new);
  }

  /**
   *
   * Calculates the antipode.
   *
   * Only for Zsums.
   *
   */
  ex Zsum::antipode(void) const
  {
    unsigned depth = get_depth();

    if ( depth == 0 ) return *this;

    ex res = 0;
    int i;
    for (i=1;i<depth;i++)
      {
	res = res + nestedsums_helper_expand( ex_to<Zsum>(this->get_head(i)).antipode() * (this->get_tail(i)) );
      }

    return -(*this) - res;
  }

  /**
   *
   * Returns a Zsum, where the letter lc is multiplied with the last letter
   * in the letter list of the original Zsum.
   *
   * If the sum is empty, e.g. \f$Z(n)\f$, the result is \f$\frac{x^n}{n^m} Z(n)\f$.
   *
   */
  ex Zsum::multiply_letter_with_last_letter(const ex & lc) const
  {
    unsigned depth = get_depth();

    if (depth == 0) return ex_to<letter>(lc).set_index(n) * (*this);

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=0;i<depth-1;i++)
      {
	l_new->append(letter_list.op(i));
      }

    l_new->append( letter_list.op(depth-1) * lc );

    return create_Zsum(n,*l_new);
  }

  /**
   *
   * Returns a Zsum, where the letter lc is multiplied with the first letter
   * in the letter list of the original Zsum.
   *
   * If the sum is empty, e.g. \f$Z(n)\f$, the result is \f$\frac{x^n}{n^m} Z(n)\f$.
   *
   */
  ex Zsum::multiply_letter_with_first_letter(const ex & lc) const
  {
    unsigned depth = get_depth();

    if (depth == 0) return ex_to<letter>(lc).set_index(n) * (*this);

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);

    l_new->append( letter_list.op(0) * lc );

    for (i=1;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }

    return create_Zsum(n,*l_new);
  }

  /**
   *
   * Takes Z1 as head and Z2 as tail and forms a new sum as the concatenation of the two.
   *
   */
  ex Zsum::concat_two_sums(const ex & Z1, const ex & Z2) const
  {
    if ( (!is_a<Zsum>(Z1)) || (!is_a<Zsum>(Z2)) ) return Z1*Z2;

    const Zsum& ZZ1 = ex_to<Zsum>(Z1);
    const Zsum& ZZ2 = ex_to<Zsum>(Z2);

    return ZZ1.append_letter_list(ZZ2.letter_list);
  }

  ex Zsum::expand_members(int level) const
  {
    unsigned depth = get_depth();

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=0;i<depth;i++)
      {
	l_new->append(nestedsums_helper_expand(letter_list.op(i),level));
      }

    return create_Zsum(nestedsums_helper_expand(n,level),*l_new);
  }

  /**
   *
   * Explicit evaluation
   *
   */
  ex Zsum::eval_explicit() const
  {
    unsigned depth = get_depth();

    int i;

    // n negative: return 0
    if ( n.info(info_flags::negint) ) return 0;
 
    // n is a non-negative integer : evaluate the sum
    if ( n.info(info_flags::nonnegint) )
      {
	// empty sum and n >=0 : return 1
	if ( depth==0 ) return 1;

	// depth > 0 now
	ex res = 0 ;
	ex letter_l = ex_to<letter>(get_first_letter()).get_scale();
	ex degree = ex_to<letter>(get_first_letter()).get_degree();
	for (i=1;i<=n;i++)
	  {
	    res = res + pow(letter_l,i) * pow(i,-degree) * remove_first_letter(i-1);
	  }
	return res;
      }

    return this->hold();

  }

  /**
   *
   * Returns the weight.
   *
   */
  ex Zsum::get_weight(void) const
  {
    unsigned depth = get_depth();

    ex res = 0;
    for (int k=0;k<depth;k++)
      {
	res = res + ex_to<letter>(letter_list.op(k)).get_degree();
      }
    return res;
  }

  // utility functions

  /**
   *
   * Functional form for the multiplication of two Zsums.
   *
   * The method shuffle_exvector is called for the multiplication.
   * If both sums are Euler-Zagier sums, the reimplementation of shuffle_exvector
   * in the class Euler_Zagier_sum is used directly.
   *
   * If the upper summation limits are not equal, the function returns unevaluated.
   *
   */
  ex shuffle_Zsum(const ex & Z1, const ex & Z2)
  {
    if (!is_a<Zsum>(Z1))
      throw(std::invalid_argument("first argument must be a Zsum"));
    if (!is_a<Zsum>(Z2))
      throw(std::invalid_argument("second argument must be a Zsum"));

    const Zsum& ZZ1 = ex_to<Zsum>(Z1);
    const Zsum& ZZ2 = ex_to<Zsum>(Z2);

    if (ZZ1.n.is_equal(ZZ2.n))
      {

	if ( is_a<Euler_Zagier_sum>(Z1) && is_a<Euler_Zagier_sum>(Z2) )
	  {
	    Euler_Zagier_sum* res = new Euler_Zagier_sum(ZZ1.n);
	    res->setflag(status_flags::dynallocated);
	    exvector vres;
	    return res->shuffle_exvector(vres,reverse_exvector_from_lst(ZZ1.letter_list),
					 reverse_exvector_from_lst(ZZ2.letter_list));
	  }
	else
	  {
	    Zsum* res = new Zsum(ZZ1.n);
	    res->setflag(status_flags::dynallocated);
	    exvector vres;
	    return res->shuffle_exvector(vres,reverse_exvector_from_lst(ZZ1.letter_list),
					 reverse_exvector_from_lst(ZZ2.letter_list));
	  } 
      }

    return Z1*Z2;
  }

  /**
   *
   * Functional form for the conversion to a Ssum.
   *
   */
  ex convert_Zsum_to_Ssum(const ex & Z1)
  {
    // already checked
    const Zsum& ZZ1 = ex_to<Zsum>(Z1);

    // empty sums are theta functions
    if ( (ZZ1.get_depth()==0) && !(ZZ1.n.is_equal(Infinity)) ) return create_Ssum(ZZ1.n+1,_empty_list);

    if ( is_a<Euler_Zagier_sum>(Z1) )
      {
	Euler_Zagier_sum* res = new Euler_Zagier_sum(ZZ1.n);
	res->setflag(status_flags::dynallocated);
	exvector vres;
	return res->convert_to_Ssum_exvector(vres,reverse_exvector_from_lst(ZZ1.letter_list));
      }
    else
      {
	Zsum* res = new Zsum(ZZ1.n);
	res->setflag(status_flags::dynallocated);
	exvector vres;
	return res->convert_to_Ssum_exvector(vres,reverse_exvector_from_lst(ZZ1.letter_list));
      } 

    return Z1;
  }

  /**
   *
   * Construct a Zsum on the heap from an exvector.
   *
   */
  ex create_Zsum_from_exvector(const ex & nc, const exvector & v)
    {
      lst* llc = new lst();
      llc->setflag(status_flags::dynallocated);
      int j;
      for (j=0;j<v.size();j++)
	{
	  llc->append(v[j]);
	}
      return (new Zsum(nc,*llc))->setflag(status_flags::dynallocated);
    }

  /**
   *
   * Convert all Zsums occuring in expr into Ssums.
   *
   */
  ex Zsum_to_Ssum(const ex & expr)
  {

    if ( is_a<Zsum>(expr)) return convert_Zsum_to_Ssum(expr);

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = expr.nops();
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( Zsum_to_Ssum(expr.op(j)));
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

  /**
   *
   * Convert all Z(n,...) appearing in the expression to Z(n+1,...).
   *
   */
  ex shift_upper_limit_plus_one_for_Zsum(const ex & expr)
  {

    if ( is_a<Zsum>(expr)) return ex_to<Zsum>(expr).adjust_upper_limit_plus_one();

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = expr.nops();
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( shift_upper_limit_plus_one_for_Zsum(expr.op(j)));
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

  /**
   *
   * Removes non-positive degrees in Zsums.
   *
   */
  ex remove_negative_degrees_from_Zsum(const ex & expr)
  {
    if ( is_a<Zsum>(expr)) 
      {
	return Ssum_to_Zsum(remove_negative_degrees_from_Ssum(convert_Zsum_to_Ssum(expr)));
      }

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = expr.nops();
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( remove_negative_degrees_from_Zsum(expr.op(j)));
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

  /**
   *
   * Does some trivial simplifications.
   *
   * \f[
   *    Z(\infty)  \rightarrow  1
   * \f]
   *
   * This function has to be used with care, since
   * \f$Z(\infty)\f$ is of type non-commutative, whereas \f$1\f$
   * is a commuting object.
   *
   */
  ex remove_trivial_Zsum(const ex & expr)
  {

    if ( is_a<Zsum>(expr)) 
      {
	const Zsum& Z = ex_to<Zsum>(expr);
	if ( (Z.get_depth() == 0) && (Z.n.is_equal(Infinity)) ) return 1;
      }

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = expr.nops();
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( remove_trivial_Zsum(expr.op(j)));
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

