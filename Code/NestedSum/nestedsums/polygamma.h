
/** @file polygamma.h
 *
 * Interface to ratio_of_tgamma
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

#ifndef __NESTEDSUMS_POLYGAMMA_H__
#define __NESTEDSUMS_POLYGAMMA_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// The class ratio_of_tgamma contains the ratio of two Gamma functions
  /**
   *
   *  The definition is 
   *  \f[
   *     \frac{\Gamma(1+b_2\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *     \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+a_2+b_2\varepsilon)}
   *  \f]
   * Here \f$ a_1 \f$, \f$ b_1 \f$, \f$ a_2 \f$ and \f$ b_2 \f$ are passed to the constructor.
   * The index \f$i\f$ and the expansion parameter \f$\varepsilon\f$ can be set via the
   * set_index(const ex &)  and set_expansion_parameter(const ex &) methods, respectively.
   *
   * Additionally, this class contains an internal variable "order", which indicates
   * to which order this object should be expanded. The "order" variable can be set via
   * the method set_order(int). The expansion is performed by calling the method
   * set_expansion(void).
   *
   * This class assumes that \f$i+a_1 > 0\f$ for all \f$i\f$, e.g. it does not handle
   * possible poles in the Gamma function.
   *
   */
  class NESTEDSUMS_API ratio_of_tgamma : public GiNaC::basic
    {
      friend class NESTEDSUMS_API list_of_tgamma;

      GINAC_DECLARE_REGISTERED_CLASS(ratio_of_tgamma, GiNaC::basic)

	// ctors
    public:
      ratio_of_tgamma(const GiNaC::ex & a1, const GiNaC::ex & b1, const GiNaC::ex & a2, const GiNaC::ex & b2);
      ratio_of_tgamma(const GiNaC::ex & a1, const GiNaC::ex & b1, const GiNaC::ex & a2, const GiNaC::ex & b2, const GiNaC::ex & i, const GiNaC::ex & eps, 
        int o, int f);

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
      virtual GiNaC::ex eval_explicit() const;

	// non-virtual functions 
    public:
      GiNaC::ex set_expansion(void) const;
      GiNaC::ex set_index(const GiNaC::ex & new_index) const;
      GiNaC::ex set_expansion_parameter(const GiNaC::ex & new_eps) const;
      GiNaC::ex set_order(int new_order) const;
      GiNaC::ex set_flag(int new_flag) const;
      GiNaC::ex set_values(const GiNaC::ex & new_index, const GiNaC::ex & new_eps, int new_order, int new_flag) const;

      GiNaC::ex get_index(void) const;

      GiNaC::ex shift_plus_one(void) const;
      GiNaC::ex shift_minus_one(void) const;
      GiNaC::ex index_eq_one(void) const;
      GiNaC::ex shift_index(const GiNaC::ex & new_index) const;

      int pole_alert(void) const;
      int expansion_alert(void) const;

    protected:
      GiNaC::ex increase_numerator(int shift_order = 0) const;
      GiNaC::ex decrease_numerator(int shift_order = 0) const;
      GiNaC::ex increase_denominator(int shift_order = 0) const;
      GiNaC::ex decrease_denominator(int shift_order = 0) const;

      GiNaC::ex prefactor_increase_numerator(void) const;
      GiNaC::ex prefactor_decrease_numerator(void) const;
      GiNaC::ex prefactor_increase_denominator(void) const;
      GiNaC::ex prefactor_decrease_denominator(void) const;

	// member variables :

    protected:

      GiNaC::ex a1;
      GiNaC::ex b1;
      GiNaC::ex a2;
      GiNaC::ex b2;

      GiNaC::ex index;
      GiNaC::ex expansion_parameter;

      int order;
      int flag_expand_status;
    };

GINAC_DECLARE_UNARCHIVER(ratio_of_tgamma);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_ratio_of_tgamma(const GiNaC::ex & a1, const GiNaC::ex & b1, const GiNaC::ex & a2, const GiNaC::ex & b2)
  {
      return (new ratio_of_tgamma(a1,b1,a2,b2))->setflag(GiNaC::status_flags::dynallocated);
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_ratio_of_tgamma(const GiNaC::ex & a1, const GiNaC::ex & b1, const GiNaC::ex & a2, const GiNaC::ex & b2, const GiNaC::ex & i, const GiNaC::ex & eps, 
        int o, int f)
  {
    return (new ratio_of_tgamma(a1,b1,a2,b2,i,eps,o,f))->setflag(GiNaC::status_flags::dynallocated);
  }

NESTEDSUMS_API GiNaC::ex eval_ratio_of_tgamma_to_scalar(const GiNaC::ex & expr);

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_POLYGAMMA_H__
