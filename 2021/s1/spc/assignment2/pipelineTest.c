#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
	int i = 0 ;
	char* commands[3][2] ;

	commands[0][0] = "ls" ;
	commands[0][1] = NULL ;

	commands[1][0] = "wc" ;
	commands[1][1] = NULL ;

	commands[2][0] = "wc" ;
	commands[2][1] = NULL ;

	/* want to create 2 pipes */
	/* 3 Commands:
	fork:
		- child process has a function
			- writes output to a current_pipe
	return to parent
		- move current_pipe data to last_pipe
		- create new current_pipe
	fork
		- child process has a function
			- reads input to function from last calls pipe
			- executes function
			- writes output to current_pipe
	return to parent
		- move current_pipe data to last_pipe
		- create new current_pipe
	fork
		- child process has a function
			- reads input to function from last calls pipe
			- executes functions
			- writes output to current_pipe
	return to parent
		- out of functions so write current_pipe output to stdout
	*/

	// 0 : read end of pipe
	// 1 : write end of pipe
	// input -> 	1 -> 0 		-> output

	int my_pid ;
	int prev_pipe[2] ;
	int new_pipe[2] ;

	pipe( prev_pipe ) ;

	int nCommands = 3 ;

	while( i < nCommands ) {
		// printf( "i = %d\n", i ) ;
		if( i != nCommands - 1 ) {
			// printf( "Created a new pipe\n" ) ;
			pipe( new_pipe ) ;
		}

		my_pid = fork() ;

			// Fork Fail
		if ( my_pid < 0 ) {
			// printf("Failed Fork\n");
		}
		else if ( my_pid == 0 ) // fork child
		{
			// printf( "\nchild: \n" ) ;
			close( prev_pipe[1] ) ;
			close( new_pipe[0] ) ;

			if( i != 0 ) {
				// printf( "Set prev_pipe[0] to stdin\n" ) ;
				dup2( prev_pipe[0], 0 ) ;
			}
			close( prev_pipe[0] ) ;

			if( i != nCommands - 1 ) {
				// printf( "Set new_pipe[1] to stdout\n" ) ;
				dup2( new_pipe[1], 1 ) ;
			}
			close( new_pipe[1] ) ;

			// printf( "Call the command: %s\n", commands[i][0] ) ;

			execvp( commands[i][0], commands[i] ) ;
		}
		else if ( my_pid > 0 )  // Fork Parent
		{
			// printf( "\nparent: \n" ) ;
			if( i != nCommands - 1 ) {
				// printf( "Trying to copy output: \n" ) ;
				char buffer[100] ;
				read( new_pipe[0], buffer, 100 ) ;
				close( new_pipe[0] ) ;
				write( prev_pipe[1], buffer, 100 ) ;
				close( prev_pipe[1] ) ;
				// printf( "Wrote output of new_pipe[0] to input of prev_pipe[1]\n" ) ;
			}

			if( i != 0 ) {
				close( prev_pipe[0] ) ;
				close( prev_pipe[1] ) ;
			}
			if( i > nCommands - 1 ) {
				close( new_pipe[0] ) ;
				close( new_pipe[0] ) ;
			}
			wait( NULL ) ;
		}
		i++ ;
	}
}