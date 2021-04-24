/* Can assume:
Maximum of 10 arguments per command
256 characters per line
100 lines per command file
One command per line

gcc -Wall -ansi -pedantic -o sequence sequence.c

Start with:
Parsing a command and its arguments
Turn this command into a string
Store this in an array
Test thoroughly with TRACE statements

C90 standard I think? */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/* Define some max values as given in the  */
#define MAXARGS 10 /* */
#define MAXCMDS 100 /* */
#define MAXCHARS 256 /* */

static int TRACE = 0 ;

static char* arguments[ MAXCMDS ][ MAXARGS ] ;
static char* command[ MAXCMDS ] ;
static bool eof = false ;

/* return a copy of the input string */
/* end the input string when the first space is read, or we reach the end of the string */
char* copyStringUntilSpace( char* string ) {
	int i ;
	char* copy = malloc( strlen( string ) + 1 ) ;
	strcpy( copy, string ) ;

	for( i = 0 ; i < strlen( copy ) ; i++ ) {
		if( copy[i] == ' ' ) copy[i] = NULL ; else
		if( copy[i] == 10  ) copy[i] = NULL ; else
		if( copy[i] == 0   ) copy[i] = NULL ;
	}

	return copy ;
}

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

	/* printf( "characters before first space %d\n", charsBeforeSpace ) ;
	printf( "characters after first space %d\n", charsAfterSpace ) ;
	printf( "%.*s", charsAfterSpace, string + charsBeforeSpace ) ; */

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

bool containsEOF( char* string ) {
	int i = 0 ;
	bool eoi = false ;
	
	while( i <= strlen( string ) + 1 && eoi == false ) {
		if( string[i] == 0 ) return true ; else
		if( string[i] == 10 ) eoi = true ;
		i++ ;
	}
	return false ;
}

void readCommand() {
	int i = 0 ;
	int j = 0 ;
	int k = 0 ;
	char input[ MAXCHARS ] ;
	char* inputPointer ;
	bool error = false ;

	/* initialize both arrays to be filled with NULL */
	for( i = 0 ; i < MAXCMDS ; i++ ) {
		command[i] = NULL ;
		for( j = 0 ; j < MAXARGS ; j++ ) {
			arguments[i][j] = NULL ;
		}
	}

	i = 0 ;
	j = 0 ;

	/* read command */
	while( j < MAXCMDS && eof == false && error == false && fgets( input, MAXCHARS, stdin ) != NULL ) {

		if( input[0] == '\n' ) {
			eof = true ;
			if( TRACE > 0 )
				printf( "EMPTY INPUT!!!\n" ) ;
		}

		if( TRACE > 0 ) {
			printf( "input: %s\n", input ) ;
			printf( "input as decimal: \n" ) ;
			for( k = 0 ; k < MAXCHARS ; k++ ) {
				printf( "%d ", input[k] ) ;
			}
			printf( "\n" ) ;
		}

		/* Check if input has any negative numbers */
		/* This could find if we've read in junk memory */
		for( i = 0 ; i < strlen( input ) ; i++ ) {
			if( input[i] < 0 ) {
				error = true ;
				eof = true ;
			}
			if( TRACE > 0 )
				printf( "input character %d: %d, error = %d\n", i, input[i], error ) ;
		}

		if( error == false && input[0] != '\n' ) {
			/* check if this is the last line of the input */
			if( containsEOF( input ) ) eof = true ;

			/* copy the first word of the input into the command string */
			command[j] = copyStringUntilSpace( input ) ;
			if( TRACE > 0 ) 
				printf( "command: %s\n", command[j] ) ;

			inputPointer = input ;
			/* loop over each word in the input line */
			for( i = 0 ; i < nWords( input ) ; i++ ) {
				/* add the first word of the input to args array */
				arguments[j][i] = copyStringUntilSpace( inputPointer ) ;

				/* move the input string across to the next word */
				inputPointer = copyStringAfterSpace( inputPointer ) ;
				if( TRACE > 0 ) 
					printf( "argument %d: %s\n", i, arguments[j][i] ) ;
			}

			if( TRACE > 0 ) 
				printf( "\n" ) ;

			/* last element of arguments string must be NULL for execvp */
			arguments[ j ][ i ] = NULL ;
		}
		j++ ;
	}
}

void printCommand( int i ) {
	int j ;
	for( j = 0 ; j < MAXARGS ; j++ ) {
		printf( "arg%d: %s\n", j, arguments[i][j] ) ;
	}
}

void executeCommands() {
	int pid = 0 ;
	int i = 0 ;

	while( i < 100 ) {
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
			if( TRACE > 0 ) {
				printf( "Executing command %d:\n", i ) ;
				printCommand( i ) ;
				printf( "Output of command:\n" ) ;
			}
			execvp( command[i], arguments[i] ) ;
		}
		i++ ;
	}

}

/* Parse Input into the input array */
/* input is a 2D array of chars */
/* This can also be thought of a 1D array of strings */
/* Access each line of input with the row, and each character with the column */

int main() {
	readCommand() ;
	executeCommands() ;

	return 0 ;
}
