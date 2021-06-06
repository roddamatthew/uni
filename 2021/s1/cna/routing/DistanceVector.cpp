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
	std::vector<struct link> routes ;
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

void printRoutingTableArray( routingTable* array, int size, int iteration )
 /* Print any routingTable array
 * Can also be called with a size of 1 to print a single routingTable 
 */
{
	for( int i = 0 ; i < size ; i++ ) {
		std::cout << "router " << array[i].name << " at t=" << iteration << std::endl ;
		for( int j = 0 ; j < array[i].routes.size() ; j++ ) {
			std::cout << array[i].routes[j].start << " " << array[i].routes[j].end << " " ;
			if( array[i].routes[j].distance >= INFINITE ) std::cout << "INF\n" ; else 
			if( array[i].routes[j].distance < 0 ) std::cout << "-\n" ; else
			std::cout << array[i].routes[j].distance << std::endl ;
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

int distanceOneWay( std::string router1, std::string router2, routingTable *table )
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
	}
	return NO_LINK ;
}

void printDV( routingTable* array, std::vector<std::string> names, int iteration ) {
	std::cout << "router " << array->name << " at t=" << iteration << std::endl ;
	for( int i = 0 ; i < names.size() ; i++ ) {
		if( names[i] != array->name )
			std::cout << "\t" << names[i] ;
	}
	std::cout << std::endl ;

	for( int i = 0 ; i < names.size() ; i++ ) {
		if( names[i] != array->name ) {
			std::cout << names[i] ;
			for( int j = 0 ; j < names.size() ; j++ ) {
				if( names[j] != array->name ) {
					int d = distanceOneWay( names[j], names[i], array ) ;

					std::cout << "\t" ;
					if( d >= INFINITE ) std::cout << "INF" ; else 
					if( d < 0 ) std::cout << "-" ; else
					std::cout << d ;
				}
			}
			std::cout << std::endl ;
		}
	}
	std::cout << std::endl ;
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
	routingTable* broadcast = (routingTable*)malloc( sizeof( routingTable ) * names.size() * names.size() * names.size() ) ;

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

routingTable* calculateDV( routingTable *DV, std::string name, std::vector<std::string> names, routingTable *neighbours, routingTable *broadcast )
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

void calculateRT( routingTable* RT, routingTable* DV, std::vector<std::string> names )
/* Find the routing table from the distance vector table
 * Result is a routingTable with only names.size() links
 	* Each link is the shortest distance currently known from a router to each of its neighbours
 */
{
	RT->name = DV->name ;

	if( TRACE > 2 )
		std::cout << "Calculating routing table for router: " << RT->name << std::endl ;

	if( TRACE > 2 )
		std::cout << "names.size() is " << names.size() << std::endl ;
	for( int i = 0 ; i < names.size() ; i++ ) {
		if( TRACE > 2 )
			std::cout << "names[" << i << "] is " << names[i] << std::endl ;
		link shortest = link( "Error!", names[i], INFINITE ) ;

		if( TRACE > 2 )
			std::cout << "DV->routes.size() is " << DV->routes.size() << std::endl ;
		for( int j = 0 ; j < DV->routes.size() ; j++ ) {
			if( TRACE > 2 )
				std::cout << "j is " << j << std::endl ;
			if( DV->routes[j].end == shortest.end && DV->routes[j].distance <= shortest.distance && DV->routes[j].distance > 0 ) {
				if( TRACE > 2 ) {
					std::cout << "Found new shortest route to " << shortest.end << " through " << DV->routes[j].start ;
					std::cout << " with distance " << DV->routes[j].distance << std::endl ;
				}
 				shortest.distance = DV->routes[j].distance ;
				shortest.start = DV->routes[j].start ;
			}
		}
		if( TRACE > 2 )
			std::cout << "Adding shortest to RT.routes" << std::endl ;
		RT->routes.push_back( shortest ) ;
	}
}

int updateBroadcast( routingTable* broadcast, routingTable* RTArray, std::vector<std::string> names )
/* Update broadcast to have all the latest routing distances
 */
{
	int count = 0 ;
	for( int i = 0 ; i < names.size() ; i++ ) {
		for( int j = 0 ; j < RTArray[i].routes.size() ; j++ ) {
			/* if destinations match */
			/* and distance is less */
			/* update distance and first hop */
			if( RTArray[i].routes[j].end == broadcast[i].routes[j].end && RTArray[i].routes[j].distance < broadcast[i].routes[j].distance ) {
				broadcast[i].routes[j].distance = RTArray[i].routes[j].distance ;
				broadcast[i].routes[j].start = RTArray[i].routes[j].start ;
				count++ ;
			}
		}
	}
	return count ;
}

void printBroadcast( routingTable* broadcast, std::vector<std::string> names ) {
	for( int i = 0 ; i < names.size() ; i++ ) {
		for( int j = 0 ; j < names.size() ; j++ ) {
			if( i != j ) {
				std::cout << "router " << names[i] << ": " << names[j] << " is " ;
				std::cout << broadcast[i].routes[j].distance << " routing through " << broadcast[i].routes[j].start << std::endl ;
			}
		}
	}
	std::cout << std::endl ;
}

void addNeighbour( routingTable* neighbours, std::string router1, std::string router2, int distance, std::vector<std::string> names )
/* Add a link to the neighbour array
 * Links are always added to both tables
 * If the link already exists, only update the distance
 */
{
	for( int i = 0 ; i < names.size() ; i++ ) { /* loop through each routingTable*/
		if( neighbours[i].name == router1 ) {
			bool linkExists = false ;
			for( int j = 0 ; j < neighbours[i].routes.size() ; j++ ) {
				if( neighbours[i].routes[j].end == router2 ) {
					neighbours[i].routes[j].distance = distance ;
					linkExists = true ;
				}
			}

			if( !linkExists )
				neighbours[i].routes.push_back( link( router1, router2, distance ) ) ;
		}
		else if( neighbours[i].name == router2 ) {
			bool linkExists = false ;
			for( int j = 0 ; j < neighbours[i].routes.size() ; j++ ) {
				if( neighbours[i].routes[j].end == router1 ) {
					neighbours[i].routes[j].distance = distance ;
					linkExists = true ;
				}
			}

			if( !linkExists )
				neighbours[i].routes.push_back( link( router2, router1, distance ) ) ;
		}

	}
}

int main() {
	std::vector<std::string> names ;
	std::string currentLine ;
	int p = 0 ;

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
			addNeighbour( neighbours, router1, router2, distance, names ) ;

			std::getline( std::cin, currentLine ) ;
		}

		routingTable *broadcast = initBroadcast( names ) ;
		if( TRACE > 1 ) {
			std::cout << "broadcast array at t=0:" << std::endl ;
			printRoutingTableArray( broadcast, names.size(), 0 ) ;
			std::cout << "neighbours array at t=0: " << std::endl ;
			printRoutingTableArray( neighbours, names.size(), 0 ) ;
		}

		routingTable* RTArray = (routingTable*)malloc( sizeof( routingTable ) * names.size() * names.size() ) ;
		while( p < 100 ) {

			for( int i = 0 ; i < names.size() ; i++ ) {
				routingTable DV ;
				calculateDV( &DV, names[i], names, neighbours, broadcast ) ;
				printDV( &DV, names, p ) ;
				calculateRT( &RTArray[i], &DV, names ) ;

				if( TRACE > 1 ) {
					std::cout << "RT: " << std::endl ;
					printRoutingTableArray( &RTArray[i], 1, p ) ;
				}

				DV.routes.clear() ;
			}


			if( updateBroadcast( broadcast, RTArray, names ) == 0 ) {
				p++ ;
				break ;
			}

			for( int i = 0 ; i < names.size() ; i++ )
				RTArray[i].routes.clear() ;

			if( TRACE > 1 ) {
				std::cout << "New broadcast array: " << std::endl ;
				printRoutingTableArray( broadcast, names.size(), p ) ;
			}
			p++ ;
		}

		printBroadcast( broadcast, names ) ;

		for( int i = 0 ; i < names.size() ; i++ ) {
			broadcast[i].routes.clear() ;
		}


		std::getline( std::cin, currentLine ) ;
	}

	return 0 ;
}