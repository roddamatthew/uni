#ifndef REDUCE_GCD
#define REDUCE_GCD

#include "ReduceGeneric.h"

class ReduceGCD : public ReduceGeneric
{
private:
	int binaryOperator( int n1, int n2 ) ;
public:
	ReduceGCD() ;
};
#endif //REDUCE_GCD