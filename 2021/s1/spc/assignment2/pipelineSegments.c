#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/* want to check if I can send any data down a pipe */
/* loop 5 times, sending a string down a pipe to the child each time */
/* each time the child is called it gets the string, adds something to it and sends it back */

int main() {
	int i = 0 ;
	int j = 0 ;
	int pid ;
	char* str = "Parent" ;
	char buffer[200] ;
	int new_pipe[2] ;
	int old_pipe[2] ;
	int y ;

	pipe( old_pipe ) ;

	printf( "FD's for old_pipe: %d, %d\n", old_pipe[0], old_pipe[1] ) ;

	/* Remember for pipes: */
	/* 0 : read end  */
	/* 1 : write end */

	for( i = 0 ; i < 3 ; i++ )
	{
		if( i != 4 ) {
			if( pipe( new_pipe ) == -1 ) return 1 ;
			printf( "FD's for new_pipe: %d, %d\n", new_pipe[0], new_pipe[1] ) ;
		}

		pid = fork() ;

		if( pid == 0 ) 
		{
			int x ;
			printf( "\nChild process started: \n" ) ;
			/* close pipe ends we won't use */
			close( old_pipe[1] ) ;
			close( new_pipe[0] ) ;

			/* read from old_pipe[0] */
			printf( "C: read from old_pipe[0]\n" ) ;
			read( old_pipe[0], &x, sizeof( x ) ) ;
			printf( "child read: %d\n", x ) ;

			/* add something to the string and send it back */
			x += 5 ;

			/* write to new_pipe[1] */
			printf( "C: wrote to new_pipe[1]: %d\n", x ) ;
			write( new_pipe[1], &x, sizeof( x ) ) ;

			close( old_pipe[0] ) ;
			close( new_pipe[1] ) ;
		}
		else if( pid > 0 )
		{
			int temp ;
			printf( "\nParent process started: \n" ) ;
			if( i == 0 ) y = 2 ;
			/* close pipe ends we won't use */
			close( old_pipe[0] ) ;
			close( new_pipe[1] ) ;

			if( i != 0 ) {
				printf( "P: read from new_pipe[0]\n" ) ;
				read( new_pipe[0], &temp, sizeof( temp ) ) ;
				y = temp ;
				printf( "Parent read: %d\n", y ) ;
			}
			close( new_pipe[0] ) ;

			if( i != 4 ) {
				printf( "P: wrote to old_pipe[1]: %d\n", y ) ;
				write( old_pipe[1], &y, sizeof( y ) ) ;
			}
			close( old_pipe[1] ) ;
			wait( NULL ) ;
		}
	}
}