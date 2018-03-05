
/** @file nielsen_polylog.h
 *
 * Interface to Nielsen's generalized polylogarithms 
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

#ifndef __NESTEDSUMS_NIELSEN_POLYLOG_H__
#define __NESTEDSUMS_NIELSEN_POLYLOG_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// A Nielsen polylog is a special case of a harmonic polylog.
  /**
   *
   *  Nielsen polylogs are defined by
   *  \f[
   *     \mbox{S}_{n,p}(x) = \mbox{H}_{n+1,1,...,1}(x) 
   *  \f]
   *  where (p-1) one's occur in the index field.
   *
   *  There are two "print" formats available. The default option prints
   *  Nielsen polylogarithms as \f$\mbox{S}_{n,p}(x)\f$.
   *  
   *  If the flag "print_format::no_nielsen_polylog" in the variable "_print_format" is set,
   *  Nielsen polylogarithms are printed as multiple polylogarithms, 
   *  e.g. in the \f$\mbox{Li}\f$ - notation.
   *
   */
  class NESTEDSUMS_API nielsen_polylog : public harmonic_polylog
    {
      GINAC_DECLARE_REGISTERED_CLASS(nielsen_polylog, harmonic_polylog)

	// ctors
    public:
      explicit nielsen_polylog(const GiNaC::ex & llc);

	// functions overriding virtual functions from bases classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      GiNaC::ex eval() const override;
    };

GINAC_DECLARE_UNARCHIVER(nielsen_polylog);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_nielsen_polylog(const GiNaC::ex & llc)
  {
    return (new nielsen_polylog(llc))->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

namespace GiNaC {

  // template specialization
template<> inline const nestedsums::nielsen_polylog &ex_to<nestedsums::nielsen_polylog>(const ex &e)
  {
    return dynamic_cast<const nestedsums::nielsen_polylog &>(*e.bp);
  }

} // end namespace GiNaC

#endif // ndef __NESTEDSUMS_NIELSEN_POLYLOG_H__
