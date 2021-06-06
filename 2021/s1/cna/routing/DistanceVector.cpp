#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "DistanceVector.h"

static int TRACE = 0 ;

int main() {
	vector<string> names ;
	vector<routingTable> neighbours ;
	vector<routingTable> broadcast ;
	string currentLine ;
	int p = 0 ;

	/* Read the router names */
	getline( cin, currentLine ) ;
	while( !currentLine.empty() ) {
		/* Copy the name of this router into names */
		names.push_back( currentLine ) ;
		getline( cin, currentLine ) ;
	}

	/* sort router names into alphabetical order */
	/* TO-DO */

	for( int i = 0 ; i < names.size() ; i++ ) {
		neighbours.push_back( routingTable() ) ; /* create a routing table for each router */
		neighbours.at(i).name = names.at(i) ; /* add its name attribute */
 	}

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

			/* COULD ADD CHECK HERE TO SEE IF THE ROUTER NAMES AND DISTANCE ARE VALID */

			/* Put the link into the correct routingTable */
			addNeighbour( &neighbours, router1, router2, distance ) ;

			getline( cin, currentLine ) ;
		}

		for( int i = 0 ; i < neighbours.size() ; i++ ) {
			for( int j = 0 ; j < neighbours.at(i).routes.size() ; j++ ) {
				cout << neighbours.at(i).routes.at(j).start << " " << neighbours.at(i).routes.at(j).end << " " << neighbours.at(i).routes.at(j).distance << endl ;
			}
		}

		cout << endl ;

	// 	routingTable *broadcast = initBroadcast( names ) ;
	// 	if( TRACE > 1 ) {
	// 		cout << "broadcast array at t=0:" << endl ;
	// 		printRoutingTableArray( broadcast, names.size(), 0 ) ;
	// 		cout << "neighbours array at t=0: " << endl ;
	// 		printRoutingTableArray( neighbours, names.size(), 0 ) ;
	// 	}

	// 	routingTable* RTArray = (routingTable*)malloc( sizeof( routingTable ) * names.size() * names.size() ) ;
	// 	while( p < 100 ) {

	// 		for( int i = 0 ; i < names.size() ; i++ ) {
	// 			routingTable DV ;
	// 			calculateDV( &DV, names[i], names, neighbours, broadcast ) ;
	// 			printDV( &DV, names, p ) ;
	// 			calculateRT( &RTArray[i], &DV, names ) ;

	// 			if( TRACE > 1 ) {
	// 				cout << "RT: " << endl ;
	// 				printRoutingTableArray( &RTArray[i], 1, p ) ;
	// 			}

	// 			DV.routes.clear() ;
	// 		}


	// 		if( updateBroadcast( broadcast, RTArray, names ) == 0 ) {
	// 			p++ ;
	// 			break ;
	// 		}

	// 		for( int i = 0 ; i < names.size() ; i++ )
	// 			RTArray[i].routes.clear() ;

	// 		if( TRACE > 1 ) {
	// 			cout << "New broadcast array: " << endl ;
	// 			printRoutingTableArray( broadcast, names.size(), p ) ;
	// 		}
	// 		p++ ;
	// 	}

	// 	printBroadcast( broadcast, names ) ;

	// 	for( int i = 0 ; i < names.size() ; i++ ) {
	// 		broadcast[i].routes.clear() ;
	// 	}


		getline( cin, currentLine ) ;
	}

	return 0 ;
}