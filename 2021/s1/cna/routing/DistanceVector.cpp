#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#define INFINITE 1073741823 /* define a constant for infinity (this is INT_MAX / 2) */
#define NO_LINK -1 /* define a constant for no link */

static int TRACE = 0 ;

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
} ;

/* Data structure to represent a routing table */
/* Has the name of the router with a vector for its links */
struct routingTable {
	std::string name ;
	std::vector<link> routes ;
} ;

/* Data Structures:
 - names: vector<string> containing all the router names in alphabetical order
 - neighbours: array of routingTable. 
 		- Elements ordered alphabetically by name
 		- Each element's name attribute is the name of the router
 		- Each element's routes attribute contains the links to its neighbours.
 - broadcast: array of routingTable.
 		- Elements ordered alphabetically by name
 		- Each element's name attribute is the name of the router
 		- Each element's routes attribute contains its lowest cost trip to each other router
 			- The start attribute of a link is the first hop
 			- The end attribute of a link is the destination
 			- The distance attribute is the total cost associated with the trip
 */

void printRoutingTableArray( routingTable* array, int size )
/* Debugging print command
 * Print any routingTable array
 * Can also be called with a size of 1 to print a single routingTable 
 */
{
	for( int i = 0 ; i < size ; i++ ) {
		std::cout << array[i].name << ":\n" ;
		for( int j = 0 ; j < array[i].routes.size() ; j++ ) {
			std::cout << array[i].routes[j].start << " " << array[i].routes[j].end << " " ;
			if( array[i].routes[j].distance >= INFINITE ) std::cout << "INF\n" ;
			else std::cout << array[i].routes[j].distance << std::endl ;
		}
	}
}

int distance( std::string router1, std::string router2, routingTable *table )
/* Find the distance between two routers in a given table
 * Loop through the routes in the table and check if router names match
 * If they do, return the distance attribute
 * If the loop finishes without finding a link, return NO_LINK
 */
{
	for( int i = 0 ; i < table->routes.size() ; i++ ) { /* loop over all the links */
		/* check if the router names match */
		if( table->routes[i].start == router1 && table->routes[i].end == router2 )
			return table->routes[i].distance ;
		/* also check if the router names are in the reverse order */
		if( table->routes[i].start == router2 && table->routes[i].end == router1 )
			return table->routes[i].distance ;
	}
	return NO_LINK ;
}

int distanceBroadcast( std::string router1, std::string router2, routingTable* broadcast, int size )
/* Use the global routingTable *broadcast variable to find the distance between two routers
 * Parameters:
 * router1: name of one end of the link
 * router2: name of the other end of the link

 * Note that links in the broadcast array are different from normal links:
 * the routingTable name is the link's beginning
 * routes[i].start is the link's first hop
 * routes[i].end is the link's destination

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
			/* distance from a router to itself is always zero */
			if( names[i] == names[j] ) broadcast[i].routes[j].distance = 0 ;
		}
	}

	return broadcast ;
}

routingTable* calculateDV( std::string name, std::vector<std::string> names, routingTable *neighbours, routingTable *broadcast )
/* Calculate the distance vector for a given router:

 * Parameters:
 * name: The name of the router who's DV table we're calculating
 * names: The names of all routers in the network
 * neighbours: routingTable with all direct links between our router and its neighbours

 * Result:
 * Return a routing table:
   - All links start at the router with name accessible by routingTable.name
   - All links first hop stored in routingTable.routes[i].start
   - All links destination stored in routingTable.routes[i].end
   - Total distance of the journey is stored in routingTable.routes[i].distance
 */
{
	int i = 0 , j = 0 ;

	routingTable* DV = new routingTable() ;
	DV->name = name ;

	while( i < names.size() ) { /* loop over each first hop */
		if( names[i] != name ) { /* exclude calculating distance to itself */
			while( j < names.size() ) { /* loop over each destination hop */
				if( names[j] != name ) { /* exclude calculating distance to itself */
					if( distance( name, names[i], &neighbours[i] ) != NO_LINK ) { /* check if there is a link between this router and the first hop */
						int firstHopDistance = distance( name, names[i], &neighbours[i] ) ;
						int desinationHopDistance = distanceBroadcast( names[i], names[j], broadcast, names.size() ) ;
						int totalDistance = firstHopDistance + desinationHopDistance ;
						DV->routes.push_back( link( names[i], names[j], totalDistance ) ) ;
					} else { /* if there is no link for the first hop */
						DV->routes.push_back( link( names[i], names[j], NO_LINK ) ) ;
					}
				}
				j++ ;
			}
		}
		j = 0 ;
		i++ ;
	}
	return DV ;
}

routingTable* calculateRT( routingTable* DV, std::vector<std::string> names )
/* Find the routing table from the distance vector table
 * Result is a routingTable with only names.size() links
 	* Each link is the shortest distance currently known from a router to each of its neighbours
 */
{
	routingTable* RT = new routingTable ;
	RT->name = DV->name ;

	for( int i = 0 ; i < names.size() ; i++ ) {
		link shortest = link( "Error!", names[i], INFINITE ) ;

		for( int j = 0 ; j < DV->routes.size() ; j++ ) {
			if( DV->routes[j].end == shortest.end && DV->routes[j].distance <= shortest.distance ) {
				shortest.distance = DV->routes[j].distance ;
				shortest.start = DV->routes[j].start ;
			}
		}
		RT->routes.push_back( shortest ) ;
	}

	return RT ;
}

routingTable* updateBroadcast( routingTable* broadcast, routingTable* RTArray, std::vector<std::string> names )
/* Update broadcast to have all the latest routing distances
 */
{
	for( int i = 0 ; i < names.size() ; i++ ) {
		for( int j = 0 ; j < RTArray[i].routes.size() ; j++ ) {
			/* if destinations match */
			/* and distance is less */
			/* update distance and first hop */
			if( RTArray[i].routes[j].end == broadcast[i].routes[j].end && RTArray[i].routes[j].distance < broadcast[i].routes[j].distance ) {
				broadcast[i].routes[j].distance = RTArray[i].routes[j].distance ;
				broadcast[i].routes[j].start = RTArray[i].routes[j].start ;
			}
		}
	}
	return broadcast ;
}

int main() {
	std::vector<std::string> names ;
	std::string currentLine ;

	/* Read the router names */
	std::getline( std::cin, currentLine ) ;
	while( !currentLine.empty() ) {
		/* Copy the name of this router into names */
		names.push_back( currentLine ) ;
		std::getline( std::cin, currentLine ) ;
	}

	/* Allocate memory for a routing table for each router */
	routingTable *neighbours = (routingTable*)malloc( sizeof( routingTable ) * names.size() ) ;

	for( int i = 0 ; i < names.size() ; i++ ) {
		/* Put the router names into the routingTables */
		neighbours[i].name = names[i] ;
 	}

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

		/* COULD ADD CHECK HERE TO SEE IF THE ROUTER NAMES AND DISTANCE ARE VALID */

		/* Put the link into the correct routingTable */
		for( int i = 0 ; i < names.size() ; i++ ) {
			if( router1 == neighbours[i].name )
				neighbours[i].routes.push_back( link( router1, router2, distance ) ) ;
			if( router2 == neighbours[i].name )
				neighbours[i].routes.push_back( link( router2, router1, distance ) ) ;
 		}

		std::getline( std::cin, currentLine ) ;
	}

	routingTable *broadcast = initBroadcast( names ) ;
	printRoutingTableArray( broadcast, names.size() ) ;

	std::cout << "neighbours array: " << std::endl ;
	printRoutingTableArray( neighbours, names.size() ) ;

	for( int p = 0 ; p < 5 ; p++ ) {
		routingTable* RTArray = (routingTable*)malloc( sizeof( routingTable ) * names.size() ) ;

		for( int i = 0 ; i < names.size() ; i++ ) {
			routingTable *DV = calculateDV( names[i], names, neighbours, broadcast ) ;
			std::cout << "DV: " << std::endl ;
			printRoutingTableArray( DV, 1 ) ;
			routingTable *RT = calculateRT( DV, names ) ;
			
			RTArray[i] = *RT ;

			std::cout << "RT: " << std::endl ;
			printRoutingTableArray( &RTArray[i], 1 ) ;
		}

		std::cout << "New broadcast array: " << std::endl ;
		updateBroadcast( broadcast, RTArray, names ) ;
		printRoutingTableArray( broadcast, names.size() ) ;
	}

	return 0 ;
}