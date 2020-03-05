#include <iostream>

extern int count_even(int number);

int main(){
	int number=23;

	std::cout << "The number is: " << count_even(number) << std::endl;

	return 0;
}