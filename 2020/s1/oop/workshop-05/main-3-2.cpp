#include <iostream>

extern int *reverseArray(int *numbers1,int length);

void arrayPrinter(int* array, int length){
	int i=0;

	for(i=0;i<length;i++){
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

int main(){
	int array1[]={1,2,3,4,5};
	int array2[]={1,2,3,4,5};
	int array3[]={5,4,3,2,1};

	arrayPrinter(reverseArray(array1,5),5);
	arrayPrinter(reverseArray(array2,5),5);
	arrayPrinter(reverseArray(array3,5),5);

	return 0;
}