#ifndef NODE_H
#define NODE_H

class Node
{
private:
	int data ;
	Node* next ;
public:
	Node() ;
	Node( int i, Node* address ) ;
	int getData() ;
	void setData( int i ) ;
	Node* getNext() ;
	void setNext( Node* address ) ;
} ;
#endif //NODE_H