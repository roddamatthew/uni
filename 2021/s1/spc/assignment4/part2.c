// #include "slow_functions.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// printf( "%d: %s", i, commands[i] ) ;
		// printf( "Call bad_write with %s", commands[i] ) ;
		// bad_write( commands[i] ) ;
		// printf( "get_written is now: %d\n", get_written() ) ;
		// printf( "call bad_read: " ) ;
		// bad_read() ;
		// printf( "get_written is now: %d\n", get_written() ) ;

// void * writer(void * in_ptr)
// {
// 	char** commands = in_ptr ;

// 	int i = 0 ;

// 	while( i < total_commands ) {
// 		pthread_mutex_lock( &lock ) ;
// 		printf( "W: lock called\n" ) ;

// 		if( get_written() == 1 ) {
// 			printf( "W: waiting\n" ) ;
// 			pthread_cond_wait( &cond, &lock ) ;
// 			printf( "W: finished waiting\n" ) ;
// 		}

// 		bad_write( commands[i] ) ;
// 		printf( "W: bad_write called\n" ) ;
// 		pthread_cond_signal( &cond ) ;
// 		printf( "W: signal called\n" ) ;
// 		pthread_mutex_unlock( &lock ) ;
// 		printf( "W: unlock called\n" ) ;
// 		i++ ;
// 	}
// }

// void * reader(void * empty)
// {
// 	int i = 0 ;
// 	while( i < total_commands ) {
// 		pthread_mutex_lock( &lock ) ;
// 		printf( "R: lock called\n" ) ;
// 		if( get_written() == 0 ) {
// 			printf( "R: waiting\n" ) ;
// 			pthread_cond_wait( &cond, &lock ) ;
// 			printf( "R: finished waiting\n" ) ;
// 		}
// 		bad_read() ;
// 		pthread_cond_signal( &cond ) ;
// 		printf( "R: bad read called\n" ) ;
// 		pthread_mutex_unlock( &lock ) ;
// 		printf( "R: unlock called\n" ) ;
// 		i++ ;
// 	}
// }

// How nice of me to include a global that tells you how many commands there were :)
int total_commands = 0;


// ####################################################################################
// ## Please write some code in the following two functions

static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * writer(void * in_ptr)
{
	char** commands = in_ptr ;

	int i = 0 ;

	while( i < total_commands ) {
		pthread_mutex_lock( &lock ) ;

		if( get_written() == 1 ) {
			pthread_cond_wait( &cond, &lock ) ;
		}

		bad_write( commands[i] ) ;
		pthread_cond_signal( &cond ) ;
		pthread_mutex_unlock( &lock ) ;
		i++ ;
	}
}

void * reader(void * empty)
{
	int i = 0 ;
	while( i < total_commands ) {
		pthread_mutex_lock( &lock ) ;
		if( get_written() == 0 ) {
			pthread_cond_wait( &cond, &lock ) ;
		}
		bad_read() ;
		pthread_cond_signal( &cond ) ;
		pthread_mutex_unlock( &lock ) ;
		i++ ;
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
