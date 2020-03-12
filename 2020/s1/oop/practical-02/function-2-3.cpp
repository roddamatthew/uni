#include <iostream>
#include <cmath>

int sum_if_a_palindrome(int integers[], int length){
	int sum=0;

	if(length>0){
		if(is_a_palindrome(integers[],length)==true){
			sum=sum_elements(integers[]);
		}else{
			sum=-2;
		}
	}else{
		sum=-1;
	}

	return sum;
}




bool is_a_palindrome(int integers[], int length){
	int symmetrical_counter=0;
	bool symmetrical=false;
	int i=0;

	if(length>0){
		// Check if the first half of the integers is symmetrical to the second half.
		for(i=0; i<floor(length/2); i++){
			if(integers[i]==integers[(length-i-1)]){
				symmetrical_counter++;
			}
		}

		if(symmetrical_counter==floor(length/2)){
			symmetrical=true;
		}
	}
	return symmetrical;
}

int sum_elements(int integers[], int length){
	int i=0;
	int sum=0;

	if(length>0){
		for(i=0; i<length; i++){
			sum=sum+integers[i];
		}
	}else{
		sum=-1;
	}

	return sum;
}