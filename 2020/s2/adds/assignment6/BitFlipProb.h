#ifndef BITFLIPPROB_H
#define BITFLIPPROB_H

#include "Individual.h"
#include "Mutator.h"

class BitFlipProb : public Mutator
{
private:
	double probability ;
public:
	BitFlipProb() ;
	BitFlipProb( double p ) ;
	Individual mutate( Individual ind, int k ) ;
};
#endif //BITFLIPPROB_H