#include <stdio.h>
#include <string.h>
 
int
main(void)
{
  char* a[3] = {"Hello","World","yay"};
  char* b[3] = {"foo","bar",NULL};
  char **c ;
  int i;
 

  c = malloc( 6 * sizeof( char* ) ) ;

  memcpy( c   , a, 3 * sizeof( char* ) ) ;
  memcpy( c + 3, b, 3 * sizeof( char* ) ) ;

  for (i = 0; i < 6; i++) {
    printf("%s\n", c[i]);
  }
}