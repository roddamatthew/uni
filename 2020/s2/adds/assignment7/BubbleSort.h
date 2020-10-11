#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "Sort.h"
#include <vector>

class BubbleSort : public Sort
{
public:
	BubbleSort() ;
	std::vector<int> sort( std::vector<int> array ) ;
} ;
#endif //BUBBLESORT_H