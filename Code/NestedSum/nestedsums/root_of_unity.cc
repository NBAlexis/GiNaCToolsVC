
/** @file root_of_unity.cc
 *
 * Implementation of root_of_unity
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

GINAC_IMPLEMENT_REGISTERED_CLASS(root_of_unity, basic)

GINAC_BIND_UNARCHIVER(root_of_unity);

  root_of_unity::root_of_unity() : inherited(),
    l(0), k(1)
  { 
  }

  void root_of_unity::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_unsigned("l",l);
    node.add_unsigned("k",k);
  }

  void root_of_unity::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_unsigned("l",l);
    node.find_unsigned("k",k);
  }

  int root_of_unity::compare_same_type(const basic &other) const
  {
    const root_of_unity &o = static_cast<const root_of_unity &>(other);

    if ( k != o.k )
      {
	return (k > o.k) ? 1 : -1;
      } 

    if ( l != o.l )
      {
	return (l > o.l) ? 1 : -1;
      } 

    // now they are equal
    return 0;

  }

  // other ctors
  root_of_unity::root_of_unity(unsigned ll, unsigned kk) : inherited(), 
    l(ll), k(kk)
  { }


  // functions overriding virtual functions from bases classes

  unsigned root_of_unity::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= l;

      v = rotate_left_31(v);
      v ^= k;

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

  void root_of_unity::print(const print_context & c, unsigned level) const
  {
    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "r^{" << l << "}_{" << k << "}";
	if (precedence() <= level) c.s << ")}";
      } 
    else if (is_a<print_tree>(c)) 
      {
	c.s << std::string(level, ' ') << class_name()
	    << std::hex << ", hash=0x" << hashvalue << ", flags=0x" << flags << std::dec
	    << ", nops=" << nops()
	    << std::endl;
      } 
    else 
      {
	if (precedence() <= level) c.s << "(";
	c.s << "r^" << l << "_" << k;
	if (precedence() <= level) c.s << ")";
      }
  }

  /**
   *
   * The following simplifications are done:
   *
   * - If \f$l = 0\f$ return 1.
   * 
   * - If \f$l > k\f$, the root of unity is reduced to \f$r_k^{l'}\f$, 
   *   where \f$ l' = l \; \mbox{mod} \; k\f$.
   *
   * - If \f$\mbox{gcd}(l,k) \neq 1\f$ the gcd is divided out.
   *
   */
  ex root_of_unity::eval() const
  {
 
    if ( l == 0) return 1;

    if ( (l==1) && (k==2) ) return -1;

    if ( l > k ) return create_root_of_unity( mod(ex_to<numeric>(l),ex_to<numeric>(k)).to_int(), k );

    unsigned g = gcd(ex_to<numeric>(l),ex_to<numeric>(k)).to_int();
    if ( g != 1 ) return create_root_of_unity( l/g, k/g );

    return this->hold();
  }

  /**
   *
   * Multiplication is done according to
   * \f[
   *    r_{k_1}^{l_1} r_{k_2}^{l_2} = \exp \left( 2 \pi i \frac{k_2 l_1 + k_1 l_2}{k_1 k_2} \right)
   * \f]
   *
   */
  ex root_of_unity::eval_ncmul(const exvector & v) const
  {
    if ( v.size() <= 1 ) return hold_ncmul(v);

    // at least two, take out the last two and multiply them

    ex e1 = v[v.size()-1];
    ex e2 = v[v.size()-2];

    if ( is_a<root_of_unity>(e1) && is_a<root_of_unity>(e2) )
      {
	exvector s = v;
	s.pop_back();
	s.pop_back();

	const root_of_unity& r1 = ex_to<root_of_unity>(e1);
	const root_of_unity& r2 = ex_to<root_of_unity>(e2);

	return ncmul(s) * create_root_of_unity( r2.k*r1.l + r1.k*r2.l, r1.k*r2.k );

      }

    // default
    return hold_ncmul(v);
  }

  ex root_of_unity::derivative(const symbol & s) const
  {
    return 0;
  }

  ex root_of_unity::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return *this;
  }

  // new virtual functions

  // non-virual functions

  // utility functions

} // namespace nestedsums

