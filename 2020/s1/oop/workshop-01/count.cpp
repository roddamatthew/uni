#include <iostream>

int count(int array[], int n){
	int total=0;
	int i;

	for(i=0; i<n;i++){
		if(array[i]%2==0){
			total++;
	}
	
	}

	return total;
}