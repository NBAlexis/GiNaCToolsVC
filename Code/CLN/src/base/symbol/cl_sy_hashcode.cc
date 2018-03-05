// cln/symbol.hashcode().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/symbol.h"


// Implementation.

#include "base/cl_offsetof.h"

#ifdef __CLN_MS_VC__
#pragma warning (disable : 4146)
#endif

namespace cln {

#define declare_alignof(where,type)  \
  struct CONCAT(aligndummy,__LINE__) { char slot1; type slot2; }; \
  const unsigned long where = offsetof(CONCAT(aligndummy,__LINE__), slot2);

unsigned long hashcode (const cl_symbol& s)
{
	// Strings don't move in memory, so we can just take the address.
	declare_alignof(string_alignment,cl_heap_string);
	return static_cast<unsigned long>((uintP)(s.pointer)
	       / (string_alignment & -string_alignment)); // divide by power of 2
}

}  // namespace cln
