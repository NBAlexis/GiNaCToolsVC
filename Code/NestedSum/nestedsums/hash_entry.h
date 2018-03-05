
/** @file hash_entry.h
 *
 * Interface to hash_entries 
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

#ifndef __NESTEDSUMS_hash_entry_H__
#define __NESTEDSUMS_hash_entry_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// This class provides a container for expressions to be stored in hash tables. 
  /**
   *
   * The class hash_entry is designed to be stored as the second entry in a hash map.
   * The map would be of type
   *  map<unsigned, ex>
   * and the ex would always refer to an object of type hash_entry.
   *
   * The class hash_entry has four data members: compare_data, replace_data, return_data and rtti_key.
   *
   * The member compare_data can be accessed via the method hash_data(void) and is used
   * to verify exactly if the entry stored in the map is equivalent to the object
   * which is being looked up.
   * "Is equivalent" can mean "is exactly identical" or "is identical up to simple substitutions".
   * 
   * The member replace_data specifies the components of the return_data which have to be
   * substituted.
   *
   * The method return_value(obj_data) takes the subst_data from the object looked up and
   * substitutes it into the return_data.
   * If the rtti_key is zero, it is assumed that no substitutions are necesarry and the
   * return_data is returned directly.
   *
   * Classes which are supposed to be stored in the hash table, have to provide four methods:
   *  unsigned get_key(void)
   *  ex hash_data(void)
   *  ex subst_data(void)
   *  ex get_template(void)
   *
   * get_key is the key for the first entry in the hash map. If the key is found in the
   * hash map, hash_data is used to verify if the entry is equivalent to the class being
   * looked up.
   * subst_data() provides the part which has to specialized.
   * If substitutions are required, get_template() returns the "raw" form for the specific
   * instance of a class.
   *
   */
  class NESTEDSUMS_API hash_entry : public GiNaC::basic
    {
      GINAC_DECLARE_REGISTERED_CLASS(hash_entry, GiNaC::basic)

	// ctors
    public:
      hash_entry(const GiNaC::ex & cd, const GiNaC::ex & sd, const GiNaC::ex & rd, unsigned rkey);

	// functions overriding virtual functions from bases classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      unsigned return_type(void) const override { return GiNaC::return_types::noncommutative; }

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      unsigned precedence(void) const override {return 60;}
      GiNaC::ex eval() const override;
      GiNaC::ex subs(const GiNaC::exmap & m, unsigned options = 0) const override;

    protected:
      GiNaC::ex eval_ncmul(const GiNaC::exvector & v) const override;
      GiNaC::ex derivative(const GiNaC::symbol & s) const override;
      unsigned calchash(void) const override;

	// new virtual functions which can be overridden by derived classes

        // non-virtual functions
    public :
      GiNaC::ex return_value(const GiNaC::ex & obj_data) const;
      GiNaC::ex hash_data(void) const;
      GiNaC::ex subst_data(void) const;

    protected:

	// member variables :

    protected:

      GiNaC::ex compare_data;
      GiNaC::ex replace_data;
      GiNaC::ex return_data;
      unsigned rtti_key;
    };

GINAC_DECLARE_UNARCHIVER(hash_entry);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_hash_entry(const GiNaC::ex & cd, const GiNaC::ex & sd, const GiNaC::ex & rd, unsigned rkey)
  {
    return (new hash_entry(cd,sd,rd,rkey))->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_hash_entry_H__
