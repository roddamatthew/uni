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
    prePrint( start -> lower ) ;
    prePrint( start -> upper ) ;
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

Node *balance( Node *start, int value ) {
    /* Find the balanace of the tree */
    int balance = getHeight( start -> lower ) - getHeight( start -> upper ) ;
    // cout << "After adding: " << value << " balance is: " << balance << endl ;
    // cout << "Shouldn't be zero: " << start << " with value: " << start -> value << endl ;
    // cout << "Lower subtree height is: " << getHeight( start -> lower ) << endl ;
    // cout << "Upper subtree height is: " << getHeight( start -> upper ) << endl ;

    if( balance > 1 ) { /* If lower side is unbalanced */
        if( value < start -> lower -> value ){
            // cout << "R Rotation" << endl ;
            return rightRotation( start ) ;
        }
        else {
            /* LR Rotation */
            // cout << "LR Rotation" << endl ;
            start -> lower = leftRotation( start -> lower ) ;
            return rightRotation( start ) ;
        }
    }
    else if( balance < -1 ) {
        if( value > start -> upper -> value ){
            // cout << "L Rotation" << endl ;
            return leftRotation( start ) ;
        }
        else {
            /* RL Rotation */
            // cout << "RL Rotation" << endl ;
            start -> upper = rightRotation( start -> upper ) ;
            return leftRotation( start ) ;
        }
    }

    return start ;
}

Node *insert( Node *start, int value )
{
    /* If subtree is empty, add new node */
    if( start == NULL ) {
        // cout << "Created new node storing: " << value << endl ;
        Node *temp = new Node( value ) ;
        return temp ;
    }

    /* Recursively search sides of tree */
    if( value < start -> value ) start -> lower = insert( start -> lower, value ) ; else
    if( value > start -> value ) start -> upper = insert( start -> upper, value ) ;

    start = balance( start, value ) ;

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
            delete( start ) ;
            start = lower ;
        }
        else if( lower == NULL ) {
            delete( start ) ;
            start = upper ;
        }
        else { /* Deleted node has two children */
            /* Delete left most child on right side */
            while( upper -> lower != NULL ) upper = upper -> lower ;
            start -> value = upper -> value ;
            start -> upper = remove( start -> upper, upper -> value ) ;
        }
    }
    if( start == NULL ) return start ; /* If there was no children we don't need to balance */

    start = balance( start, value ) ;
    
    return start ;
}

int main() 
{
    Node *root = NULL ;
    /* Read input from command line */
    char *token ;
    char input[410] ;
    fgets( input, 410, stdin ) ;

    token = strtok( input, " " ) ;
    while( token != NULL )
    {
        // cout << token ;
        // cout << root -> value << endl ;
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