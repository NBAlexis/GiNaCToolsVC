
/** @file letter.h
 *
 * Interface to letter
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

#ifndef __NESTEDSUMS_LETTER_H__
#define __NESTEDSUMS_LETTER_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// A letter is a basic_letter with offset=0.
  /**
   *
   *  The model for a letter is
   *  \f[
   *      \frac{x^i}{i^n}
   *  \f]
   *  Here \f$x\f$ is the scale, \f$n\f$ is the degree 
   *  and \f$i\f$ the index.
   *
   */
  class NESTEDSUMS_API letter : public basic_letter
    {

      GINAC_DECLARE_REGISTERED_CLASS(letter, basic_letter)

	// ctors
    public:
      letter(const GiNaC::ex & l, const GiNaC::ex & d);
      letter(const GiNaC::ex & l, const GiNaC::ex & d, const GiNaC::ex & i);

	// functions overriding virtual functions from base classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      GiNaC::return_type_t return_type_tinfo() const override;

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      GiNaC::ex eval() const override;

      GiNaC::ex concat_speedy(const GiNaC::ex & l) const override;
    };

GINAC_DECLARE_UNARCHIVER(letter);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_letter(const GiNaC::ex & l, const GiNaC::ex & d)
  {
    return (new letter(l,d))->setflag(GiNaC::status_flags::dynallocated);
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_letter(const GiNaC::ex & l, const GiNaC::ex & d, const GiNaC::ex & i)
  {
    return (new letter(l,d,i))->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_LETTER_H__
