
/** @file hash_entry.cc
 *
 * Implementation of hash_entrys 
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

GINAC_IMPLEMENT_REGISTERED_CLASS(hash_entry, basic)

GINAC_BIND_UNARCHIVER(hash_entry);



  hash_entry::hash_entry() : inherited(),
   compare_data(_default), replace_data(_default), return_data(_default), rtti_key(0)
  { 
  }

  void hash_entry::archive(archive_node &node) const
  {
    inherited::archive(node);
    node.add_ex("compare_data",compare_data);
    node.add_ex("replace_data",replace_data);
    node.add_ex("return_data",return_data);

    node.add_unsigned("rtti_key",rtti_key);
  }

  void hash_entry::read_archive(const archive_node &node, lst &sym_lst)
  {
    inherited::read_archive(node, sym_lst);

    node.find_ex("compare_data",compare_data,sym_lst);
    node.find_ex("replace_data",replace_data,sym_lst);
    node.find_ex("return_data",return_data,sym_lst);

    node.find_unsigned("rtti_key",rtti_key);
  }

  int hash_entry::compare_same_type(const basic &other) const
  {
    const hash_entry &o = static_cast<const hash_entry &>(other);
    int cmpval;

    if ( rtti_key != o.rtti_key )
      {
	return (rtti_key > o.rtti_key) ? 1 : -1;
      } 

    cmpval = compare_data.compare(o.compare_data);
    if ( cmpval) return cmpval;

    cmpval = replace_data.compare(o.replace_data);
    if ( cmpval) return cmpval;

    return return_data.compare(o.return_data);
  }

  // other ctors
  hash_entry::hash_entry(const ex & cd, const ex & sd, const ex & rd, unsigned rkey) : inherited(), 
    compare_data(cd), replace_data(sd), return_data(rd), rtti_key(rkey)
  { }

  // functions overriding virtual functions from bases classes

  unsigned hash_entry::calchash(void) const
    {
      unsigned v = make_hash_seed(typeid(*this));

      v = rotate_left_31(v);
      v ^= rtti_key;

      v = rotate_left_31(v);
      v ^= compare_data.gethash();

      v = rotate_left_31(v);
      v ^= replace_data.gethash();

      v = rotate_left_31(v);
      v ^= return_data.gethash();

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

  void hash_entry::print(const print_context & c, unsigned level) const
  {
    if (is_a<print_latex>(c)) 
      {
	if (precedence() <= level) c.s << "{(";
	c.s << "hash entry" ;
	if (precedence() <= level) c.s << ")}";
      }
    else if (is_a<print_tree>(c)) 
      {
	c.s << std::string(level, ' ') << class_name()
	    << std::hex << ", hash=0x" << hashvalue << ", flags=0x" << flags << std::dec
	    << ", nops=" << nops()
	    << std::hex << ", rtti_key=0x" << rtti_key
	    << std::endl;
	compare_data.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	replace_data.print(c, level + static_cast<const print_tree &>(c).delta_indent);
	return_data.print(c, level + static_cast<const print_tree &>(c).delta_indent);
      }
    else
      {
	if (precedence() <= level) c.s << "(";
	c.s << "hash entry" ;
	if (precedence() <= level) c.s << ")";
      }
  }

  /**
   *
   * No automatic simplifications
   *
   */
  ex hash_entry::eval() const
  {
    return this->hold();
  }

  /**
   *
   * No automatic simplifications
   *
   */
  ex hash_entry::eval_ncmul(const exvector & v) const
  {
    // default
    return hold_ncmul(v);
  }

  ex hash_entry::derivative(const symbol & s) const
  {
    return 0;
  }

  ex hash_entry::subs(const exmap & m, unsigned options) const
  {
    exmap::const_iterator it = m.find(*this);
    if (it != m.end())
        return it->second;

    return create_hash_entry(compare_data.subs(m,options),replace_data.subs(m,options),return_data.subs(m,options),rtti_key);
  }

  // new non-virtual functions

  /**
   *
   * The method return_value(obj_data) takes the subst_data from the object looked up and
   * substitutes it into the return_data.
   * The way substitutions are performed depends on the rtti_key.
   *
   * If the rtti_key is zero, it is assumed that no substitutions are necesarry and the
   * return_data is returned directly.
   *
   * If the rtti_key is one, the obj_data is substituted for the replace_data.
   *
   * The default is to return the return_data directly.
   *
   */
  ex hash_entry::return_value(const ex & obj_data) const
  {
    if ( rtti_key == 0 ) return return_data;

    if ( rtti_key == 1 ) return return_data.subs( ex_to<lst>(replace_data), ex_to<lst>(obj_data) );

    // default
    return return_data;
  }

  /**
   *
   * Returns the member compare_data.
   *
   */
  ex hash_entry::hash_data(void) const
  {
    return compare_data;
  }

  /**
   *
   * Returns the member replace_data.
   *
   */
  ex hash_entry::subst_data(void) const
  {
    return replace_data;
  }

} // namespace nestedsums

