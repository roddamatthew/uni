#ifndef FILTER_FOR_TWO_DIGIT_POSITIVE
#define FILTER_FOR_TWO_DIGIT_POSITIVE

#include "FilterGeneric.h"

class FilterForTwoDigitPositive : public FilterGeneric
{
private:
	bool g( int n ) ;
public:
	FilterForTwoDigitPositive() ;

};
#endif //FILTER_TWO_DIGIT_POSITIVE