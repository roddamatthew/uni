#include <iostream>

extern void print_sevens(int *nums,int length);

int main(){
	int array1[5]={7,14,28,4,35};
	int array2[5]={-2,4,7,84,56};

	print_sevens(array1,5);
	print_sevens(array2,5);

	return 0;
}