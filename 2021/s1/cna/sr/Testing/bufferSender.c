#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* ******************************************************************
	Selective Repeat Protocol:...
**********************************************************************/

#define RTT  15.0               /* round trip time.  MUST BE SET TO 15.0 when submitting assignment */
#define WINDOWSIZE 6            /* Maximum number of buffered unacked packet */
#define SEQSPACE 12             /* min sequence space for SR is 2 * WINDOWSIZE */
#define NOTINUSE (-1)           /* used to fill header fields that are not being used */
#define A 0

static int timercount = 0 ;
static int window_full = 0 ;
static int TRACE = 0 ;

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

/* Fake starttimer function so code compiles */
void starttimer( int i, int j ) {
  timercount++ ;
  printf( "Started a timer number: %d\n", timercount ) ;
}

/* Fake stoptimer function so code compiles */
void stoptimer( int i ){
  printf( "Stoped a timer number: %d\n", timercount ) ;
}

/* Fake tolayer3 function so code compiles */
void tolayer3( int i, struct pkt packet ) {
  printf( "Sent a packet to layer 3 with seqnum: %d\n", packet.seqnum ) ;
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

/* Start the sender timer and update the associated state variables */
/* Input parameter is the seqeunce number of the packet starting the timer */
void startTimer( int seqnum ) {
  /* If called with an invalid sequence number spit an error */
  if( seqnum >= 0 ) {
    starttimer( A, RTT ) ;
    timerAssociatedSeqNum = seqnum ;
    timerStarted = true ;
  } else {
    printf( "startTimer called with an invalid seqnuence number: %d (note: -1 denotes a seqnum not in use)\n", seqnum ) ;
  }
}

/* Stop the timer and update the associated state variables */
void stopTimer() {
  stoptimer( A ) ;
  timerAssociatedSeqNum = NOTINUSE ;
  timerStarted = false ;
}

/* called from layer 5 (application layer), passed the message to be sent to other side */
void A_output(struct msg message)
{
  if( !windowFull() ) {
    /* Create a packet and sent it to the network layer */
    struct pkt packet ;
    packet = createPacket( message ) ;
    tolayer3( A, packet ) ;

    /* Add the packet to our senderBuffer */
    addPacketToBuffer( packet ) ;

    /* If a timer is not started, start one */
    if( !timerStarted ) {
      startTimer( packet.seqnum ) ;
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
    /* Update buffer to have received ACK */
    bufferReceiveACK( packet.acknum ) ;
    /* Stop timer if ack was associated with timer */
    if( timerAssociatedSeqNum == packet.acknum ) stopTimer() ;
    /* Move window if necessary */
    moveSenderWindow() ;
  }
}

/* called when A's timer goes off */
void A_timerinterrupt(void)
{
  int i ;
  int firstResentSeqNum = -1 ;

  /* Resend all packets not yet acked */
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    /* Check that the packet is also initialized */
    if( senderBuffer[i].acked == false && senderBuffer[i].packet.seqnum != NOTINUSE ) {
      if( firstResentSeqNum == -1 ) firstResentSeqNum = senderBuffer[i].packet.seqnum ;
      /* Resend the packet not acked */
      tolayer3( A, senderBuffer[i].packet ) ;
      /* Make sure the buffer knows this packet has been sent */
      senderBuffer[i].sent = true ;
    }
  }

  /* Restart timer */
  startTimer( firstResentSeqNum ) ;
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

void printSenderBuffer() {
  int i, j ;
  printf( "senderBuffer: \n" ) ;
  for( i = 0 ; i < WINDOWSIZE ; i++ ) {
    printf( "sent: %s\n", senderBuffer[i].acked ? "true" : "false" ) ;
    printf( "acked: %s\n", senderBuffer[i].acked ? "true" : "false" ) ;
    printf( "packet: seqnum: %d, acknum: %d\n", senderBuffer[i].packet.seqnum, senderBuffer[i].packet.acknum ) ;
    printf( "payload: " ) ;
    for( j = 0 ; j < 20 ; j++ ) {
      printf( "%c", senderBuffer[i].packet.payload[j] ) ;
    }
    printf( "\n" ) ;
  }
  printf( "\n" ) ;
}

int main() {
  struct msg message ;
  int i ;

  for( i = 0 ; i < 20 ; i++ ) {
    message.data[i] = 'a' ;
  }

  struct pkt packet ;
  packet.acknum = 0 ;
  packet.seqnum = NOTINUSE ;
  for( i = 0 ; i < 20 ; i++ ) {
    packet.payload[i] = '0' ;
  }
  packet.checksum = ComputeChecksum( packet ) ;

  A_init() ;
  A_output( message ) ;
  A_output( message ) ;
  A_output( message ) ;
  A_output( message ) ;
  A_input( packet ) ;
  A_timerinterrupt() ;
  printSenderBuffer() ;

  return 0 ;
}

// /* called when A's timer goes off */
// void A_timerinterrupt(void)
// {
//   int i ;
//   int firstResentSeqNum = -1 ;

//   if (TRACE > 0)
//     printf( "----A: time out,resend packets!\n" ) ;

//   /* Resend all packets not yet acked */
//   for( i = 0 ; i < WINDOWSIZE ; i++ ) {
//     /* Check that the packet is also initialized */
//     if( senderBuffer[i].acked == false && senderBuffer[i].packet.seqnum != NOTINUSE ) {
//       if( firstResentSeqNum == -1 ) firstResentSeqNum = senderBuffer[i].packet.seqnum ;
//       /* Resend the packet not acked */
//       tolayer3( A, senderBuffer[i].packet ) ;
//       /* Make sure the buffer knows this packet has been sent */
//       senderBuffer[i].sent = true ;

//       if (TRACE > 0)
//         printf ( "---A: resending packet %d\n", senderBuffer[i].packet.seqnum ) ;
//       /* Increase counter of resent packets */
//       packets_resent++ ;
//     }
//   }

//   /* Restart timer */
//   if( firstResentSeqNum != -1 ) startTimerHandler( firstResentSeqNum ) ;
// }       