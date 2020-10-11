#include "RecursiveBinarySearch.h"
#include <vector>
#include <iostream>

using namespace std ;

RecursiveBinarySearch :: RecursiveBinarySearch() {}

int RecursiveBinarySearch :: search( std::vector<int> array, int start, int end )
{
	// Assume the input array is sorted from smallest to highest
	int middle = ( start + end ) / 2 ;

	if( start < 0 || end < 0 || start > array.size() || end > array.size() || start > end )
	{
		return -1 ;
	}

	if( array[ middle ] == 1 )
	{
		return middle ;
	}
	else if( array[ middle ] > 1 )
	{
		end = middle - 1 ;
	}
	else if( array[ middle ] < 1 )
	{
		start = middle + 1 ;
	}

	return search( array, start, end ) ;
}