
/** @file harmonic_sum.cc
 *
 * Implementation of harmonic sums 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(harmonic_sum, Ssum)

GINAC_BIND_UNARCHIVER(harmonic_sum);


  harmonic_sum::harmonic_sum() : inherited()
  { 
  }

  void harmonic_sum::archive(archive_node &node) const
  {
    inherited::archive(node);
  }

  void harmonic_sum::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);
  }

  int harmonic_sum::compare_same_type(const basic &other) const
  {
    const harmonic_sum &o = dynamic_cast<const harmonic_sum &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  harmonic_sum::harmonic_sum(const ex & nc) : inherited(nc,_empty_list)
  { }

  harmonic_sum::harmonic_sum(const ex & nc, const ex & llc) : inherited(nc,llc)
  { }


  // functions overriding virtual functions from bases classes
  return_type_t harmonic_sum::return_type_tinfo() const 
  {
    return _default_Ssum.return_type_tinfo();
  }

  void harmonic_sum::print(const print_context & c, unsigned level) const
  {
    size_t depth = get_depth();

    // empty sum equals 1
    if (depth == 0) 
      {
	if (is_a<print_latex>(c)) 
	  {
	    if (precedence() <= level) c.s << "{(";
	    c.s << "S(" ;
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
	    c.s << "S(" ;
	    n.print(c);
	    c.s << ")";
	    if (precedence() <= level) c.s << ")";
	  }
	return;
      }

    int i;

    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "S_{" ;
	for(i=0;i<depth;i++)
	  {
	    ex_to<letter>(letter_list.op(i)).get_degree().print(c,mul_precedence); 
	  }
	c.s << "}(" ;
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
	c.s << "HS(" ;
	n.print(c);
	for(i=0;i<depth;i++)
	  {
	    c.s << "," ;
	    ex_to<letter>(letter_list.op(i)).get_degree().print(c); 
	  }
	c.s << ")";
	if (precedence() <= level) c.s << ")";
      }
  }

  /**
   *
   * The simplifications are done in the following order:
   *
   * - If the upper summation limit is equal to infinity, we have a harmonic_sum_to_Infinity.
   *
   * - If the upper summation index is an integer, perform the sum explicitly.
   * 
   */
  ex harmonic_sum::eval() const
  {

    // check if the harmonic_sum simplifies to a harmonic_sum_to_Infinity
    if ( n.is_equal(Infinity) ) return create_harmonic_sum_to_Infinity(letter_list);

    // n integer
    if ( n.info(info_flags::integer) ) return this->eval_explicit();

    return this->hold();

  }

  /**
   *
   * A more efficient version for the conversion to Euler_Zagier_sums, based
   * on exvector (e.g. std::vector<GiNaC::ex> ).
   * Z0 contains the result.
   * Z1 is reversed order, so that we can use pop_back.
   *
   */ 
  ex harmonic_sum::convert_to_Zsum_exvector(const exvector & Z0, const exvector & Z1) const
  {

    // recursion start
    if ( Z1.size()==0 )
      {
	return create_Euler_Zagier_sum_from_exvector(n,Z0);
      }

    if ( Z1.size()==1 )
      {
	exvector ZZ0 = Z0;
	// use the reverse iterator
	ZZ0.insert(ZZ0.end(),Z1.rbegin(),Z1.rend());
	return create_Euler_Zagier_sum_from_exvector(n,ZZ0);
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

    ZZ3.push_back(ex_to<unit_letter>(x1).concat_speedy(x2));

    return convert_to_Zsum_exvector(ZZ01,ZZ2)
          +convert_to_Zsum_exvector(Z0,ZZ3);

  }

  /**
   *
   * A more efficient version for the multiplication of harmonic_sums, based
   * on exvector (e.g. std::vector<GiNaC::ex> ).
   * Z0 contains the result.
   * Z1 and Z2 are in reversed order, so that we can use pop_back.
   *
   */ 
  ex harmonic_sum::shuffle_exvector(const exvector & Z0, const exvector & Z1, const exvector & Z2) const
    {
      if ( Z1.size()==0 && Z2.size()==0) 
	{
	  return create_harmonic_sum_from_exvector(n,Z0);
	}

      if ( Z2.size()==0) 
	{
	  exvector ZZ0 = Z0;
	  // use the reverse iterator
	  ZZ0.insert(ZZ0.end(),Z1.rbegin(),Z1.rend());
	  return create_harmonic_sum_from_exvector(n,ZZ0);
	}

      if ( Z1.size()==0) 
	{
	  exvector ZZ0 = Z0;
	  // use the reverse iterator
	  ZZ0.insert(ZZ0.end(),Z2.rbegin(),Z2.rend());
	  return create_harmonic_sum_from_exvector(n,ZZ0);
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
      ZZ012.push_back(ex_to<unit_letter>(x1).concat_speedy(x2));

      Z1_removed.pop_back();
      Z2_removed.pop_back();

      return shuffle_exvector(ZZ01,Z1_removed,Z2)
            +shuffle_exvector(ZZ02,Z1,Z2_removed)
            -shuffle_exvector(ZZ012,Z1_removed,Z2_removed);
    }


  /**
   *
   * Sets the upper summation index to \f$i\f$
   *
   */
  ex harmonic_sum::set_index(const ex & i) const
  {
    return create_harmonic_sum(i,letter_list);
  }

  /**
   *
   * Returns \f$S(n+1,m_1,...,1,...)\f$
   *
   */
  ex harmonic_sum::shift_plus_one(void) const
  {
    return create_harmonic_sum(n+1,letter_list);
  }

  /**
   *
   * Returns \f$S(n-1,m_1,...,1,...)\f$
   *
   */
  ex harmonic_sum::shift_minus_one(void) const
  {
    return create_harmonic_sum(n-1,letter_list);
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ down to \f$i\f$, e.g.
   * \f[
   *     S(n;m_1,...;1,...) = S(i;m_1,...;1,...) 
   *      + \sum\limits_{j=0}^{n-i-1} \frac{1}{(i+j+1)^{m_1}} S(i+j+1;m_2,...;1,...)
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
  ex harmonic_sum::adjust_upper_limit_downwards(const ex & i) const
  {
    // S(n,...) = S(i,...) + sum_(j=0..n-i-1) x1^(j+1) basic_letter(x1,m1,j+1) S(i+j+1,...)

    if (get_depth()==0) return create_harmonic_sum(i,lst());

    ex m1 = ex_to<basic_letter>(letter_list.op(0)).get_degree();

    ex res = create_harmonic_sum(i,letter_list);

    for (int j=0;j<n-i;j++)
      {
	res = res + create_basic_letter((ex) 1,m1,1+j,i) * (this->remove_first_letter(i+j+1));
      }
    return res;
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ up to \f$i\f$, e.g.
   * \f[
   *     S(n;m_1,...;1,...) = S(i;m_1,...;1,...) 
   *      \mbox{} - \sum\limits_{j=0}^{i-n-1} \frac{1}{(i-j)^{m_1}} S(i-j;m_2,...;1,...)
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
  ex harmonic_sum::adjust_upper_limit_upwards(const ex & i) const
  {
    // this routine might give rise to poles

    if (get_depth()==0) return create_harmonic_sum(i,lst());

    ex m1 = ex_to<basic_letter>(letter_list.op(0)).get_degree();

    ex res = create_harmonic_sum(i,letter_list);

    for (int j=0;j<i-n;j++)
      {
	res = res - create_basic_letter((ex) 1,m1,-j,i) * (this->remove_first_letter(i-j));
      }
    return res;
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ to \f$n+1\f$, e.g.
   * \f[
   *     S(n;m_1,...;1,...) = S(n+1;m_1,...;1,...) 
   *      \mbox{} - \frac{1}{(n+1)^{m_1}} S(n+1;m_2,...;1,...).
   * \f] 
   *
   */
  ex harmonic_sum::adjust_upper_limit_plus_one(void) const
  {
    if (get_depth()==0) return create_harmonic_sum(n+1,lst());

    ex m1 = ex_to<basic_letter>(letter_list.op(0)).get_degree();

    return create_harmonic_sum(n+1,letter_list) 
      - create_unit_letter(m1,n+1) * (this->remove_first_letter(n+1));
  }

  /**
   *
   * Returns a harmonic_sum with the first letter removed from the letter_list.
   *
   */
  ex harmonic_sum::remove_first_letter(void) const
  {
    size_t depth = get_depth();

    if (depth==0)
      throw(std::logic_error("empty sum"));

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=1;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }

    return create_harmonic_sum(n,*l_new);
  }

  /**
   *
   * Returns a harmonic_sum with the first letter removed from the letter_list
   * and the upper summation index set to nc.
   *
   */
  ex harmonic_sum::remove_first_letter(const ex & nc) const
  {
    size_t depth = get_depth();

    if (depth==0)
      throw(std::logic_error("empty sum"));

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=1;i<depth;i++)
      {
	l_new->append(letter_list.op(i));
      }

    return create_harmonic_sum(nc,*l_new);
  }

  // utility functions

  /**
   *
   * Named ctor on the heap.
   * Creates S_{11...1}(n) with \f$k\f$ unit indices.
   *
   */
 ex create_harmonic_sum_with_ones(const ex &n, const int &k)
 {
   lst* l = new lst();
   l->setflag(status_flags::dynallocated);

   int i;
   for (i=0;i<k;i++)
     {
       l->append(_unit_one_letter);
     }

   return create_harmonic_sum(n,*l);
 }

  /**
   *
   * Construct a harmonic_sum on the heap from an exvector.
   *
   */
  ex create_harmonic_sum_from_exvector(const ex & nc, const exvector & v)
    {
      lst* llc = new lst();
      llc->setflag(status_flags::dynallocated);
      int j;
      for (j=0;j<v.size();j++)
	{
	  llc->append(v[j]);
	}
      return (new harmonic_sum(nc,*llc))->setflag(status_flags::dynallocated);
    }

} // namespace nestedsums

