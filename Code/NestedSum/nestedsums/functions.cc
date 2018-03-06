/** @file functions.cc
 *
 *  Implements some special functions and conversions to and from Z-sums
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


#include "nestedsum_private.h"

#include <string>


namespace nestedsums {

using namespace GiNaC;


// Harmonic sum
//static ex Harmonic_sum_eval(const ex& x1, const ex& x2)
ex Harmonic_sum_eval(const ex& x1, const ex& x2)
{
	return Harmonic_sum(x1,x2).hold();
}
REGISTER_FUNCTION(Harmonic_sum, eval_func(Harmonic_sum_eval));


// Euler-Zagier sum
//static ex EulerZagier_sum_eval(const ex& x1, const ex& x2)
ex EulerZagier_sum_eval(const ex& x1, const ex& x2)
{
	return EulerZagier_sum(x1,x2).hold();
}
REGISTER_FUNCTION(EulerZagier_sum, eval_func(EulerZagier_sum_eval));


// S sum to infinity
//static ex S_sum_infinity_eval(const ex& x1, const ex& x2)
ex S_sum_infinity_eval(const ex& x1, const ex& x2)
{
	return S_sum_infinity(x1,x2).hold();
}
REGISTER_FUNCTION(S_sum_infinity, eval_func(S_sum_infinity_eval));


// S sum
//static ex S_sum_eval(const ex& x1, const ex& x2, const ex& x3)
ex S_sum_eval(const ex& x1, const ex& x2, const ex& x3)
{
	return S_sum(x1,x2,x3).hold();
}
REGISTER_FUNCTION(S_sum, eval_func(S_sum_eval));


// Z sum
//static ex Z_sum_eval(const ex& x1, const ex& x2, const ex& x3)
ex Z_sum_eval(const ex& x1, const ex& x2, const ex& x3)
{
	return Z_sum(x1,x2,x3).hold();
}
REGISTER_FUNCTION(Z_sum, eval_func(Z_sum_eval));


struct map_remove_Zsums : public map_function
{
	ex operator()(const ex& e)
	{
		if (is_a<add>(e) || is_a<mul>(e) || is_a<ncmul>(e)) {
			return e.map(*this);
		}
		else if (is_a<classical_polylog>(e)) {
			int depth = static_cast<int>(ex_to<classical_polylog>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<classical_polylog>(e).get_letter_list();
			ex degree = ex_to<letter>(letterlist.op(0)).get_degree();
			if (degree == 1)
				return -log(1-ex_to<letter>(letterlist.op(0)).get_scale());
			else
				return Li(degree, ex_to<letter>(letterlist.op(0)).get_scale());
		}
		else if (is_a<nielsen_polylog>(e)) {
			int depth = static_cast<int>(ex_to<nielsen_polylog>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<nielsen_polylog>(e).get_letter_list();
			return S(ex_to<letter>(letterlist.op(0)).get_degree()-1, depth, ex_to<letter>(letterlist.op(0)).get_scale());
		}
		else if (is_a<harmonic_polylog>(e)) {
			int depth = static_cast<int>(ex_to<harmonic_polylog>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<harmonic_polylog>(e).get_letter_list();
			lst degrees;
			for (int i=0; i<depth; i++)
				degrees.append(ex_to<letter>(letterlist.op(i)).get_degree());
			return H(degrees, ex_to<letter>(letterlist.op(0)).get_scale());
		}
		else if (is_a<multiple_zeta_value>(e)) {
			int depth = static_cast<int>(ex_to<multiple_zeta_value>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<multiple_zeta_value>(e).get_letter_list();
			lst degrees;
			for (int i=0; i<depth; i++)
				degrees.append(ex_to<letter>(letterlist.op(i)).get_degree());
			return zeta(degrees);
		}
		else if (is_a<multiple_polylog>(e)) {
			int depth = static_cast<int>(ex_to<multiple_polylog>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<multiple_polylog>(e).get_letter_list();
			lst degrees;
			lst scales;
			for (int i=0; i<depth; i++) {
				degrees.append(ex_to<letter>(letterlist.op(i)).get_degree());
				scales.append(ex_to<letter>(letterlist.op(i)).get_scale());
			}
			return Li(degrees, scales);
		}
		else if (is_a<Euler_Zagier_sum>(e)) {
			int depth = static_cast<int>(ex_to<Euler_Zagier_sum>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<Euler_Zagier_sum>(e).get_letter_list();
			lst degrees;
			for (int i=0; i<depth; i++)
				degrees.append(ex_to<letter>(letterlist.op(i)).get_degree());
			return EulerZagier_sum(degrees, ex_to<Euler_Zagier_sum>(e).get_index());
		}
		else if (is_a<harmonic_sum>(e)) {
			int depth = static_cast<int>(ex_to<harmonic_sum>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<harmonic_sum>(e).get_letter_list();
			lst degrees;
			for (int i=0; i<depth; i++)
				degrees.append(ex_to<letter>(letterlist.op(i)).get_degree());
			return Harmonic_sum(degrees, ex_to<harmonic_sum>(e).get_index());
		}
		else if (is_a<Ssum_to_Infinity>(e)) {
			int depth = static_cast<int>(ex_to<Ssum_to_Infinity>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<Ssum_to_Infinity>(e).get_letter_list();
			lst degrees;
			for (int i=0; i<depth; i++)
				degrees.append(ex_to<letter>(letterlist.op(i)).get_degree());
			lst scales;
			for (int i=0; i<depth; i++)
				scales.append(ex_to<letter>(letterlist.op(i)).get_scale());
			return S_sum_infinity(degrees, scales);
		}
		else if (is_a<Ssum>(e)) {
			int depth = static_cast<int>(ex_to<Ssum>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<Ssum>(e).get_letter_list();
			lst degrees;
			for (int i=0; i<depth; i++)
				degrees.append(ex_to<letter>(letterlist.op(i)).get_degree());
			lst scales;
			for (int i=0; i<depth; i++)
				scales.append(ex_to<letter>(letterlist.op(i)).get_scale());
			return S_sum(ex_to<Ssum>(e).get_index(), degrees, scales);
		}
		else if (is_a<Zsum>(e)) {
			int depth = static_cast<int>(ex_to<Zsum>(e).get_depth());
			if (!depth)
				return 1;
			ex letterlist = ex_to<Zsum>(e).get_letter_list();
			lst degrees;
			for (int i=0; i<depth; i++)
				degrees.append(ex_to<letter>(letterlist.op(i)).get_degree());
			lst scales;
			for (int i=0; i<depth; i++)
				scales.append(ex_to<letter>(letterlist.op(i)).get_scale());
			return Z_sum(ex_to<Zsum>(e).get_index(), degrees, scales);
		}
		else if (is_a<letter>(e)) {
			basic_letter el = ex_to<basic_letter>(e);
			return pow(el.get_scale(), el.get_index()) / pow((el.get_index()+el.get_offset()), el.get_degree());
		}
		return e;
	}
};


struct map_insert_Zsums : public map_function
{
	ex operator()(const ex& e)
	{
		if (is_a<add>(e) || is_a<mul>(e) || is_a<ncmul>(e)) {
			return e.map(*this);
		}
		else if (is_a<function>(e)) {
			std::string name = ex_to<function>(e).get_name();
			if (name == "Li") {
				if (is_a<lst>(e.op(0))) {
					lst letterlist;
					for (int i=0; i<e.op(0).nops(); i++) {
						letterlist.append(basic_letter(e.op(1).op(i), e.op(0).op(i), 0));
					}
					return multiple_polylog(letterlist);
				}
				else {
					lst letterlist{basic_letter(e.op(1), e.op(0), 0)};
					return classical_polylog(letterlist);
				}
			}
			else if (name == "S") {
				lst letterlist;
				letterlist.append(basic_letter(e.op(2),e.op(0)+1, 0));
				for (int i=0; i<e.op(1)-1; i++) {
					letterlist.append(unit_letter(numeric(1)));
				}
				return nielsen_polylog(letterlist);
			}
			else if (name == "H") {
				lst letterlist;
				if (is_a<lst>(e.op(0))) {
					letterlist.append(basic_letter(e.op(1),e.op(0).op(0), 0));
					for (int i=1; i<e.op(0).nops(); i++) {
						letterlist.append(basic_letter(numeric(1), e.op(0).op(i), 0));
					}
				} else {
					letterlist.append(basic_letter(e.op(1),e.op(0), 0));
				}
				return harmonic_polylog(letterlist);
			}
			else if (name == "mZeta") {
				lst letterlist;
                int imax = static_cast<int>(e.op(0).nops());
				for (int i= imax -1; i>=0; i--) {
					letterlist.append(unit_letter(e.op(0).op(i)));
				}
				return multiple_zeta_value(letterlist);
			}
			else if (name == "zeta") {
				lst letterlist;
				if (is_a<lst>(e.op(0))) {
					for (int i=0; i<e.op(0).nops(); i++) {
						letterlist.append(unit_letter(e.op(0).op(i)));
					}
				} else {
					letterlist.append(unit_letter(e.op(0)));
				}
				return multiple_zeta_value(letterlist);
			}
			else if (name == "Harmonic_sum") {
				lst letterlist;
				for (int i=0; i<e.op(0).nops(); i++) {
					letterlist.append(unit_letter(e.op(0).op(i)));
				}
				return harmonic_sum(e.op(1), letterlist);
			}
			else if (name == "EulerZagier_sum") {
				lst letterlist;
				for (int i=0; i<e.op(0).nops(); i++) {
					letterlist.append(unit_letter(e.op(0).op(i)));
				}
				return Euler_Zagier_sum(e.op(1), letterlist);
			}
			else if (name == "S_sum_infinity") {
				lst letterlist;
				for (int i=0; i<e.op(0).nops(); i++) {
					letterlist.append(basic_letter(e.op(1).op(i), e.op(0).op(i), 0));
				}
				return Ssum_to_Infinity(letterlist);
			}
			else if (name == "S_sum") {
				lst letterlist;
				for (int i=0; i<e.op(1).nops(); i++) {
					letterlist.append(basic_letter(e.op(2).op(i), e.op(1).op(i), 0));
				}
				return Ssum(e.op(0), letterlist);
			}
			else if (name == "Z_sum") {
				lst letterlist;
				for (int i=0; i<e.op(1).nops(); i++) {
					letterlist.append(basic_letter(e.op(2).op(i), e.op(1).op(i), 0));
				}
				return Zsum(e.op(0), letterlist);
			}
		}
		return e;
	}
};


// converts the ginac functions in an expression into Z-sums from the nestedsums library
ex convert_to_nestedsums(const ex& e)
{
	map_insert_Zsums do_it;
	
	return do_it(e) * Zsum(Infinity);
}


// converts the Z-sums in an expression into ginac functions
ex convert_to_ginac_functions(const ex& e)
{
	map_remove_Zsums do_it;
	
	return do_it(e);
}


} // namespace nestedsums

