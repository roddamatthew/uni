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

	std::cout << R.reverseDigit(i) << " " << R.reverseString(s) << " " << T.numTrucks(numCrates,loadSize) << " " << E.numTrucks(numCrates,loadSize) << " " << std::endl;

	return 0;
}