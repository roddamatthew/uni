#include "Node.h"
#include "LinkedList.h"

#include <iostream>
#include <string>

using namespace std ;

int main()
{
	string input ;
	getline(cin, input);

	// Parameters initiliasization
	string initial = "" ;
	string integers = "" ;
	int array[100] ;
	int size = 0 ;
	string parameter1 = "" ;
	string parameter2 = "" ;
	int param1 ;
	int param2 ;
	int i = 0 ;

	// split input into integers, initial and parameters strings for processing
	while( input[i] <= '9' )
	{
		integers += input[i] ;
		i++ ;
	}

	while( input[i] > '9' )
	{
		initial += input[i] ;
		i++ ;
	}

	i++ ;

	while( input[i] != ' ' && i < input.length() )
	{
		parameter1 += input[i] ;
		i++ ;
	}

	i++ ;

	while( input[i] != ' ' && i < input.length() )
	{
		parameter2 += input[i] ;
		i++ ;
	}	

	param1 = stoi( parameter1 ) ;
	param2 = stoi( parameter2 ) ;

	string currentNumber ;

	for( i = 0; i < integers.length(); i++ )
	{
		if( integers[i] >= '0' && integers[i] <= '9' ) currentNumber += integers[i] ; else
		if( integers[i] == ' ' )
		{
			array[ size ] = stoi( currentNumber ) ;
			size++ ;
			currentNumber = "" ;
		}
	}

	// reverse order of elements in array
	int reversedArray[100] ;
	int j = 0 ;

	for( i = size - 1 ; i >= 0 ; i-- )
	{
		reversedArray[j] = array[i] ;
		j++ ;
	}

	LinkedList list = LinkedList( reversedArray, size );

	if( initial == "AF") list.addFront( param1 ) ; else
	if( initial == "AE") list.addEnd( param1 ) ;  else
	if( initial == "AP") list.addAtPosition( param1, param2 ) ;  else
	if( initial == "S") list.search( param1 ) ;  else
	if( initial == "DF") list.deleteFront() ;  else
	if( initial == "DE") list.deleteEnd() ;  else
	if( initial == "DP") list.deletePosition( param1 ) ;  else
	if( initial == "GI") list.getItem( param1 ) ;

	list.printItems() ;

	return 0 ;
}