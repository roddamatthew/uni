#include "MapGeneric.h"
#include "MapTriple.h"
#include "MapSquare.h"
#include "MapAbsoluteValue.h"

#include "FilterGeneric.h"
#include "FilterOdd.h"
#include "FilterNonPositive.h"
#include "FilterForTwoDigitPositive.h"

#include <vector>
#include <iostream>

using namespace std;

int main()
{
	MapTriple MT;
	MapSquare MS;
	MapAbsoluteValue MA;

	FilterOdd FO;
	FilterNonPositive FNP;
	FilterForTwoDigitPositive FTDP;

	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;


	for(int i = 0; i < 20; i++)
	{
		if( i % 2 == 0){
			v1.push_back( i ) ;
		}else{
			v1.push_back( -i ) ;
		}
	}

	v2 = MT.map( v1 );
	v3 = MS.map( v1 );
	v4 = MA.map( v1 );

	for(int i = 0; i < 20; i++)
	{
		std::cout << "V = " << v1[i] << "	Triple = " << v2[i] << "	Square = " << v3[i] << "	Absolute = " << v4[i] << std::endl;
	}

	v2 = FO.filter( v1 );
	v3 = FNP.filter( v1 );
	v4 = FTDP.filter( v1 );

	for(int i = 0; i < 20; i++)
	{
		std::cout << "V = " << v1[i] << "	Odd = " << v2[i] << "	NonPositive = " << v3[i] << "	TwoDigitPos = " << v4[i] << std::endl;
	}
	return 0;
}