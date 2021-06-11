#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "PoisonedReverse.h"

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

void printRoutingTableArray( vector<routingTable> *newRTs )
 /* Print any routingTable array
 * Can also be called with a size of 1 to print a single routingTable 
 */
{
	for( int i = 0 ; i < newRTs->size() ; i++ ) {
		cout << newRTs->at(i).name << ": " << endl ;
		for( int j = 0 ; j < newRTs->at(i).routes.size() ; j++ ) {
			cout << newRTs->at(i).routes.at(j).start << " " << newRTs->at(i).routes.at(j).end << " " ;
			if( newRTs->at(i).routes.at(j).distance >= INFINITE ) cout << "INF" << endl ; else
			if( newRTs->at(i).routes.at(j).distance < 0 ) cout << "-" << endl ; else
			cout << newRTs->at(i).routes.at(j).distance << endl ;
		}
		cout << endl ;
	}
}

int distance( vector<routingTable> *vec, string routerName, string firstHop, string destination )
/* Find the distance between two routers in a given table
 * Loop through the routes in the table and check if router names match
 * If they do, return the distance attribute
 * If the loop finishes without finding a link, return NO_LINK
 */
{
	for( int i = 0 ; i < vec->size() ; i++ ) {
		if( routerName == vec->at(i).name )
			for( int j = 0 ; j < vec->at(i).routes.size() ; j++ ) {
				if( vec->at(i).routes.at(j).start == firstHop 
					&& vec->at(i).routes.at(j).end == destination )
					return vec->at(i).routes.at(j).distance ;
			}
	}

	return NO_LINK ;
}

int distancePoison( vector<routingTable> *vec, string routerAsking, string routerName, string destination )
{
	if( routerName == destination ) return 0 ;

	for( int i = 0 ; i < vec->size() ; i++ ) {
		if( routerName == vec->at(i).name )
			for( int j = 0 ; j < vec->at(i).routes.size() ; j++ ) {
				if( vec->at(i).routes.at(j).end == destination ) {
					if( TRACE > 3 ) {
						cout << "Current routingTable is " << vec->at(i).name << endl ;
 						cout << "Looking for link between " << routerName << " and " << destination << endl ;
						cout << "Found link: From " <<  vec->at(i).name << " through " <<  vec->at(i).routes.at(j).start ;
						cout << " to " <<  vec->at(i).routes.at(j).end << " costing " <<  vec->at(i).routes.at(j).distance << endl ;
					}
					if( vec->at(i).routes.at(j).start == routerAsking ) return INFINITE ;
					return vec->at(i).routes.at(j).distance ;
				}
			}
	}

	return NO_LINK ;
}

void printDVs( vector<routingTable> *DVs, int iteration ) {
	for( int i = 0 ; i < DVs->size() ; i++ ) {
		cout << "router " << DVs->at(i).name << " at t=" << iteration << endl ;
		
		for( int j = 0 ; j < DVs->size() ; j++ ) {
			if( i != j )
				cout << "\t" << DVs->at(j).name ;
		}
		cout << endl ;

		for( int j = 0 ; j < DVs->size() ; j++ ) {
			if( i != j ) {
				cout << DVs->at(j).name ;
				for( int k = 0 ; k < DVs->size() ; k++ ) {
					if( i != k ) {
						// int d = distanceOneWay( names[j], names[i], array ) ;
						int d = distance( DVs, DVs->at(i).name, DVs->at(k).name, DVs->at(j).name ) ;

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
}

void calculateDVs( vector<routingTable> *DVs, vector<routingTable> *neighbours, vector<routingTable> *broadcast )
/* Calculate the distance vector for a given router */
{
	for( int i = 0 ; i < neighbours->size() ; i++ ) { /* loop over each router */
		DVs->push_back( routingTable() ) ;
		DVs->at(i).name = neighbours->at(i).name ;

		for( int j = 0 ; j < neighbours->size() ; j++ ) { /* loop over each first hop */
			if( i != j ) {
				int firstHopDistance = distance( neighbours, neighbours->at(i).name, neighbours->at(i).name, neighbours->at(j).name ) ;
				
				for( int k = 0 ; k < neighbours->size() ; k++ ) { /* loop over each final destination */ 
					if( i != k ) {
						int destinationHopDistance = distancePoison( broadcast, broadcast->at(i).name, broadcast->at(j).name, broadcast->at(k).name ) ;

						int totalDistance ;
						if( firstHopDistance == NO_LINK ) totalDistance = NO_LINK ;
						else totalDistance = firstHopDistance + destinationHopDistance ;

						if( TRACE > 2 ) {
							std::cout << neighbours->at(i).name << " -> " << neighbours->at(j).name << " -> " << neighbours->at(k).name << endl ;
							std::cout << firstHopDistance << " + " << destinationHopDistance << " = " << totalDistance << endl ;
						}

						DVs->at(i).routes.push_back( link( broadcast->at(j).name, broadcast->at(k).name, totalDistance ) ) ;
					}
				}
			}
		}
	}
}

void calculateRTs( vector<routingTable> *newRTs, vector<routingTable> *DVs )
/* Find the routing table from the distance vector table
 * Result is a routingTable with only names.size() links
 	* Each link is the shortest distance currently known from a router to each of its neighbours
 */
{
	for( int i = 0 ; i < DVs->size() ; i++ ) {
		newRTs->push_back( routingTable() ) ;
		newRTs->at(i).name = DVs->at(i).name ;

		for( int j = 0 ; j < DVs->size() ; j++ ) {
			int cost = INFINITE ;
			if( i == j ) cost = 0 ; 

			newRTs->at(i).routes.push_back( link( DVs->at(i).name, DVs->at(j).name, cost ) ) ;

			for( int k = 0 ; k < DVs->at(i).routes.size() ; k++ ) {
				if( newRTs->at(i).routes.at(j).end == DVs->at(i).routes.at(k).end
					&& newRTs->at(i).routes.at(j).distance > DVs->at(i).routes.at(k).distance
					&& DVs->at(i).routes.at(k).distance > 0 ) {
					newRTs->at(i).routes.at(j).distance = DVs->at(i).routes.at(k).distance ;
					newRTs->at(i).routes.at(j).start = DVs->at(i).routes.at(k).start ;
				}
			}
		}
	}
}

int updateBroadcast( vector<routingTable>* newRTs, vector<routingTable>* broadcast )
/* Update broadcast to have the latest routing distances
 */
{
	int count = 0 ;
	for( int i = 0 ; i < broadcast->size() ; i++ ) {
		for( int j = 0 ; j < broadcast->at(i).routes.size() ; j++ ) {
			/* if destinations match */
			/* and distance is less */
			/* update distance and first hop */
			if( newRTs->at(i).routes.at(j).end == broadcast->at(i).routes.at(j).end 
				&& newRTs->at(i).routes.at(j).distance != broadcast->at(i).routes.at(j).distance 
				&& newRTs->at(i).routes.at(j).distance > 0 ) {

				broadcast->at(i).routes.at(j).start = newRTs->at(i).routes.at(j).start ;
				broadcast->at(i).routes.at(j).distance = newRTs->at(i).routes.at(j).distance ;

				count++ ;
			}
		}
	}
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

void printBroadcast( vector<routingTable> *broadcast ) {
	for( int i = 0 ; i < broadcast->size() ; i++ ) {
		for( int j = 0 ; j < broadcast->at(i).routes.size() ; j++ ) {
			if( i != j ) {
				std::cout << "router " << broadcast->at(i).name << ": " << broadcast->at(j).name << " is " ;
				if( broadcast->at(i).routes.at(j).distance >= INFINITE ) std::cout << "unreachable" << std::endl ; else
				std::cout << broadcast->at(i).routes.at(j).distance << " routing through " << broadcast->at(i).routes.at(j).start << std::endl ;
			}
		}
	}
	std::cout << std::endl ;
}

bool compare( string a, string b ) {
	/* returns 1 if a is alphabetically less than b */
	/* otherwise returns zero */
	return a < b ;
}

vector<string> sortAlphabetically( vector<string> list )
{
	sort( list.begin(), list.end(), compare ) ;
	return list ;
}
