
/** @file symbol_factory.cc
 *
 * Implementation of a flyweight symbol factory 
 *
 */

/*
 *  Copyright (C) 2001-2017 Stefan Weinzierl
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <map>
#include <string>
#include <sstream>

#include "nestedsum_private.h"

#ifdef _DEBUG
#include <iostream>
#include <ctime>
#endif // def _DEBUG

namespace nestedsums {

using namespace GiNaC;

  /**
   *
   * The symbol factory
   *
   */
  const symbol symbol_factory(const std::string & symbol_name, const std::string & latex_name)
  {
    typedef std::map<std::string, symbol> symb_map;
    static symb_map directory;
    symb_map::iterator i = directory.find(symbol_name);
    if ( i != directory.end() )
      return i->second;
    return directory.insert(symb_map::value_type(symbol_name, symbol(symbol_name,latex_name))).first->second;
  }

  /*
   *
   * Returns the next dummy index.
   *
   */
  const symbol next_index(void)
  {
    static int number = 0;
    std::string i("_i_");
    std::string li("i_");

    number++;
    std::string n=itos(number);

    return symbol_factory(i+n,li+n);
  }

  /*
   *
   * Returns the next "x" variable.
   *
   */
  const symbol next_x(void)
  {
    static int number = 0;
    std::string i("_x_");
    std::string li("x_");

    number++;
    std::string n=itos(number);

    return symbol_factory(i+n,li+n);
  }

} // namespace nestedsums

/*
 * convert an integer into a string
 */
std::string itos(int arg)
{
    std::ostringstream buffer;
    buffer << arg; // send the int to the ostringstream
    return buffer.str(); // capture the string
}
