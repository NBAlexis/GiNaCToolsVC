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


#include <list>
#include <assert.h>
#include <stdexcept>
#include <locale>
#include <vector>
//
//#include "MultivariatePolynomialMR.h"
//#include "MultivariateTermMR.h"
//#include "VariableListPool.h"

using GiNaC::ex;
using GiNaC::add;
using GiNaC::const_iterator;
using GiNaC::is_exactly_a;

namespace GiNaCRA
{
    bool operator !=( const MonomMRCompare& m1, const MonomMRCompare& m2 )
    {
        return m1.GetMonomOrdering() != m2.GetMonomOrdering();
    }

    MultivariatePolynomialMR::MultivariatePolynomialMR():
        mCmp(),
        mTerms()    /* , mpVarList(VariableListPool::getPtToStdVarList()), mpParList(VariableListPool::getPtToStdParList()) */
    {}

    MultivariatePolynomialMR::MultivariatePolynomialMR( const MonomMRCompare& comp ):
        mCmp( comp ),
        mTerms( comp )    /* , mpVarList(VariableListPool::getPtToStdVarList()), mpParList(VariableListPool::getPtToStdParList()) */
    {}

    MultivariatePolynomialMR::MultivariatePolynomialMR( const MultivariateTermMR& t1, const MonomMRCompare& comp ):
        mCmp( comp ),
        mTerms( mCmp )    /* , mpVarList(VariableListPool::getPtToStdVarList()), mpParList(VariableListPool::getPtToStdParList()) */
    {
        mTerms.insert( t1 );
    }

    MultivariatePolynomialMR::MultivariatePolynomialMR( const MultivariateTermMR& t1, const MultivariateTermMR& t2, const MonomMRCompare& comp ):
        mCmp( comp ),
        mTerms( mCmp )    /* , mpVarList(VariableListPool::getPtToStdVarList()), mpParList(VariableListPool::getPtToStdParList()) */
    {
        mTerms.insert( t1 );
        mTerms.insert( t2 );
    }

    MultivariatePolynomialMR::MultivariatePolynomialMR( sMT_It begin, sMT_It last, const MonomMRCompare& comp ):
        mCmp( comp ),
        mTerms( begin, last, comp )    /* , mpVarList(VariableListPool::getPtToStdVarList()), mpParList(VariableListPool::getPtToStdParList()) */
    {}

    MultivariatePolynomialMR::MultivariatePolynomialMR( sMT_It begin1, sMT_It last1, sMT_It begin2, sMT_It last2, const MonomMRCompare& comp ):
        mCmp( comp ),
        mTerms( comp )    /* , mpVarList(VariableListPool::getPtToStdVarList()), mpParList(VariableListPool::getPtToStdParList()) */
    {
        sMT_It inputIt       = mTerms.begin();
        MonomOrderingFc less = mCmp.GetMonomOrdering();
        while( begin1 != last1 )
        {
            if( begin2 == last2 )
            {
                mTerms.insert( begin1, last1 );
            }
            if( less( *begin1, *begin2 ))
            {
                inputIt = mTerms.insert( inputIt, *begin1 );
                ++begin1;
                continue;
            }    // else if
            if( less( *begin1, *begin2 ))
            {
                inputIt = mTerms.insert( inputIt, *begin2 );
                ++begin2;
                continue;
            }    // else (equal)
            inputIt = mTerms.insert( inputIt, MultivariateTermMR( *begin1, begin1->getCoeffExpr() + begin2->getCoeffExpr() ));
            ++begin1;
            ++begin2;
        }
        mTerms.insert( begin2, last2 );
    }

    MultivariatePolynomialMR::MultivariatePolynomialMR( const GiNaC::ex& expr, const MonomMRCompare& cmp ):
        mCmp( cmp ),
        mTerms( cmp )
    {
        ex expression = expr.expand();
        GiNaC::lst          list = GiNaC::lst();
        std::vector<symbol> vars = VariableListPool::getVariables();
        for( std::vector<symbol>::const_iterator it = vars.begin(); it != vars.end(); ++it )
        {
            list.append( *it );
        }
        if( !expression.is_polynomial( list ))
            throw std::invalid_argument( "Argument is not a polynomial" );
        if( is_exactly_a<GiNaC::add>( expression ))    // GiNaC::add because of overriding the name "add" by the current function
        {
            for( const_iterator i = expression.begin(); i != expression.end(); ++i )    // iterate through the summands
            {
                if( GiNaC::is_constant( *i, vars ))
                {    // polynomial is constant in the current list of variables, so is a coefficient with the 1 monomial
                    mTerms.insert( MultivariateTermMR( *i ));
                }
                else if( GiNaC::is_exactly_a<GiNaC::mul>( *i ))    // GiNaC::mul because of overriding the name "mul" by the current function
                {    // polynomial is just a product
                    GiNaC::ex                                   coeff = GiNaC::ex( 1 );

                    std::vector<std::pair<unsigned, unsigned> > mon   = std::vector<std::pair<unsigned, unsigned> >();
                    for( const_iterator j = i->begin(); j != i->end(); ++j )    // iterate through the possible powers
                    {
                        std::vector<symbol>::const_iterator s   = vars.begin();
                        unsigned                            ind = 0;
                        for( ; s != vars.end(); ++s )    // only tak)e symbols given in the list (all other things are coefficient)
                        {
                            if( j->degree( *s ) > 0 )
                            {
                                mon.push_back( std::pair<unsigned, unsigned>( ind, j->degree( *s )));
                                break;
                            }
                            ++ind;
                        }
                        if( s == vars.end() )
                        {    // current power is not build upon a variable, so it belongs to the coefficient
                            coeff = coeff * *j;
                            break;
                        }
                    }
                    mTerms.insert( MultivariateTermMR( MultivariateMonomialMR( mon.begin(), mon.end() ), coeff ));
                }
                else if( GiNaC::is_exactly_a<GiNaC::power>( *i ) || GiNaC::is_exactly_a<symbol>( *i ))
                {
                    std::vector<symbol>::const_iterator s   = vars.begin();
                    unsigned                            ind = 0;
                    for( ; s != vars.end(); ++s )    // only take symbols given in the list (all other things are coefficient)
                    {
                        if( i->degree( *s ) > 0 )
                        {
                            mTerms.insert( MultivariateTermMR( MultivariateMonomialMR( ind, (unsigned)(i->degree( *s )))));
                            break;
                        }
                        ++ind;
                    }
                    if( s == vars.end() )
                    {
                        mTerms.insert( MultivariateTermMR( *i ));
                    }
                }
                else if( is_exactly_a<numeric>( *i ))
                    mTerms.insert( MultivariateTermMR( *i ));

                else if( i->is_zero() )
                    ;
            }

        }
        else
        {
            if( GiNaC::is_constant( expr, vars ))
            {    // polynomial is constant in the current list of variables, so is a coefficient with the 1 monomial
                mTerms.insert( MultivariateTermMR( expr ));
            }
            else if( GiNaC::is_exactly_a<GiNaC::mul>( expr ))    // GiNaC::mul because of overriding the name "mul" by the current function
            {    // polynomial is just a product
                GiNaC::ex                                   coeff = GiNaC::ex( 1 );

                std::vector<std::pair<unsigned, unsigned> > mon   = std::vector<std::pair<unsigned, unsigned> >();
                for( const_iterator j = expr.begin(); j != expr.end(); ++j )    // iterate through the possible powers
                {
                    std::vector<symbol>::const_iterator s   = vars.begin();
                    unsigned                            ind = 0;
                    for( ; s != vars.end(); ++s )    // only tak)e symbols given in the list (all other things are coefficient)
                    {
                        if( j->degree( *s ) > 0 )
                        {
                            mon.push_back( std::pair<unsigned, unsigned>( ind, j->degree( *s )));
                            break;
                        }
                        ++ind;
                    }
                    if( s == vars.end() )
                    {    // current power is not build upon a variable, so it belongs to the coefficient
                        coeff = coeff * *j;
                        break;
                    }
                }
                mTerms.insert( MultivariateTermMR( MultivariateMonomialMR( mon.begin(), mon.end() ), coeff ));
            }
            else if( GiNaC::is_exactly_a<GiNaC::power>( expr ) || GiNaC::is_exactly_a<symbol>( expr ))
            {
                std::vector<symbol>::const_iterator s   = vars.begin();
                unsigned                            ind = 0;
                for( ; s != vars.end(); ++s )    // only take symbols given in the list (all other things are coefficient)
                {
                    if( expr.degree( *s ) > 0 )
                    {
                        mTerms.insert( MultivariateTermMR( MultivariateMonomialMR( ind, (unsigned)(expr.degree( *s )))));
                        break;
                    }
                    ++ind;
                }
                if( s == vars.end() )
                {
                    mTerms.insert( MultivariateTermMR( expr ));
                }
            }
            else if( is_exactly_a<numeric>( expr ))
                mTerms.insert( MultivariateTermMR( expr ));

            else if( expr.is_zero() )
                ;
        }

        //if(expr.is_polynomial())
    }

    GiNaC::ex MultivariatePolynomialMR::toEx() const
    {
        GiNaC::ex expr = GiNaC::ex( 0 );
        for( sMT_cIt it = mTerms.begin(); it != mTerms.end(); ++it )
        {
            expr += it->toEx();
        }
        return expr;
    }

    bool operator ==( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 )
    {
        //TODO what to do with different ordering?!
        if( p1.mTerms.size() != p2.mTerms.size() )
            return false;
        return std::equal( p1.mTerms.begin(), p1.mTerms.end(), p2.mTerms.begin() );
    }

    bool operator !=( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 )
    {
        //TODO what to do with different ordering?!
        if( p1.mTerms.size() != p2.mTerms.size() )
            return true;
        return !std::equal( p1.mTerms.begin(), p1.mTerms.end(), p2.mTerms.begin() );
    }

    const MultivariatePolynomialMR operator +( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 )
    {
        //TODO what if not equal polynomialordering! It is correct although very slow.
        //return MultivariatePolynomialMR(p1.mTerms.begin(), p1.mTerms.end(), p2.mTerms.begin(), p2.mTerms.end(), p1.mCmp);
        MultivariatePolynomialMR newPol( p1.mCmp );
        sMT_It inputIt       = newPol.mTerms.begin();
        MonomOrderingFc less = p1.mCmp.GetMonomOrdering();

        sMT_It p1it          = p1.mTerms.begin();
        sMT_It p2it          = p2.mTerms.begin();
        sMT_It p1end         = p1.mTerms.end();
        sMT_It p2end         = p2.mTerms.end();

        while( p1it != p1end )
        {
            if( p2it == p2end )
            {
                newPol.mTerms.insert( p1it, p1end );
                return newPol;
            }
            if( p1it->hasEqualExponents( *p2it ))
            {
                ex newCoeff = p1it->getCoeffExpr() + p2it->getCoeffExpr();
                if( newCoeff != 0 )
                {
                    inputIt = newPol.mTerms.insert( inputIt, MultivariateTermMR( *p1it, newCoeff ));
                }
                ++p1it;
                ++p2it;
                continue;
            }
            if( less( *p1it, *p2it ))
            {
                inputIt = newPol.mTerms.insert( inputIt, *(p1it++) );
                //++p1it;
                continue;
            }    // else if
            else
            {    // (less(*p1it, *p2it)) {
                inputIt = newPol.mTerms.insert( inputIt, *(p2it++) );
                //++p2it;
                continue;
            }    // else (equal)
        }
        newPol.mTerms.insert( p2it, p2end );
        return newPol;

    }

    const MultivariatePolynomialMR operator +( const MultivariatePolynomialMR& p1, const MultivariateTermMR& t1 )
    {
        MultivariatePolynomialMR newPol = MultivariatePolynomialMR( p1 );
        std::pair<sMT_It, bool> ret = newPol.mTerms.insert( t1 );
        if( ret.second )
            return newPol;
            //the same monomial already exists.
            //we remove the old one and construct a new term.

        //prepare a pointer to the location where the next should be inserted after.
        sMT_It newIt = ret.first;
        --newIt;

        //calculate the coeff
        ex newCoeff = t1.getCoeffExpr() + ret.first->getCoeffExpr();

        newPol.mTerms.erase( ret.first );

        //If the new coefficient is zero, we do not add the term.
        if( newCoeff == 0 )
        {
            return newPol;
        }

        newPol.mTerms.insert( newIt, MultivariateTermMR( t1, newCoeff ));
        return newPol;
    }

    const MultivariatePolynomialMR operator +( const MultivariateTermMR& t1, MultivariatePolynomialMR& p1 )
    {
        return p1 + t1;
    }

    const MultivariatePolynomialMR operator +( const MultivariatePolynomialMR& p1, const MultivariateMonomialMR& m1 )
    {
        MultivariatePolynomialMR newPol = MultivariatePolynomialMR( p1 );
        std::pair<sMT_It, bool> ret = newPol.mTerms.insert( m1 );
        if( ret.second )
            return newPol;
            //the same monomial already exists.
            //we remove the old one and construct a new term.

        //prepare a pointer to the location where the next should be inserted after.
        sMT_It newIt = ret.first;
        --newIt;

        //the new term has coefficient 0?
        if( ret.first->getCoeffExpr() == -1 )
        {
            newPol.mTerms.erase( ret.first );
            return newPol;
        }

        //calculate the coefficient
        ex newCoeff = 1 + ret.first->getCoeffExpr();

        newPol.mTerms.erase( ret.first );
        newPol.mTerms.insert( newIt, MultivariateTermMR( m1, newCoeff ));

        return newPol;
    }

    const MultivariatePolynomialMR operator +( const MultivariateMonomialMR& m1, const MultivariatePolynomialMR& p1 )
    {
        return p1 + m1;
    }

    const MultivariatePolynomialMR operator -( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 )
    {
        MultivariatePolynomialMR newPol( p1.mCmp );
        sMT_It inputIt       = newPol.mTerms.begin();
        MonomOrderingFc less = p1.mCmp.GetMonomOrdering();

        sMT_It p1it          = p1.mTerms.begin();
        sMT_It p2it          = p2.mTerms.begin();
        sMT_It p1end         = p1.mTerms.end();
        sMT_It p2end         = p2.mTerms.end();

        while( p1it != p1end )
        {
            if( p2it == p2end )
            {
                newPol.mTerms.insert( p1it, p1end );
                return newPol;
            }

            if( p1it->hasEqualExponents( *p2it ))
            {
                ex newCoeff = p1it->getCoeffExpr() - p2it->getCoeffExpr();
                if( newCoeff != 0 )
                {
                    inputIt = newPol.mTerms.insert( inputIt, MultivariateTermMR( *p1it, newCoeff ));
                }
                ++p1it;
                ++p2it;
                continue;
            }
            if( less( *p1it, *p2it ))
            {
                inputIt = newPol.mTerms.insert( inputIt, *(p1it) );
                ++p1it;
                continue;
            }    // else if
            else
            {    // if (less(*p2it, *p1it)) {
                inputIt = newPol.mTerms.insert( inputIt, (p2it->negate()));
                ++p2it;
                continue;
            }    // else (equal)

        }
        for( ; p2it != p2end; ++p2it )
        {
            inputIt = newPol.mTerms.insert( inputIt, p2it->negate() );
        }
        return newPol;
    }

    const MultivariatePolynomialMR operator -( const MultivariatePolynomialMR& p1 )
    {
        MultivariatePolynomialMR newPol = MultivariatePolynomialMR( p1.mCmp );
        sMT_It inputloc                 = newPol.mTerms.begin();
        for( sMT_It it = p1.mTerms.begin(); it != p1.mTerms.end(); ++it )
        {
            inputloc = newPol.mTerms.insert( inputloc, it->negate() );
        }
        return newPol;

    }
    //
    //    const MultivariatePolynomialMR operator *( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 )
    //    {
    //        // MultivariatePolynomialMR 
    //    }

    const MultivariatePolynomialMR operator *( const MultivariatePolynomialMR& p1, const MultivariateTermMR& t1 )
    {
        MultivariatePolynomialMR newPol( p1.mCmp );
        sMT_cIt end1    = p1.mTerms.end();
        sMT_It inputloc = newPol.mTerms.begin();
        for( sMT_cIt it = p1.mTerms.begin(); it != end1; ++it )
        {
            inputloc = newPol.mTerms.insert( inputloc, (*it) * t1 );
        }
        return newPol;
    }

    const MultivariatePolynomialMR operator *( const MultivariateTermMR& t1, MultivariatePolynomialMR& p1 )
    {
        return p1 * t1;
    }

    const MultivariatePolynomialMR operator *( const MultivariatePolynomialMR& p1, const MultivariateMonomialMR& m1 )
    {
        MultivariatePolynomialMR newPol( p1.mCmp );
        sMT_cIt end1    = p1.mTerms.end();
        sMT_It inputloc = newPol.mTerms.begin();
        for( sMT_cIt it = p1.mTerms.begin(); it != end1; ++it )
        {
            inputloc = newPol.mTerms.insert( inputloc, (*it) * m1 );
        }
        return newPol;
    }

    const MultivariatePolynomialMR operator *( const MultivariateMonomialMR& m1, const MultivariatePolynomialMR& p1 )
    {
        return p1 * m1;
    }

    std::ostream& operator <<( std::ostream& os, const MultivariatePolynomialMR& rhs )
    {
        for( sMT_rIt it = rhs.mTerms.rbegin(); it != rhs.mTerms.rend(); ++it )
        {
            os << *it << " ";
        }
        return os;
    }

    const MultivariatePolynomialMR MultivariatePolynomialMR::SPol( const MultivariatePolynomialMR& p1, const MultivariatePolynomialMR& p2 )
    {
        //std::cout << "p1:" << p1 << "\np2:" << p2 << std::endl; 
        if( p1.getMonomOrder() != p2.getMonomOrder() )
        {
            throw std::invalid_argument( "Different orderings are not yet supported" );
        }
        if( p1.nrOfTerms() == 1 && p2.nrOfTerms() == 1 )
        {
            return MultivariatePolynomialMR( p1.mCmp );
        }
        else if( p1.nrOfTerms() == 1 )
        {
            return -(p2.lterm().lcmdivt( p1.lmon() ) * p2.truncLT());
        }
        else if( p2.nrOfTerms() == 1 )
        {
            return (p1.lterm().lcmdivt( p2.lmon() ) * p1.truncLT());
        }
        //std::cout << p2.lterm().lcmdivt(p1.lmon()) << std::endl;
        //std::cout << p2.truncLT();
        //   std::cout << (p2.truncLT().multiply(p2.lterm().lcmdivt(p1.lmon()))) << std::endl;
        return p1.truncLT().multiply( p1.lterm().lcmdivt( p2.lmon() )) - (p2.truncLT().multiply( p2.lterm().lcmdivt( p1.lmon() )));
    }

    MultivariatePolynomialMR MultivariatePolynomialMR::CalculateRemainder( std::list<MultivariatePolynomialMR>::const_iterator ideallistBegin,
                                                                           std::list<MultivariatePolynomialMR>::const_iterator ideallistEnd ) const
    {
        MultivariatePolynomialMR* p = new MultivariatePolynomialMR( *this );
        MultivariatePolynomialMR* r = new MultivariatePolynomialMR( MonomMRCompare( mCmp ));

        while( !p->isZero() )
        {
            //std::cout << "a" << std::endl;
            std::list<MultivariatePolynomialMR>::const_iterator fIt        = ideallistBegin;
            bool                                                divOccured = false;
            while( !divOccured && fIt != ideallistEnd )
            {
                //MultivariatePolynomialMR temp(*p);
                std::pair<MultivariateTermMR, bool> red = p->lterm().divby( fIt->lterm() );

                if( red.second )
                {
                    *p         = (*p) - (fIt->multiply( red.first ));
                    divOccured = true;
                }
                else
                {
                    ++fIt;
                }
            }
            //std::cout << "b" << std::endl;
            if( !divOccured )
            {
                r->mTerms.insert( p->lterm() );
                p->mTerms.erase( p->lterm() );
            }
        }
        const MultivariatePolynomialMR ret = MultivariatePolynomialMR( *r );
        delete p;
        return ret;
    }

    MultivariatePolynomialMR MultivariatePolynomialMR::normalized()
    {
        MultivariatePolynomialMR n = MultivariatePolynomialMR( mCmp );
        ex lc                      = this->lcoeff();
        for( std::set<MultivariateTermMR, MonomMRCompare>::iterator i = mTerms.begin(); i != mTerms.end(); ++i )
            n.mTerms.insert( i->divide( lc ));
        return n;
    }
}
