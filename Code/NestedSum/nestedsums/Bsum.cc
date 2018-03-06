
/** @file Bsum.cc
 *
 * Implementation of Bsums 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(Bsum, basic)

GINAC_BIND_UNARCHIVER(Bsum);


  Bsum::Bsum() : inherited(),
   n(_default), letter_list(_empty_list)
  { 
  }

  void Bsum::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("n",n);
    node.add_ex("letter_list",letter_list);
  }

  void Bsum::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("n",n,sym_lst);
    node.find_ex("letter_list",letter_list,sym_lst);
  }

  int Bsum::compare_same_type(const basic &other) const
  {
    const Bsum &o = static_cast<const Bsum &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors
  Bsum::Bsum(const ex & nc, const ex & llc) : inherited(), n(nc), letter_list(llc)
  { }

  // functions overriding virtual functions from bases classes

  unsigned Bsum::calchash(void) const
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

  void Bsum::print(const print_context & c, unsigned level) const
  {
    size_t depth = get_depth();

    int i;

    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "B(" ;
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
	c.s << "B(" ;
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
   * No automatic simplifications
   *
   */
  ex Bsum::eval() const
  {

    return this->hold();

  }

  /**
   *
   * No automatic simplifications
   *
   */
  ex Bsum::eval_ncmul(const exvector & v) const
  {
    // default
    return hold_ncmul(v);
  }

  ex Bsum::derivative(const symbol & s) const
  {
    return 0;
  }

  ex Bsum::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_Bsum(n.subs(m,options),letter_list.subs(m,options));
  }

  // new virtual functions

  /**
   *
   * The basic object is
   * \f[
   *    \left( \sum\limits_{j_1=1}^{n'} \sum\limits_{j_2=1}^{j_1} ... \sum\limits_{n=1}^{j_{l-1}} 
   *           \frac{y_1^{j_1}}{j_1^{g_1}} ...  \frac{y_l^{n}}{n^{g_l}} \right)
   *      \sum\limits_{i_1=n+1}^{N} ... \sum\limits_{i_k = i_{k-1}+1}^{N}
   *      \frac{x_1^{i_1}}{i_1^{m_1}} ... \frac{x_k^{i_k}}{i_k^{m_k}}
   * \f]
   *
   * We use
   * \f[
   *      \sum\limits_{i_1=n+1}^{N} ... \sum\limits_{i_k = i_{k-1}+1}^{N}
   *      \frac{x_1^{i_1}}{i_1^{m_1}} ... \frac{x_k^{i_k}}{i_k^{m_k}}
   * \f] \f[
   *     = (-1)^k S(n;m_1,...m_k;x_1,...,x_k) - (-1)^k S(N;m_1,...m_k;x_1,...,x_k)
   * \f] \f[
   *           + (-1)^k S(N;m_2,...m_k;x_2,...,x_k)
   *                    \sum\limits_{i_1=n+1}^{N} \frac{x_1^{i_1}}{i_1^{m_1}} 
   *           ...
   * \f] \f[
   *           + (-1)^k S(N;m_k;x_k)
   *                    \sum\limits_{i_1=n+1}^{N} ... \sum\limits_{i_{k-1} = i_{k-2}+1}^{N}
   *                    \frac{x_1^{i_1}}{i_1^{m_1}} ... \frac{x_{k-1}^{i_{k-1}}}{i_{k-1}^{m_{k-1}}}
   * 
   * \f]
   *
   */
  ex Bsum::convert_to_Ssum_exvector(const exvector & Z1) const
  {
      size_t depth = get_depth();
#ifdef _DEBUG
    if ( _debug_level & 32 ) 
      {
	std::cout << " ---------------------------- " << std::endl;
	std::cout << std::endl;
	std::cout << "entering Bsum::convert_Bsum_to_Ssum" << std::endl;
	std::cout << std::endl;
	std::cout << "S.n              : " << ex_to<Ssum>(create_Ssum_from_exvector(n,Z1)).get_index() << std::endl;
	std::cout << "S.depth          : " << ex_to<Ssum>(create_Ssum_from_exvector(n,Z1)).get_depth() << std::endl;
	std::cout << "S.letter_list    : " << ex_to<Ssum>(create_Ssum_from_exvector(n,Z1)).get_letter_list() << std::endl;
	std::cout << std::endl;
	std::cout << "n                : " << n << std::endl;
	std::cout << "depth            : " << depth << std::endl;
	std::cout << "letter_list      : " << letter_list << std::endl;
      }
#endif // def _DEBUG

    // are we done ?
    if ( depth == 0 ) return create_Ssum_from_exvector(n,Z1);

    ex k_sign = GiNaC::pow(-1,depth);

    ex res = k_sign * create_Ssum_from_exvector(n,exvector_append_lst(Z1,letter_list));

    int i,j;
    for (j=0;j<depth;j++)
      {
	exvector S_list;
	exvector C_list;
	S_list.reserve(depth-j);
	C_list.reserve(j);

	for (i=0;i<j;i++)
	  {
	    C_list.push_back(letter_list.op(i));
	  }

	for (i=j;i<depth;i++)
	  {
	    S_list.push_back(letter_list.op(i));
	  }

	res = res 
	  -  k_sign * GiNaC::pow(-1,j)
	  * create_Ssum_from_exvector(Infinity,S_list) 
	  * ex_to<Bsum>(create_Bsum_from_exvector(n,C_list)).convert_to_Ssum_exvector(Z1)
	      ;
      }

    return res;
  }

  ex Bsum::expand_members(int level) const
  {
    size_t depth = get_depth();

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=0;i<depth;i++)
      {
	l_new->append(nestedsums_helper_expand(letter_list.op(i),level));
      }

    return create_Bsum(nestedsums_helper_expand(n,level),*l_new);
  }

  // utility functions

  /**
   *
   * Functional form for the conversion to a Ssum.
   *
   */
  ex convert_Bsum_to_Ssum(const ex & C)
  {
    if (!is_a<Bsum>(C))
      throw(std::invalid_argument("argument must be a Bsum"));

    const Bsum& CC = ex_to<Bsum>(C);

    exvector vstart;
    return CC.convert_to_Ssum_exvector(vstart);
  }

  /**
   *
   * Functional form for the conversion to a Zsum.
   *
   */
  ex convert_Bsum_to_Zsum(const ex & C)
  {
    if (!is_a<Bsum>(C))
      throw(std::invalid_argument("argument must be a Bsum"));

    const Bsum& CC = ex_to<Bsum>(C);

    exvector vstart;
    return Ssum_to_Zsum(CC.convert_to_Ssum_exvector(vstart));
  }

  /**
   *
   * Construct a Bsum on the heap from an exvector.
   *
   */
  ex create_Bsum_from_exvector(const ex & nc, const exvector & v)
    {
      lst* llc = new lst();
      llc->setflag(status_flags::dynallocated);
      int j;
      for (j=0;j<v.size();j++)
	{
	  llc->append(v[j]);
	}
      return (new Bsum(nc,*llc))->setflag(status_flags::dynallocated);
    }

} // namespace nestedsums

