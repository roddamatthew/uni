#include <iostream>
#include <string>

using namespace std ;

// Enumerate the 3 different states that an element may have
enum state { never_used, tombstone, occupied } ;

// Create a class for a hash table element
class Element {
    public:
    string value ;
    int state = never_used ; // Default state to never used
} ;

// Create a class for the whole hash table
class HashTable {
    private:
    Element* table ;
    int size ;
    
    public:
    HashTable( int size_ ) {
        size = size_ ;
        table = new Element[size_] ;
    } ;

    // Insert a new value into the hash table
    // If it is a duplicate, ignore it
    // If the position is already taken, check the next until an empty one is found
    int insert( string value ) {
        // Check for a duplicate insertion
        if( search( value ) != -1 ) return 0 ;

        // Key is the last character of the passed string
        char key = value.back() ;
        // Convert key to array index
        int index = key - 97 ; // Dangerous line!

        // Loop over the size of the hash table
        for( int k = 0 ; k < size ; k++ ) {
            // Check for an unnoccupied element
            if( table[index].state != occupied ) {
                // Fill the element
                table[index].value = value ;
                table[index].state = occupied ;
                return 0 ;
            }
            // Otherwise try the next element, remembering to wrap
            index = ( index + 1 ) % size ;
        }
        cout << "Insertion failed! Could not find an unoccupied element in table" << endl ;
        return 1 ;
    } ;

    int remove( string value ) {
        int index = search( value ) ;
        
        // If the search did not find the value, we're done
        if( index == -1 ) return 0 ;
        else table[index].state = tombstone ;
        
        return 0 ;
    } ;

    int search( string value ) {
        // Key is the last character of the passed string
        char key = value.back() ;
        int index = key - 97 ; // Dangerous line!

        for( int k = 0 ; k < size ; k++ ) {
            if( table[index].value == value ) return index ;
            else index = ( index + 1 ) % size ;
        }

        return -1 ;
    }

    void print() {
        for( int i = 0 ; i < size ; i++ ) {
            if( table[i].state == occupied )
                cout << table[i].value << " " ;
        }
        cout << endl ;
        return ;
    }
} ;

int main() {
    HashTable table = HashTable( 26 ) ;

    string input ;

    while( cin >> input ) {
        switch( input[0] ) {
            case 'A':
                table.insert( input.substr( 1 ) ) ;
                break ;

            case 'D':
                table.remove( input.substr( 1 ) ) ;
                break ;
            
            default:
                cout << "Unexpected input, please try again" << endl ;
                break ;
        }
    }

    table.print() ;
    return 0 ;
}