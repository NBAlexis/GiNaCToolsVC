
/** @file Ssum.cc
 *
 * Implementation of Ssums 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(Ssum, basic)

GINAC_BIND_UNARCHIVER(Ssum);

  Ssum::Ssum() : inherited(),
   n(_default), letter_list(_empty_list)
  { 
  }

  void Ssum::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("n",n);
    node.add_ex("letter_list",letter_list);
  }

  void Ssum::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("n",n,sym_lst);
    node.find_ex("letter_list",letter_list,sym_lst);
  }

  int Ssum::compare_same_type(const basic &other) const
  {
    const Ssum &o = static_cast<const Ssum &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  Ssum::Ssum(const ex & nc) : inherited(), n(nc), letter_list(_empty_list)
  { }

  Ssum::Ssum(const ex & nc, const ex & llc) : inherited(), n(nc), letter_list(llc)
  { }

  // functions overriding virtual functions from bases classes

  unsigned Ssum::calchash(void) const
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

  void Ssum::print(const print_context & c, unsigned level) const
  {
    unsigned depth = get_depth();

    int i;

    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "S(" ;
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
	c.s << "S(" ;
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
   * - If the upper summation limit is equal to infinity, we have a Ssum_to_Infinity
   *
   * - If all \f$x_j\f$'s are equal to 1, we have a harmonic sum.
   *
   * - If the upper summation index is an integer, perform the sum explicitly.
   * 
   */
  ex Ssum::eval() const
  {
    // check if Ssum simplifies to a Ssum_to_Infinity
    if ( n.is_equal(Infinity) ) return create_Ssum_to_Infinity(letter_list);

    // check if Ssum simplifies to harmonic sum
    unsigned depth = get_depth();

    if ( depth==0 ) return create_harmonic_sum(n,letter_list);
    int i=0;
    while ( is_a<unit_letter>(letter_list.op(i++)) )
      {
	if ( i==depth) return create_harmonic_sum(n,letter_list);
      }

    // n integer
    if ( n.info(info_flags::integer) ) return this->eval_explicit();

    return this->hold();
  }

  /**
   *
   * A product of Ssums is simplified, if the last two have the same
   * upper summation index.
   *
   * A product is also simplified if the difference between the two upper summation indices is an integer.
   * The factor with the "larger" upper summation index is converted to the "smaller" index with the help
   * of the function Zsum::adjust_upper_limit_downwards.
   * Note that the algorithm returns a product, where
   * both factors have the "smaller" index.
   *
   */
  ex Ssum::eval_ncmul(const exvector & v) const
  {
    if ( v.size() <= 1 ) return hold_ncmul(v);

    // at least two Ssums, take out the last two and multiply them

    ex e1 = v[v.size()-1];
    ex e2 = v[v.size()-2];

    if ( is_a<Ssum>(e1) && is_a<Ssum>(e2) )
      {
	exvector s = v;
	s.pop_back();
	s.pop_back();

	const Ssum& Z1 = ex_to<Ssum>(e1);
	const Ssum& Z2 = ex_to<Ssum>(e2);

	// avoid infinite recursion
	if ( Z1.n.is_equal(Z2.n) )
	  {
	    // we want the friend function shuffle here
	    return ncmul(s)*shuffle_Ssum(e2,e1);
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

	// S(Infinity) is always 1
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

  ex Ssum::derivative(const symbol & s) const
  {
    return 0;
  }

  ex Ssum::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_Ssum(n.subs(m,options),letter_list.subs(m,options));
  }

  // new virtual functions

  /**
   *
   * Method to convert a Ssum to a Zsum. 
   *
   * An efficient version for the conversion to Zsums, based
   * on exvector (e.g. std::vector<GiNaC::ex> ).
   * Z0 contains the result.
   * Z1 is reversed order, so that we can use pop_back.
   *
   * The basic formula is 
   * \f[
   *    S(n;m_1,...;x_1,...) = \sum\limits_{i=1}^n \frac{x_1^i}{i^{m_1}} S(i-1;m_2,...;x_2,...)
   *     \mbox{} + S(n;m_1+m_2,...;x_1 x_2, ...)
   * \f]
   *
   */ 
  ex Ssum::convert_to_Zsum_exvector(const exvector & Z0, const exvector & Z1) const
  {

    // recursion start
    if ( Z1.size()==0 )
      {
	return create_Zsum_from_exvector(n,Z0);
      }

    if ( Z1.size()==1 )
      {
	exvector ZZ0 = Z0;
	// use the reverse iterator
	ZZ0.insert(ZZ0.end(),Z1.rbegin(),Z1.rend());
	return create_Zsum_from_exvector(n,ZZ0);
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

    return convert_to_Zsum_exvector(ZZ01,ZZ2)
          +convert_to_Zsum_exvector(Z0,ZZ3);

  }

  /**
   *
   * Method to multiply two Ssums.
   *
   * An efficient version for the multiplication of Ssums, based
   * on exvector (e.g. std::vector<GiNaC::ex> ).
   * Z0 contains the result.
   * Z1 and Z2 are in reversed order, so that we can use pop_back.
   *
   * The basic formula is 
   * \f[
   *    S(n;m_1,...;x_1,...) S(n;m_1',...;x_1',...) 
   *      = \sum\limits_{i=1}^n \frac{x_1^i}{i^{m_1}} S(i;m_2,...;x_2,...) S(i;m_1',...;x_1',...)
   * \f] \f[
   *      \mbox{} + \sum\limits_{i=1}^n \frac{{x_1'}^i}{i^{m_1'}} S(i;m_1,...;x_1,...) S(i;m_2',...;x_2',...)
   *      \mbox{} - \sum\limits_{i=1}^n \frac{(x_1 {x_1'})^i}{i^{m_1+m_1'}} S(i;m_2,...;x_2,...) S(i;m_2',...;x_2',...)
   * \f]
   * Note the minus sign in front of the last term.
   *
   */ 
  ex Ssum::shuffle_exvector(const exvector & Z0, const exvector & Z1, const exvector & Z2) const
    {
      if ( Z1.size()==0 && Z2.size()==0) 
	{
	  return create_Ssum_from_exvector(n,Z0);
	}

      if ( Z2.size()==0) 
	{
	  exvector ZZ0 = Z0;
	  // use the reverse iterator
	  ZZ0.insert(ZZ0.end(),Z1.rbegin(),Z1.rend());
	  return create_Ssum_from_exvector(n,ZZ0);
	}

      if ( Z1.size()==0) 
	{
	  exvector ZZ0 = Z0;
	  // use the reverse iterator
	  ZZ0.insert(ZZ0.end(),Z2.rbegin(),Z2.rend());
	  return create_Ssum_from_exvector(n,ZZ0);
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
            -shuffle_exvector(ZZ012,Z1_removed,Z2_removed);
    }


  /**
   *
   * Helper routine to convert a Ssum with upper limit \f$n\f$ to 
   * Ssums with upper limit \f$q \cdot n\f$.
   *
   * Z0 contains the result in reversed order.
   * Z1 the letter list, which has to be converted.
   *
   * The basic formula is
   * \f[
   *    \sum\limits_{i=1}^n \frac{x^i}{i^m} S( q \cdot i;...)
   *      = q^{m-1} \sum\limits_{l=0}^{q-1}
   *                \sum\limits_{i=1}^{q \cdot n} \frac{1}{i^m}
   *                \left( r_q^l x^{1/q} \right)^i S(i;...)
   * \f]
   * Here \f$r_q^l\f$ are roots of unity.
   *
   */ 
  ex Ssum::refine_exvector(unsigned q, const exvector & Z0, const exvector & Z1) const
  {
    // recursion start
    if ( Z1.size()==0 )
      {
	exvector ZZ0;
	// use the reverse iterator
	ZZ0.insert(ZZ0.end(),Z0.rbegin(),Z0.rend());

	if ( !(n.is_equal(Infinity)) )
	  { 
	    return create_Ssum_from_exvector(q*n,ZZ0);
	  }
	else
	  {
	    // n=Infinity stays Infinity
	    return create_Ssum_from_exvector(n,ZZ0);
	  }
      }

    // Z1 has now at least one elements
    ex ll = Z1[Z1.size()-1];
    ex x = ex_to<letter>(ll).get_scale();
    ex m = ex_to<letter>(ll).get_degree();

    exvector ZZ1 = Z1;
    ZZ1.pop_back();

    ex res = 0;

    for (unsigned l=0;l<q;l++)
      {
	exvector ZZ01 = Z0;
	ZZ01.push_back( create_letter( pow(x,numeric(1,q)) 
                                       * create_root_of_unity(l,q), m) );
	res = res + refine_exvector(q,ZZ01,ZZ1);
      }

    return pow(q,m-1)*res;
  }

  /**
   *
   * Method to convert a Ssum with upper limit \f$n\f$ to 
   * Ssums with upper limit \f$q \cdot n\f$.
   *
   */
  ex Ssum::refine(unsigned q) const
  {
    exvector vres;
    return this->refine_exvector(q,vres,exvector_from_lst(letter_list));
  }

  /**
   *
   * Returns the first letter from the letter_list.
   *
   */
  ex Ssum::get_first_letter(void) const
  {
    if (get_depth()==0)
      throw(std::logic_error("empty sum"));

    return letter_list.op(0);
  }

  /**
   *
   * Returns a Ssum with the first letter removed from the letter_list.
   *
   */
  ex Ssum::remove_first_letter(void) const
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

    return create_Ssum(n,*l_new);
  }

  /**
   *
   * Returns a Ssum with the first letter removed from the letter_list
   * and the upper summation index set to nc.
   *
   */
  ex Ssum::remove_first_letter(const ex & nc) const
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

    return create_Ssum(nc,*l_new);
  }

  /**
   *
   * Prepends the letter lc to the letter_list.
   *
   */ 
  ex Ssum::prepend_letter(const ex & lc) const
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

    return create_Ssum(n,*l_new);
  }

  /**
   *
   * Prepends the letter lc to the letter_list and sets
   * the upper summation index to nc.
   *
   */ 
  ex Ssum::prepend_letter(const ex & nc, const ex & lc) const
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

    return create_Ssum(nc,*l_new);
  }

  /**
   *
   * Appends the letter lc to the letter_list.
   *
   */ 
  ex Ssum::append_letter(const ex & lc) const
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

    return create_Ssum(n,*l_new);
  }

  /**
   *
   * Appends the list lc to the letter_list.
   *
   */ 
  ex Ssum::append_letter_list(const ex & lc) const
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

    return create_Ssum(n,*l_new);
  }

  /**
   *
   * Creates a Zsum with the same upper summation index and the
   * same letter_list.
   *
   * This is a crude cast, something like reinterpret_cast.
   *
   */
  ex Ssum::cast_to_Zsum(void) const
  {
    return create_Zsum(n,letter_list);
  }

  /**
   *
   * Sets the upper summation index to \f$i\f$
   *
   */
  ex Ssum::set_index(const ex & i) const
  {
    return create_Ssum(i,letter_list);
  }

  /**
   *
   * Returns \f$S(n+1,m_1,...,x_1,...)\f$
   *
   */
  ex Ssum::shift_plus_one(void) const
  {
    return create_Ssum(n+1,letter_list);
  }

  /**
   *
   * Returns \f$S(n-1,m_1,...,x_1,...)\f$
   *
   */
  ex Ssum::shift_minus_one(void) const
  {
    return create_Ssum(n-1,letter_list);
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ down to \f$i\f$, e.g.
   * \f[
   *     S(n;m_1,...;x_1,...) = S(i;m_1,...;x_1,...) 
   *      + \sum\limits_{j=0}^{n-i-1} x_1^{j+1} \frac{x_1^i}{(i+j+1)^{m_1}} S(i+j+1;m_2,...;x_2,...)
   * \f] 
   * with \f$n > i \f$.
   *
   * For the empty sum we have
   * \f[
   *     S(n) = S(i)
   * \f]
   *
   * This routine assumes \f$ i \ge 1 \f$.
   *
   */
  ex Ssum::adjust_upper_limit_downwards(const ex & i) const
  {
    // S(n,...) = S(i,...) + sum_(j=0..n-i-1) x1^(j+1) basic_letter(x1,m1,j+1) S(i+j+1,...)

    if (get_depth()==0) return create_Ssum(i,lst());

    const basic_letter& l1 = ex_to<basic_letter>(letter_list.op(0));

    ex x1 = l1.get_scale();
    ex m1 = l1.get_degree();

    ex res = create_Ssum(i,letter_list);

    for (int j=0;j<n-i;j++)
      {
	res = res + pow(x1,1+j) * create_basic_letter(x1,m1,1+j,i) * (this->remove_first_letter(i+j+1));
      }
    return res;
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ up to \f$i\f$, e.g.
   * \f[
   *     S(n;m_1,...;x_1,...) = S(i;m_1,...;x_1,...) 
   *      \mbox{} - \sum\limits_{j=0}^{i-n-1} x_1^{-j} \frac{x_1^i}{(i-j)^{m_1}} S(i-j;m_2,...;x_2,...)
   * \f] 
   * with \f$n < i \f$.
   *
   * For the empty sum we have
   * \f[
   *     S(n) = S(i)
   * \f]
   *
   * This routine assumes \f$ n \ge 1 \f$.
   *
   * This routine might give rise to poles for some values of \f$i\f$ and should be used with care.
   *
   */
  ex Ssum::adjust_upper_limit_upwards(const ex & i) const
  {
    // this routine might give rise to poles

    if (get_depth()==0) return create_Ssum(i,lst());

    const basic_letter& l1 = ex_to<basic_letter>(letter_list.op(0));

    ex x1 = l1.get_scale();
    ex m1 = l1.get_degree();

    ex res = create_Ssum(i,letter_list);

    for (int j=0;j<i-n;j++)
      {
	res = res - pow(x1,-j) * create_basic_letter(x1,m1,-j,i) * (this->remove_first_letter(i-j));
      }
    return res;
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ to \f$n+1\f$, e.g.
   * \f[
   *     S(n;m_1,...;x_1,...) = S(n+1;m_1,...;x_1,...) 
   *      \mbox{} - \frac{x_1^{n+1}}{(n+1)^{m_1}} S(n+1;m_2,...;x_2,...).
   * \f] 
   *
   */
  ex Ssum::adjust_upper_limit_plus_one(void) const
  {
    if (get_depth()==0) return create_Ssum(n+1,lst());

    const basic_letter& l1 = ex_to<basic_letter>(letter_list.op(0));

    ex x1 = l1.get_scale();
    ex m1 = l1.get_degree();

    return create_Ssum(n+1,letter_list)
      - create_letter(x1,m1,n+1) * (this->remove_first_letter(n+1));
  }

  /**
   *
   * Returns
   * \f[
   *     S(1;m_1,...,m_k;x_1,...,x_k) = x_1 \cdot ... \cdot x_k
   * \f]
   */
  ex Ssum::index_eq_one(void) const
  {
    // this can be done better
    return this->set_index(1);
  }

  /**
   *
   * Returns from the S-sum \f$ S(n;m_1,...,m_l;x_1,...,x_l) \f$ the head
   * \f$ S(n;m_1,...,m_{k-1};x_1,...,x_{k-1}) \f$.
   *
   */
  ex Ssum::get_head(int k) const
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

    return create_Ssum(n,*l_new);
  }

  /**
   *
   * Returns from the S-sum \f$ S(n;m_1,...,m_l;x_1,...,x_l) \f$ the tail
   * \f$ S(n;m_k,...,m_l;x_k,...,x_l) \f$.
   *
   */
  ex Ssum::get_tail(int k) const
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

    return create_Ssum(n,*l_new);
  }

  /**
   *
   * Returns a Ssum, where the letter lc is multiplied with the last letter
   * in the letter list of the original Ssum.
   *
   * If the sum is empty, e.g. \f$S(n)\f$, the result is \f$\frac{x^n}{n^m} S(n)\f$.
   *
   */
  ex Ssum::multiply_letter_with_last_letter(const ex & lc) const
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

    return create_Ssum(n,*l_new);
  }

  /**
   *
   * Returns a Ssum, where the letter lc is multiplied with the first letter
   * in the letter list of the original Ssum.
   *
   * If the sum is empty, e.g. \f$S(n)\f$, the result is \f$\frac{x^n}{n^m} S(n)\f$.
   *
   */
  ex Ssum::multiply_letter_with_first_letter(const ex & lc) const
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

    return create_Ssum(n,*l_new);
  }

  /**
   *
   * Takes Z1 as head and Z2 as tail and forms a new sum as the concatenation of the two.
   *
   */
  ex Ssum::concat_two_sums(const ex & Z1, const ex & Z2) const
  {
    if ( (!is_a<Ssum>(Z1)) || (!is_a<Ssum>(Z2)) ) return Z1*Z2;

    const Ssum& ZZ1 = ex_to<Ssum>(Z1);
    const Ssum& ZZ2 = ex_to<Ssum>(Z2);

    return ZZ1.append_letter_list(ZZ2.letter_list);
  }

  /**
   *
   * Signals if there are letters with negative or zero degrees.
   *
   * Only for Ssums.
   *
   */
  int Ssum::flag_remove_negative_degrees(void) const
  {
    unsigned depth = get_depth();

    int flag = 0;

    int i;
    for (i=depth-1;i>=0;i--)
      {
	ex m = ex_to<letter>(letter_list.op(i)).get_degree();

	if ( (m.info(info_flags::integer)) && (!m.info(info_flags::posint)) ) flag++;
      }

    return flag;
  }

  /**
   *
   * Removes letters with non-positive degrees.
   *
   * The basic formula is
   * \f[
   *    S(n;-m_1,m_2,...;x_1,x_2,...) =
   *       \sum\limits_{i2=1}^n \frac{x_2^{i_2}}{i_2^{m_2}} S(i_2;m_3,...;x_3,...) 
   *        \sum\limits_{i_1=i_2}^n i_1^{m_1} x_1^{i_1}
   * \f]
   * For \f$x_1 \neq 1\f$ we have
   * \f[
   *    \sum\limits_{i_1=i_2}^n i_1^{m_1} x_1^{i_1} =
   *      \left( x_1^- \right)^{m_1} \left( \frac{1}{1-x_1} x_1^{i_2} - \frac{x_1}{1-x_1} x_1^n \right)
   * \f]
   * For \f$x_1 = 1\f$ we have
   * \f[
   *    \sum\limits_{i_1=i_2}^n i_1^{m_1} =
   *       \sum\limits_{i_1=1}^n i_1^{m_1} - \sum\limits_{i_1=1}^{i_2-1} i_1^{m_1}
   * \f]
   * and the sums can be done analytically with the help of the Bernoulli numbers:
   * \f[
   *    \sum\limits_{i=1}^{n} i^m = n^m + \sum\limits_{k=0}^m \frac{B_k}{k!} \frac{m!}{(m+1-k)!} n^{m+1-k}
   * \f]
   * 
   *
   */
  ex Ssum::remove_negative_degrees(void) const
  {
    unsigned depth = get_depth();

    int i;
    for (i=depth-1;i>=0;i--)
      {
	const letter& actual_letter = ex_to<letter>(letter_list.op(i));
	ex m = actual_letter.get_degree();
	ex x = actual_letter.get_scale();

	// case m<=0 and x<>1
	if ( (m.info(info_flags::integer)) && (!m.info(info_flags::posint)) && (!x.is_equal(1)) )
	  {
	    ex head_ex = this->get_head(i);
	    const Ssum& head = ex_to<Ssum>(head_ex);
	    ex tail_ex = ex_to<Ssum>(this->get_tail(i)).remove_first_letter();
	    const Ssum& tail = ex_to<Ssum>(tail_ex);
	    int m_abs = - ex_to<numeric>(m).to_int();

	    int k;
	    ex res = 0 ;
	    for (k=0;k<m_abs+1;k++)
	      {
		if ( tail.get_depth() > 0 )
		  {
		    if ( ( head.get_depth()==0 ) && ( n.is_equal(Infinity) ) )
		      {
			res = res 
			  + binomial(m_abs,k)
			  * nestedsums_helper_lowering_op_geo_0(x, m_abs-k)
			  * concat_two_sums(head_ex,tail.multiply_letter_with_first_letter(create_letter(x,-k)));
		      }
		    else // no sum to Infinity
		      {
			res = res 
			  + binomial(m_abs,k)
			  * nestedsums_helper_lowering_op_geo_0(x, m_abs-k)
			  * concat_two_sums(head_ex,tail.multiply_letter_with_first_letter(create_letter(x,-k)))
			  - binomial(m_abs,k)
			  * nestedsums_helper_lowering_op_geo_1(x, m_abs-k)
			  * concat_two_sums(head.multiply_letter_with_last_letter(create_letter(x,-k)),tail_ex);
		      }
		  }
		else if ( tail.get_depth() == 0 )
		  {
		    if ( ( head.get_depth()==0 ) && ( n.is_equal(Infinity) ) )
		      {
			// nothing to be done here
		      }
		    else // no sum to Infinity
		      {
			res = res 
			  - binomial(m_abs,k)
			  * nestedsums_helper_lowering_op_geo_1(x, m_abs-k)
			  * concat_two_sums(head.multiply_letter_with_last_letter(create_letter(x,-k)),tail_ex);
		      }
		  }
	      }

	    if ( tail.get_depth() == 0 )
	      {
		res = res + nestedsums_helper_lowering_op_geo_1(x, m_abs) * head_ex;
	      }

	    return remove_negative_degrees_from_Ssum(res);
	  }

	// case m<=0 and x=1
	else if ( (m.info(info_flags::integer)) && (!m.info(info_flags::posint)) && x.is_equal(1) )
	  {
	    ex head_ex = this->get_head(i);
	    const Ssum& head = ex_to<Ssum>(head_ex);
	    ex tail_ex = ex_to<Ssum>(this->get_tail(i)).remove_first_letter();
	    const Ssum& tail = ex_to<Ssum>(tail_ex);
	    int m_abs = - ex_to<numeric>(m).to_int();

	    // cannot handle case sum to Inifinty
	    if ( ( head.get_depth()==0 ) && ( n.is_equal(Infinity) ) ) 
	      {
		throw(std::invalid_argument("cannot remove negative degree in a sum to Infinity"));
	      }

	    if ( m_abs == 0 ) 
	      {
		if ( tail.get_depth() > 0 )
		  {
		    return remove_negative_degrees_from_Ssum(
			     concat_two_sums(head.multiply_letter_with_last_letter(create_unit_letter(-1)),tail_ex)
			     - concat_two_sums(head_ex,tail.multiply_letter_with_first_letter(create_unit_letter(-1)))
			     + concat_two_sums(head_ex,tail_ex) );
		  }
		else if ( tail.get_depth() == 0 )
		  {
		    return remove_negative_degrees_from_Ssum(
			     concat_two_sums(head.multiply_letter_with_last_letter(create_unit_letter(-1)),tail_ex) );
		  }
	      }

	    ex res = concat_two_sums(head.multiply_letter_with_last_letter(create_unit_letter(-m_abs)),tail_ex);
	    int k;
	    for (k=0;k<m_abs+1;k++)
	      {
		if ( tail.get_depth() > 0 )
		  {
		    res = res + nestedsums_helper_bernoulli(k)/factorial(k)*factorial(m_abs)/factorial(m_abs+1-k)
		      * concat_two_sums(head.multiply_letter_with_last_letter(create_unit_letter(-m_abs-1+k)),tail_ex)
		      - nestedsums_helper_bernoulli(k)/factorial(k)*factorial(m_abs)/factorial(m_abs+1-k)
		      * concat_two_sums(head_ex,tail.multiply_letter_with_first_letter(create_unit_letter(-m_abs-1+k,n)))
		      ;
		  }
		else if ( tail.get_depth() == 0 )
		  {
		    res = res + nestedsums_helper_bernoulli(k)/factorial(k)*factorial(m_abs)/factorial(m_abs+1-k)
		      * concat_two_sums(head.multiply_letter_with_last_letter(create_unit_letter(-m_abs-1+k)),tail_ex)
		      ;
		  }
	      }

	    return remove_negative_degrees_from_Ssum(res);
	  }

      }

    // no negative degrees
    return *this;
  }

  ex Ssum::expand_members(int level) const
  {
    unsigned depth = get_depth();

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=0;i<depth;i++)
      {
	l_new->append(nestedsums_helper_expand(letter_list.op(i),level));
      }

    return create_Ssum(nestedsums_helper_expand(n,level),*l_new);
  }

  /**
   *
   * Explicit evaluation
   *
   */
  ex Ssum::eval_explicit() const
  {
    unsigned depth = get_depth();

    int i,flag;

    // n <= 0 : return 0
    if ( n.info(info_flags::negint) || n.is_zero() ) return 0;
 
    // n is a positive integer : evaluate the sum
    if ( n.info(info_flags::posint) )
      {
	// empty sum and n >0 : return 1
	if ( depth==0 ) return 1;

	// depth > 0 now
	ex res = 0 ;
	ex letter_l = ex_to<letter>(get_first_letter()).get_scale();
	ex degree = ex_to<letter>(get_first_letter()).get_degree();
	for (i=1;i<=n;i++)
	  {
	    res = res + pow(letter_l,i)/pow(i,degree) * remove_first_letter(i);
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
  ex Ssum::get_weight(void) const
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
   * Functional form for the multiplication of two Ssums.
   *
   * The method shuffle_exvector is called for the multiplication.
   * If both sums are harmonic sums, the reimplementation of shuffle_exvector
   * in the class harmonic_sum is used directly.
   *
   * If the upper summation limits are not equal, the function returns unevaluated.
   *
   *
   */
  ex shuffle_Ssum(const ex & Z1, const ex & Z2)
  {
    if (!is_a<Ssum>(Z1))
      throw(std::invalid_argument("first argument must be a Ssum"));
    if (!is_a<Ssum>(Z2))
      throw(std::invalid_argument("second argument must be a Ssum"));

    const Ssum& ZZ1 = ex_to<Ssum>(Z1);
    const Ssum& ZZ2 = ex_to<Ssum>(Z2);

    if (ZZ1.n.is_equal(ZZ2.n))
      {

	if ( is_a<harmonic_sum>(Z1) && is_a<harmonic_sum>(Z2) )
	  {
	    harmonic_sum* res = new harmonic_sum(ZZ1.n);
	    res->setflag(status_flags::dynallocated);
	    exvector vres;
	    return res->shuffle_exvector(vres,reverse_exvector_from_lst(ZZ1.letter_list),
					 reverse_exvector_from_lst(ZZ2.letter_list));
	  }
	else
	  {
	    Ssum* res = new Ssum(ZZ1.n);
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
  ex convert_Ssum_to_Zsum(const ex & Z1)
  {
    // already checked
    const Ssum& ZZ1 = ex_to<Ssum>(Z1);

    // empty sums are theta functions
    if ( (ZZ1.get_depth()==0) && !(ZZ1.n.is_equal(Infinity)) ) return create_Zsum(ZZ1.n-1,_empty_list);

    if ( is_a<harmonic_sum>(Z1) )
      {
	harmonic_sum* res = new harmonic_sum(ZZ1.n);
	res->setflag(status_flags::dynallocated);
	exvector vres;
	return res->convert_to_Zsum_exvector(vres,reverse_exvector_from_lst(ZZ1.letter_list));
      }
    else
      {
	Ssum* res = new Ssum(ZZ1.n);
	res->setflag(status_flags::dynallocated);
	exvector vres;
	return res->convert_to_Zsum_exvector(vres,reverse_exvector_from_lst(ZZ1.letter_list));
      } 

    return Z1;
  }

  /**
   *
   * Construct a Ssum on the heap from an exvector.
   *
   */
  ex create_Ssum_from_exvector(const ex & nc, const exvector & v)
    {
      lst* llc = new lst();
      llc->setflag(status_flags::dynallocated);
      int j;
      for (j=0;j<v.size();j++)
	{
	  llc->append(v[j]);
	}
      return (new Ssum(nc,*llc))->setflag(status_flags::dynallocated);
    }

  /**
   *
   * Convert all Ssums occuring in expr into Zsums.
   *
   */
  ex Ssum_to_Zsum(const ex & expr)
  {

    if ( is_a<Ssum>(expr)) return convert_Ssum_to_Zsum(expr);

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = expr.nops();
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( Ssum_to_Zsum(expr.op(j)));
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
   * Convert all S(n,...) appearing in the expression to S(n+1,...).
   *
   */
  ex shift_upper_limit_plus_one_for_Ssum(const ex & expr)
  {

    if ( is_a<Ssum>(expr)) return ex_to<Ssum>(expr).adjust_upper_limit_plus_one();

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = expr.nops();
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( shift_upper_limit_plus_one_for_Ssum(expr.op(j)));
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
   * Removes non-positive degrees in Ssums.
   *
   */
  ex remove_negative_degrees_from_Ssum(const ex & expr)
  {

    if ( is_a<Ssum>(expr)) return ex_to<Ssum>(expr).remove_negative_degrees();

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = expr.nops();
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( remove_negative_degrees_from_Ssum(expr.op(j)));
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
   *    S(\infty)  \rightarrow  1
   * \f]
   *
   * This function has to be used with care, since
   * \f$S(\infty)\f$ is of type non-commutative, whereas \f$1\f$
   * is a commuting object.
   *
   */
  ex remove_trivial_Ssum(const ex & expr)
  {

    if ( is_a<Ssum>(expr)) 
      {
	const Ssum& Z = ex_to<Ssum>(expr);
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
	    res_exvector.push_back( remove_trivial_Ssum(expr.op(j)));
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
   * Refines all Ssums from \f$S(n)\f$ to \f$S(q \cdot n )\f$.
   *
   */
  ex refine_Ssum(const ex & expr, unsigned q)
  {

    if ( is_a<Ssum>(expr)) return ex_to<Ssum>(expr).refine(q);

    // addition, multiplication or ncmul
    if ( is_a<add>(expr) || is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int up_limit = expr.nops();
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	  {
	    res_exvector.push_back( refine_Ssum(expr.op(j),q ));
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

