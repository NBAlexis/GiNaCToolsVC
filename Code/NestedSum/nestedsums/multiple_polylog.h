
/** @file multiple_polylog.h
 *
 * Interface to multiple polylog sums 
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

#ifndef __NESTEDSUMS_MULTIPLE_POLYLOG_H__
#define __NESTEDSUMS_MULTIPLE_POLYLOG_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// A multiple polylog sum is a special case of a Zsum.
  /**
   *
   *  Multiple polylogs are in the notation of Goncharov defined by
   *  \f[
   *     \mbox{Li}_{m_k,...,m_1}(x_k,...,x_1) = Z(\infty;m_1,...,m_k;x_1,...,x_k) 
   *  \f]
   *
   *  There are two "print" formats available. The default option prints
   *  multiple polylogarithms with reversed order of the arguments, as in the definition
   *  above. This notation is for example used by Goncharov.
   *
   *  If the flag "print_format::no_reversed_order" in the variable "_print_format" is set,
   *  multiple polylogarithms are printed without reversing the order of the arguments, e.g.
   *  \f[
   *     Z(\infty;m_1,...,m_k;x_1,...,x_k) = \mbox{Li}_{m_1,...,m_k}(x_1,...,x_k)  
   *  \f]
   *  This notation is used in the french literature.
   *
   */
  class NESTEDSUMS_API multiple_polylog : public virtual Zsum
    {
      GINAC_DECLARE_REGISTERED_CLASS(multiple_polylog, Zsum)

	// ctors
    public:
      explicit multiple_polylog(const GiNaC::ex & llc);

	// functions overriding virtual functions from bases classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      GiNaC::ex eval() const override;

      // new virtual functions
    public:
      virtual GiNaC::ex eval_approx() const;
    };

GINAC_DECLARE_UNARCHIVER(multiple_polylog);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_multiple_polylog(const GiNaC::ex & llc)
  {
    return (new multiple_polylog(llc))->setflag(GiNaC::status_flags::dynallocated);
  }

 GiNaC::ex eval_multiple_polylog_approx(const GiNaC::ex & expr);

} // namespace nestedsums

namespace GiNaC {

  // template specialization
template<> inline const nestedsums::multiple_polylog &ex_to<nestedsums::multiple_polylog>(const ex &e)
  {
    return dynamic_cast<const nestedsums::multiple_polylog &>(*e.bp);
  }

} // end namespace GiNaC

#endif // ndef __NESTEDSUMS_MULTIPLE_POLYLOG_H__
