
/** @file Euler_Zagier_sum.h
 *
 * Interface to Euler-Zagier sums 
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

#ifndef __NESTEDSUMS_EULER_ZAGIER_SUM_H__
#define __NESTEDSUMS_EULER_ZAGIER_SUM_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// A Euler-Zagier sum is a special case of a Zsum.
  /**
   *
   *  Euler-Zagier sums are recursively defined by
   *  \f[
   *     Z_{m_1,...,m_k}(n) = \sum\limits_{i=1}^n \frac{1}{i^{m_1}} Z_{m_2,...,m_k}(i-1)
   *  \f]
   *  with 
   *  \f[
   *     Z(n) = 1
   *  \f]
   *  for \f$ n \ge 0 \f$.
   *
   */
  class NESTEDSUMS_API Euler_Zagier_sum : public virtual Zsum
    {
      GINAC_DECLARE_REGISTERED_CLASS(Euler_Zagier_sum, Zsum)

	// ctors
    public:
      explicit Euler_Zagier_sum(const GiNaC::ex & nc);
      Euler_Zagier_sum(const GiNaC::ex & nc, const GiNaC::ex & llc);

	// functions overriding virtual functions from bases classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      GiNaC::return_type_t return_type_tinfo() const override;

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      GiNaC::ex eval() const override;

      GiNaC::ex convert_to_Ssum_exvector(const GiNaC::exvector & Z0, const GiNaC::exvector & Z1) const override;
      GiNaC::ex shuffle_exvector(const GiNaC::exvector & Z0, const GiNaC::exvector & Z1, const GiNaC::exvector & Z2) const override;

      GiNaC::ex set_index(const GiNaC::ex & i) const override;
      GiNaC::ex shift_plus_one(void) const override;
      GiNaC::ex shift_minus_one(void) const override;
      GiNaC::ex adjust_upper_limit_downwards(const GiNaC::ex & i) const override;
      GiNaC::ex adjust_upper_limit_upwards(const GiNaC::ex & i) const override;
      GiNaC::ex adjust_upper_limit_plus_one(void) const override;
      GiNaC::ex remove_first_letter(void) const override;
      GiNaC::ex remove_first_letter(const GiNaC::ex & nc) const override;
    };

GINAC_DECLARE_UNARCHIVER(Euler_Zagier_sum);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_Euler_Zagier_sum(const GiNaC::ex & nc, const GiNaC::ex & llc)
  {
    return (new Euler_Zagier_sum(nc,llc))->setflag(GiNaC::status_flags::dynallocated);
  }

NESTEDSUMS_API GiNaC::ex create_Euler_Zagier_sum_with_ones(const GiNaC::ex &n, const int &k);

NESTEDSUMS_API GiNaC::ex create_Euler_Zagier_sum_from_exvector(const GiNaC::ex & nc, const GiNaC::exvector & v);

} // namespace nestedsums

namespace GiNaC {

  // template specialization
template<> inline const nestedsums::Euler_Zagier_sum &ex_to<nestedsums::Euler_Zagier_sum>(const ex &e)
  {
    return dynamic_cast<const nestedsums::Euler_Zagier_sum &>(*e.bp);
  }

} // end namespace GiNaC

#endif // ndef __NESTEDSUMS_EULER_ZAGIER_SUM_H__
