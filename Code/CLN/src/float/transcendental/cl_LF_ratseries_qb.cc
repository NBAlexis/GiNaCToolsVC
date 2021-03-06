// eval_rational_series<bool>().

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

static void eval_qb_series_aux (uintC N1, uintC N2,
                                const cl_qb_series& args,
                                cl_I* Q, cl_I* B, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		throw runtime_exception(); break;
	case 1:
		*Q = args.qv[N1];
		*B = args.bv[N1];
		*T = 1;
		break;
	case 2: {
		*Q = args.qv[N1] * args.qv[N1+1];
		*B = args.bv[N1] * args.bv[N1+1];
		*T = args.bv[N1+1] * args.qv[N1+1]
		   + args.bv[N1];
		break;
		}
	case 3: {
		var cl_I q12 = args.qv[N1+1] * args.qv[N1+2];
		*Q = args.qv[N1] * q12;
		var cl_I b12 = args.bv[N1+1] * args.bv[N1+2];
		*B = args.bv[N1] * b12;
		*T = b12 * q12
		   + args.bv[N1] * (args.bv[N1+2] * args.qv[N1+2]
		                    + args.bv[N1+1]);
		break;
		}
	case 4: {
		var cl_I q23 = args.qv[N1+2] * args.qv[N1+3];
		var cl_I q123 = args.qv[N1+1] * q23;
		*Q = args.qv[N1] * q123;
		var cl_I b01 = args.bv[N1] * args.bv[N1+1];
		var cl_I b23 = args.bv[N1+2] * args.bv[N1+3];
		*B = b01 * b23;
		*T = b23 * (args.bv[N1+1] * q123
		            + args.bv[N1] * q23)
		   + b01 * (args.bv[N1+3] * args.qv[N1+3]
		            + args.bv[N1+2]);
		break;
		}
	default: {
		var uintC Nm = (N1+N2)/2; // midpoint
		// Compute left part.
		var cl_I LQ, LB, LT;
		eval_qb_series_aux(N1,Nm,args,&LQ,&LB,&LT);
		// Compute right part.
		var cl_I RQ, RB, RT;
		eval_qb_series_aux(Nm,N2,args,&RQ,&RB,&RT);
		// Put together partial results.
		*Q = LQ*RQ;
		*B = LB*RB;
		// S = LS + 1/LQ * RS, so T = RB*RQ*LT + LB*RT.
		*T = RB*RQ*LT + LB*RT;
		break;
		}
	}
}

template<>
const cl_LF eval_rational_series<false> (uintC N, const cl_qb_series& args, uintC len)
{
	if (N==0)
		return cl_I_to_LF(0,len);
	var cl_I Q, B, T;
	eval_qb_series_aux(0,N,args,&Q,&B,&T);
	return cl_I_to_LF(T,len) / cl_I_to_LF(B*Q,len);
}

static void eval_qb_series_aux (uintC N1, uintC N2,
                                cl_qb_series_stream& args,
                                cl_I* Q, cl_I* B, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		throw runtime_exception(); break;
	case 1: {
		var cl_qb_series_term v0 = args.next(); // [N1]
		*Q = v0.q;
		*B = v0.b;
		*T = 1;
		break;
		}
	case 2: {
		var cl_qb_series_term v0 = args.next(); // [N1]
		var cl_qb_series_term v1 = args.next(); // [N1+1]
		*Q = v0.q * v1.q;
		*B = v0.b * v1.b;
		*T = v1.b * v1.q + v0.b;
		break;
		}
	case 3: {
		var cl_qb_series_term v0 = args.next(); // [N1]
		var cl_qb_series_term v1 = args.next(); // [N1+1]
		var cl_qb_series_term v2 = args.next(); // [N1+2]
		var cl_I q12 = v1.q * v2.q;
		*Q = v0.q * q12;
		var cl_I b12 = v1.b * v2.b;
		*B = v0.b * b12;
		*T = b12 * q12 + v0.b * (v2.b * v2.q + v1.b);
		break;
		}
	case 4: {
		var cl_qb_series_term v0 = args.next(); // [N1]
		var cl_qb_series_term v1 = args.next(); // [N1+1]
		var cl_qb_series_term v2 = args.next(); // [N1+2]
		var cl_qb_series_term v3 = args.next(); // [N1+3]
		var cl_I q23 = v2.q * v3.q;
		var cl_I q123 = v1.q * q23;
		*Q = v0.q * q123;
		var cl_I b01 = v0.b * v1.b;
		var cl_I b23 = v2.b * v3.b;
		*B = b01 * b23;
		*T = b23 * (v1.b * q123 + v0.b * q23)
		   + b01 * (v3.b * v3.q + v2.b);
		break;
		}
	default: {
		var uintC Nm = (N1+N2)/2; // midpoint
		// Compute left part.
		var cl_I LQ, LB, LT;
		eval_qb_series_aux(N1,Nm,args,&LQ,&LB,&LT);
		// Compute right part.
		var cl_I RQ, RB, RT;
		eval_qb_series_aux(Nm,N2,args,&RQ,&RB,&RT);
		// Put together partial results.
		*Q = LQ*RQ;
		*B = LB*RB;
		// S = LS + 1/LQ * RS, so T = RB*RQ*LT + LB*RT.
		*T = RB*RQ*LT + LB*RT;
		break;
		}
	}
}

template<>
const cl_LF eval_rational_series<false> (uintC N, cl_qb_series_stream& args, uintC len)
{
	if (N==0)
		return cl_I_to_LF(0,len);
	var cl_I Q, B, T;
	eval_qb_series_aux(0,N,args,&Q,&B,&T);
	return cl_I_to_LF(T,len) / cl_I_to_LF(B*Q,len);
}

// Bit complexity (if p(n), q(n), a(n), b(n) have length O(log(n))):
// O(log(N)^2*M(N)).

}  // namespace cln
