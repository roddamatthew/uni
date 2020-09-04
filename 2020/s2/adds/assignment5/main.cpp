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
#include <string>
#include <iostream>

using namespace std;

int main()
{
	MapAbsoluteValue MAV;
	MapSquare MS;
	MapTriple MT;

	FilterOdd FO;
	FilterNonPositive FNP;
	FilterForTwoDigitPositive FTDP;

	ReduceMinimum RM;
	ReduceGCD RGCD;

	vector<int> v1 ;
	v1.clear() ;

	string input ;
	string number ;

	int j = 0;

	//Take input and remove spaces and commas
	std::getline (std::cin, input) ;

	for(int i = 0; i < 20; i++)
	{
		number.clear() ;
		while(input[j] != ',')	//Read until a comma is found
		{
			number = number + input[j] ;
			j++;

			if(j == input.length() ){
				break;
			}
		}
		
		if(number.length() > 0){
			v1.push_back( stoi( number ) ) ;
		}

		j++;	//skipping the comma
	}

	// Absolute Value
	v1 = MAV.map( v1 ) ;

	// Triple
	v1 = MT.map( v1 ) ;

	std::cout << "L': " << std::endl;
	for(int i = 0; i < v1.size(); i++){
		std::cout << v1[i] << " ";
	}

	// Two digit positive
	v1 = FTDP.filter( v1 );

	// Odds
	v1 = FO.filter( v1 );

	std::cout << std::endl << "L'': " << std::endl;
	for(int i = 0; i < v1.size(); i++){
		std::cout << v1[i] << " ";
	}

	std::cout << RM.reduce( v1 ) << " " << RGCD.reduce( v1 ) << std::endl;



	return 0;
}