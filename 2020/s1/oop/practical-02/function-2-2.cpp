#include <iostream>
#include <cmath>

int binary_to_number(int binary_digits[], int number_of_digits){
	int sum=0;
	int i=0;

	for(i=0; i<number_of_digits; i++){
		sum=sum+binary_digits[i]*pow(2,number_of_digits-1-i);
	}

	return sum;
}