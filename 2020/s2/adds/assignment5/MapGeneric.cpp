#include "MapGeneric.h"
#include <vector>

using namespace std;

MapGeneric :: MapGeneric() 
{
	index = 0;
}

vector<int> MapGeneric::map(vector<int> v)
{
	if( index == v.size() )
	{
		return v ;
	}

	v[index] = f( v[index] ) ;
	index++ ;

	return map( v ) ;
}