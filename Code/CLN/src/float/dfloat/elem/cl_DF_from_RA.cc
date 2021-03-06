// cl_RA_to_DF().

// General includes.
#include "cln_private.h"

// Specification.
#include "float/dfloat/cl_DF.h"


// Implementation.

#include "rational/cl_RA.h"
#include "cln/integer.h"
#include "integer/cl_I.h"
#include "float/cl_F.h"

namespace cln {

const cl_DF cl_RA_to_DF (const cl_RA& x)
{
// Methode:
// x ganz -> klar.
// x = +/- a/b mit Integers a,b>0:
//   Seien n,m so gewählt, daß
//     2^(n-1) <= a < 2^n, 2^(m-1) <= b < 2^m.
//   Dann ist 2^(n-m-1) < a/b < 2^(n-m+1).
//   Berechne n=(integer-length a) und m=(integer-length b) und
//   floor(2^(-n+m+54)*a/b) :
//   Bei n-m>=54 dividiere a durch (ash b (n-m-54)),
//   bei n-m<54 dividiere (ash a (-n+m+54)) durch b.
//   Der erste Wert ist >=2^53, <2^55.
//   Falls er >=2^54 ist, runde 2 Bits weg,
//   falls er <2^54 ist, runde 1 Bit weg.
      if (integerp(x)) {
        DeclareType(cl_I,x);
        return cl_I_to_DF(x);
      }
 {    // x Ratio
      DeclareType(cl_RT,x);
      var cl_I a = numerator(x); // +/- a
      var const cl_I& b = denominator(x); // b
      var cl_signean sign = -(cl_signean)minusp(a); // Vorzeichen
      if (!(sign==0)) { a = -a; } // Betrag nehmen, liefert a
      var sintC lendiff = (sintC)integer_length(a) // (integer-length a)
                          - (sintC)integer_length(b); // (integer-length b)
      if (lendiff > DF_exp_high-DF_exp_mid) // Exponent >= n-m > Obergrenze ?
        { throw floating_point_overflow_exception(); } // -> Overflow
      if (lendiff < DF_exp_low-DF_exp_mid-2) // Exponent <= n-m+2 < Untergrenze ?
        { if (underflow_allowed())
            { throw floating_point_underflow_exception(); } // -> Underflow
            else
            { return cl_DF_0; }
        }
      var cl_I zaehler;
      var cl_I nenner;
      if (lendiff >= DF_mant_len+2)
        // n-m-54>=0
        { nenner = ash(b,lendiff - (DF_mant_len+2)); // (ash b n-m-54)
          zaehler = a; // a
        }
        else
        { zaehler = ash(a,(DF_mant_len+2) - lendiff); // (ash a -n+m+54)
          nenner = b; // b
        }
      // Division zaehler/nenner durchführen:
      var cl_I_div_t q_r = cl_divide(zaehler,nenner);
      var cl_I& q = q_r.quotient;
      var cl_I& r = q_r.remainder;
      #if (cl_word_size==64)
      #if (cl_value_len>=55)
      // 2^53 <= q < 2^55: q is fixnum.
      var uint64 mant = FN_to_UV(q);
      #else
      // 2^53 <= q < 2^55: q is bignum with one Digit.
      var const uintD* ptr = BN_MSDptr(q);
      var uint64 mant = get_max64_Dptr(55,ptr);
      #endif
      if (mant >= bit(DF_mant_len+2))
        // 2^54 <= q < 2^55, schiebe um 2 Bits nach rechts
        { var uint64 rounding_bits = mant & (bit(2)-1);
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
        { var uint64 rounding_bit = mant & bit(0);
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
      if (mant >= bit(DF_mant_len+1)) // rounding overflow?
        { mant = mant>>1; lendiff = lendiff+1; }
      ab:
      // Fertig.
      return encode_DF(sign,lendiff,mant);
      #else  // (cl_word_size<64)
      // 2^53 <= q < 2^55: q is bignum with two Digits.
      var const uintD* ptr = BN_MSDptr(q);
      var uint32 manthi = get_max32_Dptr(23,ptr);
      var uint32 mantlo = get_32_Dptr(ptr mspop ceiling(23,intDsize));
      if (manthi >= bit(DF_mant_len-32+2))
        // 2^54 <= q < 2^55, schiebe um 2 Bits nach rechts
        { var uintL rounding_bits = mantlo & (bit(2)-1);
          lendiff = lendiff+1; // Exponent := n-m+1
          mantlo = (mantlo >> 2) | (manthi << 30); manthi = manthi >> 2;
          if ( (rounding_bits < bit(1)) // 00,01 werden abgerundet
               || ( (rounding_bits == bit(1)) // 10
                    && (eq(r,0)) // und genau halbzahlig (r=0)
                    && ((mantlo & bit(0)) ==0) // -> round-to-even
             )    )
            // abrunden
            goto ab;
            else
            // aufrunden
            goto auf;
        }
        else
        { var uintL rounding_bit = mantlo & bit(0);
          mantlo = (mantlo >> 1) | (manthi << 31); manthi = manthi >> 1;
          if ( (rounding_bit == 0) // 0 wird abgerundet
               || ( (eq(r,0)) // genau halbzahlig (r=0)
                    && ((mantlo & bit(0)) ==0) // -> round-to-even
             )    )
            // abrunden
            goto ab;
            else
            // aufrunden
            goto auf;
        }
      auf:
      mantlo += 1;
      if (mantlo==0)
        { manthi += 1;
          if (manthi >= bit(DF_mant_len-32+1)) // rounding overflow?
            { manthi = manthi>>1; lendiff = lendiff+1; }
        }
      ab:
      // Fertig.
      return encode_DF(sign,lendiff,manthi,mantlo);
      #endif
}}

}  // namespace cln
