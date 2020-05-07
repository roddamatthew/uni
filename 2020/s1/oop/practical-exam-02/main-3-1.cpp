#include <iostream>

extern int* readNumbers(int n);
extern void printNumbers(int* array, int length);
extern bool twinArray(int* array, int length);

int main(){
	int length=6;
	int* array;
	
	array=readNumbers(length);
	printNumbers(array,length);
	std::cout << twinArray(array, length) << std::endl;

	delete array;

	return 0;
}