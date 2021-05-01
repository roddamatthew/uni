#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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

/* Called after reading input to execute each of the commands in the global arrays */
void executeCommands() {
	int pid = 0 ;
	int i = 0 ;

	while( i < MAXCMDS * 2 ) {
		/* Check if we've run out of commands */
		if( arguments[i][0] == NULL ) break ;

		/* fork process */
		pid = fork() ;

		if( pid < 0 ) { /* fork has failed */
			printf( "Error has occurred: pid < 0" ) ;
		}
		else if( pid > 0 ) /* parent: wait for child process to finish */
		{
			wait( NULL ) ;
		}
		else if( pid == 0 ) /* child: execute new process */
		{
			/* Execute the next command in the arguments array */
			execvp( arguments[i][0], arguments[i] ) ;
		}
		i++ ;
	}

}

int main() {
	readCommands() ;
	executeCommands() ;

	return 0 ;
}
