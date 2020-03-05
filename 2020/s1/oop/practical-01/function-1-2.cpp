#include <iostream>

double average(int array[], int n){
	double average=0;
	int total=0;
	int i;

	if(n>=1){
		for(i=0; i<n; i++){
			total=total+array[i];
		}

	}else{
		total=0;
	}

	average=total/n;

	return average;
}