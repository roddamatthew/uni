#include <iostream>

using namespace std;

void copy_2d_strings(string first[][2], string second[][2], int n){
	int i=0;
	int j=0;

	for(i=0;i<3;i++){
		for(j=0;j<n;j++){
			second[i][j]=first[i][j];
		}
	}
}