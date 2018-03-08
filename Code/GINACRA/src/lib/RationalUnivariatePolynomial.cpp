#include "ginacra_private.h"
/*
 * GiNaCRA - GiNaC Real Algebra package
 * Copyright (C) 2010-2012  Ulrich Loup, Joachim Redies, Sebastian Junges
 *
 * This file is part of GiNaCRA.
 *
 * GiNaCRA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GiNaCRA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GiNaCRA.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


//#define GINACRA_UNIVARIATERATIONALPOLYNOMIAL_DEBUG

/**
 * Implementation of the class RationalUnivariatePolynomial.
 *
 * @author Ulrich Loup
 * @since 2010-09-07
 * @version 2012-04-15
 * @see ISBN 0-387-94090-1 and ISBN-13: 978-3642069642
 */

#include <assert.h>
//
//#include "utilities.h"
//#include "RationalUnivariatePolynomial.h"
//#include "operators.h"

using GiNaC::is_exactly_a;

namespace GiNaCRA
{
    //////////////////////////
    // Con- and destructors //
    //////////////////////////

    RationalUnivariatePolynomial::RationalUnivariatePolynomial( const UnivariatePolynomial& p ) throw ( invalid_argument ):
        UnivariatePolynomial( p )
    {
        if( !GiNaC::is_rational_polynomial( p, p.variable() ))
        {
            stringstream stream;
            stream << "The specified univariate polynomial " << *this << " is not rational in " << p.variable() << ".";
            throw invalid_argument( stream.str() );
        }
        // setflag(status_flags::expanded | info_flags::rational_polynomial);
    }

    RationalUnivariatePolynomial::RationalUnivariatePolynomial( const ex& p, const symbol& s ) throw ( invalid_argument ):
        UnivariatePolynomial( p, s )
    {
        if( !GiNaC::is_rational_polynomial( *this, s ))    // need to take *this for the check because *this is expanded already
        {
            stringstream stream;
            stream << "The specified expression " << *this << " is not rational in " << s << ".";
            throw invalid_argument( stream.str() );
        }
        // setflag(status_flags::expanded | info_flags::rational_polynomial);
    }

    ///////////////
    // Operators //
    ///////////////

    // const RationalUnivariatePolynomial RationalUnivariatePolynomial::operator*(const RationalUnivariatePolynomial& o)
    // {
    //     return RationalUnivariatePolynomial(*this * o, mVariable);
    // }

    ////////////////
    // Operations //
    ////////////////

    GiNaC::sign RationalUnivariatePolynomial::sgn( const numeric& a ) const
    {
        numeric p_a = ex_to<numeric>( evaluateAt( a ));    // safe because of the constructor
        if( p_a < 0 )
            return GiNaC::NEGATIVE_SIGN;
        if( p_a > 0 )
            return GiNaC::POSITIVE_SIGN;
        return GiNaC::ZERO_SIGN;
    }

    numeric RationalUnivariatePolynomial::evaluateAt( const numeric& a ) const
    {
        // use Horner's method for polynomial evaluation
        numeric result = 0;
        for( int d = this->degree(); d >= 0; --d )
            result = this->coeff( d ) + result * a;
        return result;
    }

    numeric RationalUnivariatePolynomial::oneNorm() const
    {
        // compute the sum of the absolute values of the numeric coefficients
        numeric sum = 0;
        for( int i = UnivariatePolynomial::ldegree(); i <= UnivariatePolynomial::degree(); i++ )
            sum += abs( coeff( i ));
        return sum;
    }

    numeric RationalUnivariatePolynomial::twoNorm() const
    {
        // compute the sum of the squares of the absolute values of the numeric coefficients
        numeric sum = 0;
        for( int i = ldegree(); i <= degree(); i++ )
            sum += ex_to<numeric>( pow( coeff( i ), 2 ));
        return GiNaC::sqrt( sum );
    }

    numeric RationalUnivariatePolynomial::maximumNorm() const
    {
        // compute the maximum of the absolute values of the numeric coefficients
        numeric max = 0;
        for( int i = ldegree(); i <= degree(); i++ )
        {
            ex c = abs( ex_to<numeric>( coeff( i )));
            if( c > max )
                max = ex_to<numeric>( c );
        }
        return max;
    }

    numeric RationalUnivariatePolynomial::cauchyBound() const
    {
        numeric lcf = abs( UnivariatePolynomial::lcoeff() );    // we have to perform the conversion of coefficients because it is not clear whether we have a numeric or a RealAlgebraicNumberIR
        if( lcf == 0 )
            return 0;
        numeric sum = 0;
        for( int i = UnivariatePolynomial::ldegree(); i <= UnivariatePolynomial::degree(); ++i )
            sum += abs( UnivariatePolynomial::coeff( i )) / lcf;
        return sum;
    }

    unsigned RationalUnivariatePolynomial::countRealRoots() const
    {
        list<RationalUnivariatePolynomial> seq = standardSturmSequence( *this, this->diff() );
        numeric c = this->cauchyBound();
        OpenInterval i( -c, c );
        return signVariations( seq, i.left() ) - signVariations( seq, i.right() );
    }

    numeric RationalUnivariatePolynomial::approximateRealRoot( const numeric start, const OpenInterval& i, unsigned steps ) const
    {
        numeric pivot                  = start;
        RationalUnivariatePolynomial p = this->diff();
        while( this->sgn( pivot ) != GiNaC::ZERO_SIGN )
        {
            pivot = pivot - this->evaluateAt( pivot ) / p.evaluateAt( pivot );
            if( steps == 0 ||!i.contains( pivot ))    // failed
                return start;
            --steps;
        }
        // success
        return pivot;
    }

    ////////////////////
    // Static Methods //
    ////////////////////

    list<RationalUnivariatePolynomial> RationalUnivariatePolynomial::standardSturmSequence( const RationalUnivariatePolynomial& a,
                                                                                            const RationalUnivariatePolynomial& b )
    {
        list<UnivariatePolynomial>         seqUnivariate = UnivariatePolynomial::standardSturmSequence( a, b );
        list<RationalUnivariatePolynomial> seq           = list<RationalUnivariatePolynomial>();    // Sturm sequence to compute
        for( list<UnivariatePolynomial>::const_iterator i = seqUnivariate.begin(); i != seqUnivariate.end(); ++i )
            seq.push_back( RationalUnivariatePolynomial( *i ));
        return seq;
    }

    unsigned RationalUnivariatePolynomial::signVariations( const list<RationalUnivariatePolynomial>& seq, const numeric& a )
    {
        bool     sign  = seq.front().sgn( a ) >= GiNaC::ZERO_SIGN ? true : false;    // only positive (incl. zero) [1] and negative values [0] count
        unsigned count = 0;
        for( list<RationalUnivariatePolynomial>::const_iterator iter = seq.begin(); iter != seq.end(); ++iter )
        {
            bool tobexor = iter->sgn(a) >= GiNaC::ZERO_SIGN;
            //if( sign xor( iter->sgn( a ) >= GiNaC::ZERO_SIGN ))
            if ((sign && !tobexor) || (!sign && tobexor))
            {
                ++count;
                sign = !sign;
            }
        }
        return count;
    }

    int RationalUnivariatePolynomial::calculateSturmCauchyIndex( const RationalUnivariatePolynomial& p, const RationalUnivariatePolynomial& q )
    {
        if( p.is_zero() )
            throw invalid_argument( "Can not compute the Cauchy index of a zero polynomial." );
        const list<RationalUnivariatePolynomial> SRemS      = RationalUnivariatePolynomial::standardSturmSequence( p, q );
        const numeric                            upperBound = p.cauchyBound();
        assert( upperBound > 0 );

        //TODO make it faster by only iterating once. This needs an own method to calculate signVariations with two numeric parameters.
        return (((int)RationalUnivariatePolynomial::signVariations( SRemS, -upperBound ))
                - ((int)RationalUnivariatePolynomial::signVariations( SRemS, upperBound )));
    }

    int RationalUnivariatePolynomial::calculateRemainderTarskiQuery( const RationalUnivariatePolynomial& p, const RationalUnivariatePolynomial& q )
    {
        return RationalUnivariatePolynomial::calculateSturmCauchyIndex( p, (RationalUnivariatePolynomial)p.diff() * q );
    }

    //
    //    std::list<int> RationalUnivariatePolynomial::signDeterminationHelperRows(std::list<std::vector<Sign> > signs) {
    //        list<int> L1, L2, L3;
    //        unsigned n = signs.first.size();
    //
    //    }
    //
    //    std::list<std::vector<Sign> > RationalUnivariatePolynomial::calculateSignDetermination(const RationalUnivariatePolynomial& z, const std::vector<RationalUnivariatePolynomial>& polynomials) {
    //        int tq = calculateRemainderTarskiQuery(RationalUnivariatePolynomial(1,z.Variable()),z);
    //        int nrRoots  = std::abs(tq);
    //        set<std::vector<Sign> > realizedSignConditions;
    //
    //        //return the empty set, since there are no roots.
    //        if (nrRoots == 0) return realizedSignConditions;
    //
    //
    //        RationalUnivariatePolynomial polynomialsSquared;
    //        //We iterate backwards. Not sure why, but we are following the description from the book here.
    //        //TODO explain why we do not iterate forward.
    //        for(int i = polynomials.size(); i >= 0; i-- ) {
    //            polynomialSquared = polynomials[i].square()
    //            int tqp = calculateRemainderTarskiQuery(polynomials[i],z);
    //            int tqpp = calculateRemainderTarskiQuery(polynomialSquared, z);
    //            assert((tqp+tqpp)%2 == 0); // otherwise next division is inaccurate!
    //
    //            //Calculate the numbers using equality 10.13 from page 384.
    //            //Explicitly calculated in Proposition 2.65 from page 64.
    //            int nrPositives = (tqp + tqpp)/2
    //            int nrNegatives = (tqpp - tqp)/2;
    //            int nrZeroes = tq - tqpp;
    //
    //            //Count how many different signs.
    //            int differentsigns = 0;
    //            //If differentsigns becomes two, we would like to know which wasnt there.
    //            Sign nonexistant;
    //            if (nrPositives > 0) {
    //                differentsigns++;
    //                nonexistant = POSITIVESIGN;
    //            }
    //            if (nrNegatives > 0) {
    //                differentsigns++;
    //                nonexistant = NEGATIVESIGN;
    //            }
    //            if (nrZeroes > 0) {
    //                differentsigns++;
    //                nonexistant = ZEROSIGN;
    //            }
    //            // The signs can be -, 0, +, so no more than 3, and at least one of them has to be there, since z has roots.
    //            assert(differentsigns <= 3 && differentsigns > 1);
    //
    //            //We are using matrix-tensorproducts, so we have to represent this as a matrix.
    //            //TODO implement another method which computes the elements directly and compare their speed.
    //            matrix m(2,2);
    //            //TODO check the order, perhaps another order is faster?
    //            if(differentsigns == 2) {
    //                if(nonexistant == ZEROSIGN) {
    //                    m = 1, 1,
    //                        1, -1;
    //                } else if (nonexistant == POSITIVESIGN) {
    //                    m = 1, 1,
    //                        0, -1;
    //                } else {
    //                    m = 1, 1,
    //                        0, 1;
    //                }
    //            } else if(differentsigns == 3) {
    //                m = matrix(3,3);
    //                m = 1, 1, 1,
    //                    0, 1, -1,
    //                    0, 1, 1;
    //            } else {
    //                m = matrix(1,1);
    //                m = 1;
    //            }
    //
    //            // In the first step, we do not have to do more.
    //            if(i == polynomials.size())  {
    //
    //                continue;
    //            }
    //
    //            //In the next step we want to solve mx = b.
    //            matrix b;
    //            matrix x;
    //        }
    //    }

}    // namespace GiNaC

