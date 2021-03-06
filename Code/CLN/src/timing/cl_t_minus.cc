// operator- (const cl_timespec&, const cl_timespec&)

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/timing.h"


// Implementation.

namespace cln {

const cl_time_duration operator- (const cl_timespec& a, const cl_timespec& b)
{
	var sintL sec = a.tv_sec - b.tv_sec;
	var sintL nsec = a.tv_nsec - b.tv_nsec;
	if (nsec < 0) {
		nsec += 1000000000;
		sec -= 1;
	}
	if (sec < 0) {
		sec = 0; nsec = 0;
	}
	return cl_time_duration(sec,nsec);
}

}  // namespace cln
