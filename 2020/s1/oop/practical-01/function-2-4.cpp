#include <iostream>

bool ascending(int array[], int n){
	int i;
	int true_condition=1;
	bool ascending=false;

	if(n>0){
		for(i=1; i<n; i++){
			if(array[i]>array[i-1]){
				true_condition++;
			}
		}

		if(true_condition==n){
			ascending=true;
		}
	}

	return ascending;
}