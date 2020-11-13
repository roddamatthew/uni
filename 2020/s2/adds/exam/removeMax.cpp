// a ) Doubly linked list, function removes the largest value.

#include <iostream> //include for nullptr
#include "LinkedList.h"
#include "Node.h"

// Assume that the doubly linked list has member variables:
// int data ;
// Node* linkForward ;
// Node* linkBack ;
// And that these variables can be set using member functions or are public

void removeMax()
{
	int max = 0 ;
	int maxIndex = 0 ;
	int i = 0 ;
	Node* currentNode = head ;

	// Iterate through the whole list
	while( currentNode != nullptr )
	{
		// If the current element is larger than the current max, update it
		if( currentNode -> getData() > max )
		{
			max = currentNode -> getData() ;
			// Also keep track of what index it was stored at
			maxIndex = i ;
		}
		// Read the next node
		currentNode = currentNode -> getNext() ;
		// incremenet index
		i++ ;
	}

	currentNode = head ;
	i = 0 ;
	// Remove the element at maxIndex
	while( currentNode != nullptr && i <= maxIndex )
	{
		// Remove the node if it is the max
		if( i == maxIndex )
		{
			Node* previousNode = currentNode -> getLast() ;

			// Make last node point to the next node
			previousNode -> linkForward = currentNode -> getNext() ;

			// Call destructor on currentNode
			currentNode -> ~Node() ;
		}
		// Otherwise access the next node
		currentNode = currentNode -> getNext() ;
		// incremenet index
		i++ ;
	}
}

// b ) Tight upper bound on worst case runtime:
// worst case runtime when max is the last element of the list in which case:
// Finding the max is O(n)
// Looping back to the max is O(n)
// Removing the max is O(1)
// Tight upper bound = O(n) + O(n) + O(1) = O(n)