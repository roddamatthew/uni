/* pipeline.c - code used by small shell to pipeline commands */
/* Piping implementation copied from assignment 2 
 * Only difference from pipelinePart1.c is a call to redirect
 * If a redirect is present this returns the command with that argument removed, 
 * and STDIN/STDOUT moved to the filename
 * If a redirect is not present it simply returns the command
 */


#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include 	<fcntl.h>

int nCommands( char ***commands )
/*
 * purpose: find the number of commands in the input array
 */
{
	int i = 0 ;
	while( commands[i] != NULL ){
		i++ ;
	}
	return i ;
}

int pipeline( char ***commands )
/*
 * purpose: run a program passing it arguments, pipe output of last command to input of next command
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors
 */
{
	int	pid, i ;
	int	child_info = -1;
	int n = nCommands( commands ) ;

	int p[2] ;
	int input = 0 ;
	char **redirect();
	void printCommands() ;

	for( i = 0 ; i < n ; i++ ) {
		/* If this isn't the last command, create a pipe */
		if( i != n - 1 )
			if( pipe( p ) == -1 ) {
				printf( "Pipe failed\n" ) ;
				return -1;
			}

		/* Fork and handle errors */
		if( ( pid = fork() ) < 0 ) {
			printf( "Fork failed\n" ) ;
			return -1;
		} ;

		if( pid == 0 ) { /* Child: */
			/* If this isn't the first command, redirect input from stdin to our input */
			if( i != 0 ) {
				dup2( input, STDIN_FILENO ) ;
				close( input ) ;
			}

			/* If this isn't the last command, redirect output from stdout to our pipe */
			if( i != n - 1 ) {
				dup2( p[1], STDOUT_FILENO ) ;
				close( p[1] ) ;
			}

			/* redirect the current command */
			commands[i] = redirect( commands[i] ) ;

			/* Execute the command */
			/* Input will be coming from 'input' */
			/* Output will be written to p[1] */
			execvp( commands[i][0], commands[i] ) ;


		} else if( pid > 0 ) { /* Parent */
			/* Close the input file descriptor */
			if( i != 0 ) {
				close( input ) ;
			}

			/* Next commands input will be the output of the last command */
			if( i != n - 1 ) {
				input = p[0] ;
			}
			/* Wait for child to finish executing */
			wait( NULL ) ;
		}
		/* Clean up open pipe */
		close( p[1] ) ;
	}

	return child_info ;
}