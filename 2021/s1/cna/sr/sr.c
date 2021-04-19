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

static struct senderBufferUnit senderBuffer[ WINDOWSIZE ] ; /* This is the sender buffer */
static int windowfirst, windowlast;    /* array indexes of the first/last packet awaiting ACK */
static int windowcount;                /* the number of packets currently awaiting an ACK */
static int A_nextseqnum;               /* the next sequence number to be used by the sender */

/* called from layer 5 (application layer), passed the message to be sent to other side */
void A_output(struct msg message)
{
  struct pkt sendpkt;
  int i;

  /* if not blocked waiting on ACK */
  if ( windowcount < WINDOWSIZE) {
    if ( TRACE > 1 )
      printf( "----A: New message arrives, send window is not full, send new messge to layer3!\n" ) ;

    /* create packet */
    sendpkt.seqnum = A_nextseqnum;
    sendpkt.acknum = NOTINUSE;
    for ( i = 0; i < 20 ; i++ ) 
      sendpkt.payload[ i ] = message.data[ i ] ;
    sendpkt.checksum = ComputeChecksum( sendpkt ) ; 

    /* increment our windowlast index and wrap it back to zero */
    windowlast = ( windowlast + 1 ) % WINDOWSIZE ;
    /* put packet into our senderBuffer */
    senderBuffer[ windowlast ].packet = sendpkt ;
    windowcount++ ;

    /* send out packet */
    if ( TRACE > 0 )
      printf("Sending packet %d to layer 3\n", sendpkt.seqnum);
    tolayer3 ( A, sendpkt ) ;

    /* Start timer if this is the last packet in the window */
    if ( windowcount == WINDOWSIZE )
      starttimer( A, RTT ) ;

    /* get next sequence number, wrap back to 0 */
    A_nextseqnum = (A_nextseqnum + 1) % SEQSPACE;
    printf( "NEXT SEQUENCE NUMBER TO BE USED IS: %d\n", A_nextseqnum ) ;
  }
  /* if blocked,  window is full */
  else {
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
  int ackcount = 0 ;
  int i ;

  printf( "\nA_input called with packet.acknum = %d", packet.acknum ) ;
  printf( " packet.seqnum = %d\n", packet.seqnum ) ;

  /* if received ACK is not corrupted */ 
  if ( !IsCorrupted( packet ) ) {
    if ( TRACE > 0 )
      printf( "----A: uncorrupted ACK %d is received\n", packet.acknum ) ;
    total_ACKs_received++ ;

    /* check if new ACK or duplicate */
    if ( windowcount != 0 ) {
          int seqfirst = senderBuffer[ windowfirst ].packet.seqnum ;
          int seqlast = senderBuffer[ windowlast ].packet.seqnum ;

          /* check case when seqnum has and hasn't wrapped */
          if (((seqfirst <= seqlast) && (packet.acknum >= seqfirst && packet.acknum <= seqlast)) ||
              ((seqfirst > seqlast) && (packet.acknum >= seqfirst || packet.acknum <= seqlast))) {

            /* packet is a new ACK */
            if ( TRACE > 0 )
              printf("----A: ACK %d is not a duplicate\n",packet.acknum);
            new_ACKs++ ;

            /* Update our buffer to acknowledge the received packet */
            for( i = 0 ; i < WINDOWSIZE ; i++ ) {
              if( packet.acknum == senderBuffer[i].packet.seqnum ) {
                senderBuffer[i].acked = true ;
                printf( "RECEIVED ACK FOR A PACKET IN SENDERBUFFER[%d]\n", packet.acknum ) ;
              }
            }

            /* cumulative acknowledgement - determine how many packets are ACKed */
            if (packet.acknum >= seqfirst)
              ackcount = packet.acknum + 1 - seqfirst;
            else
              ackcount = SEQSPACE - seqfirst + packet.acknum;

	    /* slide window by the number of packets ACKed */
            windowfirst = (windowfirst + ackcount) % WINDOWSIZE;

            /* delete the acked packets from window buffer */
            for (i=0; i<ackcount; i++)
              windowcount--;
          }
        }
        else
          if (TRACE > 0)
        printf ("----A: duplicate ACK received, do nothing!\n");
  }
  else 
    if (TRACE > 0)
      printf ("----A: corrupted ACK is received, do nothing!\n");
}

/* called when A's timer goes off */
void A_timerinterrupt(void)
{
  int i;

  if (TRACE > 0)
    printf("----A: time out,resend packets!\n");

  for( i = 0 ; i < windowcount ; i++ ) {

    if (TRACE > 0)
      printf ("---A: resending packet %d\n", ( senderBuffer[(windowfirst+i) % WINDOWSIZE]).packet.seqnum);

    tolayer3( A, senderBuffer[ ( windowfirst + i ) % WINDOWSIZE ].packet ) ;
    packets_resent++ ;
    if ( i == 0 ) starttimer( A, RTT ) ;
  }
}       



/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init(void)
{
  int i ;
  /* initialise A's window, buffer and sequence number */
  A_nextseqnum = 0;  /* A starts with seq num 0, do not change this */
  windowfirst = 0;
  windowlast = -1;   /* windowlast is where the last packet sent is stored.  
		     new packets are placed in winlast + 1 
		     so initially this is set to -1
		   */
  windowcount = 0;

  /* Initialize the sender buffer */
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    senderBuffer[i].sent = false ;
    senderBuffer[i].acked = false ;
    senderBuffer[i].packet.seqnum = i ;
  }
}



/********* Receiver (B)  variables and procedures ************/

/* Create a struct for the receiver buffer */
/* The receiver buffer needs to keep track of:
  - sequence number of the received packet
  - whether that packet has been acknowledged
*/
/* The implementation of this struct will be an array of buffer units to create the whole buffer */
struct receiverBufferUnit {
  int seqnum ;
  bool received ;
} ;

static struct receiverBufferUnit receiverBuffer[ WINDOWSIZE ] ; /* Receiver buffer with windowsize equal to the sender */
static int B_nextseqnum;   /* the sequence number for the next packets sent by B */


/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet)
{
  struct pkt sendpkt;
  int i;

  printf( "PACKET ARRIVED AT RECEIVER WITH SEQNUM: %d\n", packet.seqnum ) ;
  printf( "EXPECTING PACKETS WITH SEQNUM: " ) ;
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    if( receiverBuffer[i].received == false ) {
      printf( "%d, ", receiverBuffer[i].seqnum ) ;
    }
  }
  printf( "\n" ) ;

  /* If the packet is not corrupted */
  if ( !IsCorrupted( packet ) ) {
    /* Check if the sequence number was expected */
    for( i = 0 ; i < WINDOWSIZE ; i++ ) {
      if( receiverBuffer[i].seqnum == packet.seqnum ) {
        /* Update our receiverBuffer to have received this packet */
        receiverBuffer[i].received = true ;

        if (TRACE > 0)
          printf("----B: packet %d is correctly received, send ACK!\n",packet.seqnum);
        packets_received++ ;

        /* Deliver packet to application layer */
        tolayer5( B, packet.payload ) ;

        /* Fill in the ACK for the packet received */
        sendpkt.acknum = packet.seqnum ;
      }
    }
  } else {
    if (TRACE > 0) 
      printf( "----B: packet corrupted, resend ACK!\n" ) ;
    /* Using -1 to denote corrupted packet for now */
    sendpkt.acknum = -1 ;
  }

  /* While the first packet in the buffer is received, move the window across */
  while( receiverBuffer[0].received == true ) {
    /* Cycle the elements of the buffer */
    for( i = 0 ; i < WINDOWSIZE - 1 ; i++ ) {
      receiverBuffer[ i ].seqnum = receiverBuffer[ i + 1 ].seqnum ;
      receiverBuffer[ i ].received = receiverBuffer[ i + 1 ].received ;
    }

    receiverBuffer[ WINDOWSIZE - 1 ].seqnum = ( receiverBuffer[ WINDOWSIZE - 1 ].seqnum + 1 ) % SEQSPACE ;
    receiverBuffer[ WINDOWSIZE - 1 ].received = false ;
  }

  /* create packet */
  sendpkt.seqnum = B_nextseqnum;
  B_nextseqnum = ( B_nextseqnum + 1 ) % SEQSPACE ;
    
  /* we don't have any data to send.  fill payload with 0's */
  for ( i=0; i<20 ; i++ ) 
    sendpkt.payload[i] = '0';  

  /* computer checksum */
  sendpkt.checksum = ComputeChecksum(sendpkt); 

  /* send out packet */
  tolayer3 ( B, sendpkt ) ;
}

/* the following routine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init(void)
{
  int i ;

  /* Initialize our recieverBuffer */
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    receiverBuffer[i].seqnum = i ;
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
