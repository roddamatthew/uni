// test header so that variables named in workshop
// questions will have known addresses we can test
	@x
	@y
	@sum
	@ptr
	@numbers
	@arr
// add your instructions after this line
	//x = *ptr++
	//Want to deference the value stored at the end of pointer
	//Then store this value in x
	//Then increment the pointer

	@ptr	//Storing the value of ptr in D register
	D=M
	A=D
	D=M	

	@x	//Setting x = ptr
	M=D
	
	@ptr	//Incrementing ptr
	D=M+1
	M=D
