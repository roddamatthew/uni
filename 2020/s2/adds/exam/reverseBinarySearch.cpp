#include "LinkedList.h"
#include "Node.h"
#include <iostream>

// This function was written by me duing revision for an ascending array. I made some changes to implement it for a descending array.
// The function uses many of the methods of the LinkedList class
// to compile this code a copy of my LinkedList and Node classes can be downloaded from SVN

// Summary of functions:
// getItem returns the data stored in the node at index i
// getLength returns the length of the list by calling link until reading a nullptr
// makeSublist returns a LinkedList* with all the elements from between the two input indices
// printItems prints each element of the list

// This function assumes that the input list is sorted in descending order
// The input parameter obj is being searched for
bool reverseBinarySearch( LinkedList* list, int obj )
{
	int length = list -> getLength() ;
	LinkedList* half ;

	// Base Case:
	// list is of length == 1
	if( length == 1 )
	{
		// If the final entry is equal to the obj parameter, then we found it
		if( list -> getItem( 1 ) == obj ) return true ; else
		return false ;
	}

	// Recursive case:
	// Check if obj would be contained in the upper half of the list
	if( list -> getItem( length / 2 ) > obj )
	{
		// new list contains top half of list
		half = list -> makeSublist( length / 2, length ) ;
	}
	else // assume obj is in the bottom half of the list
	{
		// new list contains bottom half of list
		half = list -> makeSublist( 0, length / 2 ) ;
	}

	// print the new list
	half -> printItems() ;

	// recursive call
	return reverseBinarySearch( half, obj ) ;
}

// Sample main for testing
int main()
{
	LinkedList* list = new LinkedList() ;

	for( int i = 10 ; i > 0 ; i-- )
	{
		list -> addEnd( i ) ;
	}

	reverseBinarySearch( list, 3 ) ;

	return 0 ;
}