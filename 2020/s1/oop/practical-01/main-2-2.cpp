#include <iostream>

extern int maximum(int array[], int n);

int main(){
	int array[9]={1,2,3,4,5,6,7,8,9};
	int array_size=9;

	std::cout << "The number is: " << maximum(array, array_size) << std::endl;

	return 0;
}