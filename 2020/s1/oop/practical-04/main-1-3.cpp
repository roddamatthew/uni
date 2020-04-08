#include <iostream>

using namespace std;

extern void cpyia(int old_array[],int new_array[],int length);

int main(){
	int length=5;
	int array1[5]={1,2,3,4,5};
	int array2[5];
	int array3[5]={5,4,3,2,1};
	int array4[5];

	cpyia(array1,array2,length);
	cpyia(array3,array4,length);



	return 0;
}