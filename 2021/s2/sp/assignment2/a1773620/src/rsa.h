#ifndef __RSA_H__
#define __RSA_H__ 1

#ifndef BITSIZE
#define BITSIZE 192
#endif

#define BYTESIZE ((BITSIZE+7)/8)
#define WORDSIZE ((BYTESIZE + sizeof(uint32_t) - 1)/sizeof(uint32_t))


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


void num_setbyte(num_t m, int n, uint8_t byte);

uint8_t num_getbyte(num_t m, int n) ;

int pkcs_encode(num_t m, const uint8_t *message, int messagelen) ;


/* Calculates res = base ^ exp modulo mod */
void num_modexp(num_t res, const num_t base, const num_t exp, const num_t mod) ;

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
    const num_t n) ;



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
    const num_t n) ;


int32_t num_sub(num_t res, const num_t n1, const num_t n2) ;

int num_inc(num_t n);

void num_rand(num_t n);


#endif
