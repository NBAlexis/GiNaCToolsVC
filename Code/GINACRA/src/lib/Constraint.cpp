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


//#define GINACRA_CONSTRAINT_DEBUG

//#include "Constraint.h"
//#include "utilities.h"

using std::cout;
using std::endl;
using GiNaC::add;
using GiNaC::ex;
using GiNaC::const_iterator;
using GiNaC::is_exactly_a;
using GiNaC::ex_to;
using GiNaC::is_rational_polynomial;
using GiNaC::ZERO_SIGN;

/**
 * Implementation of the class Constraint.
 *
 * @author Ulrich Loup
 * @since 2011-12-05
 * @version 2012-04-17
 */

namespace GiNaCRA
{
    //////////////////////////
    // Con- and destructors //
    //////////////////////////

    ////////////////
    // Operations //
    ////////////////

    bool Constraint::satisfiedBy( const RealAlgebraicPoint& r ) const
    {
        if( mVariables.size() > r.dim() )
            throw invalid_argument( "Dimension of the real algebraic point is less than and the number of variables to be substituted." );
        vector<RealAlgebraicNumberIRPtr> numbersIR = vector<RealAlgebraicNumberIRPtr>( mVariables.size() );    // shall contain only interval-represented components after the preprocessing
        vector<symbol> variablesIR = vector<symbol>( mVariables.size() );    // shall contain the variable indices corresponding to the components of rInterval
        int j = 0;    // the counter of interval representations
        ex pEx = mPoly;
        // Preprocessing: substitute all NumericRepresentation occurrences of r directly in the constraint
        for( unsigned i = 0; i < mVariables.size(); ++i )
        {
            RealAlgebraicNumberNRPtr rNumeric = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( r.at( i ));
            if( rNumeric == 0 )
            {
                numbersIR[j]   = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( r.at( i ));    // safe here
                variablesIR[j] = mVariables.at( i );
                ++j;
                continue;
            }
#ifdef GINACRA_CONSTRAINT_DEBUG
            cout << "Substitute " << mVariables.at( i ) << " with " << *rNumeric << " in " << pEx << "... ";
#endif
            pEx = pEx.subs( mVariables.at( i ) == static_cast<numeric>(*rNumeric) );
#ifdef GINACRA_CONSTRAINT_DEBUG
            cout << pEx << endl;
#endif

        }
        if( is_exactly_a<numeric>( pEx ))
            return mNegated ? GiNaC::sgn( ex_to<numeric>( pEx )) != mSign : GiNaC::sgn( ex_to<numeric>( pEx )) == mSign;
        numbersIR.resize( j );
        variablesIR.resize( j );
#ifdef GINACRA_CONSTRAINT_DEBUG
        cout << "Multi-IR sign check on " << pEx << ": " << endl;
        for( unsigned k = 0; k != numbersIR.size(); ++k )
            cout << "  " << *numbersIR[k] << " vs. " << variablesIR[k] << endl;
#endif
        return mNegated ? RealAlgebraicNumberFactory::evaluateIR( UnivariatePolynomial( pEx, variablesIR.back() ),
                                                                  numbersIR,
                                                                  variablesIR )->
                                                                      sgn() != mSign : RealAlgebraicNumberFactory::evaluateIR( UnivariatePolynomial(
                                                                          pEx, variablesIR.back() ),
                                                                                                                               numbersIR,
                                                                                                                               variablesIR )->
                                                                                                                                   sgn() == mSign;
    }

    ///////////////////////
    // Auxiliary methods //
    ///////////////////////

    const vector<symbol> Constraint::checkVariables( const Polynomial& p, const vector<symbol>& v ) const throw ( invalid_argument )
    {
        if( is_exactly_a<add>( p ))
        {
            for( const_iterator i = p.begin(); i != p.end(); ++i )    // iterate through the summands
            {
                ex coefficient = ex( 1 );
                ex monomial    = ex( 1 );
                GiNaC::isolateByVariables( *i, v, coefficient, monomial );
                if( !is_exactly_a<numeric>( coefficient ))
                    throw invalid_argument( "Given polynomial contains unspecified variables." );
            }
        }
        else
        {
            ex coefficient = ex( 1 );
            ex monomial    = ex( 1 );
            GiNaC::isolateByVariables( p, v, coefficient, monomial );
            if( !is_exactly_a<numeric>( coefficient ))
                throw invalid_argument( "Given polynomial contains unspecified variables." );
        }
        return v;
    }

}    // namespace GiNaCRA

