#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RTT  15.0       	/* round trip time.  MUST BE SET TO 15.0 when submitting assignment */
#define WINDOWSIZE 6    	/* Maximum number of buffered unacked packet */
#define SEQSPACE 7      	/* min sequence space for GBN must be at least windowsize + 1 */
#define NOTINUSE (-1)   	/* used to fill header fields that are not being used */

static int currentTime = 0 ;

/* Multiple timers:
call starttimer(A, RTT) initially
	Which packet should I time:
	Time the last packet in the window

	When to stop?
	Stop the timer when the entire window has been received

	When to restart?
	Restart the timer when a timeout occurs:
	Check each packet in the buffer
	If they are not all received then restart timer.

*/

struct receiverBufferUnit {
	int bufferIndex ;
	int seqnum ;
	bool received ;
} ;

struct senderBufferUnit {
	int bufferIndex ;
	int seqnum ;
	bool sent ;
	bool acked ;
} ;

void initializeReceiverBuffer( struct receiverBufferUnit array[] ) {
	for( int i = 0 ; i < WINDOWSIZE ; i++ ) {
		array[i].received = false ;
		array[i].bufferIndex = i ;
		array[i].seqnum = i ;
	}
}

void printReceiverBuffer( struct receiverBufferUnit array[] ) {
	printf( "Remember 0 = false, 1 = true \n" ) ;
	for( int i = 0 ; i < WINDOWSIZE ; i++ ) {
		printf("Buffer slot %d : seqnum %d: %d\n", array[i].bufferIndex, array[i].seqnum, array[i].received ) ;
	}
	printf( "\n" ) ;
}

/* Called when the first packet of the window is received
This indicates that the window must move forward once
bufferIndex does not change
received moves down one index
seqnum increases by one
*/
void moveReceiverWindow( struct receiverBufferUnit array[] ) {
	int currentStart = array[0].seqnum + 1 ;

	for( int i = 0 ; i < WINDOWSIZE ; i++ ) {
		array[i].seqnum = currentStart + i ;
		if( i < WINDOWSIZE - 1 ) array[i].received = array[i+1].received ;
		else array[i].received = false ;
	}
}

void initializeSenderBuffer( struct senderBufferUnit array[] ) {
	for( int i = 0 ; i < WINDOWSIZE ; i++ ) {
		array[i].bufferIndex = i ;
		array[i].seqnum = i ;
		array[i].acked = false ;
		array[i].sent = false ;
	}
}

void printSenderBuffer( struct senderBufferUnit array[] ) {
	printf( "Remember 0 = false, 1 = true \n" ) ;

	for( int i = 0 ; i < WINDOWSIZE ; i++ ) {
		printf( "Buffer Slot %d:", array[i].bufferIndex ) ;
		printf( " with seqnum: %d", array[i].seqnum ) ;
		printf( " sent? %d", array[i].sent ) ;
		printf( " acked? %d", array[i].acked ) ;
	}

	printf( "\n" ) ;
}

void sendPacket( struct senderBufferUnit array[], int index ) {
	array[index].sent = true ;
}

void moveSenderWindow( struct senderBufferUnit array[] ) {

}

void receivedACK( struct senderBufferUnit array[], int index ) {
	array[index].acked = true ;
	while( array[0].acked == true ) {
		moveSenderWindow( array ) ;
	}
}

int main() {
	/* Receiver Buffer */
	struct receiverBufferUnit receiverBuffer[ WINDOWSIZE ] ;

	initializeReceiverBuffer( receiverBuffer ) ;
	printReceiverBuffer( receiverBuffer ) ;

	printf( "Simulate receiving packets with bufferIndex; 0, 1, 2, 4, 5 \n" ) ;
	receiverBuffer[0].received = true ;
	receiverBuffer[1].received = true ;
	receiverBuffer[2].received = true ;
	receiverBuffer[4].received = true ;
	receiverBuffer[5].received = true ;

	/* If the first buffer slot has been received, we must move the window */
	while( receiverBuffer[0].received == true ) {
		moveReceiverWindow( receiverBuffer ) ;
	}

	printReceiverBuffer( receiverBuffer ) ;

	printf( "Simulate receiving packets with bufferIndex; 4, 5 \n" ) ;
	receiverBuffer[4].received = true ;
	receiverBuffer[5].received = true ;

	/* If the first buffer slot has been received, we must move the window */
	while( receiverBuffer[0].received == true ) {
		moveReceiverWindow( receiverBuffer ) ;
	}

	printReceiverBuffer( receiverBuffer ) ;

	printf( "Simulate receiving packets with bufferIndex; 0 \n" ) ;
	receiverBuffer[0].received = true ;

	/* If the first buffer slot has been received, we must move the window */
	while( receiverBuffer[0].received == true ) {
		moveReceiverWindow( receiverBuffer ) ;
	}

	printReceiverBuffer( receiverBuffer ) ;

	return 0 ;
}