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


#ifndef GINACRA_SYMBOL_DB_H
#define GINACRA_SYMBOL_DB_H

//#include <ginac/ginac.h>

using std::vector;
using std::map;
using std::out_of_range;
using GiNaC::symbol;
using GiNaC::ex_is_less;

namespace GiNaCRA
{
    /**
     * Class encapsulating the global variable and the global parameter list.
     *
     * @author Ulrich Loup
     * @since 2011-12-07
     * @version 2011-12-15
     *
     * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
     */

    class GINACRA_API SymbolDB
    {
        public:

            //////////////////////////
            // Con- and destructors //
            //////////////////////////

            /**
             * Constructs the lookup table for variables. The variables are sorted lexicographically.
             * @param stdname The standard name new symbols get
             * @complexity O( n*log(n) ) where n is the number of variables
             */
            SymbolDB( std::string stdname );

            ///////////////
            // Operators //
            ///////////////

            /**
             * Returns the i-th variable.
             * @param i
             * @return the i-th variable
             */
            const symbol operator []( unsigned i ) const;

            /**
             * Returns the index belonging to the given variable s (in lexicographic order).
             * @param v
             * @return the index belonging to v
             * @complexity O( log(n) ) where n is the number of variables
             * @throw  throw(out_of_range);
             */
            unsigned operator []( const symbol& v ) const;

            /**
             * Add a symbol with the standardname and a indexnumber
             * @return the indexnumber.
             */
            unsigned addSymbol();

            /**
             * Add a symbol with name name
             * @param name
             * @return the indexnumber
             */
            unsigned addSymbol( std::string name );

            /**
             * @param s
             * @return
             */
            unsigned addSymbol( symbol s );

            /**
             * @complexity linear
             * @return the symbollist as a list.
             */
            std::list<symbol> getSymbolList() const
            {
                return std::list<symbol>( mVariables.begin(), mVariables.end() );
            }

            /**
             * @complexity linear
             * @return the symbollist as a vector
             */
            std::vector<symbol> getSymbolVector() const
            {
                return mVariables;
            }

            unsigned size()
            {
                return mVariables.size();
            }

        protected:
            vector<symbol>                                mVariables;
            std::map<symbol, unsigned, GiNaC::ex_is_less> mSymbollist;
            std::string                                   mStdName;

    };    // class SymbolDB

}    // namespace GiNaCRA

#endif
