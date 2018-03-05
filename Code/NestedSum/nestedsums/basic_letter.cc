
/** @file basic_letter.cc
 *
 * Implementation of basic_letter
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

GINAC_IMPLEMENT_REGISTERED_CLASS(basic_letter, basic)

GINAC_BIND_UNARCHIVER(basic_letter);

  basic_letter::basic_letter() : inherited(),
    scale(_default), degree(_default), offset(_default), index(_default_index)
  { 
  }

  void basic_letter::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("scale",scale);
    node.add_ex("degree",degree);
    node.add_ex("offset",offset);
    node.add_ex("index",index);
  }

  void basic_letter::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("scale",scale,sym_lst);
    node.find_ex("degree",degree,sym_lst);
    node.find_ex("offset",offset,sym_lst);
    node.find_ex("index",index,sym_lst);
  }

  int basic_letter::compare_same_type(const basic &other) const
  {
    const basic_letter &o = static_cast<const basic_letter &>(other);

    int cmpval = scale.compare(o.scale);

    if( cmpval ) return cmpval;

    cmpval = degree.compare(o.degree);

    if( cmpval ) return cmpval;

    cmpval = index.compare(o.index);

    if( cmpval ) return cmpval;

    return offset.compare(o.offset);

  }

  // other ctors
  basic_letter::basic_letter(const ex & l, const ex & d, const ex & o) : inherited(), 
    scale(l), degree(d), offset(o), index(_default_index)
  { }

  basic_letter::basic_letter(const ex & l, const ex & d, const ex & o, const ex & i) : inherited(),
    scale(l), degree(d), offset(o), index(i)
  { }


  // functions overriding virtual functions from bases classes

  unsigned basic_letter::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= scale.gethash();

      v = rotate_left_31(v);
      v ^= degree.gethash();

      v = rotate_left_31(v);
      v ^= offset.gethash();

      v = rotate_left_31(v);
      v ^= index.gethash();

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

  void basic_letter::print(const print_context & c, unsigned level) const
  {
    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "\\frac{";
	scale.print(c,pow_precedence);
	c.s << "^{";
	index.print(c,pow_precedence);
	c.s << "}}{";
	c.s << "(";
	index.print(c,add_precedence);
	c.s << "+";
	offset.print(c,add_precedence);
	c.s << ")";
	c.s << "^{";
	degree.print(c,pow_precedence);
	c.s << "}}";
	if (precedence() <= level) c.s << ")}";
      } 
    else if (is_a<print_tree>(c)) 
      {
	c.s << std::string(level, ' ') << class_name()
	    << std::hex << ", hash=0x" << hashvalue << ", flags=0x" << flags << std::dec
	    << ", nops=" << nops()
	    << std::endl;
	scale.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	degree.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	offset.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	index.print(c, level + static_cast<const print_tree &>(c).delta_indent);
      } 
    else 
      {
	if (precedence() <= level) c.s << "(";
	scale.print(c,pow_precedence);
	c.s << "^";
	index.print(c,pow_precedence);
	c.s << "/";
	c.s << "(";
	index.print(c,add_precedence);
	c.s << "+";
	offset.print(c,add_precedence);
	c.s << ")";
	c.s << "^";
	degree.print(c,pow_precedence);
	if (precedence() <= level) c.s << ")";
      }
  }

  /**
   *
   * If the offset is zero, evaluation returns a letter .
   *
   * If the index is an integer, the object is evaluated explicitly.
   *
   */
  ex basic_letter::eval() const
  {

    if ( offset.is_zero()) return create_letter(scale,degree,index);

    if ( index.info(info_flags::integer) ) return this->eval_explicit();

    return this->hold();

  }

  /**
   *
   * A product of two basic_letter's is simplified, if
   * - the two indices are equal, or at least one of the indices is equal to the default index;
   * - and both basic_letter's are actually of  type letter;
   * - or the types are only basic_letter's, but both degrees are integer.
   *
   * A product is also simplified if the difference between the two indices is an integer, according to
   * \f[
   *    \frac{x^{i+l}}{((i+l)+c)^m} \frac{y^i}{(i+c')^{m'}}
   *    = x^l \frac{x^{i}}{(i+(c+l))^m} \frac{y^i}{(i+c')^{m'}}
   * \f]
   * where \f$ l > 0 \f$. Note that the algorithm returns a product, where
   * both factors have the "smaller" index.
   *
   */
  ex basic_letter::eval_ncmul(const exvector & v) const
  {
    if ( v.size() <= 1 ) return hold_ncmul(v);

    // at least two, take out the last two and multiply them

    ex e1 = v[v.size()-1];
    ex e2 = v[v.size()-2];

    if ( is_a<basic_letter>(e1) && is_a<basic_letter>(e2) )
      {
	exvector s = v;
	s.pop_back();
	s.pop_back();

	const basic_letter& l1 = ex_to<basic_letter>(e1);
	const basic_letter& l2 = ex_to<basic_letter>(e2);

	// check the indices
	if (    l1.index.is_equal(_default_index) || l2.index.is_equal(_default_index)
	     || l1.index.is_equal(l2.index) )
	  {
	    // avoid infinte recursion, multiply only if concat does not return unevaluated
	    // 
	    // two letters can be multiplied
	    if ( is_a<letter>(e1) && is_a<letter>(e2) )
	      {
		return ncmul(s) * l2.concat_speedy(e1) ;
	      }

	    // integer degrees
	    if ( l1.degree.info(info_flags::integer) && l2.degree.info(info_flags::integer) )
	      {
		return ncmul(s) * l2.concat_speedy(e1) ;
	      }
	  } // end if check indices

	// difference is integer
	ex c = l1.index - l2.index;
	if ( c.info(info_flags::posint) )
	  {
	    return pow(l1.scale,c) * ncmul(s) * e2 * create_basic_letter(l1.scale,l1.degree,l1.offset+c,l2.index);
	  }
	else if ( c.info(info_flags::negint) )
	  {
	    return pow(l2.scale,-c) * ncmul(s) * create_basic_letter(l2.scale,l2.degree,l2.offset-c,l1.index) * e1; 
	  }
       
      }

    // default
    return hold_ncmul(v);

  }

  ex basic_letter::derivative(const symbol & s) const
  {
    return 0;
  }

  ex basic_letter::subs(const exmap & m, unsigned options) const
  {
	exmap::const_iterator it = m.find(*this);
	if (it != m.end())
		return it->second;

    return create_basic_letter(scale.subs(m,options),degree.subs(m,options),offset.subs(m,options),index.subs(m,options));
  }

  // new virtual functions

  /**
   *
   * Concats two letters.
   * The routine checks first if the argument is of type basic_letter.
   * 
   * It then checks, if the indices are compatible
   * (e.g., equal indices, or at least one index equal to the default one).
   *
   * If this is the case, the method concat_speedy is called, otherwise
   * the routine returns unevaluated.
   *
   */
  ex basic_letter::concat(const ex & l) const
  {
    if (!is_a<basic_letter>(l))
      throw(std::invalid_argument("argument must be a basic_letter"));

    const basic_letter& bl = ex_to<basic_letter>(l);

    // check the indices
    if (  !( index.is_equal(_default_index) 
	     || bl.index.is_equal(_default_index)
	     || index.is_equal(bl.index) ) )
      { return (*this)*l; }

    return this->concat_speedy(l);

  }

  /**
   *
   * Same as concat, but does not perform any checking.
   * Assumes that the indices are the same or equal to the default one.
   *
   *
   *  The multiplication is performed if the two basic_letters have
   *
   *   - the same offset
   *     \f[
   *        \frac{x^i}{(i+c)^{m_1}} \frac{y^i}{(i+c)^{m_2}} = \frac{(xy)^i}{(i+c)^{m_1+m_2}}
   *     \f]
   *
   *   - unequal offsets, but both degrees are integers (and not symbols).
   *     
   *     If one of the degrees is zero, we have
   *     \f[
   *        \frac{x^i}{(i+c)^{m}} y^i = \frac{(xy)^i}{(i+c)^{m}}
   *     \f]
   *
   *     If both degrees are positive, we have
   *     \f[
   *        \frac{x^i}{(i+c_1)^{m_1}} \frac{y^i}{(i+c_2)^{m_2}} 
   *           = \frac{1}{c_2-c_1} \left[ \frac{x^i}{(i+c_1)^{m_1}} \frac{y^i}{(i+c_2)^{m_2-1}}
   *                                    \mbox{} - \frac{x^i}{(i+c_1)^{m_1-1}} \frac{y^i}{(i+c_2)^{m_2}} \right]
   *     \f]
   *
   *     If one degree is positive (\f$m_1\f$), the other negative (\f$m_2\f$), we have
   *     \f[
   *        \frac{x^i}{(i+c_1)^{m_1}} \frac{y^i}{(i+c_2)^{m_2}} 
   *           = \frac{x^i}{(i+c_1)^{m_1-1}} \frac{y^i}{(i+c_2)^{m_2+1}}
   *            + (c_2-c_1) \frac{x^i}{(i+c_1)^{m_1}} \frac{y^i}{(i+c_2)^{m_2+1}} 
   *     \f]
   *
   *     Finally, if both degrees are negative, we have
   *     \f[
   *        \frac{x^i}{(i+c_1)^{m_1}} \frac{y^i}{(i+c_2)^{m_2}} 
   *           = \frac{x^i}{(i+c_1)^{m_1-1}} \frac{y^i}{(i+c_2)^{m_2+1}}
   *            + (c_2-c_1) \frac{x^i}{(i+c_1)^{m_1}} \frac{y^i}{(i+c_2)^{m_2+1}} 
   *     \f]
   *     To avoid an infinite recursion in the last case, the algorithm does not
   *     commute two basic_letters.
   *
   *  The multiplication does not alter the offset, e.g. if we have 
   *  \f$i+c_1 > 0\f$ and \f$i+c_2 > 0\f$
   *  for all \f$i\f$, then the evaluated product of the two basic_letters has only the offsets
   *  \f$c_1\f$ or \f$c_2\f$. Multiplying two basic_letters does not introduce poles.
   *
   *  The result gets the index from the first letter, if this one differs from _default_index,
   *  otherwise the result gets the index from the second letter.
   *
   *  The routine returns unevaluated if
   *
   *  - the offsets are not equal and at least one degree is not an integer.
   *
   */
  ex basic_letter::concat_speedy(const ex & l) const
  {
    const basic_letter& bl = ex_to<basic_letter>(l);

    // the indicies are the same or equal to the default one
    ex new_index;
    if ( index.is_equal(_default_index) ) 
      {
	new_index = bl.index;
      }
    else
      {
	new_index = index;
      }

    // same offset, multiply the letters and add the degrees
    if (offset.is_equal(bl.offset)) return create_basic_letter(scale*(bl.scale),degree+(bl.degree),offset,new_index);

    // trivial cases, one degree == 0
    if (degree.is_zero()) return create_basic_letter(scale*(bl.scale),bl.degree,bl.offset,new_index);

    if ( (bl.degree).is_zero()) return create_basic_letter(scale*(bl.scale),degree,offset,new_index);

    // both degrees positive, use partial fractioning
    if ( degree.info(info_flags::posint) && (bl.degree.info(info_flags::posint)) )
      {
	// closed form for partial fractioning
	int m1 = ex_to<numeric>(degree).to_int();
	int m2 = ex_to<numeric>(bl.degree).to_int();

	ex c1 = offset;
	ex c2 = bl.offset;

	ex res = 0 ;

	for (int k=1;k<=m1;k++) 
	  res += binomial(m1+m2-k-1,m2-1)*GiNaC::pow(-1,m1-k)*GiNaC::pow(c2-c1,-m1-m2+k)
	    *create_basic_letter(scale*(bl.scale),k,c1,new_index);

	for (int k=1;k<=m2;k++) 
	  res += binomial(m1+m2-k-1,m1-1)*GiNaC::pow(-1,m1)*GiNaC::pow(c2-c1,-m1-m2+k)
	    *create_basic_letter(scale*(bl.scale),k,c2,new_index);

	return res;
      }

    // one degree positive, the other negative
    if ( degree.info(info_flags::negint) && (bl.degree.info(info_flags::posint)) )
      {
	// closed form for partial fractioning
	int m1 = -ex_to<numeric>(degree).to_int();
	int m2 = ex_to<numeric>(bl.degree).to_int();

	ex c1 = offset;
	ex c2 = bl.offset;

	ex res = 0 ;

	for (int k=0;k<=m1;k++) 
	  res += binomial(m1,k)*pow(c1-c2,m1-k)
	    *create_basic_letter(scale*(bl.scale),m2-k,c2,new_index);

	return res;
      }

    if ( degree.info(info_flags::posint) && (bl.degree.info(info_flags::negint)) )
      {
	// closed form for partial fractioning
	int m1 = ex_to<numeric>(degree).to_int();
	int m2 = -ex_to<numeric>(bl.degree).to_int();

	ex c1 = offset;
	ex c2 = bl.offset;

	ex res = 0 ;

	for (int k=0;k<=m2;k++) 
	  res += binomial(m2,k)*pow(c2-c1,m2-k)
	    *create_basic_letter(scale*(bl.scale),m1-k,c1,new_index);

	return res;
      }

    // both negative
    if ( degree.info(info_flags::negint) && (bl.degree.info(info_flags::negint)) )
      {
	// closed form for partial fractioning
	int m1 = ex_to<numeric>(degree).to_int();
	int m2 = -ex_to<numeric>(bl.degree).to_int();

	ex c1 = offset;
	ex c2 = bl.offset;

	ex res = 0 ;

	for (int k=0;k<=m2;k++) 
	  res += binomial(m2,k)*pow(c2-c1,m2-k)
	    *create_basic_letter(scale*(bl.scale),m1-k,c1,new_index);

	return res;
      }

    // default
    return (*this) * l;

  }

  /**
   *
   * Explicit evaluation.
   *
   */
  ex basic_letter::eval_explicit() const
  {
    return pow(scale,index) * pow(index+offset, -degree);
  }

  // non-virual functions

  /**
   *
   * Sets the index to \f$i\f$
   *
   */
  ex basic_letter::set_index(const ex & i) const
  {
    return create_basic_letter(scale,degree,offset,i);
  }

  /**
   *
   * Sets the index to the default index.
   *
   */
  ex basic_letter::forget_index(void) const
  {
    return create_basic_letter(scale,degree,offset,_default_index);
  }


  /**
   *
   * Returns
   * \f[
   *    \frac{x}{(1+c)^m}
   * \f]
   *
   */
  ex basic_letter::index_eq_one(void) const
  {
    return this->set_index(1);
  }


  /**
   *
   * Adjusts the index according to
   * \f[
   *     \frac{x^j}{(j+c)^m} = x^{j-i} \frac{x^i}{(i+c+(j-i))^m}
   * \f]
   *
   */
  ex basic_letter::shift_index(const ex & new_index) const
  {
    ex c_offset = index - new_index;

    return pow(scale,c_offset) 
     * create_basic_letter(scale,degree,offset+c_offset,new_index);
  }

  /**
   *
   * Returns a basic_letter with offset+1
   *
   */
  ex basic_letter::shift_plus_one(void) const
  {
    return create_basic_letter(scale,degree,offset+1,index);
  }

  /**
   *
   * Returns a basic_letter with offset-1
   *
   */
  ex basic_letter::shift_minus_one(void) const
  {
    return create_basic_letter(scale,degree,offset-1,index);
  }

  /**
   *
   * Returns a basic_letter with degree-1
   *
   */
  ex basic_letter::degree_minus_one(void) const
  {
    return create_basic_letter(scale,degree-1,offset,index);
  }

  /**
   *
   * Returns a basic_letter with degree+1
   *
   */
  ex basic_letter::degree_plus_one(void) const
  {
    return create_basic_letter(scale,degree+1,offset,index);
  }

  ex basic_letter::expand_members(int level) const
  {
    // use normal instead of expand for scale
    return create_basic_letter(scale.normal(),
                               nestedsums_helper_expand(degree,level),
                               nestedsums_helper_expand(offset,level),
                               nestedsums_helper_expand(index,level)
			       );
  }

  /**
   *
   * Concat two letters.
   *
   */
 GiNaC::ex concat(const basic_letter & l1, const basic_letter & l2)
 {
   return l1.concat(l2);
 }

} // namespace nestedsums

