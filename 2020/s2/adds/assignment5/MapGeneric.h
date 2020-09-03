#ifndef MAP_GENERIC
#define MAP_GENERIC

#include <vector>

class MapGeneric
{
private:
	virtual int f(int input) = 0 ;
	int index ;
public:
	MapGeneric() ;
	std::vector<int> map(std::vector<int> v) ;
};
#endif //MAP_GENERIC