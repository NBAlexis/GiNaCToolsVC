
/** @file utils.h
 *
 * Interface to some utilities
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

#ifndef __NESTEDSUMS_UTILS_H__
#define __NESTEDSUMS_UTILS_H__

#include <typeinfo>

////#include "ginac/ginac.h"
//
//#include "config.h"

namespace nestedsums {

// some functions stolen from GiNaC:

/** Rotate lower 31 bits of unsigned value by one bit to the left
 *  (upper bit gets cleared). */
inline unsigned rotate_left_31(unsigned n)
{
	// clear highest bit and shift 1 bit to the left
	n = (n & 0x7FFFFFFFU) << 1;
	
	// overflow? clear highest bit and set lowest bit
	if (n & 0x80000000U)
		n = (n & 0x7FFFFFFFU) | 0x00000001U;
	
	GINAC_ASSERT(n<0x80000000U);
	
	return n;
}

#if SIZEOF_VOID_P == SIZEOF_INT
typedef unsigned int p_int;
#elif SIZEOF_VOID_P == SIZEOF_LONG
typedef unsigned long p_int;
#elif SIZEOF_VOID_P == SIZEOF_LONG_LONG
typedef unsigned long long p_int;
#else
typedef unsigned long p_int;
#endif

/** Golden ratio hash function for the 31 least significant bits. */
inline unsigned golden_ratio_hash(unsigned n)
{
	// This function requires arithmetic with at least 64 significant bits
#if SIZEOF_LONG >= 8
	// So 'long' has 64 bits.  Excellent!  We prefer it because it might be
	// more efficient than 'long long'.
	unsigned long l = n * 0x4f1bbcddL;
	return (l & 0x7fffffffU) ^ (l >> 32);
#elif SIZEOF_LONG_LONG >= 8
	// This requires 'long long' (or an equivalent 64 bit type)---which is,
	// unfortunately, not ANSI-C++-compliant.
	// (Yet C99 demands it, which is reason for hope.)
	unsigned long long l = n * 0x4f1bbcddL;
	return (l & 0x7fffffffU) ^ (l >> 32);
#elif SIZEOF_LONG_DOUBLE > 8
	// If 'long double' is bigger than 64 bits, we assume that the mantissa
	// has at least 64 bits. This is not guaranteed but it's a good guess.
	// Unfortunately, it may lead to horribly slow code.
	const static long double golden_ratio = .618033988749894848204586834370;
	long double m = golden_ratio * n;
	return unsigned((m - int(m)) * 0x80000000);
#else
#error "No 64 bit data type. You lose."
#endif
}

static inline unsigned make_hash_seed(const std::type_info& tinfo)
{
	// this pointer is the same for all objects of the same type.
	// Hence we can use that pointer 

    //FOR VC, mangled_name_ptr is different even when tinfo.name() is same!!!!
    unsigned v = cln::hashcode(tinfo.name());
	//const void* mangled_name_ptr = (const void*)tinfo.name();
	//unsigned v = golden_ratio_hash(static_cast<unsigned>((p_int)mangled_name_ptr));

	return v;
}


} // namespace nestedsums

#endif // ndef __NESTEDSUMS_UTILS_H__

