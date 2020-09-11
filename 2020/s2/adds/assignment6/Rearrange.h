#ifndef REARRANGE_H
#define REARRANGE_H

#include "Individual.h"
#include "Mutator.h"

class Rearrange : public Mutator
{
public:
	Rearrange() ;
	Individual mutate( Individual ind, int k ) ;
};
#endif //REARRANGE_H