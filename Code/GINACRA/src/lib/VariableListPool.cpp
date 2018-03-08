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


#include <vector>
//
//#include "VariableListPool.h"
//#include "CAD.h"

namespace GiNaCRA
{
    SymbolDB*                VariableListPool::GlobalVariables;
    SymbolDB*                VariableListPool::GlobalParameters;
    std::map<symbol, symbol> VariableListPool::Matching;
    bool                     VariableListPool::mInitialized = false;

    VariableListPool::VariableListPool(){}

    bool VariableListPool::Initialize()
    {
        if( !mInitialized )
        {
            GlobalVariables  = new SymbolDB( "x" );
            GlobalParameters = new SymbolDB( "a" );

            GlobalVariables->addSymbol( "x" );
            GlobalVariables->addSymbol( "y" );
            GlobalVariables->addSymbol( "z" );
            GlobalVariables->addSymbol( "w" );
            GlobalVariables->addSymbol( "u" );

            mInitialized = true;
        }

        return true;

    }
}
