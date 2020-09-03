#ifndef REDUCE_MINIMUM
#define REDUCE_MINIMUM

#include "ReduceGeneric.h"

class ReduceMinimum : public ReduceGeneric
{
private:
	int binaryOperator( int n1, int n2 ) ;
public:
	ReduceMinimum() ;
};
#endif //REDUCE_MINIMUM