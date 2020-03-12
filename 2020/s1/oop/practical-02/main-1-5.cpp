#include <iostream>

extern void print_summed_matrices(int array1[3][3],int array2[3][3]);

int main(){
	int array1[3][3]={1,2,3,4,5,6,7,8,9};
	int array2[3][3]={2,4,6,8,10,12,14,16,18};
	int array3[3][3]={1,1,1,1,1,1,1,1,1};

	print_summed_matrices(array1,array2);
	print_summed_matrices(array1,array3);
	print_summed_matrices(array2,array3);

	return 0;
}