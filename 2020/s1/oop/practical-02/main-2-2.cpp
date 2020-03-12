#include <iostream>

extern int binary_to_number(int binary_digits[], int number_of_digits);

int main(){
	int array1[5]={1,1,0,1,0};
	int array2[2]={1,1};
	int array3[4]={1,0,1,0};

	std::cout << binary_to_number(array1,5) << std::endl;
	std::cout << binary_to_number(array2,2) << std::endl;
	std::cout << binary_to_number(array3,4) << std::endl;

	return 0;
}