// test header so that variables named in workshop
// questions will have known addresses we can test
	@x
	@y
	@sum
	@ptr
	@numbers
	@arr
// add your instructions after this line
	// Initialize x = 0
	@x
	M=0
	
	// Initialize sum = 0
	@sum
	M=0

(LOOP)
	@10		//Loop Control
	D=A
	@x
	D=D-M
	@END
	D;JLE

	@numbers	//sum = sum + numbers[x]
	D=M
	@x
	A=D+M
	D=M		//Now numbers[x] is in D
	@sum
	D=D+M
	M=D
		
	@x		//x = x + 1
	D=M+1
	M=D
	
	@LOOP		//Loop Control
	0;JMP
(END)
