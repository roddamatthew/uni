#include "MapGeneric.h"
#include "MapTriple.h"
#include "MapSquare.h"
#include "MapAbsoluteValue.h"

#include "FilterGeneric.h"
#include "FilterOdd.h"
#include "FilterNonPositive.h"
#include "FilterForTwoDigitPositive.h"

#include "ReduceGeneric.h"
#include "ReduceMinimum.h"
#include "ReduceGCD.h"

#include <vector>
#include <iostream>

using namespace std;

int main()
{
	MapAbsoluteValue MAV;
	MapSquare MS;

	FilterOdd FO;
	FilterNonPositive FNP;
	FilterForTwoDigitPositive FTDP;

	ReduceMinimum RM;
	ReduceGCD RGCD;

	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;


	for(int i = 0; i < 20; i++)
	{
		if( i % 2 == 0){
			v1.push_back( 2*i ) ;
		}else{
			v1.push_back( -2*i ) ;
		}
	}

	v2 = MS.map( v1 ) ;
	v2 = FTDP.filter( v2 ) ;

	for(int i = 0; i < v2.size(); i++)
	{
		std::cout << v2[i] << " ";
	}
	std::cout << std::endl;

	std::cout << RGCD.reduce( v2 ) << std::endl ;

	std::cout << RM.reduce( v1 ) << std::endl ;

	return 0;
}