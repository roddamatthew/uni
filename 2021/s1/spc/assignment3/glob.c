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

int main()
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors
 */
{
	int	i = 0 ;
	int	child_info = -1;
	glob_t globbuf ;

	char* command[4] ;
	command[0] = "wc" ;
	command[1] = "smsh2" ;
	command[2] = "*.c" ;
	command[3] = NULL ;

	/* Need to check an argument to see if it requires globbing */

	/* */

	glob( "*.c", GLOB_DOOFFS, NULL, &globbuf ) ;

	while( globbuf.gl_pathv[i] != NULL ) {
		printf( "%s\n", globbuf.gl_pathv[i] ) ;
		i++ ;
	}

    globfree( &globbuf ) ;

	return 0;
}