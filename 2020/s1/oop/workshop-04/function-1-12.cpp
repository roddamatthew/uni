#include <iostream>

int size_of_variable_star_arr(){
	int a, *p;
	p=&a;
	int *t = new int;
	int *arr = new int[3];

	int size = sizeof(arr);
	delete[] arr;

	return size;
}