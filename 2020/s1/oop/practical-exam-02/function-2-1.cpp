#include <iostream>

int* readNumbers(int n){
	int* array;
	int i;
	array = new int[n];

	for(i=0;i<n;i++){
		std::cout << "Enter your " << i << "th input: " ;
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

void months(int* monthNumbers,int length){
	int i;

	if(length>0){
		for(i=0;i<length;i++){

			std::cout << i << " ";

			switch(monthNumbers[i]){
				case 1:
				std::cout << monthNumbers[i] << " Januray" << std::endl;
				break;

				case 2:
				std::cout << monthNumbers[i] << " February" << std::endl;
				break;

				case 3:
				std::cout << monthNumbers[i] << " March" << std::endl;
				break;

				case 4:
				std::cout << monthNumbers[i] << " April" << std::endl;
				break;

				case 5:
				std::cout << monthNumbers[i] << " May" << std::endl;
				break;

				case 6:
				std::cout << monthNumbers[i] << " June" << std::endl;
				break;

				case 7:
				std::cout << monthNumbers[i] << " July" << std::endl;
				break;

				case 8:
				std::cout << monthNumbers[i] << " August" << std::endl;
				break;

				case 9:
				std::cout << monthNumbers[i] << " September" << std::endl;
				break;

				case 10:
				std::cout << monthNumbers[i] << " October" << std::endl;
				break;

				case 11:
				std::cout << monthNumbers[i] << " November" << std::endl;
				break;

				case 12:
				std::cout << monthNumbers[i] << " December" << std::endl;
				break;
			}
		}
	}

}