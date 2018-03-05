
/** @file Euler_Zagier_sum.cc
 *
 * Implementation of Euler-Zagier sums 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(Euler_Zagier_sum, Zsum)

GINAC_BIND_UNARCHIVER(Euler_Zagier_sum);



  Euler_Zagier_sum::Euler_Zagier_sum() : inherited()
  { 
  }

  void Euler_Zagier_sum::archive(archive_node &node) const
  {
    inherited::archive(node);
  }

  void Euler_Zagier_sum::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);
  }

  int Euler_Zagier_sum::compare_same_type(const basic &other) const
  {
    const Euler_Zagier_sum &o = dynamic_cast<const Euler_Zagier_sum &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors

  // ctor with initialization list
  Euler_Zagier_sum::Euler_Zagier_sum(const ex & nc) : inherited(nc,_empty_list)
  { }

  Euler_Zagier_sum::Euler_Zagier_sum(const ex & nc, const ex & llc) : inherited(nc,llc)
  { }

  // functions overriding virtual functions from bases classes
  return_type_t Euler_Zagier_sum::return_type_tinfo() const 
  {
    return _default_Zsum.return_type_tinfo();
  }

  void Euler_Zagier_sum::print(const print_context & c, unsigned level) const
  {
    unsigned depth = get_depth();

    // empty sum equals 1
    if (depth == 0) 
      {
	if (is_a<print_latex>(c))
	  {
	    if (precedence() <= level) c.s << "{(";
	    c.s << "Z(" ;
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
	    c.s << "Z(" ;
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
	c.s << "Z_{" ;
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
	c.s << "EZ(" ;
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
   * - If the upper summation limit is equal to infinity, we have a multiple zeta value.
   *
   * - If the upper summation index is an integer, perform the sum explicitly.
   * 
   */
  ex Euler_Zagier_sum::eval() const
  {

    // check if the Euler_Zagier_sum simplifies to a multiple zeta value
    if ( n.is_equal(Infinity) ) return create_multiple_zeta_value(letter_list);

    // n integer
    if ( n.info(info_flags::integer) ) return this->eval_explicit();

    return this->hold();

  }

  /**
   *
   * A more efficient version for the conversion to harmonic sums, based
   * on exvector (e.g. std::vector<GiNaC::ex> ).
   * Z0 contains the result.
   * Z1 is reversed order, so that we can use pop_back.
   *
   */ 
  ex Euler_Zagier_sum::convert_to_Ssum_exvector(const exvector & Z0, const exvector & Z1) const
  {

    // recursion start
    if ( Z1.size()==0 )
      {
	return create_harmonic_sum_from_exvector(n,Z0);
      }

    if ( Z1.size()==1 )
      {
	exvector ZZ0 = Z0;
	// use the reverse iterator
	ZZ0.insert(ZZ0.end(),Z1.rbegin(),Z1.rend());
	return create_harmonic_sum_from_exvector(n,ZZ0);
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

    return convert_to_Ssum_exvector(ZZ01,ZZ2)
          -convert_to_Ssum_exvector(Z0,ZZ3);

  }

  /**
   *
   * A more efficient version for the multiplication of Euler_Zagier_sums, based
   * on exvector (e.g. std::vector<GiNaC::ex> ).
   * Z0 contains the result.
   * Z1 and Z2 are in reversed order, so that we can use pop_back.
   *
   */ 
  ex Euler_Zagier_sum::shuffle_exvector(const exvector & Z0, const exvector & Z1, const exvector & Z2) const
    {
      if ( Z1.size()==0 && Z2.size()==0) 
	{
	  return create_Euler_Zagier_sum_from_exvector(n,Z0);
	}

      if ( Z2.size()==0) 
	{
	  exvector ZZ0 = Z0;
	  // use the reverse iterator
	  ZZ0.insert(ZZ0.end(),Z1.rbegin(),Z1.rend());
	  return create_Euler_Zagier_sum_from_exvector(n,ZZ0);
	}

      if ( Z1.size()==0) 
	{
	  exvector ZZ0 = Z0;
	  // use the reverse iterator
	  ZZ0.insert(ZZ0.end(),Z2.rbegin(),Z2.rend());
	  return create_Euler_Zagier_sum_from_exvector(n,ZZ0);
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
            +shuffle_exvector(ZZ012,Z1_removed,Z2_removed);
    }

  /**
   *
   * Sets the upper summation index to \f$i\f$
   *
   */
  ex Euler_Zagier_sum::set_index(const ex & i) const
  {
    return create_Euler_Zagier_sum(i,letter_list);
  }

  /**
   *
   * Returns \f$Z(n+1,m_1,...,1,...)\f$
   *
   */
  ex Euler_Zagier_sum::shift_plus_one(void) const
  {
    return create_Euler_Zagier_sum(n+1,letter_list);
  }

  /**
   *
   * Returns \f$Z(n-1,m_1,...,1,...)\f$
   *
   */
  ex Euler_Zagier_sum::shift_minus_one(void) const
  {
    return create_Euler_Zagier_sum(n-1,letter_list);
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ down to \f$i\f$, e.g.
   * \f[
   *     Z(n;m_1,...;1,...) = Z(i;m_1,...;1,...) 
   *      + \sum\limits_{j=1}^{n-i} \frac{1}{(i+j)^{m_1}} Z(i-1+j;m_2,...;1,...)
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
  ex Euler_Zagier_sum::adjust_upper_limit_downwards(const ex & i) const
  {
    // Z(n,...) = Z(i,...) + sum_(j=1..n-i) x1^j basic_letter(x1,m1,j) Z(i+j-1,...)

    if (get_depth()==0) return create_Euler_Zagier_sum(i,lst());

    ex m1 = ex_to<basic_letter>(letter_list.op(0)).get_degree();

    ex res = create_Euler_Zagier_sum(i,letter_list);

    for (int j=1;j<n-i+1;j++)
      {
	res = res + create_basic_letter((ex) 1,m1,j,i) * (this->remove_first_letter(i+j-1));
      }
    return res;
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ up to \f$i\f$, e.g.
   * \f[
   *     Z(n;m_1,...;1,...) = Z(i;m_1,...;1,...) 
   *      \mbox{} - \sum\limits_{j=0}^{i-n-1} \frac{1}{(i-j)^{m_1}} Z(i-j-1;m_2,...;1,...)
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
  ex Euler_Zagier_sum::adjust_upper_limit_upwards(const ex & i) const
  {
    // this routine might give rise to poles

    if (get_depth()==0) return create_Euler_Zagier_sum(i,lst());

    ex m1 = ex_to<basic_letter>(letter_list.op(0)).get_degree();

    ex res = create_Euler_Zagier_sum(i,letter_list);

    for (int j=0;j<i-n;j++)
      {
	res = res - create_basic_letter((ex) 1,m1,-j,i) * (this->remove_first_letter(i-j-1));
      }
    return res;
  }

  /**
   *
   * Adjusts the upper summation limit \f$n\f$ to \f$n+1\f$, e.g.
   * \f[
   *     Z(n;m_1,...;1,...) = Z(n+1;m_1,...;1,...) 
   *      \mbox{} - \frac{1}{(n+1)^{m_1}} Z(n;m_2,...;1,...).
   * \f] 
   *
   */
  ex Euler_Zagier_sum::adjust_upper_limit_plus_one(void) const
  {
    if (get_depth()==0) return create_Euler_Zagier_sum(n+1,lst());

    ex m1 = ex_to<basic_letter>(letter_list.op(0)).get_degree();

    return create_Euler_Zagier_sum(n+1,letter_list)
      - create_unit_letter(m1,n+1) * (this->remove_first_letter());
  }

  /**
   *
   * Returns a Euler_Zagier_sum with the first letter removed from the letter_list.
   *
   */
  ex Euler_Zagier_sum::remove_first_letter(void) const
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

    return create_Euler_Zagier_sum(n,*l_new);
  }

  /**
   *
   * Returns a Euler_Zagier_sum with the first letter removed from the letter_list
   * and the upper summation index set to nc.
   *
   */
  ex Euler_Zagier_sum::remove_first_letter(const ex & nc) const
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

    return create_Euler_Zagier_sum(nc,*l_new);
  }

  // utility functions

  /**
   *
   * Named ctor on the heap.
   * Creates Z_{11...1}(n) with \f$k\f$ unit indices.
   *
   */
 ex create_Euler_Zagier_sum_with_ones(const ex &n, const int &k)
 {
   lst* l = new lst();
   l->setflag(status_flags::dynallocated);

   int i;
   for (i=0;i<k;i++)
     {
       l->append(_unit_one_letter);
     }

   return create_Euler_Zagier_sum(n,*l);
 }

  /**
   *
   * Construct a Euler_Zagier_sum on the heap from an exvector.
   *
   */
  ex create_Euler_Zagier_sum_from_exvector(const ex & nc, const exvector & v)
    {
      lst* llc = new lst();
      llc->setflag(status_flags::dynallocated);
      int j;
      for (j=0;j<v.size();j++)
	{
	  llc->append(v[j]);
	}
      return (new Euler_Zagier_sum(nc,*llc))->setflag(status_flags::dynallocated);
    }

} // namespace nestedsums

