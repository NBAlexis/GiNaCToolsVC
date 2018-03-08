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


/**
 * @file CAD.cpp
 *
 * @author: Joachim Redies
 * @author: Ulrich Loup
 * @since: 2011-11-12
 * @version: 2012-05-14
 */

//#include "settings.h"
//#include "utilities.h"
//#include "operators.h"
//#include "CAD.h"
//#include "Groebner.h"

using std::sort;
using GiNaC::signedSubresultantsCoefficients;
using GiNaC::ZERO_SIGN;

namespace GiNaCRA
{
    //////////////////////////////////
    // Constructors and Destructors //
    //////////////////////////////////

    CAD::CAD():
        mVariables(),
        mSampleTree(),
        mSampleListIncrements(),
        mEliminationSets(),
        mLiftingPositions(),
        mIsComplete( false ),
        mSetting( CADSettings::getSettings() )
    {
        // initialize root
        mSampleTree.insert( mSampleTree.begin(), RealAlgebraicNumberPtr() );    // empty root node!!
    }

    CAD::CAD( const UnivariatePolynomialSet& s, const vector<symbol>& v, CADSettings setting ):
        mVariables( v ),
        mSampleTree( tree<RealAlgebraicNumberPtr>() ),
        mSampleListIncrements( v.size(), SampleList() ),
        mEliminationSets( v.size() ),
        mLiftingPositions( v.size(), list<unsigned>() ),
        mIsComplete( false ),
        mSetting( setting )
    {
        // settings (need to be set before every other process because of VariableListPool)
        if( mSetting.simplifyByGroebner() )
        {
            MultivariatePolynomialSettings::InitializeGiNaCRAMultivariateMR();
            for( vector<symbol>::const_iterator i = mVariables.begin(); i != mVariables.end(); ++i )
                VariableListPool::addVariable( *i );
        }

        /** A note on the elimination and lifting order: (n be the number of variables)
         * - The (i-1)-th variable (main variable of the current UnivariatePolynomialSet) is eliminated in the i-th step, thus ending up with the variable n-1 in the last elimination set.
         */
        unsigned dim = mVariables.size();
        // initialize the elimination sets
        // normalization: the first main variable shall be the first variable in mVariables (for elimination order)
        UnivariatePolynomialSet currentEliminationSet = UnivariatePolynomialSet();
        mEliminationSets[0]                           = vector<UnivariatePolynomial>();    // position 0 corresponds to 0 variables eliminated
        for( UnivariatePolynomialSet::const_iterator i = s.cbegin(); i != s.cend(); ++i )
        {    // add new polynomials to level 0, unifying their variables
            UnivariatePolynomial pNewVar( *i, mVariables.front() );
            mEliminationSets[0].push_back( pNewVar );
            currentEliminationSet.insert( pNewVar );
        }
        sort( mEliminationSets[0].begin(), mEliminationSets[0].end(), mSetting.mUP_isLess );
        // this loop does nothing if we have univariate polynomials
        for( unsigned i = 1; i != dim; ++i )
        {    // perform elimination of level i-1
            // position i of mEliminationSets corresponds to variable i-1 (current main variable) eliminated in position i-1 of mEliminationSets
            currentEliminationSet = eliminationSet( currentEliminationSet, mVariables[i] );
            vector<UnivariatePolynomial> currentEliminationList( currentEliminationSet.begin(), currentEliminationSet.end() );
            // *** CADSettings: simplifyBySquarefreeing
            if( mSetting.simplifyBySquarefreeing() )
            {
                for( unsigned i = 0; i < currentEliminationList.size(); ++i )
                    currentEliminationList[i] = currentEliminationList[i].sepapart();
            }
            std::sort( currentEliminationList.begin(), currentEliminationList.end(), mSetting.mUP_isLess );
            if( mSetting.simplifyBySquarefreeing() )
                std::unique( currentEliminationList.begin(), currentEliminationList.end() );
            // *** /CADSettings: simplifyBySquarefreeing
            mEliminationSets[i] = vector<UnivariatePolynomial>( currentEliminationList.begin(), currentEliminationList.end() );
        }
        if( mEliminationSets.back().empty() )
            mIsComplete = true;
        // apply heuristics
        // *** CADSettings: simplifyByRootcounting
        if( mSetting.simplifyByRootcounting() )
        {
            vector<UnivariatePolynomial> baseLevel = mEliminationSets.back();
            for( unsigned i = 0; i < baseLevel.size(); )
            {
                if( baseLevel[i].degree() % 2 == 0 )
                {    // there could only be complex roots if the degree is even
                    RationalUnivariatePolynomial p( baseLevel[i] );
                    if( p.countRealRoots() == 0 )
                    {
                        baseLevel.erase( baseLevel.begin() + i );
                        continue;    // do not increase i
                    }
                }
                ++i;
            }
            mEliminationSets.back() = baseLevel;
        }
        // *** CADSettings: /simplifyByRootcounting
        // initialize root
        mSampleTree.insert( mSampleTree.begin(), RealAlgebraicNumberPtr() );    // empty root node!!
        // initialize lifting positions
        for( unsigned i = 0; i < dim; ++i )
        {
            list<unsigned> l = list<unsigned>();
            for( unsigned j = 0; j < mEliminationSets[i].size(); ++j )
                l.push_back( j );
            //            l.sort( isLessInLiftingPositions( mEliminationSets[i], mSetting.mUP_isLess ) );
            mLiftingPositions[i] = l;
        }
    }

    //////////////////////////////
    // Operations on CAD object //
    //////////////////////////////

    void CAD::complete()
    {
        RealAlgebraicPoint r = RealAlgebraicPoint();
        check( vector<Constraint>( 1, Constraint( Polynomial( 1 ), ZERO_SIGN, mVariables )), r );
    }

    inline const vector<RealAlgebraicPoint> CAD::samples()
    {
        unsigned                               dim  = mVariables.size();
        tree<RealAlgebraicNumberPtr>::iterator root = mSampleTree.begin( mSampleTree.head );
        vector<RealAlgebraicPoint>             s    = vector<RealAlgebraicPoint>();
        for( tree<RealAlgebraicNumberPtr>::leaf_iterator leaf = mSampleTree.begin_leaf(); leaf != mSampleTree.end_leaf(); ++leaf )
        {
            RealAlgebraicPoint sample = constructSampleAt( leaf, root );    // for each leaf construct the path by iterating back to the root
            if( sample.dim() == dim )    // discard points which are ill-formed (possible by intermediate nodes which did not yield valid child nodes)
                s.push_back( sample );
        }
        return s;
    }

    bool CAD::check( const vector<Constraint>& constraints, RealAlgebraicPoint& r )
    {
        tree<RealAlgebraicNumberPtr>::iterator root       = mSampleTree.begin( mSampleTree.head );
        int                                    dim        = mVariables.size();
        vector<RealAlgebraicPoint>             sampleList = samples();    // extract all valid samples
        // traverse the current sample tree for satisfying samples
        for( vector<RealAlgebraicPoint>::const_iterator a = sampleList.begin(); a != sampleList.end(); ++a )
        {    // check each sample point
            if( satisfys( *a, constraints ))
            {
                r = *a;
                return true;
            }
        }
        if( mIsComplete )    // there are no more samples producible
            return false;
        // collect all constraints which do have a polynomial in common with the polynomials of this CAD
//        for( vector<UnivariatePolynomial>::const_iterator pol = mEliminationSets[0].begin(); pol != mEliminationSets[0].end(); ++pol )
//
        // if still not complete, construct new samples starting at the base level mVariables.size( )-1
        return liftCheck( root, list<RealAlgebraicNumberPtr>(), dim, list<symbol>(), constraints, r );
    }

    void CAD::printSampleTree( std::ostream& os )
    {
        for( tree<RealAlgebraicNumberPtr>::iterator i = mSampleTree.begin(); i != mSampleTree.end(); ++i )
        {
            for( int d = 0; d != mSampleTree.depth( i ); ++d )
                os << "  [";
            print( *i, os );
            os << endl;
        }
    }

    ///////////////////////////
    // PUBLIC STATIC METHODS //
    ///////////////////////////

    const UnivariatePolynomialSet CAD::eliminationSet( const UnivariatePolynomialSet& polynomials,
                                                       const symbol& nextVariable )
            throw ( invalid_argument )
    {
        if( polynomials.empty() )
            return polynomials;
        UnivariatePolynomialSet eliminatedPolynomials = UnivariatePolynomialSet();
        symbol x                                      = polynomials.variable();
        assert( (ex)nextVariable != x );    // Next variable must not equal the main variable of the set!
        // !PAIRED:
        for( UnivariatePolynomialSet::const_iterator it1 = polynomials.begin(); it1 != polynomials.end(); ++it1 )
            elimination( *it1, nextVariable, eliminatedPolynomials );
        // PAIRED:
        for( UnivariatePolynomialSet::const_iterator pol_it1 = polynomials.begin(); pol_it1 != polynomials.end(); ++pol_it1 )
        {
            UnivariatePolynomialSet::const_iterator it2 = pol_it1;
            ++it2;    // guarantees pol_it1 != it2
            for( ; it2 != polynomials.end(); ++it2 )
                elimination( *pol_it1, *it2, nextVariable, eliminatedPolynomials );
        }
        eliminatedPolynomials = eliminatedPolynomials.makePrimitive();
        eliminatedPolynomials.removeNumbers();
        return eliminatedPolynomials;
    }

    const SampleList CAD::samples( const RationalUnivariatePolynomial& p,
                                   SampleList& currentSamples,
                                   CADSettings settings )
            throw ( invalid_argument )
    {
        return CAD::samples( RealAlgebraicNumberFactory::realRoots( p, settings.mIsolationStrategy ), currentSamples );
    }

    const SampleList CAD::samples( const UnivariatePolynomial& p,
                                   const list<RealAlgebraicNumberPtr>& sample,
                                   const list<symbol>& variables,
                                   SampleList& currentSamples,
                                   CADSettings settings )
            throw ( invalid_argument )
    {
        assert( variables.size() == sample.size() );
#ifdef GINACRA_CAD_DEBUG
        cout << "samples of " << p << " in ";
        for( auto i = variables.begin(); i!= variables.end(); ++i )
            cout << " " << *i;
        cout << " eval. at ";
        for( auto i = sample.begin(); i!= sample.end(); ++i )
            cout << " " << *i;
        cout << endl;
#endif
        vector<RealAlgebraicNumberIRPtr> numbersIR = vector<RealAlgebraicNumberIRPtr>( variables.size() );    // shall contain only interval-represented components after the preprocessing
        vector<symbol> variablesIR = vector<symbol>( variables.size() );    // shall contain the variable indices corresponding to the components of rInterval
        int j = 0;
        ex pEx = p;
        list<RealAlgebraicNumberPtr>::const_iterator sampleValue = sample.begin();
        list<symbol>::const_iterator                 variable    = variables.begin();
        // Preprocessing: substitute all NumericRepresentation occurrences of r directly
        while( variable != variables.end() )
        {
            RealAlgebraicNumberNRPtr rNumeric = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *sampleValue );
            if( rNumeric == 0 )
            {    // store interval representation for later substitution
                numbersIR[j]     = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *sampleValue );    // cast safe here
                variablesIR[j++] = *variable;
            }
            else
                pEx = pEx.subs( *variable == static_cast<numeric>(*rNumeric) );
            ++sampleValue;
            ++variable;
        }
        try
        {    // case: all components of r were rational numeric
#ifdef GINACRA_CAD_DEBUG
            cout << "Use roots of " << pEx << endl;
#endif
            return samples( RationalUnivariatePolynomial( pEx, p.variable() ), currentSamples );
        }
        catch( ... )
        {    // case: there are interval-represented components
            numbersIR.resize( j );
            variablesIR.resize( j );
            // go through the remaining interval components recursively
            --j;
#ifdef GINACRA_CAD_DEBUG
            cout << "Roots of " << pEx << " in ";
            for( auto k = numbersIR.begin(); k != numbersIR.end(); ++k )
                cout << " " << **k;
            cout << ": " << endl;
#endif
            list<RealAlgebraicNumberPtr> roots = RealAlgebraicNumberFactory::realRootsEval( UnivariatePolynomial( pEx, p.variable() ), numbersIR, variablesIR,
                                                                       settings.mIsolationStrategy );
#ifdef GINACRA_CAD_DEBUG
            for( auto k = roots.begin(); k != roots.end(); ++k )
                cout << " " << *k;
            cout << "." << endl;
#endif
            return samples( roots, currentSamples );
        }
    }

    // ATOMIC METHODS //
    ////////////////////

    void CAD::elimination( const UnivariatePolynomial& p, const symbol& variable, UnivariatePolynomialSet& eliminated ) throw ( invalid_argument )
    {
        UnivariatePolynomialSet truncations = CAD::truncation( p );
        for( UnivariatePolynomialSet::const_iterator it2 = truncations.begin(); it2 != truncations.end(); ++it2 )
        {
            eliminated.insert( UnivariatePolynomial( it2->lcoeff(), variable ));
            UnivariatePolynomial it2Diff = it2->diff();
            if( !it2Diff.isZero() )
            {
                vector<ex> subresultants = UnivariatePolynomial::principalSubresultantCoefficients( *it2, it2Diff );
                for( int i = 0; i <= it2->degree() - 2 || i == 0; ++i )
                    for( vector<ex>::const_iterator i = subresultants.begin(); i != subresultants.end(); ++i )
                        eliminated.insert( UnivariatePolynomial( *i, variable ));
            }
        }
    }

    void CAD::elimination( const UnivariatePolynomial& p,
                           const UnivariatePolynomial& q,
                           const symbol& variable,
                           UnivariatePolynomialSet& eliminated )
                           throw ( invalid_argument )
    {
        UnivariatePolynomialSet truncations = CAD::truncation( p );
        for( UnivariatePolynomialSet::const_iterator it1 = truncations.begin(); it1 != truncations.end(); ++it1 )
        {
            vector<ex> subresultants = UnivariatePolynomial::principalSubresultantCoefficients( *it1, q );
            for( vector<ex>::const_iterator i = subresultants.begin(); i != subresultants.end(); ++i )
                eliminated.insert( UnivariatePolynomial( *i, variable ));
        }
    }

    const SampleList CAD::samples( const list<RationalUnivariatePolynomial>& polynomials, SampleList& currentSamples ) throw ( invalid_argument )
    {
        list<RealAlgebraicNumberPtr> roots = list<RealAlgebraicNumberPtr>();
        for( list<RationalUnivariatePolynomial>::const_iterator it = polynomials.begin(); it != polynomials.end(); ++it )
        {
            list<RealAlgebraicNumberPtr> tmp = RealAlgebraicNumberFactory::realRoots( *it );
            roots.insert( roots.end(), tmp.begin(), tmp.end() );
        }
        return CAD::samples( roots, currentSamples );
    }

    ///////////////////////
    // Auxiliary methods //
    ///////////////////////

    inline const RealAlgebraicPoint CAD::constructSampleAt( tree<RealAlgebraicNumberPtr>::iterator node,
                                                            const tree<RealAlgebraicNumberPtr>::iterator& root ) const
    {
        list<RealAlgebraicNumberPtr> v = list<RealAlgebraicNumberPtr>();
        while( node != root )
        {    // proceed from the deepest node up to the root while the children of root represent the last component of the sample point and the deepest node the first
            v.push_back( *node );
            node = mSampleTree.parent( node );
        }
        return RealAlgebraicPoint( v );
    }

    inline const bool CAD::liftCheck( tree<RealAlgebraicNumberPtr>::iterator node,
                                      const list<RealAlgebraicNumberPtr>& sample,
                                      unsigned level,
                                      const list<symbol>& variables,
                                      const vector<Constraint>& constraints,
                                      RealAlgebraicPoint& r )
            throw ( invalid_argument )
    {
        // base level: zero variables left to substitute => evaluate the constraint
        if( level == 0 )
        {
            RealAlgebraicPoint t = RealAlgebraicPoint( sample );
            if( satisfys( t, constraints ))
            {
                r = t;
                return true;
            }
            return false;
        }
        // level > 0: lifting
        --level;    // previous variable will be substituted next
        list<RealAlgebraicNumberPtr> extSample    = list<RealAlgebraicNumberPtr>( sample );    // initial sample point
        list<symbol>                 newVariables = list<symbol>( variables );    // initial variable list
        newVariables.push_front( mVariables[level] );    // the first variable is always the last one lifted

        /*
         * Main loop: performs all operations possible in one level > 0, in particular, 2 phases.
         * Phase 1: Choose a lifting position and construct the corresponding samples.
         * Phase 2: Choose a sample and trigger liftCheck for the next level with the chosen sample.
         */
        bool computeMoreSamples = true;    /// determines whether new samples shall be constructed regardless of other flags
        SampleList currentSamples = SampleList();  /// the current list of samples at this position in the sample tree
        currentSamples.insert(mSampleTree.begin( node ), mSampleTree.end( node ));
        while( true )
        {
            /* Phase 1
             * Lifting position choice and corresponding sample construction.
             */
            unsigned liftingPosition;
            // loop if no samples are present at all or heuristics according to the respective setting demand to continue with a new lifting position, construct new samples
            while( computeMoreSamples || mSampleListIncrements[level].empty()
                    || (mSetting.preferNRSamples() && mSampleListIncrements[level].emptyNR())
                    || (mSetting.preferSamplesByIsRoot() && mSetting.preferNonrootSamples() && mSampleListIncrements[level].emptyNonroot())
                    || (mSetting.preferSamplesByIsRoot() &&!mSetting.preferNonrootSamples() && mSampleListIncrements[level].emptyRoot()))
            {
                if( computeMoreSamples )    // disable blind sample construction
                    computeMoreSamples = false;
                if( !mLiftingPositions[level].empty() )    // choose next lifting position, if possible
                    liftingPosition = mLiftingPositions[level].front();
                else
                    break;
#ifdef GINACRA_CAD_DEBUG
                cout << "New samples for " << mEliminationSets[level][liftingPosition] << " at " << sample << endl << " given {";
                for( auto k = currentSamples.begin(); k != currentSamples.end(); ++k )
                    cout << " " << *k << ( (*k)->isRoot() ? "r" : "" ) << ( (*k)->isNumeric() ? "n" : "" );
                cout << " }:" << endl;
#endif
                SampleList sampls = samples( mEliminationSets[level][liftingPosition], sample, variables, currentSamples );
#ifdef GINACRA_CAD_DEBUG
                for( auto k = sampls.begin(); k != sampls.end(); ++k )
                    cout << " " << *k << ( (*k)->isRoot() ? "r" : "" ) << ( (*k)->isNumeric() ? "n" : "" ) << endl;
                cout << "Current samples are " << endl;
                for( auto k = currentSamples.begin(); k != currentSamples.end(); ++k )
                    cout << " " << *k << ( (*k)->isRoot() ? "r" : "" ) << ( (*k)->isNumeric() ? "n" : "" ) << endl;
#endif
                mSampleListIncrements[level].insert( sampls );
                mLiftingPositions[level].pop_front();    // discard lifting position just used for sample construction
                if( mSetting.preferSamplesByIsRoot() || mSetting.preferNRSamples() )
                {
                    pair<SampleSimplification, bool> simplification = mSampleListIncrements[level].simplify();
                    if( simplification.second )
                    { // simplification took place => replace all
                        for( SampleSimplification::const_iterator i = simplification.first.begin(); i != simplification.first.end(); ++i )
                        {
                            SampleList::iterator simplEntry = std::lower_bound( currentSamples.begin( ), currentSamples.end( ), i->first, RealAlgebraicNumberFactory::less );
                            if( simplEntry != currentSamples.end( ) )
                                *simplEntry = i->second;
                            // it could happen that the node is not yet in the list of children
                        }
                    }
                }
            }
#ifdef GINACRA_CAD_DEBUG
            if( !mLiftingPositions.empty() )
                cout << "Current lifting position in level " << level << ": " << mEliminationSets[level][liftingPosition] << endl;
            else
                cout << "Reached final lifting position in level " << level << "." << endl;
            cout << "Current sample point in level " << level << ": " << sample << endl;
            //            cout << "Current sample list increment in level " << level << " has NRs: " << !mSampleListIncrements[level].emptyNR() << endl;
            //            cout << "Current sample list increment in level " << level << " has IRs: " << !mSampleListIncrements[level].emptyIR() << endl;
            if( mSampleListIncrements[level].empty() )
                cout << "Current sample list increment in level " << level << " empty.";
            else
            {
                cout << "Current next() of sample list increment in level " << level << ": ";
                print( mSampleListIncrements[level].next() );
            }
            cout << endl;
            cout << "Sample list increment for lifting position " << level << ": " << endl;
            for( SampleList::const_iterator s = mSampleListIncrements[level].begin(); s != mSampleListIncrements[level].end(); ++s )
                print( *s, cout << " " );
            cout << endl;
#endif

            /* Phase 2
             * Lifting of the current level.
             */
            while( !mSampleListIncrements[level].empty() )    // iterate through all samples found by the next() method
            {
                tree<RealAlgebraicNumberPtr>::iterator newNode;

                /*
                 * Sample choice
                 */
                RealAlgebraicNumberPtr newSample;
                if( mSetting.preferNRSamples() )
                {
                    if( mSampleListIncrements[level].emptyNR() &&!mLiftingPositions[level].empty() )
                    {
                        computeMoreSamples = true;
                        break;    // construct new samples until there are lifting positions
                    }
                    // otherwise take also IR samples (as implemented in nextNR
                    newSample = mSampleListIncrements[level].nextNR();
                }
                else if( mSetting.preferSamplesByIsRoot() )
                {
                    if( mSetting.preferNonrootSamples() )
                    {
                        if( mSampleListIncrements[level].emptyNonroot() &&!mLiftingPositions[level].empty() )
                        {
                            computeMoreSamples = true;
                            break;    // construct new samples until there are lifting positions
                        }
                        // otherwise take also IR samples (as implemented in nextNonroot
                        newSample = mSampleListIncrements[level].nextNonroot();
                    }
                    else
                    {
                        if( mSampleListIncrements[level].emptyRoot() &&!mLiftingPositions[level].empty() )
                        {
                            computeMoreSamples = true;
                            break;    // construct new samples until there are lifting positions
                        }
                        // otherwise take also IR samples (as implemented in nextNonroot
                        newSample = mSampleListIncrements[level].nextRoot();
                    }
                }
                else    // use FCFS
                    newSample = mSampleListIncrements[level].next();

                /*
                 * Sample storage
                 */

                newNode = std::lower_bound( mSampleTree.begin( node ), mSampleTree.end( node ), newSample, RealAlgebraicNumberFactory::less );
                if( newNode == mSampleTree.end( node ) ) // the new sample is either contained in the children nor any child is greater than it
                    newNode = mSampleTree.append_child( node, newSample );
                else if( RealAlgebraicNumberFactory::equal( *newNode, newSample ) ) // && newNode != mSampleTree.end( node )
                    newNode = mSampleTree.replace( newNode, newSample );    // update existing data in tree (could be helpful in case an interval representation was refined or converted to a numeric)
                else // newNode is a child being greater than newSample
                    newNode = mSampleTree.insert( newNode, newSample );

                extSample.push_front( newSample );    // insert at the first position in order to meet the correct variable order

                // Lifting

                if( liftCheck( newNode, extSample, level, newVariables, constraints, r ))
                    return true;    // current lifting position remains in mLiftingPositions.front()

                /*
                 * Sample pop if lifting unsuccessful
                 */
                if( mSetting.preferNRSamples() )
                    mSampleListIncrements[level].popNR();    // remove sample from increment list because it was completely lifted (pop() uses heuristics already used in next())
                else if( mSetting.preferSamplesByIsRoot() )
                {
                    if( mSetting.preferNonrootSamples() )
                        mSampleListIncrements[level].popNonroot();
                    else
                        mSampleListIncrements[level].popRoot();
                }
                else
                    mSampleListIncrements[level].pop();

                extSample.pop_front();    // clean sample point component again
            }
            if( mLiftingPositions[level].empty() )
                break;    // all samples tried and no lifting possible any more
        }
        // restore lifting positions
        list<unsigned> l = list<unsigned>();
        for( unsigned j = 0; j < mEliminationSets[level].size(); ++j )
            l.push_back( j );
        mLiftingPositions[level] = l;

        if( sample.empty() )    // no satisfying samples found in initial level => complete CAD was computed
            mIsComplete = true;    // store completeness result
        return false;
    }

    inline const bool CAD::satisfys( const RealAlgebraicPoint& r, const vector<Constraint>& constraints ) const
    {
#ifdef GINACRA_CAD_DEBUG
        cout << "Checking whether " << r << " satisfies ";
        for( vector<Constraint>::const_iterator i = constraints.begin(); i != constraints.end(); ++i )
            cout << *i << " ";
        cout << endl;
#endif
        for( vector<Constraint>::const_iterator c = constraints.begin(); c != constraints.end(); ++c )
        {
            if( !c->satisfiedBy( r ))
                return false;
        }
        return true;
    }
    //////////////////////////////
    // STATIC AUXILIARY METHODS //
    //////////////////////////////

    const SampleList CAD::samples( const list<RealAlgebraicNumberPtr>& roots, SampleList& currentSamples ) throw ( invalid_argument )
    {
        SampleList newSampleSet = SampleList();    // new samples to return - roots and maybe intermediate points
        if( roots.empty() )
        { // if there is no real root any value results in a positive sign, choose ZERO by default
            if( currentSamples.empty() )
            {
                RealAlgebraicNumberPtr r = RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( GiNaC::ZERO, false ) );
                newSampleSet.insert( r );
                currentSamples.insert( r );
            }
//            else: regardless of where the lifting position is evaluated, it has the same sign, so any point in currentSamples would be appropriate
            return newSampleSet;
        }
        for( list<RealAlgebraicNumberPtr>::const_iterator i = roots.begin(); i != roots.end(); ++i )
        {
            pair<SampleList::iterator, bool> insertValue = currentSamples.insert( *i );    // now the intervals of possible interval representations are disjoint (by equality checks)
            if( !insertValue.second )
            {    // value already in the list
                if( !(*insertValue.first)->isRoot() )
                {    // the new root is already contained, but only as sample value => take the root and start sample construction from scratch
                    currentSamples.remove( insertValue.first );
                    assert( (*i)->isRoot() );
                    insertValue = currentSamples.insert( *i );
                }
                else if( !(*insertValue.first)->isNumeric() && (*i)->isNumeric() )
                { // there is already an interval-represented root with the same value present and it can be replaced by a numeric
                    currentSamples.remove( insertValue.first );
                    insertValue = currentSamples.insert( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( (*i)->value(), true ) ) );
                }
                else
                    continue;
            }
            SampleList currentSamplesIncrement = SampleList();    // local set storing the elements which shall be added to currentSampleSet and newSampleSet in the end

            /** Situation: One, next or previous, has to be a root (assumption) or we meet one of the outmost positions.
             * --------|-------------------|-----------------|---
             *    previous        insertValue.first         next
             *     (root?)              (root)            (root?)
             */
            //
            // next: right neighbor
            SampleList::iterator neighbor = SampleList::iterator( insertValue.first );
            ++neighbor;    // -> next (safe here, but need to check for end() later)
            if( neighbor == currentSamples.end() )    // rightmost position
            {    // insert one rightmost sample (by adding 1 or taking the rightmost interval bound)
                RealAlgebraicNumberNRPtr insertValueNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *insertValue.first );
                if( insertValueNR != 0 )
                {
                    currentSamplesIncrement.insert( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( static_cast<numeric>(*insertValueNR)
                                                                                                                           + numeric( 1 ), false )));    // add as a no root
                }
                else    // interval representation
                    currentSamplesIncrement.insert( RealAlgebraicNumberPtr(
                        new RealAlgebraicNumberNR(
                            std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *insertValue.first )->interval().right(), false )));    // add as a no root
            }
            else if( (*neighbor)->isRoot() )
            {    // sample between neighbor and insertValue.first needed and will be added to newSampleSet
                RealAlgebraicNumberNRPtr insertValueNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *insertValue.first );
                RealAlgebraicNumberNRPtr neighborNR    = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *neighbor );
                if( insertValueNR != 0 )
                {
                    if( neighborNR != 0 )
                        currentSamplesIncrement.insert( RealAlgebraicNumberPtr(
                            new RealAlgebraicNumberNR( OpenInterval( *insertValueNR, *neighborNR ).sampleFast(), false )));    // add as no root
                    else
                        currentSamplesIncrement.insert( RealAlgebraicNumberPtr(
                            new RealAlgebraicNumberNR(
                                std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *neighbor )->interval().left(), false )));    // add as no root
                }
                else    // interval representation, take right bound of insertValue.first which must be strictly between insertValue.first and neighbor
                    currentSamplesIncrement.insert( RealAlgebraicNumberPtr(
                        new RealAlgebraicNumberNR(
                            std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *insertValue.first )->interval().right(), false )));    // add as no root
            }
            //
            // previous: left neighbor
            neighbor = SampleList::iterator( insertValue.first );
            if( neighbor == currentSamples.begin() )    // leftmost position
            {    // insert one leftmost sample (by subtracting 1 or taking the leftmost interval bound)
                RealAlgebraicNumberNRPtr insertValueNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *insertValue.first );
                if( insertValueNR != 0 )
                    currentSamplesIncrement.insert( RealAlgebraicNumberPtr( new RealAlgebraicNumberNR( static_cast<numeric>(*insertValueNR)
                                                                                                                           - numeric( 1 ), false )));    // add as no root
                else    // interval representation
                    currentSamplesIncrement.insert( RealAlgebraicNumberPtr(
                        new RealAlgebraicNumberNR(
                            std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *insertValue.first )->interval().left(), false )));    // add as no root
            }
            else
            {
                --neighbor;    // now neighbor is the left bound (can be safely determined now)
                if( (*neighbor)->isRoot() )
                {    // sample between neighbor and insertValue.first needed and will be added to newSampleSet
                    RealAlgebraicNumberNRPtr insertValueNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *insertValue.first );
                    RealAlgebraicNumberNRPtr neighborNR    = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *neighbor );
                    if( insertValueNR != 0 )
                    {
                        if( neighborNR != 0 )
                            currentSamplesIncrement.insert( RealAlgebraicNumberPtr(
                                new RealAlgebraicNumberNR( OpenInterval( *neighborNR, *insertValueNR ).sampleFast(), false )));    // add as no root
                        else
                            currentSamplesIncrement.insert( RealAlgebraicNumberPtr(
                                new RealAlgebraicNumberNR(
                                    std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *neighbor )->interval().right(), false )));    // add as no root
                    }
                    else    // interval representation, take left bound of insertValue.first which must be strictly between insertValue.first and neighbor
                        currentSamplesIncrement.insert( RealAlgebraicNumberPtr(
                            new RealAlgebraicNumberNR(
                                std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( *insertValue.first )->interval().left(), false )));    // add as no root
                }
            }
            newSampleSet.insert( *insertValue.first );    // add the root to new samples (with root switch on)
            newSampleSet.insert( currentSamplesIncrement.begin(), currentSamplesIncrement.end() );
            currentSamples.insert( currentSamplesIncrement.begin(), currentSamplesIncrement.end() );
        }
        return newSampleSet;
    }

    const UnivariatePolynomialSet CAD::truncation( const UnivariatePolynomial& p )
    {
        UnivariatePolynomialSet ret;
        ret.insert( p );
        UnivariatePolynomial truncation( p );
        while( !truncation.isConstant() )
        {
            truncation = truncation.trunc();
            ret.insert( truncation );
        }
        return ret;
    }

    const UnivariatePolynomialSet CAD::truncation( const UnivariatePolynomialSet& P )
    {
        UnivariatePolynomialSet ret;
        for( UnivariatePolynomialSet::const_iterator it1 = P.begin(); it1 != P.end(); ++it1 )
        {
            UnivariatePolynomialSet M = truncation( *it1 );
            for( UnivariatePolynomialSet::const_iterator it2 = M.begin(); it2 != M.end(); ++it2 )
                ret.insert( *it2 );
        }
        return ret;
    }

}
