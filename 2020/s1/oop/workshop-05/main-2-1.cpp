#include <iostream>

extern int *readNumbers();
extern void printNumbers(int *numbers,int length);
extern void hexDigits(int *numbers,int length);

int main(){
	int* array;
	int* pointer=array;
	array=readNumbers();
	hexDigits(array, 10);

	delete array;

	return 0;
}