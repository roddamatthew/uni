#include <iostream>

int minimum(int array[], int n){
	int minimum=array[1];
	int i=0;

	if(n>=1){
		for(i=0; i<n; i++){
			if(array[i]<minimum){
				minimum=array[i];
			}
		}
	}else{
		return 0;
	}

	return minimum;
}