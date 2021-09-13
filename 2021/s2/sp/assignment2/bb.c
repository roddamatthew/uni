#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "rsa.h"
#include "oracle.h"
#include "bb.h"

int range_push( range_t* ptr, num_t low, num_t high )
{
    num_t zero ;
    num_fromString( zero, "00000000" ) ;

    while( ptr -> next != NULL ) ptr = ptr -> next ;
    range_t *new_range = (range_t*)malloc( sizeof( range_t ) ) ;
    ptr -> next = new_range ;

    num_add( new_range -> low, low, zero ) ;
    num_add( new_range -> high, high, zero ) ;
    new_range -> next = NULL ;

    return 1 ; 
}

int range_length( range_t* ptr ) {
    int size = 1 ;
    while( ptr -> next != NULL ) {
        ptr = ptr -> next ;
        size++ ;
    }
    return size ;
}

void range_delete( range_t* ptr ) {
    range_t *next ;
    while( ptr != NULL ) {
        next = ptr -> next ;
        free( ptr ) ;
        ptr = next ;
    }
}

// If range has only one entry and they are the same value, return 1
int range_converged( range_t* ptr ) {
    if( range_length( ptr ) == 1 ) {
        num_t res ;
        num_sub( res, ptr -> low, ptr -> high ) ;
        if( strcmp( "0", num_toString( res ) ) == 0 )
            return 1 ;
    }

    return 0 ;
}

void range_print( range_t* ptr )
{
    while( ptr -> next != NULL ) {
        printf( "%s %s\n", num_toString( ptr -> low ), num_toString( ptr -> high ) ) ;
        ptr = ptr -> next ;
    }
    return ;
}

void num_ceil( num_t n, num_t remainder ) {
    for( int i = 0 ; i < WORDSIZE ; i++ ) {
        if( remainder[i] != 0 ) {
            num_inc( n ) ;
            return ;
        }
    }
}

/*
    c: ciphertext
    e: public exponent
    n: public modulus
    s0: blinding factor for which oracle returns true, ie. m0 = s0 * m
    c0: ciphertext after applying the blinding factor, ie. c0 = ( s0 * m )^e mod N
*/

int bb_blind(num_t c0, num_t s0, const num_t c, const num_t e, const num_t n) 
{
    // Store 1 as a num_t for later
    char one_string[] = "00000001" ;
    num_t one, partial_one, partial_two, partial_three ;
    bignum_t product, q ;
    num_fromString( one, one_string ) ;

    while( !oracle( c0 ) ) {
        // partial_one = c mod n
        num_modexp( partial_one, c, one, n ) ;

        // Generate random s0
        num_rand( s0 ) ;

        // partial_two = s^e mod n
        num_modexp( partial_two, s0, e, n ) ;

        // product = ( c mod n ) * ( s^e mod n )
        num_mul( product, partial_one, partial_two ) ;
        // c0 = ( ( c mod n ) * ( s^e mod n ) ) mod n
        num_div( q, c0, product, n ) ;
    }
    
    return 1 ;
}

/*
    c0 : ciphertext
    e, n : public key
    si : minimum value for which 
    si * m0 => oracke returns true.
*/

int bb_step0(num_t low, num_t high, num_t si, const num_t c0, const num_t e, const num_t n)
{
    // Create constants for later calculations
    num_t one, two, three ;
    num_fromString( one, "00000001" ) ;
    num_fromString( two, "00000002" ) ;
    num_fromString( three, "00000003" ) ;

    // Create num_t's for later calculations
    bignum_t product, quotient ;
    num_t remainder ;

    // Find the length of N in bytes
    char *n_string = num_toString( n ) ;
    // Remove any leading zeroes from n
    while( n_string[0] == '0' )
        n_string++ ;
    int k = strlen( n_string ) / 2 ;

    // B = 2^8( k - 2 )
    num_t B ;
    num_fromString( B, "00000002" ) ;
    for( int i = 0 ; i < ( 8*( k - 2 ) ) - 1 ; i++ ) {
        num_mul( product, B, two ) ;
        num_trim( B, product ) ;
    }

    // Store 2B and 3B for later calculations
    num_t twoB, threeB ;
    num_mul( product, B, two ) ;
    num_trim( twoB, product ) ;

    num_mul( product, B, three ) ;
    num_trim( threeB, product ) ;

    // s1 => n / 3B
    bignum_t s1_big, n_big ;
    // store n in a bignum for num_div
    num_mul( n_big, n, one ) ;
    num_t s1 ;
    num_div( s1_big, remainder, n_big, threeB ) ;
    num_trim( s1, s1_big ) ;

    printf( "s1_big before increment: %s\n", num_toString( s1_big ) ) ;
    printf( "s1 before increment: %s\n", num_toString( s1 ) ) ;

    num_mul( product, B, three ) ;
    num_trim( threeB, product ) ;

    // Set ci to zeros so while loop starts
    num_t ci, partial_one, partial_two ;
    num_fromString( ci, "00000000" ) ;
    
    // While c0( s1 )^e mod N is not PKCS, increment s1
    while( !oracle( ci ) ) {
        num_inc( s1 ) ;

        // partial_one = c0 mod n
        num_modexp( partial_one, c0, one, n ) ;

        // partial_two = s^e mod n
        num_modexp( partial_two, s1, e, n ) ;

        // product = ( c mod n ) * ( s^e mod n )
        num_mul( product, c0, partial_two ) ;
        // c0 = ( ( c mod n ) * ( s^e mod n ) ) mod n
        num_div( quotient, ci, product, n ) ;
    }

    printf( "s1 after increment = %s\n", num_toString( s1 ) ) ;

    // got s1, now find r
    num_t threeBminusOne, r ;
    bignum_t big_r, big_low, big_high ;

    // ( 3B - 1 )
    num_sub( threeBminusOne, threeB, one ) ;

    // r = ceil( ( 2B * s1 - 3B + 1 ) / n )
    num_mul( product, twoB, s1 ) ;
    num_sub( product, product, threeBminusOne ) ;
    num_div( big_r, remainder, product, n ) ;
    num_trim( r, big_r ) ;

    // If remainder > 0, increment r
    num_ceil( r, remainder ) ;

    num_t r_max ;
    bignum_t big_r_max ;
    // r = floor( ( (3B -1)*s1 - 2B ) / n )
    num_mul( product, threeBminusOne, s1 ) ;
    num_sub( product, product, twoB ) ;
    num_div( big_r, remainder, product, n ) ;
    num_trim( r_max, big_r_max ) ;

    printf( "r = %s\n", num_toString( r ) ) ;
    printf( "r_max = %s\n", num_toString( r_max ) ) ;

    // low = ( 2B + r*n ) / s1
    num_mul( product, r, n ) ;
    num_add( product, product, twoB ) ;
    num_div( big_low, remainder, product, s1 ) ;
    num_trim( low, big_low ) ;

    // If remainder > 0, increment low
    num_ceil( low, remainder ) ;

    // high = ( 3B-1 + r*n ) / s1
    num_mul( product, r, n ) ;
    num_add( product, threeBminusOne, product ) ;
    num_div( big_high, remainder, product, s1 ) ;
    num_trim( high, big_high ) ;

    printf( "low = %s\n", num_toString( low ) ) ;
    printf( "high = %s\n", num_toString( high ) ) ;
}

void calculate_B( num_t B, num_t n ) {
    bignum_t product ;
    num_t two ;
    
    // Find the length of N in bytes
    char *n_string = num_toString( n ) ;
    // Remove any leading zeroes from n
    while( n_string[0] == '0' )
        n_string++ ;
    int k = strlen( n_string ) / 2 ;

    num_fromString( B, "00000002" ) ;
    num_fromString( two, "00000002" ) ;

    // B = 2^8( k - 2 )
    for( int i = 0 ; i < ( 8*( k - 2 ) ) - 1 ; i++ ) {
        num_mul( product, B, two ) ;
        num_trim( B, product ) ;
    }
}

// M0 = { [ 2B, 3B - 1 ] }
void range_init( range_t* ptr, num_t B )
{
    num_t twoB, threeB, threeBminusOne, zero, one, two, three ;
    bignum_t product ;
    num_fromString( zero, "00000000" ) ;
    num_fromString( one, "00000001" ) ;
    num_fromString( two, "00000002" ) ;
    num_fromString( three, "00000003" ) ;
    
    num_mul( product, B, two ) ;
    num_trim( twoB, product ) ;

    num_mul( product, B, three ) ;
    num_trim( threeB, product ) ;

    num_sub( threeBminusOne, threeB, one ) ;
    
    num_add( ptr -> low, twoB, zero) ;
    num_add( ptr -> high, threeBminusOne, zero ) ;
}

void step2a( num_t s1, num_t c0, num_t B, num_t e, num_t n )
{
    num_t remainder, one, three, threeB ;
    bignum_t n_big, product, quotient ;

    num_fromString( one, "00000001" ) ;
    num_fromString( three, "00000003" ) ;

    // 3B = B * 3
    num_mul( product, B, three ) ;
    num_trim( threeB, product ) ;
    
    // s1 => n / 3B
    // store n in a bignum for num_div
    num_mul( n_big, n, one ) ;
    num_div( product, remainder, n_big, threeB ) ;
    num_trim( s1, product ) ;

    // Set ci to zeros so while loop starts
    num_t ci, partial_one, partial_two ;
    num_fromString( ci, "00000000" ) ;
    
    // While c0( s1 )^e mod N is not PKCS, increment s1
    while( !oracle( ci ) ) {
        num_inc( s1 ) ;

        // partial_one = c0 mod n
        num_modexp( partial_one, c0, one, n ) ;

        // partial_two = s^e mod n
        num_modexp( partial_two, s1, e, n ) ;

        // product = ( c mod n ) * ( s^e mod n )
        num_mul( product, c0, partial_two ) ;
        // c0 = ( ( c mod n ) * ( s^e mod n ) ) mod n
        num_div( quotient, ci, product, n ) ;
    }
}

void bleichenbacher( num_t m, const num_t c, const num_t e, const num_t n ) {
    num_t c0, s_current, s_last ;
    int i = 1 ;
    
    // Step 1: Blinding
    bb_blind( c0, s_last, c, e, n ) ;

    // Find B
    num_t B ;
    calculate_B( B, n ) ;

    range_t *M_last = (range_t*)malloc( sizeof( range_t ) ) ;
    // M0 = { [ 2B, 3B - 1 ] }
    range_init( M_last, B ) ;

    range_print( M_last ) ;

    while( range_converged( M_last ) != 1 ) {
        if( i == 1 )
            step2a( s_current, c0, B, e, n ) ;
        printf( "s = %s", num_toString( s_current ) ) ;
        // else if( range_length( M_last ) > 1 )
        //     step2b() ;
        // else if( range_length( M_last ) == 1 )
        //     step2c() ;

        // step3() ;
    }

    return 1 ;
}
