#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RTT  15.0       	/* round trip time.  MUST BE SET TO 15.0 when submitting assignment */
#define WINDOWSIZE 6    	/* Maximum number of buffered unacked packet */
#define SEQSPACE 7      	/* min sequence space for GBN must be at least windowsize + 1 */
#define NOTINUSE (-1)   	/* used to fill header fields that are not being used */
#define B 1

/* Return bool based on whether a value is between a min and max */
/* Works for ranges that wrap back from a max to zero */
/* eg. is 7 between 5-10 returns true */
/* eg. is 7 bewteen 10-5 returns false */
/* eg. is 7 bewteen 10-8 returns false */
bool withinRange( int lower, int upper, int val ) {
  if ( lower < upper ) {
    if ( val <= upper && val >= lower ) return true ;
    else return false ;
  } else {
    if ( val >= lower ) return true ;
    else if ( val <= upper ) return true ;
    else return false ;
  }
}

struct pkt {
  int seqnum;
  int acknum;
  int checksum;
  char payload[20];
};

void tolayer3( int i, struct pkt packet ) {
	printf( "sent a packet to layer 3: seqnum: %d acknum: %d\n", packet.seqnum, packet.acknum ) ;
}

int ComputeChecksum(struct pkt packet)
{
  int checksum = 0;
  int i;

  checksum = packet.seqnum;
  checksum += packet.acknum;
  for ( i=0; i<20; i++ ) 
    checksum += (int)(packet.payload[i]);

  return checksum;
}

bool IsCorrupted(struct pkt packet)
{
  if (packet.checksum == ComputeChecksum(packet))
    return (false);
  else
    return (true);
}

/* ---------------------------------------------------------------------------------------------- */

struct receiverBufferUnit {
  struct pkt packet ;
  bool received ;
} ;

static struct receiverBufferUnit receiverBuffer[ WINDOWSIZE ] ;
static int receiverSequenceNumber ;
static int rcv_base ;

/* Create an ACK packet with acknum = input and send it to layer3 */
void sendACK( int packetSeqNum ) {
  int i ;
  struct pkt ack ;

  ack.seqnum = receiverSequenceNumber ;
  receiverSequenceNumber = ( receiverSequenceNumber + 1 ) % SEQSPACE ;

  ack.acknum = packetSeqNum ;
  /* we don't have any data to send.  fill payload with 0's */
  for ( i = 0 ; i < 20 ; i++ ){
    ack.payload[i] = '0' ;  
  }
  ack.checksum = ComputeChecksum( ack ) ;

  /* send out packet */
  tolayer3 ( B, ack ) ;
}

/* Add a packet to the receiverBuffer */
void addToBuffer( struct pkt packet ) {
  int index = packet.seqnum - rcv_base ;
  receiverBuffer[ index ].packet = packet ;
  receiverBuffer[ index ].received = true ;
  printf( "receiverBuffer packet added: %d\n", receiverBuffer[index].packet.seqnum ) ;
}

void moveBufferWindow() {
  while( receiverBuffer[0].received == true ) {
    int i ;
    /* Cycle the elements of the buffer down one position */
    for( i = 0 ; i < WINDOWSIZE - 1 ; i++ ) {
      receiverBuffer[ i ].packet = receiverBuffer[ i + 1 ].packet ;
      receiverBuffer[ i ].received = receiverBuffer[ i + 1 ].received ;
    }

    rcv_base++ ;
    receiverBuffer[ WINDOWSIZE - 1 ].received = false ;
  }
}

/* Return true if seqnum is within current window */
bool withinCurrentWindow( int seqnum ) {
	printf( "%d, %d, %d", rcv_base, rcv_base + WINDOWSIZE - 1, seqnum ) ;
  if( withinRange( rcv_base, rcv_base + WINDOWSIZE - 1, seqnum ) ) {
    return true ;
  } 
  else return false ;
}

/* called from layer 3, when a packet arrives for layer 4 at B */
void B_input( struct pkt packet )
{
  struct pkt ack ;

  /* If not corrupted */
  if( !IsCorrupted( packet ) ) {
    if( withinCurrentWindow( packet.seqnum ) ) {
      printf( "Packet is within current window\n" ) ;
      sendACK( packet.seqnum ) ;
      addToBuffer( packet ) ;
      moveBufferWindow() ;
    } else {
      printf( "Packet is repeated\n" ) ;
      sendACK( packet.seqnum ) ;
    }
  } else {
  	printf( "Corrupted Packet: Do Nothing!\n" ) ;
  }
}

/* the following routine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init(void)
{
  int i ;
  receiverSequenceNumber = 0 ;
  rcv_base = 0 ;

  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    receiverBuffer[i].received = false ;
  }
}

void printReceiverBuffer() {
	int i ;
	printf( "receiverBuffer: \n" ) ;
	for( i = 0 ; i < WINDOWSIZE ; i++ ) {
		printf( "received: %s\n", receiverBuffer[i].received ? "true" : "false" ) ;
		printf( "packet: seqnum: %d, acknum: %d\n", receiverBuffer[i].packet.seqnum, receiverBuffer[i].packet.acknum ) ;
	}
	printf( "\n" ) ;
}


int main() {
	/* Create a packet to send to B */
	struct pkt packet1 ;
	int i ;
	packet1.seqnum = 2 ;
	packet1.acknum = NOTINUSE ;
	/* we don't have any data to send.  fill payload with 0's */
  	for ( i = 0 ; i < 20 ; i++ ){
    	packet1.payload[i] = '0' ;  
  	}
	packet1.checksum = ComputeChecksum( packet1 ) ;

		/* Create a packet to send to B */
	struct pkt packet2 ;
	packet2.seqnum = 0 ;
	packet2.acknum = NOTINUSE ;
	/* we don't have any data to send.  fill payload with 0's */
  	for ( i = 0 ; i < 20 ; i++ ){
    	packet2.payload[i] = '0' ;  
  	}
	packet2.checksum = ComputeChecksum( packet2 ) ;

	/* Create a packet to send to B */
	struct pkt packet3 ;
	packet3.seqnum = 1 ;
	packet3.acknum = NOTINUSE ;
	/* we don't have any data to send.  fill payload with 0's */
  	for ( i = 0 ; i < 20 ; i++ ){
    	packet3.payload[i] = '0' ;  
  	}
	packet3.checksum = ComputeChecksum( packet3 ) ;

	B_init() ;
	B_input( packet1 ) ;
	printReceiverBuffer() ;

	B_input( packet2 ) ;
	printReceiverBuffer() ;

	B_input( packet3 ) ;
	printReceiverBuffer() ;

	

	return 0 ;
}