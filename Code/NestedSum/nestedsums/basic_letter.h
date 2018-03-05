
/** @file basic_letter.h
 *
 * Interface to basic_letter
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

#ifndef __NESTEDSUMS_BASIC_LETTER_H__
#define __NESTEDSUMS_BASIC_LETTER_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// A basic_letter is an element of an alphabet.
  /**
   *
   *  The model for a basic_letter is
   *  \f[
   *     \frac{x^i}{(i+c)^m}
   *  \f]
   *  Here \f$x\f$ is the scale, \f$m\f$ the degree,
   *  \f$c\f$ the offset and \f$i\f$ a parameter (usually a summation index).
   *  \f$i\f$ does not need to be specified. In this case the index is set
   *  to the default index.
   *
   *  Two basic_letters can be multiplied ("concatenated") to form 
   *  a new basic_letter.
   *
   */
  class NESTEDSUMS_API basic_letter : public GiNaC::basic
    {
      GINAC_DECLARE_REGISTERED_CLASS(basic_letter, GiNaC::basic)

	// ctors
    public:
      basic_letter(const GiNaC::ex & l, const GiNaC::ex & d, const GiNaC::ex & o);
      basic_letter(const GiNaC::ex & l, const GiNaC::ex & d, const GiNaC::ex & o, const GiNaC::ex & i);

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
    public:
      virtual GiNaC::ex concat(const GiNaC::ex & l) const;
      virtual GiNaC::ex eval_explicit() const;
      virtual GiNaC::ex expand_members(int level = 0) const;

    protected:
      virtual GiNaC::ex concat_speedy(const GiNaC::ex & l) const;

	// non-virtual functions 
    public:
       GiNaC::ex get_scale(void) const;
       GiNaC::ex get_degree(void) const;
       GiNaC::ex get_offset(void) const;
       GiNaC::ex get_index(void) const;

       GiNaC::ex set_index(const GiNaC::ex & i) const;
       GiNaC::ex forget_index(void) const;
       GiNaC::ex shift_index(const GiNaC::ex & new_index) const;
       GiNaC::ex index_eq_one(void) const;

       GiNaC::ex shift_plus_one(void) const;
       GiNaC::ex shift_minus_one(void) const;
       GiNaC::ex degree_minus_one(void) const;
       GiNaC::ex degree_plus_one(void) const;

    protected:

        // friends :
        NESTEDSUMS_API friend GiNaC::ex concat(const basic_letter & l1, const basic_letter & l2);

	// member variables :

    protected:

      GiNaC::ex scale;
      GiNaC::ex degree;
      GiNaC::ex offset;
      GiNaC::ex index;
    };

GINAC_DECLARE_UNARCHIVER(basic_letter);

  // inline functions

  /**
   *
   * Returns the scale
   *
   */
inline GiNaC::ex basic_letter::get_scale(void) const
  {
    return scale;
  }

  /**
   *
   * Returns the degree
   *
   */
inline GiNaC::ex basic_letter::get_degree(void) const
  {
    return degree;
  }

  /**
   *
   * Returns the offset
   *
   */
inline GiNaC::ex basic_letter::get_offset(void) const
  {
    return offset;
  }

  /**
   *
   * Returns the index
   *
   */
inline GiNaC::ex basic_letter::get_index(void) const
  {
    return index;
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_basic_letter(const GiNaC::ex & l, const GiNaC::ex & d, const GiNaC::ex & o)
  {
    return (new basic_letter(l,d,o))->setflag(GiNaC::status_flags::dynallocated);
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_basic_letter(const GiNaC::ex & l, const GiNaC::ex & d, const GiNaC::ex & o, const GiNaC::ex & i)
  {
    return (new basic_letter(l,d,o,i))->setflag(GiNaC::status_flags::dynallocated);
  }

 GiNaC::ex concat(const basic_letter & l1, const basic_letter & l2);

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_BASIC_LETTER_H__
