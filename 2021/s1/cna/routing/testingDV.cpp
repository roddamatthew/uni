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

int distance( std::string router1, std::string router2, routingTable table )
/* Find the distance between two routers in a given table
 * Loop through the routes in the table and check if router names match
 * If they do, return the distance attribute
 * If the loop finishes without finding a link, return NO_LINK
 */
{
	for( int i = 0 ; i < table.routes.size() ; i++ ) { /* loop over all the links */
		/* check if the router names match */
		if( table.routes[i].start == router1 && table.routes[i].end == router2 )
			return table.routes[i].distance ;
		/* also check if the router names are in the reverse order */
		if( table.routes[i].start == router2 && table.routes[i].end == router1 )
			return table.routes[i].distance ;
	}
	return NO_LINK ;
}

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
			/* distance from a router to itself is always zero */
			if( names[i] == names[j] ) broadcast[i].routes[j].distance = 0 ;
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

routingTable* calculateDV( std::string name, std::vector<std::string> names, routingTable neighbours, routingTable *broadcast )
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
					if( distance( name, names[i], neighbours ) != NO_LINK ) { /* check if there is a link between this router and the first hop */
						int firstHopDistance = distance( name, names[i], neighbours ) ;
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

int main() {
	routingTable *table = (routingTable*)malloc( sizeof( routingTable ) * 3 ) ;
	std::vector<std::string> names ;
	names.push_back( "X" ) ;
	names.push_back( "Y" ) ;
	names.push_back( "Z" ) ;

	/* Mimic the input: 
	X
	Y
	Z
	 
	X Z 7
	X Y 2
	Y Z 1
	*/

	table[0].name = "X" ;
	table[0].routes.push_back( link( "X", "Z", 7 ) ) ;
	table[0].routes.push_back( link( "X", "Y", 2 ) ) ;

	table[1].name = "Y" ;
	table[1].routes.push_back( link( "Y", "X", 2 ) ) ;
	table[1].routes.push_back( link( "Y", "Z", 1 ) ) ;

	table[2].name = "Z" ;
	table[2].routes.push_back( link( "Z", "X", 7 ) ) ;
	table[2].routes.push_back( link( "Z", "Y", 1 ) ) ;

	routingTable* broadcast = initBroadcast( names ) ;
	printBroadcast( broadcast, names.size() ) ;

	for( int j = 0 ; j < names.size() ; j++ ) {

		routingTable* DV = calculateDV( names[j], names, table[j], broadcast ) ;

		for( int i = 0 ; i < DV->routes.size() ; i++ ) {
			std::cout << DV->routes[i].start << " " << DV->routes[i].end << " " ;
			if( DV->routes[i].distance < INFINITE ) std::cout << DV->routes[i].distance << std::endl ;
			else std::cout << "INF" << std::endl ;
		}
		std::cout << std::endl ;
	}
}