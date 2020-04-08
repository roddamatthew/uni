#include <iostream>

void cpyia(int old_array[],int new_array[],int length){
	// storing the address of the first element of the old array as a pointer called oldptr
	int* oldptr=old_array;
	// storing the address of the first element of the empty new array as a pointer called newptr
	int* newptr=new_array;

	// iterating over the length of the arrays
	for(int i=0; i<length; i++){
		// setting the value stored at the end of the newptr to the value stored at the end of the oldptr
		// iterating this over the length of the array, changing the next value in memory (4 bytes later)
		*(newptr+i)=*(oldptr+i);
		
		// // displaying the address in memory
		// std::cout << newptr+i << std::endl;
		// // displaying the value stored in that memory address
		// // note that *(newptr+i) could also be accessed using new_array[i]
		// std::cout << *(newptr+i) << std::endl;
	}
}