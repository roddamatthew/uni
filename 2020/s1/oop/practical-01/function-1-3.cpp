#include <iostream>

int count(int array[], int n, int number){
 	int count=0;
 	int i;

 	if(n>=1){
		for(i=0; i<n; i++){
			if(array[i]==number){
				count++;
			}
		}

	}else{
		count=0;
	}


 	return count;
 }