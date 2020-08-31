#include "TruckLoads.h"
#include <iostream>

Truckloads :: Truckloads(){}

int Truckloads :: numTrucks(int numCrates, int loadSize){
		return numTrucksHelper(numCrates, loadSize);
}

int Truckloads :: numTrucksHelper(int numCrates, int loadSize){
	// base case:
	if(numCrates <= loadSize){
		return 1;
	}

	int newCrates1 = numCrates/2;
	int newCrates2 = numCrates/2;

	// Recursion
	if(numCrates % 2 > 0){
		newCrates1 = (numCrates + 1)/2;
		newCrates2 = (numCrates - 1)/2;
	}
	
	return numTrucksHelper(newCrates1, loadSize) + numTrucksHelper(newCrates2, loadSize);
}