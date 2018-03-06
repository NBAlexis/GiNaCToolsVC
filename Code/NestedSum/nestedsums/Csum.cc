
/** @file Csum.cc
 *
 * Implementation of Csums 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(Csum, basic)

GINAC_BIND_UNARCHIVER(Csum);



  Csum::Csum() : inherited(),
   n(_default), letter_list(_empty_list)
  { 
  }

  void Csum::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("n",n);
    node.add_ex("letter_list",letter_list);
  }

  void Csum::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("n",n,sym_lst);
    node.find_ex("letter_list",letter_list,sym_lst);
  }

  int Csum::compare_same_type(const basic &other) const
  {
    const Csum &o = static_cast<const Csum &>(other);
    int cmpval;

    cmpval = letter_list.compare(o.letter_list);
    if ( cmpval) return cmpval;

    return n.compare(o.n);
  }

  // other ctors
  Csum::Csum(const ex & nc, const ex & llc) : inherited(), n(nc), letter_list(llc)
  { }

  // functions overriding virtual functions from bases classes

  unsigned Csum::calchash(void) const
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

  void Csum::print(const print_context & c, unsigned level) const
  {
    size_t depth = get_depth();

    int i;

    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "C(" ;
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
	c.s << "C(" ;
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
  ex Csum::eval() const
  {

    return this->hold();

  }

  /**
   *
   * No automatic simplifications
   *
   */
  ex Csum::eval_ncmul(const exvector & v) const
  {
    // default
    return hold_ncmul(v);
  }

  ex Csum::derivative(const symbol & s) const
  {
    return 0;
  }

  ex Csum::subs(const exmap & m, unsigned options) const
  {
	exmap::const_iterator it = m.find(*this);
	if (it != m.end())
		return it->second;

    return create_Csum(n.subs(m,options),letter_list.subs(m,options));
  }

  // new virtual functions

  /**
   *
   * Converts a Csum into Ssums.
   * 
   * The basic object is
   * \f[
   *    \left( \sum\limits_{j_1=1}^{n'} \sum\limits_{j_2=1}^{j_1} ... \sum\limits_{n=1}^{j_{l-1}} 
   *           \frac{y_1^{j_1}}{j_1^{g_1}} ...  \frac{y_l^{n}}{n^{g_l}} \right)
   *     \left( x_k^+ \right)^{m_k} ... 
   *     \left( x_1^+ \right)^{m_1} \left( x_0^+ \right)^{m_0}
   *     \frac{x_k}{1-x_k} \frac{x_{k-1}x_k}{1-x_{k-1}x_k} ...
   *     \frac{x_1 ... x_k}{1-x_1 ... x_k}
   *     \left[ 1 - \left( 1 - x_0 x_1 ... x_k \right)^n \right]
   * \f]
   *
   * If \f$m_0>0\f$ we have
   * \f[
   *    \left( \sum\limits_{j_1=1}^{n'} \sum\limits_{j_2=1}^{j_1} ... \sum\limits_{n=1}^{j_{l-1}} ... 
   *    \sum\limits_{i=1}^{n} \frac{1}{i} \right)
   *     \left( x_k^+ \right)^{m_k} ... 
   *     \left( x_1^+ \right)^{m_1} \left( x_0^+ \right)^{m_0-1}
   *     \frac{x_k}{1-x_k} \frac{x_{k-1}x_k}{1-x_{k-1}x_k} ...
   *     \frac{x_1 ... x_k}{1-x_1 ... x_k}
   *     \left[ 1 - \left( 1 - x_0 x_1 ... x_k \right)^i \right]
   * \f]
   *
   * If the depth of the Csum is \f$1\f$ and \f$m_0=0\f$, we have
   * \f[
   *    \left( \sum\limits_{j_1=1}^{n'} ... \sum\limits_{n=1}^{j_{l-1}} ... \right)
   *    \mbox{} - \left( \sum\limits_{j_1=1}^{n'} ... \sum\limits_{n=1}^{j_{l-1}} ... (1-x_0)^n \right)
   * \f]
   *
   * If \f$m_0=0\f$, \f$m_1>0\f$ and \f$x_0 \neq 1 \f$ we have
   * \f[
   *    \mbox{} - \left( \sum\limits_{j_1=1}^{n'} ... (1-x_0)^n 
   *     \sum\limits_{i=1}^n \frac{1}{i} \left( \frac{1}{1-x_0} \right)^i 
   *     \left( x_k^+ \right)^{m_k} ... 
   *     \left( \left(x_0 x_1\right)^+ \right)^{m_1-1} 
   *     \frac{x_k}{1-x_k} \frac{x_{k-1}x_k}{1-x_{k-1}x_k} ...
   *     \frac{x_2 ... x_k}{1-x_2 ... x_k}
   *     \left[ 1 - \left( 1 - (x_0 x_1) ... x_k \right)^i \right] \right)
   * \f]
   * \f[
   *    \mbox{} + \left( \sum\limits_{j_1=1}^{n'} ... \right)
   *     \sum\limits_{i_1=1}^N \frac{x_1}{i_1^{m_1}}
   *     \sum\limits_{i_2=i_1+1}^N ... \sum\limits_{i_k=i_{k-1}+1}^N 
   *       \frac{x_2^{i_2}}{i_2^{m_2}} ... \frac{x_k^{i_k}}{i_k^{m_k}}  
   * \f]
   * \f[
   *    \mbox{} - \left( \sum\limits_{j_1=1}^{n'} ... (1-x_0)^n \right)
   *     \sum\limits_{i_1=1}^N \frac{x_1}{i_1^{m_1}}
   *     \sum\limits_{i_2=i_1+1}^N ... \sum\limits_{i_k=i_{k-1}+1}^N 
   *       \frac{x_2^{i_2}}{i_2^{m_2}} ... \frac{x_k^{i_k}}{i_k^{m_k}}  
   * \f]
   *
   * In the case \f$m_0=0\f$, \f$m_1>0\f$ and \f$x_0 = 1 \f$ we have
   * \f[
   *    \mbox{} - \left( \sum\limits_{j_1=1}^{n'} ...  \frac{1}{n} \right)
   *     \left( x_k^+ \right)^{m_k} ... 
   *     \left( x_1^+ \right)^{m_1-1} 
   *     \frac{x_k}{1-x_k} \frac{x_{k-1}x_k}{1-x_{k-1}x_k} ...
   *     \frac{x_2 ... x_k}{1-x_2 ... x_k}
   *     \left[ 1 - \left( 1 - x_1 ... x_k \right)^n \right]
   * \f]
   * \f[
   *    \mbox{} + \left( \sum\limits_{j_1=1}^{n'} ...  \right)
   *      \sum\limits_{i=1}^N \frac{x_1^{i}}{i^{m_1}} 
   *      \sum\limits_{i_2=i+1}^{N} ... \sum\limits_{i_k = i_{k-1}+1}^{N}
   *      \frac{x_2^{i_2}}{i_2^{m_2}} ... \frac{x_k^{i_k}}{i_k^{m_k}}
   * \f]
   *
   */
  ex Csum::convert_to_Ssum_exvector(const exvector & Z1) const
  {
      size_t depth = get_depth();
#ifdef _DEBUG
    if ( _debug_level & 16 ) 
      {
	std::cout << " ---------------------------- " << std::endl;
	std::cout << std::endl;
	std::cout << "entering Csum::convert_to_Ssum_exvector" << std::endl;
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

    // letter_list contains at least x0 letter
    const letter& l0 = ex_to<letter>(letter_list.op(0));

    // m_0 > 0
    if (l0.get_degree().info(info_flags::posint))
      {
	return ex_to<Csum>(
			  this->decrease_letter_degree(0)
			 ).convert_to_Ssum_exvector(exvector_append_lst(Z1,lst{_unit_one_letter}) );
      }

    // ----------------------
    // m_0 = 0 now

    // recursion start, depth 1
    if (depth == 1)
      {
	ex x0 = l0.get_scale();

	if ( x0.is_equal(1) )
	  {
	    return create_Ssum_from_exvector(n,Z1);
	  }
	else
	  {
	    // handles also the case ZZ1.depth == 0
	    if ( Z1.size() > 0 )
	      {
		return create_Ssum_from_exvector(n,Z1) 
		  - create_Ssum_from_exvector(n,exvector_multiply_last_letter(Z1,1-x0));
	      }
	    else 
	      {
		ex temp_Ssum = create_Ssum_from_exvector(n,Z1);
		return temp_Ssum - create_letter(1-x0,0,n) * temp_Ssum;
	      }
	  }
      }

    // depth > 1, m_1 > 0
    const letter& l1 = ex_to<letter>(letter_list.op(1));

    if (l1.get_degree().info(info_flags::posint))
      {
	ex x0 = l0.get_scale();

	if ( x0.is_equal(1) ) // x0 == 1 first 
	  {
	    ex new_Csum = ex_to<Csum>(this->move_x0_into_x1()).decrease_letter_degree(0);

	    // handle case Z1.depth == 0
	    ex temp_Csum;
	    if ( Z1.size() > 0 )
	      {
		temp_Csum = ex_to<Csum>(new_Csum).convert_to_Ssum_exvector(exvector_increase_last_degree(Z1));
	      }
	    else
	      {
		temp_Csum = create_unit_letter(1,n) * ex_to<Csum>(new_Csum).convert_to_Ssum_exvector(Z1);
	      }

	    exvector new_Zinf;
	    new_Zinf.push_back(letter_list.op(1));

	    ex new_Bsum = create_Bsum(Infinity,
				      ex_to<Csum>(this->remove_x0_and_x1()).letter_list);

	    ex temp_Bsum = ex_to<Bsum>(new_Bsum).convert_to_Ssum_exvector(new_Zinf);

	    return - temp_Csum
	      + create_Ssum_from_exvector(n,Z1) * temp_Bsum ;
	      ;
	  }
	else // x0 != 1
	  {
	    ex new_l = create_letter(1/(1-x0),1);

	    ex new_Csum = ex_to<Csum>(this->move_x0_into_x1()).decrease_letter_degree(0);

	    exvector new_Zinf;
	    new_Zinf.push_back(letter_list.op(1));
	    ex new_Bsum = create_Bsum(Infinity,
				      ex_to<Csum>(this->remove_x0_and_x1()).letter_list);
	    ex temp_Bsum = ex_to<Bsum>(new_Bsum).convert_to_Ssum_exvector(new_Zinf);

	    // handle the case Z1.depth == 0
	    if ( Z1.size() > 0 )
	      {
		exvector new_Z1 = exvector_append_lst(exvector_multiply_last_letter(Z1,1-x0),lst{new_l});

		return 
		  -ex_to<Csum>(new_Csum).convert_to_Ssum_exvector(new_Z1)
		  + create_Ssum_from_exvector(n,Z1) * temp_Bsum
		  - create_Ssum_from_exvector(n,exvector_multiply_last_letter(Z1,1-x0)) * temp_Bsum
		  ;
	      }
	    else
	      {
		exvector new_Z1;
		new_Z1.push_back(new_l);

		ex temp_Ssum = create_Ssum_from_exvector(n,Z1);

		return 
		  - create_letter(1-x0,0,n) * ex_to<Csum>(new_Csum).convert_to_Ssum_exvector(new_Z1)
		  + temp_Ssum * temp_Bsum
		  - create_letter(1-x0,0,n) * temp_Ssum * temp_Bsum
		  ;
	      }

	  } // end if x0 != 1
      }

    // default, should not occur
    return create_Ssum_from_exvector(n,Z1);
  }

  /**
   *
   * Returns a Csum where the degree of the m'th letter is
   * decreased by one.
   *
   */
  ex Csum::decrease_letter_degree(int m) const
    {
      size_t depth = get_depth();

      if (depth==0)
	throw(std::logic_error("empty sum"));

      int i;
      lst* l_new = new lst();
      l_new->setflag(status_flags::dynallocated);
      for (i=0;i<m;i++)
	{
	  l_new->append(letter_list.op(i));
	}

      l_new->append(ex_to<letter>(letter_list.op(m)).degree_minus_one());

      for (i=m+1;i<depth;i++)
	{
	  l_new->append(letter_list.op(i));
	}

      return create_Csum(n,*l_new);
    }

  /**
   *
   * Returns
   * \f[
   *     \left( x_k^+ \right)^{m_k} ... 
   *     \left( \left(x_0 x_1\right)^+ \right)^{m_1} 
   *     \frac{x_k}{1-x_k} \frac{x_{k-1}x_k}{1-x_{k-1}x_k} ...
   *     \frac{x_2 ... x_k}{1-x_2 ... x_k}
   *     \left[ 1 - \left( 1 - (x_0 x_1) ... x_k \right)^i \right]
   * \f]
   *
   */
  ex Csum::move_x0_into_x1(void) const
    {
      size_t depth = get_depth();

      if (depth<2)
	throw(std::logic_error("sum must have at least depth two"));

      int i;
      lst* l_new = new lst();
      l_new->setflag(status_flags::dynallocated);

      const letter& l0 = ex_to<letter>(letter_list.op(0));
      const letter& l1 = ex_to<letter>(letter_list.op(1));

      l_new->append(create_letter(l0.get_scale()*l1.get_scale(),l1.get_degree()));

      for (i=2;i<depth;i++)
	{
	  l_new->append(letter_list.op(i));
	}

      return create_Csum(n,*l_new);
    }

  /**
   *
   * Returns
   * \f[
   *     \left( x_k^+ \right)^{m_k} ... 
   *     \left( \left(x_2 x_1\right)^+ \right)^{m_2} 
   *     \left( x_0^+ \right)^{m_0} ... 
   *     \frac{x_k}{1-x_k} \frac{x_{k-1}x_k}{1-x_{k-1}x_k} ...
   *     \frac{(x_1 x_2) ... x_k}{1-(x_1 x_2) ... x_k}
   *     \left[ 1 - \left( 1 - x_0 (x_1 x_2) ... x_k \right)^i \right]
   * \f]
   *
   */
  ex Csum::move_x1_into_x2(void) const
    {
      size_t depth = get_depth();

      if (depth<3)
	throw(std::logic_error("sum must have at least depth three"));

      int i;
      lst* l_new = new lst();
      l_new->setflag(status_flags::dynallocated);

      const letter& l1 = ex_to<letter>(letter_list.op(1));
      const letter& l2 = ex_to<letter>(letter_list.op(2));

      l_new->append(letter_list.op(0));
      l_new->append(create_letter(l1.get_scale()*l2.get_scale(),l2.get_degree()));

      for (i=3;i<depth;i++)
	{
	  l_new->append(letter_list.op(i));
	}

      return create_Csum(n,*l_new);
    }

  /**
   *
   * Removes x0.
   *
   */
  ex Csum::remove_x0(void) const
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

      return create_Csum(n,*l_new);
    }

  /**
   *
   * Removes x0 and x1.
   *
   */
  ex Csum::remove_x0_and_x1(void) const
    {
      size_t depth = get_depth();

      if (depth<2)
	throw(std::logic_error("empty sum or sum of depth one"));

      int i;
      lst* l_new = new lst();
      l_new->setflag(status_flags::dynallocated);

      for (i=2;i<depth;i++)
	{
	  l_new->append(letter_list.op(i));
	}

      return create_Csum(n,*l_new);
    }

  /**
   *
   * Returns a Bsum with the same letter list and the same upper summation limit.
   *
   */
  ex Csum::cast_to_Bsum(void) const
    {
      return create_Bsum(n,letter_list);
    }


  ex Csum::expand_members(int level) const
  {
    size_t depth = get_depth();

    int i;
    lst* l_new = new lst();
    l_new->setflag(status_flags::dynallocated);
    for (i=0;i<depth;i++)
      {
	l_new->append(nestedsums_helper_expand(letter_list.op(i),level));
      }

    return create_Csum(nestedsums_helper_expand(n,level),*l_new);
  }

  // utility functions

  /**
   *
   * Functional form for the conversion to a Ssum.
   *
   */
  ex convert_Csum_to_Ssum(const ex & C)
  {
    if (!is_a<Csum>(C))
      throw(std::invalid_argument("argument must be a Csum"));

    const Csum& CC = ex_to<Csum>(C);

    exvector vstart;
    return CC.convert_to_Ssum_exvector(vstart);
  }

  /**
   *
   * Functional form for the conversion to a Zsum.
   *
   */
  ex convert_Csum_to_Zsum(const ex & C)
  {
    if (!is_a<Csum>(C))
      throw(std::invalid_argument("argument must be a Csum"));

    const Csum& CC = ex_to<Csum>(C);

    exvector vstart;
    return Ssum_to_Zsum(CC.convert_to_Ssum_exvector(vstart));
  }

  /**
   *
   * Construct a Csum on the heap from an exvector.
   *
   */
  ex create_Csum_from_exvector(const ex & nc, const exvector & v)
    {
      lst* llc = new lst();
      llc->setflag(status_flags::dynallocated);
      int j;
      for (j=0;j<v.size();j++)
	{
	  llc->append(v[j]);
	}
      return (new Csum(nc,*llc))->setflag(status_flags::dynallocated);
    }

} // namespace nestedsums

