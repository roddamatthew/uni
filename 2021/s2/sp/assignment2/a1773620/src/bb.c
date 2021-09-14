#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "rsa.h"
#include "oracle.h"
#include "bb.h"

// Push a new range node onto the linked list
// Assumes the list already has one value
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

// Return the number of nodes in the linked list
int range_length( range_t* ptr ) {
    if( ptr == NULL ) return 0 ;
    int size = 1 ;
    while( ptr -> next != NULL ) {
        ptr = ptr -> next ;
        size++ ;
    }
    return size ;
}

// Delete the linked list
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

// Print the range
void range_print( range_t* ptr )
{
    while( ptr != NULL ) {
        printf( "%s %s\n", num_toString( ptr -> low ), num_toString( ptr -> high ) ) ;
        ptr = ptr -> next ;
    }
    return ;
}

// Check if a remainder is non-zero, if so increment n
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
        // printf( "c0: %s s0: %s\n", num_toString( c0 ), num_toString( s0 ) ) ;
    }
    
    return 1 ;
}

/*
    c0 : ciphertext
    e, n : public key
    si : minimum value for which 
    si * m0 => oracle returns true.
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
        num_mul( product, partial_one, partial_two ) ;
        // c0 = ( ( c mod n ) * ( s^e mod n ) ) mod n
        num_div( quotient, ci, product, n ) ;
    }

    printf( "s1 after increment = %s\n", num_toString( s1 ) ) ;

    // got s1, now find r
    num_t threeBminusOne, r ;
    bignum_t big_r, big_low, big_high ;

    // ( 3B - 1 )
    num_sub( threeBminusOne, threeB, one ) ;

    // Want lowest interval so only calculate minimum r value
    // r = ceil( ( 2B * s1 - 3B + 1 ) / n )
    num_mul( product, twoB, s1 ) ;
    num_sub( product, product, threeBminusOne ) ;
    num_div( big_r, remainder, product, n ) ;
    num_trim( r, big_r ) ;

    // If remainder > 0, increment r
    num_ceil( r, remainder ) ;

    printf( "r = %s\n", num_toString( r ) ) ;

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

// FUNCTIONS FOR BLEICHENBACHER FULL ATTACK

// Calculate B from N
// This is a copy from step0
void calculate_B( num_t B, const num_t n ) {
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
void range_init( range_t* ptr, const num_t B )
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
    ptr -> next = NULL ;
}

// step2a from Bleichenbacher paper
void step2a( num_t s1, num_t c0, const num_t B, const num_t e, const num_t n )
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

// Calculate range for r values for step 3
void calculate_r( num_t r_min, num_t r_max, num_t a, num_t b, num_t si, const num_t B, const num_t n ) {
    num_t one, two, three ;
    num_fromString( one, "00000001" ) ;
    num_fromString( two, "00000002" ) ;
    num_fromString( three, "00000003" ) ;
    
    num_t twoB, threeB, threeBminusOne ;
    bignum_t big_r, big_low, big_high, product, remainder ;

    // Store 2B and 3B
    num_mul( product, three, B ) ;
    num_trim( threeB, product ) ;

    num_mul( product, two, B ) ;
    num_trim( twoB, product ) ;

    // ( 3B - 1 )
    num_sub( threeBminusOne, threeB, one ) ;

    // r_min = ceil( ( a * si - ( 3B - 1 ) ) / n )
    num_mul( product, a, si ) ;
    num_sub( product, product, threeBminusOne ) ;
    num_div( big_r, remainder, product, n ) ;
    num_trim( r_min, big_r ) ;

    // If remainder > 0, increment r
    num_ceil( r_min, remainder ) ;

    // r_max = floor( ( b * si - 2B ) / n )
    num_mul( product, b, si ) ;
    num_sub( product, product, twoB ) ;
    num_div( big_r, remainder, product, n ) ;
    num_trim( r_max, big_r ) ;
}

// Return the max of two num_t
void num_max( num_t max, num_t a, num_t b ) {
    num_t zero ;
    num_fromString( zero, "00000000" ) ;

    // Starting at most significant bit, return if one number is larger
    for( int i = WORDSIZE - 1 ; i >= 0 ; i-- ) {
        if( a[i] > b[i] ) {
            num_add( max, a, zero ) ;
            return ;
        }
        else if( b[i] > a[i] ) {
            num_add( max, b, zero ) ;
            return ;
        }
    }
    num_add( max, a, zero ) ;
    return ;
}

// Starting at most significant bits check if either number is larger
// If so, return the smaller number
// If the numbers are equal, return a
void num_min( num_t min, num_t a, num_t b ) {
    num_t zero ;
    num_fromString( zero, "00000000" ) ;

    for( int i = WORDSIZE - 1 ; i >= 0 ; i--) {
        // printf( "num min: a[i]: %u b[i] %u\n", a[i], b[i] ) ;
        if( a[i] < b[i] ) {
            num_add( min, a, zero ) ;
            return ;
        }
        else if( b[i] < a[i] ) {
            num_add( min, b, zero ) ;
            return ;
        }
    }
    num_add( min, a, zero ) ;
    return ;
}

// Check if r_min to r_max is a valid range
int valid_range( num_t r_min, num_t r_max ) {
    num_t res ;
    num_min( res, r_min, r_max ) ;
    // printf( "min of %s and %s: %s", num_toString( r_min ), num_toString( r_max ), num_toString( res ) ) ;
    for( int i = WORDSIZE - 1 ; i >= 0 ; i--) {
        if( res[i] != r_min[i] ) {
            // printf( "INVALID\n" ) ;
            return 0 ;
        }
    }
    // printf( "VALID\n" ) ;
    return 1 ;
}

// Calculate new range for M in step3
void calculate_range( num_t newa, num_t newb, num_t a, num_t b, num_t r, num_t si, const num_t B, const num_t n ) {
    bignum_t product, remainder, newa_big, newb_big ;
    num_t one, two, three, twoB, threeB, threeBminusOne ;

    num_fromString( one, "00000001" ) ;
    num_fromString( two, "00000002" ) ;
    num_fromString( three, "00000003" ) ;

    // Store 2B and 3B
    num_mul( product, three, B ) ;
    num_trim( threeB, product ) ;

    num_mul( product, two, B ) ;
    num_trim( twoB, product ) ;

    // ( 3B - 1 )
    num_sub( threeBminusOne, threeB, one ) ;

    // newa = ( 2B + r*n ) / si
    num_mul( product, r, n ) ;
    num_add( product, product, twoB ) ;
    num_div( newa_big, remainder, product, si ) ;
    num_trim( newa, newa_big ) ;
    
    // If remainder > 0, increment low
    num_ceil( newa, remainder ) ;

    // check if a was bigger
    num_max( newa, a, newa ) ;

    // newb = ( 3B-1 + r*n ) / si
    num_mul( product, r, n ) ;
    num_add( product, threeBminusOne, product ) ;
    num_div( newb_big, remainder, product, si ) ;
    num_trim( newb, newb_big ) ;

    num_min( newb, b, newb ) ;

    // printf( "In calculate_range: %s %s\n", num_toString( newa ), num_toString( newb ) ) ;
}

// Step3 from Bleichenbacher paper
void step3( range_t* new, range_t* old, num_t si, const num_t B, const num_t e, const num_t n ) {
    num_t zero ;
    num_fromString( zero, "00000000" ) ;
    int empty = 1 ;

    // Loop over all intervals in Mi-1
    while( old != NULL ) {
        num_t r_min, r_max ;
        calculate_r( r_min, r_max, old -> low, old -> high, si, B, n ) ;
        printf( "r range: %s %s\n", num_toString( r_min ), num_toString( r_max ) ) ;

        // Loop over range for r
        while( valid_range( r_min, r_max ) == 1 )  {
            // printf( "Step 3 with r = %s\n", num_toString( r_min ) ) ;
            num_t a, b ;
            calculate_range( a, b, old -> low, old -> high, r_min, si, B, n ) ;
            // printf( "a b: %s %s\n", num_toString( a ), num_toString( b ) ) ;
            
            if( valid_range( a, b ) == 1 ) {
                if( empty > 0 ) {
                    empty = 0 ;
                    num_add( new -> low, a, zero ) ;
                    num_add( new -> high, b, zero ) ;
                    new -> next = NULL ;
                    // printf( "filled first element: \n" ) ;
                    // range_print( new ) ;
                } else {
                    // printf( "pushed new element: \n" ) ;
                    range_push( new, a, b ) ;
                    // range_print( new ) ;
                }
            }
            
            num_inc( r_min ) ;
        }
        old = old -> next ;
    }
}

// Step 2b from Bleichenbacher paper
void step2b( num_t s_current, num_t s_last, num_t c0, const num_t e, const num_t n ) {
    num_t remainder, one, three, threeB ;
    bignum_t n_big, product, quotient ;

    num_fromString( one, "00000001" ) ;

    // Set ci to zeros so while loop starts
    num_t ci, partial_one, partial_two ;
    num_fromString( ci, "00000000" ) ;
    num_add( s_current, s_last, ci ) ;
    
    // While c0( s1 )^e mod N is not PKCS, increment s1
    while( !oracle( ci ) ) {
        num_inc( s_current ) ;

        // partial_one = c0 mod n
        num_modexp( partial_one, c0, one, n ) ;

        // partial_two = s^e mod n
        num_modexp( partial_two, s_current, e, n ) ;

        // product = ( c mod n ) * ( s^e mod n )
        num_mul( product, c0, partial_two ) ;
        // c0 = ( ( c mod n ) * ( s^e mod n ) ) mod n
        num_div( quotient, ci, product, n ) ;
    }
}

// Calculate minimum r_value for step 2c
void calculate_rc( num_t r, num_t b, num_t s_last, const num_t B, const num_t n ) {
    num_t two, twob, twoB, fourB, remainder ;
    bignum_t product, productB, quotient ;
    num_fromString( two, "00000002" ) ;
    num_mul( product, two, b ) ;
    num_trim( twob, product ) ;
    num_mul( product, twob, s_last ) ;

    num_mul( productB, two, B ) ;
    num_trim( twoB, productB ) ;
    num_mul( productB, two, twoB ) ;
    num_trim( fourB, productB ) ;

    num_sub( product, product, fourB ) ;
    num_div( quotient, remainder, product, n ) ;
    num_trim( r, quotient ) ;
}

// Calculate minimum s value in step 2c
void calculate_s_min( num_t s, num_t r, num_t b, const num_t B, const num_t n ) {
    num_t two, twoB, remainder ;
    bignum_t product, quotient ;

    num_fromString( two, "00000002" ) ;
    num_mul( product, two, B ) ;
    num_trim( twoB, product ) ;

    num_mul( product, r, n ) ;
    num_add( product, product, twoB ) ;
    num_div( quotient, remainder, product, b ) ;
    num_trim( s, quotient ) ;
}

// Calculate maximum s value in step 2c
void calculate_s_max( num_t s, num_t r, num_t a, const num_t B, const num_t n ) {
    num_t one, three, threeB, threeBminusOne, remainder ;
    bignum_t product, quotient ;

    num_fromString( one, "00000001" ) ;
    num_fromString( three, "00000003" ) ;
    num_mul( product, three, B ) ;
    num_trim( threeB, product ) ;
    num_sub( threeBminusOne, threeB, one ) ;

    num_mul( product, r, n ) ;
    num_add( product, product, threeBminusOne ) ;
    num_div( quotient, remainder, product, a ) ;
    num_trim( s, quotient ) ;
}

void step2c( num_t s_current, num_t s_last, num_t a, num_t b, num_t c0, const num_t B, const num_t e, const num_t n ) {
    // find r = ( 2*b*s_last - 4B ) / n
    num_t r, one, zero ;
    num_fromString( one, "00000001" ) ;
    num_fromString( zero, "00000000" ) ;
    calculate_rc( r, b, s_last, B, n ) ;

    while( 1 ) {
        // printf( "rc = %s\n", num_toString( r ) ) ;
        num_t s_min, s_max ;
        // find s_min = ( r*n + 2B ) / b
        calculate_s_min( s_min, r, b, B, n ) ;
        // find s_max = ( r*n + 3B - 1 ) / a
        calculate_s_max( s_max, r, a, B, n ) ;

        while( valid_range( s_min, s_max ) ) {
            num_t partial_one, partial_two, ci ;
            bignum_t product, quotient ;

            // partial_one = c0 mod n
            num_modexp( partial_one, c0, one, n ) ;

            // partial_two = s^e mod n
            num_modexp( partial_two, s_min, e, n ) ;

            // product = ( c mod n ) * ( s^e mod n )
            num_mul( product, c0, partial_two ) ;
            // c0 = ( ( c mod n ) * ( s^e mod n ) ) mod n
            num_div( quotient, ci, product, n ) ;

            if( oracle( ci ) ) {
                num_add( s_current, s_min, zero ) ;
                return ;
            }
            num_inc( s_min ) ;
        }

        num_inc( r ) ;
    }

}

// Full Bleichenbacher attack:
void bleichenbacher( num_t m, const num_t c, const num_t e, const num_t n ) {
    num_t c0, s_current, s_last, zero, s0 ;
    num_fromString( zero, "00000000" ) ;
    int i = 1 ;
    
    // Step 1: Blinding
    printf( "1" ) ;
    bb_blind( c0, s0, c, e, n ) ;

    // Find B
    num_t B ;
    calculate_B( B, n ) ;
    printf( "B: %s", num_toString( B ) ) ;

    // Create linked lists storing current and previous range
    range_t *M_last = (range_t*)malloc( sizeof( range_t ) ) ;
    range_t *M_current = NULL ;

    // M0 = { [ 2B, 3B - 1 ] }
    range_init( M_last, B ) ;

    while( range_converged( M_last ) != 1 ) {
        if( i == 1 ) {
            step2a( s_current, c0, B, e, n ) ;
            printf( "Step 2A: %s\n", num_toString( s_current ) ) ;
        }
        else if( range_length( M_last ) > 1 ) {
            step2b( s_current, s_last, c0, e, n ) ;
            printf( "Step 2B: %s\n", num_toString( s_current ) ) ;
        }
        else if( range_length( M_last ) == 1 ) {
            step2c( s_current, s_last, M_last -> low, M_last -> high, c0, B, e, n ) ;
            printf( "Step 2C: %s\n", num_toString( s_current ) ) ;
        }

        // Allocate memory for the new range
        M_current = (range_t*)malloc( sizeof( range_t ) ) ;
        step3( M_current, M_last, s_current, B, e, n ) ;
        
        printf( "All current ranges for M are: \n" ) ;
        range_print( M_current ) ;
        printf( "\n" ) ;

        // Free all nodes in the old range
        range_delete( M_last ) ;
        // Switch lists for next iteration
        M_last = M_current ;

        // s_current becomes s_last
        num_add( s_last, s_current, zero ) ;
        
        i++ ;
    }
    printf( "Final M: %s\n", num_toString( M_last -> low ) ) ;
    printf( "s0: %s\n", num_toString( s0 ) ) ;
    printf( "Ran out of time. Original message M could be computed using a modular inverse algorithm." ) ;
}
