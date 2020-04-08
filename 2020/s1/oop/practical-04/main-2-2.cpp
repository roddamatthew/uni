#include <iostream>

extern int maximum_sum(int *nums,int length);

int main(){
	int array1[10]={ 31, -41, 59, 26, -53, 58, 97, -93, -23, 84 };
	int array2[4]={1,2,3,-4};
	int array3[5]={-1,-10,15,-7,-412};

	std::cout<< maximum_sum(array1,10) << std::endl;
	std::cout<< maximum_sum(array2,4) << std::endl;
	std::cout<< maximum_sum(array3,5) << std::endl;

	return 0;
}