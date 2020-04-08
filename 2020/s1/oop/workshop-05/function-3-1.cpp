#include <iostream>

bool equalsArray(int *numbers1,int *numbers2,int length){
	int true_counter=0;
	bool equal=false;
	
	for(int i=0; i<length; i++){
		if(*(numbers1+i)==*(numbers2+i)){
			true_counter++;
		}
	}

	if (true_counter==length){
		equal=true;
	}

	return equal;
}