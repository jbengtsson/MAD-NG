/*
 o-----------------------------------------------------------------------------o
 |
 | TPSA Example 5
 |
 | Methodical Accelerator Design - Copyright (c) 2016+
 | Support: http://cern.ch/mad  - mad at cern.ch
 | Authors: L. Deniau, laurent.deniau at cern.ch
 | Contrib: -
 |
 o-----------------------------------------------------------------------------o
 | You can redistribute this file and/or modify it under the terms of the GNU
 | General Public License GPLv3 (or later), as published by the Free Software
 | Foundation. This file is distributed in the hope that it will be useful, but
 | WITHOUT ANY WARRANTY OF ANY KIND. See http://gnu.org/licenses for details.
 o-----------------------------------------------------------------------------o

  WARNING: this file is not part of MAD, it must be used as an example with the
           standalone library, see mad/src/REAME.GTPSA for more info.
*/

#include "mad_cst.h"
#include "mad_tpsa.h"

int main(void)
{
  // descriptor for TPSA with 4 maps variables of order 3,3,2,2 and
  //                          2 knobs of order 1,1
  //                          4 variables of order 2,2,1,1 (i.e. maps variables)
  //                            with knobs cross-terms of order 1
  const desc_t *d = mad_desc_newkv(4, (ord_t[]){3,3,2,2},
                                   2, (ord_t[]){1,1},
                                   4, (ord_t[]){2,2,1,1}, 1);

  // two TPSAs, t2 is same as t1
  tpsa_t *t1 = mad_tpsa_newd(d, mad_tpsa_default);
  tpsa_t *t2 = mad_tpsa_new(t1, mad_tpsa_same);

  // set order 0 and 1 (quick and dirty!)
  mad_tpsa_setv(t1, 0, 1+6, (double[]){M_PI/6, 1,1,1,1,1,1});
  mad_tpsa_print(t1, "ini", 0,0);

  mad_tpsa_sin(t1, t2);
  mad_tpsa_print(t2, "sin", 0,0);
  mad_tpsa_del(t1);

  mad_tpsa_asin(t2, t2);            // asin(x) = -i*ln(i*x + sqrt(1-x^2))
  mad_tpsa_print(t2, "asin", 0, 0); // see the accuracy of asin(sin)
  mad_tpsa_del(t2);

  mad_desc_cleanup();
  return 0;
}