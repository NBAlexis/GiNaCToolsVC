// class cl_property_list.

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/proplist.h"


// Implementation.

namespace cln {

cl_property_list::~cl_property_list ()
{
	while (list) {
		var cl_property* l = list;
		list = l->next;
		delete l;
	}
}

}  // namespace cln
