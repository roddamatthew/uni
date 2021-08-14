#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#ifndef BITSIZE
#define BITSIZE 1024
#endif

#define BYTESIZE ((BITSIZE+7)/8)
#define WORDSIZE ((BYTESIZE + sizeof(uint32_t) - 1)/sizeof(uint32_t)) /* 32 */


/* 
 * Represents a number BITSIZE bits wide.
 * Implemented as an array of int32_t in little endian order.  That is, 
 * num = \sum 2^{32*i}*array[i]
 */
typedef uint32_t num_t[WORDSIZE];

/*
 * Represents a number 2*BITSIZE bits wide
 * Same format as num_t, only twice as long
 */
typedef uint32_t bignum_t[WORDSIZE * 2];


/*
 * Converts a num_t to a hexadecimal string. The memory for the string is allocated
 * with malloc and needs to be freed after use.
 */
char *num_toString(const num_t n);

/*
 * Converts a hexadecimal string (without 0x) to a num_t.
 */
int num_fromString(num_t in, const char *s);

/* Computes res = n1 + n2.  Returnes the carry */
uint32_t num_add(num_t res, const num_t n1, const num_t n2);

/* Computes res = n1 * n2. */
void num_mul(bignum_t res, const num_t n1, const num_t n2);

/* Computes res = n^2. */
void num_square(bignum_t res, const num_t n);

/* Trims a bignum_t n to num_t */
void num_trim(num_t res, const bignum_t n);

/* Computes numerator/denominator. Returns the quotient and the remainder. */
int num_div(bignum_t quotient, num_t remainder, const bignum_t numerator, const num_t denominator);


/******************************************************************************\
*                   IMPLEMENT THE THREE FUNCTIONS BELOW                        *  
\******************************************************************************/

/* Get the ith bit from a num_t */
int i_bit( num_t n, int i ) {
  char* str = num_toString( n ) ;

  /* get the character from the string */
  int index = strlen( str ) - 1 - ( i / 4 ) ;
  // printf( "Whole number: %s\n", str ) ;
  char c = str[index] ;
  // printf( "Hexadecimal character at position i: %c\n", c ) ;
  i = i % 4 ;
  char* binary ;

  /* Turn character into 4 bit binary */
  switch ( c ) {
    case '0':
      binary = "0000" ;
      break ;
    
    case '1':
      binary = "0001" ;
      break ;
    
    case '2':
      binary = "0010" ;
      break ;
    
    case '3':
      binary = "0011" ;
      break ;
    
    case '4':
      binary = "0100" ;
      break ;
    
    case '5':
      binary = "0101" ;
      break ;
    
    case '6':
      binary = "0110" ;
      break ;
    
    case '7':
      binary = "0111" ;
      break ;
    
    case '8':
      binary = "1000" ;
      break ;
    
    case '9':
      binary = "1001" ;
      break ;
    
    case 'A':
      binary = "1010" ;
      break ;
    
    case 'B':
      binary = "1011" ;
      break ;
    
    case 'C':
      binary = "1100" ;
      break ;
    
    case 'D':
      binary = "1101" ;
      break ;
    
    case 'E':
      binary = "1110" ;
      break ;
    
    case 'F':
      binary = "1111" ;
      break ;

    default:
      printf( "Error in i_bit, i = %d\n", i ) ;
      return -1 ;
  }

  // printf( "Binary: %s index: %d\n", binary, i ) ;

  /* Convert char to int */
  // printf( "i_bit returned %d", binary[3 - i] - 48 ) ;
  return binary[3 - i] - 48 ;
}

/* Calculates res = base ^ exp modulo mod */
void num_modexp(num_t res, const num_t base, const num_t exp, const num_t mod)
{
    bignum_t temp ;
    bignum_t dc ;

    char* num ;

    /* x = 1 */
    char* s = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" ;
    num_fromString( res, s ) ;

    char* exp_str = num_toString( exp ) ;
    // printf( "exp_str = %s\n", exp_str ) ;
    /* 0000 0000 0000 0001 0000 0000 0000 0001 */
    int exp_size = strlen( exp_str ) ;
    free( exp_str ) ;

    // printf( "exp size = %d\n", exp_size ) ;

    for( int i = exp_size * 4 - 1 ; i >= 0 ; i-- ) {
        /* Square: */
        num_square( temp, res ) ;

        /* Reduce: */
        num_div( dc, res, temp, mod ) ;

        /* print */
        num = num_toString( res ) ;
        // printf( "Square + Reduce: %s\n", num ) ;
        free( num ) ;

        if( i_bit( exp, i ) == 1 ) {
          num_mul( temp, res, base ) ;
          num_div( dc, res, temp, mod ) ;

          /* print */
          num = num_toString( res ) ;
          // printf( "Multiply + Reduce: %s\n", num ) ;
          free( num ) ;
        }
    }
}

char * random_hex( int bit_length ) {
  char * random_str = malloc( sizeof( char ) * bit_length / 4 + 1 ) ;
  char * temp ;

  for( int i = 0 ; i < bit_length / 4 ; i++ ) {
    sprintf( temp, "%X", rand() % 15 + 1 ) ;
    strcat( random_str, temp ) ;
  }
 
  return random_str ;
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
    const num_t n ) {
      num_t test ;

      /* Pad message: */
      char *str = calloc( ( 257 + messagelen ), sizeof( char ) ) ;
      strcat( str, "0002" ) ;

       /* Generate 124 random bytes of non zero hexadecimal */
       srand( time( 0 ) ) ;
      char *r = calloc( ( 251 - messagelen ), sizeof(char) ) ;
      for( int i = 0 ; i < 250 - messagelen ; i++ )
      {
        char temp[2] ;
        sprintf( temp, "%X", rand() % 15 + 1 ) ;
        strcat( r, temp ) ;
      }

      strcat( str, r ) ;
      strcat( str, "00" ) ;
      strcat( str, message ) ;

      num_t padded_message ;

      num_fromString( padded_message, str ) ;
      num_modexp( ciphertext, padded_message, e, n ) ;

  return 0 ;
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
      num_t padded_message ;
      num_modexp( padded_message, ciphertext, d, n ) ;

      char *str = num_toString( padded_message ) ;

      /* Check that the decrypted message matches PKCS 1.5 format */
      /* First four characters must be 0x0002*/
      if( str[0] != '0' ) return -1 ;
      if( str[1] != '0' ) return -1 ;
      if( str[2] != '0' ) return -1 ;
      if( str[3] != '2' ) return -1 ;

      /* Read through non-zero random padding */
      int i = 3 ;
      while( str[i++] != '0' ) {}
      /* Once 0 is found, the next character must be 0 */
      if( str[i++] != '0' ) return -1 ;

      /* Now start copying the message */
      for( int j = 0 ; j < messagebuflen ; j++ ) {
        /* Copy the character and increment counter */
        if( i <= 256 ) messagebuf[j] = (uint8_t) str[i++] ;
        /* If the buffer is longer than the message, fill the end with zeros */
        else messagebuf[j] = (uint8_t) 0 ;
      }

      free( str ) ;

  return 0;
}

/******************************************************************************\
*                     DO NOT MODIFY BELOW THIS LINE                            *  
\******************************************************************************/

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
    if (n[i] == 0)
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

/* Main for testing:
int main() {
  srand( 0 ) ;
  num_t res, base, exp, mod ;

  char *msg = "ABCDEF012341281238ABD" ;

  char *e = "10001" ;
  char *n = "cd7ddeca6ca50a39f2bc0e780478864be17a31ab04aa553b924cf8ddedb62fa9a88be62dbf14d3811d03e0d9313a9918cb9a392f1731586ffbcaa2eed10ff363c4153fb0d5653e83a1be11ac6d4b4e10f6c0afb24af9243ff85a804e5a4114bf4306fe0e36840f22dade71103482eaf54ed51cfda222ee4e5a2640d934b0d4d3" ;
  char *d = "2e17899d85f90eee28901dfeb5a2031d8a19ca823dada728918c4a561d37bc4125d91b6c2f6c1074e979313a065cca725158ea72b19513ed2a612d62bbea04017942710c1e596a533b7c9d19db2d4c0cfd386124983a158b3fcc58471ecfb5e949361494c32164dac4b383967777ec01369d1b87462f5148b04b71f58ddf15c1" ;

  int messagelen = strlen( msg ) ;

  int messagebuflen = strlen( msg ) + 2 ;
  uint8_t *messagebuf = calloc( messagebuflen, sizeof( uint8_t ) ) ;
  
  num_fromString( exp, e ) ;
  num_fromString( mod, n ) ;
  num_fromString( base, d ) ;

  rsa_pkcs_encrypt( res, (uint8_t*) msg, messagelen, exp, mod ) ;
  printf( "Encrypted message: %s\n", num_toString( res ) ) ;
  rsa_pkcs_decrypt( messagebuf, messagebuflen, res, base, mod ) ;

  for( int i = 0 ; i < messagebuflen ; i++ ) {
    printf( "%c ", messagebuf[i] ) ;
  }

  return 0 ;
}

 */