//=============================================================================
// FILENAME : nestedsum_private.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/5/2018 nbale]
//=============================================================================
#pragma once

//total header

#ifndef _NESTEDSUM_PRIVATE_H_
#define _NESTEDSUM_PRIVATE_H_

#include "cln_public.h"
#include "ginac_public.h"

#define NESTEDSUMS_API __declspec(dllexport)

#undef GINAC_API
#define GINAC_API NESTEDSUMS_API

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


//#undef GINAC_DECLARE_UNARCHIVER
//#undef DECLARE_FUNCTION_2P
//#undef DECLARE_FUNCTION_3P
//#undef GINAC_DECLARE_REGISTERED_CLASS
//#undef GINAC_DECLARE_REGISTERED_CLASS_COMMON
//
//#define GINAC_DECLARE_UNARCHIVER(classname)			\
//class NESTEDSUMS_API classname ## _unarchiver					\
//{								\
//	static int usecount;					\
//public:								\
//	static GiNaC::basic* create();				\
//	classname ## _unarchiver();				\
//	~ classname ## _unarchiver();				\
//};								\
//static classname ## _unarchiver classname ## _unarchiver_instance
//
//#define DECLARE_FUNCTION_2P(NAME) \
//class NESTEDSUMS_API NAME##_SERIAL { public: static unsigned serial; }; \
//const unsigned NAME##_NPARAMS = 2; \
//template< typename T1, typename T2 > const GiNaC::function NAME( const T1 & p1, const T2 & p2 ) { \
//	return GiNaC::function(NAME##_SERIAL::serial, GiNaC::ex(p1), GiNaC::ex(p2) ); \
//}
//
//#define DECLARE_FUNCTION_3P(NAME) \
//class NESTEDSUMS_API NAME##_SERIAL { public: static unsigned serial; }; \
//const unsigned NAME##_NPARAMS = 3; \
//template< typename T1, typename T2, typename T3 > const GiNaC::function NAME( const T1 & p1, const T2 & p2, const T3 & p3 ) { \
//	return GiNaC::function(NAME##_SERIAL::serial, GiNaC::ex(p1), GiNaC::ex(p2), GiNaC::ex(p3) ); \
//}
//
//#define GINAC_DECLARE_REGISTERED_CLASS_COMMON(classname)	\
//private: \
//	static GiNaC::registered_class_info reg_info; \
//public: \
//	static GiNaC::registered_class_info &get_class_info_static() { return reg_info; } \
//	class NESTEDSUMS_API visitor { \
//	public: \
//		virtual void visit(const classname &) = 0; \
//		virtual ~visitor() {}; \
//	};
//
////Must have classnamereturn!!!
//
//#define GINAC_DECLARE_REGISTERED_CLASS(classname, supername) \
//	GINAC_DECLARE_REGISTERED_CLASS_COMMON(classname) \
//	template<class B, typename... Args> friend B & dynallocate(Args &&... args); \
//	typedef supername inherited; \
//	classname(); \
//	GiNaC::basic * duplicate() const override { \
//		classname * bp = new classname(*this); \
//		bp->setflag(GiNaC::status_flags::dynallocated);	\
//		return bp; \
//	} \
//	\
//	void accept(GiNaC::visitor & v) const override \
//	{ \
//		if (visitor *p = dynamic_cast<visitor *>(&v)) \
//			p->visit(*this); \
//		else \
//			inherited::accept(v); \
//	} \
//	const GiNaC::registered_class_info &get_class_info() const override { return classname::get_class_info_static(); } \
//	GiNaC::registered_class_info &get_class_info() override { return classname::get_class_info_static(); } \
//	const char *class_name() const override { return classname::get_class_info_static().options.get_name(); } \
//protected: \
//	int compare_same_type(const GiNaC::basic & other) const override; \
//private:


#include "config.h"

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

#endif //#ifndef _NESTEDSUM_PRIVATE_H_

//=============================================================================
// END OF FILE
//=============================================================================
