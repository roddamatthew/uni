#ifndef REDUCE_GENERIC
#define REDUCE_GENERIC

#include <vector>

class ReduceGeneric
{
private:
	virtual int binaryOperator( int n1, int n2 ) = 0;
public:
	ReduceGeneric() ;
	int reduce( std::vector<int> v ) ;
};
#endif //REDUCE_GENERIC