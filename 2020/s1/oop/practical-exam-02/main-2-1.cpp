#include <iostream>

extern void months(int* monthNumbers,int length);
extern int* readNumbers(int n);

int main(){
	int length=5;
	int* array;
	
	array=readNumbers(length);
	months(array,length);

	return 0;
}