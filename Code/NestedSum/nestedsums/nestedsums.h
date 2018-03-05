
/** @file nestedsums.h
 *
 * Top level include file for the nestedsums library.
 * This file should be included by all applications using the library.
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

/** \mainpage Nestedsums library
 *
 * \author Stefan Weinzierl
 * \version 1.5.1
 *
 * The nestedsums library can be used for the symbolic expansion
 * of a certain class of transcendental functions.
 *
 * The library is described in :
 * S. Weinzierl, "Symbolic Expansion of Transcendental Functions",
 * Comp. Phys. Comm. 145, (2002), 357,
 *  http://arXiv.org/abs/math-ph/0201011
 *
 * Downloads for the nestedsums library:
 * The current version is 1.5.1. It requires at least GiNaC version 1.7.
 * The source code can be downloaded from
 *  http://wwwthep.physik.uni-mainz.de/~stefanw/download/nestedsums-1.5.1.tar.gz
 *
 * A version, which works with GiNaC version 1.5 or 1.6 can be downloaded from
 *  http://wwwthep.physik.uni-mainz.de/~stefanw/download/nestedsums-1.4.12.tar.gz
 *
 * An older version, which works with GiNaC version 1.4 can be downloaded from
 *  http://wwwthep.physik.uni-mainz.de/~stefanw/download/nestedsums-1.4.11.tar.gz
 *
 * An even older version, which works with GiNaC version 1.3 can be downloaded from
 *  http://wwwthep.physik.uni-mainz.de/~stefanw/download/nestedsums-1.4.9.tar.gz
 *
 * A medieval version, which works with GiNaC version 1.1 or 1.2 can be downloaded from
 *  http://wwwthep.physik.uni-mainz.de/~stefanw/download/nestedsums-1.4.5.tar.gz
 *
 * A prehistoric version, which works with GiNaC version 1.0 can be downloaded from
 *  http://wwwthep.physik.uni-mainz.de/~stefanw/download/nestedsums-1.1.1.tar.gz
 *
 * The algorithms for the expansion are based on algebraic manipulations of
 * nested sums and are described in detail in :
 * S. Moch, P. Uwer and S. Weinzierl,
 * "Nested Sums, Expansion of Transcendental Functions and Multi-Scale
 *  Multi-Loop Integrals", J. Math. Phys. 43, (2002), 3363,
 *  http://arXiv.org/abs/hep-ph/0110083
 *
 * Algorithms for the expansion around rational numbers can be found in :
 * S. Weinzierl,
 * "Expansion around half-integer values, binomial sums and inverse binomial sums",
 * J. Math. Phys. 45, (2004), 2656,
 * http://arXiv.org/abs/hep-ph/0402131
 * 
 * The library is written in C++ and uses the GiNaC library.
 * GiNaC can be obtained from
 *  http://www.ginac.de
 *
 * Documentation of the library is inserted as comment lines inside the source
 * code and can be extracted with the help of the documentation system "doxygen".
 * Doxygen is available from
 *  http://www.stack.nl/~dimitri/doxygen
 *
 * The functions which the library provides can also be used interactively with
 * the help of the gTybalt program.
 * gTybalt is available from
 *  http://wwwthep.physik.uni-mainz.de/~stefanw/gtybalt.html
 *
 * When the library is used for scientific work that leads to publication in a 
 * scientific journal, please refer to this program as :
 *  S. Weinzierl, "Symbolic Expansion of Transcendental Functions",
 *  Comp. Phys. Comm. 145, (2002), 357, (math-ph/0201011)
 *
 */ 

/** \namespace nestedsums
 *
 * All classes and functions of the nestedsums package are defined
 * in the nestedsums namespace.
 *
 */

#ifndef __NESTEDSUMS_NESTEDSUMS_H__
#define __NESTEDSUMS_NESTEDSUMS_H__

//#define _DEBUG

#include "version.h"
#include "flags.h"
#include "symbol_factory.h"
#include "hash_entry.h"

#include "root_of_unity.h"

#include "basic_letter.h"
#include "letter.h"
#include "unit_letter.h"

#include "Zsum.h"
#include "Ssum.h"
#include "Csum.h"
#include "Bsum.h"
#include "Euler_Zagier_sum.h"
#include "harmonic_sum.h"
#include "multiple_polylog.h"
#include "harmonic_polylog.h"
#include "nielsen_polylog.h"
#include "classical_polylog.h"
#include "multiple_zeta_value.h"
#include "Ssum_to_Infinity.h"
#include "harmonic_sum_to_Infinity.h"

#include "polygamma.h"
#include "list_polygamma.h"

#include "transcendental_A.h"
#include "transcendental_B.h"
#include "transcendental_C.h"
#include "transcendental_D.h"

#include "transc_fct_A.h"
#include "transc_fct_B.h"
#include "transc_fct_C.h"
#include "transc_fct_D.h"

#include "constants.h"
#include "helpers.h"
#include "functions.h"

#endif // ndef __NESTEDSUMS_NESTEDSUMS_H__

