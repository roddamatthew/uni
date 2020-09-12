#include "Individual.h"

#include <string>
#include <list>

using namespace std ;

Individual :: Individual() {}

Individual :: Individual( int length )
{
	binaryString = "";
	// Create a list zeroes of given length
	for( int i = 0 ; i < length ; i++)
	{
		binaryString += "0" ;
	}
}

Individual :: Individual( string code )
{
	// Create a list with values of the input string
	binaryString = code ;
}

string Individual :: getString()
{
	// Return the list as a string
	return binaryString ;
}

int Individual :: getBit( int pos )
{
	// Return the value of a bit at the input position
	if( pos < binaryString.length() && pos >= 0 )
	{
		return binaryString[ pos ] ;
	}
	else	// return -1 if outside of range
	{
		return - 1 ;
	}
}

void Individual :: flipBit( int pos )
{
	// Flip the value of the bit at the input position
	if( pos < binaryString.length() && pos >= 0 )
	{
		if( binaryString[ pos ] == '0' )
		{
			binaryString[ pos ] = '1' ;
		}
		else if( binaryString[ pos ] == '1' )
		{
			binaryString[ pos ] = '0' ;
		}
	}
}

int Individual :: getMaxOnes()
{
	// Return the length of the longest consecutive string of 1's
	int counter = 0 ;
	int max = 0 ;

	for( int i = 0; i < binaryString.length(); i++)
	{
		if( binaryString[ i ] == '1' ) counter++ ;
		if( counter > max ) max = counter ;
		if( binaryString[ i ] == '0' ) counter = 0;
	}

	return max ;
}

int Individual :: getLength()
{
	// Return the length of the list
	return binaryString.length() ;
}