/*
 *  GiNaCRA - GiNaC Real Algebra package
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
 * @file CAD.h
 * @author Ulrich Loup
 * @version 2012-05-19
 */

#ifndef GINACRA_CAD_H
#define GINACRA_CAD_H

//#define GINACRA_CAD_DEBUG

#include <unordered_map>
//
//#include "tree.h"
//#include "settings.h"
//#include "Constraint.h"
//#include "UnivariatePolynomialSet.h"
//#include "RealAlgebraicNumber.h"
//#include "RealAlgebraicNumberFactory.h"
//#include "RealAlgebraicPoint.h"

namespace GiNaCRA
{
    ///////////
    // TYPES //
    ///////////

    typedef std::unordered_map<RealAlgebraicNumberPtr, RealAlgebraicNumberPtr, RealAlgebraicNumberPtrHasher> SampleSimplification;

    /**
     * Type for a sorted list of RealAlgebraicNumberPtr.
     *
     * @author Ulrich Loup
     * @since 2011-12-19
     *
     */
    struct GINACRA_API SampleList:
        public std::list<RealAlgebraicNumberPtr>
    {
        private:
            /// Queue containing all samples in the order of their insertion
            list<RealAlgebraicNumberPtr> mQueue;
            /// Pair having in the first component one queue containing all numerically represented samples in the order of their insertion, and
            /// in the second component one queue containing all interval-represented samples in the order of their insertion.
            pair<list<RealAlgebraicNumberNRPtr>, list<RealAlgebraicNumberIRPtr> > mNRsIRs;
            /// Pair having in the first component one queue containing all non-root samples in the order of their insertion, and
            /// in the second component one queue containing all root samples in the order of their insertion.
            pair<list<RealAlgebraicNumberPtr>, list<RealAlgebraicNumberPtr> > mNonrootsRoots;

        public:

            /**
             * Inserts an element into the sorted list at the correct position according to the order.
             * @param r RealAlgebraicNumberPtr to be inserted
             * @return a pair, with its member <code>pair::first</code> set to an iterator pointing to either the newly inserted element or to the element that already had its same value in the set.
             * The <code>pair::second</code> element in the pair is set to <code>true</code> if a new element was inserted or <code>false</code> if an element with the same value existed.
             * If a numeric representation is inserted, the method replaces a possibly existing interval representation.
             * @complexity at most logarithmic in the size of the list
             */
            pair<iterator, bool> insert( const RealAlgebraicNumberPtr& r )
            {
                RealAlgebraicNumberNRPtr           rNR      = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( r );
                std::list<RealAlgebraicNumberPtr>::iterator position = this->begin();
                if( !this->empty() )
                {
                    position = std::lower_bound( position, this->end(), r, RealAlgebraicNumberFactory::less );
                    if( position != this->end() && RealAlgebraicNumberFactory::equal( *position, r ))    // already contained in the list
                        return pair<std::list<RealAlgebraicNumberPtr>::iterator, bool>( position, false );    // return iterator to the already contained element
                    // else: append r to the end of the list
                }
                if( rNR != 0 )
                    mNRsIRs.first.push_back( rNR );
                else    // r is numerically represented
                    mNRsIRs.second.push_back( std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( r ));
                if( r->isRoot() )
                    mNonrootsRoots.second.push_back( r );
                else
                    mNonrootsRoots.first.push_back( r );
                mQueue.push_back( r );
                return pair<std::list<RealAlgebraicNumberPtr>::iterator, bool>( std::list<RealAlgebraicNumberPtr>::insert( position, r ), true );    // insert safely and return iterator to the new element
            }

            /**
             * Inserts a range of elements into the sorted list.
             * @param first defining the first position to be inserted
             * @param last defining the last position up to which all elements, but *last, are inserted
             * @complexity at most logarithmic in the size of the list
             */
            template<class InputIterator>
            void insert( InputIterator first, InputIterator last )
            {
                for( InputIterator i = first; i != last; ++i )
                    insert( *i );
            }

            /**
             * Inserts another sampleList.
             * @param l other sampleList
             * @complexity at most logarithmic in the size of this list and linear in the size of l
             */
            void insert( const SampleList& l )
            {
                this->insert( l.begin(), l.end() );
            }

            /**
             * Safely remove the element at position.
             * @param position
             * @return the iterator to the next position in the container
             */
            SampleList::iterator remove( SampleList::iterator position )
            {
                assert( position != this->end() );
                removeFromQueue( *position );
                removeFromNRIR( *position );
                removeFromNonrootRoot( *position );
                return this->erase( position );
            }

            /**
             * Determines the next sample in the order of insertion with no particular preference.
             *
             * @return next sample in the order of insertion
             */
            inline const RealAlgebraicNumberPtr next()
            {
                if( this->empty() )
                    assert( false );    // do not call next on empty lists
                return mQueue.front();
            }

            /**
             * Determines the next sample in the order of insertion, preferring the numerically represented samples.
             *
             * Before returning an interval-represented sample, the method tries to simplify the sample.
             *
             * @return next sample in the order of insertion, preferring the numerically represented samples
             */
            inline const RealAlgebraicNumberPtr nextNR()
            {
                if( this->empty() )
                    assert( false );    // do not call next on empty lists
                if( mNRsIRs.first.empty() )    // only IRs left
                    return mNRsIRs.second.front();
                return mNRsIRs.first.front();    // return NR
            }

            /**
             * Determines the next sample in the order of insertion, preferring the non-root samples.
             *
             * @return next sample in the order of insertion, preferring the non-root samples
             */
            inline const RealAlgebraicNumberPtr nextNonroot()
            {
                if( this->empty() )
                    assert( false );    // do not call next on empty lists
                if( mNonrootsRoots.first.empty() )    // only roots left
                    return mNonrootsRoots.second.front();
                return mNonrootsRoots.first.front();    // return non-root
            }

            /**
             * Determines the next sample in the order of insertion, preferring the non-root samples.
             *
             * @return next sample in the order of insertion, preferring the non-root samples
             */
            inline const RealAlgebraicNumberPtr nextRoot()
            {
                if( this->empty() )
                    assert( false );    // do not call next on empty lists
                if( mNonrootsRoots.second.empty() )    // only non-roots left
                    return mNonrootsRoots.first.front();
                return mNonrootsRoots.second.front();    // return root
            }

            /**
             * Removes the element returned by next() from the list.
             * @complexity at most linear in the size of the list
             */
            void pop()
            {
#ifdef GINACRA_CAD_DEBUG
            cout << "pop()" << endl;
#endif
                if( this->empty() )
                    return;    // nothing to pop
                RealAlgebraicNumberPtr        r        = this->next();
                list<RealAlgebraicNumberPtr>::iterator position = std::lower_bound( this->begin(), this->end(), r, RealAlgebraicNumberFactory::less );
                if( position != this->end() )    // found in the list
                    this->erase( position );    // remove next()
                else
                    assert( false );    // r should be in this list
                mQueue.pop_front();
                removeFromNRIR(r);
                removeFromNonrootRoot(r);
            }

            /**
             * Removes the element returned by nextNR() from the list.
             * @complexity at most logarithmic in the size of the list and linear in the number of roots in the list
             */
            void popNR()
            {
#ifdef GINACRA_CAD_DEBUG
            cout << "popNR()" << endl;
#endif
                if( this->empty() )
                    return;    // nothing to pop
                RealAlgebraicNumberPtr        r        = this->nextNR();
                list<RealAlgebraicNumberPtr>::iterator position = std::lower_bound( this->begin(), this->end(), r, RealAlgebraicNumberFactory::less );
                if( position != this->end() )    // found in the list
                    this->erase( position );    // remove nextNR()
                else
                    assert( false );    // r should be in this list
                // remove next also from its bucket
                if( mNRsIRs.first.empty() ) // only IRs left, so pop from them
                    mNRsIRs.second.pop_front();
                else // NRs left, so pop from them
                    mNRsIRs.first.pop_front();
                removeFromNonrootRoot(r);
                removeFromQueue(r);
            }

            /**
             * Removes the element returned by nextNonroot() from the list. The method does nothing if there is no non-root.
             * @complexity at most linear in the size of the list
             */
            void popNonroot()
            {
#ifdef GINACRA_CAD_DEBUG
            cout << "popNonroot()" << endl;
#endif
                if( this->empty() )
                    return;    // nothing to pop
                RealAlgebraicNumberPtr        r        = this->nextNonroot();
                list<RealAlgebraicNumberPtr>::iterator position = std::lower_bound( this->begin(), this->end(), r, RealAlgebraicNumberFactory::less );
                if( position != this->end() )    // found in the list
                    this->erase( position );    // remove nextNonroot()
                else
                    assert( false );    // r should be in this list
                // remove next from its bucket
                if( mNonrootsRoots.first.empty() ) // only roots left
                    mNonrootsRoots.second.pop_front();
                else
                    mNonrootsRoots.first.pop_front();
                removeFromNRIR(r);
                removeFromQueue(r);
            }

            /**
             * Removes the element returned by nextRoot() from the list. The method does nothing if there is no root.
             * @complexity at most linear in the size of the list
             */
            void popRoot()
            {
#ifdef GINACRA_CAD_DEBUG
            cout << "popRoot()" << endl;
#endif
                if( this->empty() )
                    return;    // nothing to pop
                RealAlgebraicNumberPtr        r        = this->nextRoot();
                list<RealAlgebraicNumberPtr>::iterator position = std::lower_bound( this->begin(), this->end(), r, RealAlgebraicNumberFactory::less );
                if( position != this->end() )    // found in the list
                    this->erase( position );    // remove nextNonroot()
                else
                    assert( false );    // r should be in this list
                // remove next from its bucket
                if( mNonrootsRoots.second.empty() ) // only non-roots left
                    mNonrootsRoots.first.pop_front();
                else
                    mNonrootsRoots.second.pop_front();
                removeFromNRIR(r);
                removeFromQueue(r);
            }

            /**
             * Traverse all interval-represented samples and determine whether they could be simplified by numeric representations.
             * If so, move these samples to the NRs.
             * @return pair whose first component is a map from unsimplified real algebraic number pointers to real algebraic number pointers
             * which were simplified; the second component is true if there were samples found which could be simplified.
             * @complexity logarithmic in the number
             */
            pair< SampleSimplification, bool> simplify()
            {
                pair< SampleSimplification, bool> simplification = pair< SampleSimplification, bool>();
                simplification.second = false;
                for( list<RealAlgebraicNumberIRPtr>::iterator irIter = mNRsIRs.second.begin(); irIter != mNRsIRs.second.end(); )
                {
                    if( !(*irIter)->isNumeric() && (*irIter)->refinementCount() == 0 )    // try at least one refinement
                        (*irIter)->refine();
                    if( (*irIter)->isNumeric() )
                    {
#ifdef GINACRA_CAD_DEBUG
                        cout << "FOUND numeric in ";
                        print( *irIter, cout );
#endif
                        RealAlgebraicNumberPtr r    = std::tr1::dynamic_pointer_cast<RealAlgebraicNumber>( *irIter );
                        RealAlgebraicNumberNRPtr rNR    = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( *irIter );
                        if( rNR != 0 ) // already simplified!
                            continue;
                        RealAlgebraicNumberNRPtr nr = RealAlgebraicNumberNRPtr( new RealAlgebraicNumberNR( (*irIter)->value(), (*irIter)->isRoot() ));
#ifdef GINACRA_CAD_DEBUG
                        cout << "SIMP: replacing " << **irIter << " by " << *nr << endl;
#endif
                        // store simplification result
                        simplification.first[r] = nr;
                        simplification.second = true;
                        // add to NRs
                        mNRsIRs.first.push_back( nr );
                        // erase in IRs
                        irIter      = mNRsIRs.second.erase( irIter );
                        // replace in basic list
                        list<RealAlgebraicNumberPtr>::iterator position = std::lower_bound( this->begin(), this->end(), r,
                                                                                            RealAlgebraicNumberFactory::less );
                        if( position != this->end() )    // found in the list
                            *position = nr;    // replace ir by nr
                        else
                            assert( false );    // there must be an occurrence in the sample list or there was an error inserting the number
                        // replace in root/non-root lists
                        if( nr->isRoot() )
                        {
                            position = std::find( mNonrootsRoots.second.begin(), mNonrootsRoots.second.end(), r );
                            if( position != mNonrootsRoots.second.end() )    // found in the list
                                *position = nr;    // replace ir by nr
                            else
                                assert( false );    // there must be an occurrence in the sample list or there was an error inserting the number
                        }
                        else
                        {
                            position = std::find( mNonrootsRoots.first.begin(), mNonrootsRoots.first.end(), r );
                            if( position != mQueue.end() )    // found in the list
                                *position = nr;    // replace ir by nr
                            else
                                assert( false );    // there must be an occurrence in the sample list or there was an error inserting the number
                        }
                        // replace in queue
                        position = std::find( mQueue.begin(), mQueue.end(), r );
                        if( position != mQueue.end() )    // found in the list
                            *position = nr;    // replace ir by nr
                        else
                            assert( false );    // there must be an occurrence in the sample list or there was an error inserting the number
                    }
                    else
                        ++irIter;
                }
                return simplification;
            }

            /**
             * Determines containment of r in the list.
             * @return true if r is contained in the list, false otherwise
             */
            bool contains( RealAlgebraicNumberPtr r ) const
            {
                std::list<RealAlgebraicNumberPtr>::const_iterator position = std::lower_bound( this->begin(), this->end(), r, RealAlgebraicNumberFactory::less );
                return position != this->end();
            }

            /**
             * Answers whether there are numerically represented samples left.
             * @return true if there is no NR sample left in the list, false otherwise
             */
            bool emptyNR() const
            {
                return mNRsIRs.first.empty();
            }

            /**
             * Answers whether there are interval-represented samples left.
             * @return true if there is no IR sample left in the list, false otherwise
             */
            bool emptyIR() const
            {
                return mNRsIRs.second.empty();
            }

            /**
             * Answers whether there are non-root represented samples left.
             * @return true if there is no non-root sample left in the list, false otherwise
             */
            bool emptyNonroot() const
            {
                return mNonrootsRoots.first.empty();
            }

            /**
             * Answers whether there are root samples left.
             * @return true if there is no root sample left in the list, false otherwise
             */
            bool emptyRoot() const
            {
                return mNonrootsRoots.second.empty();
            }

    private:

        ///////////////////////
        // AUXILIARY METHODS //
        ///////////////////////

        void removeFromNonrootRoot( RealAlgebraicNumberPtr r )
        {
            if( r->isRoot() )
            {
                list<RealAlgebraicNumberPtr>::iterator pos = std::find( mNonrootsRoots.second.begin(), mNonrootsRoots.second.end(), r );    // find in roots non-root list
                if( pos != mNonrootsRoots.second.end() )
                    mNonrootsRoots.second.erase( pos );
                else
                    assert( false );    // r is marked as root
            }
            else
            {
                list<RealAlgebraicNumberPtr>::iterator pos = std::find( mNonrootsRoots.first.begin(), mNonrootsRoots.first.end(), r );    // find in roots non-root list
                if( pos != mNonrootsRoots.first.end() )
                    mNonrootsRoots.first.erase( pos );
                else
                    assert( false );    // r is marked as root
            }
        }

        void removeFromQueue( RealAlgebraicNumberPtr r )
        {
            // remove from queue
            list<RealAlgebraicNumberPtr>::iterator pos = std::find( mQueue.begin(), mQueue.end(), r );    // find in roots non-root list
            if( pos != mQueue.end() )
                mQueue.erase( pos );
            else
                assert( false );    // r is marked as root
        }

        void removeFromNRIR( RealAlgebraicNumberPtr r )
        {
#ifdef GINACRA_CAD_DEBUG
            cout << "removeFromNRIR: " << r << endl;
            cout << "List: " << endl;
            for( list<RealAlgebraicNumberPtr>::const_iterator i = begin(); i != end(); ++i )
                cout << "  " << *i;
            cout << endl << "NR: " << endl;
            for( list<RealAlgebraicNumberPtr>::const_iterator i = mNRsIRs.first.begin(); i != mNRsIRs.first.end(); ++i )
                cout << "  " << **i;
            cout << endl << "IR: " << endl;
            for( list<RealAlgebraicNumberPtr>::const_iterator i = mNRsIRs.second.begin(); i != mNRsIRs.second.end(); ++i )
                cout << "  " << **i;
#endif
            RealAlgebraicNumberNRPtr rNR = std::tr1::dynamic_pointer_cast<RealAlgebraicNumberNR>( r );
            if( rNR != 0 )
            {
                list<RealAlgebraicNumberNRPtr>::iterator pos = std::find( mNRsIRs.first.begin(), mNRsIRs.first.end(), rNR );
                if( pos != mNRsIRs.first.end() )
                    mNRsIRs.first.erase( pos );
                else
                    assert( false );    // r should be in this list, otherwise it was maybe simplified and moved to the other list
            }
            else
            {
                list<RealAlgebraicNumberIRPtr>::iterator pos = std::find( mNRsIRs.second.begin(), mNRsIRs.second.end(),
                                                                            std::tr1::dynamic_pointer_cast<RealAlgebraicNumberIR>( r ));
                if( pos != mNRsIRs.second.end() )
                    mNRsIRs.second.erase( pos );
                else
                    assert( false );    // r should be in this list
            }
        }

    };

    /** Settings for the CAD class.
     */
    struct GINACRA_API CADSettings
    {
        ////////////////
        // ATTRIBUTES //
        ////////////////

        /// the order in which the polynomials in each elimination level are sorted
        bool (*mUP_isLess)( const UnivariatePolynomial&, const UnivariatePolynomial& );
        /// standard strategy to be used for real root isolation
        RealAlgebraicNumberSettings::IsolationStrategy mIsolationStrategy;

        /////////////
        // METHODS //
        /////////////

        /**
         * Generate a CADSettings instance of the respective preset type.
         * @param setting
         * @param isolationStrategy
         * @return a CADSettings instance of the respective preset type
         */
        static const CADSettings getSettings( unsigned setting = DEFAULT_CADSETTING,
                                              RealAlgebraicNumberSettings::IsolationStrategy isolationStrategy = RealAlgebraicNumberSettings::DEFAULT_ISOLATIONSTRATEGY )
        {
            CADSettings cadSettings        = CADSettings();
            cadSettings.mIsolationStrategy = isolationStrategy;
            if( setting & LOWDEG_CADSETTING )
                cadSettings.mUP_isLess = UnivariatePolynomial::univariatePolynomialIsLessLowDeg;
            if( setting & ODDDEG_CADSETTING )
                cadSettings.mUP_isLess = UnivariatePolynomial::univariatePolynomialIsLessOddDeg;
            if( setting & LOWDEG_CADSETTING & ODDDEG_CADSETTING )
                cadSettings.mUP_isLess = UnivariatePolynomial::univariatePolynomialIsLessOddLowDeg;
            if( setting & EVENDEG_CADSETTING )
                cadSettings.mUP_isLess = UnivariatePolynomial::univariatePolynomialIsLessEvenDeg;
            if( setting & LOWDEG_CADSETTING & EVENDEG_CADSETTING )
                cadSettings.mUP_isLess = UnivariatePolynomial::univariatePolynomialIsLessEvenLowDeg;
            if( setting & EAGERLIFTING_CADSETTING )
                cadSettings.mPreferNRSamples = true;
            if( setting & GROEBNER_CADSETTING )
                cadSettings.mSimplifyByGroebner = true;
            if( setting & REALROOTCOUNT_CADSETTING )
                cadSettings.mSimplifyByRootcounting = true;
            if( setting & SQUAREFREEELIMINATION_CADSETTING )
                cadSettings.mSimplifyBySquarefreeing = true;
            return cadSettings;
        }

        GINACRA_API friend std::ostream& operator <<( std::ostream& os, const CADSettings& settings )
        {
            list<string> settingStrs = list<string>();
            if( settings.mSimplifyByGroebner )
                settingStrs.push_back( "Simplify the input polynomials corresponding to equations by a Groebner basis." );
            if( settings.mSimplifyByRootcounting )
                settingStrs.push_back( "Simplify the base elimination level by real root counting." );
            if( settings.mSimplifyBySquarefreeing )
                settingStrs.push_back( "Simplify all elimination levels by replacing the polynomials by their square-free part." );
            if( settings.mPreferNRSamples )
                settingStrs.push_back( "Prefer numerics to interval representations for sample choice." );
            if( settings.mPreferSamplesByIsRoot && settings.mPreferNonrootSamples )
                settingStrs.push_back( "Prefer non-root to root samples for sample choice." );
            if( settings.mPreferSamplesByIsRoot && !settings.mPreferNonrootSamples )
                settingStrs.push_back( "Prefer root to non-root samples for sample choice." );
            os << "+------------------------------------ CAD Setting -----------------------------------";
            if( settingStrs.empty() )
                os << endl << "| Default ";
            else
            {
                for( list<string>::const_iterator i = settingStrs.begin(); i != settingStrs.end(); ++i )
                    os << endl << "↳ " << *i;
            }
            return os << endl << "+------------------------------------------------------------------------------------";
        }

        bool simplifyByGroebner() const
        {
            return mSimplifyByGroebner;
        }

        void setSimplifyByGroebner( bool b )
        {
            mSimplifyByGroebner = b;
        }

        bool simplifyByRootcounting() const
        {
            return mSimplifyByRootcounting;
        }

        void setSimplifyByRootcounting( bool b )
        {
            mSimplifyByRootcounting = b;
        }

        bool simplifyBySquarefreeing() const
        {
            return mSimplifyBySquarefreeing;
        }

        void setSimplifyBySquarefreeing( bool b )
        {
            mSimplifyBySquarefreeing = b;
        }

        bool preferNRSamples() const
        {
            return mPreferNRSamples;
        }

        void setPreferNRSamples( bool b )
        {
            mPreferNRSamples = b;
            // dependency: PreferNRSamples excludes the use of PreferSamplesByIsRoot and vice versa
            mPreferSamplesByIsRoot = b ? false : mPreferSamplesByIsRoot;
        }

        bool preferSamplesByIsRoot() const
        {
            return mPreferSamplesByIsRoot;
        }

        void setPreferSamplesByIsRoot( bool b )
        {
            mPreferSamplesByIsRoot = b;
            // dependency: PreferSamplesByIsRoot excludes the use of PreferNRSamples and vice versa
            mPreferNRSamples = b ? false : mPreferNRSamples;
        }

        bool preferNonrootSamples() const
        {
            return mPreferNonrootSamples;
        }

        /**
         * Activates non-root/root sample choice and sets the respective setting b.
         * @param b
         */
        void setPreferNonrootSamples( bool b )
        {
            setPreferSamplesByIsRoot( true );
            mPreferNonrootSamples = b;
        }

        protected:

            ////////////////
            // ATTRIBUTES //
            ////////////////

            /// flag indicating that the construction of new samples (by taking a new polynomial for lifting) is preferred to the choice of IR samples (PreferNRSamples excludes the use of PreferSamplesByIsRoot and vice versa)
            bool mPreferNRSamples;
            /// flag indicating that the choice of samples is guided by either being a root or not (PreferSamplesByIsRoot excludes the use of PreferNRSamples and vice versa)
            bool mPreferSamplesByIsRoot;
            /// flag indicating that the construction of new samples (by taking a new polynomial for lifting) is preferred to take root samples, if and only if mPreferSamplesByIsRoot is on
            bool mPreferNonrootSamples;
            /// flag indicating that Groebner bases are used to simplify the input polynomials corresponding to equations
            bool mSimplifyByGroebner;
            /// flag indicating that the elimination uses real root counting to simplify the bottom-most level
            bool mSimplifyByRootcounting;
            /// flag indicating that the elimination uses square-free/separable polynomials in every level
            bool mSimplifyBySquarefreeing;

        private:

            /**
             * Constructor initiating a standard settings object with
             * <ul>
             *  <li>UnivariatePolynomial::univariatePolynomialIsLessDeg as polynomial ordering</li>
             *  <li>preferNRSamples enabled</li>
             *  <li>simplifyByGroebner disabled</li>
             * </ul>
             */
            CADSettings():
                mUP_isLess( UnivariatePolynomial::univariatePolynomialIsLess ),
                mIsolationStrategy( RealAlgebraicNumberSettings::DEFAULT_ISOLATIONSTRATEGY ),
                mPreferNRSamples( false ),
                mPreferSamplesByIsRoot( false ),
                mPreferNonrootSamples( false ),
                mSimplifyByGroebner( false ),
                mSimplifyByRootcounting( false ),
                mSimplifyBySquarefreeing( false )
            {}

    };

    /**
     * Functor comparing two positions of a vector of univariate polynomials.
     */
    struct GINACRA_API isLessInLiftingPositions
    {
        vector<UnivariatePolynomial> mEliminationSet;
        bool (*mIsLess)( const UnivariatePolynomial&, const UnivariatePolynomial& );

        /**
         *
         * @param eliminationSet
         * @param isLess
         */
        isLessInLiftingPositions( const vector<UnivariatePolynomial>& eliminationSet, bool (*isLess)( const UnivariatePolynomial&, const UnivariatePolynomial& ) ) :
            mEliminationSet(eliminationSet),
            mIsLess( isLess )
        {}

        bool operator ()( unsigned i, unsigned j ) const
        {
            return mIsLess( mEliminationSet[i], mEliminationSet[j] );
        }
    };

    /**
     * A collection of methods that lead directly to the computation of the
     * CAD.
     *
     * @author Joachim Redies
     * @author Ulrich Loup
     * @since 2011-11-03
     */
    class GINACRA_API CAD
    {
        public:

            //////////////////////////////////
            // Constructors and Destructors //
            //////////////////////////////////

            /*
             * Standard constructor doing nothing.
             */
            CAD();

            /**
             *
             * @param s input polynomials whose solution space is covered by this cad.
             * @param v main symbols of the polynomials in desired order of elimination (lifting order is vice versa!)
             * @param setting a setting type for a collection of CAD settings (standard option is the standard option of CADSettings::getSettings( ))
             * @complexity O( 2^(2^v.size()) ) many polynomials could be generated during the initial elimination
             */
            CAD( const UnivariatePolynomialSet& s, const vector<symbol>& v, CADSettings setting = CADSettings::getSettings() );

            /*
             * Copy constructor.
             */
            CAD( const CAD& cad ):
                mVariables( cad.mVariables ),
                mSampleTree( cad.mSampleTree ),
                mSampleListIncrements( cad.mSampleListIncrements ),
                mEliminationSets( cad.mEliminationSets ),
                mLiftingPositions( cad.mLiftingPositions ),
                mIsComplete( cad.mIsComplete ),
                mSetting( cad.mSetting )
            {}

            ///////////////
            // Selectors //
            ///////////////

            /*
             * @return list of main variables of the polynomials of this cad
             */
            const vector<symbol> variables()
            {
                return mVariables;
            }

            /*
             * Returns the input set of polynomials underlying this cad as a list.
             * @return the set of polynomials underlying this cad as a list
             */
            const vector<UnivariatePolynomial> polynomials()
            {
                return mEliminationSets[0];
            }

            /*
             * Sets with successively eliminated variables due to a CAD projection. Index i corresponds to the set where i variables were eliminated.
             * <br/ >For i>0, the i-th set was obtained by eliminating the variable i-1.
             * @return all eliminations of the polynomials and the polynomials themselves (at position 0) computed so far
             */
            const vector<vector<UnivariatePolynomial> > eliminationSets()
            {
                return mEliminationSets;
            }

            /*
             * @return true if the cad is computed completely, false if there are still samples to compute
             */
            bool isComplete() const
            {
                return mIsComplete;
            }

            //////////////////////////////
            // Operations on CAD object //
            //////////////////////////////

            /**
             * Computes all samples in this cad.
             */
            void complete();

            /**
             * Generates all real algebraic points of cad cells computed so far.
             * @return all samples computed so far
             */
            const vector<RealAlgebraicPoint> samples();

            /**
             * Checks an arbitrary constraint for satisfiability on this set of samples. The cad is extended if there are still samples not computed.
             * Remarks:
             * <ul>
             * <li>If all input constraints are build upon factors of the polynomials underlying this cad, then <code>check</code> returns a sound and complete result.</li>
             * <li>If there is a constraint whose polynomial is no factor of the polynomials underlying this cad, then only soundness is guaranteed.</li>
             * </ul>
             * @param constraints conjunction of input constraints
             * @param r contains a satisfying sample if the constraint is satisfiable by the cad
             * @return true if the constraint was satisfied by a cell in the cad, false otherwise
             */
            bool check( const vector<Constraint>& constraints, RealAlgebraicPoint& r );

            /**
             * Prints the current sample tree to the designated output stream.
             * @param os output stream (standard value is <code>std::cout</code>)
             */
            void printSampleTree( std::ostream& os = std::cout );

            /**
             * Insert the given polynomial to the cad.
             *
             * All elimination sets are recomputed.
             *
             * @param p polynomial to be added
             * @param v the polynomial's variables (parameters and main variable)
             * @param setting a setting type for a collection of CAD settings (standard option is CADSettings::GENERIC_CADSETTING). The settings are altered before the new polynomial is added.
             * @complexity O( 2^(2^mVariables.size()) ) many polynomials could be generated during the initial elimination
             */
            void addPolynomial( const UnivariatePolynomial& p, const vector<GiNaC::symbol>& v, unsigned setting = DEFAULT_CADSETTING )
            {
                list<UnivariatePolynomial> l = list<UnivariatePolynomial>( 1, p );
                addPolynomials( l.begin(), l.end(), v, setting );
            }

            /**
             * Insert the polynomials starting at first ending the point before last.
             *
             * All elimination sets are recomputed.
             *
             * @param first iterator marking the beginning of the elements to insert
             * @param last iterator marking the end of the elements to insert (not inserted!)
             * @param v the polynomials' variables (parameters and main variable)
             * @param setting a setting type for a collection of CAD settings (standard option is CADSettings::GENERIC_CADSETTING). The settings are altered before the new polynomials are added.
             * @complexity O( 2^(2^variables.size()) ) many polynomials could be generated during the elimination
             */
            template<class InputIterator>
            void addPolynomials( InputIterator first, InputIterator last, const vector<GiNaC::symbol>& v, unsigned setting = DEFAULT_CADSETTING )
            {
                this->alterSetting( setting );
                // settings (need to be set before every other process because of VariableListPool)
                if( mSetting.simplifyByGroebner() )
                {
                    MultivariatePolynomialSettings::InitializeGiNaCRAMultivariateMR();
                    for( vector<symbol>::const_iterator i = mVariables.begin(); i != mVariables.end(); ++i )
                        VariableListPool::addVariable( *i );
                }

                /* Algorithm overview:
                 * (1) Determine the variables differing from mVariables and add them to the front of the existing variables.
                 * (2) Add as many levels to the front of eliminationSets as new variables were determined.
                 * (3) Compute the elimination for the new elimination sets with the new polynomials, add the prevailing ones, and perform pairwise elimination with the prevailing ones.
                 * (4) Re-compute elimination for the newly arriving polynomials in the old elimination sets.
                 */
                // (1)
                vector<GiNaC::symbol> newVariables     = vector<GiNaC::symbol>();
                unsigned     newVariableCount = 0;
                for( vector<GiNaC::symbol>::const_iterator i = v.begin(); i != v.end(); ++i )
                {
                    if( std::find( mVariables.begin(), mVariables.end(), *i ) == mVariables.end() )
                    {    // found a new variable
                        newVariables.push_back( *i );
                        ++newVariableCount;
                    }
                }
                for( vector<GiNaC::symbol>::const_iterator i = mVariables.begin(); i != mVariables.end(); ++i )
                    newVariables.push_back( *i );
                if( newVariableCount != 0 )
                {    // extend the other data structures depending on level
                    vector<SampleList> newSampleListIncrements = vector<SampleList>( newVariableCount, SampleList() );
                    for( vector<SampleList>::const_iterator i = mSampleListIncrements.begin(); i != mSampleListIncrements.end(); ++i )
                        newSampleListIncrements.push_back( *i );
                    mSampleListIncrements = newSampleListIncrements;
                }
                // (2)
                vector<vector<UnivariatePolynomial> > newEliminationSets =
                    vector<vector<UnivariatePolynomial> >( mEliminationSets.size() + newVariableCount, vector<UnivariatePolynomial>() );
                for( unsigned i = newVariableCount; i < newEliminationSets.size(); ++i )    // copy previous elimination sets
                    newEliminationSets[i] = mEliminationSets[i - newVariableCount];
                UnivariatePolynomialSet currentEliminationSet = UnivariatePolynomialSet( newEliminationSets[0].begin(), newEliminationSets[0].end() );
                UnivariatePolynomialSet s                     = UnivariatePolynomialSet( first, last );    // collect the new polynomials
                for( UnivariatePolynomialSet::const_iterator i = s.begin(); i != s.end(); ++i )
                {    // add new polynomials to level 0, unifying their variables
                    UnivariatePolynomial pNewVar( *i, newVariables.front() );
                    newEliminationSets[0].push_back( pNewVar );
                    currentEliminationSet.insert( pNewVar );
                }
                // (3) and (4) [can be made more efficient by making use of the atomic elimination operators]
                // Caution: The elimination is recomputed completely in case we have multivariate polynomials.
                // this loop does nothing if we have univariate polynomials
                for( unsigned i = 1; i != newVariables.size(); ++i )
                {    // perform elimination of level i-1
                    // position i of mEliminationSets corresponds to variable i-1 (current main variable) eliminated in position i-1 of mEliminationSets
                    currentEliminationSet = eliminationSet( currentEliminationSet, newVariables[i] );
                    for( vector<UnivariatePolynomial>::const_iterator j = newEliminationSets[i].begin(); j != newEliminationSets[i].end();
                            ++j )    // insert possibly existing polynomials of the current level
                        currentEliminationSet.insert( *j );
                    vector<UnivariatePolynomial> currentEliminationList( currentEliminationSet.begin(), currentEliminationSet.end() );
                    // *** CADSettings: simplifyBySquarefreeing
                    if( mSetting.simplifyBySquarefreeing() )
                    {
                        for( unsigned k = 0; k < currentEliminationList.size(); ++k )
                            currentEliminationList[k] = currentEliminationList[k].sepapart();
                    }
                    std::sort( currentEliminationList.begin(), currentEliminationList.end(), mSetting.mUP_isLess );
                    if( mSetting.simplifyBySquarefreeing() )
                        std::unique( currentEliminationList.begin(), currentEliminationList.end() );
                    newEliminationSets[i] = vector<UnivariatePolynomial>( currentEliminationList.begin(), currentEliminationList.end() );
                    // *** /CADSettings: simplifyBySquarefreeing
                }
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
                mVariables       = newVariables;
                mEliminationSets = newEliminationSets;
                mIsComplete      = false;
                // reset all lifting positions
                mLiftingPositions = vector< list<unsigned> >( mVariables.size(), list<unsigned>() );
                for( unsigned i = 0; i < mVariables.size(); ++i )
                {
                    for( unsigned j = 0; j < mEliminationSets[i].size(); ++j )
                        mLiftingPositions[i].push_back(j);
        //            l.sort( isLessInLiftingPositions( mEliminationSets[i], mSetting.mUP_isLess ) );
                }
            }

            ///////////////////////////
            // PUBLIC STATIC METHODS //
            ///////////////////////////

            /**
             * Elimination/projection due to Hoon Hong ["An Improvement of the Projection Operator in Cylindrical Algebraic Decomposition", ACM, 1990.]
             * @param P set of polynomials in the variable to eliminate
             * @param nextVariable the new main variable for the returned set
             * @complexity O( m^2 * d^2 ) where m is the size of P and d the maximum degree of the polynomials in P
             * @return A set of polynomials in which the main variable of P is eliminated
             */
            static const UnivariatePolynomialSet eliminationSet( const UnivariatePolynomialSet& P,
                                                                 const symbol& nextVariable )
                    throw ( invalid_argument );

            /**
             * Constructs the samples at the base level of a CAD construction, provided a set of prevailing samples.
             * This method only returns samples which are new, i.e. not contained in currentSamples.
             * @param roots list of real roots
             * @param currentSamples samples already present where the new samples shall be integrated
             * @return a set of sample points for the given univariate polynomial sorted in ascending order.
             * @complexity linear in <code>roots.size()</code>
             */
            static const SampleList samples( const list<RealAlgebraicNumberPtr>& roots, SampleList& currentSamples ) throw ( invalid_argument );

            /**
             * Generates a list of sample points for a list of rational
             * univariate polynomials. It uses Sturm sequences to
             * generate isolating intervals of the roots and
             * adds numeric sample points of the non-root cells
             * in between. The return format is pointers to
             * real algebraic numbers.
             * @param polynomials rational univariate polynomials
             * @param currentSamples samples already present where the new samples shall be integrated
             * @complexity linear in the number of common roots of <code>polynomials</code> plus the accumulated complexities of <code>RealAlgebraicNumberFactory::realRoots</code> calls.
             * @return a list of pointers to real algebraic numbers
             */
            static const SampleList samples( const list<RationalUnivariatePolynomial>& polynomials,
                                             SampleList& currentSamples )
                    throw ( invalid_argument );

            // ATOMIC METHODS //
            ////////////////////

            /**
             * Performs all steps of a CAD elimination/projection operator which are related to one single polynomial.
             *
             *<p><strong>Note that the set returned by this method should be disjoint to the set returned by the two-polynomial variant of <code>eliminate</code>.</strong></p>
             *
             * @param p input polynomial for the elimination procedure
             * @param variable the new main variable for the returned set
             * @param eliminated the set of eliminated polynomials to be augmented by the result of the elimination
             * @complexity O ( deg(P) ) subresultant computations. The degree of the output is bound by O(deg(P)^2)!
             * @return a list of polynomials in which the main variable of p is eliminated
             */
            static void elimination( const UnivariatePolynomial& p, const symbol& variable, UnivariatePolynomialSet& eliminated ) throw ( invalid_argument );

            /**
             * Performs all steps of a CAD elimination/projection operator which are related to a pair of polynomials.
             *
             *<p><strong>Note that the set returned by this method should be disjoint to the set returned by the single-polynomial variant of <code>eliminate</code>.</strong></p>
             *
             * @param p first input polynomial for the elimination procedure
             * @param q second input polynomial for the elimination procedure
             * @param variable the new main variable for the returned set
             * @param eliminated the set of eliminated polynomials to be augmented by the result of the elimination
             * @complexity O( deg(P)^2 ) subresultant computations. The degree of the output is bound by O(max(deg(P),deg(Q))^2)!
             * @return a list of polynomials in which the main variable of p1 and p2 is eliminated
             */
            static void elimination( const UnivariatePolynomial& p,
                                                                 const UnivariatePolynomial& q,
                                                                 const symbol& variable,
                                                                 UnivariatePolynomialSet& eliminated )
                    throw ( invalid_argument );

            /**
             * Constructs the samples at the base level of a CAD construction.
             *
             * @param p rational univariate polynomial
             * @param currentSamples samples already present where the new samples shall be integrated. Each new sample is automatically inserted in this list.
             * @param settings a setting type for a collection of CAD settings (standard option is the standard option of CADSettings::getSettings( ))
             * @return a list of sample points for the given univariate polynomial
             * @complexity linear in the number of roots of <code>p</code> plus the complexity of <code>RealAlgebraicNumberFactory::realRoots( p )</code>
             */
            static const SampleList samples( const RationalUnivariatePolynomial& p,
                                             SampleList& currentSamples,
                                             CADSettings settings = CADSettings::getSettings() )
                    throw ( invalid_argument );

            /**
             * Constructs the samples for <code>p</code> given the sample values <code>sample</code> with their corresponding variables for the coefficient polynomials.
             * @param p univariate polynomial with coefficients in the given variables. <code>p</code> is univariate in a variable not contained in <code>variables</code>.
             * @param sample list of sample components in order corresponding to the variables
             * @param variables variables of the coefficients of p
             * @param currentSamples samples already present where the new samples shall be integrated. Each new sample is automatically inserted in this list.
             * @param settings a setting type for a collection of CAD settings (standard option is the standard option of CADSettings::getSettings( ))
             * @return a set of sample points for the given univariate polynomial
             * @complexity linear in the number of roots of <code>p</code> plus the complexity of <code>RealAlgebraicNumberFactory::realRoots( p )</code>
             */
            static const SampleList samples( const UnivariatePolynomial& p,
                                             const list<RealAlgebraicNumberPtr>& sample,
                                             const list<symbol>& variables,
                                             SampleList& currentSamples,
                                             CADSettings settings = CADSettings::getSettings() )
                    throw ( invalid_argument );

        private:

            ////////////////
            // Heuristics //
            ////////////////

            /**
             * Change the setting of the current CAD object.
             * @param setting
             * @param isolationStrategy
             */
            void alterSetting( unsigned setting = DEFAULT_CADSETTING,
                               RealAlgebraicNumberSettings::IsolationStrategy isolationStrategy = RealAlgebraicNumberSettings::DEFAULT_ISOLATIONSTRATEGY )
            {
                mSetting = CADSettings::getSettings( setting, isolationStrategy );
            }

            ////////////////
            // ATTRIBUTES //
            ////////////////

            /// fix list of variables for all computations
            vector<symbol> mVariables;
            /// sample components built during the computation arranged in a tree
            tree<RealAlgebraicNumberPtr> mSampleTree;
            /// level-wise list of sample components representing the samples belonging to the current lifting position
            vector<SampleList> mSampleListIncrements;
            /// lists of polynomials occurring in every elimination level (immutable; new polynomials are appended at the tail)
            vector<vector<UnivariatePolynomial> > mEliminationSets;
            /// stack of positions for the next lifting in each level
            vector<list<unsigned> > mLiftingPositions;
            /// flag indicating whether the sample construction is completed or not
            bool mIsComplete;
            /// setting for internal heuristics
            CADSettings mSetting;

            ///////////////////////
            // Auxiliary methods //
            ///////////////////////

            /**
             * Constructs the path from the given node to the root and conjoins all RealAlgebraicNumbers on the nodes of the path.
             * @param node
             * @param root of the sample tree
             * @return RealAlgebraicPoint belonging to leaf
             */
            inline const RealAlgebraicPoint constructSampleAt( tree<RealAlgebraicNumberPtr>::iterator node,
                                                               const tree<RealAlgebraicNumberPtr>::iterator& root ) const;

            /**
             * Constructs new samples in the sample tree by successive evaluation of projection polynomial coefficients and univariate sample construction until a satisfying sample is found or there is none.
             * @param node of the current level (initiate with child of mSampleTreeRoot)
             * @param level index of the current lifting level (initialize with number of variables)
             * @param sample list of sample components in order corresponding to the variables. The sample values (and the corresponding variables) are stored in reverse order compared to the lifting order. This is crucial to meet the same variable order as for the constraints.
             * @param variables list of variables. Note that the first variable is always the last one lifted.
             * @param constraints conjunction of constraints for the final check of against the current constructed RealAlgebraicPoint
             * @param r RealAlgebraicPoint which contains the satisfying sample point if the check results true
             * @return <code>true</code> if from <code>node</code> a path in the sample tree can be constructed so that the corresponding sample satisfies the <code>c</code>, <code>false</code> otherwise.
             */
            inline const bool liftCheck( tree<RealAlgebraicNumberPtr>::iterator node,
                                         const list<RealAlgebraicNumberPtr>& sample,
                                         unsigned level,
                                         const list<symbol>& variables,
                                         const vector<Constraint>& constraints,
                                         RealAlgebraicPoint& r )
                    throw ( invalid_argument );

            /**
             * Returns the truth value as to whether the conjunction of the <code>constraints</code>is satisfied by the real algebraic point <code>r</code>.
             * @param r
             * @param constraints
             * @return the truth value as to whether the conjunction of the constraints is satisfied by the real algebraic point
             */
            inline const bool satisfys( const RealAlgebraicPoint& r, const vector<Constraint>& constraints ) const;

            //////////////////////////////
            // STATIC AUXILIARY METHODS //
            //////////////////////////////

            /**
             * Generates the set of truncations of the polynomial.
             * The Algorithm is based on the notation from "Algorithms in Real Algebraic Geometry" -
             * Saugata Basu, Richard Pollack, Marie-Francoise Roy see page 21-22
             * @param P The polynomial
             * @complexity O ( deg(P) )
             * @return The set of truncations
             */
            static const UnivariatePolynomialSet truncation( const UnivariatePolynomial& P );

            /**
             * Generates the set of truncations of the polynomial set.
             * The Algorithm is based on the notation from "Algorithms in Real Algebraic Geometry" -
             * Saugata Basu, Richard Pollack, Marie-Francoise Roy see page 21-22
             * @param P The polynomial set
             * @complexity O( |P| * max_deg(P) )
             * @return The set of truncations
             */
            static const UnivariatePolynomialSet truncation( const UnivariatePolynomialSet& P );
    };
}    // namespace GiNaC
#endif /** GINACRA_CAD_H*/
