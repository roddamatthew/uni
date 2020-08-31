#include <iostream>
#include <string>
#include "Reverse.h"
#include "TruckLoads.h"
#include "EfficientTruckLoads.h"

int main(){
	int i;
	std::string s;
	int numCrates;
	int loadSize;

	Reverse R;
	Truckloads T;
	EfficientTruckloads E;

	std::cin >> i;
	std::cin >> s;
	std::cin >> numCrates;
	std::cin >> loadSize;

	if(i < 0){
		std::cout << "ERROR ";
	}else{
		std::cout << R.reverseDigit(i) << " ";
	}

	std::cout << R.reverseString(s) << " ";

	if(numCrates < 2 || numCrates > 10000){
		std::cout << "ERROR ERROR";
	}else if(loadSize < 1 || loadSize > numCrates){
		std::cout << "ERROR ERROR";
	}else{
		std::cout << T.numTrucks(numCrates,loadSize) << " " << E.numTrucks(numCrates,loadSize) << " " << std::endl;
	}

	return 0;
}