/**  smsh1.c  small-shell version 1
 **		first really useful version after prompting shell
 **		this one parses the command line into strings
 **		uses fork, exec, wait, and ignores signals
 **/

/* smsh2.c, smsh3.c and smsh4.c are identical 
 * differences between the shells are in pipelinePart*.c
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	"smsh.h"

#define	DFL_PROMPT	"> "

int main()
{
	char	*cmdline, *prompt, **arglist, ***commands;
	int	result, n, i ;
	void	setup();

	prompt = DFL_PROMPT ;
	setup();

	while ( (cmdline = next_cmd(prompt, stdin)) != NULL ){
		if ( (arglist = splitline(cmdline)) != NULL ){
			commands = splitPipes( arglist ) ; 	/* split arglist into multiple commands */
			result = pipeline( commands ) ;		/* Execute the commands, pipeling as necessary */
			n = nCommands( commands ) ;
			
			freelist(arglist);
			for( i = 0 ; i < n ; i++ )			/* Free each command in commands */
				freelist( commands[i] ) ;
		}
		free(cmdline);
	}
	return 0;
}

void setup()
/*
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
	signal(SIGINT,  SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr,"Error: %s,%s\n", s1, s2);
	exit(n);
}