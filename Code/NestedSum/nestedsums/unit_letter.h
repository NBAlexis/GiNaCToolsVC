
/** @file unit_letter.h
 *
 * Interface to unit_letter
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

#ifndef __NESTEDSUMS_UNIT_LETTER_H__
#define __NESTEDSUMS_UNIT_LETTER_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// A unit_letter is a letter whose letter content equals 1.
  /**
   *
   *  The model for a unit_letter is
   *  \f[
   *      \frac{1}{i^n}
   *  \f]
   *  Here \f$n\f$ is the degree 
   *  and \f$i\f$ the summation index.
   *
   */
  class NESTEDSUMS_API unit_letter : public letter
    {
      GINAC_DECLARE_REGISTERED_CLASS(unit_letter, letter)

	// ctors
    public:
      explicit unit_letter(const GiNaC::ex & d);
      unit_letter(const GiNaC::ex & d, const GiNaC::ex & i);

	// functions overriding virtual functions from base classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      GiNaC::ex eval() const override;

      GiNaC::ex concat_speedy(const GiNaC::ex & l) const override;
    };

GINAC_DECLARE_UNARCHIVER(unit_letter);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_unit_letter(const GiNaC::ex & d)
  {
    return (new unit_letter(d))->setflag(GiNaC::status_flags::dynallocated);
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_unit_letter(const GiNaC::ex & d, const GiNaC::ex & i)
  {
    return (new unit_letter(d,i))->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_UNIT_LETTER_H__
