#include "ReduceGeneric.h"
#include "ReduceGCD.h"

ReduceGCD :: ReduceGCD () {}

int ReduceGCD :: binaryOperator( int n1, int n2 ){

	while( n1 != n2 && n1 != 0 && n2 != 0 )
	{
		if( n1 > n2 )
		{
			n1 = n1 - n2 ;
		}else
		{
			n2 = n2 - n1 ;
		}
	}
	
	return n1 ;
}