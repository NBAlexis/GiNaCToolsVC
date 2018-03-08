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


#ifndef GINACRA_CONSTANTS_H
#define GINACRA_CONSTANTS_H

/**
 * @file constants.h
 *
 * Collection of all constants needed within the GiNaC Real Algebra package.
 *
 * @author Ulrich Loup
 * @since 2010-11-01
 * @version 2012-04-27
 */

#include <numeric> // provides accumulate(..)
#include <sstream>
#include <string>
//#include <ginac/ginac.h>

using std::string;
using std::stringstream;
using std::binary_function;
using std::unary_function;
using std::vector;
using std::list;
using std::pair;
using GiNaC::basic;
using GiNaC::numeric;
using GiNaC::ex;

namespace GiNaC
{
    /** Type for infinitesimal values.
     */
    typedef struct GINACRA_API infinitesimal_symbol_struct:
        public symbol
    {
        numeric limit_value;

        /** Constructs infinitesimal value with standard limit value by 0 and no name.
         */
        infinitesimal_symbol_struct():
            symbol(),
            limit_value( 0 )
        {}

        /** Constructs infinitesimal value with standard limit value by 0.
         * @param name
         */
        infinitesimal_symbol_struct( const std::string& name ):
            symbol( name ),
            limit_value( 0 )
        {}

        /** Constructs infinitesimal value with specified limit value.
         * @param name
         * @param l limit value
         */
        infinitesimal_symbol_struct( const std::string& name, const numeric& l ):
            symbol( name ),
            limit_value( l )
        {}

        const numeric limit()
        {
            return limit_value;
        }

    } infinitesimal_symbol;

    // infinitesimal elements: epsilon < delta < gamma < zeta
    const infinitesimal_symbol EPSILON( "eps" );
    const infinitesimal_symbol DELTA( "delta" );
    const infinitesimal_symbol GAMMA( "gamma" );
    const infinitesimal_symbol ZETA( "zeta" );

    /// type for signs
    enum sign { NEGATIVE_SIGN = -1, ZERO_SIGN = 0, POSITIVE_SIGN = 1 };

    /// standard variable for standard polynomial objects
    extern const GINACRA_API symbol X;

    /// unique representation of zero
    extern const GINACRA_API numeric ZERO;

    /** Prototypal ordering on expressions which are terms.
     */
    struct GINACRA_API ex_is_lessdeg:
        public binary_function<ex, ex, bool>
    {
        vector<symbol> variables;

        ex_is_lessdeg( const vector<symbol>& variables ):
            variables( variables )
        {}

        /** Compares two expressions lexicographically by their string representations.
         * @param a
         * @param b
         * @return true in case a is less or equal to b
         */
        bool operator ()( const ex& a, const ex& b ) const
        {
            return true;
        }

        struct get_degree:
            public unary_function<symbol, int>
        {
            ex p;

            get_degree( const ex& q ):
                p( q )
            {}

            int operator ()( const symbol& x )
            {
                return p.degree( x );
            }
        };

        inline list<int> exponents( const ex& p, const vector<symbol>& variables ) const
        {
            int n = 0;
            for( vector<symbol>::const_iterator i = variables.begin(); i != variables.end(); ++i )
                n++;
            list<int> exponents( n, 0 );
            transform( variables.begin(), variables.end(), exponents.begin(), get_degree( p ));
            return exponents;
        }
    };

    /** Graded lexicographic ordering on expressions which are terms.
     */
    struct GINACRA_API ex_is_less_deggrlex:
        public ex_is_lessdeg
    {
        ex_is_less_deggrlex( const vector<symbol>& variables ):
            ex_is_lessdeg( variables )
        {}

        /** Compares two expressions lexicographically by their string representations.
         * @param a
         * @param b
         * @return true in case a is less or equal to b
         */
        bool operator ()( const ex& a, const ex& b ) const
        {
            list<int> e1   = exponents( a, variables );
            list<int> e2   = exponents( b, variables );
            int       deg1 = accumulate( e1.begin(), e1.end(), 0 );
            int       deg2 = accumulate( e2.begin(), e2.end(), 0 );
            if( deg1 < deg2 )
                return true;
            else if( deg1 > deg2 )
                return false;
            else
                // return !lexicographical_compare(e1.begin(), e1.end(), e2.begin(), e2.end()); // for weak ordering!
                return lexicographical_compare( e2.begin(), e2.end(), e1.begin(), e1.end() );
        }
    };

    /** Lexicographic degree-reverse ordering on expressions which are terms.
     */
    struct GINACRA_API ex_is_less_degrevlex:
        public ex_is_lessdeg
    {
        ex_is_less_degrevlex( const vector<symbol>& variables ):
            ex_is_lessdeg( variables )
        {}

        /** Compares two expressions lexicographically by their string representations.
         * @param a
         * @param b
         * @return true in case a is less or equal to b
         */
        bool operator ()( const ex& a, const ex& b ) const
        {
            list<int> e1   = exponents( a, variables );
            list<int> e2   = exponents( b, variables );
            int       deg1 = accumulate( e1.begin(), e1.end(), 0 );
            int       deg2 = accumulate( e2.begin(), e2.end(), 0 );
            if( deg1 < deg2 )
                return true;
            else if( deg1 > deg2 )
                return false;
            else
                //          return !lexicographical_compare(e1.rbegin(), e1.rend(), e2.rbegin(), e2.rend()); // for weak ordering!
                return lexicographical_compare( e2.rbegin(), e2.rend(), e1.rbegin(), e1.rend() );
        }
    };

    /**
     * Relation determining whether the given expression is a monomial under the staircase, which is determined by computing the remainders dividing by the corners of a staircase.
     * @param corners corners of the staircase of a Groebner basis (unverified input)
     */
    struct GINACRA_API ex_is_under_the_staircase:
        public unary_function<ex, bool>
    {
        list<ex> corners;

        ex_is_under_the_staircase( const list<ex> corners ):
            corners( corners )
        {}

        /**
         * Tests whether the given expression is a monomial under the staircase.
         * @param monomial (unverified input)
         * @return true if the given expression is a monomial under the staircase, false otherwise
         */
        bool operator ()( const ex& monomial ) const
        {
            for( list<ex>::const_iterator i = corners.begin(); i != corners.end(); ++i )
            {
                ex q = 0;
                if( divide( *i, monomial, q ))    // monomial divides *i by q
                    return true;
            }
            return false;
        }
    };

    /** Prototypal ordering on pairs of expressions which represent terms.
     */
    template<class monomialOrdering>
    struct GINACRA_API expair_is_lesseq:
        public binary_function<pair<ex, ex>, pair<ex, ex>, bool>
    {
        vector<symbol> variables;

        expair_is_lesseq( const vector<symbol>& variables ):
            variables( variables )
        {}

        /** Compares two expressions lexicographically by their string representations.
         * @param a
         * @param b
         * @return true in case a is less or equal to b
         */
        bool operator ()( const pair<ex, ex>& a, const pair<ex, ex>& b ) const
        {
            return monomialOrdering( variables )( a.second, b.second );
        }

    };

}    // namespace GiNaC

#endif // GINACRA_CONSTANTS_H
