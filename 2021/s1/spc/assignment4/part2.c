#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// How nice of me to include a global that tells you how many commands there were :)
int total_commands = 0;


// ####################################################################################
// ## Please write some code in the following two functions

// Create static condition and mutex to share between writer and reader
// Only need a default condition and mutex,
// So can use the inbuilt macros to shorten code 
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER ;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER ;

void * writer(void * in_ptr)
{
	/* store input in a char** for printing */
	char** commands = in_ptr ;
	int i = 0 ; /* line counter */

	while( i < total_commands ) { /* loop over each command */
		pthread_mutex_lock( &lock ) ;

		/* If the reader is still reading, wait */
		if( get_written() == 1 ) {
			pthread_cond_wait( &cond, &lock ) ;
		}

		/* write the current line into the buffer */
		bad_write( commands[i] ) ;
		/* signal reader that we're done */
		pthread_cond_signal( &cond ) ;

		pthread_mutex_unlock( &lock ) ;
		i++ ; /* increment line counter */
	}
}

void * reader(void * empty)
{
	int i = 0 ; /* line counter */
	while( i < total_commands ) { /* loop over each line */
		pthread_mutex_lock( &lock ) ;

		/* If the reader isn't done yet, wait */
		if( get_written() == 0 ) {
			pthread_cond_wait( &cond, &lock ) ;
		}
		/* read the current line */
		bad_read() ;
		/* signal the writer that we're done reading */
		pthread_cond_signal( &cond ) ;

		pthread_mutex_unlock( &lock ) ;
		i++ ; /* increment the line counter */
	}
}


// ################################################################################
// ## DO NOT MODIFY 

int main()
{
	// ## Parse STDIN and read into commands
	char * commands[100];
	char line[256];
    while (fgets(line, 256, stdin))
    {
		commands[total_commands] = (char*)(malloc(strlen(line) * sizeof(char)));
 		strcpy(commands[total_commands], line);
		total_commands = total_commands + 1;
	}

	pthread_t write1;
	pthread_t read1;

	// Creates a thread which executes writer!
	if(pthread_create(&write1, NULL, writer, commands))
	{
		fprintf(stderr, "Error creating write thread\n");
		return 1;
	}

	// Creates a thread which executes reader!
	if(pthread_create(&read1, NULL, reader, NULL))
	{
		fprintf(stderr, "Error creating read thread\n");
		return 1;
	}

	// Ensure Threads Join Well
	if(pthread_join(write1, NULL)) 
	{
		fprintf(stderr, "Error joining write thread\n");
		return 2;
	}

	if(pthread_join(read1, NULL)) 
	{
		fprintf(stderr, "Error joining read thread\n");
		return 2;
	}

	// Did you really call the right functions?
	get_output();

	// I am a responsible memory user!
	int command_i;
	for (command_i = 0; command_i < total_commands; command_i++)
	{
		free(commands[command_i]);
	}
	return 0;

}
// ## DO NOT MODIFY 
// ################################################################################
