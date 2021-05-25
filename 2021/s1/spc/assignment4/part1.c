#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int i = 0 ;

	void *slow_function1() ;
	void *slow_function2() ;

	pthread_t initialThread ;

	pthread_t * threads = malloc( sizeof( pthread_t ) * 10 ) ;

	if( pthread_create( &initialThread, NULL, slow_function2, NULL ) ) {
		printf( "pthread_create() failed!\n" ) ;
		return 1 ;
	}

	for( i = 0 ; i < 10 ; i++ ) {
		if( pthread_create( &threads[i], NULL, slow_function1, NULL ) ) {
			printf( "pthread_create() failed!\n" ) ;
			return 1 ;
		}
	}

	for( i = 0 ; i < 10 ; i++ ) {
		if( pthread_join( threads[i], NULL ) ) {
			printf( "pthread_join() failed!\n" ) ;
			return 2 ;
		}
	}

	if( pthread_join( initialThread, NULL ) ) {
		printf( "pthread_join() failed!\n" ) ;
		return 2 ;
	}

	return 0 ;
}