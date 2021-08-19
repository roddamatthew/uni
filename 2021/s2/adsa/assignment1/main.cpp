#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <cmath>

#define MAXDIGITS 100

void split( int high[], int low[], int n[], int digits ) {
    for( int i = 0 ; i < digits ; i++ ) {
        low[i] = n[i] ;
    }
    for( int i = digits ; i < MAXDIGITS ; i++ ) {
        high[i - digits] = n[i] ;
    }
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

void school_sub( int s[], int a[], int b[], int radix ) {
    int c[MAXDIGITS] ;
    /* Set carry array to zeroes */
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        c[i] = 0 ;
    }

    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        int sum = a[i] - b[i] ;
        if( i > 0 ) sum += c[i-1] ;
        if( sum < 0 ) {
            sum = radix + sum ;
            c[i] = -1 ;
        }
        s[i] = sum ;
    }

    return ;
}

/* Powers of k can be done by shifting in k zeroes */
void power( int p[], int a[], int exp ) {
    if( exp > 0 ) {
        for( int i = 0 ; i < 2 * MAXDIGITS ; i++ ) {
            if( i == 0 ) p[i] = 0 ; else 
            p[i] = a[i-1] ;
        }   
    }

    int last ;
    for( int j = 1 ; j < exp ; j++ ) {
        for( int i = 0 ; i < 2 * MAXDIGITS ; i++ ) {
            if( i == 0 ) {
                last = p[i] ;
                p[i] = 0 ;
            }
            else
            {
                int temp = p[i] ; /* store current element */
                p[i] = last ; /* replace current element with last element */
                last = temp ; /* store current element for next iteration */
            }
        }
    }
}

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

    /* Print result:
    int start = MAXDIGITS - 1 ;
    while( a[start] == 0 ) start-- ;
    for( int i = start ; i >=0 ; i-- )
        std::cout << a[i] ;
    std::cout << " " ;

    start = MAXDIGITS - 1 ;
    while( b[start] == 0 ) start-- ;
    for( int i = start ; i >= 0 ; i-- )
        std::cout << b[i] ;
    std::cout << " " << std::endl ;
    */

    /* Base Case: */
    if( n < 4 ) {
        school_mult( p, a, b, radix ) ;
        return ;
    }

    /* Recursive Case: */
    /* k = ceil( n / 2 ) */
    int k = n / 2 ;
    if( n % 2 > 0 ) k++ ;

    // std::cout << "n: " << n << " k: " << k << std::endl ;
    
    int a1[MAXDIGITS], a2[MAXDIGITS] ;
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        a1[i] = 0 ;
        a2[i] = 0 ;
    }
    split( a1, a2, a, k ) ;

    int b1[MAXDIGITS], b2[MAXDIGITS] ;
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        b1[i] = 0 ;
        b2[i] = 0 ;
    }
    split( b1, b2, b, k ) ;

    int z0[2*MAXDIGITS], z1[2*MAXDIGITS], z2[2*MAXDIGITS] ;
    for( int i = 0 ; i < 2*MAXDIGITS ; i++ ) {
        z0[i] = 0 ;
        z1[i] = 0 ;
        z2[i] = 0 ;
    }
    int s1[MAXDIGITS], s2[MAXDIGITS] ;
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        s1[i] = 0 ;
        s2[i] = 0 ;
    }

    school_add( s1, a1, a2, radix ) ;
    school_add( s2, b1, b2, radix ) ;

    karatsuba( z0, a2, b2, radix ) ;
    karatsuba( z1, s1, s2, radix ) ;
    karatsuba( z2, a1, b1, radix ) ;

    // return ( z2 * pow( 10, 2 * k ) ) + ( ( z1 - z2 - z0 ) * pow( 10, k ) ) + z0 ;
    int pow1[2*MAXDIGITS], pow2[2*MAXDIGITS], sub1[MAXDIGITS], sub2[MAXDIGITS] ; ;
    for( int i = 0 ; i < 2*MAXDIGITS ; i++ ) {
        pow1[i] = 0 ;
        pow2[i] = 0 ;
    }
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        sub1[i] = 0 ;
        sub2[i] = 0 ;
    }
    power( pow1, z2, 2 * k ) ;
    school_sub( sub1, z1, z2, radix ) ;
    school_sub( sub2, sub1, z0, radix ) ;
    power( pow2, sub2, k ) ;
    school_add( p, pow1, pow2, radix ) ;
    school_add( p, p, z0, radix ) ;
}

int main() {
    int a[MAXDIGITS], b[MAXDIGITS], s[MAXDIGITS], p[2*MAXDIGITS] ;
    int radix ;

    /* Initialize arrays to be empty */
    for( int i = 0 ; i < MAXDIGITS ; i++ ) {
        a[i] = 0 ;
        b[i] = 0 ;
        s[i] = 0 ;
        p[i] = 0 ;
    }

    for( int i = 0 ; i < 2 * MAXDIGITS ; i++ )
        p[i] = 0 ;


    /* Read input from command line */
    std::string first, second ;
    char input[220] ;
    fgets( input, 220, stdin ) ;

    first  = strtok( input, " " ) ;
    second = strtok( NULL, " " ) ;
    radix  = std::stoi( strtok( NULL, " " ) ) ;

    /* Put integers into arrays */
    for( int i = first.length() - 1 ; i >= 0 ; i-- ) {
        a[first.length() - 1 - i] = first[i] - '0' ;
    }

    for( int i = second.length() - 1 ; i >= 0 ; i-- ) {
        b[second.length() - 1 - i] = second[i] - '0' ;
    }

    school_add( s, a, b, radix ) ;
    karatsuba( p, a, b, radix ) ;

    /* Print result: */
    int start = MAXDIGITS - 1 ;
    while( s[start] == 0 ) start-- ;
    for( int i = start ; i >=0 ; i-- )
        std::cout << s[i] ;
    std::cout << " " ;

    start = MAXDIGITS - 1 ;
    while( p[start] == 0 ) start-- ;
    for( int i = start ; i >= 0 ; i-- )
        std::cout << p[i] ;
    std::cout << " 0" << std::endl ;

    return 0 ;
}