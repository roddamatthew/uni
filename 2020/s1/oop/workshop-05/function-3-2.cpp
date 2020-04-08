#include <iostream>

int *reverseArray(int *numbers1,int length){
	int *reversed=new int[length];
	int j=length-1;

	for(int i=0; i<length; i++){
		*(reversed+j)=*(numbers1+i);
		j=j-1;
	}

	return reversed;
}