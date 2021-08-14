#include <stdint.h>
#include <stdio.h>

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