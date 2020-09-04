#include "FilterGeneric.h"
#include "FilterForTwoDigitPositive.h"

FilterForTwoDigitPositive :: FilterForTwoDigitPositive() {}

bool FilterForTwoDigitPositive :: g( int n )
{
	if( n >= 10 && n < 100){
		return true ;
	}else{
		return false ;
	}
}