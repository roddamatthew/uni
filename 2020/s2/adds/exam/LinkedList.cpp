#include "Node.h"
#include "LinkedList.h"

#include <iostream>

LinkedList :: LinkedList()
{
	head = nullptr ;
}

LinkedList :: LinkedList( int* array, int size )
{
	for( int i = 0 ; i < size ; i++ )
	{
		Node* newNode = new Node( array[ i ], head ) ;
		head = newNode ;
	}
}

// Add a new node to the front of the list containing newItem
void LinkedList :: addFront( int newItem )
{
	Node* newFront = new Node( newItem, head ) ;
	head = newFront ;
}

// Add a new node to the end of the list containing newItem
void LinkedList :: addEnd( int newItem )
{
	// Create a new end node
	Node* newEnd = new Node( newItem, nullptr ) ;

	// Access the node at the start of the list
	Node* currentNode = head ;

	if( head == nullptr ) addFront( newItem ) ;
	else
	{
		// Read through the nodes until reaching the tail
		while( currentNode -> getNext() != nullptr )
		{
			currentNode = currentNode -> getNext() ;
		}

		currentNode -> setNext( newEnd ) ;
	}
}

void LinkedList :: addAtPosition( int position, int newItem )
{
	Node* newNode = new Node( newItem, nullptr ) ;
	Node* currentNode = head ;

	if( position == 1 ) addFront( newItem ) ;
	else
	{
		for( int i = 2 ; i < position ; i++ )
		{
			currentNode = currentNode -> getNext() ;
		}

		newNode -> setNext( currentNode -> getNext() );
		currentNode -> setNext( newNode ) ;
	}
}

int LinkedList :: search( int item )
{
	int i = 1 ;
	Node* currentNode = head ;

	while( currentNode != nullptr )
	{
		if( currentNode -> getData() == item )
		{
			std::cout << i << " " ;
			return i ;
		}
		else
		{
			currentNode = currentNode -> getNext() ;
			i++ ;
		}
	}

	std::cout << "0 " ;
	return 0 ;
}

void LinkedList :: deleteFront()
{
	head = head -> getNext() ;
}

void LinkedList :: deleteEnd()
{
	Node* currentNode = head ;
	Node* nextNode = currentNode -> getNext() ;

	while( nextNode -> getNext() != nullptr )
	{
		currentNode = currentNode -> getNext() ;
		nextNode = currentNode -> getNext() ;
	}

	currentNode -> setNext( nullptr ) ;
}

void LinkedList :: deletePosition( int position )
{
	Node* currentNode = head ;
	Node* nodeBeforePosition = currentNode ;

	for( int i = 1 ; i < position ; i++ )
	{
		nodeBeforePosition = currentNode ;
		currentNode = currentNode -> getNext() ;
	}

	Node* nodeAfterPosition = currentNode -> getNext() ;
	nodeBeforePosition -> setNext( nodeAfterPosition ) ;
}

int LinkedList :: getItem( int position )
{
	Node* currentNode = head ;

	for( int i = 1 ; i < position ; i++ )
	{
		if( currentNode -> getNext() == nullptr )
		{
			std::cout << "Tried call getItem() with index greater than list length" << std::endl ;
			return 0 ;
		}
		else
		{
			currentNode = currentNode -> getNext() ;
		}
	}

	return currentNode -> getData() ;
}

void LinkedList :: printItems()
{
	// Access the node at the start of the list
	Node* currentNode = head ;
	int i = 0 ;

	// Read through the nodes until reaching the tail
	while( currentNode != nullptr )
	{
		std::cout << currentNode -> getData() << " " ;
		currentNode = currentNode -> getNext() ;
		i++ ;
	}

	std::cout << std::endl ;
}

int LinkedList :: getLength()
{
	int length = 0 ;
	Node* currentNode = head ;
	if( head != nullptr ) length++ ;

	// Read through the nodes until reaching the tail
	while( currentNode -> getNext() != nullptr )
	{
		currentNode = currentNode -> getNext() ;
		length++ ;
	}

	return length ;
}

LinkedList* LinkedList :: makeSublist( int start, int end )
{
	LinkedList* newList = new LinkedList() ;

	for( int i = start + 1 ; i < end + 1 ; i++ )
	{
		newList -> addEnd( getItem( i ) ) ;
	}

	return newList ;
}