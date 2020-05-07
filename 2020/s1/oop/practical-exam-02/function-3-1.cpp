#include <iostream>

int* readNumbers(int n){
	int* array;
	int i;
	array = new int[n];

	for(i=0;i<n;i++){
		std::cin >> array[i];
	}

	return array;
}

void printNumbers(int* array, int length){
	int i;
	for(i=0;i<length;i++){
		std::cout << i << " " << array[i] << std::endl;
	}
}

bool twinArray(int* numbers, int length){
	int i;
	int counter=0;

	if(length>0){
		for(i=0;i<length/2;i++){
			if(numbers[2*i]==numbers[2*i+1]){
				counter++;
			}
		}

		if(counter==length/2){
			return true;
		}else{
			return false;
		}

	}else if(length<1){
		return false;
	}
}