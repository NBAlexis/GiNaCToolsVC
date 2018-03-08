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


//#include "SymbolDB.h"
//#include "constants.h"
//#include "SymbolDB.h"

using GiNaC::symbol;

/**
 * Implementation of the class SymbolDB.
 *
 * @author Ulrich Loup
 * @since 2011-12-07
 * @version 2011-12-15
 *
 * Notation is following http://www.possibility.com/Cpp/CppCodingStandard.html.
 */

namespace GiNaCRA
{
    //////////////////////////
    // Con- and destructors //
    //////////////////////////

    SymbolDB::SymbolDB( std::string stdname ):
        mStdName( stdname )
    {}

    ///////////////
    // Operators //
    ///////////////

    const symbol SymbolDB::operator []( unsigned i ) const
    {
        return mVariables[i];
    }

    unsigned SymbolDB::operator []( const symbol& v ) const
    {
        return mSymbollist.at( v );

    }

    unsigned SymbolDB::addSymbol()
    {
        unsigned          size = mVariables.size();
        std::stringstream str;
        str << size;
        std::string name = mStdName + "_" + str.str();
        symbol s = symbol( name );
        mVariables.push_back( s );
        mSymbollist.insert( std::pair<symbol, unsigned>( s, size ));
        return size;
    }

    unsigned SymbolDB::addSymbol( std::string name )
    {
        symbol s = symbol( name );
        map<symbol, unsigned>::const_iterator pos = mSymbollist.find( s );
        if( pos != mSymbollist.end() )
            return pos->second;
        unsigned size = mVariables.size();
        mSymbollist.insert( std::pair<symbol, unsigned>( s, size ));
        mVariables.push_back( s );
        return size;
    }

    unsigned SymbolDB::addSymbol( symbol s )
    {
        map<symbol, unsigned>::const_iterator pos = mSymbollist.find( s );
        if( pos != mSymbollist.end() )
            return pos->second;
        unsigned size = mVariables.size();
        mSymbollist.insert( std::pair<symbol, unsigned>( s, size ));
        mVariables.push_back( s );
        return size;
    }

}    // namespace GiNaCRA

