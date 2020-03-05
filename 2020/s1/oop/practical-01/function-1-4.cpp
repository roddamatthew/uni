#include <iostream>

int sumtwo(int array[], int secondarray[], int n){
	int total=0;
	int i;

	if(n>=1){
		for(i=0; i<n; i++){
			total=total+array[i]+secondarray[i];
		}

	}else{
		total=0;
	}

	return total;
}