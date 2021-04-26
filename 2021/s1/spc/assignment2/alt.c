/* alternative solution 
try to store as little information as necessary
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



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

/*

1. Read line of input
	2. copy characters until reading a space into a variable: char* cmd
	3. copy remaining characters until eoi || eof into a variable: char* args[]
		- Whenever a space is read, copy the characters into the next element of char* args[]
	4. set char* args[end] = NULL
	5. execvp( cmd, args ) ;
6. Repeat step 1 with next line until eof

need to dynamically create and allocate pointers

*/



int main() {
	char* string = "Hello World!" ;
	char* copy ;




	char* copies[3] ;

	copies[0] = copyString( string ) ;
	string = "Fartmouth" ;
	copies[1] = copyString( string ) ;
	string = "Fartfoot" ;
	copies[2] = copyString( string ) ;

	printf( "%s\n", copies[0] ) ;
	printf( "%s\n", copies[1] ) ;
	printf( "%s\n", copies[2] ) ;

	return 0 ;
}

/* 
void readInput() {
	int i = 0 ;
	int j = 0 ;
	bool eof = false ;
	bool eoi = false ;

	/* Read input until we read an eof or reach our max commands */
	while( i <= MAXCMDS && eof == false ) {
		/* Read input into the next row of input */
		fgets( input[i], MAXCHARS, stdin ) ;
		/* puts( input[i] ) ; */

		/* Reset exit variables for our next loop */
		eoi = false ;
		j = 0 ;

		/* Read characters until we find an end of input, end of file or reach our max characters */
		while( j <= MAXCHARS && eoi == false && eof == false ) {
			printf( "%c", input[i][j] ) ;
			if( (int) input[i][j] == 10 ) eoi = true ; else
			if( (int) input[i][j] == 0  ) eof = true ;
			j++ ;
		}
		i++ ;
		ncmds = i ;
		printf( "\n" ) ;
	}
}

/* Isolate the commands from the rest of the input lines */
void getCommands() {
	int i ;
	int j ;
	int k ;
	char* temp ;

	/* Loop over each command in input */
	for( i = 0 ; i < ncmds ; i++ ) {
		j = 0 ;
		k = 0 ;
		temp = "" ;

		/* Read characters until the first space is read */
		while( input[i][j] != ' ' && input[i][j] != 10 && input[i][j] != 0 && j <= MAXCHARS  ) {
			cmdsIsolated[i][j] = input[i][j] ;
			printf( "%c", cmdsIsolated[i][j] ) ;
			j++ ;
		}
		/* Read characters after the first space until the eoi || eof */
		/* These are our command parameters */
		while( input[i][j] != 10 && input[i][j] != 0 && j <= MAXCHARS ) {
			if( input[i][j] == ' ' ) k++ ;
			args[i][k][j] = input[i][j] ;
			printf( "%c", args[i][k][j] ) ;
			j++ ;
		}
		/* args[i][k] = "NULL" ; */
		printf( "\n" ) ;
	}
}

void print3D( char*** array ) {
	int i = 0 ;
	int j = 0 ;
	int k = 0 ;

	while( i <= ncmds ) {
		while( k <= MAXARGS && args[i][k] != NULL ) {
			while( j <= MAXCHARS ) {
				printf( "%c", args[i][k][j] ) ;
				j++ ;
			}
			k++ ;
		}
		i++ ;
	}
}
*/
