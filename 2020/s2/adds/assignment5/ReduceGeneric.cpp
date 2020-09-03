#include "ReduceGeneric.h"
#include <vector>
#include <iostream>

using namespace std;

ReduceGeneric :: ReduceGeneric () {}

int ReduceGeneric :: reduce( vector<int> v )
{
	if( v.size() == 1 ){
		return v[0] ;
	}

	// Store first two elements
	int firstElement = v[0] ;
	int secondElement = v[1] ;

	// Erase the first two elements from the vector
	v.erase( v.begin() ) ;
	v.erase( v.begin() ) ;

	// Call binaryOperator on first and second elements and then add what it returns to the end of the vector
	v.push_back( binaryOperator( firstElement, secondElement ) ) ;

	std::cout << v.size() << std::endl;

	// Recursive call with the vector of length one less
	return reduce( v ) ;
}