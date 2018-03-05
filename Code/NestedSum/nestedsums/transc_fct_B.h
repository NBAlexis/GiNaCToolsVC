
/** @file transc_fct_B.h
 *
 * Interface to transcendental_fct_type_B
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

#ifndef __NESTEDSUMS_TRANSC_FCT_B_H__
#define __NESTEDSUMS_TRANSC_FCT_B_H__

//#include "ginac/ginac.h"

namespace nestedsums {

  /// The class transcendental_fct_type_B provides an interface
  /// to the class transcendental_sum_type_B.
  /**
   *
   *  The definition is 
   *  \f[
   *     \frac{\Gamma(d_1) ... \Gamma(d_n)}{\Gamma(d_1') ... \Gamma(d_{n'}')} 
   *      \sum\limits_{i=0}^\infty \sum\limits_{j=0}^\infty 
   *       \frac{\Gamma(i+a_1) ... \Gamma(i+a_k)}{\Gamma(i+a_1') ... \Gamma(i+a_{k-1}')} 
   *       \frac{\Gamma(j+b_1) ... \Gamma(j+b_l)}{\Gamma(j+b_1') ... \Gamma(j+b_{l-1}')} 
   *       \frac{\Gamma(i+j+c_1) ... \Gamma(i+j+c_m)}{\Gamma(i+j+c_1') ... \Gamma(i+j+c_{m}')} 
   *      \frac{x_1^i}{i!} \frac{x_2^j}{j!}
   *  \f]
   *
   */
  class NESTEDSUMS_API transcendental_fct_type_B : public GiNaC::basic
    {
      GINAC_DECLARE_REGISTERED_CLASS(transcendental_fct_type_B, GiNaC::basic)

	// ctors
    public:
      transcendental_fct_type_B(const GiNaC::ex & xx1, const GiNaC::ex & xx2, const GiNaC::ex & ii_num, const GiNaC::ex & ii_denom, 
				const GiNaC::ex & jj_num, const GiNaC::ex & jj_denom,
				const GiNaC::ex & iijj_num, const GiNaC::ex & iijj_denom, 
				const GiNaC::ex & pp_num, const GiNaC::ex & pp_denom);
      transcendental_fct_type_B(const GiNaC::ex & xx1, const GiNaC::ex & xx2, const GiNaC::ex & ii_num, const GiNaC::ex & ii_denom, 
				const GiNaC::ex & jj_num, const GiNaC::ex & jj_denom,
				const GiNaC::ex & iijj_num, const GiNaC::ex & iijj_denom, 
				const GiNaC::ex & pp_num, const GiNaC::ex & pp_denom, const GiNaC::ex & eps, int o, int f);

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

	// non-virtual functions 
    public:
      GiNaC::ex set_expansion(const GiNaC::ex & eps, int o) const;
      GiNaC::ex shift_plus_one(void) const;

	// member variables :

    protected:

      GiNaC::ex x1;
      GiNaC::ex x2;
      GiNaC::ex i_num;
      GiNaC::ex i_denom;
      GiNaC::ex j_num;
      GiNaC::ex j_denom;
      GiNaC::ex ij_num;
      GiNaC::ex ij_denom;
      GiNaC::ex pre_num;
      GiNaC::ex pre_denom;

      GiNaC::ex expansion_parameter;

      int order;

      mutable int flag_expand_status;
    };

GINAC_DECLARE_UNARCHIVER(transcendental_fct_type_B);

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_transcendental_fct_type_B(const GiNaC::ex & xx1, const GiNaC::ex & xx2, const GiNaC::ex & ii_num, const GiNaC::ex & ii_denom,
					   const GiNaC::ex & jj_num, const GiNaC::ex & jj_denom,
					   const GiNaC::ex & iijj_num, const GiNaC::ex & iijj_denom, 
					   const GiNaC::ex & pp_num, const GiNaC::ex & pp_denom)
  {
    return (new transcendental_fct_type_B(xx1,xx2,ii_num,ii_denom,jj_num,jj_denom,iijj_num,iijj_denom,pp_num,pp_denom)
	    )->setflag(GiNaC::status_flags::dynallocated);
  }

  /**
   *
   * Named ctor on the heap.
   *
   */
inline GiNaC::ex create_transcendental_fct_type_B(const GiNaC::ex & xx1, const GiNaC::ex & xx2, const GiNaC::ex & ii_num, const GiNaC::ex & ii_denom, 
					   const GiNaC::ex & jj_num, const GiNaC::ex & jj_denom,
					   const GiNaC::ex & iijj_num, const GiNaC::ex & iijj_denom, 
					   const GiNaC::ex & pp_num, const GiNaC::ex & pp_denom, const GiNaC::ex & eps, int o, int f)
  {
    return (new transcendental_fct_type_B(xx1,xx2,ii_num,ii_denom,jj_num,jj_denom,iijj_num,iijj_denom,pp_num,pp_denom,eps,o,f)
	    )->setflag(GiNaC::status_flags::dynallocated);
  }

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_TRANSC_FCT_B_H__
