#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* ----------------------------------------Copy from sequence.c------------------------------------------*/

/* Define some max values as given in the assignment brief */
#define MAXARGS 10 /* maximum number of arguments for a command */
#define MAXCMDS 100 /* maximum number of commands from a file */
#define MAXCHARS 256 /* maximum number of characters per line */

/* global variable for debugging */
/* set greater than 1 to check the behaviour at each step */
static int TRACE = 0 ;

/* global variables for storing our commands */
/* each element is a string */
/* each row is a command */
/* each column is an argument */
static char* arguments[ MAXCMDS ][ MAXARGS ] ;

/* return a copy of the input string */
/* end the input string when the first space is read, or we reach the end of the string */
char* copyStringUntilSpace( char* string ) {
	int i ;
	char* copy = malloc( strlen( string ) + 1 ) ;
	strcpy( copy, string ) ;

	for( i = 0 ; i < strlen( copy ) ; i++ ) {
		if( copy[i] == ' ' ) copy[i] = '\0' ; else
		if( copy[i] == 10  ) copy[i] = '\0' ; else
		if( copy[i] == 0   ) copy[i] = '\0' ;
	}

	return copy ;
}

/* Copy all characters in a string after the first space is read */
/* This is used to remove arguments from a line one at a time */
char* copyStringAfterSpace( char* string ) {
	int i ;
	int charsBeforeSpace = 0 ;
	int charsAfterSpace = 0 ;
	bool readSpace = false ;
	char* copy ;
	
	/* loop over the string */
	for( i = 0 ; i < strlen( string ) ; i++ ) {
		/* find how many characters are before and after the first space */
		if( string[i] == ' ' && readSpace == false ) {
			readSpace = true ;
			charsBeforeSpace++ ;
		}
		else if( readSpace == true ) charsAfterSpace++ ; else
		charsBeforeSpace++ ;
	}

	/* Allocate memory for a new string */
	copy = malloc( charsAfterSpace + 1 ) ;
	memcpy( copy, &string[ charsBeforeSpace ], charsAfterSpace ) ;
	copy[ charsAfterSpace ] = '\0' ;

	return copy ;
}

/* returns the number of 'words' in the string */
/* read through the whole string and return the number of spaces + 1 */
int nWords( char* string ) {
	int i = 0 ;
	int n = 0 ;

	while( string[i] != 10 && string[i] != 0 && i <=strlen( string ) ) {
		if( string[i] == ' ' ) n++ ;
		i++ ;
	}
	/* final word will not have a space after it */
	n++ ;

	return n ;
}

/* Read input into our arguments array */
void readCommands() {
	int i, j ;
	char input[ MAXCHARS ] ;
	char* inputPtr ;

	/* initialize both arrays to be filled with NULL */
	for( i = 0 ; i < MAXCMDS ; i++ ) {
		for( j = 0 ; j < MAXARGS ; j++ ) {
			arguments[i][j] = NULL ;
		}
	}

	/* Reset j = 0 */
	j = 0 ;

	/* Loop over the whole input or until we've read our max number of commands */
	while( fgets( input, MAXCHARS, stdin ) != NULL && j < MAXCMDS ) {

		/* Display the input for debugging */
		if( TRACE > 0 ) {
			printf( "input: %s\n", input ) ;
			printf( "input as decimal: \n" ) ;
			
			/* Display characters as ASCII decimals */
			for( i = 0 ; i < MAXCHARS ; i++ ) {
				printf( "%d ", input[i] ) ;
			}
			printf( "\n" ) ;
		}

		/* Set our temporary pointer equal to our input's address*/
		inputPtr = input ;
		/* loop over each word in the input line */
		for( i = 0 ; i < nWords( input ) ; i++ ) {
			/* add the first word of the input to args array */
			arguments[j][i] = copyStringUntilSpace( inputPtr ) ;

			/* move the input string across to the next word */
			inputPtr = copyStringAfterSpace( inputPtr ) ;
			if( TRACE > 0 ) 
				printf( "argument %d: %s\n", i, arguments[j][i] ) ;
		}

		if( TRACE > 0 ) 
			printf( "\n" ) ;

		/* last element of arguments string must be NULL for execvp */
		arguments[ j ][ i ] = NULL ;
		/* increase our commands counter */
		j++ ;
	}
}

int numberOfCommands() {
	int i ;
	int n = 0 ;
	/* Count the number of non NULL inputs in arguments */
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
				dup2( input, 0 ) ;
				close( input ) ;
			}

			/* If this isn't the last command, redirect output from stdout to our pipe */
			if( i != nCommands - 1 ) {
				dup2( p[1], 1 ) ;
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