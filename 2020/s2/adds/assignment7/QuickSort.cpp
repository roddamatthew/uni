#include "Sort.h"
#include "QuickSort.h"
#include <vector>

using namespace std ;

QuickSort :: QuickSort () {}

std::vector<int> QuickSort :: sort( std::vector<int> array )
{
	// Base Case
	if( array.size() <= 1 )
	{
		return array ;
	}

	// Recursive Case:
	vector<int> less ;
	vector<int> greater ;

	// Pivot selection
	int pivot ;
	
	if( array.size() >= 3 )
	{
		pivot = array[ 2 ] ;
		array.erase( array.begin() + 2 ) ;
	}
	else
	{
		pivot = array[ 0 ] ;
		array.erase( array.begin() ) ;
	}

	// Split vector into less and greater than the pivot
	for( int i = 0 ; i < array.size() ; i++ )
	{
		if( array[i] <= pivot )
		{
			less.push_back( array[i] ) ;
		}
		else if( array[i] > pivot )
		{
			greater.push_back( array[i] ) ;
		}
	}

	sort( less ) ;
	sort( greater ) ;

	less.push_back( pivot ) ;
	greater.insert( greater.begin(), less.begin(), less.end() ) ;

	// append( sort(less), pivot, sort(greater) ) ;

	return greater ;
}