#include <iostream>

using namespace std;

void copy_2d_strings(string first[][2], string second[][2], int n){
	int i=0;
	int j=0;

	for(i=0;i<n;i++){
		for(j=0;j<3;j++){
			second[i][j]=first[i][j];
		}
	}

	// for(i=0;i<n;i++){
	// 	for(j=0;j<3;j++){
	// 		std::cout << second[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }

}