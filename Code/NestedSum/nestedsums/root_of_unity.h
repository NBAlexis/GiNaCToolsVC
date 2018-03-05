
/** @file root_of_unity.h
 *
 * Interface to root_of_unity
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

#ifndef __NESTEDSUMS_ROOT_OF_UNITY_H__
#define __NESTEDSUMS_ROOT_OF_UNITY_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /**
   *
   * A root of unity is defined by
   * \f[
   *    r_k^l = \exp \left( \frac{2 \pi i l}{k} \right)
   * \f]
   *
   */
  class NESTEDSUMS_API root_of_unity : public GiNaC::basic
    {
      GINAC_DECLARE_REGISTERED_CLASS(root_of_unity, GiNaC::basic)

	// ctors
    public:
      root_of_unity(unsigned l, unsigned k);

	// functions overriding virtual functions from base classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      unsigned return_type(void) const override { return GiNaC::return_types::noncommutative; }

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      unsigned precedence(void) const override {return 50;}
      GiNaC::ex eval() const override;
      GiNaC::ex subs(const GiNaC::exmap & m, unsigned options = 0) const override;

    protected:
      GiNaC::ex eval_ncmul(const GiNaC::exvector & v) const override;
      GiNaC::ex derivative(const GiNaC::symbol & s) const override;
      unsigned calchash(void) const override;

	// new virtual functions which can be overridden by derived classes

	// non-virtual functions 

        // friends :

	// member variables :

    protected:

      unsigned l;
      unsigned k;
    };

GINAC_DECLARE_UNARCHIVER(root_of_unity);

  // utility functions

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_root_of_unity(unsigned l ,unsigned k)
  {
    return (new root_of_unity(l,k))->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_ROOT_OF_UNITY_H__
