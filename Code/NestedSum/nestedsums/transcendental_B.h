
/** @file transcendental_B.h
 *
 * Interface to transcendental_sum_type_B
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

#ifndef __NESTEDSUMS_TRANSCENDENTAL_B_H__
#define __NESTEDSUMS_TRANSCENDENTAL_B_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// The class transcendental_sum_type_B may contain \f$i\f$ and \f$(n-i)\f$.
  /**
   *
   *  The definition is 
   *  \f[
   *    \frac{\Gamma(1+d_1\varepsilon)}{\Gamma(1+b_1\varepsilon)} ...
   *    \frac{\Gamma(1+d_k\varepsilon)}{\Gamma(1+b_k\varepsilon)}
   *    \frac{\Gamma(1+d_1'\varepsilon)}{\Gamma(1+b_1'\varepsilon)} ...
   *    \frac{\Gamma(1+d_{k'}'\varepsilon)}{\Gamma(1+b_{k'}'\varepsilon)}
   *  \f]
   *  \f[
   *     \sum\limits_{i=1}^{n-1} 
   *       \frac{x^i}{(i+c)^m} 
   *       \frac{\Gamma(i+a_1+b_1\varepsilon)}{\Gamma(i+c_1+d_1\varepsilon)}
   *       \frac{\Gamma(i+a_2+b_2\varepsilon)}{\Gamma(i+c_2+d_2\varepsilon)} ...
   *       \frac{\Gamma(i+a_k+b_k\varepsilon)}{\Gamma(i+c_k+d_k\varepsilon)}
   *       Z(i+o-1,m_1,...,m_l,x_1,...,x_l)
   *  \f]
   *  \f[
   *       \cdot
   *       \frac{y^{n-i}}{(n-i+c')^{m'}} 
   *       \frac{\Gamma(n-i+a_1'+b_1'\varepsilon)}{\Gamma(n-i+c_1'+d_1'\varepsilon)}
   *       \frac{\Gamma(n-i+a_2'+b_2'\varepsilon)}{\Gamma(n-i+c_2'+d_2'\varepsilon)} ...
   *       \frac{\Gamma(n-i+a_{k'}'+b_{k'}'\varepsilon)}{\Gamma(n-i+c_{k'}'+d_{k'}'\varepsilon)}
   *       Z(n-i+o'-1,m_1',...,m_{l'}',x_1',...,x_{l'}')
   *  \f]
   *
   * Here, \f$c\f$, \f$c'\f$, \f$o\f$, \f$o'\f$ and all \f$a_j\f$, \f$a_j'\f$, \f$c_j\f$  and \f$c_j'\f$ are integers.
   * In addition \f$c\f$ is non-negative or \f$ c \ge -l+o \f$.
   * Simmilar, \f$c'\f$ is non-negative or \f$ c' \ge -l'+o' \f$.
   *
   * Note that the upper summation limit is \f$(n-1)\f$.
   * The upper summation limit should not be infinity.
   *
   */
  class NESTEDSUMS_API transcendental_sum_type_B : public GiNaC::basic
    {
      GINAC_DECLARE_REGISTERED_CLASS(transcendental_sum_type_B, GiNaC::basic)

	// ctors
    public:
      transcendental_sum_type_B(const GiNaC::ex & nn, const GiNaC::ex & i, const GiNaC::ex & l, const GiNaC::ex & lr, 
			       const GiNaC::ex & v, const GiNaC::ex & vr, const GiNaC::ex & ss, const GiNaC::ex & ssr, 
			       const GiNaC::ex & eps, int o, int f);

	// functions overriding virtual functions from base classes
    public:
      void archive(GiNaC::archive_node &node) const override;
      void read_archive(const GiNaC::archive_node &node, GiNaC::lst &sym_lst) override;

      unsigned return_type(void) const override { return GiNaC::return_types::noncommutative; }

      void print(const GiNaC::print_context & c, unsigned level = 0) const override;
      unsigned precedence(void) const override {return 40;}
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
      GiNaC::ex distribute_over_subsum(void) const;
      GiNaC::ex distribute_over_letter(void) const;
      GiNaC::ex distribute_over_subsum_rev(void) const;
      GiNaC::ex distribute_over_letter_rev(void) const;
      GiNaC::ex shift_plus_one(void) const;
      GiNaC::ex shift_plus_one_rev(void) const;

    protected:

	// member variables :

    protected:

      GiNaC::ex n;
      GiNaC::ex index;
      GiNaC::ex letter;
      GiNaC::ex letter_rev;
      GiNaC::ex lst_of_gammas;
      GiNaC::ex lst_of_gammas_rev;
      GiNaC::ex subsum;
      GiNaC::ex subsum_rev;

      GiNaC::ex expansion_parameter;

      int order;

      mutable int flag_expand_status;
    };

GINAC_DECLARE_UNARCHIVER(transcendental_sum_type_B);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_transcendental_sum_type_B(const GiNaC::ex & nn, const GiNaC::ex & i, const GiNaC::ex & l, const GiNaC::ex & lr, 
				    const GiNaC::ex & v, const GiNaC::ex & vr, const GiNaC::ex & ss, const GiNaC::ex & ssr, 
				    const GiNaC::ex & eps, int o, int f)
  {
    return (new transcendental_sum_type_B(nn,i,l,lr,v,vr,ss,ssr,eps,o,f))->setflag(GiNaC::status_flags::dynallocated);
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_transcendental_sum_type_B_and_set_gammas(const GiNaC::ex & nn, const GiNaC::ex & i, const GiNaC::ex & l, const GiNaC::ex & lr, 
				    const GiNaC::ex & v, const GiNaC::ex & vr, const GiNaC::ex & ss, const GiNaC::ex & ssr, 
				    const GiNaC::ex & eps, int o, int f)
  {
    // set index, expansion_parameter and order in the Gamma functions
    GiNaC::ex new_v = create_list_of_tgamma_and_set_gammas(GiNaC::ex_to<list_of_tgamma>(v).gamma_sequence,i,eps,o);

    // set index, expansion_parameter and order in the Gamma functions
    GiNaC::ex new_vr = create_list_of_tgamma_and_set_gammas(GiNaC::ex_to<list_of_tgamma>(vr).gamma_sequence,nn-i,eps,o);

    return (new transcendental_sum_type_B(nn,i,l,lr,new_v,new_vr,ss,ssr,eps,o,f))->setflag(GiNaC::status_flags::dynallocated);
  }

NESTEDSUMS_API GiNaC::ex create_transcendental_sum_type_B_and_expand(const GiNaC::ex & nn, const GiNaC::ex & i, const GiNaC::ex & l, const GiNaC::ex & lr,
					       const GiNaC::ex & v, const GiNaC::ex & vr, const GiNaC::ex & ss, const GiNaC::ex & ssr, 
					       const GiNaC::ex & eps, int o);

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_TRANSCENDENTAL_B_H__
