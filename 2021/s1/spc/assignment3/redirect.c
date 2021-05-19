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
	char *filename ;
	FILE *fileptr ;
	char *newstr() ; 	/* silence in-line declaration warning */

	int i = 0 ;
	while( args[i] != NULL ) { /* loop through current command */
		if( !strcmp( args[i], "<" ) ) { /* Check if the current argument is a redirect */
			if( args[i+1] != NULL ) { /* Avoid segfaulting if there is a unexpected input */
				filename = newstr( args[i+1], strlen( args[i+1] ) ) ; /* store the filename, this is always the next parameter */
				close( STDIN_FILENO ) ;
				fileptr = fopen( filename, "r" ) ; /* redirect to the filename, read only */
			}
		}
		else if( !strcmp( args[i], ">" ) ) { /* Check if the current argument is a redirect */
			if( args[i+1] != NULL ) { /* Avoid segfaulting if there is a unexpected input */
				filename = newstr( args[i+1], strlen( args[i+1] ) ) ; /* store the filename, this is always the next parameter */
				close( STDOUT_FILENO ) ; 
				fileptr = fopen( filename, "w" ) ; /* redirect to the filename, write only */
			}
		}

		i++ ;
	}

	/* Remove the redirect from the parameters */
	args = removeRedirect( args ) ;

	return args;
}