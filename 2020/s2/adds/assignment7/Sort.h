#ifndef SORT_H
#define SORT_H

#include <vector>

class Sort
{
public:
	Sort() ;
	virtual std::vector<int> sort( std::vector<int> array ) = 0 ;
} ;
#endif //SORT_H