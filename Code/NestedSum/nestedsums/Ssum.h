
/** @file Ssum.h
 *
 * Interface to Ssums 
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

#ifndef __NESTEDSUMS_SSUM_H__
#define __NESTEDSUMS_SSUM_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// Ssums form an algebra.
  /**
   *
   *  A Ssum is recursively defined by
   *  \f[
   *     S(n;m_1,...,m_k;x_1,...,x_k) = \sum\limits_{i=1}^n \frac{x_1^i}{i^{m_1}} S(i;m_2,...,m_k;x_2,...,x_k)
   *  \f]
   *  with 
   *  \f[
   *     S(n) = 1
   *  \f]
   *  for \f$ n > 0 \f$ and
   *  \f[
   *     S(n) = 0
   *  \f]
   * for \f$ n \le 0 \f$.
   *
   *  Ssums can be converted to Zsums (and vice versa).
   *
   *  All letters should have their index set to _default_index.
   *
   */
  class NESTEDSUMS_API Ssum : public GiNaC::basic
    {
      // Csum accesses the methods
      //   multiply_last_letter
      //   increases_las_letter
      //   append_letter
      friend class NESTEDSUMS_API Csum;

      GINAC_DECLARE_REGISTERED_CLASS(Ssum, GiNaC::basic)

	// ctors
    public:
      explicit Ssum(const GiNaC::ex & nc);
      Ssum(const GiNaC::ex & nc, const GiNaC::ex & llc);

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
      virtual GiNaC::ex convert_to_Zsum_exvector(const GiNaC::exvector & Z0, const GiNaC::exvector & Z1) const;
      virtual GiNaC::ex shuffle_exvector(const GiNaC::exvector & Z0, const GiNaC::exvector & Z1, const GiNaC::exvector & Z2) const;

      virtual GiNaC::ex refine_exvector(unsigned q, const GiNaC::exvector & Z0, const GiNaC::exvector & Z1) const;
      virtual GiNaC::ex refine(unsigned q) const;

      virtual GiNaC::ex set_index(const GiNaC::ex & i) const;
      virtual GiNaC::ex shift_plus_one(void) const;
      virtual GiNaC::ex shift_minus_one(void) const;
      virtual GiNaC::ex adjust_upper_limit_downwards(const GiNaC::ex & i) const;
      virtual GiNaC::ex adjust_upper_limit_upwards(const GiNaC::ex & i) const;
      virtual GiNaC::ex adjust_upper_limit_plus_one(void) const;
      virtual GiNaC::ex index_eq_one(void) const;

      virtual GiNaC::ex get_head(int k) const;
      virtual GiNaC::ex get_tail(int k) const;
      virtual int flag_remove_negative_degrees(void) const;
      virtual GiNaC::ex remove_negative_degrees(void) const;

      virtual GiNaC::ex expand_members(int level = 0) const;
      virtual GiNaC::ex eval_explicit() const;

      virtual GiNaC::ex get_first_letter(void) const;
      virtual GiNaC::ex remove_first_letter(void) const;
      virtual GiNaC::ex remove_first_letter(const GiNaC::ex & nc) const;
      virtual GiNaC::ex prepend_letter(const GiNaC::ex & lc) const;
      virtual GiNaC::ex prepend_letter(const GiNaC::ex & nc, const GiNaC::ex & lc) const;
      virtual GiNaC::ex append_letter(const GiNaC::ex & lc) const;
      virtual GiNaC::ex append_letter_list(const GiNaC::ex & lc) const;

    protected:
      virtual GiNaC::ex cast_to_Zsum(void) const;

      virtual GiNaC::ex multiply_letter_with_last_letter(const GiNaC::ex & lc) const;
      virtual GiNaC::ex multiply_letter_with_first_letter(const GiNaC::ex & lc) const;
      virtual GiNaC::ex concat_two_sums(const GiNaC::ex & Z1, const GiNaC::ex & Z2) const;

      // non-virtual functions
    public :
      GiNaC::ex get_index(void) const;
      GiNaC::ex get_letter_list(void) const;
      size_t get_depth(void) const;
      GiNaC::ex get_weight(void) const;

      // friends :
      NESTEDSUMS_API friend GiNaC::ex shuffle_Ssum(const GiNaC::ex & Z1, const GiNaC::ex & Z2);
      NESTEDSUMS_API friend GiNaC::ex convert_Ssum_to_Zsum(const GiNaC::ex & Z1);
      NESTEDSUMS_API friend GiNaC::ex remove_trivial_Ssum(const GiNaC::ex & expr);

	// member variables :

    protected:

      GiNaC::ex n;
      GiNaC::ex letter_list;
    };

GINAC_DECLARE_UNARCHIVER(Ssum);

  // inline functions

  /**
   *
   * Returns the upper summation limit.
   *
   */
inline GiNaC::ex Ssum::get_index(void) const
  {
    return n;
  }

  /**
   *
   * Returns the letter_list.
   *
   */
inline GiNaC::ex Ssum::get_letter_list(void) const
  {
    return letter_list;
  }

  /**
   *
   * Returns the depth.
   *
   */
inline size_t Ssum::get_depth(void) const
  {
    return letter_list.nops();
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_Ssum(const GiNaC::ex & nc, const GiNaC::ex & llc)
  {
    return (new Ssum(nc,llc))->setflag(GiNaC::status_flags::dynallocated);
  }

NESTEDSUMS_API GiNaC::ex shuffle_Ssum(const GiNaC::ex & Z1, const GiNaC::ex & Z2);

NESTEDSUMS_API GiNaC::ex convert_Ssum_to_Zsum(const GiNaC::ex & Z1);

NESTEDSUMS_API GiNaC::ex create_Ssum_from_exvector(const GiNaC::ex & nc, const GiNaC::exvector & v);

NESTEDSUMS_API GiNaC::ex Ssum_to_Zsum(const GiNaC::ex & expr);

NESTEDSUMS_API GiNaC::ex shift_upper_limit_plus_one_for_Ssum(const GiNaC::ex & expr);

NESTEDSUMS_API GiNaC::ex remove_negative_degrees_from_Ssum(const GiNaC::ex & expr);

NESTEDSUMS_API GiNaC::ex remove_trivial_Ssum(const GiNaC::ex & expr);

NESTEDSUMS_API GiNaC::ex refine_Ssum(const GiNaC::ex & expr, unsigned q);

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_SSUM_H__
