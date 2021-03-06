// cl_FF_to_float().

// General includes.
#include "cln_private.h"

// Specification.
#include "float/ffloat/cl_FF.h"

namespace cln {

// Implementation.

void cl_FF_to_float (const cl_FF& obj, ffloatjanus* val_)
{
	var ffloat val = cl_ffloat_value(obj);
	// Der Exponent muß um FF_exp_mid-126 erniedrigt werden.
	if (FF_exp_mid>126)
	  { var uintL exp = (val >> FF_mant_len) & (bit(FF_exp_len)-1); // e
	    if (exp < FF_exp_mid-126+1)
	      { // produziere denormalisiertes Float
	        val = (val & minus_bit(FF_exp_len+FF_mant_len)) // selbes Vorzeichen
	              | (0 << FF_mant_len) // Exponent 0
	              | (((val & (bit(FF_mant_len)-1)) | bit(FF_mant_len)) // Mantisse shiften
	                 >> (FF_exp_mid-126+1 - exp) // shiften
	                );
	      }
	      else
	      { val -= (FF_exp_mid - 126) << FF_mant_len; }
	  }
	val_->eksplicit = val;
}

}  // namespace cln
