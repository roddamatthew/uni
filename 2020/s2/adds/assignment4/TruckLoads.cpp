#include "TruckLoads.h"
#include <iostream>

Truckloads :: Truckloads(){}

int Truckloads :: numTrucks(int numCrates, int loadSize){
	if(numCrates > 2 && loadSize >= 1){
		return numTrucksHelper(numCrates, loadSize);
	}else{
		std::cout << "ERROR";
		return 0;
	}
}

int Truckloads :: numTrucksHelper(int numCrates, int loadSize){
	// base case:
	if(numCrates <= loadSize){
		return 1;
	}

	int newCrates1;
	int newCrates2;

	// Recursion
	if(numCrates % 2 == 0){
		newCrates1 = numCrates/2;
		newCrates2 = numCrates/2;
	}else if(numCrates % 2 > 0){
		newCrates1 = (numCrates + 1)/2;
		newCrates2 = (numCrates - 1)/2;
	}

	// std::cout << "Went from " << numCrates << " and split them into two piles of " << newCrates1 << " and " << newCrates2 << std::endl;

	return numTrucksHelper(newCrates1, loadSize) + numTrucksHelper(newCrates2, loadSize);
}