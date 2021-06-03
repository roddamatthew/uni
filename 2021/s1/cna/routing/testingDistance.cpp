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

int main() {
	routingTable *table = (routingTable*)malloc( sizeof( routingTable ) * 3 ) ;

	/* Mimic the input: 
	A
	B
	C

	A B 2
	A C 1
	*/

	table[0].name = "A" ;
	table[0].routes.push_back( link( "A", "B", 2 ) ) ;
	table[0].routes.push_back( link( "A", "C", 1 ) ) ;

	table[1].name = "B" ;
	table[1].routes.push_back( link( "B", "A", 2 ) ) ;

	table[2].name = "C" ;
	table[2].routes.push_back( link( "C", "A", 1 ) ) ;

	/* Note that this works when the routers are in the opposite order: */
	std::cout << "Distance between A and B is 2, distance() thinks it is: " << distance( "A", "B", table[1] ) << std::endl ;
	std::cout << "Distance between A and C is 1, distance() thinks it is: " << distance( "C", "A", table[0] ) << std::endl ;
	std::cout << "There is no link between B and C (NO_LINK = -1), distance() thinks it is: " << distance( "C", "B", table[2] ) << std::endl ;
}