// cl_RA_to_SF().

// General includes.
#include "cln_private.h"

// Specification.
#include "float/sfloat/cl_SF.h"


// Implementation.

#include "rational/cl_RA.h"
#include "cln/integer.h"
#include "integer/cl_I.h"

namespace cln {

const cl_SF cl_RA_to_SF (const cl_RA& x)
{
// Methode:
// x ganz -> klar.
// x = +/- a/b mit Integers a,b>0:
//   Seien n,m so gewählt, daß
//     2^(n-1) <= a < 2^n, 2^(m-1) <= b < 2^m.
//   Dann ist 2^(n-m-1) < a/b < 2^(n-m+1).
//   Berechne n=(integer-length a) und m=(integer-length b) und
//   floor(2^(-n+m+18)*a/b) :
//   Bei n-m>=18 dividiere a durch (ash b (n-m-18)),
//   bei n-m<18 dividiere (ash a (-n+m+18)) durch b.
//   Der erste Wert ist >=2^17, <2^19.
//   Falls er >=2^18 ist, runde 2 Bits weg,
//   falls er <2^18 ist, runde 1 Bit weg.
      if (integerp(x)) {
        DeclareType(cl_I,x);
        return cl_I_to_SF(x);
      }
 {    // x Ratio
      DeclareType(cl_RT,x);
      var cl_I a = numerator(x); // +/- a
      var const cl_I& b = denominator(x); // b
      var cl_signean sign = -(cl_signean)minusp(a); // Vorzeichen
      if (!(sign==0)) { a = -a; } // Betrag nehmen, liefert a
      var sintC lendiff = (sintC)integer_length(a) // (integer-length a)
                          - (sintC)integer_length(b); // (integer-length b)
      if (lendiff > SF_exp_high-SF_exp_mid) // Exponent >= n-m > Obergrenze ?
        { throw floating_point_overflow_exception(); } // -> Overflow
      if (lendiff < SF_exp_low-SF_exp_mid-2) // Exponent <= n-m+2 < Untergrenze ?
        { if (underflow_allowed())
            { throw floating_point_underflow_exception(); } // -> Underflow
            else
            { return SF_0; }
        }
      var cl_I zaehler;
      var cl_I nenner;
      if (lendiff >= SF_mant_len+2)
        // n-m-18>=0
        { nenner = ash(b,lendiff - (SF_mant_len+2)); // (ash b n-m-18)
          zaehler = a; // a
        }
        else
        { zaehler = ash(a,(SF_mant_len+2) - lendiff); // (ash a -n+m+18)
          nenner = b; // b
        }
      // Division zaehler/nenner durchführen:
      var cl_I_div_t q_r = cl_divide(zaehler,nenner);
      var cl_I& q = q_r.quotient;
      var cl_I& r = q_r.remainder;
      // 2^17 <= q < 2^19, also ist q Fixnum.
      var uint32 mant = static_cast<uint32>(FN_to_UV(q));
      if (mant >= bit(SF_mant_len+2))
        // 2^18 <= q < 2^19, schiebe um 2 Bits nach rechts
        { var uintL rounding_bits = mant & (bit(2)-1);
          lendiff = lendiff+1; // Exponent := n-m+1
          mant = mant >> 2;
          if ( (rounding_bits < bit(1)) // 00,01 werden abgerundet
               || ( (rounding_bits == bit(1)) // 10
                    && (eq(r,0)) // und genau halbzahlig (r=0)
                    && ((mant & bit(0)) ==0) // -> round-to-even
             )    )
            // abrunden
            goto ab;
            else
            // aufrunden
            goto auf;
        }
        else
        { var uintL rounding_bit = mant & bit(0);
          mant = mant >> 1;
          if ( (rounding_bit == 0) // 0 wird abgerundet
               || ( (eq(r,0)) // genau halbzahlig (r=0)
                    && ((mant & bit(0)) ==0) // -> round-to-even
             )    )
            // abrunden
            goto ab;
            else
            // aufrunden
            goto auf;
        }
      auf:
      mant += 1;
      if (mant >= bit(SF_mant_len+1)) // rounding overflow?
        { mant = mant>>1; lendiff = lendiff+1; }
      ab:
      // Fertig.
      return encode_SF(sign,lendiff,mant);
}}

}  // namespace cln