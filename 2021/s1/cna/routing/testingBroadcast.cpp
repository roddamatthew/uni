#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

#define INFINITE 22
#define NO_LINK -1

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

int distanceBroadcast( std::string router1, std::string router2, routingTable* broadcast, int size )
/* Use the global routingTable *broadcast variable to find the distance between two routers
 * Parameters:
 * router1: name of one end of the link
 * router2: name of the other end of the link

 * Result:
 * Return the int distance between the two routers
 */
{
	for( int i = 0 ; i < size ; i++ ) { /* Loop over the broadcast array */
		if( broadcast[i].name == router1 ) { /* Check if the routingTable has a matching name */
			for( int j = 0 ; j < broadcast[i].routes.size() ; j++ ) { /* loop over all the routes in the routingTable */
				if( broadcast[i].routes[j].end == router2 ) /* Check if the destination matches */
					return broadcast[i].routes[j].distance ; /* Return the distance */
			}
		}
	}
	/* Error case */
	/* Broadcast table should always have a link between every router initialised to INFINITE */
	return NO_LINK ;
}

routingTable* initBroadcast( std::vector<std::string> names )
/* Initialize the broadcast array
 * All distances are set to INFINITE
 */
{
	routingTable* broadcast = (routingTable*)malloc( sizeof( routingTable ) * names.size() ) ;

	for( int i = 0 ; i < names.size() ; i++ ) { /* loop over each router */
		for( int j = 0 ; j < names.size() ; j++ ) { /* loop over each router */
			/* name the routingTable after where each link starts*/
			broadcast[i].name = names[i] ;
			/* make a link between all routers with an initial distance of INFINITE */
			broadcast[i].routes.push_back( link( names[i], names[j], INFINITE ) ) ;
		}
	}

	return broadcast ;
}

void printBroadcast( routingTable *broadcast, int size ) {
	for( int i = 0 ; i < size ; i++ ) {
		std::cout << broadcast[i].name << ":\n" ;
		for( int j = 0 ; j < size ; j++ ) {
			std::cout << broadcast[i].routes[j].start << " " << broadcast[i].routes[j].end << " " << broadcast[i].routes[j].distance << std::endl ;
		}
		std::cout << std::endl ;
	}
}

int main() {
	std::vector<std::string> names ;
	names.push_back( "A" ) ;
	names.push_back( "B" ) ;
	names.push_back( "C" ) ;
	names.push_back( "D" ) ;

	routingTable* broadcast = initBroadcast( names ) ;

	printBroadcast( broadcast, names.size() ) ;

	std::cout << "Change distance from A to D to 4" << std::endl ;
	broadcast[0].routes[3].distance = 4 ;

	std::cout << "Searching using distanceBroadcast: Look for A to D: \n" << distanceBroadcast( "A", "D", broadcast, names.size() ) << std::endl ;

	printBroadcast( broadcast, names.size() ) ;
}