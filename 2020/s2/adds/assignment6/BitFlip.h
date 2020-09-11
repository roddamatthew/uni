#ifndef BITFLIP_H
#define BITFLIP_H

#include "Individual.h"
#include "Mutator.h"

class BitFlip : public Mutator
{
public:
	BitFlip() ;
	Individual mutate( Individual ind, int k ) ;
};
#endif //BITFLIP_H