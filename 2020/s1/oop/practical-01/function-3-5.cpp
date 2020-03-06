#include <iostream>

double sumeven(double array[], int n){
	int i;
	double sumeven=0;

	for(i=0; i<n; i=i+2){
		sumeven=array[i]+sumeven;
	}

	return sumeven;
}