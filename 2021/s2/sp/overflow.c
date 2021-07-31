#include <stdio.h>
#include <stdlib.h>

int main( int c, char **v ) {
    unsigned i, n ;

    n = strtoul( v[1], NULL, 0 ) ;

    for( i = n ; i < n + 10 ; i++ )
        printf( "%u\n", i ) ;

    return 0 ;
}