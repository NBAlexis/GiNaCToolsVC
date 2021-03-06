// expt_pos().

// General includes.
#include "cln_private.h"

// Specification.
#include "cln/integer.h"


// Implementation.

namespace cln {

const cl_I expt_pos (const cl_I& x, uintL y)
{
  // Methode:
  //   a:=x, b:=y, c:=1. [a^b*c bleibt invariant, = x^y.]
  //   Solange b>1,
  //     falls b ungerade, setze c:=a*c,
  //     setze b:=floor(b/2),
  //     setze a:=a*a.
  //   Wenn b=1, setze c:=a*c.
  //   Liefere c.
  // Oder optimiert:
  //   a:=x, b:=y.
  //   Solange b gerade, setze a:=a*a, b:=b/2. [a^b bleibt invariant, = x^y.]
  //   c:=a.
  //   Solange b:=floor(b/2) >0 ist,
  //     setze a:=a*a, und falls b ungerade, setze c:=a*c.
  //   Liefere c.
  #if 0 // unoptimiert
    var cl_I a = x;
    var uintL b = y;
    var cl_I c = 1;
    until (b == 1)
      { if (b % 2) // b ungerade?
          { c = a * c; }
        b = b >> 1; // b := (floor b 2)
        a = square(a);
      }
    return a * c;
  #else // optimiert
    var cl_I a = x;
    var uintL b = y;
    while (!(b % 2)) { a = square(a); b = b >> 1; }
    var cl_I c = a;
    until (b == 1)
      { b = b >> 1;
        a = square(a);
        if (b % 2) { c = a * c; }
      }
    return c;
  #endif
}
// Bit complexity (x of length N): O(M(N*y)).

}  // namespace cln
