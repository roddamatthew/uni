#include <iostream>

void cpyda(double *old_array,double *new_array,int length){
	double* oldptr=old_array;
	double* newptr=new_array;


	for(int i=0; i<length; i++){
		*(newptr+i)=*(oldptr+i);
		
		// std::cout << newptr+i << std::endl;
		// std::cout << *(newptr+i) << std::endl;
	}
}