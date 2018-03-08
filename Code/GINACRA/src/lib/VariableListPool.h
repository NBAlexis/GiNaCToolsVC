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


#ifndef VARIABLEPOOL_H
#define VARIABLEPOOL_H

//#include "SymbolDB.h"

namespace GiNaCRA
{
    /**
     * Class saving variable-lists.
     *
     * @author Sebastian Junges
     * @since 2011-12-08
     * @version 2011-12-15
     */
    class GINACRA_API VariableListPool
    {
        public:
            VariableListPool();

            /**
             * Add a variable to the global list
             * @return the index
             */
            static unsigned addVariable()
            {
                return GlobalVariables->addSymbol();
            }

            static unsigned addVariable( symbol s )
            {
                return GlobalVariables->addSymbol( s );
            }

            /**
             * Add a parameter to the global list
             * @return the index
             */
            static unsigned addParameter()
            {
                return GlobalParameters->addSymbol();
            }

            /**
             * Get the variable at the given index
             * @param index
             * @return
             */
            inline static GiNaC::symbol getVariableSymbol( unsigned index )
            {
                return (*GlobalVariables)[index];
            }

            /**
             * Get the parameter at the given index
             * @param index
             * @return
             */
            inline static GiNaC::symbol getParameterSymbol( unsigned index )
            {
                return (*GlobalParameters)[index];
            }

            /**
             *
             * @return The list of globally managed variables
             */
            inline static std::list<symbol> getVariableList()
            {
                return GlobalVariables->getSymbolList();
            }

            /**
             *
             * @return The list of globally managed parameters
             */
            inline static std::vector<symbol> getVariables()
            {
                return GlobalVariables->getSymbolVector();
            }

            inline static void ensureNrVariables( unsigned nrOfVars )
            {
                for( unsigned i = GlobalVariables->size(); i <= nrOfVars; ++i )
                {
                    GlobalVariables->addSymbol();
                }
            }

            /**
             * Initialize the global management.
             * @return
             */
            static bool Initialize();

        protected:

            static SymbolDB*           GlobalVariables;
            static SymbolDB*           GlobalParameters;
            static map<symbol, symbol> Matching;
            static bool                mInitialized;

    };

}

#endif   /** VARIABLEPOOL_H */
