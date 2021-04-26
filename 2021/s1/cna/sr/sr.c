#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "sr.h"

/* ******************************************************************
	Selective Repeat Protocol:
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
/* This is to account for when a seqnum or acknum have wrapped back to zero */
/* eg. is 7 between 5-10 returns true */
/* eg. is 7 bewteen 10-5 returns false */
/* eg. is 7 bewteen 10-8 returns true */
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

/* Created a struct for the sender buffer */
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
/* note: there are much faster and more memory efficient solutions than this */
/* but I find this solution makes for more readable code and ease of understanding the soluton */

/* Timer Logic:
  - Whenever a packet is sent and there is no timer, start the timer
  - When the packet associated with the timer is acked, stop the timer
  - When there is a TIMEOUT, resend all packets not yet acked and start the timer
*/

static struct senderBufferUnit senderBuffer[ WINDOWSIZE ] ; /* sender buffer used to know which packets are sent and acked */
static int timerAssociatedSeqNum ;  /* remember the seqnum that the timer was started on */
static bool timerStarted ;          /* remember whether a timer has been started */
static int sendBase ;               /* remember the first seqnum in the buffer */
static int nextSeqNum ;             /* remember the seqnum to use for the next packet to send */

/* Print the senderBuffer array */
/* This is used for debugging */
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

  /* Assign the seqnum using the global nextSeqNum variable */
  packet.seqnum = nextSeqNum ;
  packet.acknum = NOTINUSE ;

  /* increment nextSeqNum, wrapping back to zero if necessary */
  nextSeqNum = ( nextSeqNum + 1 ) % SEQSPACE ;

  /* put the input parameter into our packet */
  for ( i = 0; i < 20 ; i++ )
    packet.payload[ i ] = message.data[ i ] ;
  packet.checksum = ComputeChecksum( packet ) ;

  return packet ;
}

/* return true if the sender window is full */
bool windowFull() {
  int i ;
  int windowCount = 0 ;

  /* Loop over the window */
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    /* Check if there is a sent packet, awaiting ack in the sender buffer */
    if( senderBuffer[i].sent == true ) windowCount++ ;
  }

  /* If every buffer slot in the window is awaiting ack, the window is full */
  if( windowCount == WINDOWSIZE ) return true ;
  else return false ;
}

/* add a packet to the first available space in the buffer */
void addPacketToBuffer( struct pkt newPacket ) {
  /* Calculate the index to put the new packet */
  /* sendBase is the first packets seqnum */
  int index = newPacket.seqnum - sendBase ;

  /* add the packet to the buffer and remember that it has been sent */
  senderBuffer[ index ].sent = true ;
  senderBuffer[ index ].packet = newPacket ;
}

/* Return true if a packet has already been acked */
bool isACKed( int acknum ) {
  /* calculate the index of the input acknum in my senderBuffer */
  int index = acknum - sendBase ;

  /* If the acknum is less than the first seqnum in the buffer */
  /* we must have already received it as the window has moved */
  if( acknum < sendBase ) return true ;

  /* Check if the input packet is acked in our buffer */
  if( senderBuffer[ index ].acked == true ) return true ;
  else return false ;
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
    /* only loop until the second to last element, otherwise we will segfault */
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
  /* loop over the whole buffer */
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    /* If an element is sent, and not acked; it is awaiting an ack */
    if( senderBuffer[i].sent == true && senderBuffer[i].acked == false ) 
      return senderBuffer[i].packet.seqnum ;
  }
  return -1 ;
}



/* Start the sender timer and update the associated state variables */
/* Input parameter is the seqeunce number of the packet starting the timer */
void startTimerHandler( int seqnum ) {
  /* If called with an invalid sequence number spit an error */
  if( seqnum >= 0 ) {
    /* start timer and update global state variables */
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
  /* check if the window is full */
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
      /* pass the seqnum of the new packet */
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
  /* check if the packet is corrupted */
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
      /* if there is a packet awaiting and no timer is running */
      if( nextPacketToBeACKed() != -1 && !timerStarted ) 
        /* start the timer, pass the seqnum of the next packed awaiting ack */
        startTimerHandler( nextPacketToBeACKed() ) ;

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
  int i = 0 ;
  bool sentpacket = false ;
  int firstResentSeqNum = -1 ;

  if (TRACE > 0)
    printf( "----A: time out,resend packets!\n" ) ;

  /* loop until we send a packet, or reach the end of the window */
  while( sentpacket == false && i < WINDOWSIZE ) {
    /* If a packet is waiting to be acked and initialized */
    if( senderBuffer[i].acked == false && senderBuffer[i].packet.seqnum != NOTINUSE ) {
      /* remember the seqnum of the packet we are about to send */
      if( firstResentSeqNum == -1 ) 
        firstResentSeqNum = senderBuffer[i].packet.seqnum ;

      if (TRACE > 0)
        printf ( "---A: resending packet %d\n", senderBuffer[i].packet.seqnum ) ;
      /* Increase counter of resent packets */
      packets_resent++ ;

      /* Resend the packet not acked */
      tolayer3( A, senderBuffer[i].packet ) ;
      /* Make sure the buffer knows this packet has been sent */
      senderBuffer[i].sent = true ;

      sentpacket = true ;
    }
    i++ ;
  }

  /* Restart timer passing the seqnum we remembered in the last loop */
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

  /* Initialize our sender's state variables */
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

static struct receiverBufferUnit receiverBuffer[ WINDOWSIZE ] ; /* receiver buffer of size WINDOWSIZE */
static int receiverSequenceNumber ;   /* remember the sequence number */
static int rcv_base ;                 /* first packet's seqnum in receiver buffer */

/* Create an ACK packet with acknum = input and send it to layer3 */
void sendACK( int packetSeqNum ) {
  int i ;
  struct pkt ack ;

  /* add the sequence number and incrememnt the sequence number counter */
  ack.seqnum = receiverSequenceNumber ;
  receiverSequenceNumber = ( receiverSequenceNumber + 1 ) % SEQSPACE ;

  /* add the acknowledgement number to the new ack */
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
}

/* while the zeroth packet has been received, move the receiver window forward */
void moveBufferWindow() {
  while( receiverBuffer[0].received == true ) {
    int i ;
    /* Cycle the elements of the buffer down one position */
    for( i = 0 ; i < WINDOWSIZE - 1 ; i++ ) {
      receiverBuffer[ i ].packet = receiverBuffer[ i + 1 ].packet ;
      receiverBuffer[ i ].received = receiverBuffer[ i + 1 ].received ;
    }

    /* increment the base seqnum of our receiver buffer */
    rcv_base = ( rcv_base + 1 ) % SEQSPACE ;
    /* the last position in the receiver buffer is now empty */
    receiverBuffer[ WINDOWSIZE - 1 ].received = false ;
  }
}

/* Return true if seqnum is within current window */
bool withinCurrentWindow( int seqnum ) {
  /* need to account for the case where the window has wrapped back to zero */
  /* so call our withinRange function */
  if( withinRange( rcv_base, rcv_base + WINDOWSIZE - 1, seqnum ) ) return true ;
  else return false ;
}

/* called from layer 3, when a packet arrives for layer 4 at B */
void B_input( struct pkt packet )
{
  struct pkt ack ;

  /* If not corrupted */
  if( !IsCorrupted( packet ) ) {

    if (TRACE > 0)
        printf( "----B: packet %d is correctly received, send ACK!\n", packet.seqnum ) ;
    /* Increase counter for correctly received packets at B */
    packets_received++ ;

    /* if this is a new ack */
    if( withinCurrentWindow( packet.seqnum ) ) {
      /* send an ack back */
      sendACK( packet.seqnum ) ;
      /* add the new packet to our receiverBuffer */
      addToBuffer( packet ) ;
      /* move the window if necessary */
      moveBufferWindow() ;
      /* send the new packet to the application layer */
      tolayer5( B, packet.payload ) ;
    } else {
      /* this is a repeated packet, simply resend the ack */
      sendACK( packet.seqnum ) ;
    }
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
