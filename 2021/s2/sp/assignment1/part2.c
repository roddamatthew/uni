#include <stdint.h>
#include <stdio.h>

#define O(type, field) ( size_t )( & ( ( (type *) NULL ) -> field ) )

struct byname
{
    int16_t int16;
    int32_t int32;
    int64_t int64;
    int8_t int8;
    intptr_t intptr;
    uint16_t uint16;
    uint32_t uint32;
    uint64_t uint64;
    uint8_t uint8;
    uintptr_t uintptr;
};

struct bysize
{
    int8_t int8;
    uint8_t uint8;
    int16_t int16;
    uint16_t uint16;
    int32_t int32;
    uint32_t uint32;
    int64_t int64;
    uint64_t uint64;
    intptr_t intptr;
    uintptr_t uintptr;
};

int main()
{
    struct byname* a ;
    printf("By size: %d\n", sizeof(struct bysize));
    printf("By name: %d\n", sizeof(struct byname));

    /* Testing macro like function: */
    printf( "%d\n", ( size_t )( & ( a -> int16 ) ) ) ;
    printf( "%d\n", ( size_t )( & ( a -> int32 ) ) ) ;

    printf( "By name: %d\n", O( struct byname, int32 ) ) ;
    printf( "%d\n", O( struct byname, int64 ) ) ;
    printf( "%d\n", O( struct byname, int8 ) ) ;
    printf( "%d\n", O( struct byname, intptr ) ) ;
    printf( "%d\n", O( struct byname, uint16 ) ) ;
    printf( "%d\n", O( struct byname, uint32 ) ) ;
    printf( "%d\n", O( struct byname, uint64 ) ) ;
    printf( "%d\n", O( struct byname, uint8 ) ) ;
    printf( "%d\n", O( struct byname, uintptr ) ) ;

    printf( "By size: %d\n", O( struct bysize, int8 ) ) ;
    printf( "%d\n", O( struct bysize, uint8 ) ) ;
    printf( "%d\n", O( struct bysize, int16 ) ) ;
    printf( "%d\n", O( struct bysize, uint16 ) ) ;
    printf( "%d\n", O( struct bysize, int32 ) ) ;
    printf( "%d\n", O( struct bysize, uint32 ) ) ;
    printf( "%d\n", O( struct bysize, int64 ) ) ;
    printf( "%d\n", O( struct bysize, uint64 ) ) ;
    printf( "%d\n", O( struct bysize, intptr ) ) ;
    printf( "%d\n", O( struct bysize, uintptr ) ) ;
    
}