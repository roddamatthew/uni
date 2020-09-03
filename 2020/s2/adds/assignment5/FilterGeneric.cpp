#include "FilterGeneric.h"
#include <vector>
#include <iostream>

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
		std::cout << "Erasing: " << v[index] << std::endl;
		v.erase( v.begin() + index ) ;
	}else{
		index++;
	}

	return filter( v ) ;
}