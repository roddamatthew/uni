#include "FilterGeneric.h"
#include "FilterNonPositive.h"

FilterNonPositive :: FilterNonPositive() {}

bool FilterNonPositive :: g( int n )
{
	if( n < 0 ){
		return true ;
	}else{
		return false ;
	}
}