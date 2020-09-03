#include "MapGeneric.h"
#include "MapSquare.h"
#include <cmath>

MapSquare :: MapSquare() {}

int MapSquare :: f( int n )
{
	return pow( n, 2 ) ;
}