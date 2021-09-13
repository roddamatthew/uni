#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "rsa.h"
#include "oracle.h"



static struct {
  num_t n;
  num_t e;
  num_t d;
} key;


void oracle_init() {
  num_fromString(key.n, "9e09a0f8b28b8f66b7e5ce7dd71adea72b825901e45eeb1d");
  num_fromString(key.e, "10001");
  num_fromString(key.d, "87ef3a5190a9f05fe720391ab48b9ceeca2327633200e475");
}



int oracle(const num_t c) {
  num_t r;
  num_modexp(r, c, key.d, key.n);
  if ((r[WORDSIZE-1] & 0xffff0000 ) != 0x00020000)
    return 0;
  return 1;
}

void oracle_getn(num_t n) {
  memcpy(n, key.n, sizeof(num_t));
}

void oracle_gete(num_t e) {
  memcpy(e, key.e, sizeof(num_t));
}


