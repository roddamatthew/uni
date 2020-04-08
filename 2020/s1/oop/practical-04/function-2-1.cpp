#include <iostream>

void print_sevens(int *nums,int length){
	int i=0;

	for(i=0;i<length;i++){
		if(*(nums+i)%7==0){
			std::cout << *(nums+i) << std::endl;
		}
	}

}