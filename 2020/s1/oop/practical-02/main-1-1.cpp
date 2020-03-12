#include <iostream>

extern int diagonal(int array[4][4]);

int main(){
	int array1[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int array2[4][4]={2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32};
	int array3[4][4]={-1,1,1,1,1,1,1,1,-1,1,1,1,1,-1,1,0};

	std::cout << diagonal(array1) << std::endl;
	std::cout << diagonal(array2) << std::endl;
	std::cout << diagonal(array3) << std::endl;

	return 0;
}