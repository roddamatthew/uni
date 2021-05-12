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
	int fd ;
	char *newstr() ;

	int i = 0 ;
	while( args[i] != NULL ) {
		if( !strcmp( args[i], "<" ) ) {
			if( args[i+1] != NULL ) {
				file = newstr( args[i+1], strlen( args[i] ) ) ;
				close( 0 ) ;
				fd = open( file, O_RDONLY ) ;
			}
		}

		if( !strcmp( args[i], ">" ) ) {
			if( args[i+1] != NULL ) {
				file = newstr( args[i+1], strlen( args[i] ) ) ;
				close( 1 ) ;
				fd = open( file, O_WRONLY ) ;
			}
		}

		i++ ;
	}

	args = removeRedirect( args ) ;

	return args;
}