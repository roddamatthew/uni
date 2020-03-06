#include <iostream>
#include <math.h>

bool fanarray(int array[], int n){
	bool fanarray=false;
	int symmetrical_counter=0;
	int ascending_counter=1;
	bool symmetrical=false;
	bool ascending=false;
	int i;

	if(n>=1){
		// Check if the first half of the array is symmetrical to the second half.
		for(i=0; i<floor(n/2); i++){
			if(array[i]==array[(n-i-1)]){
				symmetrical_counter++;
			}
		}

		if(symmetrical_counter==floor(n/2)){
			symmetrical=true;
		}

		// Check if the first half of the array is ascending.
		for(i=1; i<floor(n/2); i++){
			if(array[i]>array[i-1]){
				ascending_counter++;
			}
		}

		if(ascending_counter==floor(n/2)){
			ascending=true;
		}

// If the array is both ascending and symmetrical, it is a fan array.
		if(ascending==true && symmetrical==true){
			fanarray=true;
		}
	}
	return fanarray;
}