#include <iostream>

int size_of_array_arr(){
	int a, *p;
	p=&a;
	int *t = new int;
	int *arr = new int[3];

	int size = sizeof(*arr)+sizeof(*arr+1)+sizeof(*arr+2);

	return size;
}