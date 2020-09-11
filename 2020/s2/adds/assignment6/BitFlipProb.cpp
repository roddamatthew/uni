#include "Individual.h"
#include "Mutator.h"
#include "BitFlipProb.h"

#include <cstdlib>
#include <time.h>
#include <iostream>

BitFlipProb :: BitFlipProb() {}

BitFlipProb :: BitFlipProb( double p )
{
	probability = p ;
}

Individual BitFlipProb :: mutate( Individual ind, int k )
{
	srand( time( NULL ) ) ;

	for( int i = 0; i < ind.getLength(); i++)
	{
		float random = (float) rand() / RAND_MAX ;
		std::cout << random << " " << probability << std::endl;

		if( probability <= random ) ind.flipBit( i ) ;
	}

	return ind ;
}