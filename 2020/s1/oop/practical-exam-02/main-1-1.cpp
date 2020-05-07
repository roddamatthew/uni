#include <iostream>

extern int* readNumbers(int n);
extern void printNumbers(int* array, int length);

int main(){
	int length=5;
	int* array;
	
	array=readNumbers(length);
	printNumbers(array,length);

	delete array;

	return 0;
}