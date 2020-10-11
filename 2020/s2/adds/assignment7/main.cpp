#include "Sort.h"
#include "QuickSort.h"
#include "BubbleSort.h"
#include "RecursiveBinarySearch.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std ;

int main()
{
	vector<int> inputs ;
	string str ;
	string current ;

	BubbleSort BS ;
	QuickSort QS ;

	RecursiveBinarySearch RBS ;

	// Input processing
	getline(cin, str);

	for( int i = 0 ; i < str.length() ; i++ )
	{
		if( str[i] == ' ' )
		{
			inputs.push_back( stoi( current ) ) ;
			current = "" ;
		}
		else
		{
			current += str[i] ;
		}
	}

	if( str[ str.length() - 1 ] != ' ' )
	{
		inputs.push_back( stoi( current ) ) ;
		current = "" ;
	}

	// // Print input for debugging
	// for( int i = 0 ; i < inputs.size() ; i++ )
	// {
	// 	std::cout << inputs[i] << " " ;
	// }


	// Call Bubble sort then 
	inputs = BS.sort( inputs ) ;

	if( RBS.search( inputs, 0, inputs.size() - 1 ) != -1 )
	{
		std::cout << "true " ;
	}
	else
	{
		std::cout << "false " ;
	}

	for( int i = 0 ; i < inputs.size() ; i++ )
	{
		std::cout << inputs[i] << " " ;
	}

	std::cout << std::endl ;

	return 0 ;
}