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

void setLinks( std::string router1, std::string router2, int distance, struct routingTable *tables, int size )
/* set the distance for links between router1 and router2
 * search through tables for the links
 * make sure the link is set in both router's routing tables 
 */
{
	/* search through all the tables */
	for( int i = 0 ; i < size ; i++ ) {
		/* search through all the routes */
		for( int j = 0 ; j < tables[i].routes.size() ; j++ ) {
			/* If the router names match, set the distance */
			if( tables[i].routes[j].start == router1 && tables[i].routes[j].end == router2 ) {
				tables[i].routes[j].distance = distance ;
				if( TRACE > 2 ) std::cout << "In table " << tables[i].name << "set " << tables[i].routes[j].start << " " << tables[i].routes[j].end << " " << tables[i].routes[j].distance << std::endl ;
			}
			/* Also check if they're in the reverse order */
			if( tables[i].routes[j].start == router2 && tables[i].routes[j].end == router1 ){
				tables[i].routes[j].distance = distance ;
				if( TRACE > 2 ) std::cout << "In table " << tables[i].name << "set " << tables[i].routes[j].start << " " << tables[i].routes[j].end << " " << tables[i].routes[j].distance << std::endl ;
			}
		}
	}
}

int distance( struct routingTable *table, std::string router1, std::string router2 ) {
	/* Search a routing table for a link and return the distance */
	for( int i = 0 ; i < table.routes.size() ; i++ ) {
		if( router1 == table.routes[i].start && router2 == table.routes[i].end )
			return table.routes[i].distance ;
		else if( router1 == table.routes[i].end && router2 == table.routes[i].start )
			return table.routes[i].distance ;
	}
	return -100 ;
}

routingTable* calculateDV( std::string currentTableName, struct routingTable *tables, struct routingTable *broadcast, std::vector<std::string> names, int size ) {
	routingTable *DV = new routingTable() ;

	int i, j ;

	while( i < size ) {
		if( names[i] != currentTableName ) {
			while( j < size ) {
				if( names[j] != currentTableName ) {
					if( firstHop.exists() ) {
						int distance = distance( currentTableName, names[i] ) ;
						distance += distanceBroadcasted( names[i], names[j] ) ;
						DV->routes.push_back( link( names[i], names[j], distance ) ) ;
					}
					else {
						DV->routes.push_back( link( names[i], names[j], -1 ) ) ;
					}
				}
				j++ ;
			}
		}
		i++ ;
	}

	for( i = 0 ; i < DV->routes.size() ; i++ ) {
		std::cout << DV->routes[i].start << " " << DV->routes[i].end << " " << DV->routes[i].distance << std::endl ;
	}

	return DV ;
}

int main() {
	std::vector<std::string> names ;
	std::string currentLine ;
	int tablesSize = 0 ;

	/* Read the router names */
	std::getline( std::cin, currentLine ) ;
	/* Read router names */
	while( !currentLine.empty() ) {
		/* create a routing table for this router */
		names.push_back( currentLine.substr( 0 ) ) ;
		tablesSize++ ;
		std::getline( std::cin, currentLine ) ;
	}


	/* Allocate memory for a routing table for each router */
	routingTable *tables = (routingTable*)malloc( sizeof( routingTable ) * tablesSize ) ;

	for( int j = 0 ; j < tablesSize ; j++ ){
		/* Put the router names into the routing tables */
		tables[j].name = names[j] ;

		/* Initialize infinite links between all routers */
		for( int i = 0 ; i < tablesSize ; i++ ) {
			/* links from router to itself have zero distance */
			if( i != j ) tables[j].routes.push_back( link( names[j], names[i] ) ) ;
			if( i == j ) tables[j].routes.push_back( link( names[j], names[i], 0 ) ) ;
		}
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

		setLinks( router1, router2, distance, tables, tablesSize ) ;

		std::getline( std::cin, currentLine ) ;
	}

	routingTable *broadcast = (routingTable*)malloc( sizeof( routingTable ) * tablesSize ) ;
	for( int i = 0 ; i < tablesSize ; i++ ) {
		broadcast[i].name = names[i] ;
		for( int j = 0 ; j < tablesSize ; j++ ) {
			broadcast[i].routes.push_back( link( names[i], names[j], INFINITE ) ) ;
		}
	}

	calculateDV( names[0], tables, broadcast, names, tablesSize ) ;

	return 0 ;
}