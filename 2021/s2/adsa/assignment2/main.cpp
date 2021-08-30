#include <iostream>

using namespace std ;

class Node {
    public:
    int value ;
    Node *lower ;
    Node *upper ;
    Node( int n ) {
        value = n ;
        lower = NULL ;
        upper = NULL ;
    }
} ;

/* Perform a right rotation about node 'start' */
Node *rightRotation( Node* start ) {
    /* lower of start becomes new subtree head */
    Node *newstart = start -> lower ;
    /* new subtree upper becomes original subtree head */
    newstart -> upper = start ;
    /* swap new subtree upper with original subtree lower */
    start -> lower = newstart -> upper ;

    return newstart ;
}

/* Perform a left rotation about node 'start' */
Node *leftRotation( Node* start ) {
    /* upper of start becomes new subtree head */
    Node *newstart = start -> upper ;
    /* new subtree lower becomes original subtree head */
    newstart -> lower = start ;
    /* swap new subtree lower with original subtree upper */
    start -> upper = newstart -> lower ;

    return newstart ;
}

/* 
    Traverses tree, returning pointer to Node with value == n
    If nothing found, return NULL
 */
Node *search( Node *start, int n )
{
    /* If searching empty Node, return NULLPTR */
    if( start == NULL ) return NULL ;

    /* Get the current nodes value */
    int value = start -> value ;

    /* Test if we've found the search value */
    if( n == value ) return start ;

    /* Otherwise keep going down the tree*/
    if( value < n ) return search( start -> upper, n ) ;
    if( value > n ) return search( start -> lower, n ) ;
}

int getHeight( Node *node ) 
{
    if( node == NULL ) return 0 ;
    return max( getHeight( node -> lower ), getHeight( node -> upper ) ) + 1 ;
}

Node *insert( Node *start, int value )
{
    /* If subtree is empty, add new node */
    if( start == NULL ) {
        Node *temp = new Node( value ) ;
        return temp ;
    }
    /* Recursively search sides of tree */
    if( value < start -> value ) start = insert( start -> lower, value ) ; else
    if( value > start -> value ) start = insert( start -> upper, value ) ;

    /* Find the balanace of the tree */
    int balance = getHeight( start -> lower ) - getHeight( start -> upper ) ;

    if( balance > 1 ) { /* If lower side is unbalanced */
        if( value < start -> lower -> value )
            return rightRotation( start ) ;
        else {
            /* LR Rotation */
            start -> lower = leftRotation( start -> lower ) ;
            return rightRotation( start ) ;
        }
    }
    else if( balance < -1 ) {
        if( value > start -> upper -> value )
            return leftRotation( start ) ;
        else {
            /* RL Rotation */
            start -> upper = rightRotation( start -> upper ) ;
            return leftRotation( start ) ;
        }
    }

    return start ;
}

void prePrint( Node *start )
{
    if( start == NULL ) return ;
    cout << start -> value << " " ;
    prePrint( start -> lower ) ;
    prePrint( start -> upper ) ;
}

void inorderPrint( Node *start )
{
    if( start == NULL ) return ;
    inorderPrint( start -> lower ) ;
    cout << start -> value << " " ;
    inorderPrint( start -> upper ) ;
}

int main() 
{
    Node *node1 = new Node( 1 ) ;
    Node *node2 = new Node( 2 ) ;
    Node *node3 = new Node( 3 ) ;

    node2 -> lower = node1 ;
    node2 -> upper = node3 ;

    prePrint( node1 ) ;

    return 0 ;
}