
/** @file classical_polylog.h
 *
 * Interface to classical polylogarithms 
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

#ifndef __NESTEDSUMS_CLASSICAL_POLYLOG_H__
#define __NESTEDSUMS_CLASSICAL_POLYLOG_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// A classical polylog is a special case of a Nielsen polylog.
  /**
   *
   *  Classical polylogs are defined by
   *  \f[
   *     \mbox{Li}_{n}(x) = \mbox{S}_{n-1,1}(x) 
   *  \f]
   *
   */
  class NESTEDSUMS_API classical_polylog : public nielsen_polylog
    {
      GINAC_DECLARE_REGISTERED_CLASS(classical_polylog, nielsen_polylog)

	// ctors
    public:
      explicit classical_polylog(const GiNaC::ex & llc);

	// functions overriding virtual functions from bases classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      GiNaC::ex eval() const override;
    };

GINAC_DECLARE_UNARCHIVER(classical_polylog);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_classical_polylog(const GiNaC::ex & llc)
  {
    return (new classical_polylog(llc))->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

namespace GiNaC {

  // template specialization
template<> inline const nestedsums::classical_polylog &ex_to<nestedsums::classical_polylog>(const ex &e)
  {
    return dynamic_cast<const nestedsums::classical_polylog &>(*e.bp);
  }

} // end namespace GiNaC

#endif // ndef __NESTEDSUMS_CLASSICAL_POLYLOG_H__
