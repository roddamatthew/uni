#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "smsh.h"

char **removeRedirect( char **args )
/* split a command if a < or > is found
 * Remove the < > and the filename from the command
 */
{
	char *newstr() ;
	int i = 0 ;
	int pos = -1 ;

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