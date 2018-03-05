/** @file normal.h
 *
 *  This file defines several functions that work on univariate and
 *  multivariate polynomials and rational functions.
 *  These functions include polynomial quotient and remainder, GCD and LCM
 *  computation, square-free factorization and rational function normalization. */

/*
 *  GiNaC Copyright (C) 1999-2018 Johannes Gutenberg University Mainz, Germany
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
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef GINAC_NORMAL_H
#define GINAC_NORMAL_H

#include "lst.h"

namespace GiNaC {

/**
 * Flags to control the behavior of gcd() and friends
 */
struct GINAC_API gcd_options
{
	enum {
		/**
		 * Usually GiNaC tries heuristic GCD first, because typically
		 * it's much faster than anything else. Even if heuristic
		 * algorithm fails, the overhead is negligible w.r.t. cost
		 * of computing the GCD by some other method. However, some
		 * people dislike it, so here's a flag which tells GiNaC
		 * to NOT use the heuristic algorithm.
		 */
		no_heur_gcd = 2,
		/**
		 * GiNaC tries to avoid expanding expressions when computing
		 * GCDs. This is a good idea, but some people dislike it.
		 * Hence the flag to disable special handling of partially
		 * factored polynomials. DON'T SET THIS unless you *really*
		 * know what are you doing!
		 */
		no_part_factored = 4,
		/**
		 * By default GiNaC uses modular GCD algorithm. Typically
		 * it's much faster than PRS (pseudo remainder sequence)
		 * algorithm. This flag forces GiNaC to use PRS algorithm
		 */
		use_sr_gcd = 8

	};
};

class GINAC_API ex;
class GINAC_API symbol;

// Quotient q(x) of polynomials a(x) and b(x) in Q[x], so that a(x)=b(x)*q(x)+r(x)
extern GINAC_API ex quo(const ex &a, const ex &b, const ex &x, bool check_args = true);

// Remainder r(x) of polynomials a(x) and b(x) in Q[x], so that a(x)=b(x)*q(x)+r(x)
extern GINAC_API ex rem(const ex &a, const ex &b, const ex &x, bool check_args = true);

// Decompose rational function a(x)=N(x)/D(x) into Q(x)+R(x)/D(x) with degree(R, x) < degree(D, x)
extern GINAC_API ex decomp_rational(const ex &a, const ex &x);

// Pseudo-remainder of polynomials a(x) and b(x) in Q[x]
extern GINAC_API ex prem(const ex &a, const ex &b, const ex &x, bool check_args = true);

// Pseudo-remainder of polynomials a(x) and b(x) in Q[x]
extern GINAC_API ex sprem(const ex &a, const ex &b, const ex &x, bool check_args = true);

// Exact polynomial division of a(X) by b(X) in Q[X] (quotient returned in q), returns false when exact division fails
extern GINAC_API bool divide(const ex &a, const ex &b, ex &q, bool check_args = true);

// Polynomial GCD in Z[X], cofactors are returned in ca and cb, if desired
extern GINAC_API ex gcd(const ex &a, const ex &b, ex *ca = nullptr, ex *cb = nullptr,
              bool check_args = true, unsigned options = 0);

// Polynomial LCM in Z[X]
extern GINAC_API ex lcm(const ex &a, const ex &b, bool check_args = true);

// Square-free factorization of a polynomial a(x)
extern GINAC_API ex sqrfree(const ex &a, const lst &l = lst());

// Square-free partial fraction decomposition of a rational function a(x)
extern GINAC_API ex sqrfree_parfrac(const ex & a, const symbol & x);

// Collect common factors in sums.
extern GINAC_API ex collect_common_factors(const ex & e);

// Resultant of two polynomials e1,e2 with respect to symbol s.
extern GINAC_API ex resultant(const ex & e1, const ex & e2, const ex & s);

struct GINAC_API sym_desc;
typedef std::vector<sym_desc> sym_desc_vec;
static bool heur_gcd_z(ex& res, const ex &a, const ex &b, ex *ca, ex *cb, sym_desc_vec::const_iterator var);

} // namespace GiNaC

#endif // ndef GINAC_NORMAL_H
