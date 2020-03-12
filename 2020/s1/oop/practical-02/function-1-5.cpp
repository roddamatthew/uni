#include <iostream>

void print_summed_matrices(int array1[3][3],int array2[3][3]){
	int i=0;
	int j=0;

	for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				std::cout << array1[i][j]+array2[i][j] << " ";
			}

		std::cout << std::endl;

	}
}