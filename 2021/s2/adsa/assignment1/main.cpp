#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <cmath>

#define MAXDIGITS 100

void karatsuba( int *p, int *a, int *b, int radix ) {
    int n ;
    for( int i = MAXDIGITS - 1 ; i >= 0 ; i-- ) {
        // std::cout << "i: " << i << " a: " << a[i] << " b: " << b[i] << std::endl ;
        if( a[i] != 0 || b[i] != 0 ) {
            n = i + 1 ;
            i = -1 ;
        } 
    }

    /* k = ceil( n / 2 ) */
    int k = n / 2 ;
    if( n % 2 > 0 ) k++ ;

    std::cout << "n: " << n << " k: " << k << std::endl ;

    /* Base Case: */
    // if( n < 4 ) school_mult( p, a, b, radix ) ;

    /* Recursive Case: */

    // return karatsuba( p, a1, b1, radix ) ;

}

void school_mult( int *p, int *a, int *b, int radix ) {
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

int main() {
    /* 
        Read input of form:
        I1 I2 B

        Output:
        I1+I2 I1*I2 I1/I2 all in base B
    */

   int a[MAXDIGITS], b[MAXDIGITS], c[MAXDIGITS], s[MAXDIGITS], p[MAXDIGITS*MAXDIGITS] ;
   int radix ;
   
   /* Initialize arrays to be empty */
   for( int i = 0 ; i < MAXDIGITS ; i++ ) {
       a[i] = 0 ;
       b[i] = 0 ;
       c[i] = 0 ;
       s[i] = 0 ;
       p[i] = 0 ;
   }
   

   /* Read input from command line */
   int first, second ;
   char input[300] ;
   fgets( input, 300, stdin ) ;

   first  = std::stoi( strtok( input, " " ) ) ;
   second = std::stoi( strtok( NULL, " " ) ) ;
   radix  = std::stoi( strtok( NULL, " " ) ) ;

   /* Put integers into arrays */
   for( int i = 0 ; i < MAXDIGITS ; i++ ) {
       a[i] = first % 10 ;
       first = first / 10 ;

       b[i] = second % 10 ;
       second = second / 10 ;
   }

    /* School Addition Algorithm */
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        int sum = a[i] + b[i] ;
        if( i > 0 ) sum += c[i-1] ;
        if( sum >= radix ) {
            sum -= radix ;
            c[i] = 1 ;
        }
        s[i] = sum ;
    }

    /* Reset carry array to zeroes */
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
       c[i] = 0 ;
   }

    /* Karatsuba Multiplication Algorithm */
    /* 
    
    */
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

    int start = MAXDIGITS ;
    while( s[start] == 0 ) start-- ;
    for( int i = start ; i >=0 ; i-- )
        std::cout << s[i] << "" ;
    std::cout << " " ;

    start = MAXDIGITS ;
    while( p[start] == 0 ) start-- ;
    for( int i = start ; i >= 0 ; i-- )
        std::cout << p[i] << "" ;
    std::cout << " 0" << std::endl ;

    karatsuba( p, a, b, radix ) ;

   return 0 ;
}