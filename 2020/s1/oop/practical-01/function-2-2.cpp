#include <iostream>

int maximum(int array[], int n){
	int maximum=array[1];
	int i=0;

	if(n>=1){
		for(i=0; i<n; i++){
			if(array[i]>maximum){
				maximum=array[i];
			}
		}
	}else{
		return 0;
	}

	return maximum;

}