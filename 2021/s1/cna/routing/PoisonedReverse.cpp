#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "PoisonedReverse.h"

int main() {
	vector<string> names ; /* store router names */
	string currentLine ; /* store current line of input */

	/* Read the router names */
	getline( cin, currentLine ) ;
	while( !currentLine.empty() ) {
		/* Copy the name of this router into names */
		names.push_back( currentLine ) ;
		getline( cin, currentLine ) ;
	}

	/* sort router names into alphabetical order */
	/* This was done following the tutorial at:
		https://www.includehelp.com/cpp-programs/sort-names-in-an-alphabetical-order.aspx
	*/
	names = sortAlphabetically( names ) ;

	/* Initialize neighbours and broadcast vectors (See poisoningFunctions/routingFunctions for explanation)*/
	vector<routingTable> neighbours ;
	vector<routingTable> broadcast ;

	for( int i = 0 ; i < names.size() ; i++ ) {
		neighbours.push_back( routingTable() ) ; /* create a routing table for each router */
		neighbours.at(i).name = names.at(i) ; /* add its name */

		broadcast.push_back( routingTable() ) ; /* create a routingTable for each router */
		broadcast.at(i).name = names.at(i) ; /* add its name */
		for( int j = 0 ; j < names.size() ; j++ ) {
			broadcast.at(i).routes.push_back( link( names.at(i), names.at(j), INFINITE ) ) ; /* add an initial infinite link */
			if( i == j ) broadcast.at(i).routes.at(j).distance = 0 ; /* change this to a zero cost link if going to itself */
		}
 	}

 	int iteration = 0 ; /* count of how many iterations the algorithm has gone through */

	/* Read links */
	getline( cin, currentLine ) ;
	while( !currentLine.empty() ) {
		while( !currentLine.empty() ) {
			int pos = currentLine.find( " " ) ; /* find the position of the first space */
			string router1 = currentLine.substr( 0, pos ) ; /* copy the first word */
			currentLine.erase( 0, pos + 1 ) ; /* erase the first word from the string */

			pos = currentLine.find( " " ) ; /* find the position of the new first space */
			string router2 = currentLine.substr( 0, pos ) ; /* copy the new first word */
			currentLine.erase( 0, pos + 1 ) ; /* erase the new word from the string */
			
			int distance = stoi( currentLine ) ; /* the rest of the string should now be a number */

			/* Put the link into the correct routingTable */
			addNeighbour( &neighbours, router1, router2, distance ) ;

			getline( cin, currentLine ) ;
		}

		while( iteration < 100 ) { /* set a max iteration of 100 to exit in case of an error */
			vector<routingTable> newRTs ; /* temporary storage for the current iterations routingTables */

			/* Calculate the distance vector table and print it */
			vector<routingTable> DVs ;
			calculateDVs( &DVs, &neighbours, &broadcast ) ;
			printDVs( &DVs, iteration ) ;

			/* Calculate the routing tables, storing the result in newRTs */
			calculateRTs( &newRTs, &DVs ) ;

			iteration++ ;

			/* Update the broadcast vector, exiting if there is no new information */
			if( updateBroadcast( &newRTs, &broadcast ) == 0 )
				break ;
		}

		/* Print the final routing information */
		printBroadcast( &broadcast ) ;

		/* Check for new routes given by the user */
		getline( cin, currentLine ) ;
	}

	return 0 ;
}