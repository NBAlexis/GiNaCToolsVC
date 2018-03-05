/** @file operators.h
 *
 *  Interface to GiNaC's overloaded operators. */

/*
 *  GiNaC Copyright (C) 1999-2018 Johannes Gutenberg University Mainz, Germany
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
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef GINAC_OPERATORS_H
#define GINAC_OPERATORS_H

#include <iosfwd>

namespace GiNaC {

class GINAC_API ex;
class GINAC_API numeric;
class GINAC_API relational;

// binary arithmetic operators ex with ex
GINAC_API const ex operator+(const ex & lh, const ex & rh);
GINAC_API const ex operator-(const ex & lh, const ex & rh);
GINAC_API const ex operator*(const ex & lh, const ex & rh);
GINAC_API const ex operator/(const ex & lh, const ex & rh);

// binary arithmetic operators numeric with numeric
GINAC_API const numeric operator+(const numeric & lh, const numeric & rh);
GINAC_API const numeric operator-(const numeric & lh, const numeric & rh);
GINAC_API const numeric operator*(const numeric & lh, const numeric & rh);
GINAC_API const numeric operator/(const numeric & lh, const numeric & rh);

// binary arithmetic assignment operators with ex
GINAC_API ex & operator+=(ex & lh, const ex & rh);
GINAC_API ex & operator-=(ex & lh, const ex & rh);
GINAC_API ex & operator*=(ex & lh, const ex & rh);
GINAC_API ex & operator/=(ex & lh, const ex & rh);

// binary arithmetic assignment operators with numeric
GINAC_API numeric & operator+=(numeric & lh, const numeric & rh);
GINAC_API numeric & operator-=(numeric & lh, const numeric & rh);
GINAC_API numeric & operator*=(numeric & lh, const numeric & rh);
GINAC_API numeric & operator/=(numeric & lh, const numeric & rh);

// unary operators
GINAC_API const ex operator+(const ex & lh);
GINAC_API const ex operator-(const ex & lh);

GINAC_API const numeric operator+(const numeric & lh);
GINAC_API const numeric operator-(const numeric & lh);

// increment / decrement operators
GINAC_API ex & operator++(ex & rh);
GINAC_API ex & operator--(ex & rh);
GINAC_API const ex operator++(ex & lh, int);
GINAC_API const ex operator--(ex & lh, int);

GINAC_API numeric& operator++(numeric & rh);
GINAC_API numeric& operator--(numeric & rh);
GINAC_API const numeric operator++(numeric & lh, int);
GINAC_API const numeric operator--(numeric & lh, int);

// binary relational operators ex with ex
GINAC_API const relational operator==(const ex & lh, const ex & rh);
GINAC_API const relational operator!=(const ex & lh, const ex & rh);
GINAC_API const relational operator<(const ex & lh, const ex & rh);
GINAC_API const relational operator<=(const ex & lh, const ex & rh);
GINAC_API const relational operator>(const ex & lh, const ex & rh);
GINAC_API const relational operator>=(const ex & lh, const ex & rh);

// input/output stream operators
GINAC_API std::ostream & operator<<(std::ostream & os, const ex & e);
GINAC_API std::istream & operator>>(std::istream & is, ex & e);

// input/output stream manipulators
GINAC_API std::ostream & dflt(std::ostream & os);
GINAC_API std::ostream & latex(std::ostream & os);
GINAC_API std::ostream & python(std::ostream & os);
GINAC_API std::ostream & python_repr(std::ostream & os);
GINAC_API std::ostream & tree(std::ostream & os);
GINAC_API std::ostream & csrc(std::ostream & os); // same as csrc_double
GINAC_API std::ostream & csrc_float(std::ostream & os);
GINAC_API std::ostream & csrc_double(std::ostream & os);
GINAC_API std::ostream & csrc_cl_N(std::ostream & os);

GINAC_API std::ostream & index_dimensions(std::ostream & os);
GINAC_API std::ostream & no_index_dimensions(std::ostream & os);

} // namespace GiNaC

#endif // ndef GINAC_OPERATORS_H
