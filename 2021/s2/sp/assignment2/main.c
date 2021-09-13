/* Updated 31 August 2021 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "rsa.h"
#include "bb.h"
#include "oracle.h"

int main() {
  oracle_init();

  // Set up key, plaintext, and ciphertext
  num_t m, e, c, n; 
  oracle_gete(e);
  oracle_getn(n);
  num_fromString(m, "deadbeef");
  num_modexp(c, m, e, n);

  // Blind key
  num_t c0, s0, si;

  int a = bb_blind(c0, s0, c, e, n);
  printf("Blinded:\n    ciphertext=%s\n    factor=%s\n", num_toString(c0), num_toString(s0));

  // test blinding
  bignum_t prod, q;
  num_t m0;
  num_mul(prod, m, s0); // m * s0
  num_div(q, m0, prod, n); // mod N

  // m0 = ( m * s0 ) mod N
  
  printf("Test m0=%s\n", num_toString(m0));
  if ((m0[WORDSIZE-1] & 0xFFFF0000) != 0x00020000) {
    fprintf(stderr, "Blinding failed\n");
    exit(1);
  }

  num_t test_c0;
  num_modexp(test_c0, m0, e, n);
  printf("Test c0=%s\n", num_toString(test_c0));
  for (int i = 0; i < WORDSIZE; i++) 
    if (test_c0[i] != c0[i]) {
      fprintf(stderr, "Blinding failed\n");
      exit(1);
    }

  num_t low, high ;

  char one_string[] = "11111111" ;
  num_t one ;
  num_fromString( one, one_string ) ;
  
  num_t n_tute ;
  num_fromString( c0, "5F12609D077206F34088C770758452C590A84A210BF98FB0" ) ;
  num_fromString( n_tute, "125de34213bfd0f8048032138f417f7f" ) ;
  bb_step0( low, high, si, c0, e, n ) ;

  return 0;
}