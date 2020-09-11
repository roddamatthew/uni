#ifndef MUTATOR_H
#define MUTATOR_H

#include "Individual.h"

class Mutator
{
public:
	Mutator() ;
	virtual Individual mutate( Individual ind, int k ) = 0 ;
};
#endif //MUTATOR_H