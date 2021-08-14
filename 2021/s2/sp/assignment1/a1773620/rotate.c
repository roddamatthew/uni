#include <stdint.h>
#include <stdio.h>

/* Rotate a 32 bit value count times */
uint32_t rotate( uint32_t number, uint32_t count )
{
    for( int i = 0 ; i < count ; i++ )
    {
        /* If number > 2^31, then the 32nd bit must be 1, so shift in a 1 */
        if( number > 2147483648 )
        {
            /* Bitwise shift the number and add 1 */
            number = number << 1 ;
            number++ ;
        }
        /* Otherwise, shift in a zero */
        else number = number << 1 ;
    }

    return number ;
}