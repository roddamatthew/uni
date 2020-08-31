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

	if(i > 0){
		std::cout << R.reverseDigit(i) << " ";
	}else{
		std::cout << "ERROR ";
	}

	std::cout << R.reverseString(s) << " ";

	if(numCrates > 2 && loadSize >= 1){
		std::cout << T.numTrucks(numCrates,loadSize) << " " << E.numTrucks(numCrates,loadSize) << " " << std::endl;
	}else{
		std::cout << "ERROR ERROR";
	}

	return 0;
}