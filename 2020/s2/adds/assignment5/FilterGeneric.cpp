#include "FilterGeneric.h"
#include <vector>

using namespace std;

FilterGeneric :: FilterGeneric ()
{
	index = 0 ;
}

vector<int> FilterGeneric :: filter( vector<int> v )
{
	if( index == v.size() )
	{
		return v ;
	}

	if( g( v[index]) == false )
	{
		v.erase( v.begin() + index ) ;
	}else{
		index++;
	}

	return filter( v ) ;
}