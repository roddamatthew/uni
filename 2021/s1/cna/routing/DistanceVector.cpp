#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#define INFINITE 1073741823 /* define a constant for infinity (this is INT_MAX / 2) */

/* Data structure to store a link between two routers */
struct link {
	std::string start ;
	std::string end ;
	int distance ;

	/* defualt constructor if no distance is entered, assume infinite */
	link( std::string s, std::string e ) {
		start = s ;
		end = e ;
		distance = INFINITE ;
	}

	/* constructor for a given distance */
	link( std::string s, std::string e, int d ) {
		start = s ;
		end = e ;
		distance = d ;
	}
};

/* Data structure to represent a routing table */
/* Has the name of the router with a vector for its links */
struct routingTable {
	std::string name ;
	std::vector<link> routes ;
} ;

/* link is one router connection to another */
/* routingTable is all of the links of one router to all other routers */
	/* Even if not connected, this will have an entry */
/* tables is an array storing all of the routing tables of all routers */

int main() {
	std::vector<std::string> names ;
	std::string currentLine ;
	int size = 0 ;

	/* Read the router names */
	std::getline( std::cin, currentLine ) ;
	/* Read router names */
	while( !currentLine.empty() ) {
		/* create a routing table for this router */
		names.push_back( currentLine.substr( 0 ) ) ;
		size++ ;
		std::getline( std::cin, currentLine ) ;
	}


	/* Allocate memory for a routing table for each router */
	routingTable *tables = (routingTable*)malloc( sizeof( routingTable ) * size ) ;

	/* Put the router names into the routing tables */
	for( int j = 0 ; j < names.size() ; j++ )
		tables[j].name = names[j] ;


	/* Read links */
	std::getline( std::cin, currentLine ) ;
	while( !currentLine.empty() ) {

		int pos = currentLine.find( " " ) ; /* find the position of the first space */
		std::string router1 = currentLine.substr( 0, pos ) ; /* copy the first word */
		currentLine.erase( 0, pos + 1 ) ; /* erase the first word from the string */

		pos = currentLine.find( " " ) ; /* find the position of the new first space */
		std::string router2 = currentLine.substr( 0, pos ) ; /* copy the new first word */
		currentLine.erase( 0, pos + 1 ) ; /* erase the new word from the string */
		
		int distance = std::stoi( currentLine ) ; /* the rest of the string should now be a number */

		/* Search for routing tables containing the given router names */

		/* read link into the routing table */

		tables[0].routes.push_back( link( router1, router2, distance ) ) ; /* temporary for testing */

		std::getline( std::cin, currentLine ) ;
	}

	/* Fill in the rest of the links with infinity */

	/* print for debugging */
	for( int j = 0 ; j < size ; j++ ) {
		std::cout << tables[j].name << std::endl ;
		for( int i = 0 ; i < tables[j].routes.size() ; i++ ) {
			std::cout << tables[j].routes[i].start << " " << tables[j].routes[i].end << " " << tables[j].routes[i].distance << std::endl ;
		}
	}

	return 0 ;
}