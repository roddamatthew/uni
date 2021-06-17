#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "PoisonedReverse.h"

/* Data Structures:
 - names: vector<string> containing all the router names in alphabetical order

 - neighbours: Vector of routingTables. 
 		- Elements ordered alphabetically by name
 		- Each element has a name attribute which is the name of the router
 		- Each element also has a vector of links which are the given links to this routers neighbours

 - broadcast: Vector of routingTables.
 		- Elements ordered alphabetically by name

 		- Each element's name attribute is the name of that router

 		- Each element's routes attribute contains its lowest cost trip to each other router
 			- The start attribute of a link is the first hop
 			- The end attribute of a link is the destination
 			- The distance attribute is the total cost associated with the trip
 */

void printRoutingTableArray( vector<routingTable> *newRTs )
 /* Print any routingTable vector
  * Loop over the vector
  * Prints the name of the router then any links stored in it
  * Used for debugging as tables are not in the expected output form for the automarker
  */
{
	for( int i = 0 ; i < newRTs->size() ; i++ ) {
		/* print name of routing table */
		cout << newRTs->at(i).name << ": " << endl ;

		for( int j = 0 ; j < newRTs->at(i).routes.size() ; j++ ) {
			/* Print start, end and cost of each link */
			cout << newRTs->at(i).routes.at(j).start << " " << newRTs->at(i).routes.at(j).end << " " ;

			/* Print special characters for infinite and no link cases */
			if( newRTs->at(i).routes.at(j).distance >= INFINITE ) cout << "INF" << endl ; else
			if( newRTs->at(i).routes.at(j).distance < 0 ) cout << "-" << endl ; else

			/* Otherwise just print the distance */
			cout << newRTs->at(i).routes.at(j).distance << endl ;
		}
		cout << endl ;
	}
}

int distance( vector<routingTable> *vec, string routerName, string firstHop, string destination )
/* Find the distance between two routers in a given table
 * Loop through the links in each and check if router names match
 * If they do, return the distance attribute
 * If the loop finishes without finding a link, return NO_LINK
 * This function is used for the broadcast vector as the first hop matters
 */
{
	for( int i = 0 ; i < vec->size() ; i++ ) {
		/* Check if the name of the routingTable matches */
		if( routerName == vec->at(i).name )
			for( int j = 0 ; j < vec->at(i).routes.size() ; j++ ) {
				/* Check if the names of the link's start and end match */
				if( vec->at(i).routes.at(j).start == firstHop 
					&& vec->at(i).routes.at(j).end == destination )
					return vec->at(i).routes.at(j).distance ;
			}
	}

	return NO_LINK ;
}

int distancePoison( vector<routingTable> *vec, string routerAsking, string routerName, string destination )
/* Find the distance between routers with poisoning
 * Search for the correct link as normal
 * Then check if the first hop of the link found matches the name of the routing asking for the link
 * If they do match, return an INFINITE distance
 * Otherwise return the distance as normal
 */
{
	if( routerName == destination ) return 0 ;

	for( int i = 0 ; i < vec->size() ; i++ ) {
		/* Check if the name of the routingTable matches */
		if( routerName == vec->at(i).name )
			for( int j = 0 ; j < vec->at(i).routes.size() ; j++ ) {
				/* Check if the destination of the current link matches */
				if( vec->at(i).routes.at(j).end == destination ) {

					if( TRACE > 3 ) {
						cout << "Current routingTable is " << vec->at(i).name << endl ;
 						cout << "Looking for link between " << routerName << " and " << destination << endl ;
						cout << "Found link: From " <<  vec->at(i).name << " through " <<  vec->at(i).routes.at(j).start ;
						cout << " to " <<  vec->at(i).routes.at(j).end << " costing " <<  vec->at(i).routes.at(j).distance << endl ;
					}

					/* If the first hop matches the name of the router asking, poison the route */
					if( vec->at(i).routes.at(j).start == routerAsking ) return INFINITE ;

					/* Otherwise return the true distance */
					return vec->at(i).routes.at(j).distance ;
				}
			}
	}

	return NO_LINK ;
}

void printDVs( vector<routingTable> *DVs, int iteration )
/* Print distance vectors in the desired form
 * Print each router name across and row and column
 * Then fill in each of the elements by searching for the distance of the matching link
 
 * eg. 	router A at t=4
			B 	C
		B   2 	3
		C  	6 	5

 * Don't print links to the router that owns the table (these are always 0)
 */
{
	for( int i = 0 ; i < DVs->size() ; i++ ) {
		/* Print the router name and iteration number */
		cout << "router " << DVs->at(i).name << " at t=" << iteration << endl ;
		
		/* Print the top row of router names */
		for( int j = 0 ; j < DVs->size() ; j++ ) {
			if( i != j ) /* skip the router that owns the table */
				cout << "\t" << DVs->at(j).name ;
		}
		cout << endl ;

		for( int j = 0 ; j < DVs->size() ; j++ ) {
			if( i != j ) { /* skip the router that owns the table */
				cout << DVs->at(j).name ; /* Print the row name */
				for( int k = 0 ; k < DVs->size() ; k++ ) {
					if( i != k ) { /* skip the router that owns the table */
						
						/* Get the distance from:
						 * Router that owns the table
						 * To the column router
						 * To the row router */
						int d = distance( DVs, DVs->at(i).name, DVs->at(k).name, DVs->at(j).name ) ;

						cout << "\t" ;
						/* Replace the distance with special characters in certain cases */
						if( d >= INFINITE ) cout << "INF" ; else 
						if( d < 0 ) cout << "-" ; else
						/* Otherwise just print the distance */
						cout << d ;
					}
				}
				cout << endl ;
			}
		}
		cout << endl ;
	}
}

void calculateDVs( vector<routingTable> *DVs, vector<routingTable> *neighbours, vector<routingTable> *broadcast )
/* Calculate the distance vector for a given router
 * Find the distance from each router to each other router, through all possible first hops
 * Use the neighbours vector for the first hop distance
 * Use the broadcast vector for the remaining trip distance, this time with poisoning
 * Assumes that *DVs is a pointer to an empty vector
 */
{
	for( int i = 0 ; i < neighbours->size() ; i++ ) { /* loop over each router */
		/* Add a new routingTable to the vector and assign its name */
		DVs->push_back( routingTable() ) ;
		DVs->at(i).name = neighbours->at(i).name ;

		for( int j = 0 ; j < neighbours->size() ; j++ ) { /* loop over each first hop */
			if( i != j ) {
				/* Find the first hop distance from the neighbours array */
				/* Sanity check that the first hop and table name match, but these should always match */
				int firstHopDistance = distance( neighbours, neighbours->at(i).name, neighbours->at(i).name, neighbours->at(j).name ) ;
				
				for( int k = 0 ; k < neighbours->size() ; k++ ) { /* loop over each final destination */ 
					if( i != k ) {
						/* Find the remaining distance from the broadcast array */
						/* Pass the first hop name, so we can check if we need to poison */
						int destinationHopDistance = distancePoison( broadcast, broadcast->at(i).name, broadcast->at(j).name, broadcast->at(k).name ) ;

						/* Calculate the total distance of the trip */
						int totalDistance ;
						if( firstHopDistance == NO_LINK ) totalDistance = NO_LINK ;
						else totalDistance = firstHopDistance + destinationHopDistance ;

						/* Print what's happening for debugging */
						if( TRACE > 2 ) {
							std::cout << neighbours->at(i).name << " -> " << neighbours->at(j).name << " -> " << neighbours->at(k).name << endl ;
							std::cout << firstHopDistance << " + " << destinationHopDistance << " = " << totalDistance << endl ;
						}

						/* Add the new link to the current routing table */
						DVs->at(i).routes.push_back( link( broadcast->at(j).name, broadcast->at(k).name, totalDistance ) ) ;
					}
				}
			}
		}
	}
}

void calculateRTs( vector<routingTable> *newRTs, vector<routingTable> *DVs )
/* Find the routing table from the distance vector table
 * Loop over the distance vectors
 * Starting at infinity, update the cost whenever a lower cost to the same destination is found
 * Assumes that *newRTs is a pointer to an empty vector
 */
{
	for( int i = 0 ; i < DVs->size() ; i++ ) {
		/* Add a new routingTable to the vector and assign its' name */
		newRTs->push_back( routingTable() ) ;
		newRTs->at(i).name = DVs->at(i).name ;

		for( int j = 0 ; j < DVs->size() ; j++ ) {
			int cost = INFINITE ;
			if( i == j ) cost = 0 ; /* Distance from a router to itself is always zero */

			/* Add a new route with a starting cost which we will iteratively lower */
			newRTs->at(i).routes.push_back( link( DVs->at(i).name, DVs->at(j).name, cost ) ) ;

			for( int k = 0 ; k < DVs->at(i).routes.size() ; k++ ) {
				/* Check if the destinations match and that the distance is lower, but still greater than 0 */
				if( newRTs->at(i).routes.at(j).end == DVs->at(i).routes.at(k).end
					&& newRTs->at(i).routes.at(j).distance > DVs->at(i).routes.at(k).distance
					&& DVs->at(i).routes.at(k).distance > 0 ) 
				{
					/* If the distance is lower, update the link with the new distance */
					newRTs->at(i).routes.at(j).distance = DVs->at(i).routes.at(k).distance ;
					newRTs->at(i).routes.at(j).start = DVs->at(i).routes.at(k).start ;
				}
			}
		}
	}
}

int updateBroadcast( vector<routingTable>* newRTs, vector<routingTable>* broadcast )
/* Update broadcast to have the latest routing distances
 * This is similar to calculateRTs in functionality but doesn't create new links
 * Check if routes from the same start to the same destination have a lower value in the newRTs vector
 * If newRTs is lower, update broadcast and increment a counter
 * Once we're done, return the counter to check if anything has changed this iteration
 */
{
	/* Initialize counter */
	int count = 0 ;
	for( int i = 0 ; i < broadcast->size() ; i++ ) {
		for( int j = 0 ; j < broadcast->at(i).routes.size() ; j++ ) {
			/* if destinations match */
			/* and distance is less */
			/* update distance and first hop */
			if( newRTs->at(i).routes.at(j).end == broadcast->at(i).routes.at(j).end 
				&& newRTs->at(i).routes.at(j).distance != broadcast->at(i).routes.at(j).distance 
				&& newRTs->at(i).routes.at(j).distance > 0 ) {

				/* Update the firstHop (important for poisoned reverse) and distance */
				broadcast->at(i).routes.at(j).start = newRTs->at(i).routes.at(j).start ;
				broadcast->at(i).routes.at(j).distance = newRTs->at(i).routes.at(j).distance ;

				/* We've changed a link, so increment our counter */
				count++ ;
			}
		}
	}

	/* Return the number of changed links */
	return count ;
}

void addNeighbour( vector<routingTable> *neighbours, string router1, string router2, int distance )
/* Add a link to the neighbour array
 * Links are always added to both tables
 * If the link already exists, only update the distance
 */
{
	for( int i = 0 ; i < neighbours->size() ; i++ ) {
		if( neighbours->at(i).name == router1 ) { /* find the right routingTable */
			bool exists = false ; /* Assume the link does not exist */

			for( int j = 0 ; j < neighbours->at(i).routes.size() ; j++ ) { /* check if the route already exists */
				if( neighbours->at(i).routes.at(j).end == router2 ) {
					exists = true ;
					neighbours->at(i).routes.at(j).distance = distance ;
				}
			}

			/* If the route did not exist yet, add a new link */
			if( !exists ) 
				neighbours->at(i).routes.push_back( link( router1, router2, distance ) ) ;
		}

		/* Repeat the process for the other routingTable */
		if( neighbours->at(i).name == router2 ) { /* find the right routingTable */
			bool exists = false ; /* Assume the link does not exist */

			for( int j = 0 ; j < neighbours->at(i).routes.size() ; j++ ) { /* check if the route already exists */
				if( neighbours->at(i).routes.at(j).end == router1 ) {
					/* If it does exist, update the distance */
					exists = true ;
					neighbours->at(i).routes.at(j).distance = distance ;
				}
			}

			/* If the route did not exist yet, add a new link */
			if( !exists )
				neighbours->at(i).routes.push_back( link( router2, router1, distance ) ) ;
		}
	}
}

void printBroadcast( vector<routingTable> *broadcast )
/* Print the final routing information once the algorithm finishes
 * Make output of the expected form of websubmission
 */
{
	for( int i = 0 ; i < broadcast->size() ; i++ ) {
		for( int j = 0 ; j < broadcast->at(i).routes.size() ; j++ ) {
			if( i != j ) { /* Skip routes from a router to itself */
				/* Print the name of the start and first hop routers, then the total distance of the link */
				std::cout << "router " << broadcast->at(i).name << ": " << broadcast->at(j).name << " is " ;
				if( broadcast->at(i).routes.at(j).distance >= INFINITE ) std::cout << "unreachable" << std::endl ; else
				std::cout << broadcast->at(i).routes.at(j).distance << " routing through " << broadcast->at(i).routes.at(j).start << std::endl ;
			}
		}
	}
	std::cout << std::endl ;
}

/* Alphabetical sorting functions: */
bool compare( string a, string b )
/* Check if a is alphabetically less than b
 * If a is less, return true
 * Otherwise return false
 */
{
	return a < b ;
}

vector<string> sortAlphabetically( vector<string> list )
/* Using the vector sort function: 
 * call compare on each element until the vector is sorted
 */
{
	sort( list.begin(), list.end(), compare ) ;
	return list ;
}
