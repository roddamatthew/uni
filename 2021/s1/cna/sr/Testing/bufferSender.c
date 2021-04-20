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
#define A 0

/* generic procedure to compute the checksum of a packet.  Used by both sender and receiver  
   the simulator will overwrite part of your packet with 'z's.  It will not overwrite your 
   original checksum.  This procedure must generate a different checksum to the original if
   the packet is corrupted.
*/

struct msg {
  char data[20];
};

struct pkt {
  int seqnum;
  int acknum;
  int checksum;
  char payload[20];
};

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

/* Create a packet, filling in the correct seqnum, and return it */
struct pkt createPacket( struct msg message ) {
  struct pkt packet ;
  return packet ;
}

/* add a packet to the end of the buffer */
void addPacketToBuffer( struct pkt packet ) {
  /* if sender window is full, return an error */
}

/* Fake starttimer function so code compiles */
void starttimer( int A, int RTT ) {

}

/* Fake stoptimer function so code compiles */
void stoptimer( int A ){

}

/* Update buffer to have received ack for given acknum */
void bufferReceiveACK( int acknum ) {

}

/* move senderBuffer window across as long as the zeroth packet is acked */
void moveSenderWindow() {

}

/* called from layer 5 (application layer), passed the message to be sent to other side */
void A_output(struct msg message)
{
  struct pkt packet ;
  packet = createPacket( message ) ;
  addPacketToBuffer( packet ) ;
  if( !timerStarted() ) starttimer( A, RTT ) ;
}


/* called from layer 3, when a packet arrives for layer 4 
   In this practical this will always be an ACK as B never sends data.
*/
void A_input( struct pkt packet )
{
  /* Update buffer to have received ACK */
  bufferReceiveACK( packet.acknum ) ;
  /* Stop timer if ack was associated with timer */
  if( timerAssociatedSeqNum == packet.acknum ) stoptimer( A ) ;
  /* Move window if necessary */
  moveSenderWindow() ;
}

/* called when A's timer goes off */
void A_timerinterrupt(void)
{
  /* Resend all packets not yet acked */
  for()... {}
  /* Restart timer */
  starttimer( A, RTT ) ;
}       



/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init(void)
{
  /* Initialize senderBuffer */
  for() ... ;
  timerAssociatedSeqNum = NOTINUSE ;
  timerStarted = false ;
}

int main() {
  return 0 ;
}