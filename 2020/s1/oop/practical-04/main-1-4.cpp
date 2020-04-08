#include <iostream>

using namespace std;

extern void cpyda(double *old_array,double *new_array,int length);

int main(){
	int length=5;
	double array1[5]={1,2,3,4,5};
	double array2[5];
	double array3[5]={5,4,3,2,1};
	double array4[5];

	cpyda(array1,array2,length);
	cpyda(array3,array4,length);

	return 0;
}