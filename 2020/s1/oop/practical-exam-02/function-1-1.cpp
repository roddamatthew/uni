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