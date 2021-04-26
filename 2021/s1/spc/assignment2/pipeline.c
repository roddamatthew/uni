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

void pipeline() {
	// For each command except the final one:
	// new_pipe = the output of the current command
	// For each command except the first one:
	// prev_pipe = the output of the previous command, input of current command

	/* for cmd in cmds:
	    if this is not the final command:
	        pipe (new_pipe)    // Create a new pipe

	    fork and handle errors

	    if (child)
	        if this is not the first command:
	            Redirect input to prev_pipe
	        if this is not the final command:
	            Redirect output to new_pipe
	        execute command
	    else // parent
	        if this is not the first command:
	            close prev_pipe
	        if this is not the final command:
	            prev_pipe = new_pipe

	
	close any remaining pipes, clean up */
	int i ;
	int prev_pipe[2] ;
	pipe( prev_pipe ) ;
	pid_t my_pid ;

	for( i = 0 ; i < numberOfCommands() ; i++ ) {
		// if( i != 1 ) pipe( new_pipe ) ;

		my_pid = fork() ;

			// Fork Fail
		if (my_pid < 0){
			printf("Failed Fork\n");
		} // Fork Parent
		else if ( my_pid > 0 ) {
			// close the write end of pipe
			close( prev_pipe[1] ) ;
			// set read end to stdin
			dup2( prev_pipe[0], 0 ) ;
			// close read end of pipe
			close( prev_pipe[0] ) ;
			// wait for child
			wait( NULL ) ;
		} // Fork Child
		else {
			// close the read end of pipe
			close( prev_pipe[0] ) ;
			// set write end to stdout
			dup2( prev_pipe[1], 1 ) ;
			// close the write end of our pipe
			close( prev_pipe[1] ) ;
			// execute command: output will go to new_pipe[0]?
			execvp( arguments[i][0], arguments[i] ) ;
		}
	}
}

void pipelineCommands() {
	int pid = 0 ;
	int i = 0 ;
	int nCommands = numberOfCommands() ;

	int pipe[2] ;
	pipe[0] = 0 ;
	pipe[1] = 1 ;

	while( i < MAXCMDS * 2 ) {
		/* Check if we've run out of commands */
		if( arguments[i][0] == NULL ) break ;

		/* If this isn't the last command, make a new pipe */
		if( i != nCommands - 1 )
			// pipe( pipe ) ;
			printf( "Create new pipe\n" ) ;

		/* fork process */
		pid = fork() ;

		if( pid < 0 ) { /* fork has failed */
			printf( "Error has occurred: pid < 0" ) ;
		}
		else if( pid > 0 ) /* parent: wait for child process to finish */
		{
			if( i != 0 ) {
				printf( "Close previous pipe\n" ) ;
				close( pipe[1] ) ;
			}
			if( i != nCommands - 1 ) {
				printf( "Set previous pipe = new pipe\n" ) ;
				dup2( pipe[0], 0 ) ;
			}
			wait( NULL ) ;
		}
		else if( pid == 0 ) /* child: execute new process */
		{
			/* Print out the command we're about to execute */
			if( TRACE > 0 ) {
				printf( "Executing command %d:\n", i ) ;
				printCommand( i ) ;
				printf( "Output of command:\n" ) ;
			}

			if( i != 0 ) {
				printf( "Redirect input into previous pipe\n" ) ;
				dup2( pipe[1], 1 ) ;
			}
			if( i != nCommands - 1 ) {
				 printf( "Redirect output to new pipe\n" ) ;
			}
			/* Execute the next command in the arguments array */
			execvp( arguments[i][0], arguments[i] ) ;
		}
		i++ ;
	}

}

int main() {
	readCommands() ;
	pipeline() ;

	return 0 ;
}