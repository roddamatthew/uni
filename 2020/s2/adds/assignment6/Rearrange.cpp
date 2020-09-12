#include "Individual.h"
#include "Mutator.h"
#include "Rearrange.h"

#include <string>

using namespace std;

Rearrange :: Rearrange() {}

Individual Rearrange :: mutate( Individual ind, int k )
{
	string list = "" ;
	string code = ind.getString() ;
	k-- ;

	while( k >= ind.getLength() )
	{
		k = k - ind.getLength() ;
	}

	for( int i = k; i < ind.getLength(); i++)
	{
		list += code[ i ] ;
	}

	for( int i = 0; i < k; i++)
	{
		list += code[ i ] ;
	}

	Individual ind2( list ) ;

	return ind2 ;
}
