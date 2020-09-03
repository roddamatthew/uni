#include "ReduceGeneric.h"
#include "ReduceMinimum.h"
#include <algorithm>

using namespace std;

ReduceMinimum :: ReduceMinimum() {}

int ReduceMinimum :: binaryOperator( int n1, int n2 )
{
	return min( n1, n2 ) ;
}