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
	MapAbsoluteValue MAV;

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

	v2 = FTDP.filter( v1 ) ;
	v3 = MAV.map( v1 ) ;
	v3 = FO.filter( v3 ) ;
	v4 = FNP.filter( v1 ) ;

	for (int i = 0; i < 20; i++){
		std::cout << "v1 = " << v1[i];

		if( i < v2.size() ){
			std::cout << "	v2 = " << v2[i];
		}if( i < v3.size() ){
			std::cout << "	v3 = " << v3[i];
		}if( i < v4.size() ){
			std::cout << "	v4 = " << v4[i];
		}

		std::cout << std::endl;
	}

	return 0;
}