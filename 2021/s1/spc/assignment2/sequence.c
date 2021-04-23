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

/* Define some max values as given in the  */
#define MAXARGS 10 /* */
#define MAXCMDS 100 /* */
#define MAXCHARS 256 /* */

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

	while( string[i] != 10 && string[i] != 0 ) {
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
	
	while( i <= strlen( string ) && eoi == false ) {
		if( string[i] == 0 ) return true ; else
		if( string[i] == 10 ) eoi = true ;
		i++ ;
	}
	return false ;
}

/* Parse Input into the input array */
/* input is a 2D array of chars */
/* This can also be thought of a 1D array of strings */
/* Access each line of input with the row, and each character with the column */

int main() {
	int i = 0 ;
	int j = 0 ;
	bool eof = false ;
	char input[ MAXCHARS ] ;
	char* command ;
	char* testing ;
	char* arguments[ MAXARGS ] ;
	int pid = 0 ;
	int TRACE = 0 ;

	/* read command */
	while( j <= MAXCMDS && eof == false ) {
		fgets( input, MAXCHARS, stdin ) ;
		if( TRACE > 0 ) 
			printf( "input: %s\n", input ) ;
		if( containsEOF( input ) ) eof = true ;

		command = copyStringUntilSpace( input ) ;
		if( TRACE > 0 ) 
			printf( "command: %s\n", command ) ;

		testing = input ;
		for( i = 0 ; i < nWords( input ) ; i++ ) {
			arguments[i] = copyStringUntilSpace( testing ) ;
			testing = copyStringAfterSpace( testing ) ;
			if( TRACE > 0 ) 
				printf( "argument %d: %s     ", i, arguments[i] ) ;
		}
		if( TRACE > 0 ) 
			printf( "\n" ) ;
		arguments[ i ] = NULL ;
		j++ ;

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
			execvp( command, arguments ) ;
		}
	}

	return 0 ;
}
