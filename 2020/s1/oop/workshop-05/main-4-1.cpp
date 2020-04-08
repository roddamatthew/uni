#include <iostream>

extern int secondSmallestSum(int *numbers,int length);

int main(){
	int array[4]={1,2,3,4};

	std::cout << secondSmallestSum(array,4) << std::endl;

	return 0;
}