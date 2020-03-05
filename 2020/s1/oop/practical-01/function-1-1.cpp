#include <iostream>

int sum_array(int array[], int n){
	int total=0;
	int i;

	if(n>=1){
		for(i=0; i<n; i++){
			total=total+array[i];
		}

	}else{
		total=0;
	}

	return total;
}