#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "smsh.h"

char **removeRedirect( char **args )
/* remove the redirect operator and filename from the argument
 * If a redirect is read, replace it with a NULL
 * This functionally removes it from the array for later calling with execvp
 * Could free the memory after the redirect but this is always two char*
 * Memory will be freed later so this is unnecessary
 */
{
	int i = 0 ;

	/* Find the position of the < or > */
	while( args[i] != NULL ) {
		if( !strcmp( args[i], "<" ) || !strcmp( args[i], ">" ) ) {
			args[i] = NULL ;
		}
		i++ ;
	}

	return args ;
}

/* 
 * Called if a "<" or ">" token is read
 * Redirect stdin to a file descriptor
 */

char **redirect( char** args ) {
	char *file ;
	FILE *fileptr ;
	char *newstr() ;

	int i = 0 ;
	while( args[i] != NULL ) {
		if( !strcmp( args[i], "<" ) ) {
			if( args[i+1] != NULL ) {
				file = newstr( args[i+1], strlen( args[i+1] ) ) ;
				close( 0 ) ;
				fileptr = fopen( file, "r" ) ;
			}
		}

		if( !strcmp( args[i], ">" ) ) {
			if( args[i+1] != NULL ) {
				file = newstr( args[i+1], strlen( args[i+1] ) ) ;
				close( 1 ) ;
				fileptr = fopen( file, "w" ) ;
			}
		}

		i++ ;
	}

	args = removeRedirect( args ) ;

	return args;
}