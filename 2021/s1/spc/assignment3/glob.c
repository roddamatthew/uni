#include 	<glob.h>
#include 	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include 	<string.h>

int checkGlob( char** arglist ) {
	int i = 0 ;

	while( arglist[i] != NULL ) {
		if( strchr( arglist[i], '*' ) != NULL ) return i ;
		if( strchr( arglist[i], '?' ) != NULL ) return i ;
		if( strchr( arglist[i], '[' ) != NULL ) return i ;
		i++ ;
	}

	return -1 ;
}

char** globCommand( char** command ) {
	int i = 0 ;
	int nCommands = 6 ;
	int globPosition = checkGlob( command ) ;

	if( globPosition == -1 ) return command ;

	glob_t globbuf;

   	globbuf.gl_offs = 0 ;
   	glob( command[globPosition], GLOB_DOOFFS, NULL, &globbuf);

   	int matches = globbuf.gl_pathc ;

   	/* Copy the commands */
   	char **newCommands = malloc( ( nCommands + matches ) * sizeof( char* ) ) ;
   	/* Copy all commands until the wildcard */
   	memcpy( newCommands, command, globPosition * sizeof( char* ) ) ;
   	/* Copy all matches */
   	memcpy( newCommands + globPosition, globbuf.gl_pathv, matches * sizeof( char* ) ) ;
   	/* Copy the leftover commands */
   	memcpy( newCommands + globPosition + matches, command + globPosition + 1, ( nCommands - globPosition - 1 ) * sizeof( char* ) ) ;

   	return newCommands ;
}