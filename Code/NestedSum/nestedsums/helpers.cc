
/** @file helpers.cc
 *
 * Implementation of some helpers
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

#include <stdexcept>
#include "nestedsum_private.h"

#ifdef _DEBUG
#include <iostream>
#include <ctime>
#endif // def _DEBUG

namespace nestedsums {

using namespace GiNaC;

  /**
   *
   * A helper function to force the evaluation of sub-expressions.
   *
   * This function distributes over the container classes add, mul, ncmul and power.
   *
   */
  ex nestedsums_helper_eval(const ex & expr)
  {
    // addition
    if ( is_a<add>(expr))
      {
	int up_limit = static_cast<int>(expr.nops());
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	    res_exvector.push_back( nestedsums_helper_eval(expr.op(j)) );

	return (new add(res_exvector))->setflag(status_flags::dynallocated);
      }

    // multiplication
    if ( is_a<mul>(expr))
      {
	int up_limit = static_cast<int>(expr.nops());
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	    res_exvector.push_back( nestedsums_helper_eval(expr.op(j)) );

	return (new mul(res_exvector))->setflag(status_flags::dynallocated);
      }


    // ncmultiplication
    if ( is_a<ncmul>(expr))
      {
	int up_limit = static_cast<int>(expr.nops());
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	    res_exvector.push_back( nestedsums_helper_eval(expr.op(j)) );

	return (new ncmul(res_exvector))->setflag(status_flags::dynallocated);
      }

    // power
    if ( is_a<power>(expr) )
      {
	ex base = nestedsums_helper_eval( expr.op(0) );
	ex exponent = nestedsums_helper_eval( expr.op(1) );
	return (new power(base,exponent))->setflag(status_flags::dynallocated);
      }

    return expr.eval();
  }

  /**
   *
   * A helper routine to expand expressions.
   * GiNaC's proper expand method is buggy, therefore we provide a method
   * for the things we need. 
   * This helper routine knows about 
   * the classes "add", "mul" and "ncmul".
   *
   * If (level & expand_request::member_variables) is true,
   * the routine expands also recursively the arguments of the classes
   * basic_letter, Zsum, Ssum, Csum and Bsum.
   *
   * This routine is not a "complete" expand-function, for example, it does not
   * know about the class "power" and uses in this case the native GiNaC method,
   * if (level & expand_request::power) is set.
   *
   */
  ex nestedsums_helper_expand(const ex & expr, int level)
  {
    // flags is protected ?!?
    //
    // already expanded ?
    //    if ( (expr.bp->flags) & nestedsums_status_flags::expanded ) return expr;

    // addition
    if ( is_a<add>(expr))
      {
        int up_limit = static_cast<int>(expr.nops());
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	    res_exvector.push_back( nestedsums_helper_expand(expr.op(j),level) );

	return (new add(res_exvector))->setflag(status_flags::dynallocated);
      }

    // multiplication
    if ( is_a<mul>(expr) || is_a<ncmul>(expr))
      {
	exvector factors;
    int up_limit = static_cast<int>(expr.nops());
	factors.reserve(up_limit);
	int flag = 0;

	for (int j=0;j<expr.nops();j++)
	  {
	    if ( is_a<add>(expr.op(j)))
	      {
		int pos = j;
		// found an "add" as factor,
		// call all the factors before this specific one "prefactors"
		// all factors after this specific one "postfactor".
		int i;
		exvector postfactor;
		postfactor.reserve(up_limit);
		for (i=pos+1;i<up_limit;i++)
		  postfactor.push_back(expr.op(i));

		ex pre = (new ncmul(factors))->setflag(status_flags::dynallocated);
		ex post = (new ncmul(postfactor))->setflag(status_flags::dynallocated);

		int up_limit_pos = static_cast<int>(expr.op(pos).nops());
		exvector res_exvector;
		res_exvector.reserve(up_limit_pos);

		for (i=0;i<up_limit_pos;i++)
		  res_exvector.push_back( nestedsums_helper_expand(eval(pre*expr.op(pos).op(i)*post),level) );

		return (new add(res_exvector))->setflag(status_flags::dynallocated);

	      }
	    
	    ex temp_factor = nestedsums_helper_expand(expr.op(j),level);

	    // check if it expanded to something
	    if ( !(temp_factor.is_equal(expr.op(j))) ) flag++;

	    factors.push_back(temp_factor);
	  }

	if (flag)
	  {
	    // something expanded, recursion
	    ex res = (new ncmul(factors))->setflag(status_flags::dynallocated);
	    return nestedsums_helper_expand(res,level);
	  }
	else
	  {
	    // nothing expanded
	    return expr;
	  }

      } // end type mul

    // power
    if ( is_a<power>(expr) && ( level & expand_request::power ) )
      {
	// delegate the job
	return expr.expand();
      } // end type power

    // member variables
    if ( level & expand_request::member_variables )
      {
	if ( is_a<basic_letter>(expr) )
	  {
	    return ex_to<basic_letter>(expr).expand_members(level);
	  }
	else if ( is_a<Zsum>(expr) )
	  {
	    return ex_to<Zsum>(expr).expand_members(level);
	  }
	else if ( is_a<Ssum>(expr) )
	  {
	    return ex_to<Ssum>(expr).expand_members(level);
	  }
	else if ( is_a<Csum>(expr) )
	  {
	    return ex_to<Csum>(expr).expand_members(level);
	  }
	else if ( is_a<Bsum>(expr) )
	  {
	    return ex_to<Bsum>(expr).expand_members(level);
	  }
      } // end expand_request::member_variables

    return expr;

  }


  /**
   *
   * A routine to multiply power series in eps.
   *
   * A and B are power series in eps :
   *
   * \f[
   *    A = a_0 + a_1 \varepsilon + a_{n-1} \varepsilon^{n-1} + O(\varepsilon^n),
   * \f] \f[
   *    B = b_0 + b_1 \varepsilon + b_{n-1} \varepsilon^{n-1} + O(\varepsilon^n)
   * \f]
   *
   * The function calculates the power series \f$A \cdot B\f$.
   * It only calculates terms of order < n.
   *
   * It does not handle the case of Laurent series,
   * e.g. with terms like \f$1/\varepsilon\f$.
   * In that case one should use the routine
   * nestedsums_helper_multiply_laurent.
   *
   * The result is in "expanded" form.
   *
   */
  ex nestedsums_helper_multiply_via_triangle(const ex & A, const ex & B, const ex & expansion_parameter, int order)
  {
    int i,j;

    // expand first
    ex AA = nestedsums_helper_expand(A);
    ex BB = nestedsums_helper_expand(B);

    // set up triangle sum for expansion
    ex res = 0;
    for (j=0;j<order;j++)
      {
	for (i=0;i<=j;i++)
	  {
	    res = res + nestedsums_helper_expand( nestedsums_helper_coeff(AA,expansion_parameter,i)
						  * nestedsums_helper_coeff(BB,expansion_parameter,j-i)
						  * pow(expansion_parameter,j) );
	  }
      }

    return res;
  }

  /**
   *
   * As nestedsums_helper_multiply_via_triangle but assumes that the input is 
   * already in expanded form.
   *
   * The result is in "expanded" form.
   *
   */
  ex nestedsums_helper_multiply_via_triangle_speedy(const ex & A, const ex & B, const ex & expansion_parameter, int order)
  {
    int i,j;

    // set up triangle sum for expansion
    ex res = 0;
    for (j=0;j<order;j++)
      {
	for (i=0;i<=j;i++)
	  {
	    res = res + nestedsums_helper_expand( nestedsums_helper_coeff(A,expansion_parameter,i)
				* nestedsums_helper_coeff(B,expansion_parameter,j-i)
				* pow(expansion_parameter,j) );
	  }
      }

    return res;
  }


  /**
   *
   * A routine to multiply Laurent series in eps.
   *
   * A and B are Laurent series in \f$\varepsilon\f$. 
   * Multiplies to Laurent series and neglects terms of \f$O(\varepsilon^{order})\f$.
   *
   * The result is in "expanded" form.
   *
   */
  ex nestedsums_helper_multiply_laurent(const ex & A, const ex & B, const ex & expansion_parameter, int order)
  {
    int i,j;

    // expand first
    ex AA = nestedsums_helper_expand(A);
    ex BB = nestedsums_helper_expand(B);

    int A_low_degree = nestedsums_helper_ldegree(AA,expansion_parameter);
    int B_low_degree = nestedsums_helper_ldegree(BB,expansion_parameter);

    // set up triangle sum for expansion
    ex res = 0;
    for (j=0;j<order-A_low_degree-B_low_degree;j++)
      {
	for (i=0;i<=j;i++)
	  {
	    res = res + nestedsums_helper_expand( nestedsums_helper_coeff(AA,expansion_parameter,i+A_low_degree)
						  * nestedsums_helper_coeff(BB,expansion_parameter,j-i+B_low_degree)
						  * pow(expansion_parameter,j+A_low_degree+B_low_degree) );
	  }
      }

    return res;
  }

  /**
   *
   * As nestedsums_helper_multiply_laurent but assumes that the input is 
   * already in expanded form.
   *
   * The result is in "expanded" form.
   *
   */
  ex nestedsums_helper_multiply_laurent_speedy(const ex & A, const ex & B, const ex & expansion_parameter, int order)
  {
    int i,j;

    int A_low_degree = nestedsums_helper_ldegree(A,expansion_parameter);
    int B_low_degree = nestedsums_helper_ldegree(B,expansion_parameter);

    // set up triangle sum for expansion
    ex res = 0;
    for (j=0;j<order-A_low_degree-B_low_degree;j++)
      {
	for (i=0;i<=j;i++)
	  {
	    res = res + nestedsums_helper_expand( nestedsums_helper_coeff(A,expansion_parameter,i+A_low_degree)
						  * nestedsums_helper_coeff(B,expansion_parameter,j-i+B_low_degree)
						  * pow(expansion_parameter,j+A_low_degree+B_low_degree) );
	  }
      }

    return res;
  }


  /**
   *
   * Expands 
   * \f[
   *    \frac{\Gamma(a_1+b_1 \varepsilon)}{\Gamma(a_2+b_2 \varepsilon)}
   * \f]
   * in \f$\varepsilon\f$ up to \f$O(\varepsilon^{order})\f$.
   *
   * The neglected term is exactly of order \f$O(\varepsilon^{order})\f$.
   *
   * The result is in "expanded" form.
   *
   * The inversion of a power series
   * 1/( a0 + a1 eps + a2 eps^2 + ... )
   * sucks time and memory in GiNaC.
   *
   * It is therefore more efficient to calculate the series as
   * \f[
   *  \frac{1}{\Gamma(a_2+b_2 \varepsilon)} = \frac{1}{\pi} \sin \left( \pi \left( 1 - a_2 - b_2 \varepsilon \right) \right) 
   *  \Gamma(1-a_2-b_2 \varepsilon)
   * \f]
   *
   * The build-in "series"-method of GiNaC does not guarantee that the neglected
   * term is exactly of order \f$O(\varepsilon^{order})\f$.
   * 
   * For example
   *
   * expr.series(eps==0,order) works for
   *
   *   tgamma(1+eps),
   *
   *   tgamma(eps),
   *
   *   (1+a*eps ...)^{-1},
   *
   * but does not work for
   * 
   *   (1 + a*eps + ... + a_n eps^n),
   *
   *   (1/eps + a0 + a1 eps ... )^{-1}.
   *
   */
  ex nestedsums_helper_expand_tgamma_fct(const ex & a1, const ex & b1, const ex & a2, const ex & b2,
					 const ex & expansion_parameter, int order)
  {
    // bring A into a0 + a1 eps + ... form
    // by factoring out eps^A_low_degree
    // low_degree is either 0 or -1 if a1 is an integer

    ex A = tgamma(a1+expansion_parameter*b1);
    A = nestedsums_helper_series(A,expansion_parameter,order);

    int A_low_degree = A.ldegree(expansion_parameter);

    A = A * pow(expansion_parameter,-A_low_degree);

    A = nestedsums_helper_expand(A,expand_request::power);

    // treat b2 == 0 separately
    if ( b2.is_zero() )
      {
	return nestedsums_helper_expand( 1/tgamma(a2) * pow(expansion_parameter,A_low_degree) * A );
      }

    // bring B into b0 + b1 eps + ... form

    ex B = tgamma(1-a2-expansion_parameter*b2);
    B = nestedsums_helper_series( B, expansion_parameter, order - A_low_degree );

    int B_low_degree = B.ldegree(expansion_parameter);

    B = B * pow(expansion_parameter,-B_low_degree);

    B = nestedsums_helper_expand(B,expand_request::power);

    // bring C into c0 + c1 eps + ... form

    ex C = sin(Pi*(1-a2-expansion_parameter*b2))/Pi;
    C = nestedsums_helper_series( C, expansion_parameter, order - A_low_degree - B_low_degree );

    C = nestedsums_helper_expand(C,expand_request::power);

    // calculate the result
    // if A_low_degree = -1 we have to go one order higher
    // if B_low_degree = -1 we have to go one order higher
    ex res = nestedsums_helper_multiply_via_triangle_speedy(B,C,expansion_parameter,order-A_low_degree-B_low_degree);
    
    res = nestedsums_helper_multiply_via_triangle_speedy(A,res,expansion_parameter,order-A_low_degree-B_low_degree);

    res = res * pow(expansion_parameter,A_low_degree+B_low_degree);

    res = nestedsums_helper_expand(res);

    return res;
  }

  /**
   *
   * Expands ratios of tgamma functions in eps.
   * the first argument ll1 is a list, containing the arguments in the numerator, for example
   *
   *   lst( eps, 1-eps, 3+eps ).
   *
   * The second argument ll2 is a list containing the arguments of the denominator.
   * The neglected terms are of order O(eps^order).
   *
   * The result is in "collected" form.
   *
   */
  ex nestedsums_helper_expand_lst_tgamma_fct(const ex & ll1, const ex & ll2, const ex & expansion_parameter, int order)
  {
    if (!is_a<lst>(ll1)) throw(std::invalid_argument("first argument must be a list"));
    if (!is_a<lst>(ll2)) throw(std::invalid_argument("second argument must be a list"));

    lst l1 = ex_to<lst>(ll1);
    lst l2 = ex_to<lst>(ll2);

    int i, l_max;
    int flag = 0 ;
    lst l_a1,l_b1,l_a2,l_b2;
    ex res,a1,b1,a2,b2,temp,res_temp,a1_temp;

    if ( (l1.nops() == 0) && (l2.nops() == 0) ) return 1;

    // brute force algorithm :
    // - get the total number of poles
    // - increase the order variable for each ratio_of_tgamma by the total number of poles
    // - truncate in the end

    for (i=0;i<l1.nops();i++)
      {
	temp = nestedsums_helper_expand(l1.op(i));
	temp = temp.collect(expansion_parameter);

	a1_temp = temp.coeff(expansion_parameter,0);
	if ( (a1_temp.info(info_flags::negint)) || (a1_temp.is_zero()) ) flag++;
	l_a1.append( a1_temp );
	l_b1.append(temp.coeff(expansion_parameter,1) );
      }

    for (i=0;i<l2.nops();i++)
      {
	temp = nestedsums_helper_expand(l2.op(i));
	temp = temp.collect(expansion_parameter);

	l_a2.append(temp.coeff(expansion_parameter,0) );
	l_b2.append(temp.coeff(expansion_parameter,1) );
      }

    // list with unequal number of entries
    l_max = static_cast<int>(l1.nops());

    if ( l1.nops() < l2.nops() )
      {
	int l1_max = static_cast<int>(l1.nops());
    l_max = static_cast<int>(l2.nops());
	for ( i= l1_max;i<l_max;i++)
	  {
	    l_a1.append(1);
	    l_b1.append(0);
	  }
      }

    if ( l2.nops() < l1.nops() )
      {
        
        int l1_max = static_cast<int>(l1.nops());
        int l2_max = static_cast<int>(l2.nops());
	for ( i= l2_max;i<l1_max;i++)
	  {
	    l_a2.append(1);
	    l_b2.append(0);
	  }
      }

    a1 = l_a1.op(0);
    b1 = l_b1.op(0);
    a2 = l_a2.op(0);
    b2 = l_b2.op(0);

    // order increased by number_poles
    res = nestedsums_helper_expand_tgamma_fct(a1,b1,a2,b2,expansion_parameter,order+flag);

    for (i=1;i<l_max;i++)
      {
	a1 = l_a1.op(i);
	b1 = l_b1.op(i);
	a2 = l_a2.op(i);
	b2 = l_b2.op(i);

	// order increased by number_poles
	res_temp = nestedsums_helper_expand_tgamma_fct(a1,b1,a2,b2,expansion_parameter,order+flag);

	res = nestedsums_helper_multiply_laurent(res,res_temp,expansion_parameter,order+flag);
      }

    res_temp = nestedsums_helper_expand(res);
    res = 0 ;

    // only terms up to the given order
    for (i=nestedsums_helper_ldegree(res_temp,expansion_parameter);i<order;i++)
      {
	res = res + nestedsums_helper_coeff(res_temp,expansion_parameter,i) * pow(expansion_parameter,i);
      }

    return res;
  }

  /**
   *
   * Wrapper for series expansion around expansion parameter == 0.
   * Handles order<1 correctly.
   *
   */
  ex nestedsums_helper_series(const ex & f, const ex & expansion_parameter, int order)
  {
    // raison d'etre for this subroutine: GiNaC does not handle the expansion for
    //  order<1 correctly.
    ex A;

    if ( order < 1 )
      {
	// calculate to O(1) and truncate
	ex A_temp = f.series(expansion_parameter==0,1);
	A_temp = series_to_poly(A_temp);
	A_temp = nestedsums_helper_expand(A_temp);
	int k;
	int A_temp_low_degree = A_temp.ldegree(expansion_parameter);
	A = 0;
	for ( k = A_temp_low_degree;k<order;k++)
	  {
	    A = A + A_temp.coeff(expansion_parameter,k) * pow(expansion_parameter,k);
	  }
      }
    else
      {
	A = f.series(expansion_parameter==0,order);
	A = series_to_poly(A);
      }

    return A;
  }


  /**
   *
   * Takes a list lst(a1,a2,...,an) and constructs an exvector
   * from it, e.g.
   *
   *   v[0] = a1
   *
   *   ...
   *
   *   v[n-1] = an
   *
   */
  exvector exvector_from_lst(const ex & l) 
    {
      if (!is_a<lst>(l))
	throw(std::invalid_argument("argument must be a list"));

      lst ll = ex_to<lst>(l);

      int up_limit = static_cast<int>(ll.nops());

      exvector res;
      res.reserve(up_limit);

      for (int j=0;j<up_limit;j++)
	{
	  res.push_back(ll.op(j));
	}

      return res;
    }

  /**
   *
   * Takes a list lst(a1,a2,...,an) and constructs an exvector
   * in the reverse order from it, e.g.
   *
   *   v[0] = an
   *
   *   ...
   *
   *   v[n-1] = a1
   *
   */
  exvector reverse_exvector_from_lst(const ex & l) 
    {
      if (!is_a<lst>(l))
	throw(std::invalid_argument("argument must be a list"));

      lst ll = ex_to<lst>(l);

      int up_limit = static_cast<int>(ll.nops());

      exvector res;
      res.reserve(up_limit);

      for (int j=0;j<up_limit;j++)
	{
	  // do it in the reverse order
	  res.push_back(ll.op(up_limit-1-j));
	}

      return res;
    }

  /**
   *
   * Returns an exvector, where the elements of the list l have
   * been appended to the exvector v.
   *
   */
  exvector exvector_append_lst(const exvector & v, const ex & l)
    {
      if (!is_a<lst>(l))
	throw(std::invalid_argument("second argument must be a list"));

      lst ll = ex_to<lst>(l);

      int j;
      int up_limit = static_cast<int>(ll.nops());

      exvector res;
      res.reserve(up_limit+v.size());

      for (j=0;j<v.size();j++) res.push_back(v[j]);

      for (j=0;j<up_limit;j++) res.push_back(ll.op(j));

      return res;
    }

  /**
   *
   * If v is an exvector of letters, then this function returns
   * an exvector, where the scale of the last letter has been
   * multiplied by x.
   * The degree of the last letter is not changed.
   *
   */
  exvector exvector_multiply_last_letter(const exvector & v, const ex & x)
  {
    exvector res;
    res.reserve(v.size());

    for (int j=0;j<v.size()-1;j++) res.push_back(v[j]);

    const letter& old_letter = ex_to<letter>(v[v.size()-1]);
    ex new_letter = create_letter(x*old_letter.get_scale(),old_letter.get_degree());
    res.push_back(new_letter);

    return res;
  }

  /**
   *
   * If v is an exvector of letters, then this function returns
   * an exvector, where the degree of the last letter has been
   * raised by one.
   *
   */
  exvector exvector_increase_last_degree(const exvector & v) 
  {
    exvector res;
    res.reserve(v.size());

    for (int j=0;j<v.size()-1;j++) res.push_back(v[j]);

    const letter& old_letter = ex_to<letter>(v[v.size()-1]);
    ex new_letter = create_letter(old_letter.get_scale(),1+old_letter.get_degree());
    res.push_back(new_letter);

    return res;
  }

  /**
   *
   * Returns the n-th Bernoulli number.
   * They are calculated as \f$B_0 = 1\f$, \f$B_1 = -1/2\f$, \f$B_{2k+1} = 0\f$ for \f$k>0\f$ and
   * recursively through
   * \f[
   *  B_n = - \frac{1}{n+1} \sum\limits_{i=0}^{n-1}
   *       \left( \begin{array}{c} n+1 \\ i \\ \end{array} \right) B_i
   * \f]
   *
   */
  ex nestedsums_helper_bernoulli(int n)
  {
    numeric n_num = numeric(n);

    if ( n == 0 )
      { 
	return 1;
      }
    else if ( n == 1 )
      { 
	return numeric(-1,2);
      }
    else if ( n_num.is_odd() )
      {
	return 0;
      }
    else
      {
	int i;
	ex res = 0;
	for (i=0;i<n;i++)
	  {
	    res = res + binomial(n+1, n+1-i) * nestedsums_helper_bernoulli(i);
	  }
	res = -res/binomial(n+1,1);

	return res;
      }

    // default, should not oocur
    return 0;
  }

  /**
   *
   * Returns
   *\f[
   *   \left( x \frac{d}{dx} \right)^m \frac{1}{1-x}
   * \f]
   *
   */
  ex nestedsums_helper_lowering_op_geo_0(const ex & x, int m)
  {
    symbol xx("xx");

    // hard wire the function, to avoid f.subs( x == xx)
    ex res = pow(1-xx,-1);
    int i;
    for (i=0;i<m;i++)
      {
	res = xx*diff(res,xx);
      }

    return res.subs( xx == x );
  }

  /**
   *
   * Returns
   *\f[
   *   \left( x \frac{d}{dx} \right)^m \frac{x}{1-x}
   * \f]
   *
   */
  ex nestedsums_helper_lowering_op_geo_1(const ex & x, int m)
  {
    symbol xx("xx");

    // hard wire the function, to avoid f.subs( x == xx)
    ex res = xx*pow(1-xx,-1);
    int i;
    for (i=0;i<m;i++)
      {
	res = xx*diff(res,xx);
      }

    return res.subs( xx == x );
  }

  /**
   *
   * Returns 
   * \f[
   *    \sum\limits_{i=1}^{n-1} i^m = \sum\limits_{k=0}^m \frac{B_k}{k!} \frac{m!}{(m+1-k)!} n^{m+1-k}
   * \f]
   *
   */
  ex nestedsums_helper_arithmetic_sum_type_Z(const ex & n, const ex & m)
  {
    if ( m.is_zero() ) return create_unit_letter(-1,n) - create_unit_letter(0,n);

    ex res = 0;
    int k;
    for (k=0;k<m+1;k++)
      {
	res = res + nestedsums_helper_bernoulli(k)/factorial(k)*factorial(m)/factorial(m+1-k)
	  * create_unit_letter(-m-1+k,n);
      }

    return res;
  }

  /**
   *
   * Returns
   * \f[
   *    \sum\limits_{i=1}^{n} i^m = n^m + \sum\limits_{k=0}^m \frac{B_k}{k!} \frac{m!}{(m+1-k)!} n^{m+1-k}
   * \f]
   *
   */
  ex nestedsums_helper_arithmetic_sum_type_S(const ex & n, const ex & m)
  {
    if ( m.is_zero() ) return create_unit_letter(-1,n);

    ex res = create_unit_letter(-m,n);
    int k;
    for (k=0;k<m+1;k++)
      {
	res = res + nestedsums_helper_bernoulli(k)/factorial(k)*factorial(m)/factorial(m+1-k)
	  * create_unit_letter(-m-1+k,n);
      }

    return res;
  }

  /**
   *
   * Expands \f$x^m\f$ with \f$m=a+b\varepsilon\f$ in \f$\varepsilon\f$ up to the desired order.
   *
   * \f[
   *    x^{a+b\varepsilon} 
   *      = x^a \sum\limits_{i=0}^\infty \varepsilon^i \frac{(-b)^i}{i!} \left( \mbox{Li}_1(1-x) \right)^i  
   * \f]
   *
   * The result is in expanded form.
   *
   */
  ex nestedsums_helper_expand_power(const ex & x, const ex & m, const ex & expansion_parameter, int order)
  {
    int k;

    ex temp = nestedsums_helper_expand(m);
    temp = temp.collect(expansion_parameter);

    ex a = temp.coeff(expansion_parameter,0);
    ex b = temp.coeff(expansion_parameter,1);

    ex res = create_Zsum(Infinity,_empty_list);
    ex letter = create_letter(1-x,1);
    ex Z0 = create_classical_polylog(lst{letter});
    ex Zn = 1;

    for (k=1;k<order;k++)
      {
	Zn = Zn*Z0;
	res = res + pow(-b,k) * pow(expansion_parameter,k) / factorial(k) * Zn;
      }

    return nestedsums_helper_expand( pow(x,a) * res );

  }

  /**
   *
   * Returns the power to which a variable appears in an expression.
   * 
   * On sums this function return zero, e.g. sums are not allowed to 
   * contain powers of eps.
   *
   */
  int nestedsums_helper_get_degree(const ex & expr, const ex & eps)
  {
    if ( expr.is_equal(eps) ) return 1;

    if ( is_a<power>(expr) && expr.op(0).is_equal(eps) && expr.op(1).info(info_flags::integer) ) 
      return ex_to<numeric>(expr.op(1)).to_int();

    // multiplication
    if ( is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int degree = 0;
	for (int j=0;j<expr.nops();j++)
	    degree += nestedsums_helper_get_degree(expr.op(j),eps);
	return degree;
      }

    // anything else
    return 0;
  }

  /**
   *
   * Returns the degree of the lowest order term in a Laurent series.
   *
   * The expression is assumed to be in "expanded" or "normal" form.
   *
   */
  int nestedsums_helper_ldegree(const ex & expr, const ex & eps)
  {
    if ( expr.is_equal(eps) ) return 1;

    if ( is_a<power>(expr) && expr.op(0).is_equal(eps) && expr.op(1).info(info_flags::integer) ) 
      return ex_to<numeric>(expr.op(1)).to_int();

    // addition
    if ( is_a<add>(expr)) 
      {
	int ldegree = nestedsums_helper_ldegree(expr.op(0),eps);
	for (int j=1;j<expr.nops();j++)
	  {
	    int ldegree_temp = nestedsums_helper_ldegree(expr.op(j),eps);
	    if ( ldegree_temp < ldegree ) ldegree = ldegree_temp;
	  }
	return ldegree;
      }

    // multiplication
    if ( is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int ldegree = 0;
	for (int j=0;j<expr.nops();j++)
	    ldegree += nestedsums_helper_ldegree(expr.op(j),eps);
	return ldegree;
      }

    // anything else
    return 0;
  }

  /**
   *
   * Returns the coefficient of the order \f$n\f$ term in a Laurent series.
   *
   * The expression is assumed to be in "expanded" or "normal" form.
   *
   */
  ex nestedsums_helper_coeff(const ex & expr, const ex & eps, int n)
  {
    // atomic: eps or other symbol
    if ( expr.is_equal(eps) ) 
      {
	if ( n == 1)
	  {
	    return 1;
	  }
	else
	  {
	    return 0;
	  }
      }

    // pow(eps,n) or other power
    if ( is_a<power>(expr) && expr.op(0).is_equal(eps) ) 
      {
	if ( expr.op(1).is_equal(n) )
	  {
	    return 1;
	  }
	else
	  {
	    return 0;
	  }
      }

    // addition
    if ( is_a<add>(expr))
      {
	int up_limit = static_cast<int>(expr.nops());
	exvector res_exvector;
	res_exvector.reserve(up_limit);

	for (int j=0;j<up_limit;j++)
	    res_exvector.push_back( nestedsums_helper_coeff(expr.op(j),eps,n) );

	return (new add(res_exvector))->setflag(status_flags::dynallocated);
      }

    // multiplication
    if ( is_a<mul>(expr) || is_a<ncmul>(expr) )
      {
	int degree = nestedsums_helper_get_degree(expr,eps);

	if ( degree == n)
	  {
	    return expr*pow(eps,-n);
	  }
	else
	  {
	    return 0;
	  }
      }

    // anything else
    if ( n==0 ) return expr;

    return 0;
  }

  /**
   *
   * Returns true if \f$a < b \f$ and false otherwise.
   * The actual comparison is delegated to ex::compare.
   *
   * This is a function object and needed by 
   * nestedsums_helper_normalize.
   *
   */
  bool nestedsums_helper_less::operator() (const ex & a, const ex & b) const
  {
    if ( a.compare(b) == -1 ) return true;

    return false;
  }

  /**
   *
   * Returns true if expr is of type
   * Zsum, Ssum, basic_letter,
   * transcendental_sum_type_A to transcendental_sum_type_D,
   * list_of_tgamma, ratio_of_tgamma, 
   * Bsum or Csum.
   *
   * Returns false otherwise.
   * 
   */
  bool is_class_in_nestedsums(const ex & expr)
    {
      if ( is_a<Zsum>(expr)
	   || is_a<Ssum>(expr)
	   || is_a<basic_letter>(expr)
	   || is_a<transcendental_sum_type_A>(expr)
	   || is_a<transcendental_sum_type_B>(expr)
	   || is_a<transcendental_sum_type_C>(expr)
	   || is_a<transcendental_sum_type_D>(expr)
	   || is_a<list_of_tgamma>(expr)
	   || is_a<ratio_of_tgamma>(expr)
	   || is_a<Bsum>(expr)
	   || is_a<Csum>(expr)
	   )
	{
	  return true;
	}

      return false;
    }

  /**
   *
   * Returns true if expr is a symbol (or a symbol raised to some power)
   * contained in sym_lst.
   *
   * Returns false otherwise.
   *
   */
  bool is_expr_in_sym_lst(const ex & expr, const lst & sym_lst)
    {
      // this routine is a little bit clumsy to avoid a compiler bug
      // in gcc 2.95.3
      //
      // e.g. the line
      //
      // if ( is_a<power>(expr) ) return is_expr_in_sym_lst(expr.op(0),sym_lst);
      // 
      // fails for
      // expr=pow(x1,2) and sym_lst=lst(eps)
      // (would erraneously return true).
      //
      if ( is_a<power>(expr) ) 
	{
	  if (is_expr_in_sym_lst(expr.op(0),sym_lst)) return true;
	  return false;
	}

      if ( !is_a<symbol>(expr) ) 
	{
	  return false;
	}

      for (int i=0;i<sym_lst.nops();i++)
	{
	  if ( sym_lst.op(i).is_equal(expr) ) 
	    {
	      return true;
	    }
	}

      return false;
    }


  /**
   *
   * This function deals with expressions of the form
   *  a1 Term1 + b1 Term2 + a2 Term1 + c1 Term3 + ...,
   * where a1, b1, c1 are scalars and Term1, Term2 are
   * non-commutative objects defined in this package
   * (Zsums etc.) or products thereof.
   *
   * The function combines all terms with the same Term
   * and applies the method "normal" to them.
   *
   * This function is by far more efficient than
   * a brute force application of "normal" on the
   * complete expression.
   * 
   * The result is in "normal" form.
   *
   */
  ex nestedsums_helper_normalize(const ex & expr, const lst & sym_lst)
  {

    if ( !is_a<add>(expr) ) return expr;

    // addition
    if ( is_a<add>(expr))
      {
	std::map<ex, ex, nestedsums_helper_less> expr_table;
	std::map<ex, ex, nestedsums_helper_less>::iterator p;

	// fill the table
	for (int k=0;k<expr.nops();k++)
	  {
	    ex term = expr.op(k);
	    ex pre;
	    ex obj;

	    if ( is_a<mul>(term) || is_a<ncmul>(term) )
	      {
		int up_limit = static_cast<int>(term.nops());

		exvector pre_exvector;
		pre_exvector.reserve(up_limit);

		exvector obj_exvector;
		obj_exvector.reserve(up_limit);

		for (int j=0;j<up_limit;j++)
		  {
		    ex item = term.op(j);
		    if ( is_class_in_nestedsums(item) || is_expr_in_sym_lst(item,sym_lst) )
		      {
			obj_exvector.push_back( item );
		      }
		    else
		      {
			pre_exvector.push_back( item );
		      }
		  }

		pre = (new ncmul(pre_exvector))->setflag(status_flags::dynallocated);
		obj = (new ncmul(obj_exvector))->setflag(status_flags::dynallocated);
		obj = eval(obj);

	      } // end if type term == mul
	    else if ( is_class_in_nestedsums(term) || is_expr_in_sym_lst(term,sym_lst) )
	      {
		pre = 1;
		obj = term;
	      }
	    else // should not occur
	      {
		pre = term;
		obj = 1;
	      }

	    p = expr_table.find(obj);
	    if ( p != expr_table.end() )
	      {
		expr_table[obj] += pre;
	      }
	    else
	      {
		expr_table[obj] = pre;
	      }

	  } // end fill table

	// simplify the table
	p = expr_table.begin();
	while ( p!=expr_table.end() )
	  {
	    ex pre = p->second ;
	    ex obj = p->first ;

	    expr_table[obj] = pre.normal();
	    p++;
	  }

	// readout the table
	p = expr_table.begin();
	ex res = 0;
	while ( p!=expr_table.end() )
	  {
	    ex pre = p->second ;
	    ex obj = p->first ;

	    res += pre*obj;
	    p++;
	  }

	return res;

      } // end if type expr == add

    // ----------------------------------
    // anything else
    return expr;
  }

  /**
   *
   * Expands an expression first and collects and normalizes
   * terms of the same type.
   *
   * The result is in "normal" form.
   *
   */
  ex nestedsums_helper_sort(const ex & expr, const lst & sym_lst)
  {
    ex temp = nestedsums_helper_expand(expr);
    return nestedsums_helper_normalize(temp,sym_lst);
  }

  /**
   *
   * Converts an expression involving Zsums to a standard form
   * by first removing sums with non-positive degrees, expanding
   * the expression and bringing the coefficients to normal form.
   *
   * The result is in "normal" form.
   *
   */
  ex convert_Zsums_to_standard_form(const ex & expr, const lst & sym_lst)
    {
      ex temp = remove_negative_degrees_from_Zsum(expr);
      
      temp = nestedsums_helper_expand(temp,expand_request::member_variables);

      temp = nestedsums_helper_normalize(temp,sym_lst);

      return temp;
    }

  /**
   *
   * Clear the hash tables
   *
   */
 void nestedsums_helper_clear_hashes(void)
   {
     // clearing the tables
     _table_list_of_tgamma.clear();
     _table_transcendental_sum_type_A.clear();
     _table_transcendental_sum_type_C.clear();

     // setting the count of look-ups to zero
     _count_table_list_of_tgamma = 0;
     _count_table_transcendental_sum_type_A = 0;
     _count_table_transcendental_sum_type_C = 0;
   }

} // namespace nestedsums

namespace nestedsums {

/* Version information buried into the library */
const int version_major = NESTEDSUMS_MAJOR;
const int version_minor = NESTEDSUMS_MINOR;
const int version_micro = NESTEDSUMS_MICRO;

} // namespace nestedsums
