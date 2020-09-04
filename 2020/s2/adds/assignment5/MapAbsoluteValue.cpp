#include "MapGeneric.h"
#include "MapAbsoluteValue.h"
#include <cmath>

MapAbsoluteValue :: MapAbsoluteValue () {}

int MapAbsoluteValue :: f( int n )
{
	if(n < 0){
		return -n ;
	}else{
		return n ;
	}
}