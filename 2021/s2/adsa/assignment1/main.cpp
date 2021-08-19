#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <cmath>

#define MAXDIGITS 100

void karatsuba( int p[], int a[], int b[], int radix ) {
    /* Find the max digit length of a and b */
    int n ;
    for( int i = MAXDIGITS - 1 ; i >= 0 ; i-- ) {
        // std::cout << "i: " << i << " a: " << a[i] << " b: " << b[i] << std::endl ;
        if( a[i] != 0 || b[i] != 0 ) {
            n = i + 1 ;
            i = -1 ;
        } 
    }

    /* Base Case: */
    if( n < 4 ) {
        school_mult( p, a, b, radix ) ;
        return ;
    }

    /* Recursive Case: */
    /* k = ceil( n / 2 ) */
    int k = n / 2 ;
    if( n % 2 > 0 ) k++ ;

    std::cout << "n: " << n << " k: " << k << std::endl ;
    
    /*
    int a1[] = 
    int a2[] = 

    int b1[] = 
    int b2[] = 

    int z0 = 
    int z1 =
    int z2 = 

    return ( z2 * radix ^ ( k * 2 ) ) + ( ( z1 - z2 - z0 ) * radix ^ k ) + z0 ;
    */
}

void school_mult( int p[], int a[], int b[], int radix ) {
    /* Array to store carries */
    int c[MAXDIGITS] ;
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        c[i] = 0 ;
    }

    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        for( int j = 0 ; j < MAXDIGITS ; j++ ) {
            p[i+j] += a[i] * b[j] ;
            /* add carry */
            p[i+j] += c[j] ;
            c[j] = 0 ;

            /* check for overflow */
            while( p[i+j] >= radix ) {
                c[j]++ ;
                p[i+j] -= radix ;
            }
        }
    }

    return ;
}

void school_add( int s[], int a[], int b[], int radix ) {
    int c[MAXDIGITS] ;
    /* Set carry array to zeroes */
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        c[i] = 0 ;
    }

    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        int sum = a[i] + b[i] ;
        if( i > 0 ) sum += c[i-1] ;
        if( sum >= radix ) {
            sum -= radix ;
            c[i] = 1 ;
        }
        s[i] = sum ;
    }

    return ;
}

int main() {
    /* 
    Read input of form:
    I1 I2 B

    Output:
    I1+I2 I1*I2 I1/I2 all in base B
    */

    int a[MAXDIGITS], b[MAXDIGITS], s[MAXDIGITS], p[MAXDIGITS*MAXDIGITS] ;
    int radix ;

    /* Initialize arrays to be empty */
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        a[i] = 0 ;
        b[i] = 0 ;
        s[i] = 0 ;
        p[i] = 0 ;
    }

    for( int i = 0 ; i < MAXDIGITS * MAXDIGITS ; i++ )
        p[i] = 0 ;


    /* Read input from command line */
    std::string first, second ;
    char input[220] ;
    fgets( input, 220, stdin ) ;

    first  = strtok( input, " " ) ;
    second = strtok( NULL, " " ) ;
    radix  = std::stoi( strtok( NULL, " " ) ) ;

    std::cout << first << std::endl << second << std::endl ;

    /* Put integers into arrays */
    for( int i = first.length() - 1 ; i >= 0 ; i-- ) {
        a[first.length() - 1 - i] = first[i] - '0' ;
    }

    for( int i = second.length() - 1 ; i >= 0 ; i-- ) {
        b[second.length() - 1 - i] = second[i] - '0' ;
    }

    for( int i = 0 ; i < MAXDIGITS ; i++ )
        std::cout << a[i] << " " ;
    std::cout << std::endl ;

    for( int i = 0 ; i < MAXDIGITS ; i++ )
        std::cout << b[i] << " " ;
    std::cout << std::endl ;

    school_add( s, a, b, radix ) ;
    school_mult( p, a, b, radix ) ;
    karatsuba( p, a, b, radix ) ;

    /* Print result: */
    int start = MAXDIGITS - 1 ;
    while( s[start] == 0 ) start-- ;
    for( int i = start ; i >=0 ; i-- )
        std::cout << s[i] << "" ;
    std::cout << " " ;

    start = MAXDIGITS - 1 ;
    while( p[start] == 0 ) start-- ;
    for( int i = start ; i >= 0 ; i-- )
        std::cout << p[i] << "" ;
    std::cout << " 0" << std::endl ;

    return 0 ;
}