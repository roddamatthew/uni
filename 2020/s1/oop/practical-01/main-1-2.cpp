#include <iostream>

extern double average(int[], int);

int main(){
	int array[10] = {1,2,3,4,5,4,3,2,1,1};
	int array2[10] = {10,9,8,7,6,5,4,3,2,1};
	int array_size = 10;
	int number=1;

	std::cout << "The number is: " << average(array, array_size) << std::endl;

	return 0;
}