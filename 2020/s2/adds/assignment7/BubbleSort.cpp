#include "Sort.h"
#include "BubbleSort.h"

BubbleSort :: BubbleSort() {} ;

std::vector<int> BubbleSort :: sort( std::vector<int> array )
{
	for( int i = array.size() - 1 ; i > 0 ; i-- )
	{
		for( int j = 0 ; j < i ; j++ )
		{
			if( array[ j ] > array[ j + 1 ] )
			{
				int value = array[ j + 1 ] ;
				array[ j + 1 ] = array[ j ] ;
				array[ j ] = value ;
			}
		}
	}
	return array ;
}