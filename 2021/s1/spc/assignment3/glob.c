#include 	<glob.h>
#include 	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include 	<string.h>

int checkGlob( char** arglist )
/*
 * Check for globbing operators in the current command
 * If found, return the index
 * If never found, return -1
 */
{
	int i = 0 ;

	while( arglist[i] != NULL ) {
		if( strchr( arglist[i], '*' ) != NULL ) return i ;
		if( strchr( arglist[i], '?' ) != NULL ) return i ;
		if( strchr( arglist[i], '[' ) != NULL ) return i ;
		i++ ;
	}

	return -1 ;
}

int nArgs( char** arglist )
/* Count the number of arguments in a command
 * Used for allocating the correct amount of memory in globCommand()
 */
{
	int i = 0 ;
	while( arglist[i] != NULL ) {
		i++ ;
	}
	return i ;
}

char** globCommand( char** command )
/* Expand globbing rule into matching files
 * Call glob() then replace entries in the commands array with the matches
 * Dynamically reallocte memory for the new commands array, then return it
 */
{
	int globPosition = checkGlob( command ) ; /* find the index of the globbing rule */

	/* If there is no globbing rule dont waste time allocating memory */
	if( globPosition == -1 ) return command ;

	int i = 0 ;
	int n = nArgs( command ) ; /* number of arguments in command */

	glob_t globbuf; /* initialize glob buffer */

   	globbuf.gl_offs = 0 ; /* not adding to the buffer, so 0 offset */
   	/* command[globPosition] is the parameter with the globbing rule */
   	glob( command[globPosition], GLOB_DOOFFS, NULL, &globbuf);

   	int matches = globbuf.gl_pathc ; /* store the number of matched files */

   	/* Create a new command array that has the original parameters
   	 * but the matches replace the globbing rule,
   	 * remembering to account for the globbing rule not being the last parameter
   	 */

   	/* Allocate memory for the new commands array */
   	char **newCommands = malloc( ( n + matches ) * sizeof( char* ) ) ;

   	/* memcpy parameters: memcpy( destination, source, memory_size )
   	 * destination: start address to copy to
   	 * source: start address to copy from
   	 * memory_size: amount of memory to copy
   	 */

   	/* Copy all commands until the globbing rule */
   	memcpy( newCommands, command, globPosition * sizeof( char* ) ) ;

   	/* Copy all matches, after the original commands */
   	memcpy( newCommands + globPosition, globbuf.gl_pathv, matches * sizeof( char* ) ) ;

   	/* Copy the leftover commands, skipping the globbing rule */
   	memcpy( newCommands + globPosition + matches, command + globPosition + 1, ( n - globPosition - 1 ) * sizeof( char* ) ) ;

   	return newCommands ;
}