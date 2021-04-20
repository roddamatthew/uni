/* The implementation of Selective Repeat should be identical to that described in the textbook 
(Section: Principles of Reliable Data Transfer) */

/* Testing tips
Try with no loss or corruption: the two protocols work the same
Try with just loss: Timeouts will occur
Try with just corruption: Need to use checksum
*/

/* When is the behaviour of GoBackN the same as Selective Repeat
When does the behaviour differ */

/* Copy gbn.c to sr.c and gbn.h to sr.h 
Change what is necessary */

/* Compile once its done with:
gcc -Wall -ansi -pedantic -o sr emulator.c sr.c
*/

/* ------------------------------------------ RESEARCH ------------------------------------------ */

/* Similarities between GBN and SR:
- Both are called sliding window protocols:
	- Have a window of packets that are focused on being sent
	- Size of frame is the size of the largest sequence number
	- Window moves whenever the first sequence number is received
*/

/* Differences between GBN and SR:
- Only lost packets are retransmitted
	- Correctly received packets are buffered
	- GBN retransmits all packets in the current window if there is a loss

- Receiver needs to keep track of current sequence number **
- Sender needs to havea timer for each packet sent **
	- Timer stops when an ACK is received for that seqnum
	- If timer runs out, resend that packet
- Sender window cannot move until all packets are correctly ACKed
*/

/* Plan:
- Need to make a timer function to call for each packet
- Need to make a struct for receiver that keeps of received packets, can use the BUFFER struct already defined
*/

/* Sender:
SEND PACKET:
  - Send a packet, this needs to have a seqnum
  - Start a timer
  - Wait

TIMEOUT:
  - Resend the packet that timed out
  - Restart timer
  - Wait

RECEIVE ACK:
  - Set the corresponding buffer position to true
  - If it was in the first position:
    - while( buffer[0].received == true ) moveWindow( buffer ) ;
*/

/* Receiver:
ONLY ACTS IN RESPONSE TO RECEIVING A PACKET:
  - Receive packet:
    - Check that seqnum >= buffer[0].seqnum:
      - If not send: send an ack for that packet
      - If yes: Continue
  - Receive packet in the first position of the window:
    - buffer[0].received = true ;
    - Send ACK back to sender
    - while( buffer[0].received == true ) moveWindow( buffer ) ;

  - Receive packet in position other than the first:
    - Buffer[i].received = true ;
    - Send ACK back to sender
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
/* This struct is a single buffer slot, the final buffer will be an array of these structs */
struct senderBufferUnit {
  struct pkt packet ;
  bool sent ;
  bool acked ;
} ;

/* called from layer 5 (application layer), passed the message to be sent to other side */
void A_output(struct msg message)
{

}


/* called from layer 3, when a packet arrives for layer 4 
   In this practical this will always be an ACK as B never sends data.
*/
void A_input( struct pkt packet )
{

}

/* called when A's timer goes off */
void A_timerinterrupt(void)
{

}       



/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init(void)
{

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

static int receiverBufferUnit receiverBuffer[ WINDOWSIZE ] ;
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
