#ifndef FILTER_GENERIC
#define FILTER_GENERIC

#include <vector>

class FilterGeneric
{
private:
	virtual bool g(int n) = 0;
	int index ;
public:
	FilterGeneric() ;
	std::vector<int> filter( std::vector<int> v ) ;
};
#endif //FILTER_GENERIC