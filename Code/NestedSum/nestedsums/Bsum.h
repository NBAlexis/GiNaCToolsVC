
/** @file Bsum.h
 *
 * Interface to Bsums 
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

#ifndef __NESTEDSUMS_Bsum_H__
#define __NESTEDSUMS_Bsum_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// Bsums arise from Hoelder convolutions.
  /**
   *
   * A Bsum is defined by
   *  \f[
   *       \sum\limits_{i_1=n+1}^N
   *       \sum\limits_{i_2=i_1+1}^N ...
   *       \sum\limits_{i_k=i_{k-1}+1}^N
   *        \frac{x_1^{i_1}}{i_1^{m_1}}
   *        \frac{x_2^{i_2}}{i_2^{m_2}} ...
   *        \frac{x_k^{i_k}}{i_k^{m_k}}
   *  \f]
   * This is equivalent to
   * \f[
   *     \left( x_k^+ \right)^{m_k} \left( x_{k-1}^+ \right)^{m_{k-1}} ... 
   *     \left( x_1^+ \right)^{m_1} 
   *     \frac{x_k}{1-x_k} \frac{x_{k-1}x_k}{1-x_{k-1}x_k} ...
   *     \frac{x_1 ... x_k}{1-x_1 ... x_k}
   *     \left( x_1 ... x_k \right)^n 
   *  \f]
   * up to terms of the form
   * \f[
   * \left( x^+ \right)^m \frac{x}{1-x} x^N = \sum\limits_{i=N+1}^\infty \frac{x^i}{i^m}
   * \f]
   *
   */
  class NESTEDSUMS_API Bsum : public GiNaC::basic
    {

      GINAC_DECLARE_REGISTERED_CLASS(Bsum, GiNaC::basic)

	// ctors
    public:
      Bsum(const GiNaC::ex & nc, const GiNaC::ex & llc);

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
    public :
      virtual GiNaC::ex convert_to_Ssum_exvector(const GiNaC::exvector & Z1) const;

      virtual GiNaC::ex expand_members(int level = 0) const;

      // non-virtual functions
    public :
      GiNaC::ex get_index(void) const;
      GiNaC::ex get_letter_list(void) const;
      size_t get_depth(void) const;

    protected:

      // friends :
        NESTEDSUMS_API friend GiNaC::ex convert_Bsum_to_Ssum(const GiNaC::ex & C);
        NESTEDSUMS_API friend GiNaC::ex convert_Bsum_to_Zsum(const GiNaC::ex & C);

	// member variables :

    protected:

      GiNaC::ex n;
      GiNaC::ex letter_list;
    };

GINAC_DECLARE_UNARCHIVER(Bsum);

  // inline functions

  /**
   *
   * Returns the upper summation limit.
   *
   */
inline GiNaC::ex Bsum::get_index(void) const
  {
    return n;
  }

  /**
   *
   * Returns the letter_list.
   *
   */
inline GiNaC::ex Bsum::get_letter_list(void) const
  {
    return letter_list;
  }

  /**
   *
   * Returns the depth.
   *
   */
inline size_t Bsum::get_depth(void) const
  {
    return letter_list.nops();
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_Bsum(const GiNaC::ex & nc, const GiNaC::ex & llc)
  {
    return (new Bsum(nc,llc))->setflag(GiNaC::status_flags::dynallocated);
  }

NESTEDSUMS_API GiNaC::ex create_Bsum_from_exvector(const GiNaC::ex & nc, const GiNaC::exvector & v);

NESTEDSUMS_API GiNaC::ex convert_Bsum_to_Ssum(const GiNaC::ex & C);
NESTEDSUMS_API GiNaC::ex convert_Bsum_to_Zsum(const GiNaC::ex & C);

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_Bsum_H__
