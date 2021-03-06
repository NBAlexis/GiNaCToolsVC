
/** @file Ssum_to_Infinity.h
 *
 * Interface to Ssums to Infinity
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

#ifndef __NESTEDSUMS_SSUM_TO_INFINITY_H__
#define __NESTEDSUMS_SSUM_TO_INFINITY_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// A Ssum_to_Infinity is a special case of a Ssum.
  /** 
   *
   *  A Ssum to Infinity is defined by
   *  \f[
   *     S(\infty;m_1,...,m_k;x_1,...,x_k) 
   *  \f]
   *
   */
  class NESTEDSUMS_API Ssum_to_Infinity : public virtual Ssum
    {
      GINAC_DECLARE_REGISTERED_CLASS(Ssum_to_Infinity, Ssum)

	// ctors
    public:
      explicit Ssum_to_Infinity(const GiNaC::ex & llc);

	// functions overriding virtual functions from bases classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      GiNaC::ex eval() const override;

    };

GINAC_DECLARE_UNARCHIVER(Ssum_to_Infinity);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_Ssum_to_Infinity(const GiNaC::ex & llc)
  {
    return (new Ssum_to_Infinity(llc))->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

namespace GiNaC {

  // template specialization
template<> inline const nestedsums::Ssum_to_Infinity &ex_to<nestedsums::Ssum_to_Infinity>(const ex &e)
  {
    return dynamic_cast<const nestedsums::Ssum_to_Infinity &>(*e.bp);
  }

} // end namespace GiNaC

#endif // ndef __NESTEDSUMS_SSUM_TO_INFINITY_H__
