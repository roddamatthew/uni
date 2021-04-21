/* The implementation of Selective Repeat should be identical to that described in the textbook 
(Section: Principles of Reliable Data Transfer) */

/* Testing tips
Try with no loss or corruption: the two protocols work the same
Try with just loss: Timeouts will occur
Try with just corruption: Need to use checksum
*/

/* When is the behaviour of GoBackN the same as Selective Repeat
When does the behaviour differ */

/* Compile once its done with:
gcc -Wall -ansi -pedantic -o sr emulator.c sr.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "sr.h"

/* ******************************************************************
	Selective Repeat Protocol:...
**********************************************************************/

#define RTT  15.0               /* round trip time.  MUST BE SET TO 15.0 when submitting assignment */
#define WINDOWSIZE 6            /* Maximum number of buffered unacked packet */
#define SEQSPACE 12             /* min sequence space for SR is 2 * WINDOWSIZE */
#define NOTINUSE (-1)           /* used to fill header fields that are not being used */

/* generic procedure to compute the checksum of a packet.  Used by both sender and receiver  
   the simulator will overwrite part of your packet with 'z's.  It will not overwrite your 
   original checksum.  This procedure must generate a different checksum to the original if
   the packet is corrupted.
*/
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

/********* Sender (A) variables and functions ************/

/* Create a struct for the sender buffer */
/* Sender needs to know when packets:
    - Sequence number
    - Whether they are sent yet
    - Whether they are acknowledged yet
*/

/* Timer Logic:
  - Whenever a packet is sent and there is no timer, start the timer
  - When the packet associated with the timer is acked, stop the timer
  - When there is a TIMEOUT, resend all packets not yet acked and start the timer
*/

/* This struct is a single buffer slot, the final buffer will be an array of these structs */
struct senderBufferUnit {
  struct pkt packet ;
  bool sent ;
  bool acked ;
} ;

static struct senderBufferUnit senderBuffer[ WINDOWSIZE ] ;
static int timerAssociatedSeqNum ;
static bool timerStarted ;
static int sendBase ;
static int nextSeqNum ;

void printSenderBuffer() {
  int i, j ;
  printf( "senderBuffer: \n" ) ;
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    printf( "sent: %s\n", senderBuffer[i].sent ? "true" : "false" ) ;
    printf( "acked: %s\n", senderBuffer[i].acked ? "true" : "false" ) ;
    printf( "packet: seqnum: %d, acknum: %d\n", senderBuffer[i].packet.seqnum, senderBuffer[i].packet.acknum ) ;
    printf( "payload: " ) ;
    for( j = 0 ; j < 20 ; j++ ) {
      printf( "%c", senderBuffer[i].packet.payload[ j ] ) ;
    }
    printf( "\n" ) ;
  }
  printf( "\n" ) ;
}

/* Create a packet, filling in the correct seqnum, and return it */
struct pkt createPacket( struct msg message ) {
  struct pkt packet ;
  int i ;

  packet.seqnum = nextSeqNum ;
  packet.acknum = NOTINUSE ;

  nextSeqNum = ( nextSeqNum + 1 ) % SEQSPACE ;

  for ( i = 0; i < 20 ; i++ )
    packet.payload[ i ] = message.data[ i ] ;
  packet.checksum = ComputeChecksum( packet ) ;

  return packet ;
}

/* return true if the sender window is full */
bool windowFull() {
  int i ;
  int windowCount = 0 ;

  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    if( senderBuffer[i].sent == true ) windowCount++ ;
  }

  if( windowCount == WINDOWSIZE ) return true ;
  else return false ;
}

/* add a packet to the end of the buffer */
void addPacketToBuffer( struct pkt newPacket ) {
  int index = newPacket.seqnum - sendBase ;
  senderBuffer[ index ].sent = true ;
  senderBuffer[ index ].packet = newPacket ;
}

/* Return true if a packet has already been acked */
bool isACKed( int acknum ) {
  int index = acknum - sendBase ;
  if( acknum < sendBase ) return true ;
  if( senderBuffer[ index ].acked == true ) {
    /* printf( "isACKed returned true! new_ACKs = %d acknum = %d\n", new_ACKs, acknum ) ; */
    return true ;
  }
  else {
    /* printf( "isACKed returned false! new_ACKs = %d acknum = %d\n", new_ACKs, acknum ) ; */
    return false ;
  }
}

/* Update buffer to have received ack for given acknum */
void bufferReceiveACK( int acknum ) {
  int index = acknum - sendBase ;
  senderBuffer[ index ].acked = true ;
}

/* move senderBuffer window across as long as the zeroth packet is acked */
void moveSenderWindow() {
  while( senderBuffer[0].acked == true ) {
    int i ;
    /* Cycle the elements of the buffer down one position */
    for( i = 0 ; i < WINDOWSIZE - 1 ; i++ ) {
      senderBuffer[ i ].packet = senderBuffer[ i + 1 ].packet ;
      senderBuffer[ i ].acked = senderBuffer[ i + 1 ].acked ;
      senderBuffer[ i ].sent = senderBuffer[ i + 1 ].sent ;
    }

    /* Increase the base of the sender */
    sendBase = ( sendBase + 1 ) % SEQSPACE ;

    /* empty the last element in the buffer */
    senderBuffer[ WINDOWSIZE - 1 ].acked = false ;
    senderBuffer[ WINDOWSIZE - 1 ].sent = false ;
  }
}

/* Return the seqnum of the next packet in the buffer to be acked */
/* If there is no packets waiting for an ack, return -1 */
int nextPacketToBeACKed() {
  int i ;
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    if( senderBuffer[i].sent == true && senderBuffer[i].acked == false ) return senderBuffer[i].packet.seqnum ;
  }
  return -1 ;
}



/* Start the sender timer and update the associated state variables */
/* Input parameter is the seqeunce number of the packet starting the timer */
void startTimerHandler( int seqnum ) {
  /* If called with an invalid sequence number spit an error */
  if( seqnum >= 0 ) {
    starttimer( A, RTT ) ;
    timerAssociatedSeqNum = seqnum ;
    timerStarted = true ;
  } else {
    printf( "startTimerHandler called with an invalid seqnuence number: %d (note: -1 denotes a seqnum not in use)\n", seqnum ) ;
  }
}

/* Stop the timer and update the associated state variables */
void stopTimerHandler() {
  stoptimer( A ) ;
  timerAssociatedSeqNum = NOTINUSE ;
  timerStarted = false ;
}

/* called from layer 5 (application layer), passed the message to be sent to other side */
void A_output(struct msg message)
{
  if( !windowFull() ) {
    struct pkt packet ;

    if (TRACE > 1)
      printf( "----A: New message arrives, send window is not full, send new messge to layer3!\n" ) ;

    /* Create a packet and sent it to the network layer */
    packet = createPacket( message ) ;
    if (TRACE > 0)
      printf( "Sending packet %d to layer 3\n", packet.seqnum ) ;
    tolayer3( A, packet ) ;

    /* Add the packet to our senderBuffer */
    addPacketToBuffer( packet ) ;

    /* If a timer is not started, start one */
    if( !timerStarted ) {
      startTimerHandler( packet.seqnum ) ;
    }
  } else {
    /* New message arrived at transport layer, but our send window was already full */
    /* Give a useful error message */
    if (TRACE > 0)
      printf("----A: New message arrives, send window is full\n");
    window_full++;
  }
}

/* called from layer 3, when a packet arrives for layer 4 
   In this practical this will always be an ACK as B never sends data.
*/
void A_input( struct pkt packet )
{
  if( !IsCorrupted( packet ) ){
    if (TRACE > 0)
      printf( "----A: uncorrupted ACK %d is received\n", packet.acknum ) ;
    /* increase counter of total ack's received */
    total_ACKs_received++ ;

    /* Check for duplicate ACK */
    if( !isACKed( packet.acknum ) ) {
      if (TRACE > 0)
              printf( "----A: ACK %d is not a duplicate\n", packet.acknum ) ;
      /* Update buffer to have received ACK */
      bufferReceiveACK( packet.acknum ) ;
      new_ACKs++ ;

      /* Stop timer if ack was associated with timer */
      if( timerAssociatedSeqNum == packet.acknum ) stopTimerHandler() ;
      if( nextPacketToBeACKed() != -1 ) startTimerHandler( nextPacketToBeACKed() ) ;

      /* Move window if necessary */
      moveSenderWindow() ;
    } else {
      if (TRACE > 0)
        printf ( "----A: duplicate ACK received, do nothing!\n" ) ;
    }
  } else {
    if (TRACE > 0)
      printf ( "----A: corrupted ACK is received, do nothing!\n" ) ;
  }
}

/* called when A's timer goes off */
void A_timerinterrupt(void)
{
  int i ;
  int firstResentSeqNum = -1 ;

  if (TRACE > 0)
    printf( "----A: time out,resend packets!\n" ) ;

  /* Resend all packets not yet acked */
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    /* Check that the packet is also initialized */
    if( senderBuffer[i].acked == false && senderBuffer[i].packet.seqnum != NOTINUSE ) {
      if( firstResentSeqNum == -1 ) firstResentSeqNum = senderBuffer[i].packet.seqnum ;
      /* Resend the packet not acked */
      tolayer3( A, senderBuffer[i].packet ) ;
      /* Make sure the buffer knows this packet has been sent */
      senderBuffer[i].sent = true ;

      if (TRACE > 0)
        printf ( "---A: resending packet %d\n", senderBuffer[i].packet.seqnum ) ;
      /* Increase counter of resent packets */
      packets_resent++ ;
    }
  }

  /* Restart timer */
  if( firstResentSeqNum != -1 ) startTimerHandler( firstResentSeqNum ) ;
}       



/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init(void)
{
  int i ;
  /* Initialize senderBuffer */
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    senderBuffer[i].packet.seqnum = NOTINUSE ;
    senderBuffer[i].packet.acknum = NOTINUSE ;
    senderBuffer[i].acked = false ;
    senderBuffer[i].sent = false ;
  }

  timerAssociatedSeqNum = NOTINUSE ;
  timerStarted = false ;
  nextSeqNum = 0 ;
  sendBase = 0 ;
}


/********* Receiver (B)  variables and procedures ************/

/* Create a struct for the receiver buffer */
/* The receiver buffer needs to keep track of:
  - sequence number of the received packet
  - whether that packet has been acknowledged
*/
/* The implementation of this struct will be an array of buffer units to create the whole buffer */
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
  /* printf( "receiverBuffer packet added: %d\n", receiverBuffer[index].packet.seqnum ) ; */
}

void moveBufferWindow() {
  while( receiverBuffer[0].received == true ) {
    int i ;
    /* Cycle the elements of the buffer down one position */
    for( i = 0 ; i < WINDOWSIZE - 1 ; i++ ) {
      receiverBuffer[ i ].packet = receiverBuffer[ i + 1 ].packet ;
      receiverBuffer[ i ].received = receiverBuffer[ i + 1 ].received ;
    }

    rcv_base = ( rcv_base + 1 ) % SEQSPACE ;
    receiverBuffer[ WINDOWSIZE - 1 ].received = false ;
  }
}

/* Return true if seqnum is within current window */
bool withinCurrentWindow( int seqnum ) {
  /* printf( "%d, %d, %d ", rcv_base, rcv_base + WINDOWSIZE - 1, seqnum ) ; */
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
      if (TRACE > 0)
        printf( "----B: packet %d is correctly received, send ACK!\n", packet.seqnum ) ;
      /* Increase counter for correctly received packets at B */
      packets_received++ ;
      /* printf( "Packet is within current window\n" ) ; */
      sendACK( packet.seqnum ) ;
      addToBuffer( packet ) ;
      moveBufferWindow() ;
      tolayer5( B, packet.payload ) ;
    } else {
      if (TRACE > 0) 
        printf("----B: packet not expected sequence number, resend ACK!\n");
      /* printf( "Packet is repeated\n" ) ; */
      sendACK( packet.seqnum ) ;
    }
  } else {
    if( TRACE > 0 )
      printf( "packet corrupted, do nothing\n" ) ;
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

/******************************************************************************
 * The following functions need be completed only for bi-directional messages *
 *****************************************************************************/

/* Note that with simplex transfer from a-to-B, there is no B_output() */
void B_output(struct msg message)  
{
}

/* called when B's timer goes off */
void B_timerinterrupt(void)
{
}
