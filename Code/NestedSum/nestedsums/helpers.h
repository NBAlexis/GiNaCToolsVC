
/** @file helpers.h
 *
 * Interface to some helpers
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

#ifndef __NESTEDSUMS_HELPERS_H__
#define __NESTEDSUMS_HELPERS_H__

//#include "ginac/ginac.h"

namespace nestedsums {

    NESTEDSUMS_API GiNaC::ex nestedsums_helper_eval(const GiNaC::ex & expr);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_expand(const GiNaC::ex & expr, int level = 0);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_multiply_via_triangle(const GiNaC::ex & A, const GiNaC::ex & B,
                      		            const GiNaC::ex & expansion_parameter, int order);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_multiply_via_triangle_speedy(const GiNaC::ex & A, const GiNaC::ex & B,
						   const GiNaC::ex & expansion_parameter, int order);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_multiply_laurent(const GiNaC::ex & A, const GiNaC::ex & B,
                                       const GiNaC::ex & expansion_parameter, int order);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_multiply_laurent_speedy(const GiNaC::ex & A, const GiNaC::ex & B,
					      const GiNaC::ex & expansion_parameter, int order);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_expand_tgamma_fct(const GiNaC::ex & a1, const GiNaC::ex & b1, const GiNaC::ex & a2, const GiNaC::ex & b2,
					const GiNaC::ex & expansion_parameter, int order);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_expand_lst_tgamma_fct(const GiNaC::ex & ll1, const GiNaC::ex & ll2,
					    const GiNaC::ex & expansion_parameter, int order);

    NESTEDSUMS_API GiNaC::ex nestedsums_helper_expand_power(const GiNaC::ex & x, const GiNaC::ex & m, const GiNaC::ex & expansion_parameter, int order);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_series(const GiNaC::ex & f, const GiNaC::ex & expansion_parameter, int order);

    NESTEDSUMS_API GiNaC::ex nestedsums_helper_bernoulli(int n);

    NESTEDSUMS_API GiNaC::ex nestedsums_helper_lowering_op_geo_0(const GiNaC::ex & x, int m);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_lowering_op_geo_1(const GiNaC::ex & x, int m);

    NESTEDSUMS_API GiNaC::ex nestedsums_helper_arithmetic_sum_type_Z(const GiNaC::ex & n, const GiNaC::ex & m);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_arithmetic_sum_type_S(const GiNaC::ex & n, const GiNaC::ex & m);

    NESTEDSUMS_API int nestedsums_helper_get_degree(const GiNaC::ex & expr, const GiNaC::ex & eps);
    NESTEDSUMS_API int nestedsums_helper_ldegree(const GiNaC::ex & expr, const GiNaC::ex & eps);
    NESTEDSUMS_API GiNaC::ex nestedsums_helper_coeff(const GiNaC::ex & expr, const GiNaC::ex & eps, int n = 1);

    NESTEDSUMS_API GiNaC::exvector exvector_from_lst(const GiNaC::ex & l);
    NESTEDSUMS_API GiNaC::exvector reverse_exvector_from_lst(const GiNaC::ex & l);
    NESTEDSUMS_API GiNaC::exvector exvector_append_lst(const GiNaC::exvector & v, const GiNaC::ex & l);
    NESTEDSUMS_API GiNaC::exvector exvector_multiply_last_letter(const GiNaC::exvector & v, const GiNaC::ex & x);
    NESTEDSUMS_API GiNaC::exvector exvector_increase_last_degree(const GiNaC::exvector & v);

 class NESTEDSUMS_API nestedsums_helper_less
   {
     public :
       bool operator() (const GiNaC::ex & a, const GiNaC::ex & b) const;
   };

 NESTEDSUMS_API bool is_class_in_nestedsums(const GiNaC::ex & expr);
 NESTEDSUMS_API bool is_expr_in_sym_lst(const GiNaC::ex & expr, const GiNaC::lst & sym_lst);

 NESTEDSUMS_API GiNaC::ex nestedsums_helper_normalize(const GiNaC::ex & expr, const GiNaC::lst & sym_lst = _empty_list);
 NESTEDSUMS_API GiNaC::ex nestedsums_helper_sort(const GiNaC::ex & expr, const GiNaC::lst & sym_lst = _empty_list);

 NESTEDSUMS_API GiNaC::ex convert_Zsums_to_standard_form(const GiNaC::ex & expr, const GiNaC::lst & sym_lst = _empty_list);

 NESTEDSUMS_API void nestedsums_helper_clear_hashes(void);

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_HELPERS_H__

