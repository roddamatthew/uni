#include <iostream>

extern double sumeven(double array[], int n);

int main(){
	double array1[6]={1,4,3,3,4,1};
	double array2[7]={1,2,3,4,3,2,1};
	double array3[4]={1,4,4,1};
	double array4[3]={1,3,2};


	std::cout << sumeven(array1, 6) << std:: endl;
	std::cout << sumeven(array2, 7) << std:: endl;
	std::cout << sumeven(array3, 4) << std:: endl;
	std::cout << sumeven(array4, 3) << std:: endl;

	return 0;
}