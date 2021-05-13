#include 	<glob.h>
#include 	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include 	<string.h>

/*
 * purpose: constructor for strings
 * returns: a string, never NULL
 */
char *newstr(char *s, int l)
{
	char *rv = malloc(l+1);

	rv[l] = '\0';
	strncpy(rv, s, l);
	return rv;
}

int checkGlob( char** arglist ) {
	int i = 0 ;

	while( arglist[i] != NULL ) {
		if( strchr( arglist[i], '*' ) != NULL ) return i ;
		if( strchr( arglist[i], '?' ) != NULL ) return i ;
		if( strchr( arglist[i], '[' ) != NULL ) return i ;
		i++ ;
	}

	return -1 ;
}

int main()
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors
 */
{
	int	i = 0 ;
	int n ;
	int	child_info = -1;
	glob_t globbuf ;

	char* command[4] ;
	command[0] = "wc" ;
	command[1] = "smsh2" ;
	command[2] = "*.c" ;
	command[3] = NULL ;

	n = checkGlob( command ) ;
	int nCommands = 3 ;

	if( n != -1 ) {
		printf( "Found Glob at: %d\n", checkGlob( command ) ) ;
		glob( command[n], GLOB_DOOFFS, NULL, &globbuf ) ;
		char **newCommand = malloc( ( globbuf.gl_pathc + nCommands ) * sizeof( char* ) ) ;
		memcpy( newCommand			  , command, nCommands * sizeof( char* ) ) ;
		memcpy( newCommand + nCommands, globbuf.gl_pathv, globbuf.gl_pathc * sizeof( char* ) ) ;

		while( newCommand[i] != NULL ) {
			printf( "%s\n", newCommand[i] ) ;
			i++ ;
		}

		globfree( &globbuf ) ;
	}

	/* Need to check an argument to see if it requires globbing */

	/* */

	return 0;
}