#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "DistanceVector.h"

static int TRACE = 0 ;

/* Data Structures:
 - names: vector<string> containing all the router names in alphabetical order
 - neighbours: array of routingTable. 
 		- Elements ordered alphabetically by name
 		- Each element's name attribute is the name of the router
 		- Each element's routes attribute contains the links to its neighbours->
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
		cout << "router " << array[i].name << " at t=" << iteration << endl ;
		for( int j = 0 ; j < array[i].routes.size() ; j++ ) {
			cout << array[i].routes[j].start << " " << array[i].routes[j].end << " " ;
			if( array[i].routes[j].distance >= INFINITE ) cout << "INF\n" ; else 
			if( array[i].routes[j].distance < 0 ) cout << "-\n" ; else
			cout << array[i].routes[j].distance << endl ;
		}
	}
}

int distance( string router1, string router2, routingTable *table )
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

int distanceOneWay( string router1, string router2, routingTable *table )
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

void printDV( routingTable* array, vector<string> names, int iteration ) {
	cout << "router " << array->name << " at t=" << iteration << endl ;
	for( int i = 0 ; i < names.size() ; i++ ) {
		if( names[i] != array->name )
			cout << "\t" << names[i] ;
	}
	cout << endl ;

	for( int i = 0 ; i < names.size() ; i++ ) {
		if( names[i] != array->name ) {
			cout << names[i] ;
			for( int j = 0 ; j < names.size() ; j++ ) {
				if( names[j] != array->name ) {
					int d = distanceOneWay( names[j], names[i], array ) ;

					cout << "\t" ;
					if( d >= INFINITE ) cout << "INF" ; else 
					if( d < 0 ) cout << "-" ; else
					cout << d ;
				}
			}
			cout << endl ;
		}
	}
	cout << endl ;
}

int distanceBroadcast( string router1, string router2, routingTable* broadcast, int size )
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

routingTable* calculateDV( routingTable *DV, string name, vector<string> names, routingTable *neighbours, routingTable *broadcast )
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

void calculateRT( routingTable* RT, routingTable* DV, vector<string> names )
/* Find the routing table from the distance vector table
 * Result is a routingTable with only names.size() links
 	* Each link is the shortest distance currently known from a router to each of its neighbours
 */
{
	RT->name = DV->name ;

	if( TRACE > 2 )
		cout << "Calculating routing table for router: " << RT->name << endl ;

	if( TRACE > 2 )
		cout << "names.size() is " << names.size() << endl ;
	for( int i = 0 ; i < names.size() ; i++ ) {
		if( TRACE > 2 )
			cout << "names[" << i << "] is " << names[i] << endl ;
		link shortest = link( "Error!", names[i], INFINITE ) ;

		if( TRACE > 2 )
			cout << "DV->routes.size() is " << DV->routes.size() << endl ;
		for( int j = 0 ; j < DV->routes.size() ; j++ ) {
			if( TRACE > 2 )
				cout << "j is " << j << endl ;
			if( DV->routes[j].end == shortest.end && DV->routes[j].distance <= shortest.distance && DV->routes[j].distance > 0 ) {
				if( TRACE > 2 ) {
					cout << "Found new shortest route to " << shortest.end << " through " << DV->routes[j].start ;
					cout << " with distance " << DV->routes[j].distance << endl ;
				}
 				shortest.distance = DV->routes[j].distance ;
				shortest.start = DV->routes[j].start ;
			}
		}
		if( TRACE > 2 )
			cout << "Adding shortest to RT.routes" << endl ;
		RT->routes.push_back( shortest ) ;
	}
}

int updateBroadcast( routingTable* broadcast, routingTable* RTArray, vector<string> names )
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

void printBroadcast( routingTable* broadcast, vector<string> names ) {
	for( int i = 0 ; i < names.size() ; i++ ) {
		for( int j = 0 ; j < names.size() ; j++ ) {
			if( i != j ) {
				cout << "router " << names[i] << ": " << names[j] << " is " ;
				cout << broadcast[i].routes[j].distance << " routing through " << broadcast[i].routes[j].start << endl ;
			}
		}
	}
	cout << endl ;
}

void addNeighbour( vector<routingTable> *neighbours, string router1, string router2, int distance )
/* Add a link to the neighbour array
 * Links are always added to both tables
 * If the link already exists, only update the distance
 */
{
	for( int i = 0 ; i < neighbours->size() ; i++ ) {
		if( neighbours->at(i).name == router1 ) { /* find the right routingTable */
			bool exists = false ;
			for( int j = 0 ; j < neighbours->at(i).routes.size() ; j++ ) { /* check if the route already exists */
				if( neighbours->at(i).routes.at(j).end == router2 ) {
					exists = true ;
					neighbours->at(i).routes.at(j).distance = distance ;
				}
			}
			if( !exists )
				neighbours->at(i).routes.push_back( link( router1, router2, distance ) ) ;
		}

		if( neighbours->at(i).name == router2 ) { /* find the right routingTable */
			bool exists = false ;
			for( int j = 0 ; j < neighbours->at(i).routes.size() ; j++ ) { /* check if the route already exists */
				if( neighbours->at(i).routes.at(j).end == router1 ) {
					exists = true ;
					neighbours->at(i).routes.at(j).distance = distance ;
				}
			}
			if( !exists )
				neighbours->at(i).routes.push_back( link( router2, router1, distance ) ) ;
		}
	}
}