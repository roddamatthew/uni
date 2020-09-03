// test header so that variables named in workshop
// questions will have known addresses we can test
	@x
	@y
	@sum
	@ptr
	@numbers
	@arr
// add your instructions after this line
	// x = arr[y]
	// First get arr[y]
	@arr
	D=M	// Storing arr in the D register
	@y
	A=D+M
	D=M
	// Now have arr[y] stored in the D register
	@x
	M=D
