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
	TruckLoads T;
	EfficientTruckLoads E;

	std::cin >> i;
	std::cin >> s;
	std::cin >> numCrates;
	std::cin >> loadSize;

	if(i >= 0){
		std::cout << R.reverseDigit(i) << " ";
	}else{
		std::cout << "ERROR " ;
	}

	if(s.length() > 0){
		std::cout << R.reverseString(s) << " ";
	}else{
		std::cout << "ERROR " ;
	}

	if(numCrates > 0 && loadSize > 0){
		std::cout << T.numTrucks(numCrates,loadSize) << " ";
	}else{
		std::cout << "ERROR " ;
	}

	if(numCrates > 0 && loadSize > 0){
		std::cout << E.numTrucks(numCrates,loadSize) << " ";
	}else{
		std::cout << "ERROR " ;
	}

	return 0;
}