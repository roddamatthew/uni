#include <iostream>

extern bool ascending(int array[], int n);

int main(){
	int array[7]={1,2,3,4,5,6,7};
	int array_size=7;

	int array_false[4]={65,13,33,100};
	int array_false_size=4;

	std::cout << ascending(array, array_size) << std::endl;
	std::cout << ascending(array_false, array_false_size) << std::endl;
}