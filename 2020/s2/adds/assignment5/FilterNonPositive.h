#ifndef FILTER_NON_POSITIVE
#define FILTER_NON_POSITIVE

#include "FilterGeneric.h"

class FilterNonPositive : public FilterGeneric
{
private:
	bool g( int n ) ;
public:
	FilterNonPositive() ;
};
#endif //FILTER_NON_POSITIVE