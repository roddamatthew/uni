#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "rsa.h"


int num_inc(num_t n) {
  uint32_t c = 1;
  for (int i = 0; i < WORDSIZE; i++) {
    n[i] += c;
    if (n[i] != 0)
      c = 0;
  }
  return c;
}

void num_rand(num_t n) {
  for (int i = 0 ; i < WORDSIZE; i++)
    asm volatile ("rdrand %0": "=r" (n[i])::);
  n[WORDSIZE-1] &= 0x7fffffff;
}

/* Calculates res = base ^ exp modulo mod */
void num_modexp(num_t res, const num_t base, const num_t exp, const num_t mod) {
  bignum_t t1;
  bignum_t t2;

  res[0] = 1;
  for (int i = 1; i < WORDSIZE; i++)
    res[i] = 0;

  int first = 1;
  for (int i = WORDSIZE; i--; ) {
    uint32_t w = exp[i];
    for (uint32_t mask = 0x80000000; mask; mask >>= 1) {
      if ((w&mask) == 0 && first)
	continue;
      first = 0;
      num_square(t1, res);
      num_div(t2, res, t1, mod);
      if (w & mask) {
        num_mul(t1, res, base);
        num_div(t2, res, t1, mod);
      }
    }
  }


}

/* 
 * Pads message using PKCS#1 v1.5 and encrypts with a public RSA key (n, e)
 * Returns 0 on success and 1 on failure.
 *
 * You can assume that n is full size, i.e. n>=2^{BITSIZE - 1}
 */
int rsa_pkcs_encrypt(
    num_t ciphertext, 
    const uint8_t *message, 
    int messagelen, 
    const num_t e, 
    const num_t n) {
  return 0;
}



/*
 * Decrypts ciphertext using (n, d) and verifies that it is in PKCS#1 v1.5 format.
 * If the format is correct, writes the message in messagebuf and returns the 
 *    message length. If the length of the decrypted message is larger than
 *    messagebuflen, only the first messagebuflen bytes of the message are written.
 * If the message is not in PKCS#1 v1.5 format, returns -1.
 * In case of other errors, returns -2.
 *
 * You can assume that n is full size, i.e. n>=2^{BITSIZE - 1}
 */
int rsa_pkcs_decrypt(
    uint8_t *messagebuf, 
    int messagebuflen, 
    const num_t ciphertext, 
    const num_t d, 
    const num_t n) {
  return 0;
}


int32_t num_sub(num_t res, const num_t n1, const num_t n2) {
  int64_t s = 0ULL;
  for (int i = 0; i < WORDSIZE; i++) {
    s += (uint64_t)n1[i] - (uint64_t)n2[i];
    res[i] = s & 0xffffffffULL;
    s >>= 32;
  }
  return (int32_t)s;
}



uint32_t num_add(num_t res, const num_t n1, const num_t n2) {
  uint64_t s = 0ULL;
  for (int i = 0; i < WORDSIZE; i++) {
    s += (uint64_t)n1[i] + (uint64_t)n2[i];
    res[i] = s & 0xffffffffULL;
    s >>= 32;
  }
  return (uint32_t)s;
}

void num_mul(bignum_t res, const num_t n1, const num_t n2) {
  for (int i = 0; i < WORDSIZE * 2; i++)
    res[i] = 0;

  for (int i = 0; i < WORDSIZE; i++) {
    uint64_t s = 0;
    for (int j = 0; j < WORDSIZE; j++) {
      s += (uint64_t)res[i+j] + (uint64_t)n1[i] * (uint64_t)n2[j];
      res[i+j] = s & 0xffffffffULL;
      s >>= 32;
    }
    res[i+WORDSIZE] += s;
  }
}

void num_trim(num_t res, const bignum_t n) {
  for (int i = 0; i < WORDSIZE; i++)
    res[i] = n[i];
}



static uint32_t shiftleft(uint32_t *a, const uint32_t *b, int n, int d) {
  uint64_t carry = 0;
  for (int i = 0; i < n; i++) {
    carry |= ((uint64_t)b[i]) << d;
    a[i] = carry & 0xFFFFFFFFULL;
    carry >>= 32;
  }
  return carry;
}
    

static uint64_t Step_D3(uint32_t *uj, uint32_t *v, int n) {
  uint64_t hat = ((uint64_t)uj[n]<<32) + uj[n-1];
  uint64_t qhat = hat / v[n-1];
  uint64_t rhat = hat % v[n-1];
  if (qhat == 0x100000000ULL || ( n>1 && (qhat * v[n-2] > 0x100000000ULL * rhat + uj[n-2]))) {
    qhat--;
    rhat += v[n-1];
    if (rhat < 0x100000000ULL && n>1 && (qhat * v[n-2] > 0x100000000ULL * rhat + uj[n-2])) {
      qhat--;
      rhat += v[n-1];
    }
  }
  return qhat;
}

static uint32_t Step_D4(uint32_t *uj, uint32_t *v, uint64_t qhat, int n) {
  uint64_t borrow = 0;
  for (int i = 0; i < n; i++) {
    borrow += uj[i];
    borrow -= qhat * v[i];
    uj[i] = borrow & 0xFFFFFFFFULL;
    borrow >>= 32;
    if (borrow)
      borrow |= 0xFFFFFFFF00000000ULL; // The borrow is always non-positive...
  }
  borrow += uj[n];
  uj[n] = borrow & 0xFFFFFFFFULL;
  return borrow >> 32; // The return value is 16 bits, so no need for extending the sign bit
}

static void Step_D6(uint32_t *uj, uint32_t *v, int n) {
  uint64_t carry = 0;
  for (int i = 0; i < n; i++) {
    carry += uj[i];
    carry += v[i];
    uj[i] = carry & 0xFFFFFFFFULL;
    carry >>= 32;
  }
  carry += uj[n];
  uj[n] = carry & 0xFFFFFFFFULL;
  //assert(carry > 0xFFFF); // We ignore further carry
}

static void shiftright(uint32_t *u, int n, int d) {
  if (d==0)
    return;
  for (int i = 0; i < n; i++)
    u[i] = (u[i] >> d) | (u[i+1] << (32 - d));
  u[n] >>= d;
}


static int reallen(const uint32_t *u, int l) {
  while (l-- > 0) {
    if (u[l] != 0)
      return l+1;
  }
  return 0;
}


// Using Algorithm 4.3.1 D of Knuth TAOCP
int num_div(bignum_t quotient, num_t remainder, const bignum_t numerator, const num_t denominator) {
  // Use Knuth's variable names:
  //   u -- numerator
  //   v -- denominator
  //   q -- quotient
  //   d -- normalisation factor
  //   n -- length of denominator
  //   m -- length difference between numerator and denominator
  //   b -- base = 0x100000000
  // Our base (b) is 2^32, so we can use the shift method to calculate d.
  // We use the space of the remainder for the normalised numerator, so
  // need to allocate another variable for that.
  if (quotient == numerator || 
      remainder == denominator)
    return -1;

  // Step D1
  int n = reallen(denominator, WORDSIZE);
  if (n == 0)
    return -1;
  int d = 0;
  uint32_t t = denominator[n - 1];
  assert(t != 0); // This is OK from the calculation of n
  while ((t & 0x80000000) == 0) {
    t <<= 1;
    d++;
  }
  num_t vbn;
  memset(vbn, 0, sizeof(num_t));
  uint32_t *v = vbn;
  t = shiftleft(v, denominator, n, d);
  assert(t == 0);

  int nl =  reallen(numerator, WORDSIZE * 2);
  int m = nl < n ? 0 : nl - n;

  memset(remainder, 0, sizeof(num_t));
  uint32_t ubn[2 * WORDSIZE + 1];
  memset(ubn, 0, sizeof(ubn));
  uint32_t *u = ubn;
  u[nl] = shiftleft(u, numerator, nl, d);

  uint32_t *q = quotient;


  // Steps D2, D7
  for (int j = m; j >= 0; j--) {
    // Step D3
    uint64_t qhat = Step_D3(u+j, v, n);

    // Step D4
    uint32_t borrow = Step_D4(u+j, v, qhat, n);
    
    // Step D5
    q[j] = qhat;
    if (borrow) {
      //Step D6
      assert(qhat != 0);
      Step_D6(u+j, v, n);
      q[j]--;
    }
  }
 
  // Step D8
  assert((u[0] & ((1<<d) - 1)) == 0);
  shiftright(u, n, d);
  for (int i = m+1; i < WORDSIZE * 2; i++)
    q[i] = 0;
  for (int i = n+1; i < WORDSIZE; i++)
    ubn[i] = 0;
  num_trim(remainder, ubn);

  return 0;
}

int  num_fromString(num_t in, const char *s) {
  num_t tmp = {0};
  for (int i = 0; i < WORDSIZE; i++)
    in[i] = 0;

  while (*s) {
    if (!isxdigit(*s))
      return -1;
    int c;
    if (isdigit(*s))
      c = *s - '0';
    else if (islower(*s))
      c = *s - 'a' + 10;
    else
      c = *s - 'A' + 10;
    shiftleft(tmp, in, WORDSIZE, 4);
    memcpy(in, tmp, sizeof(num_t));
    in[0] += c;
    s++;
  }
  return 0;
}

char *num_toString(const num_t n) {
  char *rv = malloc(2 * BYTESIZE + 1);
  if (rv == NULL)
    return NULL;
  char *p = rv;
  for (int i = WORDSIZE; i--;) {
    if (p==rv && n[i] == 0)
      continue;
    sprintf(p, "%08X", n[i]);
    p += sizeof(uint32_t) * 2;
  }
  if (p == rv)
    *p++ = '0';
  *p = 0;
  return rv;
}


void num_square(bignum_t res, const num_t n) {
  num_mul(res, n, n);
}