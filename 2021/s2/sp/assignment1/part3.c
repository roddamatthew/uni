#include <stdint.h>
#include <stdio.h>
#include <math.h>

uint32_t rotate( uint32_t number, uint32_t count )
{
    int i ;
    for( i = 0 ; i < count ; i++ )
    {
        /* Shift in a 1 */
        if( number > 2147483647 )
        {
            number = number << 1 ;
            number++ ;
        }
        /* Shift in a 0 */
        else
        {
            number = number << 1 ;
        }
    }

    return number ;
}

void num_modexp( int base, int exp, int mod )
{
    int x = 1 ;
    for( int i = 2 ; i >= 0 ; i-- ) {
        x = ( x * x ) % mod ;
        printf( "Square + Reduce: %d\n", x ) ;
        
        if( exp / pow( 2, i ) > 0 ) {
            printf( "YES %d\n", 5/2 ) ;
        }
    }
    printf( "%d\n", x ) ;
}

int main()
{
    num_modexp( 12, 5, 77 ) ;
    return 0 ;
}