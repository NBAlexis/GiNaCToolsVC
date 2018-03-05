
/** @file multiple_zeta_value.h
 *
 * Interface to multiple zeta values
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

#ifndef __NESTEDSUMS_MULTIPLE_ZETA_VALUE_H__
#define __NESTEDSUMS_MULTIPLE_ZETA_VALUE_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// A multiple zeta value can be viewed as a special case of a multiple polylog 
  /// or as a special case of an Euler-Zagier sum.
  /**
   *
   *  Multiple zeta values are defined by
   *  \f[
   *     \zeta_{m_k,...,m_1} = Z(\infty;m_1,...,m_k;1,...,1) 
   *  \f]
   *
   *  There are two "print" formats available. The default option prints
   *  multiple zeta values with reversed order of the arguments, as in the definition
   *  above. 
   *
   *  If the flag "print_format::no_reversed_order" in the variable "_print_format" is set,
   *  multiple zeta values are printed without reversing the order of the arguments, e.g.
   *  \f[
   *     Z(\infty;m_1,...,m_k;1,...,1) = \zeta_{m_1,...,m_k}
   *  \f]
   *  This notation is used in the french literature.
   *
   */
  class NESTEDSUMS_API multiple_zeta_value : public multiple_polylog, public Euler_Zagier_sum
    {
      GINAC_DECLARE_REGISTERED_CLASS(multiple_zeta_value, multiple_polylog)

	// ctors
    public:
      explicit multiple_zeta_value(const GiNaC::ex & llc);

	// functions overriding virtual functions from bases classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      GiNaC::return_type_t return_type_tinfo() const override;

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      GiNaC::ex eval() const override;

    };

GINAC_DECLARE_UNARCHIVER(multiple_zeta_value);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_multiple_zeta_value(const GiNaC::ex & llc)
  {
    return (new multiple_zeta_value(llc))->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

namespace GiNaC {

  // template specialization
template<> inline const nestedsums::multiple_zeta_value &ex_to<nestedsums::multiple_zeta_value>(const ex &e)
  {
    return dynamic_cast<const nestedsums::multiple_zeta_value &>(*e.bp);
  }

} // end namespace GiNaC

#endif // ndef __NESTEDSUMS_MULTIPLE_ZETA_VALUE_H__
