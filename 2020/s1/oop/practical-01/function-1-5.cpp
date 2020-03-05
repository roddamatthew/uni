#include <iostream>

int count_even(int number){
	int evens=0;
	int i;

	for(i=1; i<=number; i++){
		if(i%2==0){
			evens++;
		}
	}

	return evens;
}