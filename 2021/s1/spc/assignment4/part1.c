#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int i = 0 ;

	void *slow_function1() ; /* silence in-line declaration warning */
	void *slow_function2() ; /* silence in-line declaration warning */

	/* thread for slow_function2 */
	pthread_t initialThread ;

	/* threads for slow_function1 calls */
	pthread_t * threads = malloc( sizeof( pthread_t ) * 10 ) ;

	/* call slow_function2 in its own thread */
	if( pthread_create( &initialThread, NULL, slow_function2, NULL ) ) {
		printf( "pthread_create() failed!\n" ) ;
		return 1 ;
	}

	/* call slow_function1 on 10 different threads */
	for( i = 0 ; i < 10 ; i++ ) {
		if( pthread_create( &threads[i], NULL, slow_function1, NULL ) ) {
			printf( "pthread_create() failed!\n" ) ;
			return 1 ;
		}
	}

	/* join the threads back to main */
	for( i = 0 ; i < 10 ; i++ ) {
		if( pthread_join( threads[i], NULL ) ) {
			printf( "pthread_join() failed!\n" ) ;
			return 2 ;
		}
	}

	/* join the initial thread back to main */
	if( pthread_join( initialThread, NULL ) ) {
		printf( "pthread_join() failed!\n" ) ;
		return 2 ;
	}

	return 0 ;
}