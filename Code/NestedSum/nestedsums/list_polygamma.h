
/** @file list_polygamma.h
 *
 * Interface to list_of_tgamma
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

#ifndef __NESTEDSUMS_LIST_POLYGAMMA_H__
#define __NESTEDSUMS_LIST_POLYGAMMA_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// The class list_of_tgamma is a container for the class ratio_of_tgamma.
  /**
   *
   *  The definition is 
   *  \f[
   *    \frac{\Gamma(1+d_1\varepsilon)}{\Gamma(1+b_1\varepsilon)}
   *    \frac{\Gamma(1+d_2\varepsilon)}{\Gamma(1+b_2\varepsilon)} ...
   *    \frac{\Gamma(1+d_k\varepsilon)}{\Gamma(1+b_k\varepsilon)}
   *  \f]
   *  \f[
   *     \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+c_1+d_1\varepsilon)}
   *     \frac{\Gamma(i+a_2+b_2\varepsilon)}{\Gamma(i+c_2+d_2\varepsilon)} ...
   *     \frac{\Gamma(i+a_k+b_k\varepsilon)}{\Gamma(i+c_k+d_k\varepsilon)}
   *  \f]
   *
   */
  class NESTEDSUMS_API list_of_tgamma : public GiNaC::basic
    {
      friend class NESTEDSUMS_API transcendental_sum_type_A;
      friend class NESTEDSUMS_API transcendental_sum_type_B;
      friend class NESTEDSUMS_API transcendental_sum_type_C;
      friend class NESTEDSUMS_API transcendental_sum_type_D;

      GINAC_DECLARE_REGISTERED_CLASS(list_of_tgamma, GiNaC::basic)

	// ctors
    public:
      explicit list_of_tgamma(const GiNaC::ex & l);
      list_of_tgamma(const GiNaC::ex & l, const GiNaC::ex & i, const GiNaC::ex & eps, int o);

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
      virtual unsigned get_key(void) const;
      virtual GiNaC::ex hash_data(void) const;
      virtual GiNaC::ex subst_data(void) const;

	// non-virtual functions 
    public:
      GiNaC::ex set_expansion(void) const;
      GiNaC::ex set_index(const GiNaC::ex & new_index) const;
      GiNaC::ex set_expansion_parameter(const GiNaC::ex & new_eps) const;
      GiNaC::ex set_order(int new_order) const;

      GiNaC::ex get_index(void) const;
      size_t get_depth(void) const;

      GiNaC::ex shift_plus_one(void) const;
      GiNaC::ex shift_minus_one(void) const;
      GiNaC::ex index_eq_one(void) const;
      GiNaC::ex shift_index(const GiNaC::ex & new_index) const;

      GiNaC::ex concat(const GiNaC::ex & l) const;

      int pole_alert(void) const;
      int expansion_alert(void) const;


      // friends :
      NESTEDSUMS_API friend GiNaC::ex create_transcendental_sum_type_A_and_set_gammas(const GiNaC::ex & nn, const GiNaC::ex & i,
				const GiNaC::ex & l, const GiNaC::ex & v, const GiNaC::ex & ss, 
				const GiNaC::ex & eps, int o, int f);
      NESTEDSUMS_API friend GiNaC::ex create_transcendental_sum_type_B_and_set_gammas(const GiNaC::ex & nn, const GiNaC::ex & i, const GiNaC::ex & l, const GiNaC::ex & lr,
				const GiNaC::ex & v, const GiNaC::ex & vr, const GiNaC::ex & ss, const GiNaC::ex & ssr, 
				const GiNaC::ex & eps, int o, int f);
      NESTEDSUMS_API friend GiNaC::ex create_transcendental_sum_type_C_and_set_gammas(const GiNaC::ex & nn, const GiNaC::ex & i, const GiNaC::ex & l,
				const GiNaC::ex & v, const GiNaC::ex & ss, 
				const GiNaC::ex & eps, int o, int f);
      NESTEDSUMS_API friend GiNaC::ex create_transcendental_sum_type_D_and_set_gammas(const GiNaC::ex & nn, const GiNaC::ex & i, const GiNaC::ex & l, const GiNaC::ex & lr,
				const GiNaC::ex & v, const GiNaC::ex & vr, const GiNaC::ex & ss, const GiNaC::ex & ssr, 
				const GiNaC::ex & eps, int o, int f);

	// member variables :

    protected:

      GiNaC::ex gamma_sequence;
      GiNaC::ex index;
      GiNaC::ex expansion_parameter;
      int order;
    };

GINAC_DECLARE_UNARCHIVER(list_of_tgamma);

  // inline functions

  /**
   *
   * Returns the upper summation limit.
   *
   */
inline GiNaC::ex list_of_tgamma::get_index(void) const
  {
    return index;
  }

  /**
   *
   * Returns the depth.
   *
   */
inline size_t list_of_tgamma::get_depth(void) const
  {
    return gamma_sequence.nops();
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_list_of_tgamma(const GiNaC::ex & l)
  {
    return (new list_of_tgamma(l))->setflag(GiNaC::status_flags::dynallocated);
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_list_of_tgamma(const GiNaC::ex & l, const GiNaC::ex & i, const GiNaC::ex & eps, int o)
  {
    return (new list_of_tgamma(l,i,eps,o))->setflag(GiNaC::status_flags::dynallocated);
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_list_of_tgamma_and_set_gammas(const GiNaC::ex & l, const GiNaC::ex & i, const GiNaC::ex & eps, int o)
  {
    // set index, expansion_parameter and order in the Gamma functions
    GiNaC::lst* vl = new GiNaC::lst();
    vl->setflag(GiNaC::status_flags::dynallocated);
    int j;
    for (j=0;j<l.nops();j++)
      {
	vl->append(GiNaC::ex_to<ratio_of_tgamma>(l.op(j)).set_values(i,eps,o,expand_status::no_eval_to_scalar));
      }
    return (new list_of_tgamma(*vl,i,eps,o))->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_LIST_POLYGAMMA_H__
