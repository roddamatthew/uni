#include <iostream>

extern void print_scaled_matrix(int array[3][3],int scale);

int main(){
	int array1[3][3]={1,2,3,4,5,6,7,8,9};
	int array2[3][3]={2,4,6,8,10,12,14,16,18};
	int array3[3][3]={-1,1,1,1,1,1,1,1,-1};

	print_scaled_matrix(array1,2);
	print_scaled_matrix(array2,1);
	print_scaled_matrix(array3,4);

	return 0;
}