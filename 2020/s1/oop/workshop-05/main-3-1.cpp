#include <iostream>

extern bool equalsArray(int *numbers1,int *numbers2,int length);

int main(){
	int array1[]={1,2,3,4,5};
	int array2[]={1,2,3,4,5};
	int array3[]={5,4,3,2,1};

	std::cout << equalsArray(array1,array2,5) <<std::endl;
	std::cout << equalsArray(array2,array3,5) <<std::endl;
	std::cout << equalsArray(array1,array3,5) <<std::endl;

	return 0;
}