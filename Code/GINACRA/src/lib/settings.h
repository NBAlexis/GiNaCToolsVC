/**
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

#ifndef GINACRA_SETTINGS_H
#define GINACRA_SETTINGS_H

/**
 * @file settings.h
 *
 * Collection of global values needed within the GiNaC Real Algebra package.
 *
 * @author Sebastian Junges
 * @author Ulrich Loup
 * @since 2010-11-01
 * @version 2012-05-15
 */

#include <limits.h>
//
//#include "SymbolDB.h"
//#include "VariableListPool.h"
//#include "UnivariatePolynomial.h"

namespace GiNaCRA
{
    /////////////
    // CPPUnit //
    /////////////

    /** Collection of CPPUNIT related settings.
     */
    class GINACRA_API CPPUNITSettings
    {
        public:
            static std::string TESTSUITE_ALL;
            static std::string TESTSUITE_UNIVARIATE;
    };

    ////////////////////////////
    // MultivariatePolynomial //
    ////////////////////////////

    /** Collection of MultivariatePolynomial related settings.
     */
    class GINACRA_API MultivariatePolynomialSettings
    {
        public:

            /**
             * Initialize a VariableListPool instance in order to provide variable and parameter management for the MultivariateMR classes.
             */
            static void InitializeGiNaCRAMultivariateMR()
            {
                if( !VariableListPool::Initialize() )
                    throw std::runtime_error( "Could not initialize Variables" );
            }
    };

    /////////
    // CAD //
    /////////

    /** Predefined settings for the CAD procedure.
     * Implementation of the types is located in CAD.h. Each setting is defined as a power of two in order to use several flags at a time.
     * Note that the order of the flags plays a role: If, e.g., ODDDEG_CADSETTING and EVENDEG_CADSETTING are set, then the last one (EVENDEG_CADSETTING) is used.
     */
    enum CADSettingsType
    {
        /// low-degree first polynomial order
        LOWDEG_CADSETTING = 1,
        /// odd-degree first polynomial order
        ODDDEG_CADSETTING = 2,
        /// even-degree first polynomial order
        EVENDEG_CADSETTING = 4,
        /// complete search for each lifting position before taking a new one
        EAGERLIFTING_CADSETTING = 8,
        /// the elimination uses Groebner bases to simplify the levels below the top-most level
        GROEBNER_CADSETTING = 16,
        /// the elimination uses real root counting to simplify the bottom-most level
        REALROOTCOUNT_CADSETTING = 32,
        /// the elimination uses square-free/separable polynomials in every level
        SQUAREFREEELIMINATION_CADSETTING = 64
    };

    /// The default setting for CAD settings, which is chosen if the CAD object is initialized without any other parameter.
    static const CADSettingsType DEFAULT_CADSETTING = LOWDEG_CADSETTING;

    /////////////////////////
    // RealAlgebraicNumber //
    /////////////////////////

    /** Collection of RealAlgebraicNumber related settings.
     */
    struct GINACRA_API RealAlgebraicNumberSettings
    {
        /// Predefined flags for different refinement strategies in RealAlgebraicNumberIR::refine.
        enum RefinementStrategy
        {
            /// Performs interval splitting by OpenInterval::midpoint. If the midpoint happens to be the root itself, it is stored in RealAlgebraicNumberIR::mValue.
            GENERIC_REFINEMENTSTRATEGY,
            /// OpenInterval::sample is checked for being a root. If not, it is used to dissect the interval. Otherwise it is stored in RealAlgebraicNumberIR::mValue.
            BINARYSAMPLE_REFINEMENTSTRATEGY,
            /// Newton's iteration is applied for finding the a root first. If no root was found, the value is used to dissect the interval.
            BINARYNEWTON_REFINEMENTSTRATEGY,
            /// During the splitting process, the midpoint is checked for being a root first. Then, OpenInterval::sample is checked. If it didn't prove to be a root, it is used to dissect the interval. Otherwise it is stored in RealAlgebraicNumberIR::mValue.
            BINNARYMIDPOINTSAMPLE_REFINEMENTSTRATEGY
        };

        /// The default setting for the refinement strategy, used if no other option is specified.
        static const RefinementStrategy DEFAULT_REFINEMENTSTRATEGY = GENERIC_REFINEMENTSTRATEGY;

        /// Maximum number of refinements in which the sample() value should be computed for splitting. Otherwise the midpoint is taken.
        static const unsigned MAXREFINE_REFINEMENTSTRATEGY = 8;

        /// Predefined flags for different real root isolation strategies in RealAlgebraicNumberFactory::realRoots.
        enum IsolationStrategy
        {
            /// Performs just interval splitting by OpenInterval::midpoint.
            SIMPLE_ISOLATIONSTRATEGY,
            /// Performs interval splitting by OpenInterval::midpoint. If the midpoint happens to be the root itself, it is stored in RealAlgebraicNumberIR::mValue.
            GENERIC_ISOLATIONSTRATEGY,
            /// During the splitting process, the midpoint is checked for being a root first. Then, OpenInterval::sample is checked. If it didn't prove to be a root, it is used to dissect the interval. Otherwise it is stored in RealAlgebraicNumberIR::mValue.
            BINARYSAMPLE_ISOLATIONSTRATEGY,
            /// During the splitting process, the midpoint is checked for being a root first. Then, OpenInterval::sample is checked. If it didn't prove to be a root, both the midpoint and the sample point are used to split the interval.
            TERNARYSAMPLE_ISOLATIONSTRATEGY,
            /// During the splitting process, the midpoint is checked for being a root first. Then, OpenInterval::sample is checked. If it didn't prove to be a root, both the midpoint and the sample point are used to split the interval.
            TERNARYNEWTON_ISOLATIONSTRATEGY
        };

        /// The default setting for the real root isolation strategy, used if no other option is specified.
        static const IsolationStrategy DEFAULT_ISOLATIONSTRATEGY = TERNARYSAMPLE_ISOLATIONSTRATEGY;

        /// Maximum bound of an isolating interval so that the OpenInterval::sample method is used for splitting point selection.
        static const long MAX_FASTSAMPLE_BOUND = SHRT_MAX;
    };
}
#endif   /** GINACRA_SETTINGS_H */
