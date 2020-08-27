#include "EfficientTruckLoads.h"
#include <iostream>

EfficientTruckloads :: EfficientTruckloads(){
	// Initializing the 2D array for numTrucks records.
	array = new int*[10];	// Assuming there will only be 10 different calls of this function per run.
	for(int i = 0; i < 10; i++){
		
		array[i] = new int[3];
		
		for(int j = 0; j < 3; j++){
			array[i][j] = -1;
		}
	}

	index = 0;
}

int EfficientTruckloads :: numTrucks(int numCrates, int loadSize){
	int trucks;

	// Checking array for whether a previous call of numTrucks with the same parameters has been made and using that.
	for(int i = 0; i < 10; i++){
		if(numCrates == array[i][0] && loadSize == array[i][1]){
			return array[i][2];
		}
	}

	if(numCrates > 2 && loadSize >= 1){	// If it hasnt been called before, do the recursive function and store the data
		trucks = numTrucksHelper(numCrates, loadSize);
		array[index][0] = numCrates;
		array[index][1] = loadSize;
		array[index][2] = trucks;
		index++;

		return trucks;
	}else{
		std::cout << "ERROR" << std::endl;
		return 0;
	}
}

int EfficientTruckloads :: numTrucksHelper(int numCrates, int loadSize){
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