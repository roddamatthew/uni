/* splitline.c - commmand reading and parsing functions for smsh
 *    
 *    char *next_cmd(char *prompt, FILE *fp) - get next command
 *    char **splitline(char *str);           - parse a string

 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"smsh.h"

char * next_cmd(char *prompt, FILE *fp)
/*
 * purpose: read next command line from fp
 * returns: dynamically allocated string holding command line
 *  errors: NULL at EOF (not really an error)
 *          calls fatal from emalloc()
 *   notes: allocates space in BUFSIZ chunks.  
 */
{
	char	*buf ; 				/* the buffer		*/
	int	bufspace = 0;			/* total size		*/
	int	pos = 0;			/* current position	*/
	int	c;				/* input char		*/

	printf("%s", prompt);				/* prompt user	*/
	while( ( c = getc(fp)) != EOF ) {

		/* need space? */
		if( pos+1 >= bufspace ){		/* 1 for \0	*/
			if ( bufspace == 0 )		/* y: 1st time	*/
				buf = emalloc(BUFSIZ);
			else				/* or expand	*/
				buf = erealloc(buf,bufspace+BUFSIZ);
			bufspace += BUFSIZ;		/* update size	*/
		}

		/* end of command? */
		if ( c == '\n' )
			break;

		/* no, add to buffer */
		buf[pos++] = c;
	}
	if ( c == EOF && pos == 0 )		/* EOF and no input	*/
		return NULL;			/* say so		*/
	buf[pos] = '\0';
	return buf;
}

/**
 **	splitline ( parse a line into an array of strings )
 **/
#define	is_delim(x) ((x)==' '||(x)=='\t')

char ** splitline(char *line)
/*
 * purpose: split a line into array of white-space separated tokens
 * returns: a NULL-terminated array of pointers to copies of the tokens
 *          or NULL if line if no tokens on the line
 *  action: traverse the array, locate strings, make copies
 *    note: strtok() could work, but we may want to add quotes later
 */
{
	char	*newstr();
	char	**args ;
	int	spots = 0;			/* spots in table	*/
	int	bufspace = 0;			/* bytes in table	*/
	int	argnum = 0;			/* slots used		*/
	char	*cp = line;			/* pos in string	*/
	char	*start;
	int	len;

	if ( line == NULL )			/* handle special case	*/
		return NULL;

	args     = emalloc(BUFSIZ);		/* initialize array	*/
	bufspace = BUFSIZ;
	spots    = BUFSIZ/sizeof(char *);

	while( *cp != '\0' )
	{
		while ( is_delim(*cp) )		/* skip leading spaces	*/
			cp++;
		if ( *cp == '\0' )		/* quit at end-o-string	*/
			break;

		/* make sure the array has room (+1 for NULL) */
		if ( argnum+1 >= spots ){
			args = erealloc(args,bufspace+BUFSIZ);
			bufspace += BUFSIZ;
			spots += (BUFSIZ/sizeof(char *));
		}

		/* mark start, then find end of word */
		start = cp;
		len   = 1;
		while (*++cp != '\0' && !(is_delim(*cp)) )
			len++;
		args[argnum++] = newstr(start, len);
	}
	args[argnum] = NULL;
	return args;
}

void printCommands( char*** commands )
/* print commands array for debugging */
{
	int i = 0 ;
	int j ;

	while( commands[i] != NULL ) {
		j = 0 ;
		printf( "Command %d:\n", i ) ;
		while( commands[i][j] != NULL ){
			printf( "Arg %d: %s\n", j, commands[i][j] ) ;
			j++ ;
		}
		printf( "\n" ) ;
		i++ ;
	}
}

char ***splitPipes( char** args )
/* purpose: split a command into many commands if there are pipes
 *	action: loop over the command adding each argument to a buffer,
 * 			when a "|" is found, add the buffer to the new commands array
 * returns: 2D string array where each row is NULL terminating and the final row is only NULL
 */
{
	char	*newstr() ;			/* silence in-line declaration warning */
	char	**newstrArray() ;	/* silence in-line declaration warning */
	char ***commands, **buffer ; /* array to store commands and current command */
	int i = 0, j = 0, l = 0 ;	/* counters */
	/* i: position in the input array */
	/* j: row number of the commands array */
	/* l: length of current command being read */

	while( args[i] != NULL ) {
		if( !strcmp( args[i], "|" ) ) {
			commands[j] = newstrArray( buffer, l ) ; /* add current line to commands */
			j++ ;
			l = 0 ;
		} else {
			buffer[l] = newstr( args[i], strlen( args[i] ) ) ; /* add argument to current line */
			l++ ;
		}
		i++ ;
	}

	commands[j] = newstrArray( buffer, l ) ; /* remember to add the last command */
	commands[j+1] = NULL ; /* NULL terminate */

	return commands ;
}

/*
 * purpose: constructor for strings
 * returns: a string, never NULL
 */
char *newstr(char *s, int l)
{
	char *rv = emalloc(l+1);

	rv[l] = '\0';
	strncpy(rv, s, l);
	return rv;
}

/*
 * purpose: constructor for string array
 * returns: NULL terminated string array, will always return at least NULL
 */
char **newstrArray( char**sArray, int l ) {
	int i ;
	/* Allocate memory for new array and a NULL character on the end */
	char **array = emalloc( ( l + 1 ) * sizeof( char* ) ) ;

	/* Add each string to the array */
	for( i = 0 ; i < l ; i++ )
		array[i] = newstr( sArray[i], strlen( sArray[i] ) ) ;
	array[l] = NULL ;

	return array ;
}

void 
freelist(char **list)
/*
 * purpose: free the list returned by splitline
 * returns: nothing
 *  action: free all strings in list and then free the list
 */
{
	char	**cp = list;
	while( *cp )
		free(*cp++);
	free(list);
}

void * emalloc(size_t n)
{
	void *rv ;
	if ( (rv = malloc(n)) == NULL )
		fatal("out of memory","",1);
	return rv;
}
void * erealloc(void *p, size_t n)
{
	void *rv;
	if ( (rv = realloc(p,n)) == NULL )
		fatal("realloc() failed","",1);
	return rv;
}
