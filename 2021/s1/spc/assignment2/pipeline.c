#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/* ----------------------------------------Copy from sequence.c------------------------------------------*/

/* Define some max values as given in the assignment brief */
#define MAXARGS 10 /* maximum number of arguments for a command */
#define MAXCMDS 100 /* maximum number of commands from a file */
#define MAXCHARS 256 /* maximum number of characters per line */

/* global variables for storing our commands */
/* each element is a string */
/* each row is a command */
/* each column is an argument */
static char* arguments[ MAXCMDS ][ MAXARGS ] ;

/* Read input into our arguments array */
void readCommands() {
	char* delimiters = " \n\r" ;
	int i, j = 0 ;
	char* string ;

	while( j < MAXCMDS ) {
		// Allocate memory for current line to be stored in
		string = ( char* )malloc( ( MAXCHARS + 1 ) * sizeof( char ) ) ;
		if( string == NULL ) printf( "malloc failed!\n" ) ;

		/* if we're reached the eof, stop reading input*/
		if( fgets( string, MAXCHARS, stdin ) == NULL ) break ;

		/* read the first token of the input string */
		char* tokens = strtok( string, delimiters ) ;
		i = 0 ;

		/* loop until we read a null token or have more than 10 arguments */
		while( tokens != NULL && i < MAXARGS ) {
			/* store the current token in the arguments array */
			arguments[j][i] = tokens ;
			/* read the next token in the input string */
			tokens = strtok( NULL, delimiters ) ;
			i++ ;
		}

		/* increase our commands counter */
		j++ ;
	}
}

int numberOfCommands() {
	int i ;
	int n = 0 ;
	/* Count the number of non NULL elements in arguments */
	/* only need to read the first element as these are the commands */
	for( i = 0 ; i < MAXCMDS ; i++ ) {
		if( arguments[i][0] != NULL ) n++ ;
	}
	return n ;
}

/* Print out a command and its arguments for debugging */
void printCommand( int i ) {
	int j ;
	for( j = 0 ; j < MAXARGS ; j++ ) {
		printf( "arg%d: %s\n", j, arguments[i][j] ) ;
	}
}

/* ----------------------------------End of copy from sequence.c-----------------------------------------*/

void pipelineCommands() {
	pid_t pid ;
	int i ;
	int nCommands = numberOfCommands() ;

	int p[2] ;
	int input = 0 ;

	/* Loop over each command */
	for( i = 0 ; i < nCommands ; i++ ) {
		/* If this isn't the last command, create a pipe */
		if( i != nCommands - 1 )
			if( pipe( p ) == -1 ) {
				printf( "Pipe failed\n" ) ;
				return ;
			}

		/* Fork and handle errors */
		if( ( pid = fork() ) < 0 ) {
			printf( "Fork failed\n" ) ;
			return ;
		} ;

		if( pid == 0 ) { /* Child: */
			/* If this isn't the first command, redirect input from stdin to our input */
			if( i != 0 ) {
				dup2( input, STDIN_FILENO ) ;
				close( input ) ;
			}

			/* If this isn't the last command, redirect output from stdout to our pipe */
			if( i != nCommands - 1 ) {
				dup2( p[1], STDOUT_FILENO ) ;
				close( p[1] ) ;
			}

			/* Execute the command */
			/* Input will be coming from 'input' */
			/* Output will be written to p[1] */
			execvp( arguments[i][0], arguments[i] ) ;


		} else if( pid > 0 ) { /* Parent */
			/* Close the input file descriptor */
			if( i != 0 ) {
				close( input ) ;
			}

			/* Next commands input will be the output of the last command */
			if( i != nCommands - 1 ) {
				input = p[0] ;
			}
			/* Wait for child to finish executing */
			wait( NULL ) ;
		}
		/* Clean up open pipe */
		close( p[1] ) ;
	}
}

int main() {
	readCommands() ;
	pipelineCommands() ;

	return 0 ;
}
