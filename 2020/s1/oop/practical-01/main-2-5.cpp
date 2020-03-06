#include <iostream>

extern bool descending(int array[], int n);

int main(){
	int array[7]={7,6,5,4,3,2,1};
	int array_size=7;

	int array_false[4]={25,13,34,86};
	int array_false_size=4;

	std::cout << descending(array, array_size) << std::endl;
	std::cout << descending(array_false, array_false_size) << std::endl;
}