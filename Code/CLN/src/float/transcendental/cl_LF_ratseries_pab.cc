// eval_rational_series().

// General includes.
#include "cln_private.h"

// Specification.
#include "float/transcendental/cl_LF_tran.h"


// Implementation.

#include "cln/lfloat.h"
#include "cln/integer.h"
#include "cln/exception.h"
#include "float/lfloat/cl_LF.h"

namespace cln {

// Subroutine.
// Evaluates S = sum(N1 <= n < N2, a(n)/b(n) * (p(N1)...p(n))/(q(N1)...q(n)))
// and returns P = p(N1)...p(N2-1), Q = q(N1)...q(N2-1), B = B(N1)...B(N2-1)
// and T = B*Q*S (all integers). On entry N1 < N2.
// P will not be computed if a NULL pointer is passed.

static void eval_pab_series_aux (uintC N1, uintC N2,
                                 const cl_pab_series& args,
                                 cl_I* P, cl_I* B, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		throw runtime_exception(); break;
	case 1:
		if (P) { *P = args.pv[N1]; }
		*B = args.bv[N1];
		*T = args.av[N1] * args.pv[N1];
		break;
	case 2: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		if (P) { *P = p01; }
		*B = args.bv[N1] * args.bv[N1+1];
		*T = args.bv[N1+1] * args.av[N1] * args.pv[N1]
		   + args.bv[N1] * args.av[N1+1] * p01;
		break;
		}
	case 3: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		var cl_I p012 = p01 * args.pv[N1+2];
		if (P) { *P = p012; }
		var cl_I b12 = args.bv[N1+1] * args.bv[N1+2];
		*B = args.bv[N1] * b12;
		*T = b12 * args.av[N1] * args.pv[N1]
		   + args.bv[N1] * (args.bv[N1+2] * args.av[N1+1] * p01
		                    + args.bv[N1+1] * args.av[N1+2] * p012);
		break;
		}
	case 4: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		var cl_I p012 = p01 * args.pv[N1+2];
		var cl_I p0123 = p012 * args.pv[N1+3];
		if (P) { *P = p0123; }
		var cl_I b01 = args.bv[N1] * args.bv[N1+1];
		var cl_I b23 = args.bv[N1+2] * args.bv[N1+3];
		*B = b01 * b23;
		*T = b23 * (args.bv[N1+1] * args.av[N1] * args.pv[N1]
		            + args.bv[N1] * args.av[N1+1] * p01)
		   + b01 * (args.bv[N1+3] * args.av[N1+2] * p012
		            + args.bv[N1+2] * args.av[N1+3] * p0123);
		break;
		}
	default: {
		var uintC Nm = (N1+N2)/2; // midpoint
		// Compute left part.
		var cl_I LP, LB, LT;
		eval_pab_series_aux(N1,Nm,args,&LP,&LB,&LT);
		// Compute right part.
		var cl_I RP, RB, RT;
		eval_pab_series_aux(Nm,N2,args,(P?&RP:(cl_I*)0),&RB,&RT);
		// Put together partial results.
		if (P) { *P = LP*RP; }
		*B = LB*RB;
		// S = LS + LP * RS, so T = RB*LT + LB*LP*RT.
		*T = RB*LT + LB*LP*RT;
		break;
		}
	}
}

const cl_LF eval_rational_series (uintC N, const cl_pab_series& args, uintC len)
{
	if (N==0)
		return cl_I_to_LF(0,len);
	var cl_I B, T;
	eval_pab_series_aux(0,N,args,NULL,&B,&T);
	return cl_I_to_LF(T,len) / cl_I_to_LF(B,len);
}
// Bit complexity (if p(n), q(n), a(n), b(n) have length O(log(n))):
// O(log(N)^2*M(N)).

}  // namespace cln
