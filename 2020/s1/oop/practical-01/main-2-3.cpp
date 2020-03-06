#include <iostream>

extern void twofivenine(int array[], int n);

int main(){
	int array[9]={2,2,5,4,5,2,7,9,9};
	int array_size=9;

	twofivenine(array, array_size);

	return 0;
}