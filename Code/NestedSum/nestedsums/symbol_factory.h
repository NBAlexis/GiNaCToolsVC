
/** @file symbol_factory.h
 *
 * Interface to the flyweight symbol factory 
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

#ifndef __NESTEDSUMS_SYMBOL_FACTORY_H__
#define __NESTEDSUMS_SYMBOL_FACTORY_H__

//#include "ginac/ginac.h"

#include <string>

namespace nestedsums {

  const NESTEDSUMS_API GiNaC::symbol symbol_factory(const std::string & symbol_name, const std::string & latex_name);

  const NESTEDSUMS_API GiNaC::symbol next_index(void);
  const NESTEDSUMS_API GiNaC::symbol next_x(void);

} // namespace nestedsums


// a routine to convert from integers to string
NESTEDSUMS_API std::string itos(int arg);


#endif // ndef __NESTEDSUMS_SYMBOL_FACTORY_H__

