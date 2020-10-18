#include "Node.h"

Node :: Node()
{
	data = 0 ;
	next = 0 ;
}

Node :: Node( int i, Node* address)
{
	data = i ;
	next = address ;
}

int Node :: getData()
{
	return data ;
}

void Node :: setData( int i )
{
	data = i ;
}

Node* Node :: getNext()
{
	return next ;
}

void Node :: setNext( Node* address )
{
	next = address ;
}