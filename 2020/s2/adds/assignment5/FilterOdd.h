#ifndef FILTER_ODD
#define FILTER_ODD

#include "FilterGeneric.h"

class FilterOdd : public FilterGeneric
{
private:
	bool g( int n ) ;
public:
	FilterOdd() ;
};
#endif //FILTER_ODD