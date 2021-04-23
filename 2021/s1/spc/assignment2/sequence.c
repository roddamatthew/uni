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

/* Parse Input into the input array */
/* input is a 2D array of chars */
/* This can also be thought of a 1D array of strings */
/* Access each line of input with the row, and each character with the column */

int main() {
	int i = 0 ;
	char input[ MAXCHARS ] ;
	char* command ;
	char* arguments[ MAXARGS ] ;

	fgets( input, MAXCHARS, stdin ) ;
	printf( "%s", input ) ;

	command = copyStringUntilSpace( input ) ;
	printf( "command stores: %s\n", command ) ;

	arguments[0] = copyStringUntilSpace( input ) ;
	printf( "args[0] stores: %s\n", arguments[0] ) ;

	arguments[1] = NULL ;
	printf( "args[1] stores: %s\n", arguments[1] ) ;

	execvp( command, arguments ) ;

	
	/* 
	char* cmd = "ls" ;
	char* argv[3] ;
	argv[0] = "ls" ;
	argv[1] = "-la" ;
	argv[2] = NULL ;

	execvp( cmd, argv ) ;
	*/

	return 0 ;
}
