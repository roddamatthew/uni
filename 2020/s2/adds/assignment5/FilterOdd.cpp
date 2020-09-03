#include "FilterGeneric.h"
#include "FilterOdd.h"

FilterOdd :: FilterOdd() {}

bool FilterOdd :: g( int n )
{
	if( n % 2 == 1 ){
		return true ;
	}else{
		return false ;
	}
}