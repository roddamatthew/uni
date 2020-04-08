#include <iostream>

int *readNumbers(){
	int *numbers = new int[10];
	int i;

	for(i=0;i<10;i++){
		std::cout << "Please enter a number: ";
		std::cin >> *(numbers+i);
	}

	return numbers;
}

void printNumbers(int *numbers,int length){
	for(int i=0;i<length;i++){
		std::cout << i << " " << *(numbers+i) << std::endl;
	}
}

void hexDigits(int *numbers,int length){
	for(int i=0;i<length;i++){
	switch(*(numbers+i)){
		case 10:
		std::cout << i << " " << *(numbers+i) << " A" << std::endl;
		break;

		case 11:
		std::cout << i << " " << *(numbers+i) << " B" << std::endl;
		break;

		case 12:
		std::cout << i << " " << *(numbers+i) << " C" << std::endl;
		break;

		case 13:
		std::cout << i << " " << *(numbers+i) << " D" << std::endl;
		break;

		case 14:
		std::cout << i << " " << *(numbers+i) << " E" << std::endl;
		break;

		case 15:
		std::cout << i << " " << *(numbers+i) << " F" << std::endl;
		break;

		case 16:
		std::cout << i << " " << *(numbers+i) << " G" << std::endl;
		break;

		default :
		std::cout << i << " " << *(numbers+i) << " " << *(numbers+i) << std::endl;

	}
}
}