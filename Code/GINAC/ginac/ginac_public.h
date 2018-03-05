//=============================================================================
// FILENAME : ginac_public.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/4/2018 nbale]
//=============================================================================
#pragma once

//total header

#ifndef _GINAC_PUBLIC_H_
#define _GINAC_PUBLIC_H_

//lib
#if defined(_MSC_VER)
#   if !defined(GINAC_API)
#	define __LIB_TITLE__	"ginac"
#	define GINAC_API __declspec(dllimport)
#	ifdef _DEBUG
#		define __LIB_FILE__	__LIB_TITLE__ "_d.lib"
#	else
#		define __LIB_FILE__ __LIB_TITLE__ ".lib"
#	endif
#	pragma comment(lib, __LIB_FILE__)
#	pragma message("linking with " __LIB_FILE__ "...")
#	undef __LIB_FILE__
#	undef __LIB_TITLE__
#   endif
#else
#	error "We shall in WIN"
#endif

//IncludeFiles
#define __GINAC_PUBLIC 1

//Order of those are changed
#include "config.h"
#include "version.h"
#include "compiler.h"
#include "flags.h"
#include "assertion.h"
#include "class_info.h"
#include "print.h"
#include "registrar.h"
#include "ptr.h"
#include "basic.h"
#include "ex.h"
#include "archive.h"
#include "numeric.h"
#include "utils.h"
#include "constant.h"
#include "container.h"
#include "hash_seed.h"

//The path is changed, so include them directly
//#include "ginac/ginac.h"
#define IN_GINAC
#include "ginac.h"

//For polynomials
#include "polynomial/chinrem_gcd.h"
#include "polynomial/optimal_vars_finder.h"
#include "polynomial/upoly.h"
#include "polynomial/upoly_io.h"
#include "polynomial/mod_gcd.h"

#include "polynomial/collect_vargs.h"
#include "polynomial/gcd_euclid.h"
#include "polynomial/cra_garner.h"
#include "polynomial/smod_helpers.h"
#include "polynomial/euclid_gcd_wrap.h"

#include "polynomial/eval_point_finder.h"
#include "polynomial/newton_interpolate.h"
#include "polynomial/divide_in_z_p.h"
#include "polynomial/ring_traits.h"

#include "polynomial/normalize.h"
#include "polynomial/prem_uvar.h"
#include "polynomial/debug.h"
#include "polynomial/remainder.h"
#include "polynomial/eval_uvar.h"

#include "polynomial/heur_gcd_uvar.h"
#include "polynomial/interpolate_padic_uvar.h"
#include "polynomial/pgcd.h"
#include "polynomial/poly_cra.h"
#include "polynomial/sr_gcd_uvar.h"

#include "polynomial/polyfunctions.h"

#endif //#ifndef _GINAC_PUBLIC_H_

//=============================================================================
// END OF FILE
//=============================================================================

