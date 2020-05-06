#include <iostream>

int* readNumbers(){
	int* array;
	int i=0;
	int length=0;

	std::cout << "How many numbers would you like to enter: ";
	std::cin >> length;
	std::cout << std::endl;


	array = new int[length];

	for(i=0;i<length;i++){
		std::cout << "Please enter your '" << i+1 <<"'th number: ";
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