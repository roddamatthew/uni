#include <iostream>
#include <string.h>
#include <stdlib.h>

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

static Node *root = NULL ;

void prePrint( Node *start )
{
    if( start == NULL ) return ;
    cout << start -> value << " " ;
    prePrint( start -> lower ) ;
    prePrint( start -> upper ) ;
}

void postPrint( Node *start )
{
    if( start == NULL ) return ;
    postPrint( start -> lower ) ;
    postPrint( start -> upper ) ;
    cout << start -> value << " " ;
}

void inorderPrint( Node *start )
{
    if( start == NULL ) return ;
    inorderPrint( start -> lower ) ;
    cout << start -> value << " " ;
    inorderPrint( start -> upper ) ;
}

/* Perform a right rotation about node 'start' */
Node *rightRotation( Node* start ) {
    /* lower of start becomes new subtree head */
    Node *newstart = start -> lower ;
    /* swap new subtree upper with original subtree lower */
    start -> lower = newstart -> upper ;
    /* new subtree upper becomes original subtree head */
    newstart -> upper = start ;

    return newstart ;
}

/* Perform a left rotation about node 'start' */
Node *leftRotation( Node* start ) {
    /* upper of start becomes new subtree head */
    Node *newstart = start -> upper ;
    /* swap new subtree lower with original subtree upper */
    start -> upper = newstart -> lower ;
    /* new subtree lower becomes original subtree head */
    newstart -> lower = start ;

    return newstart ;
}

int getHeight( Node *node ) 
{
    if( node == NULL ) return 0 ;
    return max( getHeight( node -> lower ), getHeight( node -> upper ) ) + 1 ;
}

int getBalance( Node *node )
{
    if( node == NULL ) return 0 ;
    return getHeight( node -> lower ) - getHeight( node -> upper ) ;
}

Node *insert( Node *start, int value )
{
    /* If subtree is empty, add new node */
    if( start == NULL ) {
        Node *temp = new Node( value ) ;
        return temp ;
    }

    /* Recursively search sides of tree */
    if( value < start -> value ) start -> lower = insert( start -> lower, value ) ; else
    if( value > start -> value ) start -> upper = insert( start -> upper, value ) ; else
    return start ;

    /* Find the balanace of the tree */
    int balance = getBalance( start ) ;

    if( balance > 1 ) { // Left case
        if( value < start -> lower -> value ) { // Left case
            return rightRotation( start ) ;
        }
        else if ( value > start -> lower -> value ) // Right case
        {
            start -> lower = leftRotation( start -> lower ) ;
            return rightRotation( start ) ;
        }
    }
    if( balance < -1 ) { // Right case
        if( value > start -> upper -> value ) { // Right case
            return leftRotation( start ) ;
        }
        else if ( value < start -> upper -> value ) // Left case
        {
            start -> upper = rightRotation( start -> upper ) ;
            return leftRotation( start ) ;
        }
    }

    return start ;
}

Node *remove( Node *start, int value )
{
    /* Check if we've reached the end of the tree */
    if( start == NULL ) return NULL ;
    /* Recursively call down tree until the right node is found */
    if( value < start -> value )
        start -> lower = remove( start -> lower, value ) ; else
    if( value > start -> value )
        start -> upper = remove( start -> upper, value ) ;
    else { /* Current node has value we want to delete */
        Node *lower = start -> lower ;
        Node *upper = start -> upper ;

        /* If the deleted node has one or fewer children, replace it with the child */
        if( upper == NULL ) {
            delete start ;
            start = lower ;
        }
        else if( lower == NULL ) {
            delete start ;
            start = upper ;
        }
        else { /* Deleted node has two children */
            /* Delete largest left descendant */
            while( lower -> upper != NULL ) lower = lower -> upper ;
            start -> value = lower -> value ;
            start -> lower = remove( start -> lower, lower -> value ) ;
        }
    }
    if( start == NULL ) return start ; /* If there was no children we don't need to balance */

	/* Find the balance of the tree */
    int balance = getBalance( start ) ;

    // Left left case:
    if( balance > 1 && getBalance( start -> lower ) >= 0 && start -> lower != NULL ){
        return rightRotation( start ) ;
    }
    // Left right case:
    else if( balance > 1 && getBalance( start -> lower ) < 0 ) {
        start -> lower = leftRotation( start -> lower ) ;
        return rightRotation( start ) ;
    }
    // Right right case:
    else if( balance < -1 && getBalance( start -> upper ) <= 0 && start -> upper != NULL ) {
        return leftRotation( start ) ;
    }
    // Right left case:
    else if( balance < -1 && getBalance( start -> upper ) > 0 ) {
        start -> upper = rightRotation( start -> upper ) ;
        return leftRotation( start ) ;
    }

    return start ;
}

int main() 
{
    /* Read input from command line */
    char *token ;
    char input[410] ;
    fgets( input, 410, stdin ) ;

    token = strtok( input, " " ) ;
    while( token != NULL )
    {
        if( token[0] == 'A' ) {
            root = insert( root, atoi( token + 1 ) ) ;
        }
        else if( token[0] == 'D' ) {
            root = remove( root, atoi( token + 1 ) ) ;
        }
        else if( strncmp( token, "PRE", 3 ) == 0 ) {
            if( root == NULL ) cout << "EMPTY" << endl ; else
            prePrint( root ) ;
        }
        else if( strncmp( token, "POST", 4 ) == 0 ) {
            if( root == NULL ) cout << "EMPTY" << endl ; else
            postPrint( root ) ;
        }
        else if( strncmp( token, "IN", 2 ) == 0 ) {
            if( root == NULL ) cout << "EMPTY" << endl ; else
            inorderPrint( root ) ;
        }
        token = strtok( NULL, " \n" ) ;
    }

    return 0 ;
}