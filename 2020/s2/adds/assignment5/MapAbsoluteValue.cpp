#include "MapGeneric.h"
#include "MapAbsoluteValue.h"
#include <cmath>

MapAbsoluteValue :: MapAbsoluteValue () {}

int MapAbsoluteValue :: f( int n )
{
	return abs( n ) ;
}