#include "Individual.h"

#include <string>
#include <list>

using namespace std ;

Individual :: Individual() {}

Individual :: Individual( int length )
{
	// Create a list zeroes of given length
	for( int i = 0 ; i < length ; i++)
	{
		binaryString.push_back( 0 ) ;
	}
}

Individual :: Individual( string code )
{
	// Create a list with values of the input string
	for( int i = 0 ; i < code.length() ; i++ )
	{
		binaryString.push_back( (char) code[ i ] ) ;
	}
}

string Individual :: getString()
{
	// Return the list as a string
	string str = "";
	list<int> :: iterator it = binaryString.begin() ;

	for( int i = 0; i < binaryString.size() ; i++ )
	{
		str += *it ;
		advance( it, 1 ) ;
	}

	return str ;
}

int Individual :: getBit( int pos )
{
	// Return the value of a bit at the input position
	if( pos < binaryString.size() && pos >= 0 )
	{
		list<int> :: iterator it = binaryString.begin() ;
		advance( it, pos ) ;

		return *it ;
	}
	else	// return -1 if outside of range
	{
		return - 1 ;
	}
}

void Individual :: flipBit( int pos )
{
	// Flip the value of the bit at the input position
	if( pos < binaryString.size() && pos >= 0 )
	{
		list<int> :: iterator it = binaryString.begin() ;
		advance( it, pos ) ;

		if( (char) *it == '0' )
		{
			binaryString.erase( it ) ;
			// insert 1
		}
		else if( (char) *it == '1' )
		{
			binaryString.erase( it ) ;
			// insert 0
		}
	}
}

int Individual :: getMaxOnes()
{
	// Return the length of the longest consecutive string of 1's
	return 0 ;
}

int Individual :: getLength()
{
	// Return the length of the list
	return binaryString.size() ;
}