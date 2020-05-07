#include <iostream>

extern int* mergeArrays(int* A, int* B, int length);
extern int* readNumbers(int n);
extern void printNumbers(int* array, int length);

int main(){
	int length=5;
	int *array1, *array2, *array3;
	
	array1=readNumbers(length);
	array2=readNumbers(length);

	array3=mergeArrays(array1,array2,length);
	printNumbers(array3,length*2);

	delete array1;
	delete array2;

	return 0;
}