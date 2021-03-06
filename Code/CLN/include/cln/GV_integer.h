// General vectors of integers.

#ifndef _CL_GV_INTEGER_H
#define _CL_GV_INTEGER_H

#include "cln/number.h"
#include "cln/GV_rational.h"
#include "cln/integer_class.h"
#include "cln/io.h"

namespace cln {

// A vector of integers is *not* just a normal vector of numbers (the vectorops
// support the maxbits() operation), but we treat can it like this nevertheless.

template <>
struct CLN_TEMPLATE cl_heap_GV<cl_I> : cl_heap {
	cl_GV_inner<cl_I> v;
	// here room for the elements
    inline sintC maxbits () const;
};
typedef cl_heap_GV<cl_I> cl_heap_GV_I;

typedef cl_GV_index<cl_I> cl_GV_I_index;

struct CLN_API cl_GV_I : public cl_GV<cl_I,cl_GV_RA> {
public:
	// Constructors.
	inline cl_GV_I ();
    inline cl_GV_I (const cl_GV_I&);
	// Create a vector of unconstrained integers.
    inline explicit cl_GV_I (std::size_t len);
	// Create a vector of m-bit integers (>=0, <2^m).
    inline cl_GV_I (std::size_t len, sintC m);
	// Assignment operators.
    inline cl_GV_I& operator= (const cl_GV_I&);
	// Number m of bits allowed per element (-1 if unconstrained).
    inline sintC maxbits () const
	{
		return ((const cl_heap_GV_I *) pointer)->maxbits();
	}
	// Private pointer manipulations.
    inline cl_GV_I (cl_heap_GV_I* p) : cl_GV<cl_I,cl_GV_RA> (p) {}
    inline cl_GV_I (cl_private_thing p) : cl_GV<cl_I,cl_GV_RA> (p) {}
};
inline cl_GV_I::cl_GV_I (const cl_GV_I& x) : cl_GV<cl_I,cl_GV_RA> (as_cl_private_thing(x)) {}
CL_DEFINE_ASSIGNMENT_OPERATOR(cl_GV_I,cl_GV_I)
extern CLN_API cl_heap_GV_I* cl_make_heap_GV_I (std::size_t len);
inline cl_GV_I::cl_GV_I (std::size_t len)
	: cl_GV<cl_I,cl_GV_RA> (cl_make_heap_GV_I(len)) {}
extern CLN_API cl_heap_GV_I* cl_make_heap_GV_I (std::size_t len, sintC m);
inline cl_GV_I::cl_GV_I (std::size_t len, sintC m)
	: cl_GV<cl_I,cl_GV_RA> (cl_make_heap_GV_I(len,m)) {}

// Private pointer manipulations. Never throw away a `struct cl_heap_GV_I *'!
extern CLN_API const cl_GV_I cl_null_GV_I;
inline cl_GV_I::cl_GV_I ()
	: cl_GV<cl_I,cl_GV_RA> ((cl_heap_GV_I*) cl_null_GV_I) {}
class CLN_API cl_GV_I_init_helper
{
	static int count;
public:
    inline cl_GV_I_init_helper();
    inline ~cl_GV_I_init_helper();
};
static cl_GV_I_init_helper cl_GV_I_init_helper_instance;

// Copy a vector.
extern CLN_API const cl_GV_I copy (const cl_GV_I&);

// Output.
extern CLN_API cl_print_flags default_print_flags;
extern CLN_API void print_vector(std::ostream& stream, const cl_print_flags& flags, void(*fun) (std::ostream&, const cl_print_flags&, const cl_number&), const cl_GV_number& vector);
extern CLN_API void print_integer(std::ostream& stream, const cl_print_flags& flags, const cl_I& z);
inline void fprint (std::ostream& stream, const cl_GV_I& x)
{
	print_vector(stream, default_print_flags,
	             (void (*) (std::ostream&, const cl_print_flags&, const cl_number&))
	             (void (*) (std::ostream&, const cl_print_flags&, const cl_I&))
	             &print_integer,
	             x);
}
CL_DEFINE_PRINT_OPERATOR(cl_GV_I)

// Debugging support.
#ifdef CL_DEBUG
extern int cl_GV_I_debug_module;
CL_FORCE_LINK(cl_GV_I_debug_dummy, cl_GV_I_debug_module)
#endif

}  // namespace cln

#endif /* _CL_GV_INTEGER_H */
