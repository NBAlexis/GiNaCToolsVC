
/** @file version.h
 *
 *  Nestedsums library version information. 
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

#ifndef __NESTEDSUMS_VERSION_H__
#define __NESTEDSUMS_VERSION_H__

/* Major, minor, and micro version number of the Nestedsums library. */
#define NESTEDSUMS_MAJOR 1
#define NESTEDSUMS_MINOR 5
#define NESTEDSUMS_MICRO 1

namespace nestedsums {

extern const int version_major;
extern const int version_minor;
extern const int version_micro;

} // namespace nestedsums

#endif // ndef __NESTEDSUMS_VERSION_H__
