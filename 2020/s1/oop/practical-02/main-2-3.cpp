#include <iostream>

extern int sum_if_a_palindrome(int integers[], int length);

int main(){
	int array1[5]={1,15,1,15,1};
	int array2[5]={1,2,3,4,5};
	int array3[1]={10};

	std::cout << sum_if_a_palindrome(array1,5) << std::endl;
	std::cout << sum_if_a_palindrome(array2,5) << std::endl;
	std::cout << sum_if_a_palindrome(array3,1) << std::endl;

	return 0;
}