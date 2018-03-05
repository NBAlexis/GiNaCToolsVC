//=============================================================================
// FILENAME : nestedsum_public.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/5/2018 nbale]
//=============================================================================
#pragma once

//total header

#ifndef _NESTEDSUM_PUBLIC_H_
#define _NESTEDSUM_PUBLIC_H_

//lib
#if defined(_MSC_VER)
#   if !defined(NESTEDSUMS_API)
#	define __LIB_TITLE__	"nestedsums"
#	define NESTEDSUMS_API __declspec(dllimport)
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

//#include "config.h"
#undef GINAC_DECLARE_REGISTERED_CLASS
#define GINAC_DECLARE_REGISTERED_CLASS(classname, supername) \
	GINAC_DECLARE_REGISTERED_CLASS_COMMON(classname) \
	template<class B, typename... Args> friend B & dynallocate(Args &&... args); \
	typedef supername inherited; \
	classname(); \
	GiNaC::basic * duplicate() const override { \
		classname * bp = new classname(*this); \
		bp->setflag(GiNaC::status_flags::dynallocated);	\
		return bp; \
	} \
	\
	void accept(GiNaC::visitor & v) const override \
	{ \
		if (visitor *p = dynamic_cast<visitor *>(&v)) \
			p->visit(*this); \
		else \
			inherited::accept(v); \
	} \
	const GiNaC::registered_class_info &get_class_info() const override { return classname::get_class_info_static(); } \
	GiNaC::registered_class_info &get_class_info() override { return classname::get_class_info_static(); } \
	const char *class_name() const override { return classname::get_class_info_static().options.get_name(); } \
protected: \
	int compare_same_type(const GiNaC::basic & other) const override; \
private:



#include "nestedsums/version.h"
#include "nestedsums/flags.h"
#include "nestedsums/symbol_factory.h"
#include "nestedsums/hash_entry.h"

#include "nestedsums/root_of_unity.h"

#include "nestedsums/basic_letter.h"
#include "nestedsums/letter.h"
#include "nestedsums/unit_letter.h"

#include "nestedsums/Zsum.h"
#include "nestedsums/Ssum.h"
#include "nestedsums/Csum.h"
#include "nestedsums/Bsum.h"
#include "nestedsums/Euler_Zagier_sum.h"
#include "nestedsums/harmonic_sum.h"
#include "nestedsums/multiple_polylog.h"
#include "nestedsums/harmonic_polylog.h"
#include "nestedsums/nielsen_polylog.h"
#include "nestedsums/classical_polylog.h"
#include "nestedsums/multiple_zeta_value.h"
#include "nestedsums/Ssum_to_Infinity.h"
#include "nestedsums/harmonic_sum_to_Infinity.h"

#include "nestedsums/polygamma.h"
#include "nestedsums/list_polygamma.h"

#include "nestedsums/transcendental_A.h"
#include "nestedsums/transcendental_B.h"
#include "nestedsums/transcendental_C.h"
#include "nestedsums/transcendental_D.h"

#include "nestedsums/transc_fct_A.h"
#include "nestedsums/transc_fct_B.h"
#include "nestedsums/transc_fct_C.h"
#include "nestedsums/transc_fct_D.h"

#include "nestedsums/constants.h"
#include "nestedsums/helpers.h"
#include "nestedsums/functions.h"

#endif //#ifndef _NESTEDSUM_PUBLIC_H_

//=============================================================================
// END OF FILE
//=============================================================================

