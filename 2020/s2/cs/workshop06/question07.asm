// test header so that variables named in workshop
// questions will have known addresses we can test
	@x
	@y
	@sum
	@ptr
	@numbers
	@arr
// add your instructions after this line
	@x	//x = 0
	M=0
	
	@sum	//sum = 0
	M=0

(LOOP)
	@10	//Loop Control
	D=A
	@x
	D=D-M
	@END
	D;JLE
	
	@x	//sum = sum + x
	D=M
	@sum
	D=D+M
	M=D

	@x	//x = x + 1
	D=M+1
	M=D
	
	@LOOP	//Loop Control
	0;JMP
(END)
	
