#include <iostream>

extern  bool fanarray(int array[], int n);

int main(){
	int array1[6]={1,4,3,3,4,1};
	int array2[7]={1,2,3,4,3,2,1};
	int array3[4]={1,4,4,1};
	int array4[3]={1,3,2};


	std::cout << fanarray(array1, 6) << std:: endl;
	std::cout << fanarray(array2, 7) << std:: endl;
	std::cout << fanarray(array3, 4) << std:: endl;
	std::cout << fanarray(array4, 3) << std:: endl;

	return 0;
}