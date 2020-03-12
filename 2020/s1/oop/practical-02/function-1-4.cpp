#include <iostream>

void print_scaled_matrix(int array[3][3],int scale){
	int i=0;
	int j=0;

	for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				std::cout << array[i][j]*scale << " ";
			}

		std::cout << std::endl;

	}
}