#include "Individual.h"
#include "Mutator.h"
#include "BitFlip.h"

BitFlip :: BitFlip() {}

Individual BitFlip :: mutate( Individual ind, int k )
{
	while( k > ind.getLength() )
	{
		k = k - ind.getLength() ;
	}

	ind.flipBit( k ) ;

	return ind ;
}